#include "lsSequence.h"


//TO DO CANDY CANE 2, setup for random color, setfor fixed barlenght

class lsSequenceCandyCane : public lsSequence {
  public:

    const uint16_t travelSpeed = 150;
    int shiftBy = 1;  //shiftBy can be positive or negative (to change direction)
    uint8_t numColors = 3;  // Can be either 2 or 3

    lsSequenceCandyCane(int Shift) : shiftBy(Shift) {
    }

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };


    void draw(unsigned long frame) {
      if (numColors==2) {
        for (uint8_t i=0; i<STRIP_NUM_LEDS; i++){
          setPixel(i, (i+SEQUENCE_OFFSET)%((numColors)*_blockSize)<_blockSize ? SEQUENCE_SECONDARY_COLOR : SEQUENCE_PRIMARY_COLOR);
          /*if ( (i+SEQUENCE_OFFSET)%((numColors)*_blockSize)<_blockSize ) {
            setPixel(i,SEQUENCE_SECONDARY_COLOR)
            // STRIP_LEDS(i) = SEQUENCE_SECONDARY_COLOR;
          } else {
            //STRIP_LEDS(i) = SEQUENCE_PRIMARY_COLOR;
            setPixel(i,SEQUENCE_PRIMARY_COLOR)
          }*/
        }
      }

      if (numColors==3) {
        for (uint8_t i=0; i<STRIP_NUM_LEDS; i++){
          if ( (i+SEQUENCE_OFFSET)%((numColors+1)*_blockSize)<_blockSize ) {
            setPixel(i,SEQUENCE_SECONDARY_COLOR);
            //STRIP_LEDS(i) = SEQUENCE_SECONDARY_COLOR;
          }
          else if ( (i+SEQUENCE_OFFSET+(2*_blockSize))%((numColors+1)*_blockSize)<_blockSize ) {
            setPixel(i,SEQUENCE_TERTIARY_COLOR);
            //STRIP_LEDS(i) = SEQUENCE_TERTIARY_COLOR;
          } else {
            setPixel(i,SEQUENCE_PRIMARY_COLOR);
            STRIP_LEDS(i) = SEQUENCE_PRIMARY_COLOR;
          }
        }
      SEQUENCE_OFFSET = SEQUENCE_OFFSET + shiftBy;
      if (shiftBy>0) { 
         //for positive shiftBy
        if (SEQUENCE_OFFSET>=STRIP_NUM_LEDS) 
         RESET_OFFSET
        } 
        else {
            //for negitive shiftBy
          if (SEQUENCE_OFFSET<0) SEQUENCE_OFFSET = STRIP_NUM_LEDS;
        }
      }
    }
    
    void update(unsigned long frame) {
      EVERY_N_SECONDS(5) {
        _blockSize = random8(3,6);  //picks random length
      }
    }
};

/*

#include "lsSequence.h"

class lsSequenceAndroid : public lsSequence {
  public:

    uint8_t maxPosition;
    bool isFlush = false;

    void preRender(){
      _blockSize = random8(2,6);
      SEQUENCE_PRIMARY_COLOR = GETRANDOMCOLOR;
      _Strip->drawColor(SEQUENCE_SECONDARY_COLOR);
      RESET_OFFSET
      isFlush = false;
    }

    void draw(unsigned long frame) {
      // Draw two bars of width size equally offset from either end of our strand
        this->_Strip->flush(SEQUENCE_PRIMARY_COLOR,1);
    }

    void update(unsigned long frame) {
      if (INCREASE_SEQUENCE_OFFSET >= this->_blockSize) {
        _blockSize = random8(2,6);
        RESET_OFFSET
        SEQUENCE_PRIMARY_COLOR = GETRANDOMCOLOR;
      }
    }
};

*/