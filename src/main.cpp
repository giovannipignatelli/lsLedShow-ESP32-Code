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
 * - Add more transitions between effects
 * - Implement additional effects
 * - Refactor code for better organization
 * 
 * Description: [Description of what the file does]
 */

#include <Arduino.h>
#include <ESPmDNS.h>
#include <FastLED.h>
#include "lsDefinitions.h"
#include "lsStrip.h"
#include "lsSequence.h"
#include "lsLevel.h"  
#include "lsStage.h"
#include "lsShow.h"
#include "lsStruct_Enum.h"
#include "lsSequences/lsSequences.h"




// Uncomment the following line to enable WiFi Manager support
#define USE_WIFIMGR
#ifdef USE_WIFIMGR
#include <WiFiManager.h>        
  WiFiManager wm; 
#endif

int delayTime = 1000;
int fps = 120;

//CRGB leds[NUM_LEDS];

lsLedShow myShow;

#define USE_ESPUI
#ifdef USE_ESPUI
//    #include "lsRemoteControl.h"
    #include "ESPAsyncWebServer.h"
    #include "AsyncJson.h"
    const char* MyHostName = "ESP32-LedShow";

    void notFound(AsyncWebServerRequest *request) {
        request->send(404, "text/plain", "Not found");
    }

#endif

// Uncomment the following line to enable LCD support
//#define USE_LCD
#ifdef USE_LCD
#include "LCDOutput.h"        // LCDOutput.h is LCD handling class
LCDOutput lcd(0x27, 16, 2);   // Example initialization with I2C address 0x27 and size 16x2
#endif

LS_MASK evenMask_m[] = {{1,1},{0,1}};
LS_MASK oddMask_m[] =  {{0,1},{1,1}};
LS_MASK oddityMask_m[] = {{0,2},{1,2}};
LS_PATTERN_STRIP pattern_p[] = { {CRGB::White , 5},{CRGB::Yellow , 5},{CRGB::Blue, 4},{CRGB::Green, 2},  {CRGB::Red, 2}};

void setup() {
  #ifdef USE_LCD
    lcd.begin(); // Initialize the LCD if enabled
  #endif

  #ifdef USE_WIFIMGR
    WiFiManager wm;
    // reset settings - wipe stored credentials for testing
    // these are stored by the esp library
    // wm.resetSettings();
    // Automatically connect using saved credentials,
    // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
    // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
    // then goes into a blocking loop awaiting configuration and will return success result

    bool res;
    res = wm.setHostname(MyHostName);
    res = wm.autoConnect(); // auto generated AP name from chipid
    // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
    //res = wm.autoConnect("AutoConnectAP","password"); // password protected ap

    if(!res) {
        Serial.println("Failed to connect");
        ESP.restart();
    } 
    else {
        Serial.println("connected...yeey :)");
        wm.setHostname(MyHostName);
    }
  #endif

  #ifdef USE_ESPUI

      AsyncWebServer* server = new AsyncWebServer(80);
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
      //AsyncWebServer * ws = ESPUI.server;
      /*ws.on("/get-show", HTTP_GET, [](AsyncWebServerRequest *request) {
        String response;
        serializeJson(myShow.serialize(), response);
        request->send(200, "application/json", response);
      });

      ws.on("/get-stages", HTTP_GET, [](AsyncWebServerRequest *request) {
        String response;
        serializeJson(myShow.serializeStages(), response);
        request->send(200, "application/json", response);
      });
      */
      server->on("/start", HTTP_GET, [](AsyncWebServerRequest *request) {
        String response;
        myShow.start();
        request->send(200, "application/json", response);
      });

      server->on("/stop", HTTP_GET, [](AsyncWebServerRequest *request) {
        String response;
        myShow.stop();
        request->send(200, "application/json", response);
      });

      server->on("/shutdown", HTTP_GET, [](AsyncWebServerRequest *request) {
        String response;
        myShow.shutdown();
        request->send(200, "application/json", response);
      });

      AsyncCallbackJsonWebHandler *handler = new AsyncCallbackJsonWebHandler("/post-show", [](AsyncWebServerRequest *request, JsonVariant &json) {
        JsonDocument data;
        if (json.is<JsonArray>()) {
          data = json.as<JsonArray>();
        }
        else if (json.is<JsonObject>()) {
          data = json.as<JsonObject>();
        }
        String response;
        myShow.flush();
        if (myShow.update(data)) myShow.start();
        request->send(200, "application/json", response);
        Serial.println(response);
      });
      server->addHandler(handler);

      server->onNotFound(notFound);

      server->begin();

  #endif

  delay(3000); // 3 second delay for recovery
  Serial.begin(115200);
  myShow.addStrip(NUM_LEDS,27);
  myShow.addStrip(NUM_LEDS,26);
  myShow.addStrip(NUM_LEDS,25);
  myShow.addStrip(NUM_LEDS,33);
  //FastLED.addLeds<STRIP_TYPE, PIN , COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip ).setDither(BRIGHTNESS < 255);
  FastLED.setBrightness(BRIGHTNESS);
  randomSeed(analogRead(A0));
  //show.addStage("Primo").addLevel().addSequence(new lsSequenceConfetti()).setColors(CRGB::Red).setRenderEveryNFrames(2).setDuration(10*FRAMES_PER_SECOND);
  myShow.addStage("Primo").addLevel().addSequence(new lsSequenceFill()).setColoring(LS_FILL_TYPES::SOLID).setColors(CRGB::Green,CRGB::Green,CRGB::Green).setDuration(20*ONESECOND);
  //show.lastStage().lastLevel().lastSequence().setTransitionOut(new lsTransition(LS_TRANSITION_TYPES::DissolveInto,5*ONESECOND,CRGB::Blue));
  //show.lastStage().lastLevel().addSequence(new lsSequenceFill()).setColoring(LS_FILL_TYPES::PATTERN).setPatternStrip(pattern_p,5).setDuration(ONESECOND*2);
  myShow.lastStage().lastLevel().lastSequence().setTransitionIn(new lsTransition(LS_TRANSITION_TYPES::IncreasingBlink,10*ONESECOND,CRGB::Yellow));
  //show.lastStage().lastLevel().lastSequence().setTransitionOut(new lsTransition(LS_TRANSITION_TYPES::FadeOut,5*ONESECOND,CRGB::Blue));
  myShow.lastStage().lastLevel().addSequence(new lsSequenceFill()).setColoring(LS_FILL_TYPES::RANDOMSINGLE).setRenderEveryNFrames(120).setDuration(10*FRAMES_PER_SECOND);
  //show.lastStage().lastLevel().addSequence(new lsSequenceFill()).setFill(LS_FILL_TYPES::SOLID).setDuration(10*FRAMES_PER_SECOND);
  //show.lastStage().addLevel().setBlendMode(LS_BLENDMODE::N_BLEND).addSequence(new lsSequenceWanderingLine(8)).setColors(CRGB::Blue).setRenderEveryNFrames(5).setDuration(20*FRAMES_PER_SECOND);
  myShow.lastStage().lastLevel().addSequence(new lsSequenceLightning(10)).setColors(CRGB::Green).setDuration(2*FRAMES_PER_SECOND);
  myShow.lastStage().lastLevel().addSequence(new lsSequenceBPM()).setPalette(LS_PALETTES::LavaColors_p,LINEARBLEND).setDuration(4*ONESECOND);
  //show.lastStage().lastLevel().addSequence(new lsFillSequence()).setFill(GRADIENT).setGradient(CRGB::Red,CRGB::Purple).setDuration(2*FRAMES_PER_SECOND);
  //show.lastStage().lastLevel().addSequence(new lsFillSequence()).setFill(PALETTE).setPalette(LavaColors_p,LINEARBLEND).setDuration(4*FRAMES_PER_SECOND);
  //show.lastStage().lastLevel().addSequence(new lsFillSequence()).setFill(RAINBOWCIRCULAR).setRainbowCHues(10).setDuration(2*FRAMES_PER_SECOND);
  //show.lastStage().lastLevel().addSequence(new lsFillSequence()).setFill(RAINBOW).setRainbowHues(10,5).setDuration(4*FRAMES_PER_SECOND);
  //show.lastStage().lastLevel().addSequence(new lsFillSequence()).setFill(PALETTECIRCULAR).setPaletteC(	OceanColors_p,LINEARBLEND).setDuration(2*FRAMES_PER_SECOND);
  //show.lastStage().addLevel();
  //show.addStage("Secondo").addLevel().addSequence(new lsSequenceFill()).setColoring(LS_FILL_TYPES::SOLID).setColors(CRGB::Red).setDuration(ONESECOND).setMask(evenMask_m,2,5);
  //show.addStage("Terzo").addLevel().addSequence(new lsSequenceFill()).setColoring(LS_FILL_TYPES::SOLID).setColors(CRGB::Green).setDuration(ONESECOND);
  myShow.setFPS(FRAMES_PER_SECOND);

}

void loop() {
  // put your main code here, to run repeatedly:
  myShow.render();
  static long unsigned lastTime = 0;


  #ifdef USE_LCD
    // Example: Update the LCD with some information
    lcd.print("FPS: XX.X", "Other info");
  #endif
}
