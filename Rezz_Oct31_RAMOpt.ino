#include <Adafruit_NeoPixel.h>
#include <elapsedMillis.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PINLEFT 1
#define PINRIGHT 2

#define OUTSIDE_START 0
#define OUTSIDE_END 23
#define MIDDLE_START 24
#define MIDDLE_END 39
#define INNER_START 40
#define INNER_END 43
#define NUM_PIXELS 44

//AFT defines

#define OUTER_DELAY 50
#define MIDDLE_DELAY 100
#define INNER_DELAY 200
#define COLOR_DELAY 100

#define REZZ_ANIMATION_STEPS 23

int animationposoutside = 0;
int animationposinner = 0;
int animationposmiddle = 0;
int animationcolor = 0;

uint16_t q =0;
elapsedMillis timeElapsedout;
elapsedMillis timeElapsedmiddle;
elapsedMillis timeElapsedinner;
elapsedMillis timeElapsedcolor;
               
uint32_t leftREZZOutarray[OUTSIDE_END+REZZ_ANIMATION_STEPS+2];
uint32_t leftREZZMiddlearry[REZZ_ANIMATION_STEPS+MIDDLE_END-MIDDLE_START+2];
uint32_t leftREZZCenterarry[INNER_END-INNER_START+2];           
               
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel left = Adafruit_NeoPixel(44, PINLEFT, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel right = Adafruit_NeoPixel(44, PINRIGHT, NEO_GRB + NEO_KHZ800);
// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  left.begin();
  right.begin();
  left.show(); // Initialize all pixels to 'off'
  right.show();
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  
  //WORKING
 //colorWipe(left.Color(255, 0, 0), 20); // Red
 //colorWipe(left.Color(0, 255, 0), 20); // Green
 //colorWipe(left.Color(0, 0, 255), 20); // Blue
left.setBrightness(50);
right.setBrightness(50);

 trueREZZ();

// displayREZZ(200);
  
} 



void trueREZZ(){


byte OutPattern[80] = {16,8,3,1,0,0,0,0,
                          0,0,0,0,16,8,3,1,
                          0,0,0,0,0,0,0,0,
                          16,8,3,1,0,0,0,0,
                          0,0,0,0,16,8,3,1,
                          0,0,0,0,0,0,0,0,
                          16,8,3,1,0,0,0,0,
                          0,0,0,0,16,8,3,1,
                          0,0,0,0,0,0,0,0,
                          16,8,3,1,0,0,0,0,};


byte MidPattern[80] = {16,8,3,1,0,0,0,0,
                      16,8,3,1,0,0,0,0,
                      16,8,3,1,0,0,0,0,
                      16,8,3,1,0,0,0,0,
                      16,8,3,1,0,0,0,0,
                      16,8,3,1,0,0,0,0,
                      16,8,3,1,0,0,0,0,
                      16,8,3,1,0,0,0,0,
                      16,8,3,1,0,0,0,0,
                      16,8,3,1,0,0,0,0,};
  
byte CenPattern[28] = {16,3,1,0,16,3,1,0,16,3,1,0,16,3,1,0,16,3,1,0,16,3,1,0,16,3,1,0};
                                              
  
while(true){

//calculate animiation position for outer ring
    if (timeElapsedout > OUTER_DELAY) 
  {       
          timeElapsedout = 0;  // reset the counter to 0 so the counting starts over...
          animationposoutside++;
                if(animationposoutside > REZZ_ANIMATION_STEPS){
                animationposoutside = 0;
                timeElapsedout = 0;
                };
        };
//calculate animiation position for middle ring
    if (timeElapsedmiddle > MIDDLE_DELAY) 
  {       
    timeElapsedmiddle = 0;       // reset the counter to 0 so the counting starts over...
          animationposmiddle++;
                if(animationposmiddle > REZZ_ANIMATION_STEPS){
                animationposmiddle = 0;
                timeElapsedmiddle = 0;
                };
        };
//calculate animiation position for center ring
    if (timeElapsedinner > INNER_DELAY) 
  {       
    timeElapsedinner = 0;      // reset the counter to 0 so the counting starts over...
          animationposinner++;
                if(animationposinner > REZZ_ANIMATION_STEPS){
                animationposinner = 0;
                timeElapsedinner = 0;
                };
        };
        
//calculate color steps        
        if (timeElapsedcolor > COLOR_DELAY) 
  {       
          timeElapsedcolor = 0;  // reset the counter to 0 so the counting starts over...
          animationcolor++;
                if(animationcolor > 254){
                animationcolor = 0;
                timeElapsedcolor = 0;
                };
        };

 //update colors for outer ring
for(uint16_t j=0; j<(OUTSIDE_END+REZZ_ANIMATION_STEPS+2); j++){
leftREZZOutarray[j] = Wheel2(animationcolor, OutPattern[j]);
};

//update colors for middle ring
for(uint16_t j=0; j<(REZZ_ANIMATION_STEPS+MIDDLE_END-MIDDLE_START+2); j++){
leftREZZMiddlearry[j] = Wheel2(animationcolor, MidPattern[j]);
};

//update colors for inner ring
for(uint16_t j=0; j<(INNER_END-INNER_START+2); j++){
leftREZZCenterarry[j] = Wheel2(animationcolor, CenPattern[j]);
};
    
//update pixles for outer ring     
          for(uint16_t j=0; j<=OUTSIDE_END; ++j) {
          left.setPixelColor(j, leftREZZOutarray[animationposoutside+j]);
          right.setPixelColor(getRight(j), leftREZZOutarray[animationposoutside+j]);
          };
 //update pixles for middle ring         
          
          for(uint16_t j=0; j<=MIDDLE_END-MIDDLE_START; ++j) {
          right.setPixelColor(j+MIDDLE_START, leftREZZMiddlearry[animationposmiddle+j]);
          left.setPixelColor(getRight(j+MIDDLE_START), leftREZZMiddlearry[animationposmiddle+j]);
          };
 //update pixles for center ring         
          for(uint16_t j=0; j<=INNER_END-INNER_START; ++j) {
          left.setPixelColor(j+INNER_START, leftREZZCenterarry[animationposinner+j]);
          right.setPixelColor(getRight(j+INNER_START), leftREZZCenterarry[animationposinner+j]);
          };
                
          
 //write pixles for both sides
    left.show();
    right.show();
};
};
 

uint16_t getRight(uint16_t left) {
  if (left <= OUTSIDE_END) {
    return OUTSIDE_END-left;
  } else if (left <= MIDDLE_END) {
    return (MIDDLE_END-left)+MIDDLE_START;
  } else {
    return (INNER_END-left)+INNER_START;
  }
}

uint32_t Wheel2(float WheelPos, byte scale) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return left.Color(((255 - WheelPos * 3)*scale)/16, 0, ((WheelPos * 3)*scale)/16);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return left.Color(0, ((WheelPos * 3)*scale)/16, ((255 - WheelPos * 3)*scale)/16);
  }
  WheelPos -= 170;
  return left.Color(((WheelPos * 3)*scale)/16, ((255 - WheelPos * 3)*scale)/16, 0);
}
