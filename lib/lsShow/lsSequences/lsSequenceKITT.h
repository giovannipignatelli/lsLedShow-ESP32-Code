/*
 * Project: Led Show
 * Author: Giovanni Pignatelli
 * License: MIT (Open Source)
 * 
 * Inspirations:
 * - qpQuickPatterns from brimshot https://github.com/brimshot/quickPatterns
 * - atuline https://github.com/atuline/FastLED-Demos
 * - WS2812FX from kitesurfer1404 https://github.com/kitesurfer1404/WS2812FX/tree/master/examples
 * - https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/
 * 
 * Versioning:
 * - v1.0.0: Initial release
 * 
 * To Do:
 * 
 * Description: [Description of what the file does]
 */

#include "lsSequence.h"

class lsSequenceKITT : public lsSequence {
  public:
    int _EyeSize;
    int _SpeedDelay;
    int _ReturnDelay;
    uint8_t position;
    uint8_t gHue = 0;

    lsSequenceKITT(int EyeSize, int SpeedDelay, int ReturnDelay) : _EyeSize(EyeSize) , _SpeedDelay(SpeedDelay),_ReturnDelay(ReturnDelay)  {
    
    }

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };


    void draw(unsigned long frame) {
      STRIP_CLEAR
      CRGB scaledColor = SEQUENCE_PRIMARY_COLOR;
      scaledColor/=10;
      for( int i = 0; i < STRIP_NUM_LEDS; i++) { //9948
        STRIP_LEDS(position) += CHSV( gHue, 255, 192);
      }
    }

/*
void upDown(CRGB Color, int EyeSize, int SpeedDelay, int ReturnDelay, bool reverse) {
  CRGB scaledColor = Color;
  scaledColor/=10;
  int start, pace;
  if (!reverse) {
    start = 0;
    pace = 1;
  }
  else {
    start = NUM_LEDS-EyeSize-2;
    pace = -1;
  }
    for(int i = 0; i < NUM_LEDS-EyeSize-2; i++) {
      clear();
      setPixel(start+(i*pace), scaledColor);
      for(int j = 1; j <= EyeSize; j++) {
        setPixel(start+(i*pace)+j,Color); 
      }
      setPixel(start+(i*pace)+EyeSize+1, scaledColor);
      showStrip();
      delay(SpeedDelay);
    }
  delay(ReturnDelay);
}
*/

    void update(unsigned long frame) {
      this->_Strip->fadeAllToBlack(20);
      position = beatsin16( 13, 0, STRIP_NUM_LEDS-1 );
    }

    void postRender() {
      gHue = 0;
    }

};
