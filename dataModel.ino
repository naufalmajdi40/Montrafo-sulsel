void bacaConfigJSON() {
  doc2["devAddr"] = devAddr;
  doc2["nwkSKey"] = nwkSKey;
  doc2["appSKey"] = appSKey;
  doc2["ssid"] = ssid;
  doc2["pass"] = password;
  doc2["intv"] = String(eventTime_1);
}
void bacaSensorJSON() {
  doc["ir"] = String(current1);
  doc["is"] = String(current2);
  doc["it"] = String(current3);
  doc["vr"] = String(voltage1);
  doc["vs"] = String(voltage2);
  doc["vt"] = String(voltage3);
  doc["f"] = String(frequency1);
  doc["t"] = String(temp);
}
String bacasensor() {
  int  suhu1 = analogRead(0);
  int suhulm = (suhu1 / 2.0479) - 25;
  voltage1 = pzem.voltage();
  current1 = pzem.current();
  frequency1 = pzem.frequency();
  float power1 = pzem.power();
  float energy1 = pzem.energy();
  float pf1 = pzem.pf();
  //baca sensor2
  voltage2 = pzem2.voltage();
  current2 = pzem2.current();
  frequency2 = pzem2.frequency();
  // float current2 = (0.0401 * i2) + 0.0981;
  float power2 = pzem2.power();
  float energy2 = pzem2.energy();
  float pf2 = pzem2.pf();
  //baca sensor3
  voltage3 = pzem3.voltage();
  current3 = pzem3.current();
  frequency3 = pzem3.frequency();
  //float current3 = (0.0401 * i3) + 0.0981;
  float power3 = pzem3.power();
  float energy3 = pzem3.energy();
  float pf3 = pzem3.pf();
  //float t = dht.readTemperature();
  float t = suhulm;
  //  batVal=analogRead(batPin);
  float sensor = 0 ;
  for (int i = 0; i < 20; i++) {
    batVal = analogRead(batPin);
    sensor += batVal * 3.3 / 4095 * 2 ;
  }
  float batv=sensor/20;
  batVal = sensor*1000/20;
  int batp = map(batVal, 2000, 3800, 0, 100);
  if (batp > 100) {
    batp = 100;
  }
  if (batp <= 0) {
    batp = 0;
  }
  batVal = batVal / 1000;
  temp = mlx.readObjectTempC();
  String dataSensor = "montrafo|";
  dataSensor += kode;
  dataSensor += "*";
  dataSensor += String(current1);
  dataSensor += "*";
  dataSensor += String(current2);
  dataSensor += "*";
  dataSensor += String(current3);
  dataSensor += "*";
  dataSensor += String(voltage1);
  dataSensor += "*";
  dataSensor += String(voltage2);
  dataSensor += "*";
  dataSensor += String(voltage3);
  dataSensor += "*";
  dataSensor += String(frequency1);
  dataSensor += "*";
  dataSensor += String(frequency2);
  dataSensor += "*";
  dataSensor += String(frequency3);
  dataSensor += "*";
  dataSensor += String(pf1);
  dataSensor += "*";
  dataSensor += String(pf2);
  dataSensor += "*";
  dataSensor += String(pf3);
  dataSensor += "*";
  dataSensor += String(temp);
  dataSensor += "*";
  dataSensor += String(batv);
  dataSensor += "*";
  dataSensor += String(batp);
  dataSensor += '#';
  return dataSensor;
}
