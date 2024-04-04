#ifndef LS_COLORUTILS_H
#define LS_COLORUTILS_H

#include <FastLED.h>
#include "lsStruct_Enum.h"
#include <ArduinoJson.h>

class lsColorutils {

public:

    static CRGB getRandomColor();

    static CRGB getColorFromPalette(CRGBPalette16 palette, TBlendType blendType, int step);

    static byte * Wheel(byte WheelPos);
    
    static CRGB getColorWheel(byte WheelPos);

    static void fillSolid(CRGB Color, CRGB * displayLeds, int numLeds);

    static void fillRandom(CRGB * displayLeds, int numLeds);
        
    static void fillRandomSingle(CRGB * displayLeds, int numLeds);

    static void fillPalette(CRGB * displayLeds, int numLeds,CRGBPalette16 palette, TBlendType blendType);
    
    static void fillPaletteC(CRGB * displayLeds, int numLeds, CRGBPalette16 palette, TBlendType blendType, bool reversed);
    
    static void fillPattern(CRGB * displayLeds, int numLeds,LS_PATTERN_STRIP *pattern, int positions);
    
    static void fillRainbow(CRGB * displayLeds, int numLeds,uint8_t initialhue, uint8_t deltahue);
    
    static void fillRainbowC(CRGB * displayLeds, int numLeds,uint8_t initialhue, bool reversed);
    
    static void fillGradient(CRGB * displayLeds, int numLeds,CRGB c1, CRGB c2);

    static JsonDocument serialize(CRGB Color);

    static CRGBPalette16 getPalette(LS_PALETTES);

    static CRGB getColorFromJson(JsonObject);

};


#endif