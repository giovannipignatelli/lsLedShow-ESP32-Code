#include "lsSequence.h"

class lsSequenceTeatherChase : public lsSequence {
  public:

    lsSequenceTeatherChase(int dist) {
      _param1 = dist;
    }

    lsSequenceTeatherChase() {
      _param1 = 2;
    }

    void draw(unsigned long frame) {
      STRIP_CLEAR
      for (int i=0; i < STRIP_NUM_LEDS; i=i+_param1) {
        if(_inBounds(i+SEQUENCE_OFFSET))
          setPixel(i+SEQUENCE_OFFSET,SEQUENCE_PRIMARY_COLOR);// STRIP_LEDS(i+SEQUENCE_OFFSET) = SEQUENCE_PRIMARY_COLOR;
      }
    }

    void update(unsigned long frame) {
      if(INCREASE_SEQUENCE_OFFSET >= 3) {
        RESET_OFFSET
      }      
    }


};