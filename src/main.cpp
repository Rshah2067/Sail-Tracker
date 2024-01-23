#include <Adafruit_ADXL343.h>
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <Adafruit_GPS.h>
//Define GPS Serial and toggle ECHO of GPS String
#define GPSSerial Serial1
#define GPSECHO true
Adafruit_GPS GPS(&Serial1);

//Define SD card SPI Bus
const int _MOSI = 19;
const int _MISO = 16;
const int _CS = 17;
const int _SCK = 18;
//Init Accelerometer 
Adafruit_ADXL343 accel = Adafruit_ADXL343(12345);
void setup() {

  Serial.begin(9600);
  //Wait For Serial to Start
  while(!Serial){
    delay(10);
  }

  //Start GPS Serial
  GPSSerial.begin(9600);
  //Set GPS Output mode and frequency
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
  GPS.sendCommand(PGCMD_ANTENNA);
  //Start Accelerometer
  if(!accel.begin()){
    Serial.println("Failed to init Accelerometer");
    return;
  }
  //Config Accelerometer
  accel.setRange(ADXL343_RANGE_16_G);
  accel.setDataRate(ADXL343_DATARATE_0_10_HZ);

  //SD card SPI 
  SPI.setTX(_MOSI);
  SPI.setRX(_MISO);
  SPI.setCS(_CS);
  SPI.setSCK(_SCK);
  //Init SD Card
  Serial.println("Initing SD Card");
  if(!SD.begin(_CS)){
    //Debug LED, in case of SD failure, LED is turned on
    digitalWrite(LED_BUILTIN,HIGH);
    Serial.println("Failed to init SD");
    return;
  }
  Serial.println("SD Inited");
}

void loop() {

  //Create state array that contains all important information
  int[] state = new int
  //Read GPS sentance and print if desired
  char c = GPS.read();
  if(GPSECHO && c) Serial.print(c);
  //check if a new GPS sentance is recived if so parse it
  if(GPS.newNMEAreceived()){
    Serial.print(GPS.lastNMEA());
    //try parsing
    if(GPS.parse(GPS.lastNMEA())){
      return;
    }
    
  }
  //Add GPS lat/long to data String
  //get new accelerometer event
  sensors_event_t event;
  accel.getEvent(&event);
  Serial.println(event.acceleration.x);
  sleep_ms(1000);
  //Save Accelerometer Data to SD card
  File dataFile = SD.open("datalog.txt",FILE_WRITE);
  if(dataFile){
    dataFile.println(event.acceleration.x);
    Serial.println("Saving" + String(event.acceleration.x));
    dataFile.close();
  }
  else Serial.println("failed to write data");
  //LED Blink for debugging
  digitalWrite(LED_BUILTIN, HIGH);
  sleep_ms(500);
  digitalWrite(LED_BUILTIN, LOW);
  sleep_ms(500);
  
}

float accelMagnitude(float x, float y, float z){
  return sqrt(x*x +y*y + z*z);
}