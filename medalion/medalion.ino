#include "ESP8266WiFi.h"

void setup() {
  Serial.begin(115200);

  pinMode(2, OUTPUT);
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  
  delay(100);
  
  Serial.println("Setup done");  
}

void loop() {
  Serial.println("Scan start");  
  
  bool foundOpen = false;  
  int networks   = WiFi.scanNetworks();
  
  Serial.println("Scan done");
  
  if (networks != 0) {    
    for (int i = 0; i < networks; ++i) {
      if ( WiFi.encryptionType(i) == ENC_TYPE_NONE ) {
        foundOpen = true;
      }      
    }
  }

  if (foundOpen) {
    doVibration();
  }
  
  delay(5000);
}

void doVibration() {
  int delays[]   = { 200, 200, 200, 800, 800, 200, 200, 200};
  int delayCount = 8;
  
  delay(500);
  for (int thisPin = delayCount - 1; thisPin >= 0; thisPin--) { 
    digitalWrite(2, HIGH);
    delay( delays[thisPin] );  
    digitalWrite(2, LOW);
    delay(200);   
  }
}

