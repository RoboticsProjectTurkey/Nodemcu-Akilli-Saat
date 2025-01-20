/*
   EEPROM Read

   Reads the value of each byte of the EEPROM and prints it
   to the computer.
   This example code is in the public domain.
*/

#include <EEPROM.h>

// start reading from the first byte (address 0) of the EEPROM
int address = 0;
byte value;

void setup() {
  // initialize serial and wait for port to open:
  Serial.begin(9600);
  EEPROM.begin(512);
  delay(2000);
  EEPROM.write(1, 12);
  EEPROM.commit();
  Serial.println("1. yazıldı");
  delay(500);
  EEPROM.write(2, 8);
  EEPROM.commit();
  Serial.println("2. yazıldı");
  delay(500);
  EEPROM.write(3, 20);
  EEPROM.commit();
  Serial.println("3. yazıldı");
  delay(500);
  EEPROM.write(4, 30);
  EEPROM.commit();
  Serial.println("4. yazıldı");
  delay(500);
  EEPROM.write(5, 45);
  EEPROM.commit();
  Serial.println("5. yazıldı");
  delay(500);
  EEPROM.write(6, 15);
  EEPROM.commit();
  Serial.println("6. yazıldı");
  delay(500);
  EEPROM.write(7, 0);
  EEPROM.commit();
  Serial.println("7. yazıldı");
  delay(500);
  EEPROM.write(8, 0);
  EEPROM.commit();
  Serial.println("8. yazıldı");
  delay(500);
  EEPROM.write(9, 0);
  EEPROM.commit();
  Serial.println("9. yazıldı");
  delay(500);
  EEPROM.write(10, 1);
  EEPROM.commit();
  Serial.println("10. yazıldı");
  delay(500);
  EEPROM.write(11, 1);
  EEPROM.commit();
  Serial.println("11. yazıldı");
  delay(500);
  EEPROM.write(12, 1);
  EEPROM.commit();
  Serial.println("12. yazıldı");
  delay(500);
  EEPROM.write(13, 1);
  EEPROM.commit();
  Serial.println("13. yazıldı");
  delay(500);
  EEPROM.write(14, 1);
  EEPROM.commit();
  Serial.println("14. yazıldı");
  delay(500);
  EEPROM.write(15, 0);
  EEPROM.commit();
  Serial.println("15. yazıldı");
  delay(500);
  EEPROM.write(16, 0);
  EEPROM.commit();
  Serial.println("16. yazıldı");
  delay(500);
  EEPROM.write(20, 250);
  EEPROM.commit();
  Serial.println("20. yazıldı");
  delay(500);
  EEPROM.write(25, 1250);
  EEPROM.commit();
  Serial.println("25. yazıldı");
  delay(500);
  EEPROM.write(26, 52);
  EEPROM.commit();
  Serial.println("26. yazıldı");
  delay(500);
  EEPROM.write(27, 8);
  EEPROM.commit();
  Serial.println("27. yazıldı");
  delay(500);
}

void loop() {
}
