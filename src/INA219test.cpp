#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_INA219.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_INA219 ina219;

void setup() {
  Wire.begin(21, 22);  // SDA, SCL

  //OLED Setup
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  if (!ina219.begin()) {
    display.setCursor(0, 0);
    display.println("INA219 not found");
    display.display();
    while (true) {}
  }

  //Default Display for INA219
  display.setCursor(0, 0);
  display.println("INA219 Ready");
  display.display();
  delay(1000);
}

void loop() {
  //Call functions from INA 219 library
  float busVoltage = ina219.getBusVoltage_V();
  float current_mA = ina219.getCurrent_mA();
  float power_mW = ina219.getPower_mW();

  display.clearDisplay();
  display.setCursor(0, 0);

  display.println("INA219 Readings");
  display.println();

  display.print("V: ");
  display.print(busVoltage);
  display.println(" V");

  display.print("I: ");
  display.print(current_mA);
  display.println(" mA");

  display.print("P: ");
  display.print(power_mW);
  display.println(" mW");

  display.display();

  delay(500);
}