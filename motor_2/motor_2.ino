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
int plate_1=1,plate_2=0,plate_3=0;
int sPlate_1=0,sPlate_2=0,sPlate_3=0;
int tPlate_1=0,tPlate_2=0,tPlate_3=0;
int sent=0,rec=1,flor=1;
int P_P_1=0,P_P_2=0,P_P_3=0;

void setup() {
  Serial.begin(9600);
  motor_3.setSpeed(255); // Set the motor speed (255 for lift),(155 for plate)
  motor_2.setSpeed(250);
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
  if(sent==1 && product_sent == LOW){
  motor_3.run(BACKWARD);
  delay(3000); 
  
  motor_3.run(RELEASE);
  delay(1000); 
  while(1) {
    // Do nothing, the loop will exit
    if(P_P_1==0){
      for(int i=0;i<=80;i++){
          myservo3.write(i);                  
          delay(30); 
      }
      for(int i=80;i>=0;i--){
          myservo3.write(i); 
          delay(30);
      }  
      //delay(5000);
      P_P_1 = 1;
      sent = 0;
    }else if(P_P_2 == 0){
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
          P_P_2 = 1;
          sent = 0;
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
        P_P_3 = 1;
        sent = 0; 
        return; 
        //delay(5000);
      } 
    }
    return;
  }
  } //------- close--------- 

  //Receive 
  if(rec==1){
    if(flor==1){
      if(plate_1==1){
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
          rec=0;
          plate_1=0;
          return;  
        }
         
      }else if(plate_2==1){
        //rotare 2nd plate-----Start
        motor_2.run(FORWARD);
        delay(235); 
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
          delay(3000); 
          
          motor_3.run(RELEASE);
          delay(1000); 
          while(1){
          plate_2=0;
          rec=0;
          return;
        }
        }     
        
      }else{
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
              rec=0;
              return;
            } 
             
        } 
        
      }
    }else if(flor==2){       // Floor 1 plate 2 Start----
      if(sPlate_1==1){
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
        if(product_rec==LOW){
          motor_3.run(FORWARD);
          delay(3000); 
          
          motor_3.run(RELEASE);
          delay(1000); 
          while(1){
            rec=0;
            return;
          }
        }     
      }else if(sPlate_2==1){
        //rotare 2nd plate-----Start
        motor_2.run(FORWARD);
        delay(300); 
        // Stop motor
        motor_2.run(RELEASE);
        delay(5000); 
        motor_2.run(BACKWARD);
        delay(300); 
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
          if(product_rec==LOW){
            motor_3.run(FORWARD);
            delay(3000); 
            
            motor_3.run(RELEASE);
            delay(1000); 
            while(1){
               rec=0;
              return;
            }
          }    
        }
        
      }else{
        motor_2.run(FORWARD);
        delay(500); 
        // Stop motor
        motor_2.run(RELEASE);
        delay(5000); 
        motor_2.run(BACKWARD);
        delay(500); 
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
          if(product_rec==LOW){
            motor_3.run(FORWARD);
            delay(3000); 
            
            motor_3.run(RELEASE);
            delay(1000);
            while(1){
              rec=0;
              return;
            } 
          }   
       }
      }
    //3rd floor Strat--------------      
    }else{
        if(tPlate_1==1){
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
        if(product_rec==LOW){
          motor_3.run(FORWARD);
          delay(3000); 
          
          motor_3.run(RELEASE);
          delay(1000);
          while(1){
            rec=0;
            return;
          } 
        }     
      }else if(tPlate_2==1){
        //rotare 2nd plate-----Start
        motor_2.run(FORWARD);
        delay(300); 
        // Stop motor
        motor_2.run(RELEASE);
        delay(5000); 
        motor_2.run(BACKWARD);
        delay(300); 
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
          if(product_rec==LOW){
            motor_3.run(FORWARD);
            delay(3000); 
            
            motor_3.run(RELEASE);
            delay(1000); 
            while(1){
              rec=0;
              return;
            }
          }
              
        }
      //third plate third floor  
      }else{
        motor_2.run(FORWARD);
        delay(500); 
        // Stop motor
        motor_2.run(RELEASE);
        delay(5000); 
        motor_2.run(BACKWARD);
        delay(500); 
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
          if(product_rec==LOW){
            motor_3.run(FORWARD);
            delay(3000); 
            
            motor_3.run(RELEASE);
            delay(1000);
            while(1){
              rec=0;
              return;
            } 
          } 
        }    
      }    
    } 
  }
}

