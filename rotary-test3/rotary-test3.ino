/*
 * AoE Common Project
 * Mystery, Inc.
 * Does shit
 */

#include <Encoder.h>

#define ledA 2
#define ledB 3
#define rotaryOutputA 4
#define rotaryOutputB 5

long oldPosition = 0;
long newPosition;
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 750; // 750ms before LED transitions

Encoder rotaryEncoder(rotaryOutputA, rotaryOutputB);

void setup() {
      pinMode(ledA,OUTPUT);
      pinMode(ledB,OUTPUT);
      startMillis = millis(); // ms since program started
}


void loop() {
    newPosition = rotaryEncoder.read();
    currentMillis = millis();
    if (newPosition != oldPosition) {
        if (newPosition < oldPosition) {
            digitalWrite(ledB,LOW);
            digitalWrite(ledA,HIGH);
            //rotateCW();
        } else {
            digitalWrite(ledA,LOW);
            digitalWrite(ledB,HIGH);
            //rotateCCW();
        }
        startMillis = currentMillis;
        oldPosition = newPosition;
    }
    if (currentMillis - startMillis >= period) {
        startMillis = currentMillis; 
        digitalWrite(ledA,LOW);
        digitalWrite(ledB,LOW);
        rotaryEncoder.write(0);
    }
}

/*
void rotateCW() {

}

void rotateCCW() {

}
*/
