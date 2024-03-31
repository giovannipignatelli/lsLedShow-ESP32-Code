#include "lsSequence.h"

class lsSequenceConfetti : public lsSequence {
  public:

    int position = 0;
    CRGB oldColor = CRGB::Black;

    void draw(unsigned long frame) {
      this->_Strip->getLeds()[position] = this->_Color;
    }

    void update(unsigned long frame) {
      position = random16(this->_Strip->getNumLeds()) ;
    }
 
};
