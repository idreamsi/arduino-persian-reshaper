// Arduino-Persian-Reshaper
// Copyright (C) 2018 Sadraldin Rastegar and Ramin Sangesari
// https://github.com/idreamsi/arduino-persian-reshaper

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//This section should be modified according to your display type and library
#define setpixel(x, y, color)           display.writePixel(x, y, color)
#define LCDWidth                        display.width()
#define ALINE_CENTER(t)	                (LCDWidth - ((LCDWidth - (LCDWidth - CalcTextWidth(t))) / 2)) - 2
#define ALINE_RIGHT                     LCDWidth
#define ALINE_LEFT(t)                   LCDWidth - CalcTextWidth(t)

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

#if (SSD1306_LCDHEIGHT != 64)
  #error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

//Persian letters 8x8
const unsigned char alef1 [] PROGMEM= {
0x00, 0x1C, 0x20, 0x08, 0x08, 0x08, 0x08, 0x00, 
};
const unsigned char alef2 [] PROGMEM= {
0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00,  
};
const unsigned char alef3 [] PROGMEM= {
0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,  
};
const unsigned char be1 [] PROGMEM= {
0x00, 0x00, 0x00, 0x01, 0x01, 0x06, 0x00, 0x02, 
};
const unsigned char be2 [] PROGMEM= {
0x00, 0x00, 0x40, 0x81, 0x81, 0x7E, 0x00, 0x10, 
};
const unsigned char pe1 [] PROGMEM= {
0x00, 0x00, 0x00, 0x01, 0x01, 0x06, 0x00, 0x07,
};
const unsigned char pe2 [] PROGMEM= {
0x00, 0x00, 0x40, 0x81, 0x81, 0x7E, 0x00, 0x38, 
};
const unsigned char te1 [] PROGMEM= {
0x00, 0x03, 0x00, 0x01, 0x01, 0x06, 0x00, 0x00,
};
const unsigned char te2 [] PROGMEM= {
0x00, 0x14, 0x40, 0x81, 0x81, 0x7E, 0x00, 0x00, 
};
const unsigned char the1 [] PROGMEM= {
0x02, 0x05, 0x00, 0x01, 0x01, 0x06, 0x00, 0x00, 
};
const unsigned char the2 [] PROGMEM= {
0x08, 0x14, 0x40, 0x81, 0x81, 0x7E, 0x00, 0x00, 
};
const unsigned char jim1 [] PROGMEM= {
0x00, 0x00, 0x0C, 0x12, 0x01, 0x3E, 0x00, 0x04, 
};
const unsigned char jim2 [] PROGMEM= {
0x00, 0x00, 0x0C, 0x12, 0x01, 0x3E, 0x40, 0x3A, 
};
const unsigned char che1 [] PROGMEM= {
0x00, 0x00, 0x0C, 0x12, 0x01, 0x3E, 0x00, 0x1C, 
};
const unsigned char che2 [] PROGMEM= {
0x00, 0x00, 0x0C, 0x12, 0x01, 0x3E, 0x40, 0x37, 
};
const unsigned char hee1 [] PROGMEM= {
0x00, 0x00, 0x0C, 0x12, 0x01, 0x3E, 0x00, 0x00, 
};
const unsigned char hee2 [] PROGMEM= {
0x00, 0x00, 0x0C, 0x12, 0x01, 0x3E, 0x40, 0x38, 
};
const unsigned char khe1 [] PROGMEM= {
0x00, 0x20, 0x0C, 0x12, 0x01, 0x3E, 0x00, 0x00, 
};
const unsigned char khe2 [] PROGMEM= {
0x00, 0x20, 0x0C, 0x12, 0x01, 0x3E, 0x40, 0x38, 
};
const unsigned char dal [] PROGMEM= {
0x00, 0x00, 0x04, 0x02, 0x01, 0x12, 0x0C, 0x00, 
};
const unsigned char zal [] PROGMEM= {
0x00, 0x10, 0x04, 0x02, 0x01, 0x12, 0x0C, 0x00, 
};
const unsigned char re [] PROGMEM= {
0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x02, 0x0C, 
};
const unsigned char ze [] PROGMEM= {
0x00, 0x01, 0x00, 0x01, 0x01, 0x01, 0x02, 0x0C, 
};
const unsigned char zhe [] PROGMEM= {
0x02, 0x05, 0x00, 0x01, 0x01, 0x01, 0x02, 0x0C, 
};
const unsigned char sin1 [] PROGMEM= {
0x00, 0x00, 0x00, 0x15, 0x15, 0x6A, 0x00, 0x00, 
};
const unsigned char sin2 [] PROGMEM= {
0x00, 0x00, 0x00, 0x15, 0x95, 0x9A, 0x90, 0x60, 
};
const unsigned char shin1 [] PROGMEM= {
0x04, 0x0A, 0x00, 0x15, 0x15, 0x6A, 0x00, 0x00, 
};
const unsigned char shin2 [] PROGMEM= {
0x04, 0x0A, 0x00, 0x15, 0x95, 0x9A, 0x90, 0x60, 
};
const unsigned char sad1 [] PROGMEM= {
0x00, 0x00, 0x06, 0x29, 0x31, 0x5E, 0x00, 0x00, 
};
const unsigned char sad2 [] PROGMEM= {
0x00, 0x00, 0x06, 0x49, 0x91, 0x9E, 0x90, 0x60, 
};
const unsigned char zad1 [] PROGMEM= {
0x00, 0x10, 0x06, 0x29, 0x31, 0x5E, 0x00, 0x00, 
};
const unsigned char zad2 [] PROGMEM= {
0x00, 0x10, 0x06, 0x49, 0x91, 0x9E, 0x90, 0x60, 
};
const unsigned char taa [] PROGMEM= {
0x00, 0x20, 0x26, 0x29, 0x31, 0x7E, 0x00, 0x00, 
};
const unsigned char zaa [] PROGMEM= {
0x00, 0x28, 0x26, 0x29, 0x31, 0x7E, 0x00, 0x00, 
};
const unsigned char ein1 [] PROGMEM= {
0x00, 0x00, 0x03, 0x04, 0x04, 0x0F, 0x00, 0x00, 
};
const unsigned char ein2 [] PROGMEM= {
0x00, 0x00, 0x1E, 0x22, 0x1C, 0x77, 0x00, 0x00, 
};
const unsigned char ein3 [] PROGMEM= {
0x00, 0x1E, 0x22, 0x1C, 0x24, 0x23, 0x20, 0x1C, 
};
const unsigned char ein4 [] PROGMEM= {
0x00, 0x03, 0x04, 0x04, 0x0F, 0x10, 0x10, 0x0F, 
};
const unsigned char qein1 [] PROGMEM= {
0x00, 0x08, 0x03, 0x04, 0x04, 0x0F, 0x00, 0x00, 
};
const unsigned char qein2 [] PROGMEM= {
0x08, 0x00, 0x1E, 0x22, 0x1C, 0x77, 0x00, 0x00,
};
const unsigned char qein3 [] PROGMEM= {
0x40, 0x1E, 0x22, 0x1C, 0x24, 0x23, 0x20, 0x1C, 
};
const unsigned char qein4 [] PROGMEM= {
0x08, 0x03, 0x04, 0x04, 0x0F, 0x10, 0x10, 0x0F, 
};
const unsigned char fe1 [] PROGMEM= {
0x04, 0x00, 0x06, 0x09, 0x09, 0x1E, 0x00, 0x00, 
};
const unsigned char fe2 [] PROGMEM= {
0x04, 0x00, 0x06, 0x89, 0x89, 0x7E, 0x00, 0x00, 
};
const unsigned char qaf1 [] PROGMEM= {
0x06, 0x00, 0x06, 0x09, 0x09, 0x1E, 0x00, 0x00, 
};
const unsigned char qaf2 [] PROGMEM= {
0x06, 0x00, 0x06, 0x09, 0x49, 0x47, 0x41, 0x3E, 
};
const unsigned char kaf1 [] PROGMEM= {
0x00, 0x0F, 0x10, 0x1E, 0x01, 0x3E, 0x00, 0x00, 
};
const unsigned char kaf2 [] PROGMEM= {
0x00, 0x07, 0x08, 0x8E, 0x81, 0x7E, 0x00, 0x00,
};
const unsigned char gaf1 [] PROGMEM= {
0x07, 0x0F, 0x10, 0x1E, 0x01, 0x3E, 0x00, 0x00, 
};
const unsigned char gaf2 [] PROGMEM= {
0x07, 0x0F, 0x10, 0x9E, 0x81, 0x7E, 0x00, 0x00,
};
const unsigned char lam1 [] PROGMEM= {
0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x00, 0x00, 
};
const unsigned char lam2 [] PROGMEM= {
0x00, 0x01, 0x01, 0x11, 0x21, 0x22, 0x1C, 0x00, 
};
const unsigned char mim1 [] PROGMEM= {
0x00, 0x00, 0x06, 0x09, 0x09, 0x36, 0x00, 0x00, 
};
const unsigned char mim2 [] PROGMEM= {
0x00, 0x04, 0x0A, 0x19, 0x29, 0x46, 0x40, 0x20, 
};
const unsigned char noon1 [] PROGMEM= {
0x00, 0x02, 0x00, 0x01, 0x01, 0x06, 0x00, 0x00, 
};
const unsigned char noon2 [] PROGMEM= {
0x00, 0x00, 0x08, 0x21, 0x41, 0x41, 0x22, 0x1C, 
};
const unsigned char vaav [] PROGMEM= {
0x00, 0x00, 0x06, 0x09, 0x09, 0x07, 0x01, 0x0E, 
};
const unsigned char he1 [] PROGMEM= {
0x08, 0x04, 0x0A, 0x15, 0x09, 0x36, 0x00, 0x00, 
};
const unsigned char he2 [] PROGMEM= {
0x00, 0x00, 0x30, 0x48, 0x56, 0xE9, 0x50, 0x20, 
};
const unsigned char he3 [] PROGMEM= {
0x00, 0x07, 0x09, 0x09, 0x05, 0x00, 0x00, 0x00,
};
const unsigned char he4 [] PROGMEM= {
0x00, 0x08, 0x04, 0x0A, 0x11, 0x11, 0x0E, 0x00, 
};
const unsigned char ye1 [] PROGMEM= {
0x00, 0x00, 0x00, 0x01, 0x01, 0x06, 0x00, 0x06, 
};
const unsigned char ye2 [] PROGMEM= {
0x00, 0x00, 0x00, 0x4C, 0x92, 0x89, 0x84, 0x78, 
};
const unsigned char ye3 [] PROGMEM= {
0x00, 0x06, 0x29, 0x48, 0x46, 0x41, 0x21, 0x1E, 
};
const unsigned char soal [] PROGMEM= {
0x0C, 0x12, 0x10, 0x08, 0x04, 0x00, 0x04, 0x00,
};
const unsigned char tajob [] PROGMEM= {
0x00, 0x02, 0x02, 0x02, 0x02, 0x00, 0x02, 0x00,
};
const unsigned char vir [] PROGMEM= {
0x00, 0x00, 0x00, 0x04, 0x08, 0x0C, 0x0C, 0x00,
};
const unsigned char kmn1 [] PROGMEM= {
0x10, 0x08, 0x04, 0x04, 0x04, 0x04, 0x08, 0x10,
};
const unsigned char kmn2 [] PROGMEM= {
0x04, 0x08, 0x10, 0x10, 0x10, 0x10, 0x08, 0x04, 
};
const unsigned char slash [] PROGMEM= {
0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01,
};
const unsigned char backslash [] PROGMEM= {
0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80,
};

//Persian Numbers 8x8
const unsigned char num[10][8] PROGMEM = {
 0x00, 0x00, 0x00, 0x06, 0x09, 0x09, 0x06, 0x00,//0
 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00,//1
 0x00, 0x09, 0x09, 0x0E, 0x08, 0x08, 0x08, 0x00,//2
 0x00, 0x25, 0x25, 0x3A, 0x20, 0x20, 0x20, 0x00,//3
 0x00, 0x03, 0x14, 0x14, 0x1F, 0x10, 0x10, 0x00,//4 
 0x00, 0x08, 0x04, 0x12, 0x21, 0x29, 0x16, 0x00,//5
 0x00, 0x10, 0x21, 0x22, 0x1C, 0x08, 0x10, 0x00,//6
 0x00, 0x11, 0x11, 0x0A, 0x0A, 0x04, 0x04, 0x00,//7
 0x00, 0x04, 0x04, 0x0A, 0x0A, 0x11, 0x11, 0x00,//8
 0x00, 0x06, 0x09, 0x09, 0x07, 0x01, 0x01, 0x00,//9
};


void setup()   {                
  //Serial.begin(9600);
  
  //Initial settings
  display.begin(SSD1306_SWITCHCAPVCC);
  display.display();
  delay(2000);
  display.clearDisplay();
  /*
  //Draw round rectangles
  display.drawRoundRect(0, 0, 128, 64, 3, WHITE);
  display.fillRoundRect(3, 3, 122, 18, 3, WHITE);
  //
  
  char txt[] = "فارسی نویسی در آردوینو";
  PutCharPE(txt,ALINE_CENTER(txt),8,1,BLACK);

  char txt1[] = "کاری از :";
  PutCharPE(txt1,ALINE_RIGHT-4,28,1,WHITE);

  char txt2[] = "صدرالدین رستگار";
  PutCharPE(txt2,ALINE_LEFT(txt2)+2,38,1,WHITE);

  char txt3[] = "رامین سنگسری";
  PutCharPE(txt3,ALINE_LEFT(txt3)+3,50,1,WHITE);
  */
  
  
  //Draw round rectangles
  display.drawRoundRect(0, 0, 128, 64, 3, WHITE);
  display.fillRoundRect(3, 3, 122, 58, 3, WHITE);
  //
  
  char txt[] = "فارسی نویسی در آردوینو";
  PutCharPE(txt,ALINE_CENTER(txt),8,1,BLACK);

  char NUM[] = "0123456789";   //For correct representation, the numbers must be reversed.
  PutCharPE(strreverse(NUM),ALINE_CENTER(NUM),30,1,BLACK);
  
  //To make them visible on the display hardware!
  display.display();
}


void loop() {
}


char* strreverse(char* s)
{
    char* beg = s-1, *end = s, tmp;
    while (*++end);
    while (end-- > ++beg)
    { 
        tmp  = *beg; 
        *beg = *end;  
        *end =  tmp;  
    }
    return s;
}


void drawBitmapPE(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color) {

  int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
  uint8_t byte = 0;

  for(int16_t j=0; j<h; j++, y++) {
    for(int16_t i=0; i<w; i++) {
      if(i & 7) byte <<= 1;
      else      byte = pgm_read_byte(&bitmap[j * byteWidth + i / 8]);
      if(byte & 0x80) setpixel(x+i, y, color);
    }
  }
}


void PutCharPE(char *Text, int x, int y, int dis, uint16_t color){
  int cursor_x = x-8;
  int cursor_y = y;
  int haalat = 0;
  unsigned char qloghat = ' ';  //لغت قبل
  unsigned char loghat;
  unsigned char bloghat;      //لغت بعد
  unsigned char le;
  int d;
  
  while(le = *Text++){
    //is Number ?
    if (le >= '0' && le <= '9') {
      d = le - '0';
      loghat = le;
    }
    //is Number ?
    else if(le >= 128){ 
      loghat = *Text++;
      loghat += 32;
      le += 32;
      if(loghat == 207){
        if(le == 218 || le == 250){ 
          loghat = 144; //گ
        }
      }
      else if(loghat == 166)
        { 
        if(le == 218 || le == 250){ //چ
          loghat = 141;
        }
        else
        { 
          loghat = 228; //ن
        }
      }
    } 
    else
    {
      loghat = le;
    }
    if(loghat==172)
    {
      if(le==248 || le==32)
      {
        loghat=44;
      }
    }
          
    le = *Text++;
    
    if(le >= 128)
    {
      bloghat = *Text++; 
      bloghat += 32; 
      le += 32;
      if(bloghat == 207)
      {
        if(le == 218 || le == 250)
        { 
          bloghat = 144; //گ
        }
      }
    else if(bloghat == 166)
    {
      if(le == 218 || le == 250)
      { //چ
        bloghat = 141; 
      }
      else
      {
        bloghat = 228; //ن
      }
    }
    *Text--;
    *Text--;
    }
    else
    {
      bloghat = le; 
      *Text--;
    }
    if(bloghat==172)
    {
      if(le==248 || le==32)
      {
        bloghat=44;
      }
    }
        
    int isunk = 0; 
    if(qloghat==32 || qloghat=='\0' || qloghat==199 || qloghat==194 || qloghat==207 || qloghat==208 || qloghat==209 || qloghat==210 || qloghat==184 || qloghat==168 || qloghat==191 || qloghat==40 || qloghat==41 || qloghat==46 || qloghat==33 || qloghat==44 || qloghat==58 || qloghat==248)
    {
      if(bloghat==32 || bloghat=='\0' || bloghat==191 || bloghat==40 || bloghat==41 || bloghat==46 || bloghat==33 || bloghat==44 || bloghat==58 || bloghat==248){
        haalat = 0;  //دو سمت غیر چسبان
      }
      else
      {
        haalat = 1;  //آخر چسبان
      }
    }
    else
    {
      if(bloghat==32 || bloghat=='\0' || bloghat==191 || bloghat==40 || bloghat==41 || bloghat==46 || bloghat==33 || bloghat==44 || bloghat==58 || bloghat==248)
      {
        haalat = 2;  //اول چسبان آخر غیر چسبان
      }
      else
      {
        haalat = 3;  //دو سمت چسبان
      }
    }
  
    switch(loghat){
      case 48: //zero
        drawBitmapPE(cursor_x, cursor_y,  num[d], 8, 8, color);
        cursor_x -= 7;
        break;
      case 49: //1
        drawBitmapPE(cursor_x, cursor_y,  num[d], 8, 8, color);
        cursor_x -= 5;
        break;
      case 50: //2
        drawBitmapPE(cursor_x, cursor_y,  num[d], 8, 8, color);
        cursor_x -= 7;
        break;
      case 51: //3
        drawBitmapPE(cursor_x, cursor_y,  num[d], 8, 8, color);
        cursor_x -= 8;
        break;
      case 52: //4
        drawBitmapPE(cursor_x, cursor_y,  num[d], 8, 8, color);
        cursor_x -= 8;
        break;
      case 53: //5
        drawBitmapPE(cursor_x, cursor_y,  num[d], 8, 8, color);
        cursor_x -= 8;
        break;
      case 54: //6
        drawBitmapPE(cursor_x, cursor_y,  num[d], 8, 8, color);
        cursor_x -= 8;
        break;
      case 55: //7
        drawBitmapPE(cursor_x, cursor_y,  num[d], 8, 8, color);
        cursor_x -= 7;
        break;
      case 56: //8
        drawBitmapPE(cursor_x, cursor_y,  num[d], 8, 8, color);
        cursor_x -= 7;
        break;
      case 57: //9
        drawBitmapPE(cursor_x, cursor_y,  num[d], 8, 8, color);
        cursor_x -= 6;
        break;
      case 32:  //فاصله
        cursor_x -= 2;
        break;
      case 191:  //؟
        drawBitmapPE(cursor_x, cursor_y,  soal, 8, 8, color);
        cursor_x -= 6;
        break;
      case 47:  // /
        drawBitmapPE(cursor_x, cursor_y,  backslash, 8, 8, color);
        cursor_x -= 8;
        break;   
      case 33:  //!
        drawBitmapPE(cursor_x, cursor_y,  tajob, 8, 8, color);
        cursor_x -= 3;
        break;
      case 46:  //.
        setpixel(cursor_x+6, cursor_y+5, color);
        setpixel(cursor_x+6, cursor_y+6, color);
        setpixel(cursor_x+5, cursor_y+5, color);
        setpixel(cursor_x+5, cursor_y+6, color);
        cursor_x -= 4;
        break;
      case 58:  //:
        setpixel(cursor_x+6, cursor_y+2, color);
        setpixel(cursor_x+6, cursor_y+5, color);
        cursor_x -= 3;
        break;
      case ',':  //،
        drawBitmapPE(cursor_x, cursor_y,  vir, 8, 8, color);
        cursor_x -= 5;
        break;
      case 40:  //(
        drawBitmapPE(cursor_x, cursor_y,  kmn1, 8, 8, color);
        cursor_x -= 7;
        break;
      case 41:  //)
        drawBitmapPE(cursor_x, cursor_y,  kmn2, 8, 8, color);
        cursor_x -= 7;
        break;
      case 194:  //آ
        drawBitmapPE(cursor_x, cursor_y,  alef1, 8, 8, color);
        cursor_x -= 7;
        break;
      case 199:  //ا
        if(haalat == 0 || haalat == 1)
        {
          drawBitmapPE(cursor_x, cursor_y,  alef2, 8, 8, color);
          cursor_x -= 3;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  alef3, 8, 8, color);
          cursor_x -= 2;
        }
        break;
      case 200:  //ب
        if(haalat == 1 || haalat == 3){
          drawBitmapPE(cursor_x, cursor_y,  be1, 8, 8, color);
          cursor_x -= 3;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  be2, 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 222:  //پ
        if(haalat == 1 || haalat == 3){
          drawBitmapPE(cursor_x, cursor_y,  pe1, 8, 8, color);
          cursor_x -= 3;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  pe2, 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 202:  //ت
        if(haalat == 1 || haalat == 3)
        {
          drawBitmapPE(cursor_x, cursor_y,  te1, 8, 8, color);
          cursor_x -= 3;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  te2, 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 203:  //ث
        if(haalat == 1 || haalat == 3){
          drawBitmapPE(cursor_x, cursor_y,  the1, 8, 8, color);
          cursor_x -= 3;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  the2, 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 204:  //ج
        if(haalat == 1 || haalat == 3){
          drawBitmapPE(cursor_x, cursor_y,  jim1, 8, 8, color);
          cursor_x -= 6;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  jim2, 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 141:  //چ
        if(haalat == 1 || haalat == 3){
          drawBitmapPE(cursor_x, cursor_y,  che1, 8, 8, color);
          cursor_x -= 6;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  che2, 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 205:  //ح
        if(haalat == 1 || haalat == 3){
          drawBitmapPE(cursor_x, cursor_y,  hee1, 8, 8, color);
          cursor_x -= 6;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  hee2, 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 206:  //خ
        if(haalat == 1 || haalat == 3){
          drawBitmapPE(cursor_x, cursor_y,  khe1, 8, 8, color);
          cursor_x -= 6;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  khe2, 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 207:  //د
        drawBitmapPE(cursor_x, cursor_y,  dal, 8, 8, color);
        cursor_x -= 6;
        break;
      case 208:  //ذ
        drawBitmapPE(cursor_x, cursor_y,  zal, 8, 8, color);
        cursor_x -= 6;
        break;
      case 209:  //ر
        drawBitmapPE(cursor_x, cursor_y,  re, 8, 8, color);
        cursor_x -= 5;
        break;
      case 210:  //ز
        drawBitmapPE(cursor_x, cursor_y,  ze, 8, 8, color);
        cursor_x -= 5;
        break;
      case 184:  //ژ
        drawBitmapPE(cursor_x, cursor_y,  zhe, 8, 8, color);
        cursor_x -= 5;
        break;
      case 211:  //س
        if(haalat == 1 || haalat == 3){
          drawBitmapPE(cursor_x, cursor_y,  sin1, 8, 8, color);
          cursor_x -= 7;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  sin2, 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 212:  //ش
        if(haalat == 1 || haalat == 3){
          drawBitmapPE(cursor_x, cursor_y,  shin1, 8, 8, color);
          cursor_x -= 7;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  shin2, 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 213:  //ص
        if(haalat == 1 || haalat == 3){
          drawBitmapPE(cursor_x, cursor_y,  sad1, 8, 8, color);
          cursor_x -= 7;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  sad2, 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 214:  //ض
        if(haalat == 1 || haalat == 3)
        {
          drawBitmapPE(cursor_x, cursor_y,  zad1, 8, 8, color);
          cursor_x -= 7;
        }
        else if(haalat == 0 || haalat == 2){
          drawBitmapPE(cursor_x, cursor_y,  zad2, 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 215:  //ط
        drawBitmapPE(cursor_x, cursor_y,  taa, 8, 8, color);
        cursor_x -= 7;
        break;
      case 216:  //ظ
        drawBitmapPE(cursor_x, cursor_y,  zaa, 8, 8, color);
        cursor_x -= 7;
        break;
      case 217:  //ع
        if(haalat == 0)
        {
          drawBitmapPE(cursor_x, cursor_y,  ein4, 8, 8, color);
          cursor_x -= 5;
        }
        else if(haalat == 1)
        {
          drawBitmapPE(cursor_x, cursor_y,  ein1, 8, 8, color);
          cursor_x -= 4;
        }
        else if(haalat == 2)
        {
          drawBitmapPE(cursor_x, cursor_y,  ein3, 8, 8, color);
          cursor_x -= 6;
        }
        else if(haalat == 3)
        {
          drawBitmapPE(cursor_x, cursor_y,  ein2, 8, 8, color);
          cursor_x -= 7;
        }
        break;
      case 218:  //غ
        if(haalat == 0){
          drawBitmapPE(cursor_x, cursor_y,  qein4, 8, 8, color);
          cursor_x -= 5;
        }
        else if(haalat == 1)
        {
          drawBitmapPE(cursor_x, cursor_y,  qein1, 8, 8, color);
          cursor_x -= 4;
        }
        else if(haalat == 2)
        {
          drawBitmapPE(cursor_x, cursor_y,  qein3, 8, 8, color);
          cursor_x -= 6;
        }
        else if(haalat == 3)
        {
          drawBitmapPE(cursor_x, cursor_y,  qein2, 8, 8, color);
          cursor_x -= 7;
        }
        break;
      case 161:  //ف
        if(haalat == 1 || haalat == 3)
        {
          drawBitmapPE(cursor_x, cursor_y,  fe1, 8, 8, color);
          cursor_x -= 5;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  fe2, 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 162:  //ق
        if(haalat == 1 || haalat == 3)
        {
          drawBitmapPE(cursor_x, cursor_y,  qaf1, 8, 8, color);
          cursor_x -= 5;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  qaf2, 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 201:  //ک
        if(haalat == 1 || haalat == 3){
          drawBitmapPE(cursor_x, cursor_y,  kaf1, 8, 8, color);
          cursor_x -= 6;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  kaf2, 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 144:  //گ
        if(haalat == 1 || haalat == 3)
        {
          drawBitmapPE(cursor_x, cursor_y,  gaf1, 8, 8, color);
          cursor_x -= 6;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  gaf2, 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 164:  //ل
        if(haalat == 1 || haalat == 3)
        {
          drawBitmapPE(cursor_x, cursor_y,  lam1, 8, 8, color);
          cursor_x -= 2;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  lam2, 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 165:  //م
        if(haalat == 1 || haalat == 3){
          drawBitmapPE(cursor_x, cursor_y,  mim1, 8, 8, color);
          cursor_x -= 6;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  mim2, 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 228:  //ن
        if(haalat == 1 || haalat == 3){
          drawBitmapPE(cursor_x, cursor_y,  noon1, 8, 8, color);
          cursor_x -= 3;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  noon2, 8, 8, color);
          cursor_x -= 9;
        }
        break;
      case 168:  //و
        drawBitmapPE(cursor_x, cursor_y,  vaav, 8, 8, color);
        cursor_x -= 5;
        break;
      case 167:  //ه
        if(haalat == 0)
        {
          drawBitmapPE(cursor_x, cursor_y,  he4, 8, 8, color);
          cursor_x -= 6;
        }
        else if(haalat == 1)
        {
          drawBitmapPE(cursor_x, cursor_y,  he1, 8, 8, color);
          cursor_x -= 6;
        }
        else if(haalat == 2)
        {
          drawBitmapPE(cursor_x, cursor_y,  he3, 8, 8, color);
          cursor_x -= 5;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  he2, 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 172:  //ی
        if(haalat == 1 || haalat == 3)
        {
          drawBitmapPE(cursor_x, cursor_y,  ye1, 8, 8, color);
          cursor_x -= 3;
        }
        else if(haalat == 2)
        {
          drawBitmapPE(cursor_x, cursor_y,  ye2, 8, 8, color);
          cursor_x -= 8;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  ye3, 8, 8, color);
          cursor_x -= 8;
        }
        break;
      default:
        isunk = 1;
        break;
      }  
    if(isunk == 0)
    {
      qloghat = loghat;
    }
    
    if(cursor_x < 0){
        cursor_x  = LCDWidth - 8;
        cursor_y  += 8 + dis;
    } 
  }  
}

int CalcTextWidth (char *Text){
  int dis = 1;
  int cursor_x = -8;
  int cursor_y = 0;
  int haalat = 0;
  unsigned char qloghat = ' ';  //لغت قبل
  unsigned char loghat;
  unsigned char bloghat;      //لغت بعد
  unsigned char le;
  int d;
  
  while(le = *Text++){
    //is Number ?
    if (le >= '0' && le <= '9') {
      d = le - '0';
      loghat = le;
    }
    //is Number ?
    else if(le >= 128){ 
      loghat = *Text++;
      loghat += 32;
      le += 32;
      if(loghat == 207){
        if(le == 218 || le == 250){ 
          loghat = 144; //گ
        }
      }
      else if(loghat == 166)
        { 
        if(le == 218 || le == 250){ //چ
          loghat = 141;
        }
        else
        { 
          loghat = 228; //ن
        }
      }
    } 
    else
    {
      loghat = le;
    }
    if(loghat==172)
    {
      if(le==248 || le==32)
      {
        loghat=44;
      }
    }
          
    le = *Text++;
    
    if(le >= 128)
    {
      bloghat = *Text++; 
      bloghat += 32; 
      le += 32;
      if(bloghat == 207)
      {
        if(le == 218 || le == 250)
        { 
          bloghat = 144; //گ
        }
      }
    else if(bloghat == 166)
    {
      if(le == 218 || le == 250)
      { //چ
        bloghat = 141; 
      }
      else
      {
        bloghat = 228; //ن
      }
    }
    *Text--;
    *Text--;
    }
    else
    {
      bloghat = le; 
      *Text--;
    }
    if(bloghat==172)
    {
      if(le==248 || le==32)
      {
        bloghat=44;
      }
    }
        
    int isunk = 0; 
    if(qloghat==32 || qloghat=='\0' || qloghat==199 || qloghat==194 || qloghat==207 || qloghat==208 || qloghat==209 || qloghat==210 || qloghat==184 || qloghat==168 || qloghat==191 || qloghat==40 || qloghat==41 || qloghat==46 || qloghat==33 || qloghat==44 || qloghat==58 || qloghat==248)
    {
      if(bloghat==32 || bloghat=='\0' || bloghat==191 || bloghat==40 || bloghat==41 || bloghat==46 || bloghat==33 || bloghat==44 || bloghat==58 || bloghat==248){
        haalat = 0;  //دو سمت غیر چسبان
      }
      else
      {
        haalat = 1;  //آخر چسبان
      }
    }
    else
    {
      if(bloghat==32 || bloghat=='\0' || bloghat==191 || bloghat==40 || bloghat==41 || bloghat==46 || bloghat==33 || bloghat==44 || bloghat==58 || bloghat==248)
      {
        haalat = 2;  //اول چسبان آخر غیر چسبان
      }
      else
      {
        haalat = 3;  //دو سمت چسبان
      }
    }
  
    switch(loghat){
      case 48: //zero
        cursor_x -= 7;
        break;
      case 49: //1
        cursor_x -= 5;
        break;
      case 50: //2
        cursor_x -= 7;
        break;
      case 51: //3
        cursor_x -= 8;
        break;
      case 52: //4
        cursor_x -= 8;
        break;
      case 53: //5
        cursor_x -= 8;
        break;
      case 54: //6
        cursor_x -= 8;
        break;
      case 55: //7
        cursor_x -= 7;
        break;
      case 56: //8
        cursor_x -= 7;
        break;
      case 57: //9
        cursor_x -= 6;
        break;
      case 32:  //فاصله
        cursor_x -= 2;
        break;
      case 191:  //؟
        cursor_x -= 6;
        break;
      case 47:  // /
        cursor_x -= 8;
        break;  
      case 33:  //!
        cursor_x -= 3;
        break;
      case 46:  //.
        cursor_x -= 4;
        break;
      case 58:  //:
        cursor_x -= 3;
        break;
      case ',':  //،
        cursor_x -= 5;
        break;
      case 40:  //(
        cursor_x -= 7;
        break;
      case 41:  //)
        cursor_x -= 7;
        break;
      case 194:  //آ
        cursor_x -= 7;
        break;
      case 199:  //ا
        if(haalat == 0 || haalat == 1)
        {
          cursor_x -= 3;
        }
        else
        {
          cursor_x -= 2;
        }
        break;
      case 200:  //ب
        if(haalat == 1 || haalat == 3){
          cursor_x -= 3;
        }
        else
        {
          cursor_x -= 8;
        }
        break;
      case 222:  //پ
        if(haalat == 1 || haalat == 3){
          cursor_x -= 3;
        }
        else
        {
          cursor_x -= 8;
        }
        break;
      case 202:  //ت
        if(haalat == 1 || haalat == 3)
        {
          cursor_x -= 3;
        }
        else
        {
          cursor_x -= 8;
        }
        break;
      case 203:  //ث
        if(haalat == 1 || haalat == 3){
          cursor_x -= 3;
        }
        else
        {
          cursor_x -= 8;
        }
        break;
      case 204:  //ج
        if(haalat == 1 || haalat == 3){
          cursor_x -= 6;
        }
        else
        {
          cursor_x -= 8;
        }
        break;
      case 141:  //چ
        if(haalat == 1 || haalat == 3){
          cursor_x -= 6;
        }
        else
        {
          cursor_x -= 8;
        }
        break;
      case 205:  //ح
        if(haalat == 1 || haalat == 3){
          cursor_x -= 6;
        }
        else
        {
          cursor_x -= 8;
        }
        break;
      case 206:  //خ
        if(haalat == 1 || haalat == 3){
          cursor_x -= 6;
        }
        else
        {
          cursor_x -= 8;
        }
        break;
      case 207:  //د
        cursor_x -= 6;
        break;
      case 208:  //ذ
        cursor_x -= 6;
        break;
      case 209:  //ر
        cursor_x -= 5;
        break;
      case 210:  //ز
        cursor_x -= 5;
        break;
      case 184:  //ژ
        cursor_x -= 5;
        break;
      case 211:  //س
        if(haalat == 1 || haalat == 3){
          cursor_x -= 7;
        }
        else
        {
          cursor_x -= 8;
        }
        break;
      case 212:  //ش
        if(haalat == 1 || haalat == 3){
          cursor_x -= 7;
        }
        else
        {
          cursor_x -= 8;
        }
        break;
      case 213:  //ص
        if(haalat == 1 || haalat == 3){
          cursor_x -= 7;
        }
        else
        {
          cursor_x -= 8;
        }
        break;
      case 214:  //ض
        if(haalat == 1 || haalat == 3)
        {
          cursor_x -= 7;
        }
        else if(haalat == 0 || haalat == 2){
          cursor_x -= 8;
        }
        break;
      case 215:  //ط
        cursor_x -= 7;
        break;
      case 216:  //ظ
        cursor_x -= 7;
        break;
      case 217:  //ع
        if(haalat == 0)
        {
          cursor_x -= 5;
        }
        else if(haalat == 1)
        {
          cursor_x -= 4;
        }
        else if(haalat == 2)
        {
          cursor_x -= 6;
        }
        else if(haalat == 3)
        {
          cursor_x -= 7;
        }
        break;
      case 218:  //غ
        if(haalat == 0){
          cursor_x -= 5;
        }
        else if(haalat == 1)
        {
          cursor_x -= 4;
        }
        else if(haalat == 2)
        {
          cursor_x -= 6;
        }
        else if(haalat == 3)
        {
          cursor_x -= 7;
        }
        break;
      case 161:  //ف
        if(haalat == 1 || haalat == 3)
        {
          cursor_x -= 5;
        }
        else
        {
          cursor_x -= 8;
        }
        break;
      case 162:  //ق
        if(haalat == 1 || haalat == 3)
        {
          cursor_x -= 5;
        }
        else
        {
          cursor_x -= 8;
        }
        break;
      case 201:  //ک
        if(haalat == 1 || haalat == 3){
          cursor_x -= 6;
        }
        else
        {
          cursor_x -= 8;
        }
        break;
      case 144:  //گ
        if(haalat == 1 || haalat == 3)
        {
          cursor_x -= 6;
        }
        else
        {
          cursor_x -= 8;
        }
        break;
      case 164:  //ل
        if(haalat == 1 || haalat == 3)
        {
          cursor_x -= 2;
        }
        else
        {
          cursor_x -= 8;
        }
        break;
      case 165:  //م
        if(haalat == 1 || haalat == 3){
          cursor_x -= 6;
        }
        else
        {
          cursor_x -= 8;
        }
        break;
      case 228:  //ن
        if(haalat == 1 || haalat == 3){
          cursor_x -= 3;
        }
        else
        {
          cursor_x -= 9;
        }
        break;
      case 168:  //و
        cursor_x -= 5;
        break;
      case 167:  //ه
        if(haalat == 0)
        {
          cursor_x -= 6;
        }
        else if(haalat == 1)
        {
          cursor_x -= 6;
        }
        else if(haalat == 2)
        {
          cursor_x -= 5;
        }
        else
        {
          cursor_x -= 8;
        }
        break;
      case 172:  //ی
        if(haalat == 1 || haalat == 3)
        {
          cursor_x -= 3;
        }
        else if(haalat == 2)
        {
          cursor_x -= 8;
        }
        else
        {
          cursor_x -= 8;
        }
        break;
      default:
        isunk = 1;
        break;
      }
    
    if(isunk == 0)
    {
      qloghat = loghat;
    }
    
    if(cursor_x < 0){
        cursor_x  = LCDWidth - 8;
        cursor_y  += 8 + dis;
    } 
  }

return cursor_x; 
}
