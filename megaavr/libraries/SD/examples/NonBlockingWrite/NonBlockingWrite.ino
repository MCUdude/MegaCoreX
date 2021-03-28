/*
  Non-blocking Write

  This example demonstrates how to perform non-blocking writes
  to a file on a SD card. The file will contain the current millis()
  value every 10ms. If the SD card is busy, the data will be dataBuffered
  in order to not block the sketch.

  If data is successfully written, the built in LED will flash. After a few
  seconds, check the card for a file called datalog.txt

  NOTE: myFile.availableForWrite() will automatically sync the
        file contents as needed. You may lose some unsynced data
        still if myFile.sync() or myFile.close() is not called.

  Pin numbers reflect the default SPI pins for Uno and Nano models
  Updated for clarity and uniformity with other examples

  The circuit:
   analog sensors on analog ins 0, 1, and 2
   SD card attached to SPI bus as follows:
 ** SDO - pin 11
 ** SDI - pin 12
 ** CLK - pin 13
 ** CS - depends on your SD card shield or module.
    Pin 10 used here for consistency with other Arduino examples
    (for MKRZero SD: SDCARD_SS_PIN)

    modified 24 July 2020
    by Tom Igoe

  This example code is in the public domain.
*/
#include <SD.h>

const int chipSelect = 10;

// file name to use for writing
const char filename[] = "datalog.txt";

// File object to represent file
File myFile;
// string to buffer output
String dataBuffer;
// last time data was written to card:
unsigned long lastMillis = 0;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  // reserve 1kB for String used as a dataBuffer
  dataBuffer.reserve(1024);

  // set LED pin to output, used to blink when writing
  pinMode(LED_BUILTIN, OUTPUT);

  // wait for Serial Monitor to connect. Needed for native USB port boards only:
  while (!Serial);

  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("1. is a card inserted?");
    Serial.println("2. is your wiring correct?");
    Serial.println("3. did you change the chipSelect pin to match your shield or module?");
    Serial.println("Note: press reset or reopen this serial monitor after fixing your issue!");
    while (true);
  }

  Serial.println("initialization done.");

  // If you want to start from an empty file,
  // uncomment the next line:
  //  SD.remove(filename);
  // try to open the file for writing

  myFile = SD.open(filename, FILE_WRITE);
  if (!myFile) {
    Serial.print("error opening ");
    Serial.println(filename);
    while (true);
  }

  // add some new lines to start
  myFile.println();
  myFile.println("Hello World!");
  Serial.println("Starting to write to file...");
}

void loop() {
  // check if it's been over 10 ms since the last line added
  unsigned long now = millis();
  if ((now - lastMillis) >= 10) {
    // add a new line to the dataBuffer
    dataBuffer += "Hello ";
    dataBuffer += now;
    dataBuffer += "\r\n";
    // print the buffer length. This will change depending on when
    // data is actually written to the SD card file:
    Serial.print("Unsaved data buffer length (in bytes): ");
    Serial.println(dataBuffer.length());
    // note the time that the last line was added to the string
    lastMillis = now;
  }

  // check if the SD card is available to write data without blocking
  // and if the dataBuffered data is enough for the full chunk size
  unsigned int chunkSize = myFile.availableForWrite();
  if (chunkSize && dataBuffer.length() >= chunkSize) {
    // write to file and blink LED
    digitalWrite(LED_BUILTIN, HIGH);
    myFile.write(dataBuffer.c_str(), chunkSize);
    digitalWrite(LED_BUILTIN, LOW);
    // remove written data from dataBuffer
    dataBuffer.remove(0, chunkSize);
  }
}
