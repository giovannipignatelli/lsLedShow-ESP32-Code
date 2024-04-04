#include "lsSequence.h"

class lsSequenceComet : public lsSequence {
  public:



    lsSequenceComet(byte meteorTrailDecay=50, bool meteorRandomDecay=true, bool bounce = false, byte dir = 1) {
      _statusA = bounce;
      _param1 = dir;
      _statusB = meteorRandomDecay;
      _param2 = meteorTrailDecay;
      _currentPosition = 0;
      _type = LS_SEQUENCES_TYPES::lsSequenceComet;
    }

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };


    void draw(unsigned long frame) {
      
      for(int j=0; j<STRIP_NUM_LEDS; j++) {
        if( (!_statusB) || (random8(10)>5) ) {
          STRIP_LEDS(j).fadeToBlackBy( _param2 );
        }
      }
      for (int j = 0; j < this->_blockSize; j++) {
        if(_inBounds(this->_currentPosition - j*(this->_param1))) setPixel(this->_currentPosition - j*(this->_param1),SEQUENCE_PRIMARY_COLOR) ;//STRIP_LEDS(this->pos - j*(this->_param1)) = SEQUENCE_PRIMARY_COLOR;
      }
    }
    void update(unsigned long frame) {
      if((this->_currentPosition >= (STRIP_NUM_LEDS + this->_blockSize)) || (this->_currentPosition <= (0 - this->_blockSize))) {
          if(this->_statusA)
              this->_param1 *= -1;
          else
              this->_currentPosition = 0;    
      }
      this->_currentPosition += this->_param1;  
    }
 
};
