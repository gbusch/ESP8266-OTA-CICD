#include <ESP8266httpUpdate.h>
#include <ESP8266HTTPClient.h>

#include "credentials.h"

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  WiFi.begin(ssid, password);
  /*connection to WiFi*/
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  HTTPClient httpClient;
  httpClient.begin("http://192.168.178.35:8080/firmware.bin");
  int httpCode = httpClient.GET();
  Serial.println(httpCode);

  /* warning - the update is done after each reboot now */
  t_httpUpdate_return ret = ESPhttpUpdate.update("192.168.178.35", 8080, "/firmware.bin"); //Location of your binary file
  /*upload information only */
  switch (ret) {
    case HTTP_UPDATE_FAILED:
      Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
      break;
    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("HTTP_UPDATE_NO_UPDATES");
      break;
    case HTTP_UPDATE_OK:
      Serial.println("HTTP_UPDATE_OK");
      break;
  }
  pinMode(LED_BUILTIN, OUTPUT);
}

void blinkNTimes(int n) {
  for (size_t i = 0; i < n; i++)
  {
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);                      // Wait for a second
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
  }
}

void loop() {
  int n = 5;
  blinkNTimes(n);
  delay(2000); 
}
