#include "lsSequence.h"

class lsSequenceConfetti : public lsSequence {
  public:

    int position = 0;
    CRGB oldColor = CRGB::Black;

    void draw(unsigned long frame) {
      switch (this->_Coloring){
        case (LS_SEQUENCE_COLORING::SOLIDCOLOR):{
          this->_Strip->getLeds()[position] = this->_Color;
          break;
        }
        case (LS_SEQUENCE_COLORING::RANDOMCOLOR):{
          this->_Strip->getLeds()[position] = ColorFromPalette(_Palette, gHue + random16(64) , 255, _Blending);

          break;
        }
        case (LS_SEQUENCE_COLORING::PALETTECOLOR):{
          this->_Strip->getLeds()[position]  += CHSV( gHue + random8(64), 200, 255);
          break;
        }
      }
    }

    void update(unsigned long frame) {
         position = random16(this->_Strip->getNumLeds()) ;
         gHue++;
    }

 
};
