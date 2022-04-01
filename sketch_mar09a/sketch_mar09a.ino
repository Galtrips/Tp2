#include "FeatherShieldPinouts.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define NUMPIXELS 10
Adafruit_NeoPixel pixels(NUMPIXELS, A0, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500
bool lum = false;
int t;
int i = 0;
int j = 9;
int k = 4;
int l = 5;
bool monter = true;
bool monter2 = true;

volatile int interrupCounter;
hw_timer_t*timer=NULL;
int oldValue;

void IRAM_ATTR fonctionIsr(){
  if (i == 9){
    monter = false;
  }
  else if (i == 0) {
    monter = true;
  }

  if (k == 9){
    monter2 = false;
  }
  else if (k == 0) {
    monter2 = true;
  }

  if (monter == true) {
    i++;
    j--;
  }
  else if (monter == false){
    i--;
    j++;
  }

  if (monter2 == true) {
    k++;
    l--;
  }
  else if (monter2 == false){
    k--;
    l++;
  }
  pixels.clear();
  pixels.setPixelColor(i, pixels.Color(255,0,0));  
  pixels.setPixelColor(j, pixels.Color(0,0,255));  
  pixels.setPixelColor(k, pixels.Color(255,0,0));  
  pixels.setPixelColor(l, pixels.Color(0,0,255));  
}

void setup() {
  pinMode(A0, OUTPUT);
  //pinMode(D4, OUTPUT);
  pinMode(A2, INPUT);
  Serial.begin(115000);
  attachInterrupt(A2,fonctionIsr , RISING);
  timer=timerBegin(0,1,true);
  timerAttachInterrupt(timer,&fonctionIsr,true);
  timerAlarmWrite(timer,1000000,true);
  timerAlarmEnable(timer);
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  //digitalWrite(D4, HIGH);
  pixels.begin();
}


void loop() {
  pixels.show();
}

/*
void IRAM_ATTR fonctionIsr(){
 Serial.print("Interaction\n");
  if (lum == false) {
      lum = true;
    }
  else {
      lum = false;
    }
}

void setup() {
  pinMode(A0, OUTPUT);
  pinMode(A2, INPUT);
  Serial.begin(115000);
  attachInterrupt(A2,fonctionIsr , RISING);
}


void loop() {
  digitalWrite(A0,lum);
}*/
