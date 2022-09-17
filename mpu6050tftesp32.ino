#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_I2CDevice.h>
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h> 
#include <Wire.h>
#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <MPU6050.h> 
#define minval -20

#define maxval 50
MPU6050 mpu;  
WidgetTerminal terminal(V3);// Arduino SPI library

#define TFT_MOSI 23  // SDA Pin on ESP32
#define TFT_SCLK 18  // SCL Pin on ESP32
#define TFT_CS   15  // Chip select control pin
#define TFT_DC    2  // Data Command control pin
#define TFT_RST   4  // Reset pin (could connect to RST pin)


// Initialize Adafruit ST7789 TFT library
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
 
float p = 3.1415926;
 
char auth[] = "*****";             // You should get Auth Token in the Blynk App.
char ssid[] = "******";                                     // Your WiFi credentials.
char pass[] = "******";
 
void setup(void) {
  Serial.begin(115200);
   Wire.begin(); 
  tft.init(240, 240, SPI_MODE2);    // Init ST7789 display 135x240 pixel
  tft.setRotation(3);
  tft.fillScreen(ST77XX_BLACK);
  tft.fillScreen(ST77XX_BLACK);
  
  delay(500);

  // large block of text
  tft.fillScreen(ST77XX_BLACK);
  
  delay(1000);

  // tft print function!
  
  delay(4000);

  // a single pixel
  tft.drawPixel(tft.width()/2, tft.height()/2, ST77XX_GREEN);
  delay(500);

  // line draw test
  testlines(ST77XX_YELLOW);
  delay(500);

  // optimized lines
  testfastlines(ST77XX_RED, ST77XX_BLUE);
  delay(500);

  testdrawrects(ST77XX_GREEN);
  delay(500);

  testfillrects(ST77XX_YELLOW, ST77XX_MAGENTA);
  delay(500);

  tft.fillScreen(ST77XX_BLACK);
  testfillcircles(10, ST77XX_BLUE);
  testdrawcircles(10, ST77XX_WHITE);
  delay(500);

  testroundrects();
  delay(500);

  testtriangles();
  delay(500);

   
    
    Blynk.begin(auth, ssid, pass);
   while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))

  { Serial.println("Could not find a valid MPU6050 sensor, check wiring!");

    delay(500);}
  mpu.setThreshold(3); 

  checkSettings();
}
void checkSettings()

{
  Serial.println();

  Serial.print(" * Sleep Mode:        ");

  Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");

  Serial.print(" * Clock Source:      ");

  switch(mpu.getClockSource())

  {case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;

    case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;

    case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;

    case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;

    case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;

    case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;

    case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;

  }

  Serial.print(" * Gyroscope:         ");

  switch(mpu.getScale())

  {case MPU6050_SCALE_2000DPS:        Serial.println("2000 dps"); break;

    case MPU6050_SCALE_1000DPS:        Serial.println("1000 dps"); break;

    case MPU6050_SCALE_500DPS:         Serial.println("500 dps"); break;

    case MPU6050_SCALE_250DPS:         Serial.println("250 dps"); break;
    }

  Serial.print(" * Gyroscope offsets: ");

  Serial.print(mpu.getGyroOffsetX());

  Serial.print(" / ");

  Serial.print(mpu.getGyroOffsetY());

  Serial.print(" / ");

  Serial.println(mpu.getGyroOffsetZ());

  Serial.println();}
 
void loop() {
  Blynk.run();
    
 
    Vector rawGyro = mpu.readRawGyro();

    Vector normGyro = mpu.readNormalizeGyro();

    if(normGyro.XAxis > maxval || normGyro.XAxis < minval && normGyro.YAxis > maxval || normGyro.YAxis  < minval && normGyro.ZAxis > maxval || normGyro.ZAxis  < minval)
    { 
     //Serial.println("Sarsıntı");
     
     terminal.println("Sarsıntı") ;
     terminal.clear();

    }
  tft.invertDisplay(true);
  testlines(ST77XX_YELLOW);
  delay(1000);
  delay(500);

  // optimized lines
  testfastlines(ST77XX_RED, ST77XX_BLUE);
  delay(500);

  testdrawrects(ST77XX_GREEN);
  delay(500);

  testfillrects(ST77XX_YELLOW, ST77XX_MAGENTA);
  delay(500);

  tft.fillScreen(ST77XX_BLACK);
  testfillcircles(10, ST77XX_BLUE);
  testdrawcircles(10, ST77XX_WHITE);
  delay(500);

  testroundrects();
  delay(500);

  testtriangles();
  delay(500);
  tft.invertDisplay(false);
  
  delay(1000);
}
void testroundrects() {
  tft.fillScreen(ST77XX_BLACK);
  uint16_t color = 100;
  int i;
  int t;
  for(t = 0 ; t <= 4; t+=1) {
    int x = 0;
    int y = 0;
    int w = tft.width()-2;
    int h = tft.height()-2;
    for(i = 0 ; i <= 16; i+=1) {
      tft.drawRoundRect(x, y, w, h, 5, color);
      x+=2;
      y+=3;
      w-=4;
      h-=6;
      color+=1100;
    }
    color+=100;
  }
}
void testtriangles() {
  tft.fillScreen(ST77XX_BLACK);
  uint16_t color = 0xF800;
  int t;
  int w = tft.width()/2;
  int x = tft.height()-1;
  int y = 0;
  int z = tft.width();
  for(t = 0 ; t <= 15; t++) {
    tft.drawTriangle(w, y, y, x, z, x, color);
    x-=4;
    y+=4;
    z-=4;
    color+=100;
  }
}
void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=0; x < tft.width()+radius; x+=radius*2) {
    for (int16_t y=0; y < tft.height()+radius; y+=radius*2) {
      tft.drawCircle(x, y, radius, color);
    }
  }
}
void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=radius; x < tft.width(); x+=radius*2) {
    for (int16_t y=radius; y < tft.height(); y+=radius*2) {
      tft.fillCircle(x, y, radius, color);
    }
  }
}
void testfillrects(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=tft.width()-1; x > 6; x-=6) {
    tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color1);
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color2);
  }
}
void testdrawrects(uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color);
  }
}
void testfastlines(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t y=0; y < tft.height(); y+=5) {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x=0; x < tft.width(); x+=5) {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}
void testlines(uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, 0, x, tft.height()-1, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, 0, tft.width()-1, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, 0, x, tft.height()-1, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, 0, 0, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, tft.height()-1, x, 0, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, tft.height()-1, tft.width()-1, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, x, 0, color);
    delay(0);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, 0, y, color);
    delay(0);
  }
}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}
