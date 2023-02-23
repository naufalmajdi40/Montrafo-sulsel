String processor(const String& var) {
  Serial.println(var);
  if (var == "STATE") {

    String  ledState = "OFF";

    Serial.print(ledState);
    return ledState;
  }
  return String();
}
