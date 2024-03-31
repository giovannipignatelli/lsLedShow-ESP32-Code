#include "lsSequence.h"

class lsSequenceGlitter : public lsSequence {

  private:

  int _chanceOfGlitter = 0;
  int lastLed = 0;
  
  public:

    lsSequenceGlitter(fract8 chanceOfGlitter) : _chanceOfGlitter(chanceOfGlitter) {}

    void update(unsigned long frame) {
      this->_Strip->getLeds()[lastLed] = CRGB::Black;
      lastLed = random16(this->_Strip->getNumLeds());
    }


    void draw(unsigned long frame) {
      if( random8() < _chanceOfGlitter) {
        lastLed = random16(this->_Strip->getNumLeds());
        this->_Strip->getLeds()[lastLed]  += this->_Color;
      }
    }



 
};
