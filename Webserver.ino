void initServer() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  server.on("/index", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });

  // Route Api get Data Sensor
  server.on("/getData", HTTP_GET, [](AsyncWebServerRequest * request) {
    bacaSensorJSON() ;
    String output;
    serializeJson(doc, output);
    request->send(200, "application/json", output);
  });

  server.on("/getConfig", HTTP_GET, [](AsyncWebServerRequest * request) {
    bacaConfigJSON() ;
    String output;
    serializeJson(doc2, output);
    request->send(200, "application/json", output);
  });
  //Route Config
  server.on("/config", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/config.html", String(), false, processor);
  });
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  //Route saveConfig
  server.on("/saveConfig", HTTP_POST, [](AsyncWebServerRequest * request) {
    int params = request->params();
    Serial.println(params);
    String JsonData = "";
    for (int i = 0; i < params; i++) {
      AsyncWebParameter* p = request->getParam(i);
      Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
      doc2[p->name().c_str()] = p->value().c_str();
    }

    String output;
    serializeJson(doc2, output);
    writefile("/config.json", output);
    Serial.println(output);
    request->send(200, "application/json", "{\"status\":1}");
    delay(100);
    ESP.restart();
  });
  server.begin();
}
