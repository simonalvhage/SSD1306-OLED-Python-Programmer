#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }

  display.setRotation(2); // Rotate the screen upside down
  display.clearDisplay();
  display.display();
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    if (command == "CLEAR") {
      display.clearDisplay();
      display.display();
    } else {
      int fontSize = 1;
      int cursorX = 0;
      int cursorY = 0;

      if (command.startsWith("F")) {
        fontSize = command.substring(1, 2).toInt();
        command = command.substring(2);
      }
      if (command.startsWith("XY")) {
        int separatorIndex = command.indexOf(',');
        cursorX = command.substring(2, separatorIndex).toInt();
        cursorY = command.substring(separatorIndex + 1, command.indexOf(' ')).toInt();
        command = command.substring(command.indexOf(' ') + 1);
      }

      display.setTextSize(fontSize);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(cursorX, cursorY);
      display.println(command);
      display.display();
    }
  }
}
