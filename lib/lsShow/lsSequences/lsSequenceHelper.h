#include "lsSequences/lsSequences.h"

class lsSequenceHelper {
  public:
    static lsSequence * getSequence(LS_SEQUENCES_TYPES type){
      switch (type)
      {
        case(LS_SEQUENCES_TYPES::lsSequenceFill):
        {
          return new lsSequenceFill();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceScan):
        {
          return new lsSequenceScan();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceConfetti):
        {
          return new lsSequenceConfetti();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceLightning):
        {
          return new lsSequenceLightning();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceGlitter):
        {
          return new lsSequenceGlitter();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceSparkle):
        {
          return new lsSequenceSparkle();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceBPM):
        {
          return new lsSequenceBPM();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceSinelon):
        {
          return new lsSequenceSinelon();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceStrobe):
        {
          return new lsSequenceStrobe();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceColorBars):
        {
          return new lsSequenceColorBars();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceBeat8Tail):
        {
          return new lsSequenceBeat8Tail();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceCellularNoise):
        {
          return new lsSequenceCellularNoise();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceTargetA):
        {
          return new lsSequenceTargetA();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceTargetB):
        {
          return new lsSequenceTargetB();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequencePopupDroid):
        {
          return new lsSequencePopupDroid();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceBouncingBars):
        {
          return new lsSequenceBouncingBars();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceBouncingBar):
        {
          return new lsSequenceBouncingBar();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceComet):
        {
          return new lsSequenceComet();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceElectricity):
        {
          return new lsSequenceElectricity();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceJuggle):
        {
          return new lsSequenceJuggle();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequencePaletteBreathe):
        {
          return new lsSequencePaletteBreathe();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequencePaletteDissolve):
        {
          return new lsSequencePaletteDissolve();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequencePaletteGradient):
        {
          return new lsSequencePaletteGradient();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequencePaletteWave):
        {
          return new lsSequencePaletteWave();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceSparkles):
        {
          return new lsSequenceSparkles();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceTeatherChase):
        {
          return new lsSequenceTeatherChase();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceWanderingLine):
        {
          return new lsSequenceWanderingLine();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceBlink):
        {
          return new lsSequenceBlink();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceWipe):
        {
          return new lsSequenceWipe();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceSingleDynamic):
        {
          return new lsSequenceSingleDynamic();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceSweep):
        {
          return new lsSequenceSweep();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceFillUp):
        {
          return new lsSequenceFillUp();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceTetris):
        {
          return new lsSequenceTetris();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceSandWatch):
        {
          return new lsSequenceSandWatch();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceAndroid):
        {
          return new lsSequenceAndroid();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceAurora):
        {
          return new lsSequenceAurora();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceGroup):
        {
          return new lsSequenceGroup();
          break;
        }
        case(LS_SEQUENCES_TYPES::lsSequenceDigitalRain):
        {
          return new lsSequenceDigitalRain();
          break;
        }
      }
  }
};

