#include "lsSequence.h"

class lsSequenceDigitalRain : public lsSequence {
  public:

    lsSequenceDigitalRain(){
      _type = LS_SEQUENCES_TYPES::lsSequenceDigitalRain;
    }

    uint8_t maxPosition;
    bool isFlush = false;

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };


    void preRender(){
      _blockSize = random8(2,6);
      SEQUENCE_PRIMARY_COLOR = GETRANDOMCOLOR;
      _Strip->drawColor(SEQUENCE_SECONDARY_COLOR);
      RESET_OFFSET
      isFlush = false;
    }

    void draw(unsigned long frame) {
      // Draw two bars of width size equally offset from either end of our strand
        this->_Strip->flush(SEQUENCE_PRIMARY_COLOR,1);
    }

    void update(unsigned long frame) {
      if (INCREASE_SEQUENCE_OFFSET >= this->_blockSize) {
        _blockSize = random8(2,6);
        RESET_OFFSET
        SEQUENCE_PRIMARY_COLOR = GETRANDOMCOLOR;
      }
    }
};

/*

#include <Arduino.h>

#include <FastLED.h>
#include <WS2812FX.h>

#define NUM_LEDS 120
#define NUM_SCENES 5 
#define LED_TYPE WS2812
#define COLOR_ORDER GRB
#define DATA_PIN 14
#define BRIGHTNESS          96


#include "FastLED.h"
 
// Matrix size
#define NUM_ROWS 30
#define NUM_COLS 1
// LEDs pin
#define DATA_PIN 14
// LED brightness
#define BRIGHTNESS 255
#define NUM_LEDS NUM_ROWS * NUM_COLS
// Define the array of leds
CRGB leds[NUM_LEDS];
byte rain[NUM_LEDS];
byte counter = 1;
int speed = 1;

uint16_t XY (uint8_t x, uint8_t y) { return (y * NUM_COLS + x);}  

void changepattern () {
    int rand1 = random16 (NUM_LEDS);
    int rand2 = random16 (NUM_LEDS);
    if ((rain[rand1] == 1) && (rain[rand2] ==0) )    //simple get two random dot 1 and 0 and swap it, 
        {rain[rand1] = 0; rain[rand2] = 1;}           //this will not change total number of dots 
} //changepattern
 
void raininit() {                               //init array of dots. run once
    for (int i = 0; i < NUM_LEDS; i++) {
        if (random8(20) == 0) { rain[i] = 1; }       //random8(20) number of dots. decrease for more dots
        else { rain[i] = 0; }                
    }
} //raininit
 
void updaterain() {
    for (byte i = 0; i < NUM_COLS; i++) {
        for (byte j = 0; j < NUM_ROWS; j++) {
            byte layer = rain[XY(i, ((j + speed + random8(2) + NUM_ROWS) % NUM_ROWS))];     //fake scroll based on shift coordinate
                                                                                            // random8(2) add glitchy look
            if (layer) { leds[XY((NUM_COLS - 1) - i, (NUM_ROWS - 1) - j)] = CHSV(120, 255, BRIGHTNESS); }   
        }
    }
    speed ++;
    fadeToBlackBy(leds, NUM_LEDS, 40);
    blurRows(leds, NUM_COLS, NUM_ROWS, 16);      //if you want
} //updaterain
 


void setup() {
    FastLED.addLeds<LED_TYPE, DATA_PIN , COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    raininit();
}
 
void loop() {
    EVERY_N_MILLISECONDS(100) {
        updaterain();
        FastLED.show();
    }
    EVERY_N_MILLISECONDS(30) {changepattern();}
} //loop

*/
