#include <web_socket.h>
#include <user_config.h>
#include <SmingCore/SmingCore.h>
#include <led.h>
#include <Libraries/DHT/DHT.h>

extern HttpServer server;

#define WORK_PIN 4
DHT dht(WORK_PIN, 22);

int totalActiveSockets = 0;
Timer sendAdTimer;

void sendADValue() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (!(humidity > 0)) {
    temperature = random(40);
    humidity = random(100);
  }
  WebSocketsList &clients = server.getActiveWebSockets();
  // String value = String(system_adc_read());
  String data = "{\"temperature\":\"" + String(temperature) +
                "\",\"humidity\":\"" + String(humidity) + "\"}";
  if (totalActiveSockets > 0) {
    // for (int i = 0; i < totalActiveSockets; i++) {
    // clients[i].sendString(data);
    // }
    clients[0].sendString(data);
    // Serial.println(data);
  }
}

void wsConnected(WebSocket &socket) {
  Serial.printf("WebSocket Connected\r\n");
  totalActiveSockets++;
  if (!sendAdTimer.isStarted()) {
    sendAdTimer.initializeMs(500, sendADValue).start();
  }
}

void wsMessageReceived(WebSocket &socket, const String &message) {
  Serial.printf("WebSocket received:  %s\r\n", message.c_str());
  String response = "Echo: " + message;
  socket.sendString(response);
}

void wsDisconnected(WebSocket &socket) {
  Serial.printf("WebSocket disconnected\r\n");
  if (totalActiveSockets > 0) {
    totalActiveSockets--;
  } else {
    sendAdTimer.stop();
  }
}

void configWebSocket() {
  // Web Sockets configuration
  server.enableWebSockets(true);
  server.setWebSocketConnectionHandler(wsConnected);
  server.setWebSocketMessageHandler(wsMessageReceived);
  server.setWebSocketDisconnectionHandler(wsDisconnected);
  Serial.println("\r\n=== WEB Socket STARTED ===");
}
