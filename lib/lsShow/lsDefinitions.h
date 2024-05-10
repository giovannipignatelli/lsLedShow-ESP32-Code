#define SLOW_BOOT 0
#define HOSTNAME "Led Show Remote Control"
#define FORCE_USE_HOTSPOT 0
#define LS_GLOBAL extern
#define NUM_LEDS 30
#define NUM_STRIPS 1
#define NUM_SCENES 5 
#define STRIP_TYPE WS2812
#define COLOR_ORDER GRB
#define PIN 27
#define BUTTON 2
#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  fps
#define ONESECOND FRAMES_PER_SECOND
#define FIVESECONDS 5*FRAMES_PER_SECOND
#define TENSECONDS  10*FRAMES_PER_SECOND
#define TIME_ON_STAGE      40
#define FRAMES_PER_SECOND_FIRE 60

#define SPRINT(x)      Serial.print(x);
#define SPRINTLN(x)    Serial.println(x);
#define SPRINTLN       Serial.println("");
#define SPRINTCOUPLE(x,y)    Serial.print(x);Serial.print(y);