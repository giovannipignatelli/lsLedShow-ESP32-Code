#include "lsSequence.h"

class lsSequenceConfetti : public lsSequence {
  public:

    int position = 0;

    lsSequenceConfetti(){
      _type = LS_SEQUENCES_TYPES::lsSequenceConfetti;
    }

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };


    void draw(unsigned long frame) {
      setPixel(position, SEQUENCE_PRIMARY_COLOR);
      //STRIP_LEDS(position) = SEQUENCE_PRIMARY_COLOR;
    }

    void update(unsigned long frame) {
      position = random16(STRIP_NUM_LEDS) ;
    }
 
};
