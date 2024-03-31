#include "lsSequence.h"

class lsSequenceSweep : public lsSequence {
  public:

    int position=0;

    void draw(unsigned long frame) {
      setPixel(position, SEQUENCE_PRIMARY_COLOR);
      if (position >0) setPixel(position-1, !_isReversed ? SEQUENCE_SECONDARY_COLOR : SEQUENCE_TERTIARY_COLOR);
    }

    void update(unsigned long frame) {
      if (position++ == STRIP_NUM_LEDS) {
        position = 0;
        _isReversed = !_isReversed;
      }
    }
      
};
