#include "lsSequence.h"

class lsSequenceJuggle : public lsSequence {


  public:

    lsSequenceJuggle(){
      _type = LS_SEQUENCES_TYPES::lsSequenceJuggle;
    }

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };

    void draw(unsigned long frame) {
      for( int i = 0; i < 8; i++)
        setPixel(beatsin16(i+7, 0, STRIP_NUM_LEDS - 1),SEQUENCE_PRIMARY_COLOR);
        //STRIP_LEDS(beatsin16(i+7, 0, STRIP_NUM_LEDS - 1)) = SEQUENCE_PRIMARY_COLOR;
    }



 
};
