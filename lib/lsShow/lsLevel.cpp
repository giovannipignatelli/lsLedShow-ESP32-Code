#include "lsLevel.h"

    CRGB *lsLevel::getLeds() { return this->_Strip->getLeds();};

    lsLevel &lsLevel::setOpacity(float newOpacity){
      _opacity = constrain(newOpacity, 0.0f, 1.0f); 
      return *this;
    }

void lsLevel::blendLevels(CRGB* ledStripBuffer) {
    for (int i = 0; i < numLeds; ++i) {
        // Pre-apply opacity to the layer's pixel
        CRGB pixel = buffer[i];
        pixel.fadeLightBy(255 * (1.0 - _opacity)); // Adjusting pixel's brightness based on opacity

        // Perform blending based on the layer's blend mode
        switch (blendMode) {
            case lsBlendMode::ADD: {
                ledStripBuffer[i] += pixel;
                break;
            }
            case lsBlendMode::SUBTRACT: {
                // Subtracting pixel values while avoiding underflow
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

            // Additional blend modes can be implemented here
            default:
                // No action for unsupported blend modes
                break;
        }
    }
}

/*
    void lsLevel::blend(CRGB *ledStripBuffer){
      (this->*fusion)(ledStripBuffer);
    }

    lsLevel &lsLevel::setBlendMode(lsBlendMode mode){
      switch(mode) {
        case lsBlendMode::ADD:
          this->fusion = &lsLevel::mergeAdd;
          break;
        case lsBlendMode::SUBTRACT:
          this->fusion = &lsLevel::mergeSubtract;
          break;
        case lsBlendMode::FUSE_UP:
          this->fusion = &lsLevel::mergeUp;
          break;
        case lsBlendMode::FUSE_DOWN:
          this->fusion = &lsLevel::mergeDown;
          break;
        case lsBlendMode::N_BLEND:
          this->fusion = &lsLevel::mergeBlend;
          break;
      }
      return *this; 
    }

    void lsLevel::mergeAdd(CRGB *targetLayer) {      
        for(int i = 0; i < numLeds; i++) {
          targetLayer[i] += this->getLeds()[i];
        }
    };

    void lsLevel::mergeSubtract(CRGB *targetLayer) {
        for(int i = 0; i < numLeds; i++) targetLayer[i] -= this->getLeds()[i];
    };

    void lsLevel::mergeUp(CRGB *targetLayer) {
        for(int i = 0; i < numLeds; i++) targetLayer[i] |= this->getLeds()[i];
    };

    void lsLevel::mergeDown(CRGB *targetLayer) {
        for(int i = 0; i < numLeds; i++) targetLayer[i] &= this->getLeds()[i];
    };

    void lsLevel::mergeBlend(CRGB *targetLayer) {
      nblend(targetLayer, this->getLeds(), numLeds, this->_opacity);  
    };
*/
    lsSequence &lsLevel::addSequence(lsSequence *seq){
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
      Serial.print("Renderizzo Livello...");
      if (_sequences.size()>0 && currentEffectIndex < _sequences.size()) {
        _sequences.get(this->_current_sequence)->render(currentFrame);
      }
      else {
        completed = true; // Mark as completed if there are no effects or all have been rendered
      }
      Serial.println("Fatto!");
    }

  void lsLevel::effectCompleted() {
      // Assuming effects are sequential and non-overlapping for simplicity
      currentEffectIndex++;
      if (currentEffectIndex >= _sequences.size()) {
          completed = true; // No more effects to render
          currentEffectIndex = 0; // Optionally reset for looping
      }
  }