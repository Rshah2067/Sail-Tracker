#include <Arduino.h>
#include <Adafruit_ADXL343.h>
#include <Adafruit_GPS.h>
#include <SD.h>
#include <SoftwareSerial.h>

SoftwareSerial gpsSerial(7,6);
Adafruit_GPS GPS(&gpsSerial);

void setup() {
  Serial.begin(115200);
  delay(500);
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  delay(1000);
}

void loop() {
  if( GPS.fix){
  Serial.print("Lattitude");
  Serial.println(GPS.latitude);
  
  Serial.println("Longitude");
  Serial.println(GPS.longitude);
}
else{

  Serial.println(GPS.fix);
}
}

// put function definitions here:
