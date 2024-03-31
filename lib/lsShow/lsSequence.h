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
 * The lsSequence class represents a sequence of lighting effects and transitions
 * for LED strips. It includes methods for rendering the sequence, setting colors, and
 * managing transitions, among other functionalities.
 */

#ifndef LS_SEQUENCE_H
#define LS_SEQUENCE_H

#define STRIP_LEDS(i)             this->_Strip->getLeds()[i]
#define STRIP_NUM_LEDS            this->_Strip->getNumLeds()
#define STRIP_CLEAR               this->_Strip->clear();
#define SEQUENCE_PRIMARY_COLOR    this->_PrimaryColor
#define SEQUENCE_SECONDARY_COLOR  this->_SecondaryColor
#define SEQUENCE_TERTIARY_COLOR   this->_TertiaryColor
#define GETRANDOMCOLOR            lsColorutils::getRandomColor()
#define GETPALETTECOLOR(x)        lsColorutils::getColorFromPalette(this->_Palette, this->_Blending, x )
#define GETCOLORWHEEL(x)          lsColorutils::getColorWheel(x)
#define ISCOMPLETED(x)            !(((x <= this->_lastFrame ) && (_duration>0)) || ((SEQUENCE_RUN<=_repeatCount ) && (_duration==0)))

#define SEQUENCE_HUE              this->_gHue
#define INCREASE_SEQUENCE_HUE     this->_gHue++
#define RESET_HUE                 this->_gHue = 0;

#define SEQUENCE_OFFSET           this->_offSet
#define INCREASE_SEQUENCE_OFFSET  this->_offSet++
#define RESET_OFFSET              this->_offSet = 0;

#define SEQUENCE_RUN              this->_runs
#define INCREASE_SEQUENCE_RUN     this->_runs++
#define RESET_RUNS                this->_runs = 0;

#define RESET_NEXT_RENDER_FRAME   this->_nextFrameRender=this->_startAt + this->_renderEveryNFrames-1;
#define RESET_NEXT_COLOR_FRAME   this->_nextFrameColorChange =this->_startAt + _changeColorEveryNFrames-1;
#define RESET_NEXT_MASK_FRAME   this->_startAt + this->_changeMaskEveryNFrames;

#define SPRINT(x)      Serial.print(x);
#define SPRINTLN(x)    Serial.println(x);
#define SPRINTLN       Serial.println("");
#define SPRINTCOUPLE(x,y)    Serial.print(x);Serial.print(y);
#define SPRINTINFOSEQUENCE Serial.print("\tStart: ");Serial.print(_startAt);Serial.print("\tDuration: ");Serial.print(_duration);Serial.print("\tLast: ");Serial.print(_lastFrame);\
                          Serial.print("\tRepeat: ");Serial.print(_repeatCount);Serial.print("\tCurrent Run: ");Serial.print(_runs);\
                          Serial.print("\tCR: ");Serial.print(frame);Serial.print("\tRender Every: ");Serial.print(_renderEveryNFrames);Serial.print("\tNext Frame Render: ");Serial.print(_nextFrameRender);Serial.print("\tChange Color every: ");Serial.print(_changeColorEveryNFrames);\
                          Serial.println("");


#include <FastLED.h>
#include <LinkedList.h>
#include <ArduinoJson.h>
#include "lsStruct_Enum.h"
#include "lsStrip.h"
#include "lsLevel.h"
#include "lsTransitions.h"
#include "lsColorUtils.h"

// Forward declaration of lsLevel to resolve circular dependency
class lsLevel;
/// @brief 
class lsSequence {

  protected:

    uint8_t *_maskStrip;          // Mask array for the sequence

    // Timing and rendering variables

    uint32_t 
      _startAt,                         // Frame to start the sequence
      _lastFrame,                       // Last Rendering Frame 
      _duration,                        // Duration of the sequence in frames, if duration is 0 the numeber of runs will drive the end of the sequence
      _nextFrameRender,                 // The next Frame the sequence will be rendered, works in couple with _renderEveryNFrames
      _renderEveryNFrames,              // The frequency of rendering, works in couple with _nextFrameRender
      _maskSize = 0,                    // Size of the mask array
      _changeMaskEveryNFrames = -1,     // Frequency to change the mask, if -1 mask is not present, if 0 is always on
      _nextFrameMaskChange,             // Next frame to change the mask
      _changeColorEveryNFrames=0,       // Frequency to change the color, if zero does not changes the color, if -1 changes at every run
      _nextFrameColorChange,            // Next frame to change the color
      _gHue = 0,                        // Current hue used for generating colors, is a rotating "base color" used by many of the sequences
      _offSet,                          // Offset used for moving effects, offset Counter used by many of the sequences for movements
      _currentPosition,                 // Current position used for positioning effects, used by many of the sequences for movements
      _blockSize,                       // Size of blocks for block-based effects. Size of pixel blocks, used by many of the sequences for movements of pixels and bars
      _stripesSize = 0,                     // Size of stripes for stripe-based effects
      _initialhue,                      // Initial hue for rainbow effects
      _deltahue,                        // Delta hue for rainbow effects
      _minPosition,                     // Minimum position for positioning effects
      _maxPosition,                     // Maximum position for positioning effects
      _minStripLed,                     // Minimum LED index for the strip
      _maxStripLed;                     // Maximum LED index for the strip

    // Color update command structure, {updatePrimaryColor, updateSecondaryColor, updateTertiaryColor} works in tandem with _changeColorEveryNFrames
    LS_COLOR_UPDATE _updateCommand = {true, true,true};
    LS_SEQUENCES_TYPES _type;

  // Counters and state variables
    uint8_t 
      _repeatCount,             // How many times to repeat the effect, if 0 repeat until the end of the sequence duration
      _runs;                    // How many times the effect has been repeated
    
    bool 
      _isMaskOn = false,        // States if the Mask is on
      _isReversed = false,      // States if the strip has been flipped
      _isMirrored = false,      // States if the strip has activated a mirror effect
      _statusA,                 // General Purpose bool val to be used by many effects  
      _statusB;                 // General Purpose bool val to be used by many effects 

 // Pointers to the strip and mask objects
    lsStrip *_Strip;
    LS_MASK *_mask;
    lsLevel *parentLevel;

// Primary, secondary, and tertiary colors for the sequence  
    CRGB 
      _PrimaryColor = CRGB::Red,
      _SecondaryColor = CRGB::Black,
      _TertiaryColor = CRGB::Black;
    
    CRGB * _bufferLeds;

// Color palette and blending type for the sequence
    LS_PALETTES   _paletteConst = LS_PALETTES::RainbowColors_p;
    CRGBPalette16 _Palette = RainbowColors_p;
    TBlendType    _Blending = TBlendType::LINEARBLEND;
// Pattern strip array for pattern-based effects   
    LS_PATTERN_STRIP *_stripes;
// Fill type for color filling effects
    LS_FILL_TYPES _Coloring = LS_FILL_TYPES::RANDOMSOLID;

// Methods to check bounds and set positions
    bool _inBounds(uint16_t pos);
    long  getPosition(uint16_t pos);
    long  getReflectionPosition(uint16_t pos);
    void setPositionBounds();

// In and out Transition Effects
    lsTransition *_transitionIn;
    lsTransition *_transitionOut;


// Public methods for sequence configuration and rendering
  public:

    lsSequence() {
      this->_renderEveryNFrames=1;
      this->_changeColorEveryNFrames=0;
      this->_changeMaskEveryNFrames = -1;
      this->_nextFrameRender=0;
      this->_lastFrame=0;
      this->_startAt=0;
      this->_PrimaryColor = CRGB::Red;
      this->_SecondaryColor = CRGB::Black;
      this->_TertiaryColor = CRGB::Black;
      this->_blockSize = 1;
      this->_duration = 0;
      this->_repeatCount = 1;
      this->_runs = 0;
      this->_updateCommand = {true, true,true};
      this->_transitionIn = nullptr;
      this->_transitionOut = nullptr;
      this->_isMaskOn = false;
    }

    //Sostituire con CRT Pattern
    lsSequence &setColors(CRGB color, CRGB colorS = CRGB::Black, CRGB colorT = CRGB::Black);
    lsSequence &setColoring (LS_FILL_TYPES fillType);
    lsSequence &setPalette(LS_PALETTES palette, TBlendType blending);
    lsSequence &setPaletteC(LS_PALETTES palette, TBlendType blending,bool reversed=false);
    lsSequence &setPatternStrip(LS_PATTERN_STRIP *stripe, uint8_t size);
    lsSequence &setRainbowHues(uint8_t initialhue, uint8_t deltahue=5);
    lsSequence &setRainbowCHues(uint8_t initialhue, bool reversed=false);
    lsSequence &setGradient(CRGB startcolor, CRGB endcolor);

    lsSequence &setReverseOn() {this->_isReversed = true; setPositionBounds();return *this;}
    lsSequence &setReverseOff() {this->_isReversed = false;setPositionBounds();return *this;}
    lsSequence &setMirrorOn() {this->_isMirrored = true;setPositionBounds();return *this;}
    lsSequence &setMirrorOff() {this->_isMirrored = false;setPositionBounds();return *this;}
    lsSequence &setBlockSize(int size) {this->_blockSize = size;return *this;}
	  lsSequence &setStrip(lsStrip *Strip);
    lsSequence &setRenderEveryNFrames(uint32_t frames);
    lsSequence &setChangeColorEveryNFrames(uint32_t frames, LS_COLOR_UPDATE command = {true, true,true});
    lsSequence &setChangeColorEveryRun(LS_COLOR_UPDATE command = {true, true,true});
    lsSequence &setRepeat(unsigned long repeatCount);
    lsSequence &startAt(uint32_t frames);
    lsSequence &setDuration(uint32_t frames);
    lsSequence &setMask(LS_MASK *mask, uint8_t maskSize, int activateEveryNFrames = 0);
    lsSequence &setParentLevel(lsLevel* level);
    lsSequence &setTransitionIn(lsTransition *transition);
    lsSequence &setTransitionOut(lsTransition *transition);

    void printLeds(CRGB *ledsToPrint);

    void render(unsigned long frame);

    virtual void getFirstFrameRender(CRGB * leds) {};

    virtual void privateRender(unsigned long frame);
    bool isCompleted(unsigned long frame) {return ISCOMPLETED(frame);};
    void printInfo(unsigned long frame) { SPRINTINFOSEQUENCE;};
    bool hasTransitionIn() {return _transitionIn != nullptr;};
    bool hasTransitionOut() {return _transitionOut != nullptr;};

    // Derived classes will implement these functions draw to render the effect based on updated parameters
    virtual void preRender() {};
    virtual void postRender() {};
    virtual void update(unsigned long frame) {};
    virtual void draw(unsigned long frame) {};
    void updateMask(unsigned long frame);
    void updateColors(unsigned long frame);
    void updateColors();
    void setPixel(uint16_t position, CRGB color);
    void setPixel(uint16_t position, CHSV color);
    void reset();

    void fillSolid();
    void fillRandom();
    void fillRandomSingle();
    void fillPalette();
    void fillPaletteC();
    void fillPattern();
    void fillRainbow();
    void fillRainbowC();
    void fillGradient();

    //Functions for grouping sequnces (used by lsSequencegroup.h)

    virtual lsSequence &addSequence(lsSequence *seq) {};
    virtual lsSequence &addSequence(lsSequence *seq,uint16_t min,uint16_t max) {};
    virtual lsSequence &setSegmentBounds(uint16_t min,uint16_t max) {this->_minStripLed=min;this->_maxStripLed=max;}
    virtual lsSequence &lastSequence() {};
    virtual lsSequence &getSequence(int num) {};

    CRGB *getLeds();
    lsStrip *getStrip();

    int getLastFrame() { return _lastFrame;};
    void print(CRGB color);

    JsonDocument serialize();
    JsonDocument serializeMask();
    JsonDocument serializeStrip();


};

#endif