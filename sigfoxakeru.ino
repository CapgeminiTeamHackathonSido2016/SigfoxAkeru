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
  short latitude;
  short longitude;
  char pneu1;
  char pneu2;
  char pneu3;
  char pneu4;
  char pneu5;
  char pneu6;
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
  short latitude;
  short longitude;
  char pneu1;
  char pneu2;
  char pneu3;
  char pneu4;
  char pneu5;
  char pneu6;

  latitude = 459;
  longitude = 245;
  pneu1 = 23;
  pneu2 = 22;
  pneu3 = 21;
  pneu4 = 22;
  pneu5 = 19;
  pneu6 = 20;

  data datas = {latitude, longitude, pneu1, pneu2, pneu3, pneu4, pneu5, pneu6};

  // Send data to Sigfox network
  digitalWrite(13, HIGH);
  akeru.send(&datas, sizeof(data));
  digitalWrite(13, LOW);

  delay(1000);
  exit(0);
}
