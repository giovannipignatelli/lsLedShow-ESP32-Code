#include "lsSequence.h"

class lsSequenceElectricity : public lsSequence {
  public:

    lsSequenceElectricity(){
      _type = LS_SEQUENCES_TYPES::lsSequenceElectricity;
    }


    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };

    void draw(unsigned long frame) {
      for( int i = 0; i < 8; i++)
        setPixel(beatsin16(i, 0, STRIP_NUM_LEDS - 1), ColorFromPalette(this->_Palette, beatsin8(5)));
        //STRIP_LEDS(beatsin16(i, 0, STRIP_NUM_LEDS - 1)) = ColorFromPalette(this->_Palette, beatsin8(5));
    }
 
};
