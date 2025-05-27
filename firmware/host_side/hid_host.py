import sys
import hid
import psutil
import win32gui
import win32process
import time
from datetime import datetime
from time import sleep
from pycaw.pycaw import AudioUtilities, IAudioEndpointVolume
from comtypes import CLSCTX_ALL, CoInitialize, CoUninitialize
import ctypes

vendor_id = 0xFEED
product_id = 0x6060
usage_page = 0xFF60
usage = 0x61
report_length = 32

window_volume = 0
window_volume_prev = 0
selected_applications = {'Total Commander': 'app_ttc', 'Calculator': 'app_cal'}

# Initialize COM once at the start
def initialize_com():
    CoInitialize()  # Initialize COM in the single-threaded apartment (STA)

# Clean up COM at the end
def uninitialize_com():
    CoUninitialize()

# Cache the volume interface to avoid repeated creation
class SystemVolume:
    def __init__(self):
        self.devices = AudioUtilities.GetSpeakers()
        self.interface = self.devices.Activate(IAudioEndpointVolume._iid_, CLSCTX_ALL, None)
        self.volume = ctypes.cast(self.interface, ctypes.POINTER(IAudioEndpointVolume))

    def get_volume(self):
        return self.volume.GetMasterVolumeLevelScalar() * 100

    def __del__(self):
        # Ensure proper cleanup of COM objects
        if self.interface:
            self.interface.Release()

def get_window_volume(volume_obj):
    return int(volume_obj.get_volume())

def window_volume_send(volume):
    volume_str = f"{volume:03}"
    command = "vol_" + volume_str
    send_raw_report(list(command.encode('ascii')))

def get_raw_hid_interface():
    device_interfaces = hid.enumerate(vendor_id, product_id)
    raw_hid_interfaces = [i for i in device_interfaces if i['usage_page'] == usage_page and i['usage'] == usage]

    if not raw_hid_interfaces:
        return None

    interface = hid.Device(path=raw_hid_interfaces[0]['path'])
    print(f"Manufacturer: {interface.manufacturer}")
    print(f"Product: {interface.product}")
    return interface

def send_raw_report(data):
    interface = get_raw_hid_interface()
    if interface is None:
        print("No device found")
        sys.exit(1)

    request_data = [0x00] * (report_length + 1)  # First byte is Report ID
    request_data[1:len(data) + 1] = data
    request_report = bytes(request_data)

    print("Request:")
    print(request_report)

    try:
        interface.write(request_report)
        response_report = interface.read(report_length, timeout=1000)
        print("Response:")
        print(response_report)
    finally:
        interface.close()

def get_time():
    current_time = datetime.now()
    time_str = current_time.strftime("%H%M%S")
    return "ti" + time_str

def get_system_usage():
    try:
        cpu_percent = psutil.cpu_percent(interval=1)
        memory = psutil.virtual_memory()
        total_memory = memory.total / (1024 ** 3)  # Convert bytes to GB
        used_memory = memory.used / (1024 ** 3)    # Convert bytes to GB
        memory_percent = memory.percent
        return cpu_percent, total_memory, used_memory, memory_percent
    except Exception as e:
        print(f"Error: {e}")
        return None, None, None, None

def get_active_window_info():
    try:
        hwnd = win32gui.GetForegroundWindow()
        if not hwnd:
            return None, None
        window_title = win32gui.GetWindowText(hwnd)
        _, pid = win32process.GetWindowThreadProcessId(hwnd)
        process = psutil.Process(pid)
        process_name = process.name()
        return process_name, window_title
    except Exception as e:
        print(f"Error: {e}")
        return None, None

if __name__ == '__main__':
    initialize_com()  # Initialize COM at the start
    volume_obj = SystemVolume()  # Create a single volume object
    last_window_title = ""
    try:
        while True:
            process_name, window_title = get_active_window_info()
            is_found = False
            if window_title and window_title != last_window_title:
                for selected_title, cmd_frame in selected_applications.items():
                    if selected_title.lower() in window_title.lower():
                        is_found = True
                        print("YES, selected process:", window_title)
                        print("Command frame:", cmd_frame)
                        break
                last_window_title = window_title

            if is_found:
                send_raw_report(list(cmd_frame.encode('ascii')))

            window_volume = get_window_volume(volume_obj)
            if window_volume != window_volume_prev:
                window_volume_send(window_volume)
                window_volume_prev = window_volume

            time.sleep(0.05)

    except KeyboardInterrupt:
        print("\nStopped by user.")
    finally:
        uninitialize_com()  # Clean up COM when done