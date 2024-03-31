#include "lsSequence.h"

class lsSequenceTeatherChase : public lsSequence {
  public:

    int distance = 2;

    lsSequenceTeatherChase(int dist): distance(dist) {}

    void draw(unsigned long frame) {
      STRIP_CLEAR
      for (int i=0; i < STRIP_NUM_LEDS; i=i+distance) {
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