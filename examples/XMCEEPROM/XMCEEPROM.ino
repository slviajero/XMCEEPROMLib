/* 
 * Stefan's XMC EEPROM Library
 *
 * See the licence file on for copyright/left.
 * (GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007)
 *
 * Author: Stefan Lenz, sl001@serverfabrik.de
 *  
 * Simple test program 
 * 
 */

#include <XMCEEPROMLib.h>


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  delay(3000); 

  // begin the EEPROM Emulator
  Serial.println("EEPROM emulator started");
  EEPROM.begin(4096);
  Serial.print("Status: "); Serial.println(EEPROM.status());

  // wait a little
  delay(3000);

  // show what is there
  Serial.println("EEPROM page 0");
  for (int i=0; i<256; i++) {
    if (i % 16 == 0 ) {
      Serial.println();
      Serial.print(i);
      Serial.print(": ");
    }
    Serial.print(EEPROM.read(i)); Serial.print(" "); 
  } 
  Serial.println();

  // wait a little and say something
  Serial.print("Error status is "); 
  Serial.println(EEPROM.status());
  delay(1000);
  
  // test 1 - write one byte and make permanent with a commit
  Serial.println("First test, write one cell");
  Serial.print("Cell 10 is "); 
  Serial.println(EEPROM.read(10));
  if (EEPROM.read(10) == 42) EEPROM.write(10,84); else EEPROM.write(10, 42);
  Serial.print("Cell 10 is now "); 
  Serial.println(EEPROM.read(10));
  Serial.println("This should have changed now.");
  Serial.println("Committing to flash");
  EEPROM.commit();

  // test 2 - provoke a write page fault
  Serial.println("EEPROM page 0 is now");
  for (int i=0; i<256; i++) {
    if (i % 16 == 0 ) {
      Serial.println();
      Serial.print(i);
      Serial.print(": ");
    }
    Serial.print(EEPROM.read(i)); Serial.print(" ");     
  }
  Serial.println();
  
  // wait a little and say something
  Serial.print("Error status is "); 
  Serial.println(EEPROM.status());
  delay(1000);

  // write and then provoke the page fault
  EEPROM.write(10, 77);
  EEPROM.write(256, 0); 
  Serial.println("EEPROM page 0 is now");
  for (int i=0; i<256; i++) {
    if (i % 16 == 0 ) {
      Serial.println();
      Serial.print(i);
      Serial.print(": ");
    }
    Serial.print(EEPROM.read(i)); Serial.print(" ");     
  }
  Serial.println();

}

void loop() {
  // put your main code here, to run repeatedly:

}
