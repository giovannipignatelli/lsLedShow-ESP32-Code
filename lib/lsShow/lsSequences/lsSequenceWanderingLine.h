#include "lsSequence.h"

class lsSequenceWanderingLine : public lsSequence {
  public:

    int pos = 0;
    int dir = 1;
    int dist = 0;

    void getNewDistance() {
      this->dist = random16(STRIP_NUM_LEDS / 2);
    }

    void chooseRandomDirection() {
      if(random8(100) > 50)
        this->changeDirection();
    }

    void changeDirection() {
      this->dir *= -1;
      this->pos += (this->dir * this->_blockSize);
    }

    void preRender() {
      // get an initial starting position
      this->pos = random16((STRIP_NUM_LEDS - this->_blockSize));
      this->getNewDistance();
      this->chooseRandomDirection();
    }

    void draw(unsigned long frame) {
      this->pos += this->dir;

       //STRIP_LEDS(this->pos) = SEQUENCE_PRIMARY_COLOR;
       setPixel(pos,SEQUENCE_PRIMARY_COLOR);
  
      if(! _inBounds(this->pos)) {
        // We hit a boundary - reverse direction, calculate a new distance to roam and count a cycle
        this->changeDirection();
        this->getNewDistance();

      } else if(this->dist == 0) {
        // We roamed our distance, get new values and count a cycle
        this->getNewDistance();
        this->chooseRandomDirection();
      }
    }

    void update(unsigned long frame) {
      if(_inBounds(this->pos - (this->_blockSize*this->dir))) 
        setPixel(this->pos - (this->_blockSize*this->dir),CRGB::Black);
        //STRIP_LEDS(this->pos - (this->_blockSize*this->dir)) = CRGB::Black;

      this->dist--;
    }


};