#include "lsSequence.h"

class lsSequenceSinelon : public lsSequence {
  public:

    uint8_t position;

    void draw(unsigned long frame) {
      for( int i = 0; i < STRIP_NUM_LEDS; i++) { //9948
        STRIP_LEDS(position) += CHSV( SEQUENCE_HUE, 255, 192);
      }
    }

    void update(unsigned long frame) {
      this->_Strip->fadeAllToBlack(20);
      position = beatsin16( 13, 0, STRIP_NUM_LEDS-1 );
    }


};
