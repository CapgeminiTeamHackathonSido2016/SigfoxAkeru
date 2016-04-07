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
  char pneu1;
  char pneu2;
  char pneu3;
  char pneu4;
};

void setup() {

    static int i = 0;
    static int j = 0;
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
  char pneu1;
  char pneu2;
  char pneu3;
  char pneu4;
  static int i = 0;
  static int j = 0;
  
  latitude = reverse_nibbles(modify_latitude(&i));
  longitude = reverse_nibbles(modify_longitude(&i));
  i++;
  //longitude = reverse_nibbles(12345678);
  /*pneu1 = 22;
  pneu2 = 25;
  pneu3 = 26;
  pneu4 = 28; */
  pneu1 = 65;
  pneu2 = 66;
  pneu3 = 67;
  pneu4 = 66;
  
  data datas = {latitude, longitude, pneu1, pneu2, pneu3, pneu4};
  
  // Send data to Sigfox network

  akeru.send(&datas, sizeof(data));

  delay(1000);
}
