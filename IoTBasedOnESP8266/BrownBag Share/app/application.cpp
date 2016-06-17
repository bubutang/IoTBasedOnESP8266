#include <user_config.h>
#include <SmingCore/SmingCore.h>
#include <wifi.h>
#include <led.h>

void systemInit() {
  System.setCpuFrequency(eCF_80MHz);
  spiffs_mount(); // Mount file system, in order to work with files
  ledInit();
  Serial.begin(115200);            // 115200 by default
  Serial.systemDebugOutput(false); // Enable debug output to serial
}
void init() {
  systemInit();
  wifiConfig();
}
