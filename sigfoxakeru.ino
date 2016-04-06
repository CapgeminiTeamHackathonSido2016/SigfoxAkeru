/*
 * - GPS TX pin is plugged to Akeru pin 0
 * - GPS VCC pin is plugged to Akeru pin 3V3
 * - GPS GND pin is plugged to Akeru pin GND
 */


#include <SoftwareSerial.h>
#include "TinyGPS.h"
#include "Akeru.h"

Akeru_ akeru;
TinyGPS gps;


struct data {
  long latitude;
  long longitude;
  char pneu;
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
  long latitude;
  long longitude;
  char pneu;

  latitude = 1;
  longitude = 2;
  pneu = 65;

  data datas = {latitude, longitude, pneu};

  // Send data to Sigfox network
  digitalWrite(13, HIGH);
  akeru.send(&datas, sizeof(data));
  digitalWrite(13, LOW);

  delay(1000);
  exit(0);
}
