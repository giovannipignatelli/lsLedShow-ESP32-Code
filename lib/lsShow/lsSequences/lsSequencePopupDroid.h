#include "lsSequence.h"

class lSSequencePopupDroid : public lsSequence {
  public:
    enum {POPUP, GO} state = POPUP;

    bool clearEachCycle = true;
    uint16_t startPos = 0;
    int dir = 1;

    //popup state
    byte numFlashes = 8;
    byte flashSteps = 0;

    //go state
    byte goMoves = 0;
    byte goDist = 0;

    lSSequencePopupDroid(int size = 6, bool clearEachCycle = true) {
        this->_blockSize = size;
        this->clearEachCycle = clearEachCycle;
        this->_type = LS_SEQUENCES_TYPES::lsSequencePopupDroid;
    }

    void preRender() {
      this->restart();
    }

    void restart() {
      this->flashSteps = numFlashes*2;
      this->startPos = random16(0, (STRIP_NUM_LEDS - this->_blockSize));
      this->state = POPUP;
    }

    void changeDirection() {
      this->dir *= -1;
    }

    //bool _inBounds(int pos) { return ((pos >= 0) && (pos < STRIP_NUM_LEDS )); }

    void draw(unsigned long frame) {
      STRIP_CLEAR
      switch(this->state) {
        case POPUP:
          this->doPOPUP();
          break;
        case GO:
          this->doGO();
          break;
      }

    }

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };


    void doPOPUP() {
      for(int i = 0; i < this->_blockSize; i++) {
        /*
        if(this->flashSteps%2)
          STRIP_LEDS(this->startPos+i) = SEQUENCE_PRIMARY_COLOR;
        else
          STRIP_LEDS(this->startPos+i) = CRGB::Black;
        */
        setPixel(this->startPos+i, this->flashSteps%2 ? SEQUENCE_PRIMARY_COLOR : CRGB::Black );
      }

      //init GO here
      if(--this->flashSteps <= 0) {
        this->state = GO;
        this->goMoves = random16(4, 8);
        this->goDist = random(this->_blockSize, (STRIP_NUM_LEDS  / 2));
      }
    }

    void doGO() {
      for(int i = 0; i < this->_blockSize; i++) {
        if(_inBounds(this->startPos+i))
          this->_Strip->getLeds() [(this->startPos+i)] =  SEQUENCE_PRIMARY_COLOR;
      }

      this->startPos += this->dir;

      if(!_inBounds(this->startPos+this->_blockSize) || (--this->goDist <= 0)) {
        if(--this->goMoves <= 0) {
          this->restart();
          if(this->clearEachCycle) STRIP_CLEAR;
        }
        this->goDist = random(this->_blockSize, (STRIP_NUM_LEDS  / 2));
        this->changeDirection();
      }
    }

};