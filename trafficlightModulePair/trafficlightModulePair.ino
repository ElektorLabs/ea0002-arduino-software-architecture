#include "tlmodule.h"

#define red 3
#define amber 4
#define green 5

#define red_two 6
#define amber_two 7
#define green_two 8

#define red_pedestrian_one 9
#define amber_pedestrian_one 10

#define button_pedestrian_one 12

tlModule tlGroupOne;
tlModule tlGroupTwo;
byte tlGroupActive = 1;

/* Local implementation for time delay */
void mytlWait (int waitTime) {
  Serial.print("mtlWait called: ");
  Serial.println(waitTime);
  delay(waitTime);
}

/* Local implementation of lamp control */
void mytlOneLampControl(int lamp, bool control) {
  byte led = 0;
  
  Serial.print("mytOnelLampControl called: ");
  Serial.print(lamp);
  Serial.print(" ");
  Serial.println(control);
  
  switch (lamp) {
    case tlRed:
      led = red;
      break;

    case (tlAmber):
      led = amber;
      break;

    case (tlGreen):
      led = green;
      break;

    default:
      Serial.println("mytlOneLampControl ERROR");
      break;
  }

  if (control == false) {
    digitalWrite(led, LOW);
  } else {
    // We're assuming when not "0" LED should be turned on!
    digitalWrite(led, HIGH);
  }
}

/* Local implementation of lamp control */
void mytlTwoLampControl(int lamp, bool control) {
  byte led = 0;
  
  Serial.print("mytlTwoLampControl called: ");
  Serial.print(lamp);
  Serial.print(" ");
  Serial.println(control);
  
  switch (lamp) {
    case tlRed:
      led = red_two;
      break;

    case (tlAmber):
      led = amber_two;
      break;

    case (tlGreen):
      led = green_two;
      break;

    default:
      Serial.println("mytlTwoLampControl ERROR");
      break;
  }

  if (control == false) {
    digitalWrite(led, LOW);
  } else {
    // We're assuming when not "0" LED should be turned on!
    digitalWrite(led, HIGH);
  }
}


void setup() {
  // Debug output
  Serial.begin(115200);

  // Plug in everything for first set of traffic lights
  // Initialize traffic light module
  tlControlInit(&tlGroupOne);
  // Lamp control
  tlGroupOne.tlLampControl = &mytlOneLampControl;
  // Timer
  tlGroupOne.tlWait = &mytlWait;

  // Plug in everything for second set of traffic lights
  // Initialize traffic light module
  tlControlInit(&tlGroupTwo);
  // Non-default phase timing
  tlGroupTwo.tlPhaseTiming.timePhaseOne = 750;
  tlGroupTwo.tlPhaseTiming.timePhaseTwo = 250;
  tlGroupTwo.tlPhaseTiming.timePhaseThree = 750;
  tlGroupTwo.tlPhaseTiming.timePhaseFour = 250;
  // Plug in lamp control function
  tlGroupTwo.tlLampControl = &mytlTwoLampControl;
  // Plug in timer delay function
  tlGroupTwo.tlWait = &mytlWait;

  // Locally reset hardware to a "reset" default (all lamps off, button ready)
  bool button_pressed = LOW;
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(amber, OUTPUT);
  pinMode(green, OUTPUT);
  
  pinMode(red_two, OUTPUT);
  pinMode(amber_two, OUTPUT);
  pinMode(green_two, OUTPUT);
  
  pinMode(red_pedestrian_one, OUTPUT);
  pinMode(amber_pedestrian_one, OUTPUT);
  
  pinMode(button_pedestrian_one, INPUT);

  digitalWrite(red, LOW);
  digitalWrite(amber, LOW);
  digitalWrite(green, LOW);
  
  digitalWrite(red_two, LOW);
  digitalWrite(amber_two, LOW);
  digitalWrite(green_two, LOW);
  
  pinMode(red_pedestrian_one, LOW);
  pinMode(amber_pedestrian_one, LOW);
  
  // Start once button is pressed
  do {
    button_pressed = digitalRead(button_pedestrian_one);
  } while (button_pressed == !LOW);

  //Take both out of reset and force to phase one (red light on)
  tlGroupOne.tlPhaseTiming.timePhaseOne = 1;
  tlGroupTwo.tlPhaseTiming.timePhaseOne = 1;
  tlControl(&tlGroupOne);
  tlControl(&tlGroupOne);
  tlControl(&tlGroupTwo);
  tlControl(&tlGroupTwo);
  // Set phase one times to correct values
  tlGroupOne.tlPhaseTiming.timePhaseOne = 3000;
  tlGroupTwo.tlPhaseTiming.timePhaseOne = 750;
  // Wait three second so both set of traffic lights are red
  delay(3000);
}

void loop() {
  trafficLightState currentTlState;
  
  Serial.println("Looping...");

  if (tlGroupActive == 1) {
    // Get current traffic light state  
    currentTlState = tlGroupOne.tlState;
  
    switch(currentTlState) {
    case Reset:
      Serial.println("Reset");
      break;
    case Phase_One:
      Serial.println("Phase one");
      // Now switch to second set of traffic lights
      tlGroupActive = 2;
      break;
    case Phase_Two:
      Serial.println("Phase two");
      break;
    case Phase_Three:
      Serial.println("Phase three");
      break;
    case Phase_Four:
      Serial.println("Phase four");
      break;
    default:
      break;
    }

    // Now call the control of the traffic lights
    tlControl(&tlGroupOne);
  } else {
    // Get current traffic light state  
    currentTlState = tlGroupTwo.tlState;
  
    switch(currentTlState) {
    case Reset:
      Serial.println("Reset");
      break;
    case Phase_One:
      Serial.println("Phase one");
      // Now switch to first set of traffic lights
      tlGroupActive = 1;
      break;
    case Phase_Two:
      Serial.println("Phase two");
      break;
    case Phase_Three:
      Serial.println("Phase three");
      break;
    case Phase_Four:
      Serial.println("Phase four");
      break;
    default:
      break;
    }
    
    // Now call the control of the traffic lights
    tlControl(&tlGroupTwo);
  }
}
