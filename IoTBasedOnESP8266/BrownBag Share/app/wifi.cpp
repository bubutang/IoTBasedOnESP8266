#include <wifi.h>
#include <user_config.h>
#include <SmingCore/SmingCore.h>
#include <led.h>
#include <web_http.h>
#include <web_api.h>
#include <web_socket.h>
#include <server_ftp.h>

HttpServer server;

bool serverStatus = false;
void startServer() {
  if (!serverStatus) {
    serverStatus = true;

    startFTP();
    server.listen(80);
    configHttp();
    configApi();
    configWebSocket();

    if (WifiStation.isEnabled()) {
      Serial.println(WifiStation.getIP());
    }
    if (WifiAccessPoint.isEnabled()) {
      Serial.println(WifiAccessPoint.getIP());
    }
    Serial.println("======================\r\n");
  }
}

void connectOk() {
  Serial.println("I'm CONNECTED");
  startServer();
}

void wifiConfig() {
  WifiStation.enable(false);
  if (WifiStation.isEnabled()) {
    WifiStation.config(WIFI_SSID, WIFI_PWD);
    WifiStation.waitConnection(connectOk);
  }

  WifiAccessPoint.enable(!WifiStation.isEnabled());
  if (WifiAccessPoint.isEnabled()) {
    WifiAccessPoint.config("Brown Bag", "111111111", AUTH_WPA_WPA2_PSK);
    WifiAccessPoint.setIP(IPAddress(192, 168, 4, 1));
    System.onReady(startServer);
  }
}
