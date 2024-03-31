#include "lsSequence.h"

class lsSequencePaletteGradient : public lsSequence {
  public:

    byte startHue = 0;
    byte deltaY = 0;
    byte deltaX = 0;

    lsSequencePaletteGradient(byte deltaX = 3, byte deltaY = 1) {
        this->deltaX = deltaX;
        this->deltaY = deltaY;
    }

    void preRender(){
      RESET_HUE
    }

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };


    void draw(unsigned long frame) {
      uint8_t hue = SEQUENCE_HUE;

      for( uint16_t i = 0; i < STRIP_NUM_LEDS; i++) {
        setPixel(i,ColorFromPalette(this->_Palette, hue, 255, LINEARBLEND));
        //STRIP_LEDS(i) = ColorFromPalette(this->_Palette, hue, 255, LINEARBLEND);
        hue += this->deltaX;
      }

      SEQUENCE_HUE += this->deltaY;

      if(SEQUENCE_HUE > 255) {
       RESET_HUE
      }
    }

};