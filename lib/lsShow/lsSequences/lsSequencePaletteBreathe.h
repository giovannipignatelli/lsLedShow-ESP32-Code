#include "lsSequence.h"

class lsSequencePaletteBreathe : public lsSequence {
  public:

    byte speed;


    lsSequencePaletteBreathe(byte speed) : speed(speed) {}

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };


    void draw(unsigned long frame) {
      int flowWave = beatsin8(this->speed/4);
        for(int i = 0; i < STRIP_NUM_LEDS; i++)
          setPixel(i, ColorFromPalette(this->_Palette, (flowWave +i), beatsin8(this->speed, 30, 255)));
          //STRIP_LEDS(i) = ColorFromPalette(this->_Palette, (flowWave +i), beatsin8(this->speed, 30, 255));
    }

};