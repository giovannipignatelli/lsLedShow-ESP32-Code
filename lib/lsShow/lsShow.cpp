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

#include "lsShow.h"
#include "lsSequences/lsSequenceHelper.h"

    // Set FPS with potential for chaining
    lsLedShow& lsLedShow::setFPS(int newFPS) {
        this->_tickMillis = 1000/newFPS;
        fps = newFPS;

        return *this;
    }

int   lsLedShow::getTick(){return _tickMillis;}
void   lsLedShow::setTick(int millisec){_tickMillis = millisec;}

lsStage &lsLedShow::addStage(String name){
  _stages.add(new lsStage(name,_Strip));
  _stages.get(this->_stages.size()-1)->setParentShow(this);
  _currentScene = this->_stages.get(this->_stages.size()-1);
  currentStageIndex = this->_stages.size() - 1;
  return *_currentScene;
}

lsStage &lsLedShow::lastStage(){
  //return (this->_stages.size()==0) ? this->addStage("Automatic Created 0") : *this->_stages.get(this->_stages.size()-1);
  if (this->_stages.size()==0) {return this->addStage("Automatic Created 0");}
  else {return *this->_stages.get(this->_stages.size()-1);}
}

lsStage &lsLedShow::getStage(int num){
  // return (num>this->_stages.size()) ? nullptr : *this->_stages.get(num);
  //if (num>this->_stages.size()) return nullptr;
  return *this->_stages.get(num);
}

lsStage &lsLedShow::getCurrentStage(){
  // return (this->_stages.size()==0) ? nullptr : *this->_stages.get(this->_currentStage);
  //if (this->_stages.size()==0) {return nullptr;}
  //else {
	return *this->_stages.get(this->currentStageIndex);
  //}
}  

void lsLedShow::nextStage() {
	this->_stages.get(currentStageIndex)->reset();
	currentStageIndex++;
	if (currentStageIndex == _stages.size()) currentStageIndex=0;
  currentStageFrame = -1;
	//_currentStage = (_currentStage == _stages.size()-1) ? 0 : _currentStage+1;
}

void lsLedShow::setStage(int stage) {
  this->_stages.get(currentStageIndex)->reset();
	//_currentStage = (stage>this->_stages.size()) ? this->_stages.size()-1 : stage;
	if (stage>this->_stages.size()) currentStageIndex = this->_stages.size()-1; 
	else currentStageIndex = stage;
	if (currentStageIndex == _stages.size()) currentStageIndex=0;
}

void lsLedShow::render() {
  uint32_t currentMillis = millis();
  if(currentMillis >= _nextTickMillis && _isActive)  {
    _nextTickMillis = (currentMillis + _tickMillis);
    lsStage *stage;
    stage = _stages.get(currentStageIndex);
    stage->render(currentStageFrame);
    _Strip->showStrip();
    currentStageFrame++;
  }
}

  JsonDocument lsLedShow::serialize(){
    JsonDocument doc;

      // Add values in the document
      doc["FPS"] = this->getFPS();

      // Add an array
      JsonArray data = doc["Stages"].to<JsonArray>();
      for(int i = 0; i < this->_stages.size(); i++){  
        data.add(this->_stages.get(i)->serialize());
      }

      return doc;
  }

  JsonDocument lsLedShow::serializeStages(){
    JsonDocument doc;

      // Add values in the document
      doc["FPS"] = this->getFPS();

      // Add an array
      JsonArray data = doc["Stages"].to<JsonArray>();
      for(int i = 0; i < this->_stages.size(); i++){  
        data.add(this->_stages.get(i)->serializeSimple());
      }
      // Generate the minified JSON and send it to the Serial port
      serializeJsonPretty(doc, Serial);
      return doc;
  }

  bool lsLedShow::update(JsonDocument data){
    int fps = data["FPS"] | 120;
    setFPS(fps);
    JsonArray stages = data["Stages"];
    for (int i=0; i<stages.size(); i++) {
      JsonObject stage = stages[i];
      const char* name = stage["Name"];
      int Duration = stage["Duration"];
      int Repeat = stage["Repeat"];
      int StartAt = stage["StartAt"];
      addStage(name);
      lastStage().setRepeat(Repeat).setStartAt(StartAt);
      JsonArray levels = data["Levels"];
      for (int j=0; j<stages.size(); j++) {
        JsonObject level = levels[j];
        float Opacity = stage["Opacity"];
        int BlendMode = stage["BlendMode"];
        lastStage().addLevel().setOpacity(Opacity).setBlendMode(static_cast<LS_BLENDMODE>(BlendMode));
        JsonArray sequences = data["Sequences"];
        for (int k=0; j<sequences.size(); k++) {
          JsonObject sequence             = sequences[k];
          int type                        = sequence["_type"];
          LS_SEQUENCES_TYPES _type        = static_cast<LS_SEQUENCES_TYPES>(type);
          int   _startAt                  = sequence["_startAt"];
          int   _repeatCount              = sequence["_repeatCount"];
          int   _blockSize                = sequence["_blockSize"];
          int   _duration                 = sequence["_duration"];
          bool  _isReversed               = sequence["_isReversed"];
          bool  _isMirrored               = sequence["_isMirrored"];
          int   _param1                   = sequence["_param1"];
          int   _param2                   = sequence["_param2"];
          int   _param3                   = sequence["_param3"];
          bool  _statusA                  = sequence["_statusA"];
          bool  _statusB                  = sequence["_statusB"];
          int   _renderEveryNFrames       = sequence["_renderEveryNFrames"];
          int   _changeColorEveryNFrames  = sequence["_changeColorEveryNFrames"];
          lastStage().lastLevel().addSequence(lsSequenceHelper::getSequence(_type));
          lastStage().lastLevel().lastSequence().startAt(_startAt).setRepeat(_repeatCount).setBlockSize(_blockSize).setDuration(_duration);
          lastStage().lastLevel().lastSequence().setReverse(_isReversed).setMirror(_isMirrored);
          lastStage().lastLevel().lastSequence().setChangeColorEveryNFrames(_changeColorEveryNFrames).setRenderEveryNFrames(_renderEveryNFrames);
          lastStage().lastLevel().lastSequence().setParam1(_param1).setParam2(_param2).setParam3(_param3).setStatusA(_statusA).setStatusB(_statusB);

          JsonObject command = sequence["_upDateCommand"];
          bool upBG = command["BG"];
          bool upFG = command["FG"];
          bool upTG = command["TG"];
          LS_COLOR_UPDATE colorCommand = {upBG,upFG,upTG};
          lastStage().lastLevel().lastSequence().setChangeColorEveryRun(colorCommand);
          
          JsonObject color = sequence["_PrimaryColor"];
          CRGB _primary = lsColorutils::getColorFromJson(color);
          color = sequence["_SecondaryColor"];
          CRGB _secondary = lsColorutils::getColorFromJson(color);
          color = sequence["_TertiaryColor"];
          CRGB _tertiary = lsColorutils::getColorFromJson(color);
          lastStage().lastLevel().lastSequence().setColors(_primary,_secondary,_tertiary);
          int paletNum = sequence["_paletteConst"];
          LS_PALETTES _palette = static_cast<LS_PALETTES>(paletNum);
          int blending = sequence["_Blending"];
          TBlendType _blending = static_cast<TBlendType>(blending);
          lastStage().lastLevel().lastSequence().setPalette(_palette,_blending);
          int _initialhue = sequence["_initialhue"];
          int _deltahue   = sequence["_deltahue"];
          lastStage().lastLevel().lastSequence().setPalette(_palette,_blending);

          int maskSize = sequence["_maskSize"];
          if (maskSize>0){
            LS_MASK mask[maskSize]; 
            JsonArray maskJ = data["_mask"];
            for (int h = 0;h<maskSize;h++){
              JsonObject maskElement = maskJ[h];
              int fade = maskJ["fadeValue"];
              int size = maskJ["stripSize"];
              mask[h].fadeValue = fade;
              mask[h].stripSize = size;
            }
            lastStage().lastLevel().lastSequence().setMask(mask,maskSize);
          }
          int stripSize = sequence["_stripesSize"];
          if (stripSize>0){
            LS_PATTERN_STRIP strip[stripSize]; 
            JsonArray pattern = data["_stripes"];
            for (int h = 0;h<stripSize;h++){
              JsonObject pElement = pattern[h];
              JsonObject color = pElement["stripColor"];
              CRGB _primary = lsColorutils::getColorFromJson(color);
              int size = pElement["stripSize"];
              strip[h].stripColor = _primary;
              strip[h].stripSize = size;
            }
            lastStage().lastLevel().lastSequence().setPatternStrip(strip,stripSize);
          }
          int _Coloring = sequence["_Coloring"];
          LS_FILL_TYPES _colorFill = static_cast<LS_FILL_TYPES>(_Coloring);
          lastStage().lastLevel().lastSequence().setColoring(_colorFill);
          LS_FILTER channel = sequence["_channel"];
          lastStage().lastLevel().lastSequence().setFilterChannel(channel);
          JsonObject trans = sequence["_transitionIn"];
          if (!trans.isNull()) {
            int mytype = trans["type"];
            LS_TRANSITION_TYPES type = static_cast<LS_TRANSITION_TYPES>(mytype);
            int _duration = trans["_duration"] = _duration; 
            color = trans["_transitionColor"];
            _primary = lsColorutils::getColorFromJson(color);
            lastStage().lastLevel().lastSequence().setTransitionIn(new lsTransition(type,_duration,_primary));
          }
          trans = sequence["_transitionOut"];
          if (!trans.isNull()) {
            int mytype = trans["type"];
            LS_TRANSITION_TYPES type = static_cast<LS_TRANSITION_TYPES>(mytype);
            int _duration = trans["_duration"] = _duration; 
            color = trans["_transitionColor"];
            _primary = lsColorutils::getColorFromJson(color);
            bool _isOn = trans["_isOn"];      
            lastStage().lastLevel().lastSequence().setTransitionOut(new lsTransition(type,_duration,_primary));
          }
        }
      }
      return true;
    }
  }
