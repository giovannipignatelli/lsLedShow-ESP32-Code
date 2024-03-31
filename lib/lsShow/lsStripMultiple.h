/*
 * Project: Led Show
 * Author: Giovanni Pignatelli
 * License: MIT (Open Source)
 * 
 * Inspirations:
 * - qpQuickPatterns from brimshot https://github.com/brimshot/quickPatterns
 * - atuline https://github.com/atuline/FastLED-Demos
 * - WS2812FX from kitesurfer1404 https://github.com/kitesurfer1404/WS2812FX/tree/master/examples
 * - https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/
 * 
 * Versioning:
 * - v1.0.0: Initial release
 * 
 * To Do:
 * 
 * Description: [Description of what the file does]
 */

#ifndef LS_LIGHT_STRIPMULTIPLE_H
#define LS_LIGHT_STRIPMULTIPLE_H

#include <FastLED.h>
#include <LinkedList.h>
#include "lsStruct_Enum.h"

class lsStripMultiple {
   protected:
      CRGB **displayLeds;
      int numLeds;
      int numStrips;
      int *datapins;

   public:
    lsStripMultiple(CRGB **displayLeds, int numLeds, int *dataPins) : displayLeds(displayLeds), numLeds(numLeds), datapins(dataPins) {};
    int getNumLeds();
    CRGB *getLeds(int stripNumber);
    void applyMask(uint8_t *maskStrip);
    void clear(int stripIndex = -1);
    void flush(CRGB ColorFill, int offset, int stripIndex = -1);
    void drawColor(CRGB Color, int stripIndex = -1);
    void drawRainbow(uint8_t initialhue, uint8_t deltahue, int stripIndex = -1);
    void drawRainbowC(uint8_t initialhue, bool reversed, int stripIndex = -1);
    void drawGradient(CRGB c1, CRGB c2, int stripIndex = -1);
    void drawPalette(CRGBPalette16 palette, TBlendType blendType, int stripIndex = -1);
    void drawPaletteC(CRGBPalette16 palette, TBlendType blendType, bool reversed, int stripIndex = -1);
    void drawPattern(LS_PATTERN_STRIP *pattern, int positions, int stripIndex = -1);
    void printLeds(int stripIndex = -1);
    void printLeds(int num, int stripIndex = -1);
    void setLeds(CRGB *newLeds, int stripIndex);
    void setPixel(int Strip, int Pixel, CRGB Color);
    void showStrip();
    void fadeAllToBlack(byte fadeValue, int stripIndex = -1);
    void replicateToAllStrips(int sourceIndex, int offset = 0);
    void copyStripData(int sourceIndex, int destIndex, int offset = 0);
};
#endif