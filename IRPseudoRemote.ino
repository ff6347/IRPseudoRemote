/**
 *
 * IRPseudo Remote.
 * So you bought that shiny Apple Remote and learnd at home that
 * your shiny MacBook Air has no IR reciever?
 *
 * Luckily you can build something like it yourself.
 * Use the Sparkfun Arduino Pro Micro
 * https://www.sparkfun.com/products/12640
 *
 * and an IR reciever
 * I used this Sparkfun Breakout Board
 * https://www.sparkfun.com/products/8554
 *
 * get the Arduino IRRemote Library
 *
 * https://github.com/shirriff/Arduino-IRremote
 *
 *
 * based on
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 *
 * See also this stackoverflow
 * http://stackoverflow.com/questions/15113128/ir-hex-comparison
 *
 */

#include <IRremote.h>

int RECV_PIN = 3;// digital in pin

IRrecv irrecv(RECV_PIN);

decode_results results;

// the keys we use for now
char upKey = KEY_UP_ARROW;
char downKey = KEY_DOWN_ARROW;
char leftKey = KEY_LEFT_ARROW;
char rightKey = KEY_RIGHT_ARROW;

void setup(){
  Serial.begin(9600); // just for testing
  Keyboard.begin(); // init keyboard
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {

  if (irrecv.decode(&results)) {
    //if we get seomthing displa it
    Serial.println(results.value, HEX);


    if(results.value == 0x77E1B07E){
      // Down
      press_release_key(downKey, "DOWN");
    }
    else if(results.value == 0x77E1D07E){
      // Up
      press_release_key(upKey, "UP");
    }
    else if(results.value == 0x77E1107E){
      // left
      press_release_key(leftKey, "LEFT");
    }
    else if(results.value == 0x77E1E07E){
      // right
      press_release_key(rightKey, "RIGHT");
    }

    Serial.println("-");
    irrecv.resume(); // Receive the next value
  }
}

void press_release_key(char key, String msg){
  Serial.println(msg);
  Keyboard.press(key);
  delay(100);
  Keyboard.releaseAll();
}

