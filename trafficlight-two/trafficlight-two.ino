#define red_one 3
#define amber_one 4
#define green_one 5

#define red_two 6
#define amber_two 7
#define green_two 8

#define red_pedestrian_one 9
#define green_pedestrian_one 10

#define button_pedestrian_one 12

bool pedestrianRequest = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  bool button_pressed = LOW;

  pinMode(red_one, OUTPUT);
  pinMode(amber_one, OUTPUT);
  pinMode(green_one, OUTPUT);
  
  pinMode(red_two, OUTPUT);
  pinMode(amber_one, OUTPUT);
  pinMode(green_one, OUTPUT);
  
  pinMode(red_pedestrian_one, OUTPUT);
  pinMode(green_pedestrian_one, OUTPUT);
  
  pinMode(button_pedestrian_one, INPUT);

  digitalWrite(red_one, LOW);
  digitalWrite(amber_one, LOW);
  digitalWrite(green_one, LOW);
  
  digitalWrite(red_two, LOW);
  digitalWrite(amber_one, LOW);
  digitalWrite(green_one, LOW);
  
  digitalWrite(red_pedestrian_one, LOW);
  digitalWrite(green_pedestrian_one, LOW);

  // Start once button is pressed
  do {
    button_pressed = digitalRead(button_pedestrian_one);
  } while (button_pressed == !LOW);

  Serial.println("Starting...");

  attachInterrupt(digitalPinToInterrupt(button_pedestrian_one), crossingRequest, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  bool button_pressed = LOW;

  digitalWrite(red_pedestrian_one, HIGH);
  
  while (1) {
    // Start with RED phase
    digitalWrite(amber_one, LOW);
    digitalWrite(red_one, HIGH);
    delay(3000);

    //button_pressed = digitalRead(button_pedestrian_one);
    //Serial.println("Getting button");
    
    if (pedestrianRequest == true) {
      Serial.println("Button pressed");

      //Clear request
      pedestrianRequest = false;
      
      digitalWrite(red_pedestrian_one, LOW);
      digitalWrite(green_pedestrian_one, HIGH);
      delay(3000);

      // Flash
      for (int count = 0; count < 5; ++count) {
        digitalWrite(green_pedestrian_one, LOW);
        delay(500);
        digitalWrite(green_pedestrian_one, HIGH);
        delay(500);
      }

      digitalWrite(red_pedestrian_one, HIGH);
      digitalWrite(green_pedestrian_one, LOW);
      delay(1000);
    }
    //Serial.println("Past getting button");
    
    // RED/AMBER phase
    digitalWrite(amber_one, HIGH);
    delay(750);

    // GREEN phase
    digitalWrite(red_one, LOW);
    digitalWrite(amber_one, LOW);
    digitalWrite(green_one, HIGH);
    delay(3000);

    // AMBER phase
    digitalWrite(green_one, LOW);
    digitalWrite(amber_one, HIGH);
    delay(1000);
    
    // Repeats
  }
}

void crossingRequest() {
  pedestrianRequest = true;
}
