#include "lsSequence.h"

class lsSequenceWipe : public lsSequence {
  public:

    int position=0;
    bool isPrimaryColor = true; 

    void preRender(){
      position = 0;
      isPrimaryColor = true; 
    }

    void draw(unsigned long frame) {
        setPixel(position,isPrimaryColor ? SEQUENCE_PRIMARY_COLOR : SEQUENCE_SECONDARY_COLOR);
    }

    void update(unsigned long frame) {
      if (position++ == STRIP_NUM_LEDS) { position = 0; isPrimaryColor = !isPrimaryColor;}
    }

};
