#include "lsSequence.h"

class lsSequenceBouncingBar : public lsSequence {
  public:


    lsSequenceBouncingBar(){
      _type = LS_SEQUENCES_TYPES::lsSequenceBouncingBar;
    }

    void preRender(){
      RESET_OFFSET
    }

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };


    void draw(unsigned long frame) {

      // Black out previous pixels before drawing the next frame
      STRIP_CLEAR



      // Draw two bars of width size equally offset from either end of our strand
      for(int i = 0; i < this->_blockSize; i++) {
        setPixel(SEQUENCE_OFFSET+i,SEQUENCE_PRIMARY_COLOR);
        //if (_isReversed) this->_Strip->getLeds()[(STRIP_NUM_LEDS - 1) - (SEQUENCE_OFFSET + i)] = SEQUENCE_PRIMARY_COLOR;
        //else this->_Strip->getLeds()[SEQUENCE_OFFSET+i] = SEQUENCE_PRIMARY_COLOR;
      }

    }

    void update(unsigned long frame) {
      if (INCREASE_SEQUENCE_OFFSET >= ((STRIP_NUM_LEDS  - 1) - this->_blockSize)) {
        _isReversed = !_isReversed;
        RESET_OFFSET
      }
    }
 
};
