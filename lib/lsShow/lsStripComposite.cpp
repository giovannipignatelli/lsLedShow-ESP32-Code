#include "lsStripComposite.h"

void lsStripComposite::add(int numLeds, uint8_t pin) {
    _strips.add(new lsStrip(numLeds,pin));
}

void lsStripComposite::showStrip() {
    for (int i = 0;i<_strips.size();i++) {
        _strips.get(i)->showStrip();
    }
}

void lsStripComposite::setChangeIndexEveryNFrames(uint32_t frames){
      this->changeCurrentIndexEveryNframes = frames;
      this->nextChangeFrame = changeCurrentIndexEveryNframes;
    }

 void lsStripComposite::reverseLeds(CRGB *toRevert, int size){
    for (int i = 0;i<size;i++) this->reversed[i] = toRevert[size-i-1];
}


void lsStripComposite::setLeds(CRGB *newLeds ) {
    currentFrame++;
    if (currentFrame >= this->nextChangeFrame ){
        nextChangeFrame+=this->changeCurrentIndexEveryNframes;
        current_Strip++;
        if (current_Strip == _strips.size()) current_Strip=0;
    }
    switch(this->effect){
        case (LS_MULTIPLE_STRIPS_EFFECTS::lsNone):{
            for (int i = 0;i<_strips.size();i++) _strips.get(i)->setLeds(newLeds);
            break;
            }
        case (LS_MULTIPLE_STRIPS_EFFECTS::lsAlternate):{
            for (int i = 0;i<_strips.size();i++) {
                if (i % 2 == current_Strip % 2) _strips.get(i)->setLeds(newLeds);
                else _strips.get(i)->clear();
            }
            break;
            }
        case (LS_MULTIPLE_STRIPS_EFFECTS::lsRound):{
            _strips.get(current_Strip)->setLeds(newLeds);
            if (current_Strip==0)  _strips.get(_strips.size()-1)->clear();
            else _strips.get(current_Strip-1)->clear();
            break;
            }
        case (LS_MULTIPLE_STRIPS_EFFECTS::lsAlternateReversed):{
            reverseLeds(newLeds,NUM_LEDS);
            for (int i = 0;i<_strips.size();i++) {
                if (i % 2 == 0) _strips.get(i)->setLeds(newLeds);
                else _strips.get(i)->setLeds(this->reversed);
            }
            break;
            }
        case (LS_MULTIPLE_STRIPS_EFFECTS::lsOffset):{
            for (int i = 0;i<_strips.size();i++) {
                _strips.get(i)->setLeds(newLeds,i*this->_offSet);
            }
            break;
            }
        case (LS_MULTIPLE_STRIPS_EFFECTS::lsCarousel):{
            _strips.get(current_Strip)->setLeds(newLeds);
            break;
            }
        }
}

void lsStripComposite::setEffects(LS_MULTIPLE_STRIPS_EFFECTS effect, int Parameter){
    this->effect = effect;
    switch(this->effect){
        case (LS_MULTIPLE_STRIPS_EFFECTS::lsNone):{
            break;
            }
        case (LS_MULTIPLE_STRIPS_EFFECTS::lsAlternate):{
            break;
            }
        case (LS_MULTIPLE_STRIPS_EFFECTS::lsRound):{
            break;
            }
        case (LS_MULTIPLE_STRIPS_EFFECTS::lsAlternateReversed):{
            break;
            }
        case (LS_MULTIPLE_STRIPS_EFFECTS::lsOffset):{
            this->_offSet = Parameter;
            break;
            }
        }
};

void lsStripComposite::clear() {
    for (int i = 0;i<_strips.size();i++) _strips.get(i)->clear();
}

void lsStripComposite::clear(int i ) {
    _strips.get(i)->clear();
}

void lsStripComposite::drawColor(CRGB Color) {
    switch(this->effect){
    case (LS_MULTIPLE_STRIPS_EFFECTS::lsNone):{
        for (int i = 0;i<_strips.size();i++) {
            _strips.get(i)->drawColor(Color);
        }
        break;
        }
    case (LS_MULTIPLE_STRIPS_EFFECTS::lsAlternate):{
        for (int i = 0;i<_strips.size();i++) {
            _strips.get(i)->drawColor(Color);
        }
        break;
        }
    }
}

void lsStripComposite::drawRainbow(uint8_t initialhue, uint8_t deltahue) { 
    for (int i = 0;i<_strips.size();i++) _strips.get(i)->drawRainbow( initialhue,  deltahue);
}

void lsStripComposite::drawRainbowC(uint8_t initialhue, bool reversed){ 
    for (int i = 0;i<_strips.size();i++) _strips.get(i)->drawRainbowC(initialhue, reversed);
}

void lsStripComposite::drawGradient(CRGB c1, CRGB c2) {
    for (int i = 0;i<_strips.size();i++) _strips.get(i)->drawGradient( c1,  c2);
}

void lsStripComposite::drawPalette(CRGBPalette16 palette, TBlendType blendType) {
    for (int i = 0;i<_strips.size();i++) _strips.get(i)->drawPalette( palette,  blendType) ;
}
void lsStripComposite::drawPaletteC(CRGBPalette16 palette, TBlendType blendType, bool reversed) {
    for (int i = 0;i<_strips.size();i++) _strips.get(i)->drawPaletteC(palette,  blendType,  reversed);
}

void lsStripComposite::drawPattern(LS_PATTERN_STRIP *pattern, int positions) {
    for (int i = 0;i<_strips.size();i++) _strips.get(i)->drawPattern(pattern,  positions);
}
