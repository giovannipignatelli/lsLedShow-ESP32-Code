#include "lsSequence.h"

class lsSequencePaletteWave : public lsSequence {
  public:

    lsSequencePaletteWave(byte speed){
      _param1 = speed;
      _type = LS_SEQUENCES_TYPES::lsSequencePaletteWave;
    }

    lsSequencePaletteWave() {
      _param1 = 50;
      _type = LS_SEQUENCES_TYPES::lsSequencePaletteWave;
    }    

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };


    void draw(unsigned long frame) {
        for(int i = 0; i < STRIP_NUM_LEDS; i++)
          setPixel(i,ColorFromPalette(this->_Palette, (beatsin8(this->_param1) + i)));
          //STRIP_LEDS(i) = ColorFromPalette(this->_Palette, (beatsin8(this->speed) + i));
    }

};