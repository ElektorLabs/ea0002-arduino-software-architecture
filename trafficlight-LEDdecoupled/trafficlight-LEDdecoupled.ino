#define red 3
#define amber 4
#define green 5

#define red_two 6
#define amber_two 7
#define green_two 8

#define red_pedestrian_one 9
#define amber_pedestrian_one 10

#define button_pedestrian_one 12

// Create new type of enum for our state machine
// traffic light phases plus a reset "start" phase
typedef enum {
    Reset,
    Phase_One,
    Phase_Two,
    Phase_Three,
    Phase_Four
} trafficLightState;

// Create our statemachine variable; set to "reset" state
trafficLightState trafficLightOne = Reset;

// Create a new type of struct for traffic light
// phase timings
typedef struct tlPhaseTiming {
   int timePhaseOne;
   int timePhaseTwo;
   int timePhaseThree;
   int timePhaseFour;
} tlPhaseTime;

// Create a variable to store the phase timings
tlPhaseTime tlTiming;

// Create user's own delay function that can accept millisecond
// timing units and execute the delay
void mytlWait (int waitTime) {
  Serial.print("mytlWait called: ");
  Serial.print(waitTime);
  Serial.println(" ms");
  delay(waitTime);
}

// Pointer to user's "delay" function
void (*tlWait)(int) = NULL; // Alternatively: = &mytlWait;

// LED Decoupling support - this is how I (the traffic light
// module) will name the three lamps
typedef enum {
    tlRed,
    tlAmber,
    tlGreen
} tlLamps;

// Declare user's own lamp control function that can accept a tlLamps
// timing units and execute the delay
void mytlLampControl(tlLamps lamp, bool control);

// Implement the function (we declare seperately because we cannot 
// implement the function using a typedef enum without declaring it
// first).
void mytlLampControl(tlLamps lamp, bool control) {
  byte led = 0;
  
  Serial.print("mytlLampControl called: ");
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
      Serial.println("mytlLampControl ERROR");
      break;
  }

  if (control == 0) {
    digitalWrite(led, LOW);
  } else {
    // We're assuming when not "0" LED should be turned on!
    digitalWrite(led, HIGH);
  }
}

// Pointer to user's "LED control" function
void (*tlLampControl)(tlLamps, bool) = NULL;

void setup() {
  Serial.begin(115200);

  // Plug in your delay function for my traffic light module
  tlWait = &mytlWait;
  //tlWait = NULL;

  // Plug in your LED control function for my traffic light module
  tlLampControl = &mytlLampControl;
  
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

  // Setup Phase Timings
  tlTiming.timePhaseOne = 3000;
  tlTiming.timePhaseTwo = 750;
  tlTiming.timePhaseThree = 3000;
  tlTiming.timePhaseFour = 1000;
  
  // Start once button is pressed
  do {
    button_pressed = digitalRead(button_pedestrian_one);
  } while (button_pressed == !LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Entering loop...");
  
  Serial.print("State of trafficLightOne = ");
  Serial.println(trafficLightOne);
  
  switch (trafficLightOne) {
    case Reset:
      Serial.println("Reset");
      tlLampControl(tlRed, false);
      tlLampControl(tlAmber, false);
      tlLampControl(tlGreen, false);
      trafficLightOne = Phase_One;
      break;
      
    case Phase_One:
      Serial.println("Phase_One");
      tlLampControl(tlAmber, false);
      tlLampControl(tlRed, true);
      tlWait(tlTiming.timePhaseOne);
      trafficLightOne = Phase_Two;
      break;
      
    case Phase_Two:
      Serial.println("Phase_Two");
      tlLampControl(tlAmber, true);
      tlWait(tlTiming.timePhaseTwo);
      trafficLightOne = Phase_Three;
      break;
      
    case Phase_Three:
      Serial.println("Phase_Three");
      tlLampControl(tlRed, false);
      tlLampControl(tlAmber, false);
      tlLampControl(tlGreen, true);
      tlWait(tlTiming.timePhaseThree);
      trafficLightOne = Phase_Four;
      break;
      
    case Phase_Four:
      Serial.println("Phase_Four");
      tlLampControl(tlGreen, false);
      tlLampControl(tlAmber, true);
      tlWait(tlTiming.timePhaseFour);
      trafficLightOne = Phase_One;
      break;
      
    default:
      break;
  }
}
