#define IR_SENSOR_PIN_1 31
#define IR_SENSOR_PIN_2 30 

void setup() {
  Serial.begin(9600);
  pinMode(IR_SENSOR_PIN_1, INPUT); // Set IR sensor pin as input
  pinMode(IR_SENSOR_PIN_2, INPUT);
}

void loop() {
  int product_sent = digitalRead(IR_SENSOR_PIN_1); 
  int product_rec = digitalRead(IR_SENSOR_PIN_2);
  
  if (product_sent == LOW) {
    Serial.println("1"); // Print "1" if obstacle detected
  } else {
    Serial.println("0"); 
  }
  delay(500); 
  if (obs == LOW) {
    Serial.println("1"); 
  } else {
    Serial.println("0"); 
  }
  delay(500); 
}
