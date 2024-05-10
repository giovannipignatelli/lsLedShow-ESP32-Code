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

#include "lsStrip.h"
#include "lsDefinitions.h"
#include <FastLED.h>
#include "lsLinkedList.h"

#include <lsStruct_Enum.h>

void lsStrip::add(int numLeds, uint8_t pin){
	this->displayLeds = new CRGB[numLeds];
	this->_numLeds = numLeds;
	this->_pin = pin;
	// This code avoid the issue with the definition of the template in FastLed. Waiting for new version to come up with a structured solution
	// https://github.com/FastLED/FastLED/issues/282

	switch (pin){
		case 0:  FastLED.addLeds<STRIP_TYPE, 0 , COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		case 1:  FastLED.addLeds<STRIP_TYPE, 1 , COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		case 2:  FastLED.addLeds<STRIP_TYPE, 2 , COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		case 3:  FastLED.addLeds<STRIP_TYPE, 3 , COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		case 4:  FastLED.addLeds<STRIP_TYPE, 4, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		case 5:  FastLED.addLeds<STRIP_TYPE, 5, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		//case 6:  FastLED.addLeds<STRIP_TYPE, 6, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		//case 7:  FastLED.addLeds<STRIP_TYPE, 7, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		//case 8:  FastLED.addLeds<STRIP_TYPE, 8, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		//case 9:  FastLED.addLeds<STRIP_TYPE, 9, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		//case 10: FastLED.addLeds<STRIP_TYPE, 10, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		case 11: FastLED.addLeds<STRIP_TYPE, 11, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		case 12: FastLED.addLeds<STRIP_TYPE, 12, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		case 13: FastLED.addLeds<STRIP_TYPE, 13, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		case 14: FastLED.addLeds<STRIP_TYPE, 14, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		case 15: FastLED.addLeds<STRIP_TYPE, 15, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		case 16: FastLED.addLeds<STRIP_TYPE, 16, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		case 17: FastLED.addLeds<STRIP_TYPE, 17, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		case 18: FastLED.addLeds<STRIP_TYPE, 18, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		case 19: FastLED.addLeds<STRIP_TYPE, 19, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		//case 20: FastLED.addLeds<STRIP_TYPE, 20, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		case 21: FastLED.addLeds<STRIP_TYPE, 21, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		case 22: FastLED.addLeds<STRIP_TYPE, 22, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		case 23: FastLED.addLeds<STRIP_TYPE, 23, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		//case 24: FastLED.addLeds<STRIP_TYPE, 24, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		case 25: FastLED.addLeds<STRIP_TYPE, 25, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		case 26: FastLED.addLeds<STRIP_TYPE, 26, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		case 27: FastLED.addLeds<STRIP_TYPE, 27, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		//case 28: FastLED.addLeds<STRIP_TYPE, 28, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		//case 29: FastLED.addLeds<STRIP_TYPE, 29, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		//case 30: FastLED.addLeds<STRIP_TYPE, 30, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		//case 31: FastLED.addLeds<STRIP_TYPE, 31, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		case 32: FastLED.addLeds<STRIP_TYPE, 32, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		case 33: FastLED.addLeds<STRIP_TYPE, 33, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		//case 34: FastLED.addLeds<STRIP_TYPE, 34, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		//case 35: FastLED.addLeds<STRIP_TYPE, 35, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		//case 36: FastLED.addLeds<STRIP_TYPE, 36, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		//case 37: FastLED.addLeds<STRIP_TYPE, 37, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		//case 38: FastLED.addLeds<STRIP_TYPE, 38, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		//case 39: FastLED.addLeds<STRIP_TYPE, 39, COLOR_ORDER>(displayLeds, _numLeds).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);break;
		case 100:break;
	}
}

int lsStrip::getNumLeds() { return this->_numLeds; }

CRGB *lsStrip::getLeds() { return this->displayLeds ;}

void lsStrip::clear() { fill_solid(this->displayLeds, this->_numLeds, CRGB::Black); }

void lsStrip::printLeds(int num){
  //Serial.println("");
  for(int j = 0; j < num; j++ ) {
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

void lsStrip::printLeds(){printLeds(this->_numLeds);}

void lsStrip::fadeAllToBlack( byte fadeValue) {
	for (int j=0; j < this->_numLeds; j++) { 
		fadeToBlackBy(this->displayLeds,this->_numLeds,fadeValue);
	}
}

void lsStrip::setLeds(CRGB *newLeds){
	for(int j = 0; j < this->_numLeds; j++ ) { 
		displayLeds[j] = newLeds[j];
	}
} 

void lsStrip::flush(CRGB ColorFill, int offset){
	for(int j = this->_numLeds-offset;j > offset-1;j--) displayLeds[j] = displayLeds[j-offset];
	for(int j = 0;j<offset;j++)  displayLeds[j] = ColorFill;
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

void lsStrip::drawColor(CRGB Color) { fill_solid(this->displayLeds, this->_numLeds, Color);}
void lsStrip::drawRainbow(uint8_t initialhue, uint8_t deltahue) { 	fill_rainbow(this->displayLeds, this->_numLeds,  initialhue,  deltahue); }
void lsStrip::drawRainbowC(uint8_t initialhue, bool reversed) { 	fill_rainbow(this->displayLeds, this->_numLeds,  initialhue,  reversed); }
void lsStrip::drawGradient(CRGB c1, CRGB c2) {fill_gradient_RGB (this->displayLeds, this->_numLeds, c1, c2);};
void lsStrip::drawPalette(CRGBPalette16 palette, TBlendType blendType) {fill_palette(this->displayLeds, this->_numLeds, 0, 255/this->_numLeds ,palette, 255, blendType);};
void lsStrip::drawPaletteC(CRGBPalette16 palette, TBlendType blendType, bool reversed) {fill_palette_circular(this->displayLeds, this->_numLeds, 0, palette, 255, blendType, reversed);}
void lsStrip::drawPattern(LS_PATTERN_STRIP *pattern, int positions) {
  int pixel = 0;
  while (pixel < this->_numLeds) {
	for(int j = 0; j < positions; j++ ) {
	  for(int i = 0; i < pattern[j].stripSize; i++ ) {
		this->displayLeds[pixel] = pattern[j].stripColor;
		pixel++;
	  }
	}
  }
}

void lsStrip::applyMask(uint8_t *maskStrip){

  	for(int j = 0; j < this->_numLeds; j++ ) { 
		this->displayLeds[j] *= maskStrip[j];
  	}
}

