#include <Servo.h>
#include <Keypad.h>
#include <SPI.h>

//-------
const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {22, 23, 24, 25}; 
byte colPins[COLS] = {26, 27, 28, 29}; 
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
//----------------
Servo myservo1;  
Servo myservo2;
Servo myservo3;
   
void setup() {
  myservo1.attach(48);
  myservo1.write(180);
  myservo2.attach(49);
  myservo2.write(140);
  myservo3.attach(47);
  myservo3.write(0);
}

void loop() {
  
  char key = keypad.getKey();
  if (key){
    Serial.println(key);
    if(key == '5'){
      for(int i=180;i>=50;i--){
          myservo1.write(i);                  
          delay(30);  
      }
      for(int i=50;i<=180;i++){
          myservo1.write(i);
          delay(30);
      }
     //delay(5000);
    }if(key=='6'){
      for(int i=140;i>=0;i--){
          myservo2.write(i);
          delay(30);
      }    
      for(int i=0;i<=140;i++){
          myservo2.write(i);                  
          delay(30);
      }
      

    }if(key=='7'){
      for(int i=0;i<=80;i++){
          myservo3.write(i);                  
          delay(30); 
      }
      for(int i=80;i>=0;i--){
          myservo3.write(i); 
          delay(30);
      }  
      
    }
  } 
                         
}