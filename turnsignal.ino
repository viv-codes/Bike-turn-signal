#include <Adafruit_NeoPixel.h>

#define PIN 6 //I may need to adjust this for production hardware when I move to nano or micro
#define NUMPIXELS 8 //the number of pixels being used. Make sure to update this if I end up chaining the strips

Adafruit_Neopixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
    pixels.begin();             //initializes the pixels
    pixels.show();              //turns brightness off
    pixels.setBrightness(200);  //sets the brightness (max 255)
}

void loop() {


}