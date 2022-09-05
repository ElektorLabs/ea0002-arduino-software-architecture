#define red 3
#define amber 4
#define green 5

#define red_two 6
#define amber_two 7
#define green_two 8

#define red_pedestrian_one 9
#define amber_pedestrian_one 10

#define button_pedestrian_one 12

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  bool button_pressed = LOW;
  
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
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Entering loop...");

  // Start with RED phase
  Serial.println("Phase_One");
  digitalWrite(amber, LOW);
  digitalWrite(red, HIGH);
  delay(3000);

  // RED/AMBER phase
  Serial.println("Phase_Two");
  digitalWrite(amber, HIGH);
  delay(750);

  // GREEN phase
  Serial.println("Phase_Three");
  digitalWrite(red, LOW);
  digitalWrite(amber, LOW);
  digitalWrite(green, HIGH);
  delay(3000);

  // AMBER phase
  Serial.println("Phase_Four");
  digitalWrite(green, LOW);
  digitalWrite(amber, HIGH);
  delay(1000);

}
