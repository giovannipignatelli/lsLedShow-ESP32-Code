#include "lsSequence.h"
#include "lsLevel.h"

    CRGB *lsSequence::getLeds() { return this->_Strip->getLeds();}
    lsStrip *lsSequence::getStrip() { return this->_Strip;}

    lsSequence& lsSequence::setParentLevel(lsLevel* show) {
      parentLevel = show;
      return *this;
    }

    lsSequence &lsSequence::setStrip(lsStrip *Strip){
      this->_Strip = Strip;
      this->_maskStrip = new uint8_t[this->_Strip->getNumLeds()];
      return *this;
    }

    lsSequence &lsSequence::startAt(int frame){
      this->_startAt = frame;
      this->_nextFrameRender=this->_startAt + this->_renderEveryNFrames-1;
      this->_nextFrameColorChange =this->_startAt + _changeColorEveryNFrames;
      return *this;
    }

    lsSequence &lsSequence::setRenderEveryNFrames(int frames){
      this->_renderEveryNFrames = frames;
      this->_nextFrameRender=this->_startAt + this->_renderEveryNFrames-1;
      return *this;
    }

    lsSequence &lsSequence::setDuration(int frames){
      this->_duration = frames;
      this->_lastFrame = (frames > 0) ? this->_startAt + this->_duration : 0;
      return *this;
    }

    void lsSequence::reset(){
      this->_nextFrameRender=this->_startAt + this->_renderEveryNFrames-1;
      this->_nextFrameColorChange =this->_startAt + _changeColorEveryNFrames;
      this->_nextFrameMask = this->_startAt + this->_maskEveryNFrames;
      //this->_lastFrame = this->_startAt + this->_duration;
      //Serial.print("--->Reset ---- Start at ");Serial.print(_startAt);Serial.print("--->Prossimo Render  ");Serial.print(_nextFrameRender);Serial.print("--->Prossimo ColorChange  ");Serial.print(_nextFrameColorChange);;Serial.print("--->Ultimo Frame  ");Serial.println(_lastFrame);
      bool _isMaskOn = false;
    }

    void lsSequence::render(uint8_t currentFrame) { 
      //Serial.print("\tSequence FRAME ");Serial.print(currentFrame);
      if (currentFrame >= this->_nextFrameRender &&  (currentFrame <= this->_lastFrame )){
        this->_nextFrameRender+=this->_renderEveryNFrames;
        //Serial.print("--Frame Effect ");Serial.print(currentFrame);Serial.print("\t ");Serial.print(this->_nextFrameRender);Serial.print("\t");Serial.println(this->_lastFrame);
        this->updateColor(currentFrame);
        this->update(currentFrame);
        this->draw(currentFrame);
        this->applyMask(currentFrame);
      }
      else {
        //this->reset();
        this->parentLevel->sequenceCompleted(currentFrame);
      }
    }

// Masking Functions

    lsSequence &lsSequence::setMask(lsMask *mask, uint8_t maskSize, int activateEveryNFrames){
      this->_mask = mask;
      this->_maskSize = maskSize;
      this->_maskEveryNFrames = activateEveryNFrames;
      this->_nextFrameMask = this->_startAt + this->_maskEveryNFrames;
      //uint8_t myMask[this->_Strip->getNumLeds()];
      int pixel = 0;
      while (pixel < this->_Strip->getNumLeds()) {
        for(int j = 0; j < maskSize; j++ ) {
          for(int i = 0; i < mask[j].stripSize; i++ ) {
            this->_maskStrip[pixel]=mask[j].fadeValue;
            pixel++;
          }
        }
      }
      return *this;
    }


    void lsSequence::applyMask(uint8_t currentFrame){
     //Serial.print(":\tDurata");Serial.print(this->_lastFrame);Serial.print("\tCambio Mask ogni ");Serial.print(_maskEveryNFrames);Serial.print("\tProssimo ");Serial.print(_nextFrameMask);
      if (_maskEveryNFrames == -1) this->_isMaskOn = false;
      if (_maskEveryNFrames == 0) this->_isMaskOn = true;
      if (_maskEveryNFrames >0) {
        if (currentFrame >= _nextFrameMask) {
          this->_nextFrameMask = currentFrame + this->_maskEveryNFrames;
          _isMaskOn = !_isMaskOn;
        } 
      }
      if (this->_isMaskOn) this->_Strip->applyMask(this->_maskStrip);
      Serial.println("");
    }

// Color management functions

    CRGB lsSequence::getRandomColor(){
      return ColorFromPalette( RainbowColors_p, random16(255), 180, LINEARBLEND);
    }

    CRGB lsSequence::getColorFromPalette(int step){
      return ColorFromPalette( _Palette, step, 180, LINEARBLEND);
    }

    lsSequence &lsSequence::setColoring(LS_SEQUENCE_COLORING coloring){
      this->_Coloring = coloring;
      return *this;
    }

    lsSequence &lsSequence::setPalette(CRGBPalette16 palette, TBlendType blending) {
      this->_Coloring = LS_SEQUENCE_COLORING::PALETTECOLOR;
      this->_Palette = palette;
      this->_Blending = blending;
      return *this;
    }

    lsSequence &lsSequence::setPaletteC(CRGBPalette16 palette, TBlendType blending,bool reversed) {
      this->_Palette = palette;
      this->_Blending = blending;
      this->_reversed = reversed;
      return *this;
    }

    lsSequence &lsSequence::setPatternStrip(lsPatternStrip *stripe, uint8_t size) {
      this->_stripes = stripe;
      this->_stripesSize = size;
      return *this;
    }

    lsSequence &lsSequence::setColor(CRGB _Color){
      this->_Color = _Color;
      this->_Coloring = LS_SEQUENCE_COLORING::FIXEDCOLOR;
      return *this;
    }

    lsSequence &lsSequence::setChangeColorEveryNFrames(int frames){
      this->_changeColorEveryNFrames = frames;
      this->_nextFrameColorChange=this->_startAt + this->_changeColorEveryNFrames-1;
      return *this;
    }

    void lsSequence::updateColor(unsigned long frame){
    if( gHue++ > 255) gHue=0;
     //Serial.print(":\tDurata");Serial.print(this->_lastFrame);Serial.print("\tCambio Colore ogni ");Serial.print(_changeColorEveryNFrames);Serial.print("\tProssimo ");Serial.print(_nextFrameColorChange);
      CRGB myColor = this->_Color;
      if (_changeColorEveryNFrames >0 && frame>=_nextFrameColorChange && this->_Coloring != LS_SEQUENCE_COLORING::FIXEDCOLOR){
        switch (this->_Coloring){
          case (LS_SEQUENCE_COLORING::FIXEDCOLOR):{
            myColor = this->_Color;
            break;
          }
          case (LS_SEQUENCE_COLORING::RANDOMCOLOR):{
            myColor = getRandomColor();
            break;
          }
          case (LS_SEQUENCE_COLORING::PALETTECOLOR):{
            myColor = getColorFromPalette(gHue);
            break;
          }
        }
        _nextFrameColorChange += _changeColorEveryNFrames;
      }
      this->_Color = myColor;
    }

    lsSequence &lsSequence::setRainbowHues(uint8_t initialhue, uint8_t deltahue) {
      this->_initialhue = initialhue;
      this->_deltahue = deltahue;
      return *this;
    }

    lsSequence &lsSequence::setRainbowCHues(uint8_t initialhue, bool reversed) {
      this->_initialhue = initialhue;
      this->_reversed = reversed;
      return *this;
    }

    lsSequence &lsSequence::setGradient(CRGB startcolor, CRGB endcolor) {
      this->_Color = startcolor;
      this->_EndColor = endcolor;
      return *this;
    }