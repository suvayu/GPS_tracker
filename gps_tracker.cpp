#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>

File myFile;
uint32_t lastsave(0);
SoftwareSerial mySerial(3, 2);
Adafruit_GPS GPS(&mySerial);
#define GPSECHO  false
boolean usingInterrupt = false;
void useInterrupt(boolean); // Func prototype keeps Arduino 0023 happy

const char* rowHeaders = "date, time, fix, quality, latitude, longitude, altitude(metres), speed(knots), angle, satellites";

void setup()  
{
  Serial.begin(115200);
  //Serial.println("Adafruit GPS library basic test!");
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  GPS.sendCommand(PGCMD_ANTENNA);
  useInterrupt(true);
  delay(1000);
  mySerial.println(PMTK_Q_RELEASE);
  //Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  //Serial.println("initialization done.");
  myFile = SD.open("test.csv", FILE_WRITE);
  myFile.println(rowHeaders);
  myFile.flush();
}

SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
#ifdef UDR0
  if (GPSECHO)
    if (c) UDR0 = c;  
#endif
}

void useInterrupt(boolean v) {
  if (v) {
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } else {
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}

uint32_t timer = millis();

char* getRow(char *row, Adafruit_GPS& gpsNow)
{
  char lat[15], lng[16], alt[9], spd[6], agl[7];

  sprintf(row, "%d/%d/%d, %d:%d:%d, %d, %d, %s, %s, %s, %s, %s, %d", 
          GPS.day, GPS.month, GPS.year,
          GPS.hour, GPS.minute, GPS.seconds,
          GPS.fix,
          GPS.fixquality,
          dtostrf(GPS.latitudeDegrees,  14, 10, lat),
          dtostrf(GPS.longitudeDegrees, 15, 10, lng),
          dtostrf(GPS.altitude,          8,  2, alt),
          dtostrf(GPS.speed,             5,  2, spd),
          dtostrf(GPS.angle,             6,  2, spd),
          GPS.satellites);
  return row;
}
void loop()                     // run over and over again
{
  if(myFile){
    //Serial.print("In Loop");
    if (! usingInterrupt) {
      // read data from the GPS in the 'main loop'
      char c = GPS.read();
      if (GPSECHO)
        if (c) Serial.print(c);
    }
    if (GPS.newNMEAreceived()) {
      if (!GPS.parse(GPS.lastNMEA())) 
        return; 
    }
  
    if (timer > millis())  timer = millis();
    if (millis() - timer > 2000) { 
      timer = millis(); // reset the timer
      char row[128];
      getRow(row, GPS);
      myFile.println(row);
      Serial.println(row);
      myFile.flush();
    }
  }
  else
    Serial.print("File is corrupt");
}
