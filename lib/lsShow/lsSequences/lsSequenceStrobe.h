#include "lsSequence.h"

class lsSequenceStrobe : public lsSequence {

  private:

  int lastLed = 0;
  int _strobeNumber = 0;

  public:

    lsSequenceStrobe(int count, int FlashDelay, int EndPause)  {
      _param1 = count;
      _param2 = FlashDelay;
      _param3 = EndPause;
      _type = LS_SEQUENCES_TYPES::lsSequenceStrobe; 
    }

    lsSequenceStrobe()  {
      _type = LS_SEQUENCES_TYPES::lsSequenceStrobe; 
    }

    void update(unsigned long frame) {
      _strobeNumber++;
      if (_strobeNumber == _param1*2) {
        _strobeNumber=0;
        _statusA = false;
         this->_nextFrameRender = frame + _param3;
      }
    }


    void draw(unsigned long frame) {     
      if (_statusA) {
        this->_Strip->drawColor(SEQUENCE_PRIMARY_COLOR);
      }
      else {
        STRIP_CLEAR
      }
      this->_nextFrameRender = frame + _param2;     
      _statusA = !_statusA;
    }



 
};
