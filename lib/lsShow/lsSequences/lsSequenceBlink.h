#include "lsSequence.h"
#include "lsSequenceFill.h"

class lsSequenceBlink : public lsSequence {
  public:

    bool isStrobe;
    bool ison = false;

    lsSequenceBlink(bool isStrobe= false) : isStrobe(isStrobe) {
      _type = LS_SEQUENCES_TYPES::lsSequenceBlink;
    }

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };


    void draw(unsigned long frame) {
      
      if (isStrobe){
        if ((frame) % _renderEveryNFrames == 0)
          this->_Strip->drawColor(SEQUENCE_PRIMARY_COLOR);
        else this->_Strip->drawColor(SEQUENCE_SECONDARY_COLOR);
      }
      else{
        if (!ison) this->_Strip->drawColor(SEQUENCE_SECONDARY_COLOR);
        else this->_Strip->drawColor(SEQUENCE_PRIMARY_COLOR);
      }
    }

    void update(unsigned long frame) {
      ison = !ison;
      if(!ison) INCREASE_SEQUENCE_RUN;
    }
};
