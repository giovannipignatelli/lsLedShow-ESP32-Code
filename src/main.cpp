#include <Arduino.h>
#include <FastLED.h>
#include <LinkedList.h>
#define NUM_LEDS 120
#define NUM_STRIPS 1
#define NUM_SCENES 5 
#define STRIP_TYPE WS2812
#define COLOR_ORDER GRB
#define PIN 14
#define BUTTON 2
#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120
#define TIME_ON_STAGE      40
#define FRAMES_PER_SECOND_FIRE 60

#include "lsStrip.h"
#include "lsSequence.h"
#include "lsLevel.h"
#include "lsStage.h"
#include "lsShow.h"
#include "lsStruct_Enum.h"
#include "lsSequences/lsSequences.h"


CRGB leds[NUM_LEDS];

extern lsMask evenMask_m[] = {{1,1},{0,1}};
extern lsMask oddMask_m[] =  {{0,1},{1,1}};
extern lsMask oddityMask_m[] = {{0,2},{1,2}};
extern lsPatternStrip pattern_p[] = { {CRGB::White , 5},{CRGB::Yellow , 5},{CRGB::Blue, 4},{CRGB::Green, 2},  {CRGB::Red, 2}};

lsLedShow show(leds,NUM_LEDS);

void setup() {
  delay(3000); // 3 second delay for recovery
  Serial.begin(115200);

  FastLED.addLeds<STRIP_TYPE, PIN , COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);
  FastLED.setBrightness(BRIGHTNESS);
  randomSeed(analogRead(A0));
  show.addStage("Primo").addLevel().addSequence(new lsSequenceFill()).setFill(SOLID).setColor(CRGB::Green).setDuration(20*FRAMES_PER_SECOND);
  show.lastStage().addLevel().setBlendMode(lsBlendMode::COVER).addSequence(new lsSequenceGlitter(80)).setRenderEveryNFrames(10).setColor(CRGB::Red).setDuration(20*FRAMES_PER_SECOND);
  /*show.lastStage().lastLevel().addSequence(new lsFillSequence()).setFill(SOLID).setColor(CRGB::Green).setDuration(4*FRAMES_PER_SECOND);
  show.lastStage().lastLevel().addSequence(new lsFillSequence()).setFill(GRADIENT).setGradient(CRGB::Red,CRGB::Purple).setDuration(2*FRAMES_PER_SECOND);
  show.lastStage().lastLevel().addSequence(new lsFillSequence()).setFill(PALETTE).setPalette(LavaColors_p,LINEARBLEND).setDuration(4*FRAMES_PER_SECOND);
  show.lastStage().lastLevel().addSequence(new lsFillSequence()).setFill(RAINBOWCIRCULAR).setRainbowCHues(10).setDuration(2*FRAMES_PER_SECOND);
  show.lastStage().lastLevel().addSequence(new lsFillSequence()).setFill(RAINBOW).setRainbowHues(10,5).setDuration(4*FRAMES_PER_SECOND);
  show.lastStage().lastLevel().addSequence(new lsFillSequence()).setFill(PALETTECIRCULAR).setPaletteC(	OceanColors_p,LINEARBLEND).setDuration(2*FRAMES_PER_SECOND);
  //show.lastStage().addLevel();
  show.addStage("Secondo").addLevel().addSequence(new lsFillSequence()).setFill(SOLID).setColor(CRGB::Red).setDuration(10);
  show.lastStage().lastLevel().addSequence(new lsFillSequence()).setFill(SOLID).setColor(CRGB::White).setDuration(20);
  show.lastStage().lastLevel().addSequence(new lsFillSequence()).setFill(SOLID).setColor(CRGB::Red).setDuration(20);

  show.addStage("Terzo").addLevel().addSequence(new lsFillSequence()).setFill(SOLID).setColor(CRGB::Green).setDuration(10);
  show.lastStage().lastLevel().addSequence(new lsFillSequence()).setFill(SOLID).setColor(CRGB::Purple).setDuration(20);
  show.lastStage().lastLevel().addSequence(new lsFillSequence()).setFill(SOLID).setColor(CRGB::Green).setDuration(20);
*/
  show.setFPS(FRAMES_PER_SECOND);
}

void loop() {
  // put your main code here, to run repeatedly:
  show.render();

  EVERY_N_SECONDS(TIME_ON_STAGE) {
    show.nextStage();
    show.getCurrentStage().activate();
  }
}
