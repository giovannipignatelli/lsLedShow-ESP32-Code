#include <Arduino.h>
#include <FastLED.h>
#include <LinkedList.h>

#include "advancedSerial.h"

#define NUM_LEDS 120
#define NUM_STRIPS 1
#define NUM_SCENES 5 
#define STRIP_TYPE WS2812
#define COLOR_ORDER GRB
#define PIN 14
#define BUTTON 2
#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  5
#define TIME_ON_STAGE      10
#define FRAMES_PER_SECOND_FIRE 60

#include "lsStrip.h"
#include "lsSequence.h"
#include "lsLevel.h"
#include "lsStage.h"
#include "lsShow.h"
#include "lsStruct_Enum.h"
#include "lsSequences.h"


CRGB leds[NUM_LEDS];

extern lsMask evenMask_m[] = {{1,1},{0,1}};
extern lsMask oddMask_m[] =  {{0,1},{1,1}};
extern lsMask oddityMask_m[] = {{0,2},{1,2}};
extern lsPatternStrip pattern_p[] = { {CRGB::White , 5},{CRGB::Yellow , 5},{CRGB::Blue, 4},{CRGB::Green, 2},  {CRGB::Red, 2}};

lsLedShow show(leds,NUM_LEDS);

void setup() {
  delay(3000); // 3 second delay for recovery
  Serial.begin(115200);
  aSerial.setPrinter(Serial);
  aSerial.setFilter(Level::vv);

  FastLED.addLeds<STRIP_TYPE, PIN , COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);
  FastLED.setBrightness(BRIGHTNESS);
  randomSeed(analogRead(A0));
 show.addStage("Primo").setStartAt(5).addLevel();//.addSequence(new lsFillSequence()).setFill(SOLID).setColor(CRGB::Blue);
//  lsLedShow.addStage("Primo").addTrack(new lsFillTrack()).setFill(GRADIENT).setGradient(CRGB::Black,CRGB::Red);
  //lsLedShow.lastStage().addTrack(new lsMaskTrack()).setMask(oddityMask_m,2);
  //lsLedShow.lastStage().addTrack(new lsFilterBlur(100));
  //lsLedShow.addStage("Secondo").addTrack(new lsFillTrack()).setFill(PALETTE).setPalette(LavaColors_p,LINEARBLEND);
  //lsLedShow.addStage("Terzo").addTrack(new lsFillTrack()).setFill(RANDOM);
  //lsLedShow.addStage("Q").addTrack(new lsFillTrack()).setFill(RAINBOW).setRainbowHues(10,5);
  //lsLedShow.addStage("Qu").addTrack(new lsFillTrack()).setFill(RAINBOWCIRCULAR).setRainbowCHues(10); // DA CAPIRE COSA NN VA oddityMask_m
  //lsLedShow.addStage("B").addTrack(new lsFillTrack()).setFill(RAINBOWCIRCULAR).setRainbowCHues(10,true).setMask(oddMask_m,2);
  //lsLedShow.addStage("Qu").addTrack(new lsFillTrack()).setFill(PALETTECIRCULAR).setPaletteC(	OceanColors_p,LINEARBLEND);
  //lsLedShow.addStage("Qu").addTrack(new lsFillTrack()).setFill(PATTERN).setPatternStrip(pattern_p,5).setMask(oddityMask_m,4);
  //lsLedShow.addStage("Terzo").addTrack().addPattern(new lsBarPattern()).setPalette(LavaColors_p).setDuration(20);
  //lsLedShow.addStage("Secondo").addTrack().addPattern(new lsFillPattern()).setRandom().startAt(10).setDuration(20);
  //.addPattern(new lsFillPattern()).setColor(CRGB::Red).setDuration(120);
  //lsLedShow.lastStage().lastTrack().addPattern(new lsFillPattern()).setColor(CRGB::Blue).setDuration(120);
  //lsLedShow.lastStage().lastTrack().addPattern(new lsFillPattern()).setColor(CRGB::White).setDuration(120);
  //lsLedShow.lastStage().lastTrack().addPattern(new lsBarPattern()).setColor(CRGB::Green).setDuration(120);
  //lsLedShow.lastStage().addTrack().addPattern(new lsBarPattern()).setColor(CRGB::Blue).setDuration(10);
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
