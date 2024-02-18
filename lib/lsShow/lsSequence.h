#ifndef LS_SEQUENCE_H
#define LS_SEQUENCE_H

#include <FastLED.h>
#include <LinkedList.h>
#include "lsStruct_Enum.h"
#include "lsStrip.h"

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

    bool _isMaskActive;
    bool _isRandom;
    bool _usePalette;
    bool _useColor;
    bool _isActive;

    lsStrip *_Strip;
    lsMask *_mask;
    CRGB _Color;
    CRGBPalette16 _Palette;
    CRGB getRandomColor();
    CRGB getColorFromPalette(int step);

  public:

    lsSequence() {
      this->_isActive = true;
      this->_isMaskActive = false;
      this->_Color = CRGB::Black;
      this->_renderEveryNFrames=1;
      this->_nextFrameRender=1;
      this->_lastFrame=0;
      this->_startAt=0;
      this->_isActive = true;
    }

    //Sostituire con CRT Pattern
    virtual lsSequence &setColor(CRGB color) {};
    virtual lsSequence &setFill(LS_FILL_TYPES fillType) {};
    virtual lsSequence &setOpacity(uint8_t opacity) {};
    virtual lsSequence &setPalette(CRGBPalette16 palette, TBlendType blending) {};
    virtual lsSequence &setPaletteC(CRGBPalette16 palette, TBlendType blending,bool reversed=false) {};
    virtual lsSequence &setPatternStrip(lsPatternStrip *stripe, uint8_t size)  {};
    virtual lsSequence &setRainbowHues(uint8_t initialhue, uint8_t deltahue=5) {};
    virtual lsSequence &setRainbowCHues(uint8_t initialhue, bool reversed=false)  {};
    virtual lsSequence &setGradient(CRGB startcolor, CRGB endcolor)  {};
    virtual void fillStrip(uint8_t currentFrame) {};

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

};

#endif