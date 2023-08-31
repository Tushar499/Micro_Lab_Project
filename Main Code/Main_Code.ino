#include <AFMotor.h>
#include <Servo.h>
#include <Keypad.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display


#define IR_SENSOR_PIN_1 31
#define IR_SENSOR_PIN_2 30 
//--------------Scanner Start----------
#define SS_PIN 53 
#define RST_PIN 38

MFRC522 mfrc522(SS_PIN, RST_PIN); 

byte Name1[4] = {0xD3, 0x46, 0x14, 0x0A}; // Tushar UID card
byte Name2[4] = {0x43, 0x9E, 0x5D, 0x97}; // Rakib UID card
//------------Keypad Start----------
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

Servo myservo1;  
Servo myservo2;
Servo myservo3;
String Str;
//--------------
AF_DCMotor motor_3(3); // 3 for belt , 2for Plate, 1for Lift
AF_DCMotor motor_2(2);
AF_DCMotor motor_1(1);
//------------
int plate_1=0,plate_2=0,plate_3=0;
int sPlate_1=0,sPlate_2=0,sPlate_3=0;
int tPlate_1=0,tPlate_2=0,tPlate_3=0;
int sent=0,rec=0,flor=1,model=0;
int P_P_1=0,P_P_2=0,P_P_3=0;
int Red=0,Green=0,Blue=0;
int bag=0,pen=0,others=0;
int person1=0,person2=0,xx=1;
char aa,bb,cc,dd;
String s="";


void setup() {
  Serial.begin(9600);
  motor_3.setSpeed(255); // Set the motor speed (255 for lift),(155 for plate)
  motor_2.setSpeed(250);
  motor_1.setSpeed(255);
  //Serial.print("Connected...");
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
  //-----------Display Start---------
  lcd.begin();         // initialize the lcd
  lcd.backlight();    // Turn on the LCD screen backlight
  SPI.begin(); 
  mfrc522.PCD_Init(); 

}

void loop() {

  String str_category="0",str_color="none",str_text="none",str_person="none";
  String str_signal = "0";
  String send_info = str_signal + "#" + str_category + "#" + str_color + "#" + str_text + "#" + str_person;
  Serial.println(send_info);
  
  int product_sent = digitalRead(IR_SENSOR_PIN_1); 
  int product_rec = digitalRead(IR_SENSOR_PIN_2);
  lcd.setCursor(0, 0);
  lcd.print("Scan Your ID");
    if(person1 == 1 || person2==1){
      if(person1==1){
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Mahmud Tushar");
          str_person = "Mahmud Tushar";
        }else if(person2==1){
          lcd.setCursor(0, 0);
          lcd.print("Rakibul Hasan");
          str_person = "Rakibul Hasan";
        }
       delay(2000);
      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("Sent? -> Press 1");
      
      lcd.setCursor(0, 1);
      lcd.print("Rece? -> Press 2");
      char key;
      while(1){
        key = keypad.getKey();
        if(key){
          break;
        }
      }
      
      lcd.clear();
    
      
      if(key == '1'){
        
        lcd.setCursor(0, 0);
        lcd.print("Place item");
        delay(5000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Processing...");
        str_signal = "1";
        send_info = str_signal + "#" + str_category + "#" + str_color + "#" + str_text + "#" + str_person;
        
        Serial.println(send_info);
        while(Serial.available()==0){
          //
        }
        str_category = Serial.readStringUntil('\n');
        str_signal = "0";
        send_info = str_signal + "#" + str_category + "#" + str_color + "#" + str_text + "#" + str_person;
        Serial.println(send_info);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("detect.completed");
        delay(3000);

        sendItem(str_category);
     
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Thank You");
        delay(5000);
        person1=0;
        person2=0;
        
      }else if(key == '2'){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Select Your");
        lcd.setCursor(0, 1);
        lcd.print("Lost item!");
        delay(3000);
        lcd.clear();
        String category = "",color = "",text = "";

        lcd.setCursor(0, 0);
        lcd.print("Select Your");
        lcd.setCursor(0, 1);
        lcd.print("Item Name");
        delay(3000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Pendrive -> 7");
        lcd.setCursor(0, 1);
        lcd.print("Handbag -> 8");
        delay(4000); 
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Other item -> 9");
        delay(4000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Press Key For");
        lcd.setCursor(0, 1);
        lcd.print("Answer Query");
        char temp_key;
        while(1){
          temp_key = keypad.getKey();
          if(temp_key == '7'){
            category = "1";
            break;
          }else if(temp_key == '8'){
            category = "2";
            break;
          }else if(temp_key == '9'){
            category = "3";
            break;
          }
        }
        
        lcd.clear();

        lcd.setCursor(0, 0);
        lcd.print("Item Color ?");
        delay(3000);
        lcd.clear();
        
        lcd.setCursor(0, 0);
        lcd.print("red->4,green->5");
        lcd.setCursor(0, 1);
        lcd.print("blue->6");
        delay(3000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Press Key For");
        lcd.setCursor(0, 1);
        lcd.print("Answer Query");
        char temp2_key;
        while(1){
          temp2_key = keypad.getKey();
          if(temp2_key == '4'){
            color = "red";
            break;
          }else if(temp2_key == '5'){
            color = "green";
            break;
          }else if(temp2_key == '6'){
            color = "blue";
            break;
          }  
        }

        lcd.clear();

        lcd.setCursor(0, 0);
        lcd.print("Item Text ?");
        lcd.setCursor(0, 1);
        lcd.print("A-B-C-D");
        delay(4000);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Press Key For");
        lcd.setCursor(0, 1);
        lcd.print("Answer Query");
        char temp3_key;
        while(1){
          temp3_key = keypad.getKey();
          if(temp3_key == 'A'){
            text = "a";
            break;
          }else if(temp3_key == 'B'){
            text = "b";
            break;
          }else if(temp3_key == 'C'){
            text = "c";
            break;
          }else if(temp3_key == 'D'){
            text = "d";
            break;
          }
        }
        lcd.clear();

        lcd.setCursor(0, 0);
        lcd.print("Verifying...");

        str_signal = "2";
        send_info = str_signal + "#" + category + "#" + color + "#" + text + "#" + str_person;
        Serial.println(send_info);
        while(Serial.available()==0){
          //
        }
        String valid = Serial.readStringUntil('\n');
        str_signal = "0";
        send_info = str_signal + "#" + str_category + "#" + str_color + "#" + str_text + "#" + str_person;
        Serial.println(send_info);
        lcd.clear();
        if(valid == "ok"){
          lcd.setCursor(0, 0);
          lcd.print("Processing...");
          
          receiveItem(category);

          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Delivered To");
          lcd.setCursor(0, 1);
          lcd.print(str_person);
          delay(4000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Thank You");
          delay(2000);
          lcd.clear();
        }else if(valid == "notok"){
          lcd.setCursor(0, 0);
          lcd.print("Item Not Found!");
          delay(4000);
          lcd.clear();
        }
        person1=0;
        person2=0;
      }
}


if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  if (compareUID(mfrc522.uid.uidByte, Name1)) {
    person1=1;
  }if (compareUID(mfrc522.uid.uidByte, Name2)) {
    person2=1;
  } 
  // Halt PICC
  mfrc522.PICC_HaltA();
  // Stop encryption on PCD
  mfrc522.PCD_StopCrypto1(); 
}


bool compareUID(byte* cardID, byte* expectedID) {
  for (int i = 0; i < 4; i++) {
    if (cardID[i] != expectedID[i]) {
      return false;
    }
  }
  return true;
}





void sendItem(String c)
{

  motor_3.run(BACKWARD);
  delay(6000); 
  
  motor_3.run(RELEASE);
  delay(1000); 
  while(1) {
    // Do nothing, the loop will exit
    if(c=="1"){
      for(int i=0;i<=80;i++){
          myservo3.write(i);                  
          delay(30); 
      }
      for(int i=80;i>=0;i--){
          myservo3.write(i); 
          delay(30);
      }  
      //delay(5000);
      return;
      
    }else if(c == "2"){
      motor_2.run(FORWARD);
      delay(150); 
      // Stop motor
      
      while(1){
        motor_2.run(RELEASE);
        delay(3000);
        for(int i=0;i<=80;i++){
        myservo3.write(i);                  
        delay(30); 
        }
        for(int i=80;i>=0;i--){
            myservo3.write(i); 
            delay(30);
        }  
        motor_2.run(BACKWARD);
        delay(150); 
        // Stop motor
        motor_2.run(RELEASE);
        delay(1000);
        while(1){
          return;
        } 
      } 
      
    }else{
      motor_2.run(FORWARD);
      delay(200); 
      motor_2.run(RELEASE);
      delay(2000); 
      motor_2.run(FORWARD);
      delay(200); 
      motor_2.run(RELEASE);
      delay(2000); 
      while(1){
          for(int i=0;i<=80;i++){
          myservo3.write(i);                  
          delay(30); 
        }
        for(int i=80;i>=0;i--){
            myservo3.write(i); 
            delay(30);
        }
        motor_2.run(BACKWARD);
        delay(209); 
        // Stop motor
        motor_2.run(RELEASE);
        delay(1000); 
        motor_2.run(BACKWARD);
        delay(209); 
        // Stop motor
        motor_2.run(RELEASE);
        delay(1000); 
        return; 
        //delay(5000);
      } 
    }
    return;
  }
}

void receiveItem(String category){
  if(category == "1"){
    //--------plate to lift-------start
    for(int i=180;i>=50;i--){
      myservo1.write(i);                  
      delay(30);  
    }
    for(int i=50;i<=180;i++){
      myservo1.write(i);
      delay(30);
    }
    //--------plate to lift-------end
    //--------lift to belt-------start
    for(int i=140;i>=0;i--){
      myservo2.write(i);
      delay(30);
    }    
    for(int i=0;i<=140;i++){
      myservo2.write(i);                  
      delay(30);
    }
    //--------lift to belt-------end
    //belt start towards door
    delay(1000);
    motor_3.run(FORWARD);
    delay(3000); 
    
    motor_3.run(RELEASE);
    delay(1000); 
    while(1){
      return;  
    }
    
  }else if(category == "2"){
    //rotare 2nd plate-----Start
    motor_2.run(FORWARD);
    delay(235); 
    // Stop motor
    motor_2.run(RELEASE);
    delay(1000); 
    
    while(1){
      //--------plate to lift-------start
    for(int i=180;i>=50;i--){
      myservo1.write(i);                  
      delay(30);  
    }
    for(int i=50;i<=180;i++){
      myservo1.write(i);
      delay(30);
    }
    //-------
    motor_2.run(BACKWARD);
    delay(240); 
    // Stop motor
    motor_2.run(RELEASE);
    delay(1000);
    //--------plate to lift-------end
    //--------lift to belt-------start
    for(int i=140;i>=0;i--){
      myservo2.write(i);
      delay(30);
    }    
    for(int i=0;i<=140;i++){
      myservo2.write(i);                  
      delay(30);
    }
    //--------lift to belt-------end
    //belt start towards door
    delay(2000);
      motor_3.run(FORWARD);
      delay(6000); 
      
      motor_3.run(RELEASE);
      delay(1000); 
      while(1){
      return;
    }
    }     
    
  }else if(category == "3"){
    motor_2.run(FORWARD);
    delay(209); 
    motor_2.run(RELEASE);
    delay(2000);
    motor_2.run(FORWARD);
    delay(209); 
    // Stop motor
    motor_2.run(RELEASE);
    delay(5000); 
    
    while(1){
        //--------plate to lift-------start
      for(int i=180;i>=50;i--){
        myservo1.write(i);                  
        delay(30);  
      }
      for(int i=50;i<=180;i++){
        myservo1.write(i);
        delay(30);
      }
      motor_2.run(BACKWARD);
      delay(210);
      motor_2.run(RELEASE);
      delay(2000);
      motor_2.run(BACKWARD);
      delay(210); 
      // Stop motor
      motor_2.run(RELEASE);
      delay(1000);
      //--------plate to lift-------end
      //--------lift to belt-------start
      for(int i=140;i>=0;i--){
        myservo2.write(i);
        delay(30);
      }    
      for(int i=0;i<=140;i++){
        myservo2.write(i);                  
        delay(30);
      }
      //--------lift to belt-------end
      //belt start towards door
      delay(1000);
      motor_3.run(FORWARD);
      delay(3000); 
      
      motor_3.run(RELEASE);
      delay(1000);
      while(1){
        return;
      }    
    }
  } 

}
