
void initLoRa() {
   SPI.begin(SCK, MISO, MOSI, SS);
  if (!lora.init()) {
    Serial.println("RFM95 not detected");
    delay(5000);
    return;
  }
  lora.setDeviceClass(CLASS_C);

  // Set Data Rate
  lora.setDataRate(SF7BW125);

  // set channel to random
  lora.setChannel(MULTI);
  // Put ABP Key and DevAddress here
  lora.setNwkSKey(nwkSKey.c_str());
  lora.setAppSKey(appSKey.c_str());
  lora.setDevAddr(devAddr.c_str());
  Serial.println(devAddr);
}
