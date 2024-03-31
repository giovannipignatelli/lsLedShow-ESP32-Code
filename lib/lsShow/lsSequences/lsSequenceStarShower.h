#include "lsSequence.h"

class lsSequenceStarShower : public lsSequence {
  public:

    uint8_t _blockSize = 8;  //number of pixels per section
    uint8_t maxPosition;
    bool isFlush = false;

    void preRender(){
      _blockSize = random8(2,6);
      SEQUENCE_PRIMARY_COLOR = GETRANDOMCOLOR;
      _Strip->drawColor(SEQUENCE_SECONDARY_COLOR);
      RESET_OFFSET
      isFlush = false;
    }

    void draw(unsigned long frame) {
        
      for(int j=0; j<SEQUENCE_OFFSET; j++) {
          STRIP_LEDS(j).fadeToBlackBy(((255/_blockSize+1)) );
      }
      this->_Strip->flush(SEQUENCE_PRIMARY_COLOR,1);
    }

    void update(unsigned long frame) {
      if (INCREASE_SEQUENCE_OFFSET >= this->_blockSize) {
        _blockSize = random8(2,6);
        RESET_OFFSET
        SEQUENCE_PRIMARY_COLOR = GETRANDOMCOLOR;
      }
    }

};
