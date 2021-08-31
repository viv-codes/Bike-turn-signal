#include <Adafruit_NeoPixel.h>

#define PIN 6 //I may need to adjust this for production hardware when I move to nano or micro
#define NUMPIXELS 8 //the number of pixels being used. Make sure to update this if I end up chaining the strips
#define SWITCH0 3 //make sure this is ok, used for direction
#define SWITCH1 4 //make sure this is ok, used for direction
#define BUTTON0 2 //this is for the mode-switcher, make sure this is ok

Adafruit_Neopixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
    pixels.begin();             //initializes the pixels
    pixels.show();              //turns brightness off
    pixels.setBrightness(200);  //sets the brightness (max 255)
}

void loop() {
    if(SWITCH0=HIGH) {

    }

}

void solidBar(int wait) {
    pixels.clear();
    for(int i=0; i<NUMPIXELS; i++) {
        pixels.setPixelColor(i, pixels.Color(255,0,0));
        pixels.show();
    }
    delay(1000);
}