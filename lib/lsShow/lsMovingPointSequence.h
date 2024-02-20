#include "lsSequence.h"

class lsMovingPointSequence : public lsSequence {
  public:

    int position = 0;
    CRGB oldColor = CRGB::Black;

    void draw(unsigned long frame) {
      if (position > 0 ) this->_Strip->getLeds()[position-1] = oldColor;
        oldColor = this->_Strip->getLeds()[position];
        this->_Strip->getLeds()[position] = this->_Color;
    }

    void update(unsigned long frame) {
         position = frame % this->_Strip->getNumLeds();
         if (position>this->_Strip->getNumLeds()) position -= this->_Strip->getNumLeds();
    }


};
