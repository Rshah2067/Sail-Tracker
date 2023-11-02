#include <Arduino.h>
#include <Adafruit_ADXL343.h>
#include <Adafruit_GPS.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <heaversine.h>

//GPS should be connected to digital pins 6&7
SoftwareSerial gpsSerial(7,6);
Adafruit_GPS GPS(&gpsSerial);
//default constructor is used to the reference lat/long is set to 0 by default, must call
heaversine hv();

Sd2Card card;
SdVolume volume;
SdFile root;

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
//Varaible to store the current GPS position with item 0 being lat and 1 being long
double posGPS(2);
void loop() {
  //TODO implement data logging
  

  if(!GPS.fix){
      Serial.println("Lost Print");
      while(!GPS.fix){
        Serial.println("waiting to regain fix");
      }
  }
  //TODO Implement function that converts minutes and seconds to one lat/long value
  

}


