#include "lsSequence.h"

class lsSequenceCellularNoise : public lsSequence {
  public:



    lsSequenceCellularNoise(uint8_t dens,u_int8_t sc, uint8_t speed) {
      _param1 = dens;
      _param2 = sc;
      _param3 = speed;
      _type=LS_SEQUENCES_TYPES::lsSequenceCellularNoise;
    }

    lsSequenceCellularNoise() {
      _param1 = 150;  // Adjust this value to control the density of cells
      _param2 = 16;     // Adjust this value to control the size of cells
      _param3 = 4; // Adjust this value to control the color animation speed
      _type=LS_SEQUENCES_TYPES::lsSequenceCellularNoise;
    }

    void getFirstFrameRender(CRGB * leds)  {
      fill_solid(leds,STRIP_NUM_LEDS,SEQUENCE_SECONDARY_COLOR);
    };


    void draw(unsigned long frame) {
      for (uint16_t i = 0; i < STRIP_NUM_LEDS; i++) {
        // Calculate the cellular noise value for the current pixel
        uint8_t value = inoise8(i * _param2, millis() / _param3) % 255;

        // Map the noise value to the LED's color range
        //STRIP_LEDS(i) = ColorFromPalette(RainbowColors_p, value, 255, LINEARBLEND);
        setPixel(i,ColorFromPalette(RainbowColors_p, value, 255, LINEARBLEND));
        // Apply density threshold to create cells
        if (value > _param1) {
          //STRIP_LEDS(i) = CRGB::Black;  // Set the cell color to black
          setPixel(i,CRGB::Black);
        }
      }
    }

    void update(unsigned long frame) {
    }

    void postRender() {
    }

};
