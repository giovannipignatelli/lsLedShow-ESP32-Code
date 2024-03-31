#include "lsSequence.h"

class lsSequenceSingleDynamic : public lsSequence {
  public:

    bool isFirstRender = true; 

    void preRender(){ isFirstRender = true; }

    void draw(unsigned long frame) {
      if (isFirstRender) {
        this->_Strip->drawColor(GETRANDOMCOLOR);
        isFirstRender = false;
      }
      else {
        setPixel(random8(STRIP_NUM_LEDS),GETRANDOMCOLOR);
        //STRIP_LEDS(random8(STRIP_NUM_LEDS)) = GETRANDOMCOLOR;
      }
    }
     
};
