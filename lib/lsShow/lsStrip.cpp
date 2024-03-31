#include "lsStrip.h"
#include <FastLED.h>
#include <LinkedList.h>
#include <lsStruct_Enum.h>

int lsStrip::getNumLeds() { return this->numLeds; }

CRGB *lsStrip::getLeds() { return this->displayLeds ;}

void lsStrip::clear() { fill_solid(this->displayLeds, this->numLeds, CRGB::Black); }

void lsStrip::printLeds(){
  //Serial.println("");
  for(int j = 0; j < this->numLeds; j++ ) {
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

void lsStrip::fadeAllToBlack( byte fadeValue) {
for (int j=0; j < this->numLeds; j++) { 
	fadeToBlackBy(this->displayLeds,this->numLeds,fadeValue);
}
}

void lsStrip::setLeds(CRGB *newLeds){
  for(int j = 0; j < this->numLeds; j++ ) { 
	displayLeds[j] = newLeds[j];
  }
} 

void lsStrip::showStrip() {
  #ifdef ADAFRUIT_NEOPIXEL_H 
	// NeoPixel
	strip.show();
  #endif
  #ifndef ADAFRUIT_NEOPIXEL_H
	// FastLED
	FastLED.show();
  #endif
}

void lsStrip::setPixel(int Strip, int Pixel, CRGB Color) {
  #ifdef ADAFRUIT_NEOPIXEL_H 
	// NeoPixel
	strip.setPixelColor(Pixel, strip.Color(Color.r, Color.g, Color.b));
  #endif
  #ifndef ADAFRUIT_NEOPIXEL_H 
	// FastLED
	displayLeds[Pixel].r = Color.r;
	displayLeds[Pixel].g = Color.g;
	displayLeds[Pixel].b = Color.b;
  #endif
}

void lsStrip::drawColor(CRGB Color) { fill_solid(this->displayLeds, this->numLeds, Color); }
void lsStrip::drawRainbow(uint8_t initialhue, uint8_t deltahue) { 	fill_rainbow(this->displayLeds, this->numLeds,  initialhue,  deltahue); }
void lsStrip::drawRainbowC(uint8_t initialhue, bool reversed) { 	fill_rainbow(this->displayLeds, this->numLeds,  initialhue,  reversed); }
void lsStrip::drawGradient(CRGB c1, CRGB c2) {fill_gradient_RGB (this->displayLeds, this->numLeds, c1, c2);};
void lsStrip::drawPalette(CRGBPalette16 palette, TBlendType blendType) {fill_palette(this->displayLeds, this->numLeds, 0, 255/this->numLeds ,palette, 255, blendType);};
void lsStrip::drawPaletteC(CRGBPalette16 palette, TBlendType blendType, bool reversed) {fill_palette_circular(this->displayLeds, this->numLeds, 0, palette, 255, blendType, reversed);}
void lsStrip::drawPattern(lsPatternStrip *pattern, int positions) {
  int pixel = 0;
  while (pixel < this->numLeds) {
	for(int j = 0; j < positions; j++ ) {
	  for(int i = 0; i < pattern[j].stripSize; i++ ) {
		this->displayLeds[pixel] = pattern[j].stripColor;
		pixel++;
	  }
	}
  }
}

void lsStrip::applyMask(uint8_t *maskStrip){

  	for(int j = 0; j < this->numLeds; j++ ) { 
		this->displayLeds[j] *= maskStrip[j];
  	}
}