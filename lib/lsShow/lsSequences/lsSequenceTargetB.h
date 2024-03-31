#include "lsSequence.h"

// TO DO FIX IT AND CONVERT TARGET A, B C from https://github.com/marmilicious/FastLED_examples 

class lsSequenceTargetB : public lsSequence {
  public:

    uint8_t *target;  // Place to save some target values.
    CHSV    *leds_vu;  // FastLED array using HSV.

    int count;
    int delta;
    int temp;
    int highCutoff = 200;
    int lowCutoff = 30;
    int hueHigh, hueLow;

    lsSequenceTargetB(HSVHue high, HSVHue low): hueHigh(high),hueLow(low) {}

    void preRender(){
      target  = new uint8_t[STRIP_NUM_LEDS];
      leds_vu = new CHSV[STRIP_NUM_LEDS];
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
        if (leds_vu[i].value < target[i]){  // less then the target, so fade up.
          delta = (leds_vu[i].value - target[i]) / 5;
          if (leds_vu[i].value + delta >= target[i]){
            leds_vu[i].value = target[i];  // limit to target.
          }
          else {
            leds_vu[i].value += delta;
          }
        }

        else {  // greater then the target, so fade down.
          delta = ((leds_vu[i].value - target[i])/8) + 1;  // +1 so delta is always at least 1.
          if (leds_vu[i].value - delta <= target[i]){
            leds_vu[i].value = target[i];  // limit to target.
          }
          else {
            leds_vu[i].value -= delta;
          }
        }
        if (i == 0){ temp = delta; }  // Save first pixel's delta number to print below.

        // Tweak hue color based on brightness.
        int c_hue = constrain(leds_vu[i].value,lowCutoff,highCutoff);
        leds_vu[i].hue = map(c_hue, lowCutoff, highCutoff, hueLow, hueHigh);
                      // map(valueIn, fromLow,   fromHigh,   toLow,   toHigh)

        leds_vu[i].saturation = 255;  // Set saturation to full.

        // Copy the HSV leds_vu[] data to the leds[] array.
        STRIP_LEDS(i) = leds_vu[i];
          // FastLED will automatically convert HSV to RGB data.  Converting from HSV
          // to RGB is very fast and also accurate.  It is possible to convert from
          // RGB to HSV, but it is not automatic, not totally acurate, and not as fast.

        // Continously fade target to zero.
        if (target[i] > lowCutoff){
          target[i] -= 2;  // Fade by this ammount.
        }
        else {
          target[i] = 0;  // If target less then lowCutoff, clamp to zero.
        }

      }//end of looping over pixels.

    }

    void update(unsigned long frame) {
      count--;       // Assign random target values whenever count is zero.
      if (count == 0) setTarget();
    }
 
};
