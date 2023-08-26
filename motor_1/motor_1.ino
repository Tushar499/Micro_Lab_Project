#include <AFMotor.h>
#include <Servo.h>
#include <Keypad.h>
#include <SPI.h>

#define IR_SENSOR_PIN_1 31
#define IR_SENSOR_PIN_2 30 
//--------------
Servo myservo1;  
Servo myservo2;
Servo myservo3;
//--------------
AF_DCMotor motor_3(3); // 3 for belt , 2for Plate, 1for Lift
AF_DCMotor motor_2(2);
AF_DCMotor motor_1(1);
//------------
int plate_1=0,plate_2=0,plate_3=0;
int sent=0,rec=1,flor=1;
int P_P_1=1,P_P_2=0,P_P_3=0;

void setup() {
  Serial.begin(9600);
  motor_3.setSpeed(255); // Set the motor speed (255 for lift),(155 for plate)
  motor_2.setSpeed(255);
  motor_1.setSpeed(255);

  //--------------
  pinMode(IR_SENSOR_PIN_1, INPUT); // Set IR sensor pin as input
  pinMode(IR_SENSOR_PIN_2, INPUT);
  //--------
  myservo1.attach(48);
  myservo1.write(180);
  myservo2.attach(49);
  myservo2.write(140);
  myservo3.attach(47);
  myservo3.write(0);
  //-----------
}

void loop() {
  int product_sent = digitalRead(IR_SENSOR_PIN_1); 
  int product_rec = digitalRead(IR_SENSOR_PIN_2);

//Send Product in First plate and booked P_1 ---------------
  motor_1.run(FORWARD);
  delay(465);
  motor_1.run(RELEASE);
  delay(1000);
  motor_1.run(BACKWARD);
  delay(465);
  motor_1.run(RELEASE);
  delay(1000);

}
