#include "lsSequence.h"

class lsSequenceSparkles : public lsSequence {
  public:



    lsSequenceSparkles(byte speed= 50) {
       _param1 = speed;
      _type = LS_SEQUENCES_TYPES::lsSequenceSparkles;
    }

    void draw(unsigned long frame) {
      _currentPosition = beatsin8(beatsin8(this->_param1), 0, STRIP_NUM_LEDS);
      setPixel(_currentPosition, SEQUENCE_PRIMARY_COLOR);
      //STRIP_LEDS(pos)  = SEQUENCE_PRIMARY_COLOR;
    }

};