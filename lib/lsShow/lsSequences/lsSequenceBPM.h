#include "lsSequence.h"

class lsSequenceBPM : public lsSequence {
  public:

    uint8_t BeatsPerMinute = 62;
    uint8_t beat;
    uint8_t gHue = 0;

    void draw(unsigned long frame) {
      for( int i = 0; i < this->_Strip->getNumLeds(); i++) { //9948
        this->_Strip->getLeds()[i] = ColorFromPalette(_Palette, gHue+(i*2), beat-gHue+(i*10));
      }
    }

    void update(unsigned long frame) {
      beat = beatsin8( BeatsPerMinute, 64, 255);
    }

    void postRender() {
      gHue = 0;
    }

};
