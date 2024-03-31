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

#include "lsSequence.h"

class lsSequenceLightning : public lsSequence {

  private:

  int _flashCounter = 0;
  uint8_t _maxFlashes = 8;
  uint8_t _nFlashes;
  int _dimmer = 1;
  bool _flashesOn = true;
  uint8_t _ledstart;                                             // Starting location of a flash
    
  

  public:

    lsSequenceLightning(uint8_t flashes = 8) : _maxFlashes(flashes) {
       _type = LS_SEQUENCES_TYPES::lsSequenceLightning;
    }

    void preRender() {
      _flashCounter = 0;
      _flashesOn = false;  
      _ledstart = random8(STRIP_NUM_LEDS);                               // Determine starting location of flash
      _blockSize = random8(STRIP_NUM_LEDS-_ledstart); 
      _nFlashes = random8(3,_maxFlashes);
    }

    void update(unsigned long frame) {

      if (_flashCounter == _nFlashes) {
        _flashCounter = 0;
        this->_nextFrameRender += random8(5,10);
      } 
      else if(_flashCounter == 0) {
        this->_nextFrameRender +=10;
        _dimmer = 5; // the brightness of the leader is scaled down by a factor of 5
      }                         
      else {
        _dimmer = random8(1,3); // return strokes are brighter than the leader
        this->_nextFrameRender += random8(1,3);
      }
    }

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };


    void draw(unsigned long frame) {
      if (_flashesOn) {
        for (int i = _ledstart;i< _ledstart+_blockSize;i++) setPixel(i, CHSV(255, 0, 255/_dimmer)); //STRIP_LEDS(i)  = CHSV(255, 0, 255/_dimmer);
      }
      else {
        for (int i = _ledstart;i< _ledstart+_blockSize;i++) setPixel(i, CHSV(255, 0, 0));//STRIP_LEDS(i)  = CHSV(255, 0, 0);
      }
      _flashCounter++;
      _flashesOn = !_flashesOn;
    }



 
};
