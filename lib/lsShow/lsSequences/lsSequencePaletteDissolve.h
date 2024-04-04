#include "lsSequence.h"

class lsSequencePaletteDissolve : public lsSequence {
  public:



    lsSequencePaletteDissolve(byte speed= 50) {
      _param1 = speed;
      _type = LS_SEQUENCES_TYPES::lsSequencePaletteDissolve;
    }
    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };


    void draw(unsigned long frame) {
      int flowWave = beatsin8(this->_param1/4);
        for(int i = 0; i < STRIP_NUM_LEDS; i++)
          setPixel(i,ColorFromPalette(this->_Palette, (beatsin8(this->_param1) + i), beatsin8(i/2)));
          //STRIP_LEDS(i) = ColorFromPalette(this->_Palette, (beatsin8(this->speed) + i), beatsin8(i/2));
    }

};