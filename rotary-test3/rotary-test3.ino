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
 
static uint8_t enc_prev_pos   = 0;
static uint8_t enc_flags      = 0;
 
void setup() {
  pinMode(ledA,OUTPUT);
  pinMode(ledB,OUTPUT);
  // set pins as input with internal pull-up resistors enabled
  pinMode(rotaryOutputA, INPUT_PULLUP);
  pinMode(rotaryOutputB, INPUT_PULLUP);
  //pinMode(stepPin,OUTPUT); 
 
  // get an initial reading on the encoder pins
  if (digitalRead(rotaryOutputA) == LOW) {
    enc_prev_pos |= (1 << 0);
  }
  if (digitalRead(rotaryOutputB) == LOW) {
    enc_prev_pos |= (1 << 1);
  }
}
 
void loop() {
  int8_t enc_action = 0; // 1 or -1 if moved, sign is direction
 
  // note: for better performance, the code will use
  // direct port access techniques
  // http://www.arduino.cc/en/Reference/PortManipulation
  uint8_t enc_cur_pos = 0;
  // read in the encoder state first
  if (bit_is_clear(TRINKET_PINx, rotaryOutputA)) {
    enc_cur_pos |= (1 << 0);
  }
  if (bit_is_clear(TRINKET_PINx, rotaryOutputB)) {
    enc_cur_pos |= (1 << 1);
  }
 
  // if any rotation at all
  if (enc_cur_pos != enc_prev_pos) {
    if (enc_prev_pos == 0x00) {
      // this is the first edge
      if (enc_cur_pos == 0x01) {
        enc_flags |= (1 << 0);
      }
      else if (enc_cur_pos == 0x02) {
        enc_flags |= (1 << 1);
      }
    }
 
    if (enc_cur_pos == 0x03) {
      // this is when the encoder is in the middle of a "step"
      enc_flags |= (1 << 4);
    }
    else if (enc_cur_pos == 0x00) {
      // this is the final edge
      if (enc_prev_pos == 0x02) {
        enc_flags |= (1 << 2);
      }
      else if (enc_prev_pos == 0x01) {
        enc_flags |= (1 << 3);
      }
 
      // check the first and last edge
      // or maybe one edge is missing, if missing then require the middle state
      // this will reject bounces and false movements
      if (bit_is_set(enc_flags, 0) && (bit_is_set(enc_flags, 2) || bit_is_set(enc_flags, 4))) {
        enc_action = 1;
      }
      else if (bit_is_set(enc_flags, 2) && (bit_is_set(enc_flags, 0) || bit_is_set(enc_flags, 4))) {
        enc_action = 1;
      }
      else if (bit_is_set(enc_flags, 1) && (bit_is_set(enc_flags, 3) || bit_is_set(enc_flags, 4))) {
        enc_action = -1;
      }
      else if (bit_is_set(enc_flags, 3) && (bit_is_set(enc_flags, 1) || bit_is_set(enc_flags, 4))) {
        enc_action = -1;
      }
 
      enc_flags = 0; // reset for next time
    }
  }
 
  enc_prev_pos = enc_cur_pos;
 
  if (enc_action > 0) {
    //rotateCW(); 
  }
  else if (enc_action < 0) {
    //rotateCCW();
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
