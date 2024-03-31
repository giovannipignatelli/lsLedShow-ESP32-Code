/*
 * Project: Led Show
 * Author: Giovanni Pignatelli
 * License: MIT (Open Source)
 * 
 * Inspirations:
 * - qpQuickPatterns from brimshot https:
github.com/brimshot/quickPatterns
 * - atuline https://github.com/atuline/FastLED-Demos
 * - WS2812FX from kitesurfer1404 https://github.com/kitesurfer1404/WS2812FX/tree/master/examples
 * - https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/
 * 
 * Versioning:
 * - v1.0.0: Initial release
 * 
 * Description: [Description of what the file does]
 */

#ifndef QP_ENUMS_H
#define QP_ENUMS_H

#define FSH(x) (__FlashStringHelper*)(x)

#include <FastLED.h>
#include <LinkedList.h>

struct LS_PATTERN_STRIP{CRGB stripColor;int  stripSize; };
struct LS_MASK{ uint8_t fadeValue; int  stripSize; };
struct LS_COLOR_UPDATE {bool FG; bool BG ; bool TG;};

//enum LS_SEQUENCE_COLORING {FIXEDCOLOR, RANDOMCOLOR, PALETTECOLOR};
enum LS_FILL_TYPES {SOLID,RANDOMSOLID,RANDOMSINGLE,RAINBOW,RAINBOWCIRCULAR,GRADIENT,PALETTE,PALETTECIRCULAR,PATTERN,COLORSET};
//enum LS_MERGE_TYPES {ADD,SUBTRACT,COMBINEUP,COMBINEDOWN,BLEND,MASK};
enum LS_FILTER {RED,GREEN,BLUE};
enum class LS_BLENDMODE {
    ADD,
    SUBTRACT,
    MULTIPLY,
    FUSE_UP,    // New blend mode using |= operator for 'fusing' colors upwards
    FUSE_DOWN,  // New blend mode using &= operator for 'fusing' colors downwards
    N_BLEND,    // New blend mode using FastLED's nblend method for smooth blending
    COVER,
    // Additional blend modes can be added here
};

enum class LS_TRANSITION_TYPES {
    None            = 0,
    FadeIn          = 1,
    FadeOut         = 2,
    WipeLeft        = 3,
    WipeRight       = 4,
    SlideLeft       = 5,
    SlideRight      = 6,
    IrisIn          = 7, 
    IrisInSolid     = 8,
    IrisOut         = 9,
    IrisOutSolid    = 10,
    DissolveIn      = 11,
    Ciak            = 12,
    WhiteDissolve   = 13,
    ColorDissolve   = 14,
    BlackDissolve   = 15,
    CrossDissolve   = 16,
    SweepLeft       = 17,
    SweepRight      = 18,
    BlinkIn         = 19,
    BlinkOut        = 20,
    DecreasingBlink = 21,
    IncreasingBlink = 22,
    Atomic          = 23,
    LightsOff       = 24,
    DissolveInto    = 25,

    // ... Add more as needed
};

#define TRANSITION_COUNT (sizeof(_transitionNames)/sizeof(_transitionNames[0]))
#define TRANSITION_NAME(x) _transitionNames[x]

const char transitionName_0[] PROGMEM = "None";
const char transitionName_1[] PROGMEM = "Fade In";
const char transitionName_2[] PROGMEM = "Fade Out";
const char transitionName_3[] PROGMEM = "Wipe Left";
const char transitionName_4[] PROGMEM = "Wipe Right";
const char transitionName_5[] PROGMEM = "Slide Left";
const char transitionName_6[] PROGMEM = "Slide Right";
const char transitionName_7[] PROGMEM = "Iris In";
const char transitionName_8[] PROGMEM = "Iris In Solid";
const char transitionName_9[] PROGMEM = "Iris Out";
const char transitionName_10[] PROGMEM = "Iris Out Solid";
const char transitionName_11[] PROGMEM = "DissolveIn";
const char transitionName_12[] PROGMEM = "Ciak";
const char transitionName_13[] PROGMEM = "White Dissolve";
const char transitionName_14[] PROGMEM = "Color Dissolve";
const char transitionName_15[] PROGMEM = "Black Dissolve";
const char transitionName_16[] PROGMEM = "Cross Dissolve";
const char transitionName_17[] PROGMEM = "Sweep Left";
const char transitionName_18[] PROGMEM = "Sweep Right";
const char transitionName_19[] PROGMEM = "Blink In";
const char transitionName_20[] PROGMEM = "Blink Out";
const char transitionName_21[] PROGMEM = "Decreasing Blink";
const char transitionName_22[] PROGMEM = "Increasing Blink";
const char transitionName_23[] PROGMEM = "Atomic";
const char transitionName_24[] PROGMEM = "Lights Off";
const char transitionName_25[] PROGMEM = "Dissolve Into";

static const __FlashStringHelper* _transitionNames[] = {
  FSH(transitionName_0),
  FSH(transitionName_1),
  FSH(transitionName_2),
  FSH(transitionName_3),
  FSH(transitionName_4),
  FSH(transitionName_5),
  FSH(transitionName_6),
  FSH(transitionName_7),
  FSH(transitionName_8),
  FSH(transitionName_9),
  FSH(transitionName_10),
  FSH(transitionName_11),
  FSH(transitionName_12),
  FSH(transitionName_13),
  FSH(transitionName_14),
  FSH(transitionName_15),
  FSH(transitionName_16),
  FSH(transitionName_17),
  FSH(transitionName_18),
  FSH(transitionName_19),
  FSH(transitionName_20),
  FSH(transitionName_21),
  FSH(transitionName_22),
  FSH(transitionName_23),
  FSH(transitionName_24),
  FSH(transitionName_25),
};

enum class LS_SEQUENCES_TYPES {
    lsSequenceFill              = 0,
    lsSequenceScan              = 1,
    lsSequenceConfetti          = 2,
    lsSequenceLightning         = 3,
    lsSequenceGlitter           = 4,
    lsSequenceSparkle           = 5,
    lsSequenceBPM               = 6,
    lsSequenceSinelon           = 7,
    lsSequenceStrobe            = 8,
    lsSequenceColorBars         = 9,
    lsSequenceBeat8Tail         = 10,
    lsSequenceCellularNoise     = 11,
    lsSequenceTargetA           = 12,
    lsSequenceTargetB           = 13,
    lSSequencePopupDroid        = 14,
    lsSequenceBouncingBars      = 15,
    lsSequenceBouncingBar       = 16,
    lsSequenceComet             = 17,
    lsSequenceElectricity       = 18,
    lsSequenceJuggle            = 19,
    lsSequencePaletteBreathe    = 20,
    lsSequencePaletteDissolve   = 21,
    lsSequencePaletteGradient   = 22,
    lsSequencePaletteWave       = 23,
    lsSequenceSparkles          = 24,
    lsSequenceTeatherChase      = 25,
    lsSequenceWanderingLine     = 26,
    lsSequenceBlink             = 27,
    lsSequenceWipe              = 28,
    lsSequenceSingleDynamic     = 29,
    lsSequenceSweep             = 30,
    lsSequenceFillUp            = 31,
    lsSequenceTetris            = 32,
    lsSequenceSandWatch         = 33,
    lsSequenceAndroid           = 34,
    lsSequenceAurora            = 35,
    lsSequenceGroup             = 36,
    lsSequenceDigitalRain       = 37,
};

#define SEQUENCE_COUNT (sizeof(_sequenceNames)/sizeof(_sequenceNames[0]))
#define SEQUENCE_NAME(x) _sequenceNames[x]

const char sequenceName_0[] PROGMEM = "Fill";
const char sequenceName_1[] PROGMEM = "Scan";
const char sequenceName_2[] PROGMEM = "Confetti";
const char sequenceName_3[] PROGMEM = "Lightning";
const char sequenceName_4[] PROGMEM = "Glitter";
const char sequenceName_5[] PROGMEM = "Sparkle";
const char sequenceName_6[] PROGMEM = "BPM";
const char sequenceName_7[] PROGMEM = "Sinelon";
const char sequenceName_8[] PROGMEM = "Strobe";
const char sequenceName_9[] PROGMEM = "ColorBars";
const char sequenceName_10[] PROGMEM = "Beat8Tail";
const char sequenceName_11[] PROGMEM = "Cellular Noise";
const char sequenceName_12[] PROGMEM = "TargetA";
const char sequenceName_13[] PROGMEM = "TargetB";
const char sequenceName_14[] PROGMEM = "PopupDroid";
const char sequenceName_15[] PROGMEM = "Bouncing Bars";
const char sequenceName_16[] PROGMEM = "Bouncing Bar";
const char sequenceName_17[] PROGMEM = "Comet";
const char sequenceName_18[] PROGMEM = "Electricity";
const char sequenceName_19[] PROGMEM = "Juggle";
const char sequenceName_20[] PROGMEM = "Palette Breathe";
const char sequenceName_21[] PROGMEM = "Palette Dissolve";
const char sequenceName_22[] PROGMEM = "Palette Gradient";
const char sequenceName_23[] PROGMEM = "Palette Wave";
const char sequenceName_24[] PROGMEM = "Sparkles";
const char sequenceName_25[] PROGMEM = "Teather Chase";
const char sequenceName_26[] PROGMEM = "Wandering Line";
const char sequenceName_27[] PROGMEM = "Blink";
const char sequenceName_28[] PROGMEM = "Wipe";
const char sequenceName_29[] PROGMEM = "Single Dynamic";
const char sequenceName_30[] PROGMEM = "Sweep";
const char sequenceName_31[] PROGMEM = "FillUp";
const char sequenceName_32[] PROGMEM = "Tetris";
const char sequenceName_33[] PROGMEM = "SandWatch";
const char sequenceName_34[] PROGMEM = "Android";
const char sequenceName_35[] PROGMEM = "Aurora";
const char sequenceName_36[] PROGMEM = "Group";
const char sequenceName_37[] PROGMEM = "Digital Rain";

static const __FlashStringHelper* _sequenceNames[] = {
  FSH(sequenceName_0),
  FSH(sequenceName_1),
  FSH(sequenceName_2),
  FSH(sequenceName_3),
  FSH(sequenceName_4),
  FSH(sequenceName_5),
  FSH(sequenceName_6),
  FSH(sequenceName_7),
  FSH(sequenceName_8),
  FSH(sequenceName_9),
  FSH(sequenceName_10),
  FSH(sequenceName_11),
  FSH(sequenceName_12),
  FSH(sequenceName_13),
  FSH(sequenceName_14),
  FSH(sequenceName_15),
  FSH(sequenceName_16),
  FSH(sequenceName_17),
  FSH(sequenceName_18),
  FSH(sequenceName_19),
  FSH(sequenceName_20),
  FSH(sequenceName_21),
  FSH(sequenceName_22),
  FSH(sequenceName_23),
  FSH(sequenceName_24),
  FSH(sequenceName_25),
  FSH(sequenceName_26),
  FSH(sequenceName_27),
  FSH(sequenceName_28),
  FSH(sequenceName_29),
  FSH(sequenceName_30),
  FSH(sequenceName_31),
  FSH(sequenceName_32),
  FSH(sequenceName_33),
  FSH(sequenceName_34),
  FSH(sequenceName_35),
  FSH(sequenceName_36),
  FSH(sequenceName_37),
};

enum class LS_PALETTES {
    CloudColors_p               = 0,
    LavaColors_p                = 1,
    OceanColors_p               = 2,
    ForestColors_p              = 3,
    RainbowColors_p             = 4,
    RainbowStripeColors_p       = 5,
    PartyColors_p               = 6,
    HeatColors_p                = 7,
    Rainbow_gp                  = 8,
    //Palettes from WLED
    Sunset_Real_gp              = 9,               
    es_rivendell_15_gp          = 10,           
    es_ocean_breeze_036_gp      = 11,       
    rgi_15_gp                   = 12,                    
    retro2_16_gp                = 13,                 
    Analogous_1_gp              = 14,
    es_pinksplash_08_gp         = 15,          
    Sunset_Yellow_gp            = 16,             
    Another_Sunset_gp           = 17,            
    Beech_gp                    = 18,                     
    es_vintage_01_gp            = 19,             
    departure_gp                = 20,                 
    es_landscape_64_gp          = 21,           
    es_landscape_33_gp          = 22,           
    rainbowsherbet_gp           = 23,            
    gr65_hult_gp                = 24,                 
    gr64_hult_gp                = 25,                 
    GMT_drywet_gp               = 26,                
    ib_jul01_gp                 = 27,                  
    es_vintage_57_gp            = 28,             
    ib15_gp                     = 29,                      
    Tertiary_01_gp              = 30,               
    lava_gp                     = 31,                      
    fierce_ice_gp               = 32,                
    Colorfull_gp                = 33,                 
    Pink_Purple_gp              = 34,               
    es_autumn_19_gp             = 35,              
    BlacK_Blue_Magenta_White_gp = 36,  
    BlacK_Magenta_Red_gp        = 37,         
    BlacK_Red_Magenta_Yellow_gp = 38,  
    Blue_Cyan_Yellow_gp         = 39,          
    Orange_Teal_gp              = 40,               
    Tiamat_gp                   = 41,                    
    April_Night_gp              = 42,               
    Orangery_gp                 = 43,                  
    C9_gp                       = 44,                        
    Sakura_gp                   = 45,                    
    Aurora_gp                   = 46,                    
    Atlantica_gp                = 47,                 
    C9_2_gp                     = 48,                      
    C9_new_gp                   = 49,                    
    temperature_gp              = 50,               
    Aurora2_gp                  = 51,                   
    retro_clown_gp              = 52,               
    candy_gp                    = 53,                     
    toxy_reaf_gp                = 54,                 
    fairy_reaf_gp               = 55,                
    semi_blue_gp                = 56,                 
    pink_candy_gp               = 57,                
    red_reaf_gp                 = 58,                  
    aqua_flash_gp               = 59,                
    yelblu_hot_gp               = 60,                
    lite_light_gp               = 61,                
    red_flash_gp                = 62,                 
    blink_red_gp                = 63,                 
    red_shift_gp                = 64,                 
    red_tide_gp                 = 65,                  
    candy2_gp                   = 66,                    
};

#define PALETTE_COUNT (sizeof(_paletteNames)/sizeof(_paletteNames[0]))
#define PALETTE_NAME(x) _paletteNames[x]

const char paletteName_0[] PROGMEM = "Cloud Colors";
const char paletteName_1[] PROGMEM = "Lava Colors";
const char paletteName_2[] PROGMEM = "Ocean Colors";
const char paletteName_3[] PROGMEM = "Forest Colors";
const char paletteName_4[] PROGMEM = "Rainbow Colors";
const char paletteName_5[] PROGMEM = "Rainbow Stripe Colors";
const char paletteName_6[] PROGMEM = "Party Colors";
const char paletteName_7[] PROGMEM = "Heat Colors";
const char paletteName_8[] PROGMEM = "Rainbow";
const char paletteName_9[] PROGMEM = "Sunset Real";   
const char paletteName_10[] PROGMEM = "Rivendell 15";
const char paletteName_11[] PROGMEM = "Ocean breeze";
const char paletteName_12[] PROGMEM = "Rgi 15";  
const char paletteName_13[] PROGMEM = "Retro2 16";
const char paletteName_14[] PROGMEM = "Analogous 1";
const char paletteName_15[] PROGMEM = "Es pinksplash 08";
const char paletteName_16[] PROGMEM = "Sunset Yellow";
const char paletteName_17[] PROGMEM = "Another Sunset";
const char paletteName_18[] PROGMEM = "Beech";
const char paletteName_19[] PROGMEM = "Vintage 01";
const char paletteName_20[] PROGMEM = "Departure";  
const char paletteName_21[] PROGMEM = "Landscape 64";
const char paletteName_22[] PROGMEM = "Landscape 33";
const char paletteName_23[] PROGMEM = "Rainbow Sherbet";     
const char paletteName_24[] PROGMEM = "Gr65 hult";    
const char paletteName_25[] PROGMEM = "Gr64 hult";        
const char paletteName_26[] PROGMEM = "GMT drywet";      
const char paletteName_27[] PROGMEM = "Ib jul01";   
const char paletteName_28[] PROGMEM = "Vintage 57";
const char paletteName_29[] PROGMEM = "Ib15"; 
const char paletteName_30[] PROGMEM = "Tertiary 01";
const char paletteName_31[] PROGMEM = "Lava"; 
const char paletteName_32[] PROGMEM = "Fierce ice";
const char paletteName_33[] PROGMEM = "Colorfull";       
const char paletteName_34[] PROGMEM = "Pink Purple";  
const char paletteName_35[] PROGMEM = "Autumn 19";
const char paletteName_36[] PROGMEM = "BlacK Blue Magenta White";
const char paletteName_37[] PROGMEM = "BlacK Magenta Red";   
const char paletteName_38[] PROGMEM = "Black Red Magenta Yellow";
const char paletteName_39[] PROGMEM = "Blue Cyan Yellow";          
const char paletteName_40[] PROGMEM = "Orange Teal";               
const char paletteName_41[] PROGMEM = "Tiamat";                    
const char paletteName_42[] PROGMEM = "April Night";               
const char paletteName_43[] PROGMEM = "Orangery";                  
const char paletteName_44[] PROGMEM = "C9";                        
const char paletteName_45[] PROGMEM = "Sakura";                    
const char paletteName_46[] PROGMEM = "Aurora";                    
const char paletteName_47[] PROGMEM = "Atlantica";                 
const char paletteName_48[] PROGMEM = "C9 2";                      
const char paletteName_49[] PROGMEM = "C9 new";                    
const char paletteName_50[] PROGMEM = "Temperature";               
const char paletteName_51[] PROGMEM = "Aurora 2";                   
const char paletteName_52[] PROGMEM = "Retro clown";               
const char paletteName_53[] PROGMEM = "Candy";                     
const char paletteName_54[] PROGMEM = "Toxy reaf";                 
const char paletteName_55[] PROGMEM = "Fairy reaf";                
const char paletteName_56[] PROGMEM = "Semi blue";                 
const char paletteName_57[] PROGMEM = "Pinky Candy";                
const char paletteName_58[] PROGMEM = "Red Reaf";                  
const char paletteName_59[] PROGMEM = "Aqua Flash";                
const char paletteName_60[] PROGMEM = "Yelblu Hot";                
const char paletteName_61[] PROGMEM = "Lite Light";     
const char paletteName_62[] PROGMEM = "Red Flash";
const char paletteName_63[] PROGMEM = "Blink Red";    
const char paletteName_64[] PROGMEM = "Red Shift";  
const char paletteName_65[] PROGMEM = "Red Tide";           
const char paletteName_66[] PROGMEM = "Candy 2";

static const __FlashStringHelper* _paletteNames[] = {
   FSH(paletteName_0),
   FSH(paletteName_1),
   FSH(paletteName_2),
   FSH(paletteName_3),
   FSH(paletteName_4),
   FSH(paletteName_5),
   FSH(paletteName_6),
   FSH(paletteName_7),
   FSH(paletteName_8),
   FSH(paletteName_9),
   FSH(paletteName_10),
   FSH(paletteName_11),
   FSH(paletteName_12),
   FSH(paletteName_13),
   FSH(paletteName_14),
   FSH(paletteName_15),
   FSH(paletteName_16),
   FSH(paletteName_17),
   FSH(paletteName_18),
   FSH(paletteName_19),
   FSH(paletteName_20),
   FSH(paletteName_21),
   FSH(paletteName_22),
   FSH(paletteName_23),
   FSH(paletteName_24),
   FSH(paletteName_25),
   FSH(paletteName_26),
   FSH(paletteName_27),
   FSH(paletteName_28),
   FSH(paletteName_29),
   FSH(paletteName_30),
   FSH(paletteName_31),
   FSH(paletteName_32),
   FSH(paletteName_33),
   FSH(paletteName_34),
   FSH(paletteName_35),
   FSH(paletteName_36),
   FSH(paletteName_37),
   FSH(paletteName_38),
   FSH(paletteName_39),
   FSH(paletteName_40),
   FSH(paletteName_41),
   FSH(paletteName_42),
   FSH(paletteName_43),
   FSH(paletteName_44),
   FSH(paletteName_45),
   FSH(paletteName_46),
   FSH(paletteName_47),
   FSH(paletteName_48),
   FSH(paletteName_49),
   FSH(paletteName_50),
   FSH(paletteName_51),
   FSH(paletteName_52),
   FSH(paletteName_53),
   FSH(paletteName_54),
   FSH(paletteName_55),
   FSH(paletteName_56),
   FSH(paletteName_57),
   FSH(paletteName_58),
   FSH(paletteName_59),
   FSH(paletteName_60),
   FSH(paletteName_61),
   FSH(paletteName_62),
   FSH(paletteName_63),
   FSH(paletteName_64),
   FSH(paletteName_65),
   FSH(paletteName_66)      
};

#endif
