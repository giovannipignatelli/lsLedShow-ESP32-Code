#include "lsSequence.h"

class lsSequencePaletteBreathe : public lsSequence {
  public:



    lsSequencePaletteBreathe(byte speed= 50) {
      _param1 = speed;
      _type = LS_SEQUENCES_TYPES::lsSequencePaletteBreathe;
    }

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };


    void draw(unsigned long frame) {
      int flowWave = beatsin8(this->_param1/4);
        for(int i = 0; i < STRIP_NUM_LEDS; i++)
          setPixel(i, ColorFromPalette(this->_Palette, (flowWave +i), beatsin8(this->_param1, 30, 255)));
          //STRIP_LEDS(i) = ColorFromPalette(this->_Palette, (flowWave +i), beatsin8(this->speed, 30, 255));
    }

};