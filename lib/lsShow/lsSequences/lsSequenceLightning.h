#include "lsSequence.h"

class lsSequenceLightning : public lsSequence {

  private:

  int _flashCounter = 0;
  uint8_t _maxFlashes = 8;
  uint8_t _nFlashes;
  int _dimmer = 1;
  bool _flashesOn = true;
  uint8_t _ledstart;                                             // Starting location of a flash
  uint8_t _ledlen; 
    
  

  public:

    lsSequenceLightning(uint8_t flashes = 8) : _maxFlashes(flashes) {}

    void preRender() {
      _flashCounter = 0;
      _flashesOn = false;  
      _ledstart = random8(this->_Strip->getNumLeds());                               // Determine starting location of flash
      _ledlen = random8(this->_Strip->getNumLeds()-_ledstart); 
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


    void draw(unsigned long frame) {
      if (_flashesOn) {
        for (int i = _ledstart;i< _ledstart+_ledlen;i++) this->_Strip->getLeds()[i]  = CHSV(255, 0, 255/_dimmer);
      }
      else {
        for (int i = _ledstart;i< _ledstart+_ledlen;i++) this->_Strip->getLeds()[i]  = CHSV(255, 0, 0);
      }
      _flashCounter++;
      _flashesOn = !_flashesOn;
    }



 
};
