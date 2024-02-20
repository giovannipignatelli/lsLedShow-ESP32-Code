#include "lsShow.h"

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
  currentStageFrame = 0;
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
  if(currentMillis >= _nextTickMillis) {
    _nextTickMillis = (currentMillis + _tickMillis);
    lsStage *stage;
    stage = _stages.get(currentStageIndex);
    stage->render(currentStageFrame);
    _Strip->showStrip();
    currentStageFrame++;
  }
}
