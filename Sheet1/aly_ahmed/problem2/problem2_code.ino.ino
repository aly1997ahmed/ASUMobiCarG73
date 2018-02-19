#define led1 7
#define led2 6
#define led3 5
#define led4 4

void setup() {
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  

}

void loop() {
  digitalWrite(led1,HIGH);
  delay(1000);
  digitalWrite(led1,LOW);
  digitalWrite(led2,HIGH);
  delay(1000);
  digitalWrite(led2,LOW);
  digitalWrite(led3,HIGH);
  delay(1000);
  digitalWrite(led3,LOW);
  digitalWrite(led4,HIGH);
  delay(1000);
  digitalWrite(led4,LOW);
  digitalWrite(led3,HIGH);
  delay(1000);
  digitalWrite(led3,LOW);
  digitalWrite(led2,HIGH);
  delay(1000);
  digitalWrite(led2,LOW);
}
