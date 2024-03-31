#include "lsSequence.h"

class lsSequenceSparkle : public lsSequence {

  private:

  int _SparkleDelay = 0;
  int _SpeedDelay = 0;
  int lastLed = 0;
  bool _isOn = false;

  public:

    lsSequenceSparkle(int SparkleDelay, int SpeedDelay) : _SparkleDelay(SparkleDelay),_SpeedDelay(SpeedDelay)  {}

    void update(unsigned long frame) {
      //STRIP_LEDS(lastLed) = CRGB::Black;
      setPixel(lastLed,CRGB::Black);
      lastLed = random16(STRIP_NUM_LEDS);
    }


    void draw(unsigned long frame) {     
      if (_isOn) {
        STRIP_LEDS(lastLed)  += SEQUENCE_PRIMARY_COLOR;
        this->_nextFrameRender += _SparkleDelay;
      }
      else {
        this->_nextFrameRender += _SpeedDelay;
      } 
      _isOn = !_isOn;
    }



 
};
