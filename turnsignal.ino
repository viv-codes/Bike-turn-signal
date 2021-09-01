#include <Adafruit_NeoPixel.h>

// Light Hardware
#define PIN0 6      // Left side turn signal lightbar
#define PIN1 7      // Right side turn signal lightbar
#define NUMPIXELS 8
#define LED0 11     // headunit led indicator for left turn 
#define LED1 12     // headunit led indicator for right turn

// Turn signal direction switch
#define SWITCH0 3 //LEFT SIDE
#define SWITCH1 4 //RIGHT SIDE

// Mode selection switch
#define SWITCH00 9  //Normal operation
#define SWITCH01 10 //Pride Mode

// Timing of turn signal
#define time0 100 //1/10 second is the default blink time

//Color defs FIX THESE
int red[] = {255,0,0};
int pink[] = {85,205,252};
int blue[] = {247,168,184};
int white[] = {255,255,255};

// Telling the NeoPixels how to do their thing
Adafruit_NeoPixel pixels0(NUMPIXELS, PIN0, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels1(NUMPIXELS, PIN1,  NEO_GRB + NEO_KHZ800);

void setup() {
    pinMode(PIN0, OUTPUT); // Makes sure that the pins are properly defined
    pinMode(PIN1, OUTPUT);
    pinMode(LED0, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(SWITCH00, INPUT);
    pinMode(SWITCH01, INPUT);
    pinMode(SWITCH0, INPUT);
    pinMode(SWITCH1, INPUT);
    pixels0.begin();    //initializes the pixels
    pixels1.begin();
    pixels0.show();  
    pixels1.show();     //turns brightness off
    pixels0.setBrightness(200); //sets the brightness (max 255)
    pixels1.setBrightness(200);
}

// Primary body of code
void loop() {
    if (digitalRead(SWITCH00) == HIGH) {    // This outer if sequence is what runs the mode switcher
    // Normal mode
        if (digitalRead(SWITCH0) == HIGH) { // Turn signals themselves are consistent between modes for safety and universal recognizability. 
            solidBarLeft();                 
        } else if (digitalRead(SWITCH1) == HIGH) {
            solidBarRight();
        } else {
            solidBar();
        }
    } else if (digitalRead(SWITCH01) == HIGH) {
    // Pride mode, displays a rainbow running light
        if (digitalRead(SWITCH0) == HIGH) {
            solidBarLeft();
        } else if (digitalRead(SWITCH1) == HIGH) {
            solidBarRight();
        } else {
            prideBar();
        }
    } else {
    // Trans pride mode, displays the trans flag as the running light
        if (digitalRead(SWITCH0) == HIGH) {
            solidBarLeft();
        } else if (digitalRead(SWITCH1) == HIGH) {
            solidBarRight();
        } else {
            transPrideBar(pixels0);
            transPrideBar(pixels1);
        }
    }
}

// Functions!!!

// A basic, normal running light
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

// void solidBarLeft and solidBarRight could theoretically be done with a single section of code and args, but the adafruit lib is throwing compile errors and I didn't wanna mess with it

// Left turn signal
void solidBarLeft() { 
    pixels0.clear(); //clears the pixels
    for(int i=0; i<NUMPIXELS; i++) { //sets the pixels, one at a time, to red
        pixels0.setPixelColor(i, pixels0.Color(255,0,0));
        pixels0.show(); // Displays the pixels
    }
    digitalWrite(LED0, HIGH); // Activates the indicator LED
    delay(time0);    //waits 0.1 sec
    pixels0.clear(); //clears the pixels
    pixels0.show();  //displays that the pixels are cleared
    digitalWrite(LED0, LOW);
    delay(time0);    //waits 0.1 sec
}

// Right turn signal
void solidBarRight() {
    pixels1.clear();
    for(int i=0; i<NUMPIXELS; i++) {
        pixels1.setPixelColor(i, pixels1.Color(255,0,0));
        pixels1.show();
    }
    digitalWrite(LED1, HIGH);
    delay(time0);
    pixels1.clear();
    pixels1.show();
    digitalWrite(LED1, HIGH);
    delay(time0);
}

// Pride-themed running lights
void prideBar() {
    pixels0.clear();
    pixels1.clear();
    for(long firstPixelHue=0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
        for(int i=0; i<NUMPIXELS; i++) {
            int pixelHue = firstPixelHue + (i * 65536L / NUMPIXELS);
            pixels0.setPixelColor(i, pixels0.gamma32(pixels0.ColorHSV(pixelHue)));
        }
        pixels0.show();
        delay(10); //this might have to change
    }
}

// Trans-pride themed running lights

void transPrideBar(Adafruit_NeoPixel pixelset) {  //does this work? I don't know. But it verifies. 
    for(int i=0; i<2; i++) {
        pixelset.clear();
        for(int i=0; i<3; i++) {
            pixelset.setPixelColor(i, pixelset.Color(85,205,252));
        }
        for(int i=3; i<6; i++) {
            pixelset.setPixelColor(i, pixelset.Color(247,168,184));
        }
        for(int i=6; i<8; i++) {
            pixelset.setPixelColor(i, pixelset.Color(255,255,255));
        }
        pixelset.show();
    }
}


/*  I'mma just keep this here until I'm sure the for loop version works
void transPrideBar() { //yea I know this is a lot of code, but I did the math. for loops would take almost as much space 
    pixels0.clear();
    pixels1.clear();
    pixels0.setPixelColor(0, pixels0.Color(85,205,252)); 
    pixels0.setPixelColor(1, pixels0.Color(85,205,252));
    pixels0.setPixelColor(2, pixels0.Color(85,205,252));
    pixels0.setPixelColor(3, pixels0.Color(247,168,184));
    pixels0.setPixelColor(4, pixels0.Color(247,168,184));
    pixels0.setPixelColor(5, pixels0.Color(247,168,184));
    pixels0.setPixelColor(6, pixels0.Color(255,255,255));
    pixels0.setPixelColor(7, pixels0.Color(255,255,255)); //I'm probably going to have to change the second strip pending hardware configuration
    pixels1.setPixelColor(0, pixels1.Color(255,255,255));
    pixels1.setPixelColor(1, pixels1.Color(255,255,255));
    pixels1.setPixelColor(2, pixels1.Color(247,168,184));
    pixels1.setPixelColor(3, pixels1.Color(247,168,184));
    pixels1.setPixelColor(4, pixels1.Color(247,168,184));
    pixels1.setPixelColor(5, pixels1.Color(85,205,252));
    pixels1.setPixelColor(6, pixels1.Color(85,205,252));
    pixels1.setPixelColor(7, pixels1.Color(85,205,252));
    pixels0.show();
    pixels1.show();
} */
