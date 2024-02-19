#include "lsSequence.h"

class lsMovingPoint : public lsSequence {
  public:

    int position = 0;

    void draw(unsigned long frame) {
         this->_Strip->getLeds()[position] = this->_Color;

    }

    void Update(unsigned long frame) {
         position = frame % this->_Strip->getNumLeds();
    }

    lsMovingPoint &setPalette(CRGBPalette16 palette, TBlendType blending) {
      this->_usePalette = true;
      this->_isRandom = false;
      this->_useColor = false;
      this->_Palette = palette;
      this->_Blending = blending;
      return *this;
    }

    lsMovingPoint &setPaletteC(CRGBPalette16 palette, TBlendType blending,bool reversed=false) {
      this->_Palette = palette;
      this->_Blending = blending;
      this->_reversed = reversed;
      return *this;
    }

    lsMovingPoint &setPatternStrip(lsPatternStrip *stripe, uint8_t size) {
      this->_stripes = stripe;
      this->_stripesSize = size;
      return *this;
    }

    lsMovingPoint &setColor(CRGB _Color){
      this->_Color = _Color;
      this->_usePalette = false;
      this->_isRandom = false;
      this->_useColor = true;
      return *this;
    }

    lsMovingPoint &setRainbowHues(uint8_t initialhue, uint8_t deltahue=5) {
      this->_initialhue = initialhue;
      this->_deltahue = deltahue;
      return *this;
    }

    lsMovingPoint &setRainbowCHues(uint8_t initialhue, bool reversed=false) {
      this->_initialhue = initialhue;
      this->_reversed = reversed;
      return *this;
    }

    lsMovingPoint &setGradient(CRGB startcolor, CRGB endcolor) {
      this->_Color = startcolor;
      this->_EndColor = endcolor;
      return *this;
    }
 
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
