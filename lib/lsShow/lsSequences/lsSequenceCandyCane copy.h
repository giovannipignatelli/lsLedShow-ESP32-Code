#include "lsSequence.h"


//TO DO CANDY CANE 2, setup for random color, setfor fixed barlenght

class lsSequenceCandyCane : public lsSequence {
  public:

    CRGB color1;  // color used between color 2 (and 3 if used)
    CRGB color2;
    CRGB color3 ;  //optional 3rd color
    const uint16_t travelSpeed = 150;
    int shiftBy = 1;  //shiftBy can be positive or negative (to change direction)
    uint8_t numColors = 3;  // Can be either 2 or 3
    uint8_t stripeLength = 5;  //number of pixels per color
    int offset;

    lsSequenceCandyCane(CRGB col1,CRGB col2,CRGB col3, int Shift) : color1(col1), color2(col2), color3(col3), shiftBy(Shift) {}

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };


    void draw(unsigned long frame) {
      if (numColors==2) {
        for (uint8_t i=0; i<this->_Strip->getNumLeds(); i++){
          if ( (i+offset)%((numColors)*stripeLength)<stripeLength ) {
            _Strip->getLeds()[i] = color2;
          } else {
            _Strip->getLeds()[i] = color1;
          }
        }
      }

      if (numColors==3) {
        for (uint8_t i=0; i<_Strip->getNumLeds(); i++){
          if ( (i+offset)%((numColors+1)*stripeLength)<stripeLength ) {
            _Strip->getLeds()[i] = color2;
          }
          else if ( (i+offset+(2*stripeLength))%((numColors+1)*stripeLength)<stripeLength ) {
            _Strip->getLeds()[i] = color3;
          } else {
            _Strip->getLeds()[i] = color1;
          }
        }
      offset = offset + shiftBy;
      if (shiftBy>0) { 
         //for positive shiftBy
        if (offset>=_Strip->getNumLeds()) 
          offset = 0;
        } 
        else {
            //for negitive shiftBy
          if (offset<0) offset = _Strip->getNumLeds();
        }
      }
    }
    
    void update(unsigned long frame) {
      EVERY_N_SECONDS(5) {
        //numColors = random8(2,4);  //picks either 2 or 3
        stripeLength = random8(3,6);  //picks random length
      }
    }
};

/*

void candyCane(){
  CRGB color1 = CRGB::White;  // color used between color 2 (and 3 if used)
  CRGB color2 = CRGB::Red;
  //CRGB color3 = CHSV(0,170,255);  //optional 3rd color
  CRGB color3 = CRGB(0,255,0);  //optional 3rd color
  const uint16_t travelSpeed = 150;
  int shiftBy = 1;  //shiftBy can be positive or negative (to change direction)
  static uint8_t numColors = 3;  // Can be either 2 or 3
  static uint8_t stripeLength = 5;  //number of pixels per color
  static int offset;

  EVERY_N_SECONDS(5) {
    numColors = random8(2,4);  //picks either 2 or 3
    stripeLength = random8(3,6);  //picks random length
  }

  EVERY_N_MILLISECONDS(travelSpeed) {
    if (numColors==2) {
      for (uint8_t i=0; i<NUM_LEDS; i++){
        if ( (i+offset)%((numColors)*stripeLength)<stripeLength ) {
          leds[i] = color2;
        } else {
          leds[i] = color1;
        }
      }
    }

    if (numColors==3) {
      for (uint8_t i=0; i<NUM_LEDS; i++){
        if ( (i+offset)%((numColors+1)*stripeLength)<stripeLength ) {
          leds[i] = color2;
        }
        else if ( (i+offset+(2*stripeLength))%((numColors+1)*stripeLength)<stripeLength ) {
          leds[i] = color3;
        } else {
          leds[i] = color1;
        }
      }
    }

    FastLED.show();

    offset = offset + shiftBy;
    if (shiftBy>0) {  //for positive shiftBy
      if (offset>=NUM_LEDS) offset = 0;
    } else {  //for negitive shiftBy
      if (offset<0) offset = NUM_LEDS;
    }

  }//end EVERY_N
}//end candyCane

*/