RotaryEncoder::RotaryEncoder( int pin_button, int pin_a, int pin_b ) {
	pinA = pin_a;
	pinB = pin_b;
  pinButton = pin_button;
}
void RotaryEncoder::setup()
{
  button = MomentaryButton(pin_button);
  button.setup();
  currentPos = 0;
  maxPos = 24;
  enc_prev_pos = 0;
  enc_flags = 0;
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
  // get an initial reading on the encoder pins
  if (digitalRead(pinA) == LOW) {
    enc_prev_pos |= (1 << 0);
  }
  if (digitalRead(pinB) == LOW) {
    enc_prev_pos |= (1 << 1);
  }
}

void RotaryEncoder::poll() {
  int8_t enc_action = 0; // 1 or -1 if moved, sign is direction
  // note: for better performance, the code will use
  // direct port access techniques
  // http://www.arduino.cc/en/Reference/PortManipulation
  uint8_t enc_cur_pos = 0;
  // read in the encoder state first
  if (bit_is_clear(PIND, pinA)) {
    enc_cur_pos |= (1 << 0);
  }
  if (bit_is_clear(PIND, pinB)) {
    enc_cur_pos |= (1 << 1);
  }
 
  // if any rotation at all
  if (enc_cur_pos != enc_prev_pos)
  {
    if (enc_prev_pos == 0x00)
    {
      // this is the first edge
      if (enc_cur_pos == 0x01) {
        enc_flags |= (1 << 0);
      }
      else if (enc_cur_pos == 0x02) {
        enc_flags |= (1 << 1);
      }
    }
 
    if (enc_cur_pos == 0x03)
    {
      // this is when the encoder is in the middle of a "step"
      enc_flags |= (1 << 4);
    }
    else if (enc_cur_pos == 0x00)
    {
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
 
  functionIndex+=(enc_action+INDEXCLAMP);
  functionIndex%=INDEXCLAMP;
}

void RotaryEncoder::setMaxPos( int max ) {
	maxPos = max;
}

int RotaryEncoder::getCurrentPos() {
	return currentPos;
}
uint8_t RotaryEncoder::isPressed() { return button.isPressed(); }
uint8_t RotaryEncoder::wasPressed() { return button.wasPressed(); }
