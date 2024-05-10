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


#ifndef LS_STAGE_H
#define LS_STAGE_H

#include <FastLED.h>
#include "lsLinkedList.h"

#include "lsStruct_Enum.h"
#include "lsLevel.h"
#include "lsShow.h"
#include <ArduinoJson.h>

class lsLedShow;
class lsLevel;

class lsStage {
  
  private:
  String _name;
  uint8_t _currentFrame;
  uint8_t _duration;
  LinkdList<lsLevel*> _levels = LinkdList<lsLevel*>();
  lsLedShow* parentShow; // Pointer to the parent LedShow
  unsigned long startAt; // Frame to start the scene
  unsigned long repeatCount; // How many times to repeat the scene
  unsigned long currentRepeat; // Current repeat iteration
  unsigned long frameCounter; // Frame counter for timing within the scene
	bool allLayersCompleted;
  
  public:

    bool _isActive;

    lsStage(String name, uint8_t duration=0) {
      this->_name = name;
      this->_duration = duration;
      this->repeatCount = 1;
      this->currentRepeat = 0;
      this->startAt = 0;
    }
    String getName(){return _name;}
    lsLevel &addLevel ();
    lsLevel &lastLevel ();
    lsLevel &getLevel (uint8_t num);
    void printLeds(CRGB* displayLeds, int number);
    lsStage &setRepeat (unsigned long repeatCount);
    lsStage &setStartAt (unsigned long startAt);

    void reset();
    void render(unsigned long currentFrame);
    void mergeLevels();
    void updateState();
	  void checkLayersCompletion();

    JsonDocument serialize();
    JsonDocument serializeSimple();
    lsStage& setParentShow(lsLedShow* show);

};

#endif