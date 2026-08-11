import importlib.util
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import MagicMock, patch


MODULE_PATH = Path(__file__).parents[1] / "upload_firmware.py"
SPEC = importlib.util.spec_from_file_location("upload_firmware", MODULE_PATH)
upload_firmware = importlib.util.module_from_spec(SPEC)
assert SPEC.loader is not None
sys.modules[SPEC.name] = upload_firmware
SPEC.loader.exec_module(upload_firmware)


class UploadFirmwareTests(unittest.TestCase):
    def test_enter_bootloader_sends_the_padded_raw_hid_command(self):
        device = MagicMock()
        device.write.return_value = 33
        hid_module = MagicMock()
        hid_module.enumerate.return_value = [{
            "path": b"/dev/hidraw0",
            "usage_page": upload_firmware.USAGE_PAGE,
            "usage": upload_firmware.USAGE,
        }]
        hid_module.Device.return_value = device

        with patch.object(upload_firmware, "hid", hid_module):
            upload_firmware.enter_bootloader()

        expected = bytes([0]) + b"rst_".ljust(32, b"\0")
        device.write.assert_called_once_with(expected)
        device.close.assert_called_once_with()

    def test_find_bootloader_volume_recurses_and_uses_label(self):
        lsblk = {
            "blockdevices": [
                {"path": "/dev/sda", "label": None, "mountpoint": None, "children": [
                    {"path": "/dev/sda1", "label": "RPI-RP2", "mountpoint": "/media/test/RPI-RP2"}
                ]}
            ]
        }
        completed = subprocess.CompletedProcess([], 0, json.dumps(lsblk), "")
        with patch.object(upload_firmware.subprocess, "run", return_value=completed):
            volume = upload_firmware.find_bootloader_volume()

        self.assertEqual(volume.device, "/dev/sda1")
        self.assertEqual(volume.mountpoint, Path("/media/test/RPI-RP2"))

    def test_copy_firmware_writes_the_exact_uf2_data(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            firmware = root / "firmware.uf2"
            mountpoint = root / "RPI-RP2"
            firmware.write_bytes(b"UF2 test data")
            mountpoint.mkdir()

            destination = upload_firmware.copy_firmware(firmware, mountpoint)

            self.assertEqual(destination.read_bytes(), b"UF2 test data")

    def test_non_uf2_input_is_rejected(self):
        with tempfile.TemporaryDirectory() as directory:
            image = Path(directory) / "firmware.bin"
            image.write_bytes(b"test")
            self.assertEqual(upload_firmware.main(["--firmware", str(image)]), 2)


if __name__ == "__main__":
    unittest.main()
