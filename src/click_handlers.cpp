#include "hidcomposite.h"
// #include "OneButton.h"
#include "click_handlers.h"
#include "defines.h"

void pause_click_f(void * pvdev){
  HIDcomposite dev = *(HIDcomposite*)pvdev;
  dev.sendKey(KEY_MEDIA_PLAYPAUSE);
}

void ff_click_f(void * pvdev){
  HIDcomposite dev = *(HIDcomposite*)pvdev;
  dev.sendKey(KEY_MEDIA_NEXTSONG);
}

void rw_click_f(void * pvdev){
  HIDcomposite dev = *(HIDcomposite*)pvdev;
  dev.sendKey(KEY_MEDIA_PREVIOUSSONG);
}

void enc_click_f(void * pvdev){
  HIDcomposite dev = *(HIDcomposite*)pvdev;
  dev.sendKey(KEY_MEDIA_MUTE);
}