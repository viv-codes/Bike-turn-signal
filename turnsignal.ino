/* Notes:
- It would probably be best to keep the turn signals red and blinking solid to prevent confusion. 
- However, the running light could be colorful or rainbow (let's try both)

*/
#include <Adafruit_NeoPixel.h>

#define PIN0 6 //LEFT SIDE I may need to adjust this for production hardware when I move to nano or micro
#define PIN1 7 //RIGHT SIDE lightbar
#define NUMPIXELS 8 //the number of pixels being used. Make sure to update this if I end up chaining the strips

//these are for the 3 pos switch that will be used for signal direction.
#define SWITCH0 3 //LEFT SIDE
#define SWITCH1 4 //RIGHT SIDE

#define BUTTON0 2 //this is for the mode-switcher, make sure this is ok

// Timing
#define time0 100 //1/10 second is the default blink time

Adafruit_NeoPixel pixels0(NUMPIXELS, PIN0, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels1(NUMPIXELS, PIN1,  NEO_GRB + NEO_KHZ800);


void setup() {
    pixels0.begin();             //initializes the pixels
    pixels1.begin();
    pixels0.show();  
    pixels1.show();            //turns brightness off
    pixels0.setBrightness(200);  //sets the brightness (max 255)
    pixels1.setBrightness(200);
}

//there might be a better way of doing this where clears would only happen if there is a state change. IDK if it matters tho

void loop() {
   if (SWITCH0=HIGH) {
        solidBarLeft();
    } 
    else if (SWITCH1=HIGH) {
        solidBarRight();
    }
    else {
        solidBar();
    }

}


void solidBar() {
    pixels0.clear();
    pixels1.clear();
    for(int i=0; i<NUMPIXELS; i++) {
      pixels0.setPixelColor(i, pixels0.Color(255,0,0));
      pixels0.show();
    }
    for(int i=0; i<NUMPIXELS; i++) {
      pixels1.setPixelColor(i, pixels1.Color(255,0,0));
      pixels1.show();
    }
    delay(time0);
}

//void solidBarLeft and solidBarRight could theoretically be done with a single section of code and args, but the adafruit lib is throwing compile errors and I didn't wanna mess with it

void solidBarLeft() { 
    pixels0.clear(); //clears the pixels
    for(int i=0; i<NUMPIXELS; i++) { //sets the pixels, one at a time, to red
        pixels0.setPixelColor(i, pixels0.Color(255,0,0));
        pixels0.show(); //displays the pixels
    }
    delay(time0);    //waits 0.1 sec
    pixels0.clear(); //clears the pixels
    pixels0.show();  //displays that the pixels are cleared
    delay(time0);    //waits 0.1 sec
}

void solidBarRight() {
    pixels1.clear();
    for(int i=0; i<NUMPIXELS; i++) {
        pixels1.setPixelColor(i, pixels1.Color(255,0,0));
        pixels1.show();
    }
    delay(time0);
    pixels1.clear();
    pixels1.show();
    delay(time0);
}
