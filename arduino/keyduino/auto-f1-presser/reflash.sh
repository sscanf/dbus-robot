#!/bin/sh
ACTION=$1

if [ -z "$ACTION" ] ; then
    echo "Don't run this script directly; inspect it and take what you need"
    exit 1
fi

# http://mitchtech.net/arduino-usb-hid-keyboard/ uses at90usb82 but only
# atmega16u2 worked for me

if [ "$ACTION" = "dump" ]; then 
    # Dump current firmware (test)
    dfu-programmer atmega16u2 dump
fi

if [ "$ACTION" = "devel" ]; then
    # Erase and re-flash current firmware (test, also reset for loading new code)
    dfu-programmer atmega16u2 erase
    dfu-programmer atmega16u2 flash --debug 1 Arduino-usbserial-uno.hex
    dfu-programmer atmega16u2 reset
fi

if [ "$ACTION" = "keyboard" ]; then
    # Erase and re-flash keyboard firmware
    dfu-programmer atmega16u2 erase
    dfu-programmer atmega16u2 flash --debug 1 Arduino-keyboard-0.3.hex.1
    dfu-programmer atmega16u2 reset
fi
