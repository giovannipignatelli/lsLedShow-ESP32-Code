#ifndef QP_ENUMS_H
#define QP_ENUMS_H

#include <FastLED.h>
#include <LinkedList.h>

struct lsPatternStrip{CRGB stripColor;int  stripSize; };
struct lsMask{ uint8_t fadeValue; int  stripSize; };

enum LS_SEQUENCE_COLORING {FIXEDCOLOR, RANDOMCOLOR, PALETTECOLOR};
enum LS_FILL_TYPES {RANDOM,RAINBOW,RAINBOWCIRCULAR,GRADIENT,SOLID,PALETTE,PALETTECIRCULAR,PATTERN};
//enum LS_MERGE_TYPES {ADD,SUBTRACT,COMBINEUP,COMBINEDOWN,BLEND,MASK};
enum LS_FILTER {RED,GREEN,BLUE};
enum class LS_BLENDMODE {
    ADD,
    SUBTRACT,
    MULTIPLY,
    FUSE_UP,    // New blend mode using |= operator for 'fusing' colors upwards
    FUSE_DOWN,  // New blend mode using &= operator for 'fusing' colors downwards
    N_BLEND,    // New blend mode using FastLED's nblend method for smooth blending
    COVER,
    // Additional blend modes can be added here
};

#endif