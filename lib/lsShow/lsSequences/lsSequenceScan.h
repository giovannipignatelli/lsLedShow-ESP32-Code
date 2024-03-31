#include "lsSequence.h"

class lsSequenceScan : public lsSequence {
  public:

    int position = 0;
    CRGB oldColor = CRGB::Black;

    void draw(unsigned long frame) {
      if (position > 0 ) STRIP_LEDS(position-1) = oldColor;
        oldColor = STRIP_LEDS(position);
        setPixel(position,SEQUENCE_PRIMARY_COLOR);
        //STRIP_LEDS(position) = SEQUENCE_PRIMARY_COLOR;
    }

    void update(unsigned long frame) {
        
         position++;
         if (position>STRIP_NUM_LEDS) position -= STRIP_NUM_LEDS;
    }


};
