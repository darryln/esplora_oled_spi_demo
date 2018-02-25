#include <Esplora.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_SH1106.h"

// OLED connections

// right hand side header:
// hdr disp   Arduino
// pin signal pin
// --- ------ -----
// 1   5V      
// 2   n.c.    
// 3   SCK     9 
// 4   MOSI    10
// 5   CS      7
// 6   n.c.
// 7   DC      0
// 8   RES     1
// 9   n.c.
// 10  GND

const int dispDataPin = 10; // MOSI
const int dispClkPin  = 9;  // CLK
const int dispCsPin   = 7;  // CS
const int dispDcPin   = 0;  // DC
const int dispRstPin  = 1;  // RES

// Use hardware SPI
Adafruit_SH1106 disp(dispDcPin, dispRstPin, dispCsPin);

#define ROW_H 10
#define JOY_ROW      (0*ROW_H)
#define JOY_COL      (0)
#define SLIDER_ROW   (1*ROW_H)
#define SLIDER_COL   (0)
#define SWITCHES_ROW (2*ROW_H)
#define SWITCHES_COL (0)
#define LIGHT_ROW    (3*ROW_H)
#define LIGHT_COL    (0)
#define TEMP_ROW     (4*ROW_H)
#define TEMP_COL     (0)
#define ACCEL_ROW    (5*ROW_H)
#define ACCEL_COL    (0)

#if (SH1106_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SH1106.h!");
#endif

const int ledPin = 13;
int ledState = LOW;


void setup(void) 
{
    pinMode(ledPin, OUTPUT);
    disp.begin(SH1106_SWITCHCAPVCC);
    disp.clearDisplay();
    disp.setTextColor(WHITE);
    disp.setTextSize(1);
}

void loop(void) 
{
      disp.clearDisplay();
      joystick();
      slider();
      switches();
      lightsensor();
      tempsensor();
      accelerometer();
      disp.display();
      digitalWrite(ledPin, ledState = (ledState == LOW ? HIGH:LOW));
      delay(250);
}

void joystick()
{
    int x = Esplora.readJoystickX();
    int y = Esplora.readJoystickY();
    int sw = Esplora.readJoystickSwitch();
    disp.setCursor(JOY_COL,JOY_ROW);
    disp.print("Joy X:");
    disp.print(x);
    disp.print(" Y:");
    disp.print(y);
    disp.print(" sw:");
    disp.print(~sw & 1, HEX);
}

void slider()
{
    int x = Esplora.readSlider();
    disp.setCursor(SLIDER_COL,SLIDER_ROW);
    disp.print("Slider:");
    disp.print(x);
}

void switches()
{
    int down = ~Esplora.readButton(SWITCH_DOWN) & 1;
    int left = ~Esplora.readButton(SWITCH_LEFT) & 1;
    int up = ~Esplora.readButton(SWITCH_UP) & 1;
    int right = ~Esplora.readButton(SWITCH_RIGHT) & 1;
    disp.setCursor(SWITCHES_COL,SWITCHES_ROW);
    disp.print("Switches:");
    if (down) disp.print("DN ");
    if (left) disp.print("LF ");
    if (up) disp.print("UP ");
    if (right) disp.print("RT ");
}

void lightsensor()
{
    int x = Esplora.readLightSensor();
    disp.setCursor(LIGHT_COL,LIGHT_ROW);
    disp.print("Light:");
    disp.print(x);
}

void tempsensor()
{
    int x = Esplora.readTemperature(DEGREES_F);
    disp.setCursor(TEMP_COL,TEMP_ROW);
    disp.print("Temp:");
    disp.print(x);
    disp.print("F");
}

void accelerometer()
{
    int x = Esplora.readAccelerometer(X_AXIS);
    int y = Esplora.readAccelerometer(Y_AXIS);
    int z = Esplora.readAccelerometer(Z_AXIS);
    disp.setCursor(ACCEL_COL,ACCEL_ROW);
    disp.print("Accel:X");
    disp.print(x);
    disp.print(" Y:");
    disp.print(y);
    disp.print(" Z:");
    disp.print(z);
}





