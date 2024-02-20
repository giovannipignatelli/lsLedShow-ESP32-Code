#include "lsSequence.h"

class lsFilterBlurSequence : public lsSequence{
    
  public:
    
    lsFilterBlurSequence(fract8 blur_amount) {
      this->_blur_amount = blur_amount;
    }
    
    CRGB *getLeds() { return nullptr;}

    void render(uint8_t currentFrame) {
      Serial.println("RENDERIZZO LA MASK");
    }

    void merge(CRGB *targetLayer, int size){
      Serial.println("MEREGE LA MASK");
      blur1d(targetLayer,size,this->_blur_amount);
      Serial.println("FINE MEREGE LA MASK");
    }

  private:
    fract8 	_blur_amount;

};