void initWifi() {
  String cfg = readFileStr("/config.json");
  Serial.println(cfg);
  DeserializationError error = deserializeJson(doc3, cfg);
  const char* ssidJson = doc3["ssid"];
  const char* passJson = doc3["pass"];
  const char* devAddrJson = doc3["devAddr"];
  const char* nwkSKeyJson = doc3["nwkSKey"];
  const char*appSKeyJson = doc3["appSKey"];
  const char* kodeJson = doc3["kode"];
  kode = kodeJson;
  eventTime_1 = doc3["intv"];
  Serial.println(eventTime_1);
  ssid = ssidJson;
  password = passJson;

  devAddr = devAddrJson;
  nwkSKey = nwkSKeyJson;
  appSKey = appSKeyJson;
  //Serial.println(ssid);
  //Serial.println(password);
  // WiFi.begin(ssidJson, passJson);
  //while (WiFi.status() != WL_CONNECTED) {
  // delay(1000);
  // Serial.println("Connecting to WiFi..");
  //}
  //Serial.println(WiFi.localIP());
}
void scanWifi() {
  // WiFi.disconnect();
  // delay(100);
  // WiFi.mode(WIFI_STA);
  // WiFi.disconnect();
  // delay(100);
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
      delay(10);
    }
  }
  Serial.println("");
  //initWifi();
}
