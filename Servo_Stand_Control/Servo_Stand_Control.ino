#include <Servo.h>
#include <Keypad.h>

// Define the servo and keypad objects
Servo myServo;
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'9', '6', '3', 'A'},
  {'8', '5', '2', 'B'},
  {'7', '4', '1', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {6, 7, 8, 9}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int initialPos = 0; // Initial position of the servo (90 degrees)
int rotationAmount = 110; // Amount to rotate the servo (90 degrees)
int x=0,y=0,z=0,receive=0,sent=0;

void setup() {
  myServo.attach(11); // Attach servo to pin 11
  myServo.write(initialPos); // Move servo to initial position
  Serial.begin(9600);
}

void task1() {
  // Perform task based on subsequent key press
  char taskKey = keypad.getKey();
  if (taskKey == '1') {
    int targetPos = initialPos + rotationAmount;
    myServo.write(targetPos);
    delay(1000);
    myServo.write(initialPos);
  }
}
void loop() {
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
    if(key == 5){
      receive = 1;
    } 
    if (key == '7' && receive == 1) {
      myServo.write(120);
      delay(3000);
      myServo.write(initialPos);
      x=0;
    }if(key == '8' && receive == 1){
      myServo.write(240);
      delay(3000);
      myServo.write(initialPos);
      y=0
    }
    if(key == '9' && receive == 1){
      myServo.write(360);
      delay(3000);
      myServo.write(initialPos);
      z=0;
    }
  }
  if(key == 6){
      sent = 1;
    } 
    if (sent == 1 && x==0) {
      myServo.write(120);
      delay(3000);
      myServo.write(initialPos);
      x=1;
    }if(sent == 1 && y==0){
      myServo.write(240);
      delay(3000);
      myServo.write(initialPos);
      y=1;
    }
    if(sent == 1 && z==0){
      myServo.write(360);
      delay(3000);
      myServo.write(initialPos);
      z=1;
    }
  }
  
}
