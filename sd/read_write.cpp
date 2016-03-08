/* -*- mode: c; -*- */

/*
  SD card read/write

 This example shows how to read and write data to and from an SD card file
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4

 */

/*
  This example program writes time stamps to the SD card every 0.1
  second.  It also flushes the file to the card every 5 seconds to
  protect against data loss due to file corruption due to power
  failure - Suvayu & Harmandeep.
*/

#include <SPI.h>
#include <SD.h>

File myFile;
uint32_t lastsave(0);

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // NOTE: only one file can be open at a time, so you have to close
  // this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);
}

void loop()
{
  // if the file opened okay, write to it:
  if (myFile) {
    myFile.println(millis());
    delay(100);
    if (50 == lastsave) {
      Serial.println("Flushing ...");
      myFile.flush();
      lastsave = 0;
    } else {
      lastsave = lastsave + 1;
      Serial.println(lastsave);
    }
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
