#include "lsStripMultiple.h"

void lsStripMultiple::clear(int stripIndex) {
    if (stripIndex == -1) {
        for (int i = 0; i < stripIndex; i++) {
            fill_solid(displayLeds[i], numLeds, CRGB::Black);
        }
    } else if (stripIndex >= 0 && stripIndex < stripIndex) {
        fill_solid(displayLeds[stripIndex], numLeds, CRGB::Black);
    }
}

void lsStripMultiple::flush(CRGB ColorFill, int offset, int stripIndex) {
    if (stripIndex == -1) {
        for (int i = 0; i < stripIndex; i++) {
            // Implement flush for all strips with offset
        }
    } else if (stripIndex >= 0 && stripIndex < stripIndex) {
        // Implement flush for a single strip with offset
    }
}

void lsStripMultiple::drawColor(CRGB Color, int stripIndex) {
    if (stripIndex == -1) {
        for (int i = 0; i < numStrips; i++) {
            fill_solid(displayLeds[i], numLeds, Color);
        }
    } else if (stripIndex >= 0 && stripIndex < numStrips) {
        fill_solid(displayLeds[stripIndex], numLeds, Color);
    }
}

void lsStripMultiple::replicateToAllStrips(int sourceIndex, int offset) {
    if (sourceIndex < 0 || sourceIndex >= numStrips) return;

    for (int i = 0; i < numStrips; i++) {
        if (i != sourceIndex) {
            // Similar to previously discussed logic for replication with offset
        }
    }
}