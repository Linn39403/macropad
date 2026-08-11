#!/usr/bin/env python3
"""Patch a four-key macropad lock PIN into a copy of an RP2040 UF2 image."""

from __future__ import annotations

import argparse
from pathlib import Path
import struct
import sys


UF2_BLOCK_SIZE = 512
UF2_HEADER_SIZE = 32
UF2_DATA_SIZE = 476
UF2_MAGIC_START0 = 0x0A324655
UF2_MAGIC_START1 = 0x9E5D5157
UF2_MAGIC_END = 0x0AB16F30

PIN_MAGIC = b"MPLOCK01"
PIN_VERSION = 1
PIN_LENGTH = 4
PIN_GUARD = bytes((0xA5, 0x5A, 0xC3))
PIN_RECORD_SIZE = len(PIN_MAGIC) + 1 + PIN_LENGTH + 1 + len(PIN_GUARD)


class PinConfigurationError(RuntimeError):
    """The PIN file or UF2 image cannot be configured safely."""


def pin_checksum(pin: list[int] | bytes) -> int:
    checksum = 0xA5
    for key in pin:
        checksum = ((checksum << 1) | (checksum >> 7)) & 0xFF
        checksum ^= key
    return checksum


def read_pin(pin_file: Path) -> list[int]:
    try:
        values = pin_file.read_text(encoding="ascii").split()
    except OSError as error:
        raise PinConfigurationError(f"Could not read PIN file {pin_file}: {error}") from error

    if len(values) != PIN_LENGTH:
        raise PinConfigurationError(f"PIN file must contain exactly {PIN_LENGTH} key numbers (1 through 20).")
    try:
        pin = [int(value, 10) for value in values]
    except ValueError as error:
        raise PinConfigurationError("PIN file may contain only decimal key numbers.") from error
    if any(key < 1 or key > 20 for key in pin):
        raise PinConfigurationError("Each PIN key number must be in the inclusive range 1 through 20.")
    return pin


def validate_uf2(image: bytearray) -> None:
    if not image or len(image) % UF2_BLOCK_SIZE:
        raise PinConfigurationError("Input is not a whole-block UF2 file.")

    for offset in range(0, len(image), UF2_BLOCK_SIZE):
        magic0, magic1, _, _, payload_size, _, _, _ = struct.unpack_from("<8I", image, offset)
        magic_end = struct.unpack_from("<I", image, offset + UF2_BLOCK_SIZE - 4)[0]
        if magic0 != UF2_MAGIC_START0 or magic1 != UF2_MAGIC_START1 or magic_end != UF2_MAGIC_END:
            raise PinConfigurationError(f"Invalid UF2 magic values in block {offset // UF2_BLOCK_SIZE}.")
        if payload_size > UF2_DATA_SIZE:
            raise PinConfigurationError(f"Invalid UF2 payload size in block {offset // UF2_BLOCK_SIZE}.")


def find_pin_record(image: bytearray) -> int:
    matches: list[int] = []
    for block_offset in range(0, len(image), UF2_BLOCK_SIZE):
        payload_size = struct.unpack_from("<I", image, block_offset + 16)[0]
        data_start = block_offset + UF2_HEADER_SIZE
        data_end = data_start + payload_size
        search_start = data_start
        while True:
            match = image.find(PIN_MAGIC, search_start, data_end)
            if match < 0:
                break
            if match + PIN_RECORD_SIZE <= data_end:
                matches.append(match)
            search_start = match + 1

    if len(matches) != 1:
        raise PinConfigurationError(
            f"Expected exactly one lock PIN record marker in the UF2; found {len(matches)}. Rebuild firmware and retry."
        )
    return matches[0]


def patch_pin(image: bytearray, pin: list[int]) -> None:
    record_offset = find_pin_record(image)
    version_offset = record_offset + len(PIN_MAGIC)
    pin_offset = version_offset + 1
    checksum_offset = pin_offset + PIN_LENGTH
    guard_offset = checksum_offset + 1

    if image[version_offset] != PIN_VERSION or bytes(image[guard_offset:guard_offset + len(PIN_GUARD)]) != PIN_GUARD:
        raise PinConfigurationError("Lock PIN record format is not supported by this configuration tool.")
    if any(image[pin_offset:pin_offset + PIN_LENGTH]) or image[checksum_offset] != 0:
        raise PinConfigurationError("UF2 already contains a configured PIN; rebuild before configuring a new one.")

    image[pin_offset:pin_offset + PIN_LENGTH] = bytes(pin)
    image[checksum_offset] = pin_checksum(pin)


def configure(input_uf2: Path, output_uf2: Path, pin_file: Path) -> None:
    try:
        image = bytearray(input_uf2.read_bytes())
    except OSError as error:
        raise PinConfigurationError(f"Could not read UF2 file {input_uf2}: {error}") from error

    pin = read_pin(pin_file)
    validate_uf2(image)
    patch_pin(image, pin)
    try:
        output_uf2.parent.mkdir(parents=True, exist_ok=True)
        output_uf2.write_bytes(image)
    except OSError as error:
        raise PinConfigurationError(f"Could not write configured UF2 {output_uf2}: {error}") from error


def parse_args(argv: list[str] | None = None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--pin-file", type=Path, required=True, help="four key numbers in the range 1..20")
    parser.add_argument("--input", type=Path, required=True, dest="input_uf2", help="unconfigured input UF2")
    parser.add_argument("--output", type=Path, required=True, dest="output_uf2", help="configured output UF2")
    return parser.parse_args(argv)


def main(argv: list[str] | None = None) -> int:
    args = parse_args(argv)
    try:
        configure(args.input_uf2, args.output_uf2, args.pin_file)
    except PinConfigurationError as error:
        print(f"error: {error}", file=sys.stderr)
        return 1
    print(f"Configured lock PIN in {args.output_uf2}.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
