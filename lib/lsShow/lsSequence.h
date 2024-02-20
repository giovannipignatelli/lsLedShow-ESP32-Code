#ifndef LS_SEQUENCE_H
#define LS_SEQUENCE_H

#include <FastLED.h>
#include <LinkedList.h>
#include "lsStruct_Enum.h"
#include "lsStrip.h"
#include "lsLevel.h"

class lsLevel;
/// @brief 
class lsSequence {

  protected:

    uint8_t _startAt;
    uint8_t _lastFrame;
    uint8_t _duration;
    uint8_t _nextFrameRender;
    uint8_t *_maskStrip;
    uint8_t _maskSize;
    uint8_t _renderEveryNFrames;
    int repeatCount; // How many times to repeat the effect
    bool isCompleted; // Whether the effect has completed its animation

    bool _isMaskActive;
    bool _isRandom;
    bool _usePalette;
    bool _useColor;
    bool _isActive;

    lsStrip *_Strip;
    lsMask *_mask;
    lsLevel *parentLevel;
    uint8_t gHue = 0; // rotating "base color" used by many of the patterns
    CRGB _Color;
    CRGBPalette16 _Palette;
    CRGB getColorFromPalette(int step);

    CRGB getRandomColor();

    CRGB _EndColor;
    TBlendType    _Blending;
    lsPatternStrip *_stripes;
    uint8_t   _stripesSize;
    uint8_t _initialhue;
    uint8_t _deltahue;
    bool _reversed;

  public:

    lsSequence() {
      this->_isActive = true;
      this->_isMaskActive = false;
      this->_Color = CRGB::Black;
      this->_renderEveryNFrames=1;
      this->_nextFrameRender=0;
      this->_lastFrame=0;
      this->_startAt=0;
      this->_isActive = true;
      this->isCompleted = false;
    }

    //Sostituire con CRT Pattern
    lsSequence &setColor(CRGB color);
    lsSequence &setFill(LS_FILL_TYPES fillType) {};
    lsSequence &setPalette(CRGBPalette16 palette, TBlendType blending);
    lsSequence &setPaletteC(CRGBPalette16 palette, TBlendType blending,bool reversed=false);
    lsSequence &setPatternStrip(lsPatternStrip *stripe, uint8_t size);
    lsSequence &setRainbowHues(uint8_t initialhue, uint8_t deltahue=5);
    lsSequence &setRainbowCHues(uint8_t initialhue, bool reversed=false);
    lsSequence &setGradient(CRGB startcolor, CRGB endcolor);
    //virtual void fillStrip(uint8_t currentFrame) {};

    void reset();
    void printLeds(CRGB *ledsToPrint);
    void render(uint8_t currentFrame) ;

    lsSequence &activateMask();
    lsSequence &deactivateMask();
	  lsSequence &setStrip(lsStrip *Strip);
    lsSequence &setRenderEveryNFrames(int frames);
    lsSequence &startAt(int frame);
    lsSequence &setDuration(int frames);
    lsSequence &setMask(lsMask *mask, uint8_t maskSize);
    lsSequence &applyMask();
    CRGB *getLeds();
    lsStrip *getStrip();
    lsSequence& setParentLevel(lsLevel* level);
    int getLastFrame() { return _lastFrame;};

    virtual void update(unsigned long frame) {};

    // Derived classes will implement draw to render the effect based on updated parameters
    virtual void draw(unsigned long frame) {};

};

#endif