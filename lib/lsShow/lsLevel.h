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

#ifndef LS_LEVEL_H
#define LS_LEVEL_H

#include <FastLED.h>
#include "lsLinkedList.h"
#include <ArduinoJson.h>
#include "lsStruct_Enum.h"
#include "lsSequence.h"

#include "lsStrip.h"
#include "lsStage.h"

#define SPRINTLEVEL_STATUS            \
  Serial.print("Current Sequence: "); \
  Serial.print(_current_sequence);

class lsStage;
class lsSequence;

class lsLevel
{

protected:
  LinkdList<lsSequence *> _sequences = LinkdList<lsSequence *>();
  float _opacity;
  uint8_t _current_sequence;
  lsStrip *_Strip;
  lsStage *parentStage;
  bool completed;

  LS_BLENDMODE _blendMode;

public:
  lsLevel(int size)
  {
    Serial.print("Size");Serial.println(size);
    CRGB *buffer = new CRGB[size];
    for (int i = 0; i < size; i++)
      buffer[i] = CRGB::Black;
    this->_Strip = new lsStrip(size);
    this->_Strip->drawColor(CRGB::Black);
    this->_current_sequence = 0;
    this->_blendMode = LS_BLENDMODE::ADD;
    completed = false;
    _opacity = 1.0f;
  }

  CRGB *getLeds();

  lsLevel &setOpacity(float newOpacity);
  lsLevel &setBlendMode(LS_BLENDMODE blendMode)
  {
    this->_blendMode = blendMode;
    return *this;
  };
  void printLeds(CRGB *displayLeds, int number);
  lsSequence &addSequence(lsSequence *seq);
  lsSequence &lastSequence();
  lsSequence &getSequence(int num);
  lsSequence &getNextSequence();

  void (lsLevel::*fusion)(CRGB *targetLayer);
  void blendLevels(CRGB *ledStripBuffer);
  void mergeAdd(CRGB *targetLayer);
  void mergeSubtract(CRGB *targetLayer);
  void mergeUp(CRGB *targetLayer);
  void mergeDown(CRGB *targetLayer);
  void mergeBlend(CRGB *targetLayer);
  void render(unsigned long currentFrame);
  void reset();

  void sequenceCompleted(unsigned long currentFrame);

  bool isCompleted() { return completed; }

  lsLevel &setParentStage(lsStage *stage);

  JsonDocument serialize();

  static lsSequence getSequence(LS_SEQUENCES_TYPES type);
};

#endif