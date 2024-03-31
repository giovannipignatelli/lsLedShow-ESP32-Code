#include "lsSequence.h"

class lsSequenceSandWatch : public lsSequence {
  public:

    uint8_t maxPosition;
    bool isFlush = false;

    void preRender(){
      maxPosition = STRIP_NUM_LEDS;
      _Strip->drawColor(SEQUENCE_SECONDARY_COLOR);
      RESET_OFFSET
      isFlush = false;
    }

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };

    void draw(unsigned long frame) {
      // Draw two bars of width size equally offset from either end of our strand
      if (isFlush) {
        this->_Strip->flush(SEQUENCE_SECONDARY_COLOR,1);
        _nextFrameRender += _renderEveryNFrames*5;
      }
      else {
        if(_inBounds( SEQUENCE_OFFSET-1) ) setPixel(SEQUENCE_OFFSET-1,SEQUENCE_SECONDARY_COLOR);
        for(int i = 0; i < _blockSize; i++) {
          setPixel(SEQUENCE_OFFSET+i,SEQUENCE_PRIMARY_COLOR);
        }
      } 
    }

    void update(unsigned long frame) {
      if (!isFlush){
        if (INCREASE_SEQUENCE_OFFSET >= ((maxPosition  ) - this->_blockSize)) {
          maxPosition -= _blockSize;
          RESET_OFFSET
        }
        if (maxPosition <= _blockSize) 
        {
          RESET_OFFSET
          isFlush = true;
        } 
      } else {
        if (INCREASE_SEQUENCE_OFFSET >= STRIP_NUM_LEDS){
          maxPosition = STRIP_NUM_LEDS;
          RESET_OFFSET
          isFlush = false;
          INCREASE_SEQUENCE_RUN;
        }
      }
    }
};
