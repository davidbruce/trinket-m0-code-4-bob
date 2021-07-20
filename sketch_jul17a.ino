#include <Adafruit_DotStar.h>
#include <Adafruit_NeoPixel.h>

Adafruit_DotStar internalLED(1, INTERNAL_DS_DATA, INTERNAL_DS_CLK, DOTSTAR_BGR);

#define NUMPIXELS                 4
#define DELAYVAL                 64
#define BRIGHTNESS_DELAYVAL       8

Adafruit_NeoPixel section1(NUMPIXELS, 1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel section2(NUMPIXELS, 2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel section3(NUMPIXELS, 3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel section4(NUMPIXELS, 4, NEO_GRB + NEO_KHZ800); //CHANGE NUMPIXELS to the number of pixels you would like

struct Section {
  Adafruit_NeoPixel pixels;
  int brightness;
  boolean increase; 
};

//int brightnessSteps[4] = {4, 8, 12, 16}; //use for random brightness 
int brightnessSteps[4] = {4, 8, 12, 16}; //use for random brightness 


#define SECTIONS_SIZE    4
Section sections[SECTIONS_SIZE] = {
  { section1, 64, false },
  { section2, 64, false },
  { section3, 64, false },
  { section4, 64, false }
};
          
void initSectionPins(Adafruit_NeoPixel *section, int PIN) {
  section->begin();
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN, HIGH);
}

void colorSection(Adafruit_NeoPixel *pixels, uint32_t color) {
  pixels->clear();
  pixels->setPixelColor(0, pixels->Color(0, 0, 255));
  pixels->setPixelColor(1, color);
  pixels->setPixelColor(2, color);
  pixels->setPixelColor(3, pixels->Color(64, 128, 255));
  pixels->show();
}

void changeBrightness(Section *section, int iterations) {
    while (iterations != 0) {
      section->pixels.setBrightness(section->brightness);
      if (section->increase) {
        section->brightness = section->brightness + 1;
      }
      else {
          section->brightness = section->brightness - 1;
      }
    
      if (section->brightness <= 10) {
        section->increase = true;
      }
      if (section->brightness >= 99) {
        section->increase = false;
      }
      iterations--;
   }
}

void setup() {
  //set internal DotStar LED to dim and blue
  internalLED.begin();
  internalLED.setBrightness(30); //dim because it's brighter than the sun
  internalLED.setPixelColor(0, 128, 0, 128); 
  internalLED.show();

  randomSeed(analogRead(0));


  for (int i = 0; i < SECTIONS_SIZE; i++) {
     initSectionPins(&sections[i].pixels, i + 1);
  }
}

void loop() {
  for (int i = 0; i < SECTIONS_SIZE; i++) {
    changeBrightness(&sections[i], 4);
    colorSection(&sections[i].pixels, sections[i].pixels.Color(0, 128, 128));
    delay(BRIGHTNESS_DELAYVAL); //ignore unless you wanna add some delays between iterations might make things choppy
  }

//  GET RANDOM SECTION EXAMPLE:
//  int section = random(0,4);
//  changeBrightness(&sections[section], brightnessSteps[random(0,4)]);
//  colorSection(&sections[section].pixels, sections[section].pixels.Color(0, 128, 128));

//  YOU CAN PROBABLY IGNORE BELOW
//  SECTION 1
//  changeBrightness(&sections[0], brightnessSteps[random(0,4)]);
//  colorSection(&sections[0].pixels, sections[0].pixels.Color(0, 128, 128));

//  SECTION 2
//  changeBrightness(&sections[1], brightnessSteps[random(0,4)]);
//  colorSection(&sections[1].pixels, sections[1].pixels.Color(0, 128, 128));

//  SECTION 3
//  changeBrightness(&sections[2], brightnessSteps[random(0,4)]);
//  colorSection(&sections[2].pixels, sections[2].pixels.Color(0, 128, 128));

//  SECTION 4
//  changeBrightness(&sections[3], brightnessSteps[random(0,4)]);
//  colorSection(&sections[3].pixels, sections[3].pixels.Color(0, 128, 128));

  
  delay(DELAYVAL);
}

//void blinkBackAndForth(Adafruit_NeoPixel *section, uint32_t color, int delayDuration) {
//  for(int i=0; i<NUMPIXELS; i++) {
//    section->setPixelColor(i, color);
//    section->show();
//    delay(delayDuration);
//  }
//  for(int i=0; i<NUMPIXELS; i++) {
//    section->setPixelColor(i, section->Color(0, 0, 0));
//    section->show();
//    delay(delayDuration);
//  }
//  for (int i= (NUMPIXELS - 1); i != -1; i--) {
//    section->setPixelColor(i, color);
//    section->show();
//    delay(delayDuration);
//  }
//  for (int i= (NUMPIXELS - 1); i != -1; i--) {
//    section->setPixelColor(i, section->Color(0, 0, 0));
//    section->show();
////    delay(delayDuration);
//  }
//}
