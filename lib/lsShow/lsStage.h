#ifndef LS_STAGE_H
#define LS_STAGE_H

#include <FastLED.h>
#include <LinkedList.h>
#include "lsStruct_Enum.h"
#include "lsLevel.h"
#include "lsShow.h"

class lsLedShow;
class lsLevel;

class lsStage {
  
  private:
  lsStrip *_Strip;
  String _Name;
  uint8_t _currentFrame;
  uint8_t _duration;
  LinkedList<lsLevel*> _levels = LinkedList<lsLevel*>();
  lsLedShow* parentShow; // Pointer to the parent LedShow
  unsigned long startAt; // Frame to start the scene
  unsigned long repeatCount; // How many times to repeat the scene
  unsigned long currentRepeat; // Current repeat iteration
  unsigned long frameCounter; // Frame counter for timing within the scene
	bool allLayersCompleted;
  
  public:

    bool _isActive;

    lsStage(String name,lsStrip *_Strip, uint8_t duration=0) {
      this->_Strip = _Strip;
      this->_Name = name;
      //this->_isActive = false;
      this->_duration = duration;
      this->repeatCount = 1;
      this->currentRepeat = 0;
      this->startAt = 0;
    }
    String getName(){return _Name;}
    lsLevel &addLevel ();
    lsLevel &lastLevel ();
    lsLevel &getLevel (uint8_t num);
    void printLeds(CRGB* displayLeds, int number);
    lsStage &setRepeat (unsigned long repeatCount);
    lsStage &setStartAt (unsigned long startAt);

    void reset();
    void render(unsigned long currentFrame);
    void mergeLevels();
    //void activate() ;
    //void deactivate() ;

    void updateState();

	  void checkLayersCompletion();


    lsStage& setParentShow(lsLedShow* show);

};

#endif