/*
 * AoE Common Project
 * Mystery, Inc.
 * Does shit
 */

#include <Encoder.h>

#define rotaryOutputA 4
#define rotaryOutputB 5

Encoder myEnc(rotaryOutputA, rotaryOutputB);

void setup() {
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
}

long oldPosition  = -999;

void loop() {
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
  }
}
