#include "lsSequence.h"

class lsSequenceGlitter : public lsSequence {

  private:

  int _chanceOfGlitter = 0;
  int lastLed = 0;
  
  public:

    lsSequenceGlitter(fract8 chanceOfGlitter) : _chanceOfGlitter(chanceOfGlitter) {
      _type=LS_SEQUENCES_TYPES::lsSequenceGlitter;
    }

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };


    void update(unsigned long frame) {
      //STRIP_LEDS(lastLed) = CRGB::Black;
      setPixel(lastLed,CRGB::Black);
      lastLed = random16(STRIP_NUM_LEDS);
    }


    void draw(unsigned long frame) {
      if( random8() < _chanceOfGlitter) {
        lastLed = random16(STRIP_NUM_LEDS);
        STRIP_LEDS(lastLed) += SEQUENCE_PRIMARY_COLOR;
      }
    }



 
};
