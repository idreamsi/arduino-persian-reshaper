## Arduino Persian Reshaper
Reconstruct Persian/Arabic letters to be used in Arduino IDE and OLED/LCD display. This script is applicable to all Arduino family boards such as ESP8266/ESP32, Particle Photon, ....

All displays and libraries that can be set to ```writepixel(x, y, color)``` can be used.

## Description
Persian/Arabic script is very special with two essential features:
1. It is written from right to left.
2. The characters change shape according to their surrounding characters.

The code attempts to resolve the problem of displaying letters and numbers in Persian/Arabic with a 8x8 font.

## Prerequisites
First you need to install the [Adafruit GFX library](https://github.com/adafruit/Adafruit-GFX-Library) (for drawing shapes, lines, ...) then according to the type of display, install the library you need. Here I used the 128x64 display with SSD1306 chip driver so I installed the [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306) library.

## Usage
Change the following lines according to the library you are using:
```
//This section should be modified according to your display type and library
#define setpixel(x, y, color)           display.writePixel(x, y, color)
#define LCDWidth                        display.width()

//This example is for a 128x64 (SSD1306 chip driver) size display using Hardware SPI
#define OLED_DC                          4
#define OLED_CS                         12
#define OLED_RESET                       6
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);
```
Finally, run the following code:
```
char txt[] = "فارسی نویسی در آردوینو";
PutCharPE(txt,ALINE_CENTER(txt),8,1,BLACK);

char NUM[] = "0123456789";              //For correct representation, the numbers must be reversed.
PutCharPE(strreverse(NUM),ALINE_CENTER(NUM),30,1,BLACK);
```

## Contact
Copyright (C) 2018 [Sadraldin Rastegar](mailto:s_qwerty13@live.com) and [Ramin Sangesari](mailto:r.sangsari@gmail.com).
