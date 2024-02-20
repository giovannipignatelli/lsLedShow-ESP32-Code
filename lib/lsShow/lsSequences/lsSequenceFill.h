#include "lsSequence.h"

class lsSequenceFill : public lsSequence {
  public:

    void draw(unsigned long frame) {
        (this->*fillLeds)();
        if (this->_isMaskActive) this->applyMask();
    }

    void (lsSequenceFill::*fillLeds)();

    lsSequenceFill &setFill(LS_FILL_TYPES fillType) {
      Serial.println("Hallo");
      switch(fillType) {
        case SOLID:
          this->fillLeds = &lsSequenceFill::fillSolid;
          break;
        case PALETTE:
          this->fillLeds = &lsSequenceFill::fillPalette;
          break;
        case PATTERN:
          this->fillLeds = &lsSequenceFill::fillPattern;
          break;
        case RANDOM:
          this->fillLeds = &lsSequenceFill::fillRandom;
          break;
        case RAINBOW:
          this->fillLeds = &lsSequenceFill::fillRainbow;
          break;
        case RAINBOWCIRCULAR:
          this->fillLeds = &lsSequenceFill::fillRainbowC;
          break;
        case PALETTECIRCULAR:
          this->fillLeds = &lsSequenceFill::fillPaletteC;
          break;
        case GRADIENT:
          this->fillLeds = &lsSequenceFill::fillGradient;
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
