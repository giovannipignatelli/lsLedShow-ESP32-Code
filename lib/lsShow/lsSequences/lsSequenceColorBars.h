#include "lsSequence.h"

class lsSequenceColorBars : public lsSequence {
  public:

    lsSequenceColorBars(){
      _type = LS_SEQUENCES_TYPES::lsSequenceColorBars;
    }


    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };


    void draw(unsigned long frame) {
      for (uint8_t n=0; n<( STRIP_NUM_LEDS/ (_blockSize*2) )+1; n++) {
        uint8_t pos;
        for (uint8_t i=0; i<_blockSize; i++) {
          pos = (n*_blockSize*2) + i;
          if(_inBounds(pos)) setPixel(pos,SEQUENCE_PRIMARY_COLOR);
          //if ( pos >= STRIP_NUM_LEDS ) { break; }  //don't go past last pixel
          //STRIP_LEDS(pos) = SEQUENCE_PRIMARY_COLOR;

        }
        for (uint8_t i=0; i<_blockSize; i++) {
          pos = (n*_blockSize*2) + i + _blockSize;
          if(_inBounds(pos)) setPixel(pos,SEQUENCE_SECONDARY_COLOR);
          //if ( pos >= STRIP_NUM_LEDS ) { break; }  //don't go past last pixel
          //STRIP_LEDS(pos) = SEQUENCE_SECONDARY_COLOR;
        }
      }
    }

    void update(unsigned long frame) {
      if (frame % 20 == 0) _blockSize = random8(2,9);
    }


};
