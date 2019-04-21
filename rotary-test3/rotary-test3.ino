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

Encoder myEnc(rotaryOutputA, rotaryOutputB);

void setup() {
      pinMode(ledA,OUTPUT);
      pinMode(ledB,OUTPUT);
}

long oldPosition  = -999;

void loop() {
    long newPosition = myEnc.read();
    if (newPosition != oldPosition) {
        if (newPosition > oldPosition) {
            digitalWrite(ledB,HIGH);
            //rotateCCW();
        } else {
            digitalWrite(ledA,HIGH);
            //rotateCW();
        }
        oldPosition = newPosition;
    }
    digitalWrite(ledA,LOW);
    digitalWrite(ledB,LOW);
}

/*
void rotateCW() {

}

void rotateCCW() {

}
*/
