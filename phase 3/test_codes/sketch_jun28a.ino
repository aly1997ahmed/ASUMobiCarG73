#define f1 23                                            // motor a
#define b1 22
#define speeda 2

#define f2 24                                           // motor b
#define b2 25
#define speedb 3

#define encoder1 18                                     //encoders
#define encoder2 19

#define wheeldiameter 6.5
#define numberofsteps 20 
#define spacebetweenwheels 25

int bluetooth_var ; 
int counter1;                                           //encoder counters
int counter2;

int X ;

void forward();
void back();
void Stop();
void left();
void right();
void leftS();
void rightS();
void Speed(int s1, int s2);
void ISR_count1();
void ISR_count2();
int CMtoSteps(float cm);
int AngletoSteps(float ang);
void MoveForward(int steps,int mspeed);
void MoveBack(int steps,int mspeed);
void SpinRight(int steps,int mspeed);
void SpinLeft(int steps,int mspeed);
void setup() {
  Serial.begin(9600); 
  pinMode(f1,OUTPUT);
  pinMode(f2,OUTPUT);
  pinMode(b1,OUTPUT);
  pinMode(b2,OUTPUT);
  pinMode(speeda,OUTPUT);
  pinMode(speedb,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(encoder1),ISR_count1,RISING);
  attachInterrupt(digitalPinToInterrupt(encoder2),ISR_count2,RISING);
}

void loop() {
 if(Serial.available()>0)
 {
  Serial.println("enter distance or angle value");
  X = 0;
  while(1)
  {
    X = Serial.parseInt();
    if(X > 0)
    break;
  }
  Serial.println("F or B ,, L or R ");
  bluetooth_var= 0;
  while(1)
  {
  bluetooth_var = Serial.read();
    if(bluetooth_var == 'F' || bluetooth_var == 'B' || bluetooth_var == 'R' || bluetooth_var == 'L')
    break;
  }
  switch(bluetooth_var)
  {
    case 'F' : MoveForward(CMtoSteps(X),100);
    case 'B' : MoveBack(CMtoSteps(X),100);
    case 'R' : SpinRight(AngletoSteps(X),100);
    case 'L' : SpinLeft(AngletoSteps(X),100);
  }
  
 }

}
void forward()                  //functions
{
  digitalWrite(f1,HIGH);
  digitalWrite(b1,LOW);
  digitalWrite(f2,HIGH);
  digitalWrite(b2,LOW); 
}
void back()
{
  digitalWrite(f1,LOW);
  digitalWrite(b1,HIGH);
  digitalWrite(f2,LOW);
  digitalWrite(b2,HIGH);
}
void Stop()
{
  digitalWrite(f1,LOW);
  digitalWrite(b1,LOW);
  digitalWrite(f2,LOW);
  digitalWrite(b2,LOW);
}
void left()
{
  digitalWrite(f1,HIGH);
  digitalWrite(b1,LOW);
  digitalWrite(f2,LOW);
  digitalWrite(b2,HIGH);
}
void right()
{
  digitalWrite(f1,LOW);
  digitalWrite(b1,HIGH);
  digitalWrite(f2,HIGH);
  digitalWrite(b2,LOW);
}
void leftS()
{
  digitalWrite(f1,HIGH);
  digitalWrite(b1,LOW);
  digitalWrite(f2,LOW);
  digitalWrite(b2,LOW);
}
void rightS()
{
  digitalWrite(f1,LOW);
  digitalWrite(b1,LOW);
  digitalWrite(f2,HIGH);
  digitalWrite(b2,LOW);
}
void Speed(int s1, int s2)
{
  s1 = map(s1,0,100,0,255);
  s2 = map(s2,0,100,0,255);
  analogWrite(speeda,s1);
  analogWrite(speedb,s2);
}
void ISR_count1()
{
  counter1++;
}
void ISR_count2()
{
  counter2++;
}
int CMtoSteps(float cm)
{
  int result;
  float mo7et = wheeldiameter * 3.14 ;
  float cm_step = mo7et / numberofsteps ;
  float resultx = cm / cm_step ;
  result = (int) resultx ;
  return result;
}
int AngletoSteps(float ang)
{
  int result;
  float mo7et = spacebetweenwheels * 2 * 3.14 ;
  float frac = ang / 360 ;
  float resultm = frac * mo7et ;
  float resultx = CMtoSteps(resultm);
  result = (int) resultx ;
  return result;
}
void MoveForward(int steps,int mspeed)
{
  counter1 = 0;
  counter2 = 0;
  forward();
  while(steps > counter1 && steps > counter2)
  {
    Speed(mspeed,mspeed);
  }
  Speed(0,0);
  counter1 = 0;
  counter2 = 0;
}
void MoveBack(int steps,int mspeed)
{
  counter1 = 0;
  counter2 = 0;
  back();
  while(steps > counter1 && steps > counter2)
  {
    Speed(mspeed,mspeed);
  }
  Speed(0,0);
  counter1 = 0;
  counter2 = 0;
}
void SpinRight(int steps,int mspeed)
{
  counter1 = 0;
  counter2 = 0;
  rightS();
  while(steps > counter1 && steps > counter2)
  {
    Speed(mspeed,mspeed);
  }
  Speed(0,0);
   counter1 = 0;
  counter2 = 0;
}
void SpinLeft(int steps,int mspeed)
{
  counter1 = 0;
  counter2 = 0;
  leftS();
  while(steps > counter1 && steps > counter2)
  {
    Speed(mspeed,mspeed);
  }
  Speed(0,0);
   counter1 = 0;
  counter2 = 0;
}
