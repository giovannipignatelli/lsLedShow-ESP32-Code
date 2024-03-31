#include "lsColorUtils.h"
#include "lsPalettes.h"



    JsonDocument lsColorutils::serialize(CRGB Color){
      JsonDocument doc;
      doc["Red"] = Color.r;
      doc["Green"] = Color.g;
      doc["Blue"] = Color.b;
      return doc;
    }


    CRGB lsColorutils::getColorWheel(byte WheelPos){
      CRGB Color;
      byte *c; 
      c=Wheel(WheelPos);
      Color.r = *c;
      Color.g = *(c+1);
      Color.b = *(c+2);
      return Color;
    }

    byte * lsColorutils::Wheel(byte WheelPos) {
      static byte c[3];
      
      if(WheelPos < 85) {
        c[0]=WheelPos * 3;
        c[1]=255 - WheelPos * 3;
        c[2]=0;
      } else if(WheelPos < 170) {
        WheelPos -= 85;
        c[0]=255 - WheelPos * 3;
        c[1]=0;
        c[2]=WheelPos * 3;
      } else {
        WheelPos -= 170;
        c[0]=0;
        c[1]=WheelPos * 3;
        c[2]=255 - WheelPos * 3;
      }
      return c;
    }

    CRGB lsColorutils::getRandomColor(){
      return ColorFromPalette(RainbowColors_p, random16(255), 180, LINEARBLEND);
    }

    CRGB lsColorutils::getColorFromPalette(CRGBPalette16 palette, TBlendType blendType, int step){
      return ColorFromPalette(palette, step, 180, blendType);
    }

    void lsColorutils::fillSolid(CRGB Color, CRGB * displayLeds, int numLeds){ 
      fill_solid(displayLeds, numLeds, Color);
    }

    void lsColorutils::fillRandom(CRGB * displayLeds, int numLeds){ 
      fill_solid(displayLeds, numLeds, getRandomColor());
    }
        
    void lsColorutils::fillRandomSingle(CRGB * displayLeds, int numLeds) { 
      for (int i = 0; i<numLeds; i++ ) displayLeds[i] = getRandomColor(); 
    }

    void lsColorutils::fillPalette(CRGB * displayLeds, int numLeds,CRGBPalette16 palette, TBlendType blendType){
       fill_palette(displayLeds, numLeds, 0, 255/numLeds ,palette, 255, blendType);
    }
    
    void lsColorutils::fillPaletteC(CRGB * displayLeds, int numLeds, CRGBPalette16 palette, TBlendType blendType, bool reversed){ 
      fill_palette_circular(displayLeds, numLeds, 0, palette, 255, blendType, reversed);
    }
    
    void lsColorutils::fillPattern(CRGB * displayLeds, int numLeds,LS_PATTERN_STRIP *pattern, int positions){ 
      int pixel = 0;
      while (pixel < numLeds) {
        for(int j = 0; j < positions; j++ ) {
          for(int i = 0; i < pattern[j].stripSize; i++ ) {
            displayLeds[pixel] = pattern[j].stripColor;
            pixel++;
          }
        }
      }
    }
    
    void lsColorutils::fillRainbow(CRGB * displayLeds, int numLeds,uint8_t initialhue, uint8_t deltahue){ 
      fill_rainbow(displayLeds, numLeds,  initialhue,  deltahue); 
    }
    
    void lsColorutils::fillRainbowC(CRGB * displayLeds, int numLeds,uint8_t initialhue, bool reversed){ 
      fill_rainbow(displayLeds, numLeds,  initialhue,  reversed);
    }
    
    void lsColorutils::fillGradient(CRGB * displayLeds, int numLeds,CRGB c1, CRGB c2){ 
      fill_gradient_RGB (displayLeds, numLeds, c1, c2);
    }

    CRGBPalette16 lsColorutils::getPalette(LS_PALETTES palette){
      CRGBPalette16 myPalette;
      switch (palette)
      {
        case (LS_PALETTES::CloudColors_p):
        {
          myPalette = CloudColors_p;
          break;
        }
        case (LS_PALETTES::LavaColors_p):
        {
          myPalette = LavaColors_p;
          break;
        }
        case (LS_PALETTES::OceanColors_p):
        {
          myPalette = OceanColors_p;
          break;
        }
        case (LS_PALETTES::ForestColors_p):
        {
          myPalette = ForestColors_p;
          break;
        }
          case (LS_PALETTES::RainbowColors_p):
        {
          myPalette = RainbowColors_p;
          break;
        }
        case (LS_PALETTES::RainbowStripeColors_p):
        {
          myPalette = RainbowStripeColors_p;
          break;
        }
        case (LS_PALETTES::PartyColors_p):
        {
          myPalette = PartyColors_p;
          break;
        }
        case (LS_PALETTES::HeatColors_p):
        {
          myPalette = HeatColors_p;
          break;
        }
        case (LS_PALETTES::Rainbow_gp):
        {
          myPalette = Rainbow_gp;
          break;
        }
        case (LS_PALETTES::Sunset_Real_gp):
        {
          myPalette = Sunset_Real_gp;
          break;
        }        
        case (LS_PALETTES::es_rivendell_15_gp):
        {
          myPalette = es_rivendell_15_gp;
          break;
        }    
        case (LS_PALETTES::es_ocean_breeze_036_gp):
        {
          myPalette = es_ocean_breeze_036_gp;
          break;
        }
        case (LS_PALETTES::rgi_15_gp):
        {
          myPalette = rgi_15_gp;
          break;
        }             
        case (LS_PALETTES::retro2_16_gp):
        {
          myPalette = retro2_16_gp;
          break;
        }          
        case (LS_PALETTES::Analogous_1_gp):
        {
          myPalette = Analogous_1_gp;
          break;
        }        
        case (LS_PALETTES::es_pinksplash_08_gp):
        {
          myPalette = es_pinksplash_08_gp;
          break;
        }   
        case (LS_PALETTES::Sunset_Yellow_gp):
        {
          myPalette = es_pinksplash_08_gp;
          break;
        }      
        case (LS_PALETTES::Another_Sunset_gp):
        {
          myPalette = Another_Sunset_gp;
          break;
        }     
        case (LS_PALETTES::Beech_gp):
        {
          myPalette = Beech_gp;
          break;
        }              
        case (LS_PALETTES::es_vintage_01_gp):
        {
          myPalette = es_vintage_01_gp;
          break;
        }      
        case (LS_PALETTES::departure_gp):
        {
          myPalette = departure_gp;
          break;
        }          
        case (LS_PALETTES::es_landscape_64_gp):
        {
          myPalette = es_landscape_64_gp;
          break;
        }    
        case (LS_PALETTES::es_landscape_33_gp):
        {
          myPalette = es_landscape_33_gp;
          break;
        }    
        case (LS_PALETTES::rainbowsherbet_gp):
        {
          myPalette = rainbowsherbet_gp;
          break;
        }     
        case (LS_PALETTES::gr65_hult_gp):
        {
          myPalette = gr65_hult_gp;
          break;
        }          
        case (LS_PALETTES::gr64_hult_gp):
        {
          myPalette = gr64_hult_gp;
          break;
        }          
        case (LS_PALETTES::GMT_drywet_gp):
        {
          myPalette = GMT_drywet_gp;
          break;
        }         
        case (LS_PALETTES::ib_jul01_gp):
        {
          myPalette = ib_jul01_gp;
          break;
        }           
        case (LS_PALETTES::es_vintage_57_gp):
        {
          myPalette = es_vintage_57_gp;
          break;
        }      
        case (LS_PALETTES::ib15_gp):
        {
          myPalette = ib15_gp;
          break;
        }               
        case (LS_PALETTES::Tertiary_01_gp):
        {
          myPalette = Tertiary_01_gp;
          break;
        }        
        case (LS_PALETTES::lava_gp):
        {
          myPalette = lava_gp;
          break;
        }               
        case (LS_PALETTES::fierce_ice_gp):
        {
          myPalette = fierce_ice_gp;
          break;
        }         
        case (LS_PALETTES::Colorfull_gp):
        {
          myPalette = Colorfull_gp;
          break;
        }          
        case (LS_PALETTES::Pink_Purple_gp):
        {
          myPalette = Pink_Purple_gp;
          break;
        }        
        case (LS_PALETTES::es_autumn_19_gp):
        {
          myPalette = es_autumn_19_gp;
          break;
        }       
        case (LS_PALETTES::BlacK_Blue_Magenta_White_gp):
        {
          myPalette = BlacK_Blue_Magenta_White_gp;
          break;
        }         
        case (LS_PALETTES::BlacK_Magenta_Red_gp):
        {
          myPalette = BlacK_Magenta_Red_gp;
          break;
        }  
        case (LS_PALETTES::BlacK_Red_Magenta_Yellow_gp):
        {
          myPalette = BlacK_Red_Magenta_Yellow_gp;
          break;
        }        
        case (LS_PALETTES::Blue_Cyan_Yellow_gp):
        {
          myPalette = Blue_Cyan_Yellow_gp;
          break;
        }   
        case (LS_PALETTES::Orange_Teal_gp):
        {
          myPalette = Orange_Teal_gp;
          break;
        }        
        case (LS_PALETTES::Tiamat_gp):
        {
          myPalette = Tiamat_gp;
          break;
        }             
        case (LS_PALETTES::April_Night_gp):
        {
          myPalette = April_Night_gp;
          break;
        }        
        case (LS_PALETTES::Orangery_gp):
        {
          myPalette = Orangery_gp;
          break;
        }           
        case (LS_PALETTES::C9_gp):
        {
          myPalette = C9_gp;
          break;
        }                  
        case (LS_PALETTES::Aurora_gp):
        {
          myPalette = Aurora_gp;
          break;
        }             
        case (LS_PALETTES::Atlantica_gp):
        {
          myPalette = Atlantica_gp;
          break;
        }          
        case (LS_PALETTES::C9_2_gp):
        {
          myPalette = C9_2_gp;
          break;
        }               
        case (LS_PALETTES::C9_new_gp):
        {
          myPalette = C9_new_gp;
          break;
        }             
        case (LS_PALETTES::temperature_gp):
        {
          myPalette = temperature_gp;
          break;
        }        
        case (LS_PALETTES::Aurora2_gp):
        {
          myPalette = Aurora2_gp;
          break;
        }            
        case (LS_PALETTES::retro_clown_gp):
        {
          myPalette = retro_clown_gp;
          break;
        }        
        case (LS_PALETTES::candy_gp):
        {
          myPalette = candy_gp;
          break;
        }              
        case (LS_PALETTES::toxy_reaf_gp):
        {
          myPalette = toxy_reaf_gp;
          break;
        }          
        case (LS_PALETTES::fairy_reaf_gp):
        {
          myPalette = fairy_reaf_gp;
          break;
        }         
        case (LS_PALETTES::semi_blue_gp):
        {
          myPalette = semi_blue_gp;
          break;
        }          
        case (LS_PALETTES::pink_candy_gp):
        {
          myPalette = pink_candy_gp;
          break;
        }         
        case (LS_PALETTES::red_reaf_gp):
        {
          myPalette = red_reaf_gp;
          break;
        }           
        case (LS_PALETTES::aqua_flash_gp):
        {
          myPalette = aqua_flash_gp;
          break;
        }         
        case (LS_PALETTES::yelblu_hot_gp):
        {
          myPalette = yelblu_hot_gp;
          break;
        }         
        case (LS_PALETTES::lite_light_gp):
        {
          myPalette = lite_light_gp;
          break;
        }         
        case (LS_PALETTES::red_flash_gp):
        {
          myPalette = red_flash_gp;
          break;
        }          
        case (LS_PALETTES::blink_red_gp):
        {
          myPalette = blink_red_gp;
          break;
        }          
        case (LS_PALETTES::red_shift_gp):
        {
          myPalette = red_shift_gp;
          break;
        }          
        case (LS_PALETTES::red_tide_gp):
        {
          myPalette = red_tide_gp;
          break;
        }           
        case (LS_PALETTES::candy2_gp):
        {
          myPalette = candy2_gp;
          break;
        }        
      }

      return myPalette;
    }