#include "lsSequence.h"

class lsSequenceKITT : public lsSequence {
  public:
    int _EyeSize;
    int _SpeedDelay;
    int _ReturnDelay;
    uint8_t position;
    uint8_t gHue = 0;

    lsSequenceKITT(int EyeSize, int SpeedDelay, int ReturnDelay) : _EyeSize(EyeSize) , _SpeedDelay(SpeedDelay),_ReturnDelay(ReturnDelay)  {}

    void draw(unsigned long frame) {
      this->_Strip->clear();
      CRGB scaledColor = _Color;
      scaledColor/=10;
      for( int i = 0; i < this->_Strip->getNumLeds(); i++) { //9948
        this->_Strip->getLeds()[position] += CHSV( gHue, 255, 192);
      }
    }

/*
void upDown(CRGB Color, int EyeSize, int SpeedDelay, int ReturnDelay, bool reverse) {
  CRGB scaledColor = Color;
  scaledColor/=10;
  int start, pace;
  if (!reverse) {
    start = 0;
    pace = 1;
  }
  else {
    start = NUM_LEDS-EyeSize-2;
    pace = -1;
  }
    for(int i = 0; i < NUM_LEDS-EyeSize-2; i++) {
      clear();
      setPixel(start+(i*pace), scaledColor);
      for(int j = 1; j <= EyeSize; j++) {
        setPixel(start+(i*pace)+j,Color); 
      }
      setPixel(start+(i*pace)+EyeSize+1, scaledColor);
      showStrip();
      delay(SpeedDelay);
    }
  delay(ReturnDelay);
}
*/

    void update(unsigned long frame) {
      this->_Strip->fadeAllToBlack(20);
      position = beatsin16( 13, 0, this->_Strip->getNumLeds()-1 );
    }

    void postRender() {
      gHue = 0;
    }

};
