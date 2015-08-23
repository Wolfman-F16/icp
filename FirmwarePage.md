# Firmware #

## Fuses ##
The ATmega8 has to be changed to the following fuse settings to make use of the 12 MHz crystal quarz
> LFuse 0xCE
> HFuse 0xD9

## Driver ##
No drivers need to be installed, the HID Joystick driver is used.

## Missing Button signals ##
32 buttons are actually not enough for all switches and buttons to work.
Falcon BMS 4.32 does however support Press/Release configuration of DX buttons. This technique allows full operation of all switches and buttons.

## HUD ##
The brightness of the HUD in Falcon BMS 4.32 can be controlled by an analog axis.
However, Falcon BMS 4.32 requires the Signal SimHudOn to switch the HUD display on.
This has to be done at least once at RAMP start, before the analog axis can control the brightness of the HUD.
Therefore a short button signal is emitted, when the Sym Wheel is turned up. This can be mapped to SimHudOn, resulting in normal control of the HUD brightness.