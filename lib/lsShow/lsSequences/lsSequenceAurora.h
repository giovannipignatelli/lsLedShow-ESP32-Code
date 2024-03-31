#include "lsSequence.h"

class lsSequenceAurora : public lsSequence {
  public:

    uint8_t maxPosition;
    bool isFlush = false;

    lsSequenceAurora(){
      _type = LS_SEQUENCES_TYPES::lsSequenceAurora;
    }

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };

    void preRender(){
      _blockSize = random8(2,6);
      SEQUENCE_PRIMARY_COLOR = GETRANDOMCOLOR;
      _Strip->drawColor(SEQUENCE_SECONDARY_COLOR);
      RESET_OFFSET
      isFlush = false;
    }

    void draw(unsigned long frame) {
        STRIP_LEDS(1).fadeToBlackBy( SEQUENCE_OFFSET*(255/_blockSize)*SEQUENCE_OFFSET );

      // Draw two bars of width size equally offset from either end of our strand
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
