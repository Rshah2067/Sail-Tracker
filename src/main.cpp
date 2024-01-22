#include <Adafruit_ADXL343.h>
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
//Define SD card SPI Bus
const int _MOSI = 19;
const int _MISO = 16;
const int _CS = 17;
const int _SCK = 18;
//Init Accelerometer 
Adafruit_ADXL343 accel = Adafruit_ADXL343(12345);
void setup() {

  Serial.begin(9600);
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
    digitalWrite(LED_BUILTIN,HIGH);
    Serial.println("Failed to init SD");
    return;
  }
  Serial.println("SD Inited");
}

void loop() {
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
