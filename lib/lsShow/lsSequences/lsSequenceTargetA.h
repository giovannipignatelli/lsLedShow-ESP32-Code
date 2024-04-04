#include "lsSequence.h"

// TO DO FIX IT AND CONVERT TARGET A, B C from https://github.com/marmilicious/FastLED_examples 

class lsSequenceTargetA : public lsSequence {
  public:

    uint8_t *target;  // Place to save some target values.
    int count = 0;
    int delta;
    int temp;
    int lowCutoff = 50;

    lsSequenceTargetA(LS_FILTER channel) {
      _channel = channel;
      _type = LS_SEQUENCES_TYPES::lsSequenceTargetA;
    }

    lsSequenceTargetA() {
      _type = LS_SEQUENCES_TYPES::lsSequenceTargetA;
    }

    void preRender(){
      target = new uint8_t[STRIP_NUM_LEDS];
      setTarget();
    }

    void setTarget(){
      STRIP_CLEAR
      for (int i=0; i < STRIP_NUM_LEDS; i++){
        target[random8(STRIP_NUM_LEDS)] = random8();  // Pick random pixels, assign random values.
        if (target[i] < lowCutoff){
          target[i] = 0;  // Force low values to clamp to zero.
        }
      }
      count = random8(35,70);  // Pick a new count value.  
      
    }

    void draw(unsigned long frame) {

      for (int i=0; i < STRIP_NUM_LEDS; i++){
        // Check current values against target values.
        switch (_channel) {
          case LS_FILTER::RED:
              if (STRIP_LEDS(i).r < target[i]){  // less then the target, so fade up.
                delta = (target[i] - STRIP_LEDS(i).r) / 5;
                if (STRIP_LEDS(i).r + delta >= target[i]){
                  STRIP_LEDS(i).r = target[i];  // limit to target.
                } else { STRIP_LEDS(i).r += delta; }
              }
              else {  // greater then the target, so fade down.
                delta = ((STRIP_LEDS(i).r - target[i])/8) + 1;  // +1 so delta is always at least 1.
                if (STRIP_LEDS(i).r - delta <= target[i]){
                  STRIP_LEDS(i).r = target[i];  // limit to target.
                }
                else { STRIP_LEDS(i).r -= delta; }
              }
            break;
          case LS_FILTER::GREEN:
              if (STRIP_LEDS(i).g < target[i]){  // less then the target, so fade up.
                delta = (target[i] - STRIP_LEDS(i).g) / 5;
                if (STRIP_LEDS(i).g + delta >= target[i]){
                  STRIP_LEDS(i).g = target[i];  // limit to target.
                } else { STRIP_LEDS(i).g += delta; }
              }
              else {  // greater then the target, so fade down.
                delta = ((STRIP_LEDS(i).g - target[i])/8) + 1;  // +1 so delta is always at least 1.
                if (STRIP_LEDS(i).g - delta <= target[i]){
                  STRIP_LEDS(i).g = target[i];  // limit to target.
                }
                else { STRIP_LEDS(i).g -= delta; }
              }
            break;
          case LS_FILTER::BLUE:
              if (STRIP_LEDS(i).b < target[i]){  // less then the target, so fade up.
                delta = (target[i] - STRIP_LEDS(i).b) / 5;
                if (STRIP_LEDS(i).b + delta >= target[i]){
                  STRIP_LEDS(i).b = target[i];  // limit to target.
                } else { STRIP_LEDS(i).b += delta; }
              }
              else {  // greater then the target, so fade down.
                delta = ((STRIP_LEDS(i).b - target[i])/8) + 1;  // +1 so delta is always at least 1.
                if (STRIP_LEDS(i).b - delta <= target[i]){
                  STRIP_LEDS(i).b = target[i];  // limit to target.
                }
                else { STRIP_LEDS(i).b -= delta; }
              }
            break;
        }
        if (i == 0){ temp = delta; }  // Save first pixel's delta number to print below.
        // Continously fade target to zero.
        if (target[i] > lowCutoff){
          target[i] -= 2;  // Fade by this ammount.
        }
        else { target[i] = 0; }  // If target is less then lowCutoff, clamp to zero.

      }//end of looping over pixels.

    }

    void update(unsigned long frame) {
      count--;       // Assign random target values whenever count is zero.
      if (count == 0) setTarget();
    }
 
};
