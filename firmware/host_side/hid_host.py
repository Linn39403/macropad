import sys
import hid
import psutil
import win32gui, win32process
import time
from datetime import datetime
from time import sleep
from pycaw.pycaw import AudioUtilities, IAudioEndpointVolume
from comtypes import CLSCTX_ALL
import ctypes

vendor_id     = 0xFEED
product_id    = 0x6060

usage_page    = 0xFF60
usage         = 0x61
report_length = 32

window_volume = 0
window_volume_prev = 0
selected_applications = {'Total Commander' : 'app_ttc',
                          'Calculator' : 'app_cal'}
              
def get_window_volume():
    return int(get_system_volume()) 
    
def window_volume_send(volume):
    #window_volume = int(get_system_volume())
    volume_str = f"{volume:03}"
    command = "vol_" + volume_str
    send_raw_report(list(command.encode('ascii')))

def get_system_volume():
    devices = AudioUtilities.GetSpeakers()
    interface = devices.Activate(IAudioEndpointVolume._iid_, CLSCTX_ALL, None)
    volume = ctypes.cast(interface, ctypes.POINTER(IAudioEndpointVolume))
    return volume.GetMasterVolumeLevelScalar() * 100
    
def get_raw_hid_interface():
    device_interfaces = hid.enumerate(vendor_id, product_id)
    raw_hid_interfaces = [i for i in device_interfaces if i['usage_page'] == usage_page and i['usage'] == usage]

    if len(raw_hid_interfaces) == 0:
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

    request_data = [0x00] * (report_length + 1) # First byte is Report ID
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
    # Get current time
    current_time = datetime.now()
    
    # Format as HHMMSS (always two digits)
    time_str = current_time.strftime("%H%M%S")
    return "ti"+time_str    

def get_system_usage():
    try:
        # Get CPU usage percentage (interval=1 means measure over 1 second)
        cpu_percent = psutil.cpu_percent(interval=1)

        # Get RAM usage
        memory = psutil.virtual_memory()
        total_memory = memory.total / (1024 ** 3)  # Convert bytes to GB
        used_memory = memory.used / (1024 ** 3)    # Convert bytes to GB
        memory_percent = memory.percent            # Percentage used

        return cpu_percent, total_memory, used_memory, memory_percent
    except Exception as e:
        print(f"Error: {e}")
        return None, None, None, None

def get_active_window_info():
    try:
        # Get the handle of the foreground window
        hwnd = win32gui.GetForegroundWindow()
        if not hwnd:
            return None, None

        # Get the window title
        window_title = win32gui.GetWindowText(hwnd)

        # Get the process ID associated with the window
        _, pid = win32process.GetWindowThreadProcessId(hwnd)

        # Get the process name using psutil
        process = psutil.Process(pid)
        process_name = process.name()

        return process_name, window_title
    except Exception as e:
        print(f"Error: {e}")
        return None, None
    
if __name__ == '__main__':
    last_window_title = ""
    try:
       while True:
            #Get current active window info
            process_name, window_title = get_active_window_info()
            #filter out selected processes
            is_found = False
            if window_title and window_title != last_window_title:
                for selected_title, cmd_frame in selected_applications.items():
                    if selected_title.lower() in window_title.lower():
                        is_found = True
                        print("YES, selected process : ", window_title)
                        print("Command frame: ", cmd_frame)
                        break
                last_window_title = window_title
            
            #Sleep briefly to reduce CPU usage
            if(is_found):
                send_raw_report(list(cmd_frame.encode('ascii')))
 
            window_volume = get_window_volume() 
            if(window_volume != window_volume_prev):
                window_volume_send(window_volume)
                #update the volume
                window_volume_prev = window_volume
            
            time.sleep(0.05)
            
    except KeyboardInterrupt:
        print("\nStopped by user.")
