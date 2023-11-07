#include <Arduino.h>
#include <Adafruit_ADXL343.h>
#include <Adafruit_GPS.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <SPI.h>
//GPS should be connected to digital pins 6&7
SoftwareSerial gpsSerial(7,6);
Adafruit_GPS GPS(&gpsSerial);
//default constructor is used to the reference lat/long is set to 0 by default, must call
//heaversine hv();

#define GPSECHO = true;
void setup() {
  Serial.begin(115200);
  while(!Serial){
    ;
  }
  delay(500);
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_ANTENNA);

  Serial.print("Initializing SD card...");

  if (!SD.begin(10))
  {
    Serial.println("failed init");

    while(1){
  //    Serial.println("failed to init");
    }
  }
  
  Serial.println("SD Card inited");
  File dataFile = SD.open("Log1.txt",FILE_WRITE);
  if(dataFile){
  dataFile.println("Time,lattitude,longitude");
  Serial.println("Time,lattitude,longitude");
  dataFile.close();
  }
  while(!GPS.fix){
   
   Serial.println(GPS.fix);
  }
  Serial.println(GPS.fixquality);
}
//Varaible to store the current GPS position with item 0 being lat and 1 being long
//double posGPS(2);
void loop() {
  //TODO implement data logging
  //String output = "";
  
  File dataFile = SD.open("Log1.txt",FILE_WRITE);
  if(dataFile){
    dataFile.println(GPS.latitude_fixed + "," + GPS.longitude_fixed);
    Serial.println(GPS.latitude_fixed + "," + GPS.longitude_fixed);
    dataFile.close();
  }
  delay(2000);
  if(!GPS.fix){
      Serial.println("Lost Print");
      while(!GPS.fix){
        Serial.println("waiting to regain fix");
      }
  }
  
  //TODO Implement function that converts minutes and seconds to one lat/long value
  

}


