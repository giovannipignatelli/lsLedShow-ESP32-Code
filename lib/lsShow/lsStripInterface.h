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

#ifndef LS_LIGHT_STRIP_INTERFACE_H
#define LS_LIGHT_STRIP_INTERFACE_H

#include <FastLED.h>
#include "lsLinkedList.h"
#include "lsStruct_Enum.h"

class lsStripInterface {

   public:
    
    LS_MULTIPLE_STRIPS_EFFECTS effect;

    lsStripInterface(){};
    void add(int numLeds, uint8_t pin);
    int getNumLeds();
    CRGB *getLeds();
    void applyMask(uint8_t *maskStrip);
    void clear();
    void clear(int i);
    void flush(CRGB ColorFill, int offset);
    void drawColor(CRGB Color);
    void drawRainbow(uint8_t initialhue, uint8_t deltahue);
    void drawRainbowC(uint8_t initialhue, bool reversed);
    void drawGradient(CRGB c1, CRGB c2);
    void drawPalette(CRGBPalette16 palette, TBlendType blendType);
    void drawPaletteC(CRGBPalette16 palette, TBlendType blendType, bool reversed); 
    void drawPattern(LS_PATTERN_STRIP *pattern, int positions);
    void printLeds();
    void printLeds(int num);
    void setLeds(CRGB *newLeds);
    void setPixel(int Strip, int Pixel, CRGB Color);
    void showStrip();
    void fadeAllToBlack(byte fadeValue);
    void setEffects(LS_MULTIPLE_STRIPS_EFFECTS effect);
};
#endif