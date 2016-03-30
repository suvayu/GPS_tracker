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

String getFileName()
{
  File counter;
  counter = SD.open("last", FILE_WRITE);
  counter.seek(0);
  uint32_t num = 0;
  if(counter.size()>0) num = counter.read();
  counter.seek(0);
  counter.write(num+1);
  counter.close();

  String str = String(num);
  return "GPS"+str+".txt";
}
void setup()  
{
  Serial.begin(115200);
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  GPS.sendCommand(PGCMD_ANTENNA);
  useInterrupt(true);
  delay(1000);
  mySerial.println(PMTK_Q_RELEASE);
  if (!SD.begin(4)) {
    return;
  }
  String fileName = getFileName();
  myFile = SD.open(fileName, FILE_WRITE);
  myFile.println(F("date, time, fix, quality, latitude, longitude, altitude(metres), satellites"));
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

  sprintf(row, "%d/%d/%d, %d:%d:%d, %d, %d, %s, %s, %s, %d", 
          gpsNow.day, gpsNow.month, gpsNow.year,
          gpsNow.hour, gpsNow.minute, gpsNow.seconds,
          gpsNow.fix,
          gpsNow.fixquality,
          dtostrf(gpsNow.latitudeDegrees,  14, 10, lat),
          dtostrf(gpsNow.longitudeDegrees, 15, 10, lng),
          dtostrf(gpsNow.altitude,          8,  2, alt),
          gpsNow.satellites);
  return row;
}
void loop()
{
  if(myFile){
    if (! usingInterrupt) {
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
    Serial.print(F("File is corrupt"));
}