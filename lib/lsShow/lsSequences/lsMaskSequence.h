#include "lsSequence.h"

class lsMaskSequence: public lsSequence {
    
  public:
    
    lsMaskSequence() {
      //this->setFusion(MASK);
    }
    
    CRGB *getLeds() { return nullptr;}

    void render(uint8_t currentFrame) {
      //Serial.println("RENDERIZZO LA MASK");
    }

};