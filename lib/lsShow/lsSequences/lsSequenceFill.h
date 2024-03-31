#include "lsSequence.h"
#ifndef SEQUENCE_FILL
#define SEQUENCE_FILL

class lsSequenceFill : public lsSequence {
  public:

    lsSequenceFill(){
      _type = LS_SEQUENCES_TYPES::lsSequenceFill;
    }


    void getFirstFrameRender(CRGB * leds)  {
      switch(_Coloring) {
        case LS_FILL_TYPES::SOLID:
          lsColorutils::fillSolid(SEQUENCE_PRIMARY_COLOR,leds,STRIP_NUM_LEDS);
          break;
        case LS_FILL_TYPES::PALETTE:
          lsColorutils::fillPalette(leds,STRIP_NUM_LEDS,_Palette,_Blending);
          break;
        case LS_FILL_TYPES::PATTERN:
          lsColorutils::fillPattern(leds,STRIP_NUM_LEDS,_stripes,_stripesSize);
          break;
        case LS_FILL_TYPES::RANDOMSOLID:
          lsColorutils::fillRandom(leds,STRIP_NUM_LEDS);
          break;
        case LS_FILL_TYPES::RANDOMSINGLE:
          lsColorutils::fillRandomSingle(leds,STRIP_NUM_LEDS);
          break;
        case LS_FILL_TYPES::RAINBOW:
          lsColorutils::fillRainbow(leds,STRIP_NUM_LEDS,_initialhue,_deltahue);
          break;
        case LS_FILL_TYPES::RAINBOWCIRCULAR:
          lsColorutils::fillRainbowC(leds,STRIP_NUM_LEDS,_initialhue,_isReversed);
          break;
        case LS_FILL_TYPES::PALETTECIRCULAR:
          lsColorutils::fillPaletteC(leds,STRIP_NUM_LEDS,_Palette,_Blending,_isReversed);
          break;
        case GRADIENT:
          lsColorutils::fillGradient(leds,STRIP_NUM_LEDS,SEQUENCE_PRIMARY_COLOR,SEQUENCE_SECONDARY_COLOR);
          break;
      }
    };

    void draw(unsigned long frame) {
      switch(_Coloring) {
        case LS_FILL_TYPES::SOLID:
          fillSolid();
          break;
        case LS_FILL_TYPES::PALETTE:
          fillPalette();
          break;
        case LS_FILL_TYPES::PATTERN:
          fillPattern();
          break;
        case LS_FILL_TYPES::RANDOMSOLID:
          fillRandom();
          break;
        case LS_FILL_TYPES::RANDOMSINGLE:
          fillRandomSingle();
          break;
        case LS_FILL_TYPES::RAINBOW:
          fillRainbow();
          break;
        case LS_FILL_TYPES::RAINBOWCIRCULAR:
          fillRainbowC();
          break;
        case LS_FILL_TYPES::PALETTECIRCULAR:
          fillPaletteC();
          break;
        case GRADIENT:
          fillGradient();
          break;
      }
    }

};
#endif