#include <FastLED.h>
#include <LinkedList.h>
#include "lsStruct_Enum.h"
#include "lsSequence.h"
#include "lsStrip.h"
#include "lsLevel.h"

#include "lsColorUtils.h"

#define STRIP_NUM_LEDS this->_Strip->getNumLeds()

#define SPRINTINFOTRANSITION Serial.print("\tStart: ");Serial.print(_startAt);Serial.print("\tDuration: ");Serial.print(_duration);Serial.print("\tLast: ");\
                          Serial.print("\tCR: ");Serial.print(currentFrame);Serial.print("\tRender Every: ");Serial.print(_renderEveryNFrames);\
                          Serial.println("");


class lsTransition {
private:
    LS_TRANSITION_TYPES _type;
    unsigned long _duration; // Duration of the transition in frames
    unsigned long _startAt = -1; // The frame at which the transition starts
    unsigned long _step    = 0; // The frame at which the transition starts
    unsigned long _renderEveryNFrames = 1; // Duration of one on/off cycle in frames
    CRGB _transitionColor; // Target color for the transition
    CRGB *_targetFirstRenderedLeds; // Target color array for the transition
    bool _isOn = true;

 // Pointers to the strip and mask objects
    lsStrip *_Strip;

public:
    lsTransition(LS_TRANSITION_TYPES type, unsigned long duration,CRGB Color = CRGB::Red)
        : _type(type), _duration(duration), _startAt(-1), _transitionColor(Color) {
        }

    lsTransition &setStrip(lsStrip *Strip){
      this->_Strip = Strip;
      return *this;
    }

    void reset(){
        _startAt = -1;
        _step = 0;
        _isOn = true;
        _renderEveryNFrames = 1;
    }

    bool isCompleted(unsigned long currentFrame){
        if (_startAt == 4294967295 ) {
            _startAt = currentFrame;
        }
        unsigned long elapsedFrames = currentFrame - _startAt;
        float progress = min(1.0f, static_cast<float>(elapsedFrames) / _duration);
        return (progress == 1.0f);
    }

    int getDuration() {return this->_duration;}

    // Update the transition effect on the LEDs for the current frame
    void update(unsigned long currentFrame, CRGB* newTargetColors) {
        
        _targetFirstRenderedLeds = newTargetColors;
        // Calculate progress as a percentage
        unsigned long elapsedFrames = currentFrame - _startAt;
        float progress = min(1.0f, static_cast<float>(elapsedFrames) / _duration);
        int position = static_cast<int>(progress * STRIP_NUM_LEDS); // Calculate position based on progress
        int midPoint = STRIP_NUM_LEDS / 2;
        int sizeIncreaseDecrease = (sqrt16((4*_duration)-1))/2;
        int doorsWidth = static_cast<int>(progress * midPoint); // Width of each door based on progress

        float intervalProgress; 
        unsigned long currentBlinkInterval;

        // Apply the transition effect based on the type
        switch (_type) {
            case LS_TRANSITION_TYPES::FadeIn:
                nblend(this->_Strip->getLeds(),_targetFirstRenderedLeds,STRIP_NUM_LEDS,progress*255);
                break;
            case LS_TRANSITION_TYPES::FadeOut:
                for (int i = 0; i < STRIP_NUM_LEDS; ++i) {
                    this->_Strip->getLeds()[i].fadeToBlackBy(255 * progress);
                }
                break;
            case LS_TRANSITION_TYPES::WipeLeft:
                for (int i = 0; i < STRIP_NUM_LEDS; ++i) {
                    if (i < STRIP_NUM_LEDS * progress) {
                        // Turn off LEDs from the start to the progress point
                        this->_Strip->getLeds()[i] = CRGB::Black;
                    }
                }
                break;
            case LS_TRANSITION_TYPES::WipeRight:
                for (int i = STRIP_NUM_LEDS - 1; i >= 0; --i) {
                    if (i > STRIP_NUM_LEDS * (1 - progress)) {
                        // Turn off LEDs from the end to the progress point
                        this->_Strip->getLeds()[i] = CRGB::Black;
                    }
                }
                break;
            case LS_TRANSITION_TYPES::SlideLeft:
                // Slide In from the right to left
                for (int i = 0; i < position; ++i) {
                    this->_Strip->getLeds()[i] = this->_targetFirstRenderedLeds[STRIP_NUM_LEDS -position + i];
                }
                break;
            case LS_TRANSITION_TYPES::SlideRight:
                // Slide Out from left to right
                for (int i = STRIP_NUM_LEDS - position; i < STRIP_NUM_LEDS; ++i) {
                    this->_Strip->getLeds()[i] =  this->_targetFirstRenderedLeds[i];
                }
                break;
            case LS_TRANSITION_TYPES::IrisIn:
                // Iris In from center to edges
                for (int i = 0; i < STRIP_NUM_LEDS / 2; ++i) {
                    if (i < position) {
                        this->_Strip->getLeds()[STRIP_NUM_LEDS / 2 + i] =  this->_targetFirstRenderedLeds[STRIP_NUM_LEDS / 2 + i];
                        this->_Strip->getLeds()[STRIP_NUM_LEDS / 2 - i] =  this->_targetFirstRenderedLeds[STRIP_NUM_LEDS / 2 - i];
                    }
                }
                break;
            case LS_TRANSITION_TYPES::IrisInSolid:
                // Iris In from center to edges
                for (int i = 0; i < STRIP_NUM_LEDS / 2; ++i) {
                    if (i < position) {
                        this->_Strip->getLeds()[STRIP_NUM_LEDS / 2 + i] =  this->_transitionColor;
                        this->_Strip->getLeds()[STRIP_NUM_LEDS / 2 - i] =  this->_transitionColor;
                    }
                }
                break;
            case LS_TRANSITION_TYPES::IrisOut:
                // Iris Out from edges to center
                for (int i = 0; i < STRIP_NUM_LEDS / 2; ++i) {
                    if (i < position) {
                        this->_Strip->getLeds()[i] =  this->_targetFirstRenderedLeds[i];
                        this->_Strip->getLeds()[STRIP_NUM_LEDS - i - 1] =  this->_targetFirstRenderedLeds[STRIP_NUM_LEDS - i - 1];
                    }
                }
                break;
            case LS_TRANSITION_TYPES::IrisOutSolid:
                // Iris Out from edges to center
                for (int i = 0; i < STRIP_NUM_LEDS / 2; ++i) {
                    if (i < position) {
                        this->_Strip->getLeds()[i] =  this->_transitionColor;
                        this->_Strip->getLeds()[STRIP_NUM_LEDS - i - 1] =  this->_transitionColor;
                    }
                }
                break;
            case LS_TRANSITION_TYPES::DissolveIn:
                for (int i = 0; i < STRIP_NUM_LEDS; ++i) {
                    // Assuming leds[i] contains the current color, blend towards the target color based on progress
                    this->_Strip->getLeds()[i].r = this->_Strip->getLeds()[i].r + ((this->_targetFirstRenderedLeds[i].r - this->_Strip->getLeds()[i].r) * progress);
                    this->_Strip->getLeds()[i].g = this->_Strip->getLeds()[i].g + ((this->_targetFirstRenderedLeds[i].g - this->_Strip->getLeds()[i].g) * progress);
                    this->_Strip->getLeds()[i].b = this->_Strip->getLeds()[i].b + ((this->_targetFirstRenderedLeds[i].b - this->_Strip->getLeds()[i].b) * progress);
                }
                break;
            case LS_TRANSITION_TYPES::CrossDissolve:
                for (int i = 0; i < STRIP_NUM_LEDS/4; ++i) {
                    int pos = random(0,STRIP_NUM_LEDS);
                    if (random8(10)>5){
                        this->_Strip->getLeds()[pos].r = this->_Strip->getLeds()[pos].r + ((this->_targetFirstRenderedLeds[pos].r - this->_Strip->getLeds()[pos].r) * progress);
                        this->_Strip->getLeds()[pos].g = this->_Strip->getLeds()[pos].g + ((this->_targetFirstRenderedLeds[pos].g - this->_Strip->getLeds()[pos].g) * progress);
                        this->_Strip->getLeds()[pos].b = this->_Strip->getLeds()[pos].b + ((this->_targetFirstRenderedLeds[pos].b - this->_Strip->getLeds()[pos].b) * progress);
                        }                
                    }
                break;
            case LS_TRANSITION_TYPES::WhiteDissolve:
                for (int i = 0; i < STRIP_NUM_LEDS/4; ++i) {
                    int pos = random(0,STRIP_NUM_LEDS);
                    if (random8(10)>5){
                        this->_Strip->getLeds()[pos].r = this->_Strip->getLeds()[pos].r + 255;
                        this->_Strip->getLeds()[pos].g = this->_Strip->getLeds()[pos].g + 255;
                        this->_Strip->getLeds()[pos].b = this->_Strip->getLeds()[pos].b + 255;
                        }                
                    }
                break;
            case LS_TRANSITION_TYPES::ColorDissolve:
                for (int i = 0; i < STRIP_NUM_LEDS/4; ++i) {
                    int pos = random(0,STRIP_NUM_LEDS);
                    if (random8(10)>5){
                    this->_Strip->getLeds()[i].r = this->_Strip->getLeds()[i].r + ((_transitionColor.r - this->_Strip->getLeds()[i].r) * progress);
                    this->_Strip->getLeds()[i].g = this->_Strip->getLeds()[i].g + ((_transitionColor.g - this->_Strip->getLeds()[i].g) * progress);
                    this->_Strip->getLeds()[i].b = this->_Strip->getLeds()[i].b + ((_transitionColor.b - this->_Strip->getLeds()[i].b) * progress);
                        }                
                    }
                break;
            case LS_TRANSITION_TYPES::BlackDissolve:
                for (int i = 0; i < STRIP_NUM_LEDS/4; ++i) {
                    int pos = random(0,STRIP_NUM_LEDS);
                    if (random8(10)>5) this->_Strip->getLeds()[pos] = CRGB::Black;
                    }
                break;
            case LS_TRANSITION_TYPES::DissolveInto:
                for (int i = 0; i < STRIP_NUM_LEDS/4; ++i) {
                    int pos = random(0,STRIP_NUM_LEDS);
                    if (random8(10)>5) this->_Strip->getLeds()[pos] = this->_targetFirstRenderedLeds[pos];
                    }
                break;
            case LS_TRANSITION_TYPES::LightsOff:
                for (int i = 0; i < STRIP_NUM_LEDS/10; ++i) {
                    int pos = random(0,STRIP_NUM_LEDS);
                    if (random8(10)>5) this->_Strip->getLeds()[pos] = CRGB::Black;
                    }
                break;
            case LS_TRANSITION_TYPES::BlinkIn:
                // Determine whether we are in the 'on' or 'off' part of the blink
                _isOn = (elapsedFrames / _renderEveryNFrames) % 2 == 0;
                for (int i = 0; i < STRIP_NUM_LEDS; ++i) {
                    this->_Strip->getLeds()[i] = _isOn ? CRGB::White : CRGB::Black; // Toggle full brightness or off
                }
                break;
            case LS_TRANSITION_TYPES::BlinkOut:
                // Determine whether we are in the 'on' or 'off' part of the blink
                _isOn = (elapsedFrames / _renderEveryNFrames) % 2 == 0;
                for (int i = 0; i < STRIP_NUM_LEDS; ++i) {
                    this->_Strip->getLeds()[i] = _isOn ? CRGB::White : CRGB::Black; // Toggle full brightness or off
                }
                break;
            case LS_TRANSITION_TYPES::Ciak:
                if (progress < 0.5f) {
                    for (int i = 0; i < doorsWidth*2; ++i) {
                        this->_Strip->getLeds()[i] =  this->_transitionColor; // Left door opening
                        this->_Strip->getLeds()[STRIP_NUM_LEDS -1  - i] =  this->_transitionColor; // Right door opening
                    }
                } else {
                    for (int i = 0; i < STRIP_NUM_LEDS / 2; ++i) {
                        if (i < position/2) {
                            this->_Strip->getLeds()[STRIP_NUM_LEDS / 2 + i] =  this->_targetFirstRenderedLeds[STRIP_NUM_LEDS / 2 + i];
                            this->_Strip->getLeds()[STRIP_NUM_LEDS / 2 - i] =  this->_targetFirstRenderedLeds[STRIP_NUM_LEDS / 2 - i];
                        }
                    }
                }
                break;
               case LS_TRANSITION_TYPES::SweepLeft:
                // Determine whether we are in the 'on' or 'off' part of the blink
                this->_Strip->getLeds()[position] = this->_transitionColor;
                if (position > 0) {
                    for (int i = 0; i < position-1; ++i) {
                        this->_Strip->getLeds()[i] = this->_targetFirstRenderedLeds[i];
                    }
                }
                break;
               case LS_TRANSITION_TYPES::SweepRight:
                // Determine whether we are in the 'on' or 'off' part of the blink
                this->_Strip->getLeds()[STRIP_NUM_LEDS-position] = this->_transitionColor;
                if (STRIP_NUM_LEDS-position+1 < STRIP_NUM_LEDS) {
                    for (int i = 0; i < position-1; ++i) {
                        this->_Strip->getLeds()[STRIP_NUM_LEDS-position +1 + i] = this->_targetFirstRenderedLeds[STRIP_NUM_LEDS-position+1+i];
                    }
                }
                break;
            case LS_TRANSITION_TYPES::Atomic:
                if (progress < 0.5f) {
                    for (int i = 0; i < STRIP_NUM_LEDS; ++i) {
                        this->_Strip->getLeds()[i] = blend(this->_Strip->getLeds()[i],this->_transitionColor,255*progress*2);
                    }
                } else {
                    for (int i = 0; i < STRIP_NUM_LEDS; ++i) {
                        this->_Strip->getLeds()[i] = blend(this->_Strip->getLeds()[i],this->_targetFirstRenderedLeds[i],255*(progress-0.5f)*2);
                    }
                }
                break;
            case LS_TRANSITION_TYPES::IncreasingBlink:
                if (elapsedFrames==0) {
                    _renderEveryNFrames = sizeIncreaseDecrease;
                    _step = sizeIncreaseDecrease;
                }
                if (elapsedFrames>=_renderEveryNFrames) {
                    _isOn = !_isOn;
                    if(!_isOn){
                        _step--;
                    }
                    _renderEveryNFrames +=_step;
                }
                fill_solid(this->_Strip->getLeds(), STRIP_NUM_LEDS, _isOn ? _transitionColor : CRGB::Black);                
                break;
            case LS_TRANSITION_TYPES::DecreasingBlink: 
                if (elapsedFrames>=_renderEveryNFrames) {
                    _isOn = !_isOn;
                    if(!_isOn){
                        _step++;
                    }
                    _renderEveryNFrames += _step;
                }
                fill_solid(this->_Strip->getLeds(), STRIP_NUM_LEDS, _isOn ? _transitionColor : CRGB::Black);
                break;
            }
        }

        JsonDocument serialize(){
            JsonDocument doc;

            doc["type"] = static_cast<int>(this->_type);;
            doc["_duration"] = _duration; 
            doc["_startAt"]  = _startAt;
            doc["_step"] = _step;
            doc["_renderEveryNFrames"] = _renderEveryNFrames;
            doc["_transitionColor"] = lsColorutils::serialize(_transitionColor);
            doc["_isOn"] = _isOn;

            return doc;
        }

    };

        