#include <web_api.h>
#include <user_config.h>
#include <SmingCore/SmingCore.h>
#include <led.h>

extern HttpServer server;

void onApiRGB(HttpRequest &request, HttpResponse &response) {
  int color = request.getPostParameter("color").toInt(); // post
  ws2812Updata(color);

  JsonObjectStream *stream = new JsonObjectStream();
  JsonObject &json = stream->getRoot();
  json["status"] = (bool)true;

  response.sendJsonObject(stream);
}

void onApiColor(HttpRequest &request, HttpResponse &response) {

  char r = 0xff & request.getPostParameter("red", "0").toInt();
  char g = 0xff & request.getPostParameter("green", "0").toInt();
  char b = 0xff & request.getPostParameter("blue", "0").toInt();
  ws2812Updata(r, g, b);

  JsonObjectStream *stream = new JsonObjectStream();
  JsonObject &json = stream->getRoot();
  json["status"] = (bool)true;
  json["red"] = r;
  json["green"] = g;
  json["blue"] = b;
  response.sendJsonObject(stream);
}

void onApiLED(HttpRequest &request, HttpResponse &response) {
  int led = request.getPostParameter("led").toInt(); // post
  ledSet(led);

  JsonObjectStream *stream = new JsonObjectStream();
  JsonObject &json = stream->getRoot();
  json["status"] = (bool)true;
  json["led"] = ledStatus();
  response.sendJsonObject(stream);
}

void onApiAD(HttpRequest &request, HttpResponse &response) {
  JsonObjectStream *stream = new JsonObjectStream();
  JsonObject &json = stream->getRoot();
  json["status"] = (bool)true;
  JsonObject &sensors = json.createNestedObject("sensors");
  sensors["ADValue"] = system_adc_read();
  response.sendJsonObject(stream);
}

void configApi() {
  server.addPath("/api/ad", onApiAD);
  server.addPath("/api/led", onApiLED);
  server.addPath("/api/color", onApiColor);
  server.addPath("/api/rgb", onApiRGB);
}
