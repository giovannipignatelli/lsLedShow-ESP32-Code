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
#include "lsLevel.h"
#include "lsColorUtils.h"

    CRGB *lsSequence::getLeds() { return this->_Strip->getLeds();}
    lsStrip *lsSequence::getStrip() { return this->_Strip;}

    lsSequence& lsSequence::setParentLevel(lsLevel* show) {
      parentLevel = show;
      return *this;
    }

    lsSequence &lsSequence::setStrip(lsStrip *Strip){
      this->_Strip = Strip;
      this->_minPosition = 0;
      this->_maxPosition = STRIP_NUM_LEDS;
      this->_bufferLeds = new CRGB[STRIP_NUM_LEDS];
      this->_maskStrip = new uint8_t[STRIP_NUM_LEDS];
      setPositionBounds();
      return *this;
    }

    lsSequence &lsSequence::setTransitionIn(lsTransition *transition){
      this->_transitionIn = transition;
      this->_transitionIn->setStrip(this->_Strip);
      this->_duration += _transitionIn->getDuration();
      return *this;
    }

    lsSequence &lsSequence::setTransitionOut(lsTransition *transition){
      this->_transitionOut = transition;
      this->_transitionOut->setStrip(this->_Strip);
      return *this;
    }

    lsSequence &lsSequence::startAt(uint32_t frames){
      this->_startAt = frames;
      this->_lastFrame = (frames > 0) ? this->_startAt + this->_duration : 0;
      RESET_NEXT_RENDER_FRAME
      RESET_NEXT_COLOR_FRAME
      RESET_NEXT_MASK_FRAME
      return *this;
    }

    lsSequence &lsSequence::setRenderEveryNFrames(uint32_t frame){
      this->_renderEveryNFrames = frame;
      RESET_NEXT_RENDER_FRAME  // this->_nextFrameRender=this->_startAt + this->_renderEveryNFrames-1;
      return *this;
    }

    lsSequence &lsSequence::setDuration(uint32_t frames){
      this->_duration = frames;
      this->_lastFrame = (frames > 0) ? this->_startAt + this->_duration : 0;
      return *this;
    }

    lsSequence &lsSequence::setRepeat (unsigned long repeatCount){
      this->_repeatCount = repeatCount;
      return *this;
    }

    void lsSequence::reset() {
      RESET_NEXT_RENDER_FRAME
      RESET_NEXT_COLOR_FRAME
      RESET_NEXT_MASK_FRAME
      _isMaskOn = false;
      RESET_OFFSET
      RESET_HUE
      RESET_RUNS
      if (_transitionIn != nullptr) _transitionIn->reset();
      if (_transitionOut != nullptr) _transitionOut->reset();
    }

    void lsSequence::render(unsigned long frame) {
      privateRender(frame);
    }

    // void lsSequence::getFirstFrameRender(CRGB *tempLeds) {
    //   fill_solid(tempLeds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    // };

    void lsSequence::privateRender(unsigned long frame){
      // Initial part of the sequence. If a transition is set it will start the transition first
      if (SEQUENCE_RUN==0) {
        if(this->_transitionIn != nullptr && !this->_transitionIn->isCompleted(frame)){
          getFirstFrameRender(_bufferLeds);
          this->_transitionIn->update(frame,_bufferLeds);
          return;
        }
        else {
          preRender();
          INCREASE_SEQUENCE_RUN;
        }
      }
      else {
        int lastRun = SEQUENCE_RUN;
        if(!ISCOMPLETED(frame))  {
          if (frame >= this->_nextFrameRender ){
            _nextFrameRender+=this->_renderEveryNFrames;
            this->updateColors(frame);
            this->update(frame);
            this->draw(frame);
            //this->updateMask(frame);
          }
        }
        else {
          if(this->_transitionOut != nullptr && !this->_transitionOut->isCompleted(frame)) {
            if  (this->parentLevel != nullptr) this->parentLevel->getNextSequence().getFirstFrameRender(_bufferLeds);
            this->_transitionOut->update(frame,_bufferLeds);
            return;
          } else {
            if (this->parentLevel != nullptr) this->parentLevel->sequenceCompleted(frame);
          }
          
        }
        if (lastRun < SEQUENCE_RUN && _changeColorEveryNFrames == -1) updateColors();
      }
    }

// Masking Functions

    lsSequence &lsSequence::setMask(LS_MASK *mask, uint8_t maskSize, int activateEveryNFrames){
      this->_mask = mask;
      this->_maskSize = maskSize;
      this->_changeMaskEveryNFrames = activateEveryNFrames;
      RESET_NEXT_MASK_FRAME
      int pixel = 0;
      while (pixel < STRIP_NUM_LEDS) {
        for(int j = 0; j < maskSize; j++ ) {
          for(int i = 0; i < mask[j].stripSize; i++ ) {
            this->_maskStrip[pixel]=mask[j].fadeValue;
            pixel++;
          }
        }
      }
      return *this;
    }

    void lsSequence::updateMask(unsigned long currentFrame){
      if (_changeMaskEveryNFrames == -1) this->_isMaskOn = false;
      if (_changeMaskEveryNFrames == 0) this->_isMaskOn = true;
      if (_changeMaskEveryNFrames >0) {
        if (currentFrame >= _nextFrameMaskChange) {
          this->_nextFrameMaskChange = currentFrame + this->_changeMaskEveryNFrames;
          _isMaskOn = !_isMaskOn;
        } 
      }
    if (this->_isMaskOn) this->_Strip->applyMask(this->_maskStrip);

    }

// Position Management

    bool lsSequence::_inBounds(uint16_t pos) { return ((pos >= 0) && (pos < _Strip->getNumLeds())); }

    void  lsSequence::setPositionBounds() {
      _minPosition = 0;
      if (_isMirrored) {
        _maxPosition = STRIP_NUM_LEDS/2;
      } else {
        _maxPosition = STRIP_NUM_LEDS;
      }
      if (_isReversed) {
        _minPosition = _maxPosition;
        _maxPosition = 0;
      }
      
    }

    long lsSequence::getPosition(uint16_t pos){
      if (_isReversed) return _maxPosition  - map(pos,0,STRIP_NUM_LEDS,_minPosition,_maxPosition);
      else return (map(pos,0,STRIP_NUM_LEDS,_minPosition,_maxPosition));
    }

    long lsSequence::getReflectionPosition(uint16_t pos){
      return STRIP_NUM_LEDS - getPosition(pos);
    }

    void lsSequence::setPixel(uint16_t position, CRGB color) {
      STRIP_LEDS(getPosition(position)) = color; 
      if (_isMirrored) STRIP_LEDS(getReflectionPosition(position)) = color; 
    }

   lsSequence &lsSequence::setParam1 (int p){
      this->_param1 = p;
      return *this;
    }

       lsSequence &lsSequence::setParam2 (int p){
      this->_param2 = p;
      return *this;
    }

    lsSequence &lsSequence::setParam3 (int p){
      this->_param3 = p;
      return *this;
    }

    lsSequence &lsSequence::setStatusA (bool A){
      this->_statusA = A;
      return *this;
    }

    lsSequence &lsSequence::setStatusB (bool A){
      this->_statusB = A;
      return *this;
    }


    void lsSequence::setPixel(uint16_t position, CHSV color) {
      STRIP_LEDS(getPosition(position)) = color; 
      if (_isMirrored) STRIP_LEDS(getReflectionPosition(position)) = color; 
    }

// Color management functions

    void lsSequence::print(CRGB color){
      Serial.print(color.r);Serial.print(":");Serial.print(color.g);Serial.print(":");Serial.print(color.b);
    }

    lsSequence &lsSequence::setColoring(LS_FILL_TYPES LS_FILL_TYPES){
      this->_Coloring = LS_FILL_TYPES;
      return *this;
    }

    lsSequence &lsSequence::setPalette(LS_PALETTES palette, TBlendType blending) {
      this->_Coloring = LS_FILL_TYPES::PALETTE;
      this->_paletteConst = palette;
      this->_Palette = lsColorutils::getPalette(palette);
      this->_Blending = blending;
      return *this;
    }

    lsSequence &lsSequence::setPaletteC(LS_PALETTES palette, TBlendType blending,bool reversed) {
      this->_Coloring = LS_FILL_TYPES::PALETTECIRCULAR;
      this->_Palette = lsColorutils::getPalette(palette);
      this->_paletteConst = palette;
      this->_Blending = blending;
      this->_isReversed = reversed;
      return *this;
    }

    lsSequence &lsSequence::setPatternStrip(LS_PATTERN_STRIP *stripe, uint8_t size) {
      this->_Coloring = LS_FILL_TYPES::PATTERN;
      this->_stripes = stripe;
      this->_stripesSize = size;
      return *this;
    }

    lsSequence &lsSequence::setColors(CRGB _ColorA,CRGB _ColorB,CRGB _ColorC){
      this->_PrimaryColor   = _ColorA;
      this->_SecondaryColor = _ColorB;
      this->_TertiaryColor  = _ColorC;
      this->_Coloring = LS_FILL_TYPES::SOLID;
      return *this;
    }

    lsSequence &lsSequence::setChangeColorEveryNFrames(uint32_t frames, LS_COLOR_UPDATE command){
      this->_updateCommand.BG = command.BG;
      this->_updateCommand.FG = command.FG;
      this->_updateCommand.TG = command.TG;
      this->_changeColorEveryNFrames = frames;
      RESET_NEXT_COLOR_FRAME
      return *this;
    }

    lsSequence &lsSequence::setChangeColorEveryRun(LS_COLOR_UPDATE command){
      this->_updateCommand.BG = command.BG;
      this->_updateCommand.FG = command.FG;
      this->_updateCommand.TG = command.TG;
      this->_changeColorEveryNFrames = -1;
      return *this;
    }

    void lsSequence::updateColors(unsigned long frame){
    if (_changeColorEveryNFrames >0 && frame>=_nextFrameColorChange && this->_Coloring != LS_FILL_TYPES::SOLID){
      if (INCREASE_SEQUENCE_HUE > 255) SEQUENCE_HUE = 0;
      _nextFrameColorChange += _changeColorEveryNFrames;
      updateColors();
      }
    }

    void lsSequence::updateColors()
    {
      
      CRGB myPColor = SEQUENCE_PRIMARY_COLOR;
      CRGB mySColor = SEQUENCE_SECONDARY_COLOR;
      CRGB myTColor = SEQUENCE_TERTIARY_COLOR;
      switch (this->_Coloring)
      {
      case (LS_FILL_TYPES::SOLID):
      {
        myPColor = SEQUENCE_PRIMARY_COLOR;
        mySColor = SEQUENCE_SECONDARY_COLOR;
        myTColor = SEQUENCE_TERTIARY_COLOR;
        break;
      }
      case (LS_FILL_TYPES::RANDOMSOLID):
      {
        myPColor = lsColorutils::getRandomColor();
        mySColor = lsColorutils::getRandomColor();
        myTColor = lsColorutils::getRandomColor();
        break;
      }
      case (LS_FILL_TYPES::RANDOMSINGLE):
      {
        myPColor = lsColorutils::getRandomColor();
        mySColor = lsColorutils::getRandomColor();
        myTColor = lsColorutils::getRandomColor();
        break;
      }
      case (LS_FILL_TYPES::PALETTE):
      {
        myPColor = GETPALETTECOLOR(SEQUENCE_HUE);
        mySColor = GETPALETTECOLOR(SEQUENCE_HUE + 32);
        myTColor = GETPALETTECOLOR(SEQUENCE_HUE + 64);
        break;
      }
      case (LS_FILL_TYPES::PALETTECIRCULAR):
      {
        myPColor = GETPALETTECOLOR(SEQUENCE_HUE);
        mySColor = GETPALETTECOLOR(SEQUENCE_HUE + 32);
        myTColor = GETPALETTECOLOR(SEQUENCE_HUE + 64);
        break;
      }
      }
      if (_updateCommand.FG)  this->_PrimaryColor = myPColor;
      if (_updateCommand.BG)  this->_SecondaryColor = mySColor;
      if (_updateCommand.TG)  this->_TertiaryColor = myTColor;
      
    }

    lsSequence &lsSequence::setRainbowHues(uint8_t initialhue, uint8_t deltahue) {
      this->_Coloring = LS_FILL_TYPES::RAINBOW;
      this->_initialhue = initialhue;
      this->_deltahue = deltahue;
      return *this;
    }

    lsSequence &lsSequence::setRainbowCHues(uint8_t initialhue, bool reversed) {
      this->_Coloring = LS_FILL_TYPES::RAINBOWCIRCULAR;
      this->_initialhue = initialhue;
      this->_isReversed = reversed;
      return *this;
    }

    lsSequence &lsSequence::setGradient(CRGB startcolor, CRGB endcolor) {
      this->_Coloring = LS_FILL_TYPES::GRADIENT;
      this->_PrimaryColor = startcolor;
      this->_SecondaryColor = endcolor;
      return *this;
    }

    lsSequence &lsSequence::setFilterChannel(LS_FILTER filter){
      this->_channel = filter;
      return *this;
    }

    void lsSequence::fillSolid(){ this->_Strip->drawColor(SEQUENCE_PRIMARY_COLOR);}
    void lsSequence::fillRandom(){ this->_Strip->drawColor(lsColorutils::getRandomColor()); }
    void lsSequence::fillRandomSingle(){ for (int i = 0; i<STRIP_NUM_LEDS; i++ ) STRIP_LEDS(i) = lsColorutils::getRandomColor(); }
    void lsSequence::fillPalette(){ this->_Strip->drawPalette(this->_Palette, this->_Blending); }
    void lsSequence::fillPaletteC(){ this->_Strip->drawPaletteC(this->_Palette, this->_Blending,this->_isReversed); }
    void lsSequence::fillPattern(){ this->_Strip->drawPattern(this->_stripes, this->_stripesSize); }
    void lsSequence::fillRainbow(){ this->_Strip->drawRainbow(this->_initialhue, this->_deltahue); }
    void lsSequence::fillRainbowC(){ this->_Strip->drawRainbowC(this->_initialhue, this->_isReversed); }
    void lsSequence::fillGradient(){ this->_Strip->drawGradient(SEQUENCE_PRIMARY_COLOR,SEQUENCE_SECONDARY_COLOR); }

    JsonDocument lsSequence::serialize(){
      JsonDocument doc;


      // Add values in the document
      JsonDocument command;
      command["BG"] = _updateCommand.BG;
      command["FG"] = _updateCommand.FG;
      command["TG"] = _updateCommand.TG;
      doc["_upDateCommand"] = command;
      doc["_channel"] = static_cast<int>(this->_channel);
      doc["_type"] = static_cast<int>(this->_type);
      doc["_isReversed"] = _isReversed;
      doc["_isMirrored"] = _isMirrored;
      doc["_Coloring"]  = static_cast<int>(this->_Coloring);
      doc["_type"] = static_cast<int>(this->_type);
      doc["_renderEveryNFrames"] = _renderEveryNFrames;
      doc["_changeColorEveryNFrames"] = _changeColorEveryNFrames;
      doc["_param1"] = _param1;
      doc["_param2"] = _param2;
      doc["_param3"] = _param3;
      doc["_statusA"] = _statusA;
      doc["_statusB"] = _statusB;
      doc["_stripesSize"] = _stripesSize;
      if (_stripesSize > 0) doc["_stripes"] =  serializeStrip();
      doc["_maskSize"] = (_changeMaskEveryNFrames == 4294967295) ? 0 : _maskSize;
      doc["_changeMaskEveryNFrames"] = (_changeMaskEveryNFrames == 4294967295) ? -1 : _changeMaskEveryNFrames;
      if(_changeMaskEveryNFrames !=4294967295 ) doc["_mask"] = serializeMask();      
      doc["_Blending"] = static_cast<int>(this->_Blending);
      doc["_paletteConst"] = static_cast<int>(this->_paletteConst);
      doc["_lastFrame"] = _lastFrame;
      doc["_startAt"] = _startAt;
      doc["_PrimaryColor"] = lsColorutils::serialize(_PrimaryColor);
      doc["_SecondaryColor"] = lsColorutils::serialize(_SecondaryColor);
      doc["_TertiaryColor"] = lsColorutils::serialize(_TertiaryColor);
      doc["_blockSize"] = _blockSize;
      doc["_duration"] = _duration;
      doc["_repeatCount"] = _repeatCount;
      doc["_initialhue"] = _initialhue;
      doc["_deltahue"] = _deltahue;
      if(_transitionIn !=nullptr) doc["_transitionIn"] = _transitionIn->serialize();
      if(_transitionOut !=nullptr) doc["_transitionOut"] = _transitionOut->serialize();
      return doc;
  }

  JsonDocument lsSequence::serializeMask(){
    JsonDocument doc;
    for(int j = 0; j < _maskSize; j++ ) {
      JsonDocument element;
      element["stripSize"] =  _mask[j].stripSize;
      element["fadeValue"] =  _mask[j].fadeValue;
      doc["LS_MASK"].add(element);
    }
    return doc;
  }

  JsonDocument lsSequence::serializeStrip(){
    JsonDocument doc;
    for(int j = 0; j < _stripesSize; j++ ) {
      JsonDocument element;
      element["stripColor"] =  lsColorutils::serialize(_stripes[j].stripColor);
      element["stripSize"] =  _stripes[j].stripSize;
      doc["LS_PATTERN_STRIP"].add(element);
    }
    return doc;
  }