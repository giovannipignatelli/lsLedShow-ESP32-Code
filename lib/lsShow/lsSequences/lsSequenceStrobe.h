#include "lsSequence.h"

class lsSequenceStrobe : public lsSequence {

  private:

  int _FlashDelay = 0;
  int _EndPause = 0;
  int lastLed = 0;
  bool _isOn = false;
  int _count;
  int _strobeNumber = 0;

  public:

    lsSequenceStrobe(int count, int FlashDelay, int EndPause) : _count(count), _FlashDelay(FlashDelay),_EndPause(EndPause)  {}

    void update(unsigned long frame) {
      _strobeNumber++;
      if (_strobeNumber == _count*2) {
        _strobeNumber=0;
        _isOn = false;
         this->_nextFrameRender = frame + _EndPause;
      }
    }


    void draw(unsigned long frame) {     
      if (_isOn) {
        this->_Strip->drawColor(this->_Color);
      }
      else {
        this->_Strip->clear();
      }
      this->_nextFrameRender = frame + _FlashDelay;     
      _isOn = !_isOn;
    }



 
};
