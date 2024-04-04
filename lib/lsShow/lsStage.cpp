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

#include "lsStruct_Enum.h"
#include "lsStrip.h"
#include "lsLevel.h"
#include "lsStage.h"


lsStage &lsStage::setRepeat (unsigned long repeatCount){
  this->repeatCount = repeatCount;
  return *this;
}

lsStage &lsStage::setStartAt (unsigned long startAt){
  this->startAt = startAt;
  return *this;
}

void lsStage::reset(){
  //for(int i = 0; i < this->_levels.size(); i++) this->_levels.get(i)->reset();L
  this->_isActive = false;
}

lsLevel &lsStage::addLevel(){
  _levels.add(new lsLevel(this->_strip->getNumLeds()));
  _levels.get(this->_levels.size()-1)->setParentStage(this);
  return *this->_levels.get(this->_levels.size()-1);
}

lsLevel &lsStage::lastLevel(){
  //return (this->_levels.size()==0) ? this->addLevel("Automatic Created 0") : *this->_stages.get(this->_stages.size()-1);
  return *this->_levels.get(this->_levels.size()-1);
}    

lsLevel &lsStage::getLevel(uint8_t num){
  return *this->_levels.get(num);
}

  void lsStage::printLeds(CRGB* displayLeds, int number){
    //Serial.println("");
    for(int j = 0; j < number; j++ ) {
    if(displayLeds[j].r<10) Serial.print(" ");
    if(displayLeds[j].r<100) Serial.print(" ");
    Serial.print(displayLeds[j].r);Serial.print(":");
    if(displayLeds[j].g<10) Serial.print(" ");
    if(displayLeds[j].g<100) Serial.print(" ");
    Serial.print(displayLeds[j].g);Serial.print(":");
    if(displayLeds[j].b<10) Serial.print(" ");
    if(displayLeds[j].b<100) Serial.print(" ");
    Serial.print(displayLeds[j].b);Serial.print(" - ");
    }
    Serial.println("");
  }
lsStage& lsStage::setParentShow(lsLedShow* show) {
  parentShow = show;
return *this;
}

void lsStage::render(unsigned long currentFrame) {
	if (_strip == nullptr || currentFrame < startAt) return;
	// Calculate the relative frame number within the scene
	//unsigned long relativeFrame = currentFrame - startAt + (frameCounter * (currentFrame - startAt));
  //Serial.print("\tStage FRAME ");Serial.print(currentFrame);
	CRGB* finalBuffer = new CRGB[_strip->getNumLeds()];
  for (int i = 0; i<_strip->getNumLeds();i++ ) finalBuffer[i]=CRGB::Black;
	//Serial.print("Frame Stage ");Serial.println(currentFrame);
  allLayersCompleted = true; // Assume all layers are completed until proven otherwise
	for (int i = 0; i < _levels.size(); ++i) {
    
		lsLevel* layer = _levels.get(i);
    //Serial.print("Frame Stage ");Serial.print(currentFrame);Serial.println("\t ");
		layer->render(currentFrame); // Render each layer to its own buffer
	  layer->blendLevels(finalBuffer); // Blend the layer's buffer into the final buffer
    if (!layer->isCompleted()) {
        allLayersCompleted = false;
    }
    
	}
  //Serial.print("Layer Complete ");Serial.println(allLayersCompleted);

	// Copy the final blended buffer to the ledStrip
  this->_strip->setLeds(finalBuffer);
	_strip->showStrip();

	delete[] finalBuffer; // Clean up the buffer

	//frameCounter++; // Increment the scene's frame counter
	if (allLayersCompleted) updateState();
}

void lsStage::updateState() {
  //Serial.println(".....................updateState ");
  currentRepeat++;
  if (currentRepeat >= repeatCount || allLayersCompleted) {
  // Reset for potential future repeats and notify parent show to move to the next scene
    currentRepeat = 0;
    //frameCounter = 0;
    allLayersCompleted = false;
    for (int i = 0; i < _levels.size(); ++i) { _levels.get(i)->reset();}
    parentShow->nextStage();
  }
}

JsonDocument lsStage::serialize(){
    JsonDocument doc;

      // Add values in the document
      doc["Name"] = this->_name;
      doc["Duration"] = this->_duration;
      doc["Repeat"] = this->repeatCount = 1;
      doc["StartAt"] = this->startAt = 0;


      // Add an array
      JsonArray data = doc["Levels"].to<JsonArray>();
      for(int i = 0; i < this->_levels.size(); i++){  
        data.add(this->_levels.get(i)->serialize());
      }
    return doc;
  }

  JsonDocument lsStage::serializeSimple(){
    JsonDocument doc;

      // Add values in the document
      doc["Name"]     = this->_name;
      doc["Duration"] = this->_duration;
      doc["Repeat"]   = this->repeatCount = 1;
      doc["StartAt"]  = this->startAt = 0;
      doc["Levels"]   = this->_levels.size();
      return doc;
  }
