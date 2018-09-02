//////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Persian/Arabic letters on WEMOS D1 mini with OLED Shield or usable with any 0.66" display.
// Add "SparkFun Micro OLED Breakout" library from "Library Manager" window and then Upload code !
//
// Copyright (C) 2018 Sadraldin Rastegar and Ramin Sangesari
// https://github.com/idreamsi/arduino-persian-reshaper
//
//////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Wire.h>  // Include Wire if you're using I2C
#include <SFE_MicroOLED.h>  // Include the SFE_MicroOLED library

#define PIN_RESET 255  //
#define DC_JUMPER 0  // I2C Addres: 0 - 0x3C, 1 - 0x3D

MicroOLED oled(PIN_RESET, DC_JUMPER); // Example I2C declaration

#define setpixel(x, y, color)           oled.pixel(x, y, color, NORM)
#define LCDWidth                        oled.getLCDWidth()
#define ALINE_CENTER(t)                 (LCDWidth - ((LCDWidth - (LCDWidth - CalcTextWidth(t))) / 2)) - 2
#define ALINE_RIGHT                     LCDWidth
#define ALINE_LEFT(t)                   LCDWidth - CalcTextWidth(t)

//Persian Letters 8x8
const unsigned char PeChar[71][8] PROGMEM = {
  0x00, 0x1C, 0x20, 0x08, 0x08, 0x08, 0x08, 0x00, //0 alef1
  0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, //1 alef2 
  0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, //2 alef3
  0x00, 0x00, 0x00, 0x01, 0x01, 0x06, 0x00, 0x02, //3 be1
  0x00, 0x00, 0x40, 0x81, 0x81, 0x7E, 0x00, 0x10, //4 be2
  0x00, 0x00, 0x00, 0x01, 0x01, 0x06, 0x00, 0x07, //5 pe1
  0x00, 0x00, 0x40, 0x81, 0x81, 0x7E, 0x00, 0x38, //6 pe2
  0x00, 0x03, 0x00, 0x01, 0x01, 0x06, 0x00, 0x00, //7 te1
  0x00, 0x14, 0x40, 0x81, 0x81, 0x7E, 0x00, 0x00, //8 te2
  0x02, 0x05, 0x00, 0x01, 0x01, 0x06, 0x00, 0x00, //9 the1
  0x08, 0x14, 0x40, 0x81, 0x81, 0x7E, 0x00, 0x00, //10  the2
  0x00, 0x00, 0x0C, 0x12, 0x01, 0x3E, 0x00, 0x04, //11  jim1
  0x00, 0x00, 0x0C, 0x12, 0x01, 0x3E, 0x40, 0x3A, //12  jim2
  0x00, 0x00, 0x0C, 0x12, 0x01, 0x3E, 0x00, 0x1C, //13  che1
  0x00, 0x00, 0x0C, 0x12, 0x01, 0x3E, 0x40, 0x37, //14  che2
  0x00, 0x00, 0x0C, 0x12, 0x01, 0x3E, 0x00, 0x00, //15  hee1
  0x00, 0x00, 0x0C, 0x12, 0x01, 0x3E, 0x40, 0x38, //16  hee2
  0x00, 0x20, 0x0C, 0x12, 0x01, 0x3E, 0x00, 0x00, //17  khe1
  0x00, 0x20, 0x0C, 0x12, 0x01, 0x3E, 0x40, 0x38, //18  khe2
  0x00, 0x00, 0x04, 0x02, 0x01, 0x12, 0x0C, 0x00, //19  dal
  0x00, 0x10, 0x04, 0x02, 0x01, 0x12, 0x0C, 0x00, //20  zal
  0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x02, 0x0C, //21  re
  0x00, 0x01, 0x00, 0x01, 0x01, 0x01, 0x02, 0x0C, //22  ze
  0x02, 0x05, 0x00, 0x01, 0x01, 0x01, 0x02, 0x0C, //23  zhe
  0x00, 0x00, 0x00, 0x15, 0x15, 0x6A, 0x00, 0x00, //24  sin1
  0x00, 0x00, 0x00, 0x15, 0x95, 0x9A, 0x90, 0x60, //25  sin2
  0x04, 0x0A, 0x00, 0x15, 0x15, 0x6A, 0x00, 0x00, //26  shin1
  0x04, 0x0A, 0x00, 0x15, 0x95, 0x9A, 0x90, 0x60, //27  shin2
  0x00, 0x00, 0x06, 0x29, 0x31, 0x5E, 0x00, 0x00, //28  sad1
  0x00, 0x00, 0x06, 0x49, 0x91, 0x9E, 0x90, 0x60, //29  sad2
  0x00, 0x10, 0x06, 0x29, 0x31, 0x5E, 0x00, 0x00, //30  zad1
  0x00, 0x10, 0x06, 0x49, 0x91, 0x9E, 0x90, 0x60, //31  zad2
  0x00, 0x20, 0x26, 0x29, 0x31, 0x7E, 0x00, 0x00, //32  taa
  0x00, 0x28, 0x26, 0x29, 0x31, 0x7E, 0x00, 0x00, //33  zaa
  0x00, 0x00, 0x03, 0x04, 0x04, 0x0F, 0x00, 0x00, //34  ein1
  0x00, 0x00, 0x1E, 0x22, 0x1C, 0x77, 0x00, 0x00, //35  ein2
  0x00, 0x1E, 0x22, 0x1C, 0x24, 0x23, 0x20, 0x1C, //36  ein3
  0x00, 0x03, 0x04, 0x04, 0x0F, 0x10, 0x10, 0x0F, //37  ein4
  0x00, 0x08, 0x03, 0x04, 0x04, 0x0F, 0x00, 0x00, //38  qein1
  0x08, 0x00, 0x1E, 0x22, 0x1C, 0x77, 0x00, 0x00, //39  qein2
  0x40, 0x1E, 0x22, 0x1C, 0x24, 0x23, 0x20, 0x1C, //40  qein3
  0x08, 0x03, 0x04, 0x04, 0x0F, 0x10, 0x10, 0x0F, //41  qein4
  0x04, 0x00, 0x06, 0x09, 0x09, 0x1E, 0x00, 0x00, //42  fe1
  0x04, 0x00, 0x06, 0x89, 0x89, 0x7E, 0x00, 0x00, //43  fe2
  0x06, 0x00, 0x06, 0x09, 0x09, 0x1E, 0x00, 0x00, //44  qaf1
  0x06, 0x00, 0x06, 0x09, 0x49, 0x47, 0x41, 0x3E, //45  qaf2
  0x00, 0x0F, 0x10, 0x1E, 0x01, 0x3E, 0x00, 0x00, //46  kaf1
  0x00, 0x07, 0x08, 0x8E, 0x81, 0x7E, 0x00, 0x00, //47  kaf2
  0x07, 0x0F, 0x10, 0x1E, 0x01, 0x3E, 0x00, 0x00, //48  gaf1
  0x07, 0x0F, 0x10, 0x9E, 0x81, 0x7E, 0x00, 0x00, //49  gaf2
  0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x00, 0x00, //50  lam1  
  0x00, 0x01, 0x01, 0x11, 0x21, 0x22, 0x1C, 0x00, //51  lam2
  0x00, 0x00, 0x06, 0x09, 0x09, 0x36, 0x00, 0x00, //52  mim1  
  0x00, 0x04, 0x0A, 0x19, 0x29, 0x46, 0x40, 0x20, //53  mim2
  0x00, 0x02, 0x00, 0x01, 0x01, 0x06, 0x00, 0x00, //54  noon1
  0x00, 0x00, 0x08, 0x21, 0x41, 0x41, 0x22, 0x1C, //55  noon2
  0x00, 0x00, 0x06, 0x09, 0x09, 0x07, 0x01, 0x0E, //56  vaav
  0x08, 0x04, 0x0A, 0x15, 0x09, 0x36, 0x00, 0x00, //57  he1
  0x00, 0x00, 0x30, 0x48, 0x56, 0xE9, 0x50, 0x20, //58  he2
  0x00, 0x07, 0x09, 0x09, 0x05, 0x00, 0x00, 0x00, //59  he3
  0x00, 0x08, 0x04, 0x0A, 0x11, 0x11, 0x0E, 0x00, //60  he4
  0x00, 0x00, 0x00, 0x01, 0x01, 0x06, 0x00, 0x06, //61  ye1
  0x00, 0x00, 0x00, 0x4C, 0x92, 0x89, 0x84, 0x78, //62  ye2
  0x00, 0x06, 0x29, 0x48, 0x46, 0x41, 0x21, 0x1E, //63  ye3
  0x0C, 0x12, 0x10, 0x08, 0x04, 0x00, 0x04, 0x00, //64  soal
  0x00, 0x02, 0x02, 0x02, 0x02, 0x00, 0x02, 0x00, //65  tajob
  0x00, 0x00, 0x00, 0x04, 0x08, 0x0C, 0x0C, 0x00, //66  vir
  0x10, 0x08, 0x04, 0x04, 0x04, 0x04, 0x08, 0x10, //67  kmn1
  0x04, 0x08, 0x10, 0x10, 0x10, 0x10, 0x08, 0x04, //68  kmn2
  0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, //69  slash
  0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, //70  backslash
};

//Persian Numbers 8x8
const unsigned char num[10][8] PROGMEM = {
  0x00, 0x00, 0x00, 0x06, 0x09, 0x09, 0x06, 0x00, //0
  0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, //1
  0x00, 0x09, 0x09, 0x0E, 0x08, 0x08, 0x08, 0x00, //2
  0x00, 0x25, 0x25, 0x3A, 0x20, 0x20, 0x20, 0x00, //3
  0x00, 0x03, 0x14, 0x14, 0x1F, 0x10, 0x10, 0x00, //4 
  0x00, 0x08, 0x04, 0x12, 0x21, 0x29, 0x16, 0x00, //5
  0x00, 0x10, 0x21, 0x22, 0x1C, 0x08, 0x10, 0x00, //6
  0x00, 0x11, 0x11, 0x0A, 0x0A, 0x04, 0x04, 0x00, //7
  0x00, 0x04, 0x04, 0x0A, 0x0A, 0x11, 0x11, 0x00, //8
  0x00, 0x06, 0x09, 0x09, 0x07, 0x01, 0x01, 0x00, //9
};


void setup()   {                
  //Serial.begin(9600);
  oled.begin();
  oled.clear(PAGE);
  oled.rect(0,0,oled.getLCDWidth(),oled.getLCDHeight(),WHITE,NORM);
    
  char txt[] = "آی دریمز";
  PutCharPE(txt,ALINE_CENTER(txt),8,1,WHITE);
  
  char txt2[] = "فارسی نویسی";
  PutCharPE(txt2,ALINE_CENTER(txt2),26,1,WHITE);
  
  //To make them visible on the display hardware!
  oled.display();
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
  unsigned char qloghat = ' ';   //Previous word
  unsigned char loghat;
  unsigned char bloghat;       //Next word
  unsigned char le;
  int d;
  
  while(le = *Text++){
    //is Number ?
    if (le >= '0' && le <= '9') {
      d = le - '0';
      loghat = le;
    }
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
        haalat = 0;  //Isolated
      }
      else
      {
        haalat = 1;  //Final
      }
    }
    else
    {
      if(bloghat==32 || bloghat=='\0' || bloghat==191 || bloghat==40 || bloghat==41 || bloghat==46 || bloghat==33 || bloghat==44 || bloghat==58 || bloghat==248)
      {
        haalat = 2;  //Initial
      }
      else
      {
        haalat = 3;  //Medial
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
        drawBitmapPE(cursor_x, cursor_y,  PeChar[64], 8, 8, color);
        cursor_x -= 6;
        break;
      case 47:  // /
        drawBitmapPE(cursor_x, cursor_y,  PeChar[70], 8, 8, color);
        cursor_x -= 8;
        break;   
      case 33:  //!
        drawBitmapPE(cursor_x, cursor_y,  PeChar[65], 8, 8, color);
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
        drawBitmapPE(cursor_x, cursor_y,  PeChar[66], 8, 8, color);
        cursor_x -= 5;
        break;
      case 40:  //(
        drawBitmapPE(cursor_x, cursor_y,  PeChar[67], 8, 8, color);
        cursor_x -= 7;
        break;
      case 41:  //)
        drawBitmapPE(cursor_x, cursor_y,  PeChar[68], 8, 8, color);
        cursor_x -= 7;
        break;
      case 194:  //آ
        drawBitmapPE(cursor_x, cursor_y,  PeChar[0], 8, 8, color);
        cursor_x -= 7;
        break;
      case 199:  //ا
        if(haalat == 0 || haalat == 1)
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[1], 8, 8, color);
          cursor_x -= 3;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[2], 8, 8, color);
          cursor_x -= 2;
        }
        break;
      case 200:  //ب
        if(haalat == 1 || haalat == 3){
          drawBitmapPE(cursor_x, cursor_y,  PeChar[3], 8, 8, color);
          cursor_x -= 3;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[4], 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 222:  //پ
        if(haalat == 1 || haalat == 3){
          drawBitmapPE(cursor_x, cursor_y,  PeChar[5], 8, 8, color);
          cursor_x -= 3;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[6], 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 202:  //ت
        if(haalat == 1 || haalat == 3)
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[7], 8, 8, color);
          cursor_x -= 3;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[8], 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 203:  //ث
        if(haalat == 1 || haalat == 3){
          drawBitmapPE(cursor_x, cursor_y,  PeChar[9], 8, 8, color);
          cursor_x -= 3;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[10], 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 204:  //ج
        if(haalat == 1 || haalat == 3){
          drawBitmapPE(cursor_x, cursor_y,  PeChar[11], 8, 8, color);
          cursor_x -= 6;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[12], 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 141:  //چ
        if(haalat == 1 || haalat == 3){
          drawBitmapPE(cursor_x, cursor_y,  PeChar[13], 8, 8, color);
          cursor_x -= 6;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[14], 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 205:  //ح
        if(haalat == 1 || haalat == 3){
          drawBitmapPE(cursor_x, cursor_y,  PeChar[15], 8, 8, color);
          cursor_x -= 6;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[16], 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 206:  //خ
        if(haalat == 1 || haalat == 3){
          drawBitmapPE(cursor_x, cursor_y,  PeChar[17], 8, 8, color);
          cursor_x -= 6;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[18], 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 207:  //د
        drawBitmapPE(cursor_x, cursor_y,  PeChar[19], 8, 8, color);
        cursor_x -= 6;
        break;
      case 208:  //ذ
        drawBitmapPE(cursor_x, cursor_y,  PeChar[20], 8, 8, color);
        cursor_x -= 6;
        break;
      case 209:  //ر
        drawBitmapPE(cursor_x, cursor_y,  PeChar[21], 8, 8, color);
        cursor_x -= 5;
        break;
      case 210:  //ز
        drawBitmapPE(cursor_x, cursor_y,  PeChar[22], 8, 8, color);
        cursor_x -= 5;
        break;
      case 184:  //ژ
        drawBitmapPE(cursor_x, cursor_y,  PeChar[23], 8, 8, color);
        cursor_x -= 5;
        break;
      case 211:  //س
        if(haalat == 1 || haalat == 3){
          drawBitmapPE(cursor_x, cursor_y,  PeChar[24], 8, 8, color);
          cursor_x -= 7;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[25], 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 212:  //ش
        if(haalat == 1 || haalat == 3){
          drawBitmapPE(cursor_x, cursor_y,  PeChar[26], 8, 8, color);
          cursor_x -= 7;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[27], 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 213:  //ص
        if(haalat == 1 || haalat == 3){
          drawBitmapPE(cursor_x, cursor_y,  PeChar[28], 8, 8, color);
          cursor_x -= 7;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[29], 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 214:  //ض
        if(haalat == 1 || haalat == 3)
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[30], 8, 8, color);
          cursor_x -= 7;
        }
        else if(haalat == 0 || haalat == 2){
          drawBitmapPE(cursor_x, cursor_y,  PeChar[31], 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 215:  //ط
        drawBitmapPE(cursor_x, cursor_y,  PeChar[32], 8, 8, color);
        cursor_x -= 7;
        break;
      case 216:  //ظ
        drawBitmapPE(cursor_x, cursor_y,  PeChar[33], 8, 8, color);
        cursor_x -= 7;
        break;
      case 217:  //ع
        if(haalat == 0)
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[37], 8, 8, color);
          cursor_x -= 5;
        }
        else if(haalat == 1)
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[34], 8, 8, color);
          cursor_x -= 4;
        }
        else if(haalat == 2)
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[36], 8, 8, color);
          cursor_x -= 6;
        }
        else if(haalat == 3)
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[35], 8, 8, color);
          cursor_x -= 7;
        }
        break;
      case 218:  //غ
        if(haalat == 0){
          drawBitmapPE(cursor_x, cursor_y,  PeChar[41], 8, 8, color);
          cursor_x -= 5;
        }
        else if(haalat == 1)
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[38], 8, 8, color);
          cursor_x -= 4;
        }
        else if(haalat == 2)
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[40], 8, 8, color);
          cursor_x -= 6;
        }
        else if(haalat == 3)
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[39], 8, 8, color);
          cursor_x -= 7;
        }
        break;
      case 161:  //ف
        if(haalat == 1 || haalat == 3)
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[42], 8, 8, color);
          cursor_x -= 5;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[43], 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 162:  //ق
        if(haalat == 1 || haalat == 3)
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[44], 8, 8, color);
          cursor_x -= 5;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[45], 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 201:  //ک
        if(haalat == 1 || haalat == 3){
          drawBitmapPE(cursor_x, cursor_y,  PeChar[46], 8, 8, color);
          cursor_x -= 6;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[47], 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 144:  //گ
        if(haalat == 1 || haalat == 3)
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[48], 8, 8, color);
          cursor_x -= 6;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[49], 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 164:  //ل
        if(haalat == 1 || haalat == 3)
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[50], 8, 8, color);
          cursor_x -= 2;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[51], 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 165:  //م
        if(haalat == 1 || haalat == 3){
          drawBitmapPE(cursor_x, cursor_y,  PeChar[52], 8, 8, color);
          cursor_x -= 6;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[53], 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 228:  //ن
        if(haalat == 1 || haalat == 3){
          drawBitmapPE(cursor_x, cursor_y,  PeChar[54], 8, 8, color);
          cursor_x -= 3;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[55], 8, 8, color);
          cursor_x -= 9;
        }
        break;
      case 168:  //و
        drawBitmapPE(cursor_x, cursor_y,  PeChar[56], 8, 8, color);
        cursor_x -= 5;
        break;
      case 167:  //ه
        if(haalat == 0)
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[60], 8, 8, color);
          cursor_x -= 6;
        }
        else if(haalat == 1)
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[57], 8, 8, color);
          cursor_x -= 6;
        }
        else if(haalat == 2)
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[59], 8, 8, color);
          cursor_x -= 5;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[58], 8, 8, color);
          cursor_x -= 8;
        }
        break;
      case 172:  //ی
        if(haalat == 1 || haalat == 3)
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[61], 8, 8, color);
          cursor_x -= 3;
        }
        else if(haalat == 2)
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[62], 8, 8, color);
          cursor_x -= 8;
        }
        else
        {
          drawBitmapPE(cursor_x, cursor_y,  PeChar[63], 8, 8, color);
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
  unsigned char qloghat = ' ';  //Previous word
  unsigned char loghat;
  unsigned char bloghat;  //Next word
  unsigned char le;
  int d;
  
  while(le = *Text++){
    //is Number ?
    if (le >= '0' && le <= '9') {
      d = le - '0';
      loghat = le;
    }
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
        haalat = 0;  //Isolated
      }
      else
      {
        haalat = 1;  //Final
      }
    }
    else
    {
      if(bloghat==32 || bloghat=='\0' || bloghat==191 || bloghat==40 || bloghat==41 || bloghat==46 || bloghat==33 || bloghat==44 || bloghat==58 || bloghat==248)
      {
        haalat = 2;  //Initial
      }
      else
      {
        haalat = 3;  //Medial
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
