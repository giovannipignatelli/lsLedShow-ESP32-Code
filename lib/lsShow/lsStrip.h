#ifndef LS_LIGHT_STRIP_H
#define LS_LIGHT_STRIP_H

#include <FastLED.h>
#include <LinkedList.h>
#include "lsStruct_Enum.h"

class lsStrip {
   protected:
      CRGB *displayLeds;
      int numLeds;

   public:
    lsStrip(CRGB *displayLeds, int numLeds) : displayLeds(displayLeds), numLeds(numLeds) {};
    int getNumLeds();
    CRGB *getLeds();
    void applyMask(uint8_t *maskStrip);
    void clear();
    void drawColor(CRGB Color);
    void drawRainbow(uint8_t initialhue, uint8_t deltahue);
    void drawRainbowC(uint8_t initialhue, bool reversed);
    void drawGradient(CRGB c1, CRGB c2);
    void drawPalette(CRGBPalette16 palette, TBlendType blendType);
    void drawPaletteC(CRGBPalette16 palette, TBlendType blendType, bool reversed); 
    void drawPattern(lsPatternStrip *pattern, int positions);
    void printLeds();
    void setLeds(CRGB *newLeds);
    void setPixel(int Strip, int Pixel, CRGB Color);
    void showStrip();
};
#endif