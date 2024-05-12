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
#include "lsLinkedList.h"
#include "lsStruct_Enum.h"
#include <ArduinoJson.h>
#include "lsStripComposite.h"


class lsStage;

class lsLedShow {

  private:
    lsStripComposite *_Strip;
    lsStage *_currentScene = nullptr;
    int currentStageIndex = -1; // Index of the current scene in the list;
    int _tickMillis;
    int _numLeds;
    unsigned long currentStageFrame = 0; // Frame counter for the current scene
    int fps;
    bool _isActive = true;
    uint32_t _nextTickMillis;
    LinkdList<lsStage*> _stages = LinkdList<lsStage*>();

  public:

    lsLedShow() {
      this->_Strip = new lsStripComposite();
      this->currentStageIndex   = -1;
      this->fps = 30;
      this->_tickMillis     = 1000/fps;
      this->_nextTickMillis = _tickMillis;
      this->_isActive = false;
    }

    lsLedShow& addStrip(int numLeds,int pin);

    int  getTick();
    int  getNumLeds();
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
    void shutdown();
    void flush();
    void showStrip();
    void setLeds(CRGB *newLeds);
    void setMultiStripEffect(LS_MULTIPLE_STRIPS_EFFECTS effect);


};

#endif // LEDSHOW_H