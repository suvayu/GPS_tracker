#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>

File myFile;
uint32_t lastsave(0);
SoftwareSerial mySerial(3, 2);
Adafruit_GPS GPS(&mySerial);
#define GPSECHO  true
boolean usingInterrupt = false;
void useInterrupt(boolean); // Func prototype keeps Arduino 0023 happy

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
  myFile = SD.open("test.txt", FILE_WRITE);
  myFile.print("GPS Data-");
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
      
      myFile.print("\nTime: ");
      myFile.print(GPS.hour, DEC); myFile.print(':');
      myFile.print(GPS.minute, DEC); myFile.print(':');
      myFile.print(GPS.seconds, DEC); myFile.print('.');
      myFile.println(GPS.milliseconds);
      myFile.print("Date: ");
      myFile.print(GPS.day, DEC); myFile.print('/');
      myFile.print(GPS.month, DEC); myFile.print("/20");
      myFile.println(GPS.year, DEC);
      
      myFile.print("Fix: "); myFile.print((int)GPS.fix);
      myFile.print(" quality: "); myFile.println((int)GPS.fixquality);
      Serial.print("Year: "); Serial.print(GPS.year, DEC); 
      Serial.print(" Fix: "); Serial.println((int)GPS.fix);
      if (GPS.fix) {
        Serial.println("Getting data");
        myFile.print("Location: ");
        myFile.print(GPS.latitude, 4); Serial.print(GPS.lat);
        myFile.print(", "); 
        myFile.print(GPS.longitude, 4); Serial.println(GPS.lon);
        myFile.print("Location (in degrees, works with Google Maps): ");
        myFile.print(GPS.latitudeDegrees, 4);
        myFile.print(", "); 
        myFile.println(GPS.longitudeDegrees, 4);
        
        myFile.print("Speed (knots): "); Serial.println(GPS.speed);
        myFile.print("Angle: "); Serial.println(GPS.angle);
        myFile.print("Altitude: "); Serial.println(GPS.altitude);
        myFile.print("Satellites: "); Serial.println((int)GPS.satellites);
      }
      myFile.flush();
    }
  }
  else;
   // Serial.print("File is corrupt");
}
