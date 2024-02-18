#include "lsSequence.h"

    CRGB lsSequence::getRandomColor(){
      return ColorFromPalette( RainbowColors_p, random16(255), 180, LINEARBLEND);
    }
    CRGB lsSequence::getColorFromPalette(int step){
      return ColorFromPalette( RainbowColors_p, step, 180, LINEARBLEND);
    }

    lsSequence &lsSequence::activateMask() {this->_isMaskActive = true;return *this;}
    lsSequence &lsSequence::deactivateMask() {this->_isMaskActive = false;return *this;}
    CRGB *lsSequence::getLeds() { return this->_Strip->getLeds();}
    lsStrip *lsSequence::getStrip() { return this->_Strip;}

    lsSequence &lsSequence::setStrip(lsStrip *Strip){
      this->_Strip = Strip;
      uint8_t mask[this->_Strip->getNumLeds()];
      this->_maskStrip = mask;
      return *this;
    }

    lsSequence &lsSequence::setRenderEveryNFrames(int frames){
      this->_renderEveryNFrames = frames;
      this->_nextFrameRender+= frames;
      return *this;
    }

    lsSequence &lsSequence::startAt(int frame){
      this->_startAt = frame;
      this->_nextFrameRender+= frame;
      return *this;
    }

    lsSequence &lsSequence::setDuration(int frames){
      this->_duration = frames;
      this->_lastFrame = (frames > 0) ? this->_startAt + this->_duration : 0;
      return *this;
    }

    void lsSequence::reset(){
      this->_nextFrameRender=this->_renderEveryNFrames;
      this->_lastFrame = this->_startAt + this->_duration;
      this->_isActive = true;
    }

    void lsSequence::printLeds(CRGB *ledsToPrint){
      //Serial.println("");
      for(int j = 0; j < this->_Strip->getNumLeds(); j++ ) {
        if(ledsToPrint[j].r<10) Serial.print(" ");
        if(ledsToPrint[j].r<100) Serial.print(" ");
        Serial.print(ledsToPrint[j].r);Serial.print(":");
        if(ledsToPrint[j].g<10) Serial.print(" ");
        if(ledsToPrint[j].g<100) Serial.print(" ");
        Serial.print(ledsToPrint[j].g);Serial.print(":");
        if(ledsToPrint[j].b<10) Serial.print(" ");
        if(ledsToPrint[j].b<100) Serial.print(" ");
        Serial.print(ledsToPrint[j].b);Serial.print(" - ");
      }
      Serial.println("");
    }

    void lsSequence::render(uint8_t currentFrame) {
      if (currentFrame >= this->_nextFrameRender && ( (currentFrame <= this->_lastFrame && this->_lastFrame>0) || this->_lastFrame == 0 ) ){
        this->_nextFrameRender+=this->_renderEveryNFrames;
        this->fillStrip(currentFrame);
      }
    }

    lsSequence &lsSequence::setMask(lsMask *mask, uint8_t maskSize){
      this->_mask = mask;
      this->_maskSize = maskSize;
      int pixel = 0;
      while (pixel < this->_Strip->getNumLeds()) {
        for(int j = 0; j < maskSize; j++ ) {
          for(int i = 0; i < mask[j].stripSize; i++ ) {
            this->_maskStrip[pixel]=mask[j].fadeValue;
            pixel++;
          }
        }
      }
      //for (int i = 0; i  < NUM_LEDS ; i++) {Serial.print(this->_maskStrip[i]);Serial.print(" - ");}
      //Serial.println("");
      this->_isMaskActive = true;
      return *this;
      
    }

    lsSequence &lsSequence::applyMask(){
      this->_Strip->applyMask(this->_maskStrip);
      return *this;
    }

