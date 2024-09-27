/*
 * This example Uses RTC_DS3231 and Nokia5110 LCD
 * GREGORIAN Date is fetched from RTC and converted to Jalali
 * And display Jalali Date on the LCD
 */

#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "JalaliDateConverter.h"  // Include the modified library

#define RST_PIN 9
#define CE_PIN 10
#define DC_PIN 8
#define DIN_PIN 11  // MOSI
#define CLK_PIN 13  // SCK

// RTC and Display Instances
RTC_DS3231 rtc;

// Create a display object using software SPI
//Adafruit_PCD8544 display(CE_PIN, DC_PIN, DIN_PIN, CLK_PIN, RST_PIN);

// Create a display object using Hardware SPI
Adafruit_PCD8544 display(DC_PIN, CE_PIN, RST_PIN);

// Jalali date converter
JalaliDateConverter dateConverter;

void setup() {
  // Initialize serial monitor
  Serial.begin(9600);

  // Initialize RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, setting time...");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  // Set to compile time
  }

  // Initialize Nokia 5110 LCD
  display.begin();
  display.setContrast(60);
  display.clearDisplay();
}

void loop() {
  DateTime now = rtc.now();

  // Convert to Jalali and display on LCD
  String jalaliDate = dateConverter.convertToJalali(now);
  
  // Display Jalali date and time on Nokia 5110 LCD
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Jalali Date:");
  display.setCursor(0, 10);
  display.print(jalaliDate);
  
  display.setCursor(0, 20);
  display.print("Time: ");
  display.print(now.hour());
  display.print(":");
  display.print(now.minute());
  display.print(":");
  display.print(now.second());
  
  display.display();
  delay(1000);  // Update every second

  // Print Jalali date on Serial Monitor for verification
  Serial.print("Jalali Date: ");
  Serial.print(jalaliDate);
  
  Serial.print(" | Time: ");
  Serial.print(now.hour());
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print(":");
  Serial.println(now.second());
}
