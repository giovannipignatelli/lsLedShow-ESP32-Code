#include "lsSequence.h"

class lsSequenceSparkles : public lsSequence {
  public:

    byte speed;


    lsSequenceSparkles(byte speed) : speed(speed) {}

    void draw(unsigned long frame) {
      int pos = beatsin8(beatsin8(this->speed), 0, STRIP_NUM_LEDS);
      setPixel(pos, SEQUENCE_PRIMARY_COLOR);
      //STRIP_LEDS(pos)  = SEQUENCE_PRIMARY_COLOR;
    }

};