## Arduino Persian Reshaper
Reconstruct Persian/Arabic letters to be used in Arduino IDE and OLED/LCD display. This script is applicable to all Arduino family boards such as ESP8266/ESP32, Particle Photon, ....

All displays that can be set to ```pixel(x, y, color)``` can be used.

## Description
Persian/Arabic script is very special with two essential features:
1. It is written from right to left.
2. The characters change shape according to their surrounding characters.

## Prerequisites
First you need to install the [Adafruit GFX library](https://github.com/adafruit/Adafruit-GFX-Library) Then according to the type of display, install the library you need. Here I used the 128x64 display with SSD1306 chip driver So I installed the [Adafruit SSD1306] (https://github.com/adafruit/Adafruit_SSD1306) library.

## Usage
```
char txt[] = "فارسی نویسی در آردوینو";
PutCharPE(txt,ALINE_CENTER(txt),8,1,BLACK);

char NUM[] = "0123456789";   //For correct representation, the numbers must be reversed.
PutCharPE(strreverse(NUM),ALINE_CENTER(NUM),30,1,BLACK);
```

## Contact
Copyright (C) 2018 [Sadraldin Rastegar](mailto:s_qwerty13@live.com) and [Ramin Sangesari](mailto:r.sangsari@gmail.com).
