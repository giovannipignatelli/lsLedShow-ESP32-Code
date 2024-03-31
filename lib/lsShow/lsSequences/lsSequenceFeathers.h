#include "lsSequence.h"

// TO MODIFY, rigth now is useless

class lsSequenceFeathers : public lsSequence {
  public:

    int direction;
    int startPos = 0;

    lsSequenceFeathers(int size, int direction = 1) : direction(direction) {
    
    }

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };


    void preRender() {
      this->startPos = (this->direction == 1? 0:STRIP_NUM_LEDS);
    }

    void postRender() {
      this->startPos = (this->direction == 1? 0:STRIP_NUM_LEDS);
    }

    void draw(unsigned long frame) {
      for(int i = 0; i < this->_blockSize; i++) {
        if(_inBounds(this->startPos + (this->direction*i)))
          STRIP_LEDS(this->startPos + (this->direction*i)) = SEQUENCE_PRIMARY_COLOR;
      }
    }
 
    void update(unsigned long frame) {
      this->startPos += ((this->_blockSize*0.75)*this->direction);
      if(! _inBounds(this->startPos)) {
        this->startPos = (this->direction == 1? 0:STRIP_NUM_LEDS);
      }
    }

};




