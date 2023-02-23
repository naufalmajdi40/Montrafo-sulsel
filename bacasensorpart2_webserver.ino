#include <PZEM004Tv30.h>
#define PZEM_RX_PIN 17
#define PZEM_TX_PIN 13
#define PZEM_SERIAL Serial2
#include <Adafruit_MLX90614.h>
#include <lorawan.h>
#include <WiFi.h>
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
#include <ArduinoJson.h>
#include "AsyncJson.h"
#define SCK 5
#define MISO 19
#define MOSI 27
PZEM004Tv30 pzem(PZEM_SERIAL, PZEM_RX_PIN, PZEM_TX_PIN, 0x01);
PZEM004Tv30 pzem2(PZEM_SERIAL, PZEM_RX_PIN, PZEM_TX_PIN, 0x02);
PZEM004Tv30 pzem3(PZEM_SERIAL, PZEM_RX_PIN, PZEM_TX_PIN, 0x03);

Adafruit_MLX90614 mlx = Adafruit_MLX90614(); //create object mlx Sensor
//////////config Wifi////////////

String ssid, password = "";
AsyncWebServer server(80);


/////////// config millis///////
unsigned long eventTime_1 = 10000;
unsigned long eventTime_2 = 5000;
unsigned long eventTime_3 = 600000;
unsigned long previousTime_1 = 0;
unsigned long previousTime_2 = 0;
unsigned long previousTime_3 = 0;
//ABP Credentials
//const char *devAddr = "0109c82d";
//const char *nwkSKey = "7c731bd2d514cb882f951be64d7a5d81";
//const char *appSKey = "e732c6a6fe2e91a1e0c89fe50c370007";
String devAddr;
String nwkSKey;
String kode;
String appSKey;
//const char *devAddr = "01f3f6e1";
//const char *nwkSKey = "012f4425b739f0a9d2a47cc0ccee9b3d";
//const char *appSKey = "f9275304fdbdaf617a479e84a7774261";


char dtLoRaSensor[100];
char outStr[255];
byte recvStatus = 0;
int wifiCount = 0;
int wifiMode = 0;
const int batPin=38;
float batVal=0;
//Lora RFM95 PIN
const sRFM_pins RFM_pins = {
  .CS = 18,
  .RST = 14,
  .DIO0 = 26,
  .DIO1 = -1,
  .DIO2 = -1,
  .DIO5 = -1,
};
DynamicJsonDocument doc(1024);
DynamicJsonDocument doc2(1024);
StaticJsonDocument<1024> doc3;
float voltage1, voltage2, voltage3, current1, current2, current3, frequency1, frequency2, frequency3, temp = 0;
#define uS_TO_S_FACTOR 1000
void setup() {
  // Debugging Serial port
  Serial.begin(115200);
  //Serial2.begin(9600);
  print_wakeup_reason();
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  mlx.begin(0x5A);
  initWifi();
  delay(1);
  initLoRa();
  //    initSpiffs();
 // initServer();
  Serial.println(eventTime_1);
  esp_sleep_enable_timer_wakeup(eventTime_1 * uS_TO_S_FACTOR);
  // pzem.resetEnergy()
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - previousTime_1 >= eventTime_1) {
    String Sensor = bacasensor();
    sprintf(dtLoRaSensor, Sensor.c_str());
    lora.sendUplink(dtLoRaSensor, strlen(dtLoRaSensor), 0, 1);
    Serial.println(Sensor);
    lora.update();
    previousTime_1 = currentTime;
    
    esp_deep_sleep_start();
  }
  if (currentTime - previousTime_2 >= eventTime_2) {
//    if (WiFi.status() != WL_CONNECTED && wifiMode == 0 ) {
//      wifiCount ++;
//      Serial.println("connectiong Wifi...");
//    }
//    if (wifiCount > 5 && wifiMode == 0) {
//      WiFi.disconnect(true);
//      delay(100);
//      WiFi.softAP("MONTRAFO0007", "montrafo1234");
//      IPAddress IP = WiFi.softAPIP();
//      wifiMode = 1;
//    }
    previousTime_2 = currentTime;
  }
  if (currentTime - previousTime_3 >= eventTime_3) {
//    if (WiFi.status() != WL_CONNECTED ) {
//      wifiMode = 0;
//      WiFi.disconnect(true);
//      initWifi();
//      Serial.println("reconnectWifi");
//    }
    previousTime_3 = currentTime;
  }
  recvStatus = lora.readData(outStr);
  if (recvStatus) {
    Serial.print("====>> ");
    Serial.println(outStr);
  }

  // Check Lora RX
  
}
