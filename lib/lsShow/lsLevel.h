#ifndef LS_LEVEL_H
#define LS_LEVEL_H

#include <FastLED.h>
#include <LinkedList.h>
#include "lsStruct_Enum.h"
#include "lsSequence.h"
#include "lsStrip.h"
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
    
    int numLeds;
    LS_BLENDMODE blendMode;

  public:

    

    lsLevel(int size) {
      CRGB* buffer = new CRGB[size];
      for (int i = 0; i< size; i++) buffer[i]=CRGB::Black;
      this->_Strip = new lsStrip(buffer, size);
      this->_Strip->drawColor(CRGB::Black);
      this->_current_sequence = 0;
      this->blendMode = LS_BLENDMODE::ADD;
      completed = false;
      numLeds = size;
      _opacity = 1.0f;
    }

    CRGB *getLeds();
	
    lsLevel &setOpacity(float newOpacity);
    lsLevel &setBlendMode(LS_BLENDMODE blendMode) {this->blendMode = blendMode;return *this;};
    void printLeds(CRGB* displayLeds, int number);
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

    void sequenceCompleted(uint8_t currentFrame);

    bool isCompleted()  { return completed; }

    lsLevel& setParentStage(lsStage* stage);



};

#endif