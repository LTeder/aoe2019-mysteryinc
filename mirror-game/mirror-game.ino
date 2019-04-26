/*
   AoE Common Project
   Mystery, Inc.
   Runs the full mirror game
*/
#include <AFMotor.h>
#include <Encoder.h>
#include <Servo.h>
#include <Bounce2.h>
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>


#define rotaryOutputA 2
#define rotaryOutputB 3
#define ledA 4
#define ledB 5
#define receptor A0
#define laserPin 9
#define receptorMotorPin 10
#define CALIB 0
#define READY 1
#define GAME 2
#define startButton 11
#define toggleButton 12


long oldPosition = 0;
Adafruit_7segment matrix = Adafruit_7segment();
long newPosition;
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 100; // 750ms before LED transitions
int total;
int n;
int threshold;
float coef = .7;
int state;
boolean forMirror;
unsigned long gameStart;
int gameLen = 30;
int prevStartButton = HIGH;
int prevToggleButton = HIGH;
boolean CW = false;
boolean CCW = false;

Bounce bstartButton = Bounce();
Bounce btoggleButton = Bounce();


Servo laserMotor;
Servo receptorMotor;

Encoder rotaryEncoder(rotaryOutputA, rotaryOutputB);

void setup() {
  matrix.begin(0x70);
  Serial.begin(9600);
  state = CALIB;
  //SAY CALIB

  pinMode(startButton, INPUT_PULLUP);
  bstartButton.attach(startButton);
  bstartButton.interval(5);

  pinMode(toggleButton, INPUT_PULLUP);
  btoggleButton.attach(toggleButton);
  btoggleButton.interval(5);


  //turn off laser
  laserMotor.attach(laserPin);
  receptorMotor.attach(receptorMotorPin);
  laserMotor.write(89);
  receptorMotor.write(89);
  pinMode(ledA, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(receptor, INPUT_PULLUP);
  startMillis = millis(); // ms since program started
  Serial.begin(9600);
  for (int i = 0; i < 50; i++) {
    total += analogRead(receptor);
    n++;
  }
  threshold = coef * total / n;
  state = READY;
}


void loop() {

  bstartButton.update();
  btoggleButton.update();
  //  Serial.println("YO");
  //  Serial.println(bstartButton.read());
  if (state == READY) {
    //    Serial.println("READY");
    if (bstartButton.read() == LOW) {
      //      Serial.println("NEW GAME");
      int randomSpeed = random(180);
      for (int i = 0; i < random(200, 400); i++) {
        Serial.println("TURN");
        receptorMotor.write(randomSpeed);
        forMirror = false;
      }
      receptorMotor.write(89);
      gameStart = millis();
      //      digitalWrite(ledA, HIGH);
      state = GAME;
    }
  }
  else if (state == GAME) {
    int timeLeft = gameLen - (int)((millis() - gameStart ) / 1000);
    if (timeLeft > 0) {
      matrix.print(timeLeft);
      matrix.writeDisplay();
      Serial.println(timeLeft);
    }
    else {
      matrix.print(0);
      matrix.writeDisplay();
      //      Serial.println("UYUYUYUYUY");
      state = READY;
    }
    if ((bstartButton.read() == LOW && prevStartButton == HIGH)) {
      Serial.println("ON LAZER");
      state = READY;
    }

    if (analogRead(receptor) < threshold) {
      matrix.print(9999);
      matrix.writeDisplay();
      state = READY;
    }
    if (prevToggleButton == HIGH && btoggleButton.read() == LOW) {
      forMirror = !forMirror;
    }
    newPosition = rotaryEncoder.read();
    currentMillis = millis();
    if (newPosition < oldPosition) {
      digitalWrite(ledB, LOW);
      digitalWrite(ledA, HIGH);
      updateEnc();
      //rotateCW();
      CCW = true;
    }
    else if (newPosition > oldPosition) {
      digitalWrite(ledA, LOW);
      digitalWrite(ledB, HIGH);
      updateEnc();
      CW = true;
      //rotateCCW();
    }
    if (currentMillis - startMillis >= period) {
      digitalWrite(ledA, LOW);
      digitalWrite(ledB, LOW);
      CW = false;
      CCW = false;
      updateEnc();
    }
    if (CW) {
      if (forMirror) {
        //idk mirror
        laserMotor.write(89);
      } else {
        //idk mirror
        laserMotor.write(180);
      }
    } else if (CCW) {
      if (forMirror) {
        //idk mirror
        laserMotor.write(89);
      } else {
        //idk mirror
        laserMotor.write(0);
      }
    } else {
      //idk mirror
      laserMotor.write(89);
    }
  }
  prevStartButton = bstartButton.read();
  prevToggleButton = btoggleButton.read();
}

void updateEnc() {
  startMillis = currentMillis;
  oldPosition = newPosition;
}
