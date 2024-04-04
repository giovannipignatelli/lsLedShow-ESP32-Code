#include "lsSequence.h"

class lsSequenceSparkle : public lsSequence {

  private:

  int _param1 = 0;
  int _param2 = 0;
  int lastLed = 0;
  bool _isOn = false;

  public:

    lsSequenceSparkle(int SparkleDelay, int SpeedDelay) : _param1(SparkleDelay),_param2(SpeedDelay)  {
      _type = LS_SEQUENCES_TYPES::lsSequenceSparkle;
    }

    lsSequenceSparkle() {
      _type = LS_SEQUENCES_TYPES::lsSequenceSparkle;
    }


    void update(unsigned long frame) {
      //STRIP_LEDS(lastLed) = CRGB::Black;
      setPixel(lastLed,CRGB::Black);
      lastLed = random16(STRIP_NUM_LEDS);
    }


    void draw(unsigned long frame) {     
      if (_isOn) {
        STRIP_LEDS(lastLed)  += SEQUENCE_PRIMARY_COLOR;
        this->_nextFrameRender += _param1;
      }
      else {
        this->_nextFrameRender += _param2;
      } 
      _isOn = !_isOn;
    }



 
};
