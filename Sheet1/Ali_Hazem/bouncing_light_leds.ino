/*
   a bouncing light of 4 leds with delay one second of each one
 */
int Led[4] = {4,5,6,7} ; //config of each led
int selector = 0 ;         //to select which led will be turned on at once
void setup() {
   pinMode(Led[0],OUTPUT);
   pinMode(Led[1],OUTPUT);
   pinMode(Led[2],OUTPUT);
   pinMode(Led[3],OUTPUT);
   
}

void loop() {
     for(selector =0;selector <=3;selector++){
        digitalWrite(Led[selector],HIGH);
        delay(1000);
        digitalWrite(Led[selector],LOW);
     }
     for(selector =2;selector >0;selector--){
       digitalWrite(Led[selector],HIGH);
       delay(1000);
       digitalWrite(Led[selector],LOW);
     }
      

}
