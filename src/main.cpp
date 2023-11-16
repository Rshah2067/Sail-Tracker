#include <Arduino.h>
#include <Adafruit_ADXL343.h>
#include <Adafruit_GPS.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <SPI.h>
//GPS should be connected to digital pins 8 & 7
SoftwareSerial mySerial(8, 7);
Adafruit_GPS GPS(&mySerial);


void setup() {
  Serial.begin(115200);
  delay(5000);
  GPS.begin(9600);
  delay(500);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  delay(1000);
  mySerial.println(PMTK_Q_RELEASE);
 

  Serial.print("Initializing SD card...");

  if (!SD.begin(10))
  {
    Serial.println("failed init");

    while(1){
      Serial.println("failed to init");
    }
  }
  Serial.println("inited SD");
}
//boolean that tracks wheter we have parsed a new NMEA sentance
boolean updated = false;
void loop() {
  //parse new GPS info
  char c = GPS.read();
  if(GPS.newNMEAreceived()){
      updated = true;
      if(!GPS.parse(GPS.lastNMEA())){
        return;
      }
  }
  if(updated == true){
    Serial.println(GPS.longitude);
    Serial.println(GPS.latitude);
  }

  updated = false;
}


