#include <Adafruit_ADXL343.h>
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <Adafruit_GPS.h>
//Define GPS Serial and toggle ECHO of GPS String
#define GPSSerial Serial1
#define GPSECHO false
Adafruit_GPS GPS(&Serial1);
//define timer
u32_t timer = micros();
//Define SD card SPI Bus
const int _MOSI = 19;
const int _MISO = 16;
const int _CS = 17;
const int _SCK = 18;
//Init Accelerometer 
Adafruit_ADXL343 accel = Adafruit_ADXL343(12345);

//TODO implement mulit core processing by adding setup for second core and investigate how memory resourcse are shared between cores
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

  //SD card SPI bus init
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
  /*TODO currently t is being stored as a floating point long meaning it can't be put into this array. 
  Investigate wheter time can be stored as a double by truncating unecessary zeros and shifting decimal place.
  The time is stored as a floating long because it is meant to store time in micro seconds up to 50 days but I 
  don't need for this long storage. 
  */

  //Create state array that contains all important information
  //[lat,long,t,ax,zy,az]
  //creating an array for 2 reasons 1)if it is necessary to pass informtion via a FIFO bridge it will be more convient as one object
  //2)when doing kalman math it will become necessary to represent state as an array anyways

  double state[6];
  //Read GPS sentance and print if desired
  char c = GPS.read();
  if(GPSECHO && c) Serial.print(c);
  //check if a new GPS sentance is recived if so parse it
  if(GPS.newNMEAreceived()){
    Serial.print(GPS.lastNMEA());
    //try parsing
    if(!GPS.parse(GPS.lastNMEA())){
      return;
    }
    //if GPS is succesfully parsed update the current position
    else{
      //First convert GPS cordinates from minute seconds to decimal then store into state
      state[0] = GPS.latitude;
      state[1] = GPS.longitude;

    }
  }
  //Add GPS lat/long to data String
  //get new accelerometer event
  sensors_event_t event;
  accel.getEvent(&event);
  
  state[3] = event.acceleration.x;
  state[4] = event.acceleration.y;
  state[5] = event.acceleration.z;
  sleep_ms(1000);
  //Save Accelerometer Data to SD card
  File dataFile = SD.open("datalog.txt",FILE_WRITE);
  if(dataFile){
    for(int i=0;i<=5;i++){
      dataFile.print(String(state[i]) + ",");
      Serial.print(String(state[i])+",");
    }
    
    dataFile.close();
  }
  else Serial.println("failed to write data");
  //LED Blink for debugging
  digitalWrite(LED_BUILTIN, HIGH);
  sleep_ms(500);
  digitalWrite(LED_BUILTIN, LOW);
  sleep_ms(500);
}
//TODO test wheter conversion is necessary

//Funtion to convert GPS cordinates in minutes/seconds format to decimal, unsure if needed as there is conflicting documentation on how GPS outputs latitude
double degreesPlusSeconds (float minutes,float seconds){
  return minutes + seconds/60;
}
//TODO add method to pass information to other core
//TODO add method implementing haversine conversion of GPS cordinates to relative cartesian positions