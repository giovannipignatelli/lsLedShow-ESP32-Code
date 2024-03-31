#include "lsSequence.h"

class lsFilterRGBSequence : public lsSequence{
    
  public:
    
    lsFilterRGBSequence(LS_FILTER filter){
      this->setFilter(filter);
    }
    
    CRGB *getLeds() { return nullptr;}

    void render(uint8_t currentFrame) {
      //Serial.println("RENDERIZZO LA MASK");
    }

    lsFilterRGBSequence &setFilter(LS_FILTER filter){
      this->_filter = filter;
      switch(_filter) {
        case RED:
          this->_colorMask = CRGB(0,255,255);
          break;
        case GREEN:
          this->_colorMask = CRGB(255,0,255);
          break;
        case BLUE:
          this->_colorMask = CRGB(255,255,0);
          break;
      }
      return *this;
    }

    void merge(CRGB *targetLayer, int size){
      fadeUsingColor(targetLayer,size,this->_colorMask);
    }

  private:
    LS_FILTER _filter;
    CRGB _colorMask;

};
