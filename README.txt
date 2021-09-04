# rtc_controller_hari
Automatic lights and fan controller using RTC module interfaced with PIC 8 bit microcontroller

Files included:

- bh1750 - header which included functions for light sensor
- lcd - header which included functions for lcd
- functions - header which contains general purpose functions for control
- eeprom - header which contains functions for eeprom
- main - main source file

Working :

-LCD
-EEPROM
-Relay controls

Not working :

-Light sensor
-Interface with light sensor
-Control conditions based on data from light sensor
-Change functionality of RTC based controls
Current build :

-RTC readings are used to control relays
-I/O configuration properly working
-RTC error correction working

Future build :

-Use light sensor data instead of RTC for relay control

