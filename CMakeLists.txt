#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

const int BUTTON_PIN = 0; // change to your pin

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  WiFi.begin(ssid, password);
  Serial.print("Connecting WiFi");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
}

void loop() {
  if(digitalRead(BUTTON_PIN) == LOW) { // button pressed
    Serial.println("Button pressed!");

    if(WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin("http://<your_local_server>/button");
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{\"button\":\"pressed\"}");
      Serial.println(httpResponseCode);
      http.end();
    }
    delay(500); // debounce
  }
}
