#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup() {
  Serial.begin(115200);

  pinMode(4, OUTPUT);

  tft.init();
  tft.setRotation(1);

  // Use this calibration code in setup():
  uint16_t calData[5] = { 268, 3640, 249, 3520, 7 };
  tft.setTouch(calData);

  tft.fillScreen(tft.color24to16(0x641178));
  tft.fillCircle(100, 100, 60, tft.color24to16(0xC3C3C3));
  tft.fillRect(0, 200, 240, 120, tft.color24to16(0x0CC70C));
  tft.fillRect(240, 200, 240, 120, tft.color24to16(0xFF0000));

  tft.setTextSize(6);
  tft.setTextColor(tft.color24to16(0xFFFFFF));
  tft.setTextDatum(ML_DATUM);
  tft.drawString("RELAY", 200, 100);

  tft.setTextSize(4);
  tft.setTextColor(tft.color24to16(0xFFFFFF));
  tft.setTextDatum(MC_DATUM);
  tft.drawString("ON", 120, 260);
  tft.drawString("OFF", 360, 260);

}

void loop() {
  uint16_t x, y;
  if (tft.getTouch(&x, &y)) {
    Serial.printf("Touched at (%d, %d)\n", x, y);
    if ((x > 0 && x < 240) && (y > 20 && y < 120)) {
      digitalWrite(14, HIGH);
      tft.fillCircle(100, 100, 60, tft.color24to16(0x0CC70C));
    } else if ((x > 240 && x < 480) && (y > 20 && y < 120)) {
      digitalWrite(14, LOW);
      tft.fillCircle(100, 100, 60, tft.color24to16(0xFF0000));
    }
  }
  delay(10);
}
