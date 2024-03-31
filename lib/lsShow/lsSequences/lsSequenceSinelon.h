#include "lsSequence.h"

class lsSequenceSinelon : public lsSequence {
  public:

    uint8_t position;

    void draw(unsigned long frame) {
      for( int i = 0; i < this->_Strip->getNumLeds(); i++) { //9948
        this->_Strip->getLeds()[position] += CHSV( gHue, 255, 192);
      }
    }

    void update(unsigned long frame) {
      this->_Strip->fadeAllToBlack(20);
      position = beatsin16( 13, 0, this->_Strip->getNumLeds()-1 );
    }


};
