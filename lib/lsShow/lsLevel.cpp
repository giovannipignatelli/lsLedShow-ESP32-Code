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

#include "lsLevel.h"
#define CURRENT_SEQUENCE this->_current_sequence

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
    for (int i = 0; i < STRIP_NUM_LEDS; ++i) {
        // Pre-apply opacity to the layer's pixel
        pixel = this->_Strip->getLeds()[i];
        pixel.fadeLightBy(255 * (1.0 - _opacity)); // Adjusting pixel's brightness based on opacity

        // Perform blending based on the layer's blend mode
        switch (_blendMode) {
            case LS_BLENDMODE::ADD: {
                ledStripBuffer[i] += pixel;
                break;
            }
            case LS_BLENDMODE::SUBTRACT: {
                //Serial.println("Subtracting pixel values while avoiding underflow");
                ledStripBuffer[i].r = max(0, ledStripBuffer[i].r - pixel.r);
                ledStripBuffer[i].g = max(0, ledStripBuffer[i].g - pixel.g);
                ledStripBuffer[i].b = max(0, ledStripBuffer[i].b - pixel.b);
                break;
            }
            case LS_BLENDMODE::MULTIPLY: {
                // Multiplying pixel values
                ledStripBuffer[i].r = (ledStripBuffer[i].r * pixel.r) / 255;
                ledStripBuffer[i].g = (ledStripBuffer[i].g * pixel.g) / 255;
                ledStripBuffer[i].b = (ledStripBuffer[i].b * pixel.b) / 255;
                break;
            }
            case LS_BLENDMODE::FUSE_UP: {
                ledStripBuffer[i] |= pixel;
                break;
            }
            case LS_BLENDMODE::FUSE_DOWN: {
                ledStripBuffer[i] &= pixel;
                break;
            }
            case LS_BLENDMODE::N_BLEND: {
                blend(ledStripBuffer[i],pixel, _opacity);
                break;
            }
            case LS_BLENDMODE::COVER: {
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

    lsSequence &lsLevel::getNextSequence(){
      if(CURRENT_SEQUENCE == _sequences.size()-1)
        return *this->_sequences.get(0);
      else
        return *this->_sequences.get(CURRENT_SEQUENCE+1);
    }

    void lsLevel::render(unsigned long currentFrame) {
      //Serial.print("\tLevel FRAME ");Serial.print(currentFrame);
      if (_sequences.size()>0 && CURRENT_SEQUENCE < _sequences.size() && !completed) {
        _sequences.get(CURRENT_SEQUENCE)->render(currentFrame);
        
      }
    }

  void lsLevel::sequenceCompleted(unsigned long currentFrame) {
      _sequences.get(CURRENT_SEQUENCE)->postRender();
      _sequences.get(CURRENT_SEQUENCE)->reset();
      CURRENT_SEQUENCE++;
      if (CURRENT_SEQUENCE == _sequences.size()) {
          completed = true; // No more effects to render
          CURRENT_SEQUENCE = 0; // Optionally reset for looping
      }
      else {
        _sequences.get(CURRENT_SEQUENCE)->startAt(currentFrame++);
        if (!_sequences.get(CURRENT_SEQUENCE)->hasTransitionIn()) _sequences.get(CURRENT_SEQUENCE)->preRender();
      }
  }

  void lsLevel::reset(){
      completed = false; 
      CURRENT_SEQUENCE = 0; // Optionally reset for looping
  }

  JsonDocument lsLevel::serialize(){
    JsonDocument doc;

      // Add values in the document
      doc["Opacity"] = this->_opacity;
      doc["BlendMode"] = static_cast<int>(this->_blendMode);


      // Add an array
      JsonArray data = doc["Sequences"].to<JsonArray>();
      for(int i = 0; i < this->_sequences.size(); i++){  
        data.add(this->_sequences.get(i)->serialize());
      }
    return doc;
  }