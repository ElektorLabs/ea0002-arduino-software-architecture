#define red 3
#define amber 4
#define green 5

#define red_two 6
#define amber_two 7
#define green_two 8

#define red_pedestrian_one 9
#define amber_pedestrian_one 10

#define button_pedestrian_one 12

typedef enum {
    Reset,
    Phase_One,
    Phase_Two,
    Phase_Three,
    Phase_Four
} trafficLightState;

trafficLightState trafficLightOne = Reset;

typedef struct tlPhaseTiming {
   int timePhaseOne;
   int timePhaseTwo;
   int timePhaseThree;
   int timePhaseFour;
} tlPhaseTime;

tlPhaseTime trafficLightOneTime;

void setup() {
  Serial.begin(115200);
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
  trafficLightOneTime.timePhaseOne = 3000;
  trafficLightOneTime.timePhaseTwo = 750;
  trafficLightOneTime.timePhaseThree = 3000;
  trafficLightOneTime.timePhaseFour = 1000;
  
  // Start once button is pressed
  do {
    button_pressed = digitalRead(button_pedestrian_one);
  } while (button_pressed == !LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (1) {
    Serial.print("Loop trafficLightOne = ");
    Serial.println(trafficLightOne);
    switch (trafficLightOne) {
      case Reset:
        Serial.println("Reset");
        digitalWrite(red, LOW);
        digitalWrite(amber, LOW);
        digitalWrite(green, LOW);
        trafficLightOne = Phase_One;
        break;
        
      case Phase_One:
        Serial.println("Phase_One");
        digitalWrite(amber, LOW);
        digitalWrite(red, HIGH);
        delay(3000);
        trafficLightOne = Phase_Two;
        break;
        
      case Phase_Two:
        Serial.println("Phase_Two");
        digitalWrite(amber, HIGH);
        delay(750);
        trafficLightOne = Phase_Three;
        break;
        
      case Phase_Three:
        Serial.println("Phase_Three");
        digitalWrite(red, LOW);
        digitalWrite(amber, LOW);
        digitalWrite(green, HIGH);
        delay(3000);
        trafficLightOne = Phase_Four;
        break;
        
      case Phase_Four:
        Serial.println("Phase_Four");
        digitalWrite(green, LOW);
        digitalWrite(amber, HIGH);
        delay(1000);
        trafficLightOne = Phase_One;
        break;
        
      default:
        break;
    }
  }
}
