# USB-Driver_Missile-Launcher

This repository holds the driver code used to control the [Dream Cheeky USB Missile Launcher](https://www.amazon.com/Dream-Cheeky-908-Electronic-Reference/dp/B004SAYO46) with a high-level C code.

This project involved writing the USB driver necessary to send/receive the proper data packets to the Dream Cheeky launcher over USB, as well as develop high-level C programs to send messages to the launcher in sequence, as well as allow user control through the keyboard.

## Linux Host system
This project uses the Xilinx Zedboard as the linux host running the driver code and user-level application.

## File Descriptions
All relevant software files are contained in ```driver_sw/drivers```
```launcher_driver.c``` - kernel code defining the USB driver
```launcher_fire_buttons.{c,h}``` - control the missile launcher using the pushbuttons on the Xilinx Zedboard
```launcher_fire_keyboard.{c,c}``` - control the missile launcher using keyboard input through stdin
```setup_zynq.sh``` - helper script to properly set up usb driver once linux boots up
