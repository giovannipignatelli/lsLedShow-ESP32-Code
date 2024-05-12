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

#ifndef LS_LIGHT_STRIP_COMPOSITE_H
#define LS_LIGHT_STRIP_COMPOSITE_H

#include <FastLED.h>

#include "lsLinkedList.h"
#include "lsDefinitions.h"

#include "lsStruct_Enum.h"
#include "lsStripInterface.h"
#include "lsStrip.h"

class lsStripComposite : public lsStripInterface {

   private:
      void reverseLeds(CRGB *toRevert, int size);
      CRGB * reversed;

   protected:
      LinkdList<lsStrip*> _strips = LinkdList<lsStrip*>();
      int current_Strip;
      uint32_t changeCurrentIndexEveryNframes, nextChangeFrame,currentFrame;

   public:
    lsStripComposite(){
      effect = LS_MULTIPLE_STRIPS_EFFECTS::lsOffset;
      current_Strip=0;
      currentFrame=0;setChangeIndexEveryNFrames(30);
      this->reversed = new CRGB[NUM_LEDS];
   };
    void setEffects(LS_MULTIPLE_STRIPS_EFFECTS effect);
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
    void setLeds(CRGB *newLeds) ;
    void setPixel(int Strip, int Pixel, CRGB Color);
    void setChangeIndexEveryNFrames(uint32_t frames);
    void showStrip();
    void fadeAllToBlack(byte fadeValue);
};
#endif