#ifndef LS_LEVEL_H
#define LS_LEVEL_H

#include <FastLED.h>
#include <LinkedList.h>
#include "lsStruct_Enum.h"
#include "lsSequence.h"
#include "lsStrip.h"
#include "lsBlendMode.h"
#include "lsStage.h"

class lsStage;
class lsSequence;

class lsLevel {
 
  protected:
    LinkedList<lsSequence*> _sequences = LinkedList<lsSequence*>();
    float _opacity;
    uint8_t _current_sequence;
    lsStrip *_Strip;
    lsStage *parentStage;
    bool completed;
    CRGB* buffer;
    int numLeds;
    lsBlendMode blendMode;

  public:

    

    lsLevel(int size) {
      buffer = new CRGB[size];
      this->_Strip = new lsStrip(buffer, size);
      this->_current_sequence = 0;
      this->blendMode = lsBlendMode::ADD;
      //memset(buffer, 0, sizeof(CRGB) * numLeds);
      completed = false;
      numLeds = size;
      _opacity = 1.0f;
    }

    CRGB *getLeds();
	
    lsLevel &setOpacity(float newOpacity);
    lsLevel &setBlendMode(lsBlendMode blendMode);

    lsSequence &addSequence(lsSequence *seq);
    lsSequence &lastSequence();
    lsSequence &getSequence(int num);

    void (lsLevel::*fusion)(CRGB *targetLayer);
    void blendLevels(CRGB* ledStripBuffer);
    void mergeAdd(CRGB *targetLayer) ;
    void mergeSubtract(CRGB *targetLayer) ;
    void mergeUp(CRGB *targetLayer) ;
    void mergeDown(CRGB *targetLayer) ;
    void mergeBlend(CRGB *targetLayer);
    void render(uint8_t currentFrame);
    void reset();

    void effectCompleted();

    bool isCompleted()  { return completed; }

    lsLevel& setParentStage(lsStage* stage);



};

#endif