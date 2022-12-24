
//USB HID Key codes
//https://gist.github.com/MightyPork/6da26e382a7ad91b5496ee55fdc73db2

//USB Library
//https://github.com/chegewara/EspTinyUSB
#include "Arduino.h"
#include "hidcomposite.h"
#include "OneButton.h"
#include "Encoder.h"
#include "stdlib.h"

//My header files
#include "click_handlers.h"
#include "defines.h"

OneButton pause_button(PAUSE_BUTTON_PIN, true, true);
OneButton ff_button(FF_BUTTON_PIN, true, true);
OneButton rw_button(RW_BUTTON_PIN, true, true);
OneButton enc_button(ENCODER_CLICK_PIN, true, true);

Encoder knob(ENCODER_A_PIN, ENCODER_B_PIN);

HIDcomposite dev;

int msg[11] = {104, 101, 108,108,111,32,119,111,114,108,100}; //hello world

long pos = 0;
long abs_pos = 0;
int timer = 0;
int knob_timer=0;

void setup()
{
  pinMode(SWITCH_PIN,INPUT_PULLUP);
  // link the button 1 functions.
  pause_button.attachClick(pause_click_f, &dev);
  // button1.attachDoubleClick(doubleclick1);
  // button1.attachLongPressStart(longPressStart1);
  // button1.attachLongPressStop(longPressStop1);
  // button1.attachDuringLongPress(longPress1);

  // link the button 2 functions.
  ff_button.attachClick(ff_click_f, &dev);
  // button2.attachDoubleClick(doubleclick2);
  // button2.attachLongPressStart(longPressStart2);
  // button2.attachLongPressStop(longPressStop2);
  // button2.attachDuringLongPress(longPress2);

  // link the button 2 functions.
  rw_button.attachClick(rw_click_f, &dev);
  // button2.attachDoubleClick(doubleclick2);
  // button2.attachLongPressStart(longPressStart2);
  // button2.attachLongPressStop(longPressStop2);
  // button2.attachDuringLongPress(longPress2);

  // link the button 2 functions.
  enc_button.attachClick(enc_click_f, &dev);
  // button2.attachDoubleClick(doubleclick2);
  // button2.attachLongPressStart(longPressStart2);
  // button2.attachLongPressStop(longPressStop2);
  // button2.attachDuringLongPress(longPress2);

  dev.begin();
}

void loop()
{
  timer = millis();

  pause_button.tick();
  ff_button.tick();
  rw_button.tick();
  enc_button.tick();

  if ( (timer-knob_timer) > 75 ) {
    pos = knob.readAndReset()/3;

    if (pos !=0){
      abs_pos = min(std::abs(pos)/2, (long) 1);
      for (int i = 0; i<=abs_pos; i++){
        if (pos > 0){
          dev.sendKey(KEY_MEDIA_VOLUMEDOWN);
          delay(1);
        }
        if (pos < 0){
          dev.sendKey(KEY_MEDIA_VOLUMEUP);
          delay(1);
        }

      }
    }
    knob_timer = millis();
  }
}

