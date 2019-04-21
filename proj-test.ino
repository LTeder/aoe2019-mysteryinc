/*
 * AoE Common Project
 * Mystery, Inc.
 * Does shit
 */
 
#define ledA 2
#define ledB 3
#define rotaryOutputA 4
#define rotaryOutputB 5
//#define stepPin 8 

int rotaryState;
int rotaryLastState;  
 
void setup() {
    pinMode(ledA,OUTPUT);
    pinMode(ledB,OUTPUT);
    pinMode(rotaryOutputA,INPUT);
    pinMode(rotaryOutputB,INPUT);
    //pinMode(stepPin,OUTPUT); 
    rotaryLastState = digitalRead(rotaryOutputA);
}

void loop() {
    rotaryState = digitalRead(rotaryOutputA);
    if (rotaryState != rotaryLastState) {     
        if (digitalRead(rotaryOutputB) != rotaryState) {
            digitalWrite(ledA,HIGH);
            //rotateCW();  
        } else {
            digitalWrite(ledB,HIGH);
            //rotateCCW(); 
        }
    }
    digitalWrite(ledA,LOW);
    digitalWrite(ledB,LOW);
    rotaryLastState = rotaryState;
}

/*
void rotateCW() {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(2000); 
}

void rotateCCW() {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(2000);   
}
*/
