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
      this->_Strip->getLeds()[lastLed] = CRGB::Black;
      lastLed = random16(this->_Strip->getNumLeds());
    }


    void draw(unsigned long frame) {     
      if (_isOn) {
        this->_Strip->getLeds()[lastLed]  += this->_Color;
        this->_nextFrameRender += _SparkleDelay;
      }
      else {
        this->_nextFrameRender += _SpeedDelay;
      } 
      _isOn = !_isOn;
    }



 
};
