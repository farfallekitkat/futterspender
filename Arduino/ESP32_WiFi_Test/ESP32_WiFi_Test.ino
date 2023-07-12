#include <WiFi.h>

const char* ssid = "iPhone von Falk mini";
const char* password = "hallo1234";

void initWiFi() {
  Serial.printf("\nConnecting to %s", ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println("\nConnected to network");
  Serial.print("My IP address is: ");
  Serial.println(WiFi.localIP());
  Serial.print("RRSI: ");
  Serial.println(WiFi.RSSI());
}

void setup() {
  Serial.begin(9600);
  initWiFi();
}

void loop() {

}