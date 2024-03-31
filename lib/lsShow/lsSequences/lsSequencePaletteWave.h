#include "lsSequence.h"

class lsSequencePaletteWave : public lsSequence {
  public:

    byte speed;


    lsSequencePaletteWave(byte speed) : speed(speed) {}

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };


    void draw(unsigned long frame) {
        for(int i = 0; i < STRIP_NUM_LEDS; i++)
          setPixel(i,ColorFromPalette(this->_Palette, (beatsin8(this->speed) + i)));
          //STRIP_LEDS(i) = ColorFromPalette(this->_Palette, (beatsin8(this->speed) + i));
    }

};