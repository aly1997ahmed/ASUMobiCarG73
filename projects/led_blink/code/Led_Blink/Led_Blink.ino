/*
    LED_Blink with duty cycle 25%
    total cycle time period is 2 second 
 */

int led = 9;
void setup() {
  pinMode(led,OUTPUT);
}

void loop() {
  digitalWrite(led,HIGH);
  delay(500);
  digitalWrite(led,LOW);
  delay(1500);

}
