#include <SoftwareSerial.h>
#include "TinyGPS.h"
#include "Akeru.h"

Akeru_ akeru;
TinyGPS gps;


struct data {
  float latitude;
  float longitude;
  float pression;
};

void setup() {
  // LED 13 is used to "debug" sigfox operations
  pinMode(13, OUTPUT);

  // Initialize sigfox modem
  akeru.begin();
  
  // Start serial communication, because everyone needs to !
  Serial.begin(115200);

  delay(2000);
}

void loop() {
  // Get NMEA data
  float latitude;
  float longitude;
  unsigned long fix_age = 9999;
  float pression = 50;

  while (fix_age > 1000) {
    while (Serial.available()) {
      if (gps.encode(Serial.read())) {
        gps.f_get_position(&latitude, &longitude, &fix_age);
      }
      Serial.flush();
    }
  }

  latitude = 1000.0;
  longitude = 1000.0;
  // Some debug can't be harmful
  Serial.println(latitude);
  Serial.println(longitude);
  Serial.println(fix_age);
  Serial.println(pression);

  data my_data = {latitude, longitude, pression};

  // Send data to Sigfox network
  digitalWrite(13, HIGH);
  akeru.send(&my_data, sizeof(data));
  digitalWrite(13, LOW);

  delay(1000);
}
