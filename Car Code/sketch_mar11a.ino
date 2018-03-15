
#define motorR1 2
#define motorR2 3
#define motorL1 4
#define motorL2 5
#define trig 6
#define echo 7
int value ;
void forward()
{
  digitalWrite(motorR1,HIGH);
  digitalWrite(motorR2,LOW);
  digitalWrite(motorL1,HIGH);
  digitalWrite(motorL2,LOW);
}
void backward()
{
  digitalWrite(motorR1,LOW);
  digitalWrite(motorR2,HIGH);
  digitalWrite(motorL1,LOW);
  digitalWrite(motorL2,HIGH);
}

void right()
{
  digitalWrite(motorR1,LOW);
  digitalWrite(motorR2,HIGH);
  digitalWrite(motorL1,HIGH);
  digitalWrite(motorL2,LOW);
}

void left ()
{
  digitalWrite(motorR1,HIGH);
  digitalWrite(motorR2,LOW);
  digitalWrite(motorL1,LOW);
  digitalWrite(motorL2,HIGH);
}

void stops()
{
  digitalWrite(motorR1,LOW);
  digitalWrite(motorR2,LOW);
  digitalWrite(motorL1,LOW);
  digitalWrite(motorL2,LOW); 
}
long USReadings()
{
  long duration,distance;
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration = pulseIn(echo,HIGH);
  distance= (duration/2)*0.034 ; 
  return distance ; 
}
void setup() {
Serial.begin(9600);
pinMode (motorR1,OUTPUT );
pinMode (motorR2,OUTPUT );
pinMode (motorL1,OUTPUT );
pinMode (motorL2,OUTPUT );
pinMode (trig ,OUTPUT);
pinMode (echo,INPUT );

}

void loop() {
  if (USReadings() >20)
  {
  value=Serial.read();
  switch(value) 
  {
    case 'F': forward();
    case'B' : backward();
    case 'R' :right();
    case 'L':left();
  }
  }
  else  
  {
    right();
  }
  
 
}
