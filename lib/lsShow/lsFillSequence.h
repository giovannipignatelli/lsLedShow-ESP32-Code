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

    lsFillSequence &setPalette(CRGBPalette16 palette, TBlendType blending) {
      this->_usePalette = true;
      this->_isRandom = false;
      this->_useColor = false;
      this->_Palette = palette;
      this->_Blending = blending;
      return *this;
    }

    lsFillSequence &setPaletteC(CRGBPalette16 palette, TBlendType blending,bool reversed=false) {
      this->_Palette = palette;
      this->_Blending = blending;
      this->_reversed = reversed;
      return *this;
    }

    lsFillSequence &setPatternStrip(lsPatternStrip *stripe, uint8_t size) {
      this->_stripes = stripe;
      this->_stripesSize = size;
      return *this;
    }

    lsFillSequence &setColor(CRGB _Color){
      this->_Color = _Color;
      this->_usePalette = false;
      this->_isRandom = false;
      this->_useColor = true;
      return *this;
    }

    lsFillSequence &setRainbowHues(uint8_t initialhue, uint8_t deltahue=5) {
      this->_initialhue = initialhue;
      this->_deltahue = deltahue;
      return *this;
    }

    lsFillSequence &setRainbowCHues(uint8_t initialhue, bool reversed=false) {
      this->_initialhue = initialhue;
      this->_reversed = reversed;
      return *this;
    }

    lsFillSequence &setGradient(CRGB startcolor, CRGB endcolor) {
      this->_Color = startcolor;
      this->_EndColor = endcolor;
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
    

  private:

    CRGB getRandomColor(){ return ColorFromPalette( RainbowColors_p, random16(255), 180, LINEARBLEND); }

    CRGB _Color,_EndColor;
    CRGBPalette16 _Palette;
    TBlendType    _Blending;
    lsPatternStrip *_stripes;
    uint8_t   _stripesSize;
    uint8_t _initialhue;
    uint8_t _deltahue;
    bool _reversed;
  
};
