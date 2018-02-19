//Write embedded program that show a bouncing light between 4 LEDs connected to pins 4, 5, 6 and 7.
//The bouncing delay is 1 second.
void setup() {
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(4, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(4, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(5, LOW);   
  digitalWrite(6, LOW);  
  digitalWrite(7, LOW);   
  delay(1000);              // wait for a second
      digitalWrite(4, LOW);  
      digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(6, LOW);  
      digitalWrite(7, LOW);  
      delay(1000);              // wait for a second
        digitalWrite(4, LOW);  
        digitalWrite(5, LOW);   
        digitalWrite(6, HIGH);  // turn the LED on (HIGH is the voltage level)
        digitalWrite(7, LOW);  
        delay(1000);              // wait for a second
            digitalWrite(4, LOW);  
            digitalWrite(5, LOW);   
            digitalWrite(6, LOW);  
            digitalWrite(7, HIGH);  // turn the LED on (HIGH is the voltage level)
            delay(1000);              // wait for a second
              digitalWrite(4, LOW);  
              digitalWrite(5, LOW);   
              digitalWrite(6, HIGH);  
              digitalWrite(7, LOW);  // turn the LED on (HIGH is the voltage level)
              delay(1000); 
                digitalWrite(4, LOW);  
                digitalWrite(5, HIGH);   
                digitalWrite(6, LOW);  
                digitalWrite(7, LOW);  // turn the LED on (HIGH is the voltage level)
                delay(1000); 
}

