#ifndef LS_LIGHT_SHOW_H
#define LS_LIGHT_SHOW_H

#include "lsStage.h"
#include <FastLED.h>
#include <LinkedList.h>
#include "lsStruct_Enum.h"
#include "lsStrip.h"

class lsStage;

class lsLedShow {

  private:
    lsStrip *_Strip;
    lsStage *_currentScene = nullptr;
    int currentStageIndex = -1; // Index of the current scene in the list;
    int _tickMillis;
    unsigned long currentStageFrame = 0; // Frame counter for the current scene
    int fps;
    uint32_t _nextTickMillis;
    LinkedList<lsStage*> _stages = LinkedList<lsStage*>();

  public:

    lsLedShow(CRGB *leds, int numLeds) {
      this->_Strip = new lsStrip(leds, numLeds);
      this->currentStageIndex   = -1;
      this->fps = 30;
      this->_tickMillis     = 1000/fps;
      this->_nextTickMillis = _tickMillis;

      Serial.println("LedShow");
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


};

#endif // LEDSHOW_H