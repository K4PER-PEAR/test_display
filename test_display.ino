#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LOGO_HEIGHT   32
#define LOGO_WIDTH    32
static const unsigned char PROGMEM logo_bmp[] =
{ 
  0b00000000,0b00000000,0b00000000,0b00000000,
  0b00000000,0b00000000,0b00000000,0b00000000,
  0b00000000,0b00000000,0b00000000,0b00000000,
  0b00000000,0b00000000,0b00000111,0b10000000,
  0b00000000,0b00000000,0b00001100,0b11000000,
  0b00000000,0b00000000,0b00111000,0b01000000,
  0b00000000,0b00000000,0b00110000,0b00000000,
  0b00000000,0b00000000,0b01100000,0b00000000,
  0b00000000,0b00000000,0b01100000,0b00000000,
  0b00000000,0b00000001,0b11111000,0b00000000,
  0b00000000,0b00000011,0b11111100,0b00000000,
  0b00000000,0b00000111,0b11111110,0b00000000,
  0b00000000,0b00000111,0b11111110,0b00000000,
  0b00000000,0b00000111,0b11111110,0b00000000,
  0b00000000,0b00011111,0b11111111,0b00000000,
  0b00000000,0b11111111,0b11111111,0b11000000,
  0b00000011,0b11111111,0b11111111,0b11100000,
  0b00001111,0b11111111,0b11111111,0b11110000,
  0b00011111,0b11111111,0b11111111,0b11111000,
  0b00111111,0b11000001,0b11000001,0b11111100,
  0b01111111,0b11011101,0b11011101,0b11111110,
  0b01111111,0b11011101,0b11000001,0b11111110,
  0b01111111,0b11011101,0b11111101,0b11111110,
  0b01111111,0b11000001,0b11111101,0b11111110,
  0b00111111,0b11111111,0b11111111,0b11111000,
  0b00011111,0b11111111,0b11111111,0b11110000,
  0b00001111,0b11111111,0b11111111,0b11100000,
  0b00000111,0b11111111,0b11111111,0b11000000,
  0b00000001,0b11111111,0b11111111,0b00000000,
  0b00000000,0b00111111,0b11110000,0b00000000,
  0b00000000,0b00000000,0b00000000,0b00000000,
  0b00000000,0b00000000,0b00000000,0b00000000
  };

void setup() {
  // put your setup code here, to run once:

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    //Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  testdrawbitmap();

}

void loop() {
  // put your main code here, to run repeatedly:

  testdrawchar();      // Draw characters of the default font

}

void testdrawbitmap(void) {
  display.clearDisplay();

  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  delay(2000);
}

void testdrawchar(void) {
  display.clearDisplay();

  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  display.write('V');
  display.write(':');
  display.println(200.155,3);
  display.write('I');
  display.write(':');
  display.print(15.2,3);    
  //display.setCursor(0, 2);  
  //display.write('I:');
  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  /*
  for(int16_t i=0; i<256; i++) {
    if(i == '\n') display.write(' ');
    else          display.write(i);
  }
  */
  display.display();
  delay(2000);
}
