#include "lsLevel.h"

    CRGB *lsLevel::getLeds() { return this->_Strip->getLeds();};

    lsLevel &lsLevel::setOpacity(float newOpacity){
      _opacity = constrain(newOpacity, 0.0f, 1.0f); 
      return *this;
    }

  void lsLevel::printLeds(CRGB* displayLeds, int number){
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

void lsLevel::blendLevels(CRGB* ledStripBuffer) {
    CRGB pixel;
    for (int i = 0; i < numLeds; ++i) {
        // Pre-apply opacity to the layer's pixel
        pixel = this->_Strip->getLeds()[i];
        pixel.fadeLightBy(255 * (1.0 - _opacity)); // Adjusting pixel's brightness based on opacity

        // Perform blending based on the layer's blend mode
        switch (blendMode) {
            case lsBlendMode::ADD: {
                ledStripBuffer[i] += pixel;
                break;
            }
            case lsBlendMode::SUBTRACT: {
                //Serial.println("Subtracting pixel values while avoiding underflow");
                ledStripBuffer[i].r = max(0, ledStripBuffer[i].r - pixel.r);
                ledStripBuffer[i].g = max(0, ledStripBuffer[i].g - pixel.g);
                ledStripBuffer[i].b = max(0, ledStripBuffer[i].b - pixel.b);
                break;
            }
            case lsBlendMode::MULTIPLY: {
                // Multiplying pixel values
                ledStripBuffer[i].r = (ledStripBuffer[i].r * pixel.r) / 255;
                ledStripBuffer[i].g = (ledStripBuffer[i].g * pixel.g) / 255;
                ledStripBuffer[i].b = (ledStripBuffer[i].b * pixel.b) / 255;
                break;
            }
            case lsBlendMode::FUSE_UP: {
                ledStripBuffer[i] |= pixel;
                break;
            }
            case lsBlendMode::FUSE_DOWN: {
                ledStripBuffer[i] &= pixel;
                break;
            }
            case lsBlendMode::N_BLEND: {
                blend(ledStripBuffer[i],pixel, _opacity);
                break;
            }
            case lsBlendMode::COVER: {
                if (pixel != CRGB::Black) ledStripBuffer[i] = pixel;
                break;
            }

            // Additional blend modes can be implemented here
            default:
                // No action for unsupported blend modes
                break;
        }
    }
}

lsLevel& lsLevel::setParentStage(lsStage* stage) {
  parentStage = stage;
  return *this;
}

    lsSequence &lsLevel::addSequence(lsSequence *seq){
      seq->startAt((_sequences.size()==0) ? 0 : _sequences.get(this->_sequences.size()-1)->getLastFrame());
      seq->setStrip(this->_Strip);
      seq->setParentLevel(this);
      _sequences.add(seq);
      return *this->_sequences.get(this->_sequences.size()-1);
    }

    lsSequence &lsLevel::lastSequence(){
      return *this->_sequences.get(this->_sequences.size()-1);
    }    

    lsSequence &lsLevel::getSequence(int num){
      return *this->_sequences.get(num);
    }   

    void lsLevel::render(uint8_t currentFrame) {
      if (_sequences.size()>0 && _current_sequence < _sequences.size()) {
       // Serial.print("-Frame Level ");Serial.print(currentFrame);Serial.print("\t ");Serial.print(" Effetto "); Serial.println(_current_sequence);
        _sequences.get(this->_current_sequence)->render(currentFrame);
      }
    }

  void lsLevel::effectCompleted() {
      //Serial.print("Effetto Completato ");Serial.println(_current_sequence);
      // Assuming effects are sequential and non-overlapping for simplicity
      _sequences.get(this->_current_sequence)->postRender();
      _current_sequence++;
      if (_current_sequence >= _sequences.size()) {
          completed = true; // No more effects to render
          _current_sequence = 0; // Optionally reset for looping
      }
      _sequences.get(this->_current_sequence)->preRender();
  }

  void lsLevel::reset(){
      completed = false; 
      _current_sequence = 0; // Optionally reset for looping
}