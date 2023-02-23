
void writefile(String loc, String s) {
  File file = SPIFFS.open(loc, "w");
  if (!file) {
    Serial.println("Error opening file for writing");
    return;
  }
  int bytesWritten = file.print(s);
}
String readFileStr(String str) {
  String dataFs;
  File file = SPIFFS.open(str, "r");
  Serial.println(file);
  if (!file) {
    Serial.println("Failed to open file for reading");
    //return;
  }
  while (file.available()) {
    //Serial.write(file.read());
    dataFs += (char)file.read();
    delayMicroseconds(100);
  }
  file.close();
  return dataFs;
}
