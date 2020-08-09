/*
 Simple coil winder/rotation counter by Richard Sagpao
 Working prototype as of 08 August 2020
 Parts:
  1. Arduino Nano (Connecttions: SCL - A5, SDA - A4, Hall Sensor out - D2, Zeroing push button - D3, +5V out, GND)
  2. A3144LU Unipolar Hall Effect Sensor (Interrupt 0)(https://www.digchip.com/datasheets/download_datasheet.php?id=99583&part-number=A3144LU)
  3. SH1106 128 x 64 I2C OLED using the U8x8 library (U8G2)
  4. Zeroing NO push button switch (Interrupt 1)
 */
 
#include <U8x8lib.h>
#include <Wire.h>
const byte interruptPin2 = 2;
const byte interruptPin3 = 3;
volatile int count = 0;

U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE); //Constructor  

void setup(void) {
  u8x8.begin();
  pinMode(interruptPin2, INPUT_PULLUP); //Hall Effect sensor out (Digital LOW output)
  pinMode(interruptPin3, INPUT_PULLUP); //Zeroing push button (faster than uprocessor reset)
  attachInterrupt(digitalPinToInterrupt(interruptPin2), countPulse, FALLING);
  attachInterrupt(digitalPinToInterrupt(interruptPin3), resetPulse, RISING);
}

void loop(void) {
  u8x8.setFont(u8x8_font_inb46_4x8_n);
  u8x8.setCursor(2,0);
  u8x8.print(count);
  delay(20);
  if (count==0){
    u8x8.print("  "); //Easier way to clear without the flicker associated with the "clear" command
  }
}

void countPulse() {   //Increments the counter by 1 per revolution
  count++;
}

void resetPulse() {   //Zeroes the counter
  count=0;
}
