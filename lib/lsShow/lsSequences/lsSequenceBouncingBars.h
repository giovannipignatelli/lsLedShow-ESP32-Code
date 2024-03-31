#include "lsSequence.h"

class lsSequenceBouncingBars : public lsSequence {
  public:

    lsSequenceBouncingBars(){
      _type = LS_SEQUENCES_TYPES::lsSequenceBouncingBars;
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
        setPixel((STRIP_NUM_LEDS - 1) - (SEQUENCE_OFFSET + i),SEQUENCE_PRIMARY_COLOR);
        //this->_Strip->getLeds()[SEQUENCE_OFFSET+i] = SEQUENCE_PRIMARY_COLOR;
        //this->_Strip->getLeds()[(STRIP_NUM_LEDS - 1) - (SEQUENCE_OFFSET + i)] = SEQUENCE_PRIMARY_COLOR;
      }
    }

    void update(unsigned long frame) {
      if(INCREASE_SEQUENCE_OFFSET >= ((STRIP_NUM_LEDS  - 1) - this->_blockSize)) {
        RESET_OFFSET
      }
    }
 
};
