#include <Arduino.h>
#include <Adafruit_ADXL343.h>
#include <Adafruit_GPS.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <heaversine.h>
SoftwareSerial gpsSerial(7,6);
Adafruit_GPS GPS(&gpsSerial);
heaversine hv();
void setup() {
  Serial.begin(115200);
  delay(500);
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  delay(1000);
   while(!GPS.fix){
    Serial.println("waiting for fix");
  }
  Serial.println(GPS.fixquality);
  delay(1000);
}

void loop() {
 

  if(!GPS.fix){
     // Serial.println("Lost Print");
  }
}


// put function definitions here:
