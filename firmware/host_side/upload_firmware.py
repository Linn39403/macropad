#!/usr/bin/env python3
"""Enter the macropad RP2040 bootloader over Raw HID and copy a UF2 image."""

from __future__ import annotations

import argparse
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import time
from dataclasses import dataclass
from typing import Any, Iterable

try:
    import hid
except ImportError:  # Report a useful error only when HID access is requested.
    hid = None


VENDOR_ID = 0xFEED
PRODUCT_ID = 0x6060
USAGE_PAGE = 0xFF60
USAGE = 0x61
RAW_HID_REPORT_SIZE = 32
BOOTLOADER_COMMAND = b"rst_"
BOOTLOADER_LABEL = "RPI-RP2"


class UploadError(RuntimeError):
    """A recoverable problem while entering the bootloader or copying firmware."""


@dataclass(frozen=True)
class BootloaderVolume:
    device: str
    mountpoint: Path | None


def find_raw_hid_path() -> bytes:
    if hid is None:
        raise UploadError("Python package 'hid' is required (install python3-hid or hidapi).")

    for interface in hid.enumerate(VENDOR_ID, PRODUCT_ID):
        if interface.get("usage_page") == USAGE_PAGE and interface.get("usage") == USAGE:
            return interface["path"]
    raise UploadError(
        f"Macropad Raw HID interface {VENDOR_ID:#06x}:{PRODUCT_ID:#06x} was not found."
    )


def enter_bootloader() -> None:
    """Send the firmware's `rst_` command and let the USB device disconnect."""
    path = find_raw_hid_path()
    report = bytes([0]) + BOOTLOADER_COMMAND.ljust(RAW_HID_REPORT_SIZE, b"\0")
    device = hid.Device(path=path)
    try:
        written = device.write(report)
    finally:
        device.close()

    if written != len(report):
        raise UploadError(f"Bootloader command write was incomplete ({written}/{len(report)} bytes).")


def _walk_block_devices(devices: Iterable[dict[str, Any]]) -> Iterable[dict[str, Any]]:
    for device in devices:
        yield device
        yield from _walk_block_devices(device.get("children") or [])


def find_bootloader_volume() -> BootloaderVolume | None:
    result = subprocess.run(
        ["lsblk", "--json", "--output", "PATH,LABEL,MOUNTPOINT"],
        check=False,
        capture_output=True,
        text=True,
    )
    if result.returncode != 0:
        raise UploadError(f"lsblk failed: {result.stderr.strip() or 'unknown error'}")

    try:
        devices = json.loads(result.stdout).get("blockdevices", [])
    except json.JSONDecodeError as error:
        raise UploadError(f"Could not parse lsblk output: {error}") from error

    for device in _walk_block_devices(devices):
        if device.get("label") == BOOTLOADER_LABEL and device.get("path"):
            mountpoint = device.get("mountpoint")
            return BootloaderVolume(device["path"], Path(mountpoint) if mountpoint else None)
    return None


def wait_for_bootloader(timeout: float, poll_interval: float = 0.25) -> BootloaderVolume:
    deadline = time.monotonic() + timeout
    while time.monotonic() < deadline:
        volume = find_bootloader_volume()
        if volume is not None:
            return volume
        time.sleep(poll_interval)
    raise UploadError(f"Timed out after {timeout:g}s waiting for the {BOOTLOADER_LABEL} bootloader volume.")


def ensure_mounted(volume: BootloaderVolume, timeout: float) -> Path:
    if volume.mountpoint is not None and volume.mountpoint.is_dir():
        return volume.mountpoint

    try:
        result = subprocess.run(
            ["udisksctl", "mount", "--block-device", volume.device],
            check=False,
            capture_output=True,
            text=True,
        )
    except FileNotFoundError as error:
        raise UploadError(
            f"{BOOTLOADER_LABEL} is not mounted and udisksctl is unavailable; mount {volume.device} and retry."
        ) from error
    if result.returncode != 0:
        raise UploadError(
            f"Could not mount {volume.device}: {result.stderr.strip() or result.stdout.strip()}"
        )

    deadline = time.monotonic() + timeout
    while time.monotonic() < deadline:
        refreshed = find_bootloader_volume()
        if refreshed is not None and refreshed.mountpoint is not None and refreshed.mountpoint.is_dir():
            return refreshed.mountpoint
        time.sleep(0.25)
    raise UploadError(f"Timed out after {timeout:g}s waiting for {BOOTLOADER_LABEL} to mount.")


def copy_firmware(firmware: Path, mountpoint: Path) -> Path:
    destination = mountpoint / firmware.name
    try:
        with firmware.open("rb") as source, destination.open("wb") as target:
            shutil.copyfileobj(source, target)
            target.flush()
            os.fsync(target.fileno())
    except OSError as error:
        raise UploadError(f"Could not copy {firmware} to {mountpoint}: {error}") from error
    return destination


def wait_for_bootloader_exit(timeout: float, poll_interval: float = 0.25) -> None:
    deadline = time.monotonic() + timeout
    while time.monotonic() < deadline:
        if find_bootloader_volume() is None:
            return
        time.sleep(poll_interval)
    raise UploadError(f"Firmware was copied, but {BOOTLOADER_LABEL} did not disconnect within {timeout:g}s.")


def parse_args(argv: list[str] | None = None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--firmware", type=Path, required=True, help="UF2 firmware image to upload")
    parser.add_argument("--boot-timeout", type=float, default=20.0, help="seconds to wait for bootloader (default: 20)")
    parser.add_argument("--exit-timeout", type=float, default=10.0, help="seconds to wait for firmware reboot (default: 10)")
    return parser.parse_args(argv)


def main(argv: list[str] | None = None) -> int:
    args = parse_args(argv)
    firmware = args.firmware.resolve()
    if firmware.suffix.lower() != ".uf2":
        print(f"error: firmware must be a .uf2 file: {firmware}", file=sys.stderr)
        return 2
    if not firmware.is_file():
        print(f"error: firmware file does not exist: {firmware}", file=sys.stderr)
        return 2
    if args.boot_timeout <= 0 or args.exit_timeout <= 0:
        print("error: timeouts must be greater than zero", file=sys.stderr)
        return 2

    try:
        print("Requesting RP2040 bootloader over Raw HID...")
        enter_bootloader()
        volume = wait_for_bootloader(args.boot_timeout)
        mountpoint = ensure_mounted(volume, args.boot_timeout)
        destination = copy_firmware(firmware, mountpoint)
        print(f"Copied {firmware.name} to {destination}; waiting for the RP2040 to reboot...")
        wait_for_bootloader_exit(args.exit_timeout)
    except UploadError as error:
        print(f"error: {error}", file=sys.stderr)
        return 1

    print("Firmware upload completed successfully.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
