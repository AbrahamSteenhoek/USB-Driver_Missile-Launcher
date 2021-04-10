#!/bin/bash
cd /lib; ln -s ld-linux.so.3 ld-linux-armhf.so.3
echo “1-1:1.0” > /sys/bus/usb/drivers/usbhid/unbind
rx launcher_driver.ko ; rx launcher_fire_keyboard