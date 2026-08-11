import importlib.util
from pathlib import Path
import struct
import sys
import tempfile
import unittest


MODULE_PATH = Path(__file__).parents[1] / "configure_lock_pin.py"
SPEC = importlib.util.spec_from_file_location("configure_lock_pin", MODULE_PATH)
configure_lock_pin = importlib.util.module_from_spec(SPEC)
assert SPEC.loader is not None
sys.modules[SPEC.name] = configure_lock_pin
SPEC.loader.exec_module(configure_lock_pin)


def make_uf2(pin_record_count=1):
    blocks = bytearray()
    for block_number in range(max(pin_record_count, 1)):
        block = bytearray(configure_lock_pin.UF2_BLOCK_SIZE)
        struct.pack_into(
            "<8I",
            block,
            0,
            configure_lock_pin.UF2_MAGIC_START0,
            configure_lock_pin.UF2_MAGIC_START1,
            0,
            0x10000000 + block_number * 256,
            256,
            block_number,
            max(pin_record_count, 1),
            0,
        )
        if block_number < pin_record_count:
            record = (
                configure_lock_pin.PIN_MAGIC
                + bytes([configure_lock_pin.PIN_VERSION])
                + bytes(4)
                + bytes([0])
                + configure_lock_pin.PIN_GUARD
            )
            block[configure_lock_pin.UF2_HEADER_SIZE + 64:configure_lock_pin.UF2_HEADER_SIZE + 64 + len(record)] = record
        struct.pack_into("<I", block, configure_lock_pin.UF2_BLOCK_SIZE - 4, configure_lock_pin.UF2_MAGIC_END)
        blocks.extend(block)
    return blocks


class ConfigureLockPinTests(unittest.TestCase):
    def test_configure_patches_only_the_pin_record(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            input_uf2 = root / "input.uf2"
            output_uf2 = root / "output.uf2"
            pin_file = root / "lock_pin.txt"
            input_uf2.write_bytes(make_uf2())
            pin_file.write_text("7 12 5 18\n", encoding="ascii")

            configure_lock_pin.configure(input_uf2, output_uf2, pin_file)

            output = bytearray(output_uf2.read_bytes())
            record_start = configure_lock_pin.UF2_HEADER_SIZE + 64
            pin_start = record_start + len(configure_lock_pin.PIN_MAGIC) + 1
            self.assertEqual(list(output[pin_start:pin_start + 4]), [7, 12, 5, 18])
            self.assertEqual(output[pin_start + 4], configure_lock_pin.pin_checksum([7, 12, 5, 18]))

    def test_read_pin_rejects_out_of_range_key(self):
        with tempfile.TemporaryDirectory() as directory:
            pin_file = Path(directory) / "lock_pin.txt"
            pin_file.write_text("1 2 3 21\n", encoding="ascii")
            with self.assertRaises(configure_lock_pin.PinConfigurationError):
                configure_lock_pin.read_pin(pin_file)

    def test_patch_rejects_ambiguous_pin_marker(self):
        with self.assertRaises(configure_lock_pin.PinConfigurationError):
            configure_lock_pin.patch_pin(make_uf2(pin_record_count=2), [1, 2, 3, 4])


if __name__ == "__main__":
    unittest.main()
