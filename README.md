## Arduino Persian Reshaper
Reconstruct Persian/Arabic letters to be used in Arduino IDE and OLED/LCD display. This script is compatible to all Arduino family boards such as Arduboy, ESP8266/ESP32, Particle Photon, ....

All displays and libraries that can be set to ```writepixel(x, y, color)``` can be used and there is no limit.

## Description
Persian/Arabic script is very special with two essential features:
- It is written from right to left.
- The characters change shape according to their surrounding characters.

The code attempts to resolve the problem of displaying letters and numbers in Persian/Arabic with a [8x8 font](https://raw.githubusercontent.com/idreamsi/arduino-persian-reshaper/master/8x8_FONT.bmp).

## Screenshot
![Persian Letters on Arduboy](https://raw.githubusercontent.com/idreamsi/arduino-persian-reshaper/master/arduboy.jpg)
![Persian Letters on Wemos D1 mini](https://raw.githubusercontent.com/idreamsi/arduino-persian-reshaper/master/wemos_d1_mini.jpg)
![Persian Letters on Particle Photon](https://raw.githubusercontent.com/idreamsi/arduino-persian-reshaper/master/particle_photon.jpg)

## Prerequisites
First you need to install the [Adafruit GFX library](https://github.com/adafruit/Adafruit-GFX-Library) (for drawing shapes, lines, ...) of course this is optional, then according to the type of display, install the library you need. Here I used the [128x64 display with SSD1306](https://www.adafruit.com/product/326) chip driver so I installed the [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306) library.

## Download & Usage
Download/Clone repository, change the following lines according to the library you are using:
```
//This section should be modified according to your display type and library
#define setpixel(x, y, color)           display.writePixel(x, y, color)
#define LCDWidth                        display.width()

//If you use SPI display, change the following lines according to your display type (I used the Arduboy)
#define OLED_DC                         4
#define OLED_CS                         12
#define OLED_RESET                      6
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);

//If you use i2c display, uncomment this part.
/*
#define OLED_RESET                      4
Adafruit_SSD1306 display(OLED_RESET);
*/

```
Finally, change the following lines and then upload on the Arduino board:
```
char txt[] = "فارسی نویسی در آردوینو";
PutCharPE(txt,ALINE_CENTER(txt),8,1,BLACK);

char NUM[] = "0123456789";              //For correct representation, the numbers must be reversed.
PutCharPE(strreverse(NUM),ALINE_CENTER(NUM),30,1,BLACK);
```

[راهنمای استفاده به زبان فارسی](http://www.idreams.ir/%d8%b1%d8%a7%d9%87%d9%86%d9%85%d8%a7%db%8c-%d9%81%d8%a7%d8%b1%d8%b3%db%8c-%d9%86%d9%88%db%8c%d8%b3%db%8c-%d8%b1%d9%88%db%8c-%d9%86%d9%85%d8%a7%db%8c%d8%b4%da%af%d8%b1%d9%87%d8%a7%db%8c-%d9%be%db%8c/)

## Contact
Copyright (C) 2018 [Sadraldin Rastegar](mailto:s_qwerty13@live.com) and [Ramin Sangesari](mailto:r.sangsari@gmail.com).

## Donation
If this project help you reduce time to develop, you can give me a cup of coffee :)

- Donate via Bitcoin: 176H7tbpfyUVKiwkkwj6BJfC1X7hQWTq8v
- [Donate via IDPay](https://idpay.ir/idreams)
