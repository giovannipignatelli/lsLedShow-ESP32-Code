#include "lsSequence.h"

class lsFillSequence : public lsSequence {
  public:

    void draw(unsigned long frame) {
        (this->*fillLeds)();
        if (this->_isMaskActive) this->applyMask();
    }

    void (lsFillSequence::*fillLeds)();

    lsFillSequence &setFill(LS_FILL_TYPES fillType) {
      switch(fillType) {
        case SOLID:
          this->fillLeds = &lsFillSequence::fillSolid;
          break;
        case PALETTE:
          this->fillLeds = &lsFillSequence::fillPalette;
          break;
        case PATTERN:
          this->fillLeds = &lsFillSequence::fillPattern;
          break;
        case RANDOM:
          this->fillLeds = &lsFillSequence::fillRandom;
          break;
        case RAINBOW:
          this->fillLeds = &lsFillSequence::fillRainbow;
          break;
        case RAINBOWCIRCULAR:
          this->fillLeds = &lsFillSequence::fillRainbowC;
          break;
        case PALETTECIRCULAR:
          this->fillLeds = &lsFillSequence::fillPaletteC;
          break;
        case GRADIENT:
          this->fillLeds = &lsFillSequence::fillGradient;
          break;
      }
      return *this;   
    } 

    void fillSolid(){ this->_Strip->drawColor(this->_Color);}
    void fillRandom(){ this->_Strip->drawColor(this->getRandomColor()); }
    void fillPalette(){ this->_Strip->drawPalette(this->_Palette, this->_Blending); }
    void fillPaletteC(){ this->_Strip->drawPaletteC(this->_Palette, this->_Blending,this->_reversed); }
    void fillPattern(){ this->_Strip->drawPattern(this->_stripes, this->_stripesSize); }
    void fillRainbow(){ this->_Strip->drawRainbow(this->_initialhue, this->_deltahue); }
    void fillRainbowC(){ this->_Strip->drawRainbowC(this->_initialhue, this->_reversed); }
    void fillGradient(){ this->_Strip->drawGradient(this->_Color,this->_EndColor); }
  
  
};
