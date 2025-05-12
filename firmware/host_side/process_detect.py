import win32gui
import win32process
import psutil
import time

selected_titles = {'Total Commander' : 'app_ttc', 
                   'Calculator' : 'app_cal'}
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

def main():
    print("Detecting active application... (Press Ctrl+C to stop)")
    last_window_title = ""
    try:
        while True:
            # Get current active window info
            process_name, window_title = get_active_window_info()

            # Filter out selected processes 
            #if window_title and window_title != last_window_title:
                #for selected, cmd_frame in selected_titles.items():
                #    if selected.lower() in window_title.lower():
                #        print("YES, selected process : ", window_title)
                #        print("Command frame: ", cmd_frame)
                #        break
                #last_window_title = window_title
            # Only print if the window has changed to avoid spamming
            if window_title and window_title != last_window_title:
                print(window_title)
                last_window_title = window_title

            # Sleep briefly to reduce CPU usage
            time.sleep(0.5)

    except KeyboardInterrupt:
        print("\nStopped by user.")

if __name__ == "__main__":
    main()