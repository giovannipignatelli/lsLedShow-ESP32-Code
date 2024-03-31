#include "lsSequence.h"

class lsSequenceFillUp : public lsSequence {
  public:

    int position=0;

    lsSequenceFillUp(){
      _type = LS_SEQUENCES_TYPES::lsSequenceFillUp;
    }

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };


    void draw(unsigned long frame) {
      setPixel(position,SEQUENCE_PRIMARY_COLOR);
    }

    void update(unsigned long frame) {
      if (position++ == STRIP_NUM_LEDS) {
        position = 0;
        STRIP_CLEAR
      }
    }
      
};
