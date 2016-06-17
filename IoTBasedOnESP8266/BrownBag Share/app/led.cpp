#include <led.h>
#include <user_config.h>
#include <WS2812/WS2812.h>

#define WS2812_PIN 5 // D1
#define LED_PIN 16

bool status = false;
void ws2812OFF();

void ledInit() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, OFF);
  ws2812Updata(0x00,0x00,0x00);
}

void ledON() {
  digitalWrite(LED_PIN, ON);
  status = TRUE;
}
void ledToggle() {
  status = !status;
  digitalWrite(LED_PIN, status);
}

void ledOFF() {
  digitalWrite(LED_PIN, OFF);
  status = FALSE;
}
void ledSet(bool sta) {
  status = sta;
  digitalWrite(LED_PIN, !sta);
}

bool ledStatus() { return status; }

void ws2812OFF() {
  char buffer[21];
  for (int i = 0; i < 21; i++) {
    buffer[i] = 0;
  }
  ws2812_writergb(WS2812_PIN, buffer, sizeof(buffer));
}

Timer autoOFFTimer;

void autoOFF2812() { autoOFFTimer.initializeMs(5000, ws2812OFF).startOnce(); }

void ws2812Updata(char r, char g, char b) {
  char buffer[21];
  for (int i = 0; i < 7; i++) {
    buffer[3 * i] = r;
    buffer[3 * i + 1] = g;
    buffer[3 * i + 2] = b;
  }
  ws2812_writergb(WS2812_PIN, buffer, sizeof(buffer));
  autoOFF2812();
}

void ws2812Updata(int color) {
  char buffer[21];
  for (int i = 0; i < 7; i++) {
    buffer[3 * i] = color >> 16;
    buffer[3 * i + 1] = color >> 8;
    buffer[3 * i + 2] = color;
  }
  ws2812_writergb(WS2812_PIN, buffer, sizeof(buffer));
  autoOFF2812();
}
