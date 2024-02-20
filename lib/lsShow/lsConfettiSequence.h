#include "lsSequence.h"

class lsConfettiSequence : public lsSequence {
  public:

    int position = 0;
    CRGB oldColor = CRGB::Black;

    void draw(unsigned long frame) {
      Serial.println("Ciao");
      if (!_usePalette) this->_Strip->getLeds()[position]  += CHSV( gHue + random8(64), 200, 255);
      else this->_Strip->getLeds()[position] = ColorFromPalette(_Palette, gHue + random16(64) , 255, _Blending);
    }

    void update(unsigned long frame) {
         position = random16(this->_Strip->getNumLeds()) ;
         gHue++;
    }

 
};
