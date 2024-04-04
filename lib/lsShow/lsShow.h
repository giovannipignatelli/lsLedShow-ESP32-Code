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

#ifndef LS_LIGHT_SHOW_H
#define LS_LIGHT_SHOW_H

#include "lsStage.h"
#include <FastLED.h>
#include <LinkedList.h>
#include "lsStruct_Enum.h"
#include "lsStrip.h"
#include <ArduinoJson.h>


class lsStage;

class lsLedShow {

  private:
    lsStrip *_Strip;
    lsStage *_currentScene = nullptr;
    int currentStageIndex = -1; // Index of the current scene in the list;
    int _tickMillis;
    unsigned long currentStageFrame = 0; // Frame counter for the current scene
    int fps;
    bool _isActive = true;
    uint32_t _nextTickMillis;
    LinkedList<lsStage*> _stages = LinkedList<lsStage*>();

  public:

    lsLedShow(CRGB *leds, int numLeds) {
      this->_Strip = new lsStrip(leds, numLeds);
      this->currentStageIndex   = -1;
      this->fps = 30;
      this->_tickMillis     = 1000/fps;
      this->_nextTickMillis = _tickMillis;
    }

    int  getTick();
    void  setTick(int millisec);
    lsLedShow& setFPS(int fps);
    int getFPS() const { return fps; }
    void nextStage();
    void setStage(int stage);
    void render();
    lsStage &addStage(String name);
    lsStage &lastStage();
    lsStage &getStage(int num);
    lsStage &getCurrentStage();
    void serialPrintf(const char *fmt, ...);
    int getCurrentSceneIndex() const { return currentStageIndex; }
    unsigned long getCurrentSceneFrame() const { return currentStageFrame; }
    JsonDocument serialize();
    JsonDocument serializeStages();
    bool update(JsonDocument data);
    void start() {_isActive = true;};
    void stop() {_isActive = false;};


};

#endif // LEDSHOW_H