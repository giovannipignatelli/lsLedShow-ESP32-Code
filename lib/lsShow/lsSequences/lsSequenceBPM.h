#include "lsSequence.h"

class lsSequenceBPM : public lsSequence {
  public:

    lsSequenceBPM(){
      _type = LS_SEQUENCES_TYPES::lsSequenceBPM;
      _param1 = 62;
    }

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };


    void draw(unsigned long frame) {
      for( int i = 0; i < STRIP_NUM_LEDS; i++) { //
        // ORIGINALE --- STRIP_LEDS(i) = ColorFromPalette(_Palette, SEQUENCE_HUE+(i*2), _param2-SEQUENCE_HUE+(i*10));
        setPixel(i,ColorFromPalette(_Palette, SEQUENCE_HUE+(i*2), _param2-SEQUENCE_HUE+(i*10)));
      }
    }

    void update(unsigned long frame) {
      _param2 = beatsin8( _param1, 64, 255);
    }

    void postRender() {
      SEQUENCE_HUE = 0;
    }

};
