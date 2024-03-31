#include "lsSequence.h"

class lsSequenceComet : public lsSequence {
  public:

    bool bounce;
    int pos = 0;
    int dir = 1;
    bool randomDecay;
    byte trailDecay;


    lsSequenceComet(byte meteorTrailDecay, bool meteorRandomDecay, bool bounce = false, byte dir = 1) : bounce(bounce), dir(dir), randomDecay(meteorRandomDecay), trailDecay(meteorTrailDecay) {
      _type = LS_SEQUENCES_TYPES::lsSequenceComet;
    }

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };


    void draw(unsigned long frame) {
      
      for(int j=0; j<STRIP_NUM_LEDS; j++) {
        if( (!randomDecay) || (random8(10)>5) ) {
          STRIP_LEDS(j).fadeToBlackBy( trailDecay );
        }
      }
      for (int j = 0; j < this->_blockSize; j++) {
        if(_inBounds(this->pos - j*(this->dir))) setPixel(this->pos - j*(this->dir),SEQUENCE_PRIMARY_COLOR) ;//STRIP_LEDS(this->pos - j*(this->dir)) = SEQUENCE_PRIMARY_COLOR;
      }
    }
    void update(unsigned long frame) {
      if((this->pos >= (STRIP_NUM_LEDS + this->_blockSize)) || (this->pos <= (0 - this->_blockSize))) {
          if(this->bounce)
              this->dir *= -1;
          else
              this->pos = 0;    
      }
      this->pos += this->dir;  
    }
 
};
