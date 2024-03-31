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
  _levels.add(new lsLevel(this->_Strip->getNumLeds()));
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
	if (_Strip == nullptr || currentFrame < startAt) return;
	// Calculate the relative frame number within the scene
	//unsigned long relativeFrame = currentFrame - startAt + (frameCounter * (currentFrame - startAt));

	CRGB* finalBuffer = new CRGB[_Strip->getNumLeds()];
  for (int i = 0; i<_Strip->getNumLeds();i++ ) finalBuffer[i]=CRGB::Black;
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
  this->_Strip->setLeds(finalBuffer);
	_Strip->showStrip();

	delete[] finalBuffer; // Clean up the buffer

	//frameCounter++; // Increment the scene's frame counter
	if (allLayersCompleted) updateState();
}

void lsStage::updateState() {

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
/*
void lsStage::activate() {
  //this->_isActive = true;
  //this->_Strip->clear();
}

void lsStage::deactivate() {
  //this->_isActive = false;
}
*/