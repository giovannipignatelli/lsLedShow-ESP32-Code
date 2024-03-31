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
    uint8_t _maskEveryNFrames = 0; // if -1 mask is not present, if 0 is always on
    uint8_t _nextFrameMask;
    uint8_t _changeColorEveryNFrames=0; //if zero does not changes the color
    uint8_t _renderEveryNFrames;
    uint8_t _nextFrameColorChange;
    int repeatCount; // How many times to repeat the effect
    bool isCompleted; // Whether the effect has completed its animation
    bool _isMaskOn = false;

    lsStrip *_Strip;
    lsMask *_mask;
    lsLevel *parentLevel;
    uint8_t gHue = 0; // rotating "base color" used by many of the sequences
    CRGB _Color = CRGB::Red;
    CRGBPalette16 _Palette = RainbowColors_p;
    CRGB getColorFromPalette(int step);

    CRGB getRandomColor();

    CRGB _EndColor;
    TBlendType    _Blending = TBlendType::LINEARBLEND;
    lsPatternStrip *_stripes;
    uint8_t   _stripesSize;
    uint8_t _initialhue;
    uint8_t _deltahue;
    bool _reversed;
    LS_SEQUENCE_COLORING _Coloring = LS_SEQUENCE_COLORING::RANDOMCOLOR;

  public:

    lsSequence() {
      this->_Color = CRGB::Black;
      this->_renderEveryNFrames=1;
      this->_nextFrameRender=0;
      this->_lastFrame=0;
      this->_startAt=0;
      this->isCompleted = false;
    }

    //Sostituire con CRT Pattern
    lsSequence &setColor(CRGB color);
    lsSequence &setColoring (LS_SEQUENCE_COLORING coloring);
    virtual lsSequence &setFill(LS_FILL_TYPES fillType) {};
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

	  lsSequence &setStrip(lsStrip *Strip);
    lsSequence &setRenderEveryNFrames(int frames);
    lsSequence &setChangeColorEveryNFrames(int frames);
    lsSequence &startAt(int frame);
    lsSequence &setDuration(int frames);
    lsSequence &setMask(lsMask *mask, uint8_t maskSize, int activateEveryNFrames = 0);
    void applyMask(uint8_t frame);
    void updateColor(unsigned long frame);
    CRGB *getLeds();
    lsStrip *getStrip();
    lsSequence& setParentLevel(lsLevel* level);
    int getLastFrame() { return _lastFrame;};


    virtual void preRender() {};
    virtual void postRender() {};
    virtual void update(unsigned long frame) {};

    // Derived classes will implement draw to render the effect based on updated parameters
    virtual void draw(unsigned long frame) {};

};

#endif