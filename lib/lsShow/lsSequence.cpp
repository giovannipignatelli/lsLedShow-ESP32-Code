#include "lsSequence.h"
#include "lsLevel.h"

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

    lsSequence& lsSequence::setParentLevel(lsLevel* show) {
      parentLevel = show;
      return *this;
    }

    lsSequence &lsSequence::setStrip(lsStrip *Strip){
      this->_Strip = Strip;
      uint8_t mask[this->_Strip->getNumLeds()];
      this->_maskStrip = mask;
      return *this;
    }

    lsSequence &lsSequence::setRenderEveryNFrames(int frames){
      this->_renderEveryNFrames = frames;
      this->_nextFrameRender=this->_startAt + this->_renderEveryNFrames-1;
      return *this;
    }

    lsSequence &lsSequence::startAt(int frame){
      this->_startAt = frame;
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
      this->_lastFrame = this->_startAt + this->_duration;
      this->_isActive = true;
    }

    void lsSequence::render(uint8_t currentFrame) {

      if (currentFrame >= this->_nextFrameRender &&  (currentFrame <= this->_lastFrame )){
        this->_nextFrameRender+=this->_renderEveryNFrames;
        //Serial.print("--Frame Effect ");Serial.print(currentFrame);Serial.print("\t ");Serial.print(this->_nextFrameRender);Serial.print("\t");Serial.println(this->_lastFrame);
        this->update(currentFrame);
        this->draw(currentFrame);
      }
      else {
        this->reset();
        this->parentLevel->effectCompleted();
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
      this->_isMaskActive = true;
      return *this;
    }

    lsSequence &lsSequence::applyMask(){
      this->_Strip->applyMask(this->_maskStrip);
      return *this;
    }

    lsSequence &lsSequence::setPalette(CRGBPalette16 palette, TBlendType blending) {
      this->_usePalette = true;
      this->_isRandom = false;
      this->_useColor = false;
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
      this->_usePalette = false;
      this->_isRandom = false;
      this->_useColor = true;
      return *this;
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
