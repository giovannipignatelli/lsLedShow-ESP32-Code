#include "lsSequence.h"

class lsSequenceBPM : public lsSequence {
  public:

    uint8_t BeatsPerMinute = 62;
    uint8_t beat;

    lsSequenceBPM(){
      _type = LS_SEQUENCES_TYPES::lsSequenceBPM;
    }

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };


    void draw(unsigned long frame) {
      for( int i = 0; i < STRIP_NUM_LEDS; i++) { //
        // ORIGINALE --- STRIP_LEDS(i) = ColorFromPalette(_Palette, SEQUENCE_HUE+(i*2), beat-SEQUENCE_HUE+(i*10));
        setPixel(i,ColorFromPalette(_Palette, SEQUENCE_HUE+(i*2), beat-SEQUENCE_HUE+(i*10)));
      }
    }

    void update(unsigned long frame) {
      beat = beatsin8( BeatsPerMinute, 64, 255);
    }

    void postRender() {
      SEQUENCE_HUE = 0;
    }

};
