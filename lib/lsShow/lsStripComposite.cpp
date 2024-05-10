#include "lsStripComposite.h"

void lsStripComposite::add(int numLeds, uint8_t pin) {
    _strips.add(new lsStrip(numLeds,pin));
}

void lsStripComposite::showStrip() {
    for (int i = 0;i<_strips.size();i++) {
        _strips.get(i)->showStrip();
    }
}

void lsStripComposite::setLeds(CRGB *newLeds) {
    for (int i = 0;i<_strips.size();i++) _strips.get(i)->setLeds(newLeds);
}

void lsStripComposite::setEffects(LS_MULTIPLE_STRIPS_EFFECTS effect){
    this->effect = effect;
};

void lsStripComposite::clear() {
    for (int i = 0;i<_strips.size();i++) _strips.get(i)->clear();
}

void lsStripComposite::clear(int i ) {
    _strips.get(i)->clear();
}

void lsStripComposite::drawColor(CRGB Color) { 
    for (int i = 0;i<_strips.size();i++) {
        _strips.get(i)->drawColor(Color);
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
