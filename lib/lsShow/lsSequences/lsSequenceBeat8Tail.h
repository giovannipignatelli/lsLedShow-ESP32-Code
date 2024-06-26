#include "lsSequence.h"



class lsSequenceBeat8Tail : public lsSequence {
  public:

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };


    lsSequenceBeat8Tail(accum88 movespeed=6, uint8_t fadeRate=80) {
      _param1 = fadeRate;
      _param2 = movespeed;
      _type = LS_SEQUENCES_TYPES::lsSequenceBeat8Tail;
    }

    void draw(unsigned long frame) {
      fadeToBlackBy( this->_Strip->getLeds(), STRIP_NUM_LEDS, _param1*5);  // Fade out pixels.
      uint16_t pos = beatsin16( _param2, 0, STRIP_NUM_LEDS-1 );
      setPixel(pos, CHSV( SEQUENCE_HUE, 200, 255));
    }

};


//ORIGINAL EXAMPLE 
/*
//***************************************************************
// beat8 example.  Moves pixel position based on beat8.
//
// -Marc Miller, Jan 2016
// Updated Feb 2016 - made move speed and fade rate variables.
//***************************************************************

#include "FastLED.h"
#define LED_TYPE LPD8806
#define DATA_PIN 11
#define CLOCK_PIN 13
#define NUM_LEDS 32
#define COLOR_ORDER GRB
#define BRIGHTNESS 50
CRGB leds[NUM_LEDS];

uint8_t gHue = 0;  // Used to cycle through rainbow.
uint8_t moveSpeed = 6;  // Higher value moves pixel faster.
uint8_t fadeRate = 80;  // Use lower value to give a fading tail.


//---------------------------------------------------------------
void setup() 
{
  Serial.begin(115200);  // Allows serial monitor output (check baud rate)
  delay(3000);  // 3 second delay
  FastLED.addLeds<LED_TYPE, DATA_PIN, CLOCK_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
}


//---------------------------------------------------------------
void loop() 
{
  EVERY_N_MILLISECONDS( 50 ) { gHue++; }  // Slowly cycle through the rainbow

  beat8_tail();  // Subroutine to move the pixel!
  
  FastLED.show();  // Display the pixels.

}//end main loop



//===============================================================
void beat8_tail()
{
  EVERY_N_MILLISECONDS( 5 ) {
    fadeToBlackBy( leds, NUM_LEDS, fadeRate);  // Fade out pixels.
  }
  uint16_t pos = beat8(moveSpeed) % NUM_LEDS;  // modulo the position to be within NUM_LEDS
  leds[pos] = CHSV( gHue, 200, 255);
  //Serial.print("pos: "); Serial.println(pos);
}


//---------------------------------------------------------------
//EOF
*/