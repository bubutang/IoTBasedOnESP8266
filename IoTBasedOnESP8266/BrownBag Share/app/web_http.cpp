#include <web_http.h>
#include <user_config.h>
#include <SmingCore/SmingCore.h>
#include <led.h>
extern HttpServer server;

void onIndex(HttpRequest &request, HttpResponse &response) {
  TemplateFileStream *tmpl = new TemplateFileStream("index.html");
  // auto &vars = tmpl->variables();
  // vars["counter"] = String(counter);
  // this template object will be deleted automatically
  response.sendTemplate(tmpl);
}

void onFile(HttpRequest &request, HttpResponse &response) {
  String file = request.getPath();
  if (file[0] == '/')
    file = file.substring(1);
  if (file[0] == '.')
    response.forbidden();
  else {
    // It's important to use cache for better performance.
    response.setCache(86400, true);
    response.sendFile(file);
  }
}

void configHttp() {

  server.addPath("/", onIndex);
  server.setDefaultHandler(onFile);

  Serial.println("\r\n=== HTTP SERVER STARTED ===");
}
