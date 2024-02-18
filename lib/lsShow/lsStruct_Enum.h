#ifndef QP_ENUMS_H
#define QP_ENUMS_H

#include <FastLED.h>
#include <LinkedList.h>

struct lsPatternStrip{CRGB stripColor;int  stripSize; };
struct lsMask{ uint8_t fadeValue; int  stripSize; };
enum LS_FILL_TYPES {RANDOM,RAINBOW,RAINBOWCIRCULAR,GRADIENT,SOLID,PALETTE,PALETTECIRCULAR,PATTERN};
//enum LS_MERGE_TYPES {ADD,SUBTRACT,COMBINEUP,COMBINEDOWN,BLEND,MASK};
enum LS_FILTER {RED,GREEN,BLUE};

#endif