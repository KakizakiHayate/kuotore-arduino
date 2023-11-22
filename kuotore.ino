#include <M5StickCPlus.h>
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;
TFT_eSprite img = TFT_eSprite(&M5.Lcd);

void setup() {
  M5.begin();
  Wire.begin(0, 26);

  img.createSprite(160, 80);
  img.fillSprite(BLACK);
  img.setTextColor(WHITE);
  img.setTextSize(2);

  sensor.setTimeout(500);
  if (!sensor.init()) {
    img.setCursor(10, 10);
    img.print("Failed");
    img.pushSprite(0,0);
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }
  sensor.startContinuous(1000);
}

void loop() {
  uint16_t distance = sensor.readRangeContinuousMillimeters();
  Serial.print(distance);
  if (sensor.timeoutOccurred()) {
    Serial.print("TIMEOUT");
  }
  Serial.println();
  img.fillSprite(BLACK);
  img.setCursor(0,0);
  img.print(distance);
  img.print("mm");
  img.pushSprite(0,0);
  delay(500);
}
