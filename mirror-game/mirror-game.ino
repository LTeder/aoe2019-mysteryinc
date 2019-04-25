/*
 * AoE Common Project
 * Mystery, Inc.
 * Runs the full mirror game
 */

#include <Encoder.h>

#define rotaryOutputA 2
#define rotaryOutputB 3
#define ledA 4
#define ledB 5

long oldPosition = 0;
long newPosition;
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 250; // 750ms before LED transitions

Encoder rotaryEncoder(rotaryOutputA, rotaryOutputB);

void setup() {
      pinMode(ledA,OUTPUT);
      pinMode(ledB,OUTPUT);
      startMillis = millis(); // ms since program started
}


void loop() {
    newPosition = rotaryEncoder.read();
    currentMillis = millis();
    if (newPosition < oldPosition) {
        digitalWrite(ledB,LOW);
        digitalWrite(ledA,HIGH);
        updateEnc();
        //rotateCW();
    } else if (newPosition > oldPosition) {
        digitalWrite(ledA,LOW);
        digitalWrite(ledB,HIGH);
        updateEnc();
        //rotateCCW();
    }
    if (currentMillis - startMillis >= period) {
        digitalWrite(ledA,LOW);
        digitalWrite(ledB,LOW);
        updateEnc();
    }
}

void updateEnc() {
    startMillis = currentMillis;
    oldPosition = newPosition;
}

/*
void rotateCW() {

}

void rotateCCW() {

}
*/
