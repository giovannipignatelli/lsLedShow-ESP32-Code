#include "lsSequence.h"

class lsSequencePaletteDissolve : public lsSequence {
  public:

    byte speed;


    lsSequencePaletteDissolve(byte speed) : speed(speed) {}

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };


    void draw(unsigned long frame) {
      int flowWave = beatsin8(this->speed/4);
        for(int i = 0; i < STRIP_NUM_LEDS; i++)
          setPixel(i,ColorFromPalette(this->_Palette, (beatsin8(this->speed) + i), beatsin8(i/2)));
          //STRIP_LEDS(i) = ColorFromPalette(this->_Palette, (beatsin8(this->speed) + i), beatsin8(i/2));
    }

};