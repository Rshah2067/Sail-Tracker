#include <Arduino.h>
#include <Adafruit_ADXL343.h>
#include <Adafruit_GPS.h>
#include <SD.h>
#include <SoftwareSerial.h>
#include <SPI.h>
//GPS should be connected to digital pins 6&7
<<<<<<< Updated upstream
SoftwareSerial mySerial(8, 7);
Adafruit_GPS GPS(&mySerial);
=======
SoftwareSerial gpsSerial(8,7);
Adafruit_GPS GPS(&gpsSerial);
>>>>>>> Stashed changes
//default constructor is used to the reference lat/long is set to 0 by default, must call
//heaversine hv();

void setup() {
  Serial.begin(115200);
<<<<<<< Updated upstream
 
=======
  delay(5000);
  Serial.println("file");
  delay(500);
>>>>>>> Stashed changes
  GPS.begin(9600);
  delay(500);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);

  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
<<<<<<< Updated upstream
 
  delay(1000);
  mySerial.println(PMTK_Q_RELEASE);
 

=======
  GPS.sendCommand(PGCMD_ANTENNA);
  delay(1000);
>>>>>>> Stashed changes
  Serial.print("Initializing SD card...");

  if (!SD.begin(10))
  {
    Serial.println("failed init");

    while(1){
  //    Serial.println("failed to init");
    }
  }
  Serial.println("inited SD");

  // while(!GPS.fix){
  // Serial.println("wayr" + GPS.fix);
  // delay(2000);
  // }
  delay(5000);
  while (!GPS.fix){

    if (GPS.newNMEAreceived())
    {
      if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
        return;  // we can
    }
  }
  Serial.println(GPS.fixquality);
}
//Varaible to store the current GPS position with item 0 being lat and 1 being long
//double posGPS(2);
void loop() {
  //TODO implement data logging
  //String output = "";
   if (GPS.newNMEAreceived())
  {
    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can
  }
  File dataFile = SD.open("Log1.txt",FILE_WRITE);
  if(dataFile){
    dataFile.println(GPS.latitude_fixed + "," + GPS.longitude_fixed);
    Serial.println(GPS.latitude_fixed + "," + GPS.longitude_fixed);
    dataFile.close();
  }
  
  // if(!GPS.fix){
  //     Serial.println("Lost Print");
  //     while(!GPS.fix){
  //       Serial.println("waiting to regain fix");
  //     }
  // }
  delay(2000);
  //TODO Implement function that converts minutes and seconds to one lat/long value
  

}


