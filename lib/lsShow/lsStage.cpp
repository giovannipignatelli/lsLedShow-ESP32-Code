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
  //for(int i = 0; i < this->_levels.size(); i++) this->_levels.get(i)->reset();
  this->_currentFrame=0;
  this->_isActive = false;
}

lsLevel &lsStage::addLevel(){
   Serial.println("lsStage aggiungo un livello");
  _levels.add(new lsLevel(this->_Strip->getNumLeds()));
  return *this->_levels.get(this->_levels.size()-1);
}

lsLevel &lsStage::lastLevel(){
  //return (this->_levels.size()==0) ? this->addLevel("Automatic Created 0") : *this->_stages.get(this->_stages.size()-1);
  return *this->_levels.get(this->_levels.size()-1);
}    

lsLevel &lsStage::getLevel(uint8_t num){
  return *this->_levels.get(num);
}   

lsStage& lsStage::setParentShow(lsLedShow* show) {
  parentShow = show;
return *this;
}

/*
void lsStage::render() {

  //this->_isActive = (this->_currentFrame < this->_duration && this->_duration > 0 || th) ? true : false;
  if (this->_isActive) {
      Serial.println("Renderizzo Stage");
	for (int i = 0; i<this->_levels.size(); i++ ) { _levels.get(i)->render(this->_currentFrame); }
	this->mergeLevels();
	this->_currentFrame++;
  }
}

void lsStage::mergeLevels(){
  CRGB tgtLeds[this->_Strip->getNumLeds()];
  for (int i = 0; i < this->_Strip->getNumLeds(); i++ ) {
	tgtLeds[i] = _levels.get(0)->getLeds()[i];
  }
  for (int j = 1; j < this->_levels.size(); j++ ){
	_levels.get(j)->merge(tgtLeds,this->_Strip->getNumLeds());
  }
  this->_Strip->setLeds(tgtLeds);
}
*/

void lsStage::render(unsigned long currentFrame) {
  
	if (_Strip == nullptr || currentFrame < startAt) return;
	// Calculate the relative frame number within the scene
  Serial.print("Renderizzo lo stage al frame ");
  Serial.println(currentFrame);
	unsigned long relativeFrame = currentFrame - startAt + (frameCounter * (currentFrame - startAt));

	CRGB* finalBuffer = new CRGB[_Strip->getNumLeds()];
  for (int i = 0; i<_Strip->getNumLeds();i++ ) finalBuffer[i]=CRGB::White;
	//memset(finalBuffer, 0, _Strip->getNumLeds() * sizeof(CRGB)); // Initialize the final buffer
	allLayersCompleted = true; // Assume all layers are completed until proven otherwise
  Serial.print("Renderizzo i livelli ");
	for (int i = 0; i < _levels.size(); ++i) {
		lsLevel* layer = _levels.get(i);
		layer->render(relativeFrame); // Render each layer to its own buffer
    Serial.print("Inizio il blending ");
		layer->blendLevels(finalBuffer); // Blend the layer's buffer into the final buffer
    if (!layer->isCompleted()) {
        allLayersCompleted = false;
    }
    Serial.print("Finito il Blending ");
	}

	// Copy the final blended buffer to the ledStrip

  this->_Strip->setLeds(finalBuffer);
	_Strip->showStrip();

	delete[] finalBuffer; // Clean up the buffer

	frameCounter++; // Increment the scene's frame counter
	if (allLayersCompleted) updateState();
}

void lsStage::updateState() {
  Serial.print("Mi aggiorno ");
  currentRepeat++;
  if (currentRepeat >= repeatCount || allLayersCompleted) {
  // Reset for potential future repeats and notify parent show to move to the next scene
    currentRepeat = 0;
    frameCounter = 0;
    allLayersCompleted = false;
    parentShow->nextStage();
  }
}

void lsStage::activate() {
  this->_isActive = true;
  this->_Strip->clear();
}

void lsStage::deactivate() {
  this->_isActive = false;
}