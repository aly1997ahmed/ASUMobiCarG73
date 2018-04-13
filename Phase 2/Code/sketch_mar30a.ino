
/* The IR sensors arrangment is in order:
       L2    L1    M    R1    R2
       
  L1, M and R1 determine the track.....
  L2 and R2 is used for  sharp turns.
  
 "" I assumed that the IR sensor shows low when detetcting a black surface. ""

*/        
// int number = map(input,0,255,inital scale, final scale); //

//Declaring Pins For IR Inputs//
#define L3 22
#define L2 23
#define L1 24

#define R1 25
#define R2 26
#define R3 27

//UltraSonic Pins
#define trig 5
#define echo 2

//Motor A
#define leftForward 10
#define leftReverse 8
#define pwmLeft 11


//Motor B
#define rightForward 9
#define rightReverse 6
#define pwmRight 12


 /*UltraSonic Readings*/

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
  return(distance);
}

//////////////Move Functions////////////////
namespace Move{
void allStop() {
  digitalWrite(leftForward, LOW);
  digitalWrite(leftReverse, LOW);
  digitalWrite(rightForward, LOW);
  digitalWrite(rightReverse, LOW);
  analogWrite(pwmLeft, 0);
  analogWrite(pwmRight, 0);
}
 
void allForward() {
  digitalWrite(leftForward, HIGH);
  digitalWrite(leftReverse, LOW);
  digitalWrite(rightForward, HIGH);
  digitalWrite(rightReverse, LOW);
  analogWrite(pwmLeft, 255);
  analogWrite(pwmRight, 255);
}
 
void allReverse() {
  digitalWrite(leftForward, LOW);
  digitalWrite(leftReverse, HIGH);
  digitalWrite(rightForward, LOW);
  digitalWrite(rightReverse, HIGH);
  analogWrite(pwmLeft, 255);
  analogWrite(pwmRight, 255);
}
 
void steerLeft() {
  analogWrite(leftReverse, 80);
  digitalWrite(leftForward, LOW);
  analogWrite(rightForward, 120);
  digitalWrite(rightReverse, LOW);
  analogWrite(pwmLeft, 255);
  analogWrite(pwmRight, 255);
}
void steer90Left() {
  digitalWrite(leftReverse, LOW);
  digitalWrite(leftForward, LOW);
  analogWrite(rightForward, 120);
  digitalWrite(rightReverse, LOW);
  analogWrite(pwmLeft, 255);
  analogWrite(pwmRight, 255);
}

void sharpLeft() {
  digitalWrite(leftForward, LOW);
  analogWrite(leftReverse, 70);
  analogWrite(rightForward, 70);
  digitalWrite(rightReverse, LOW);
  analogWrite(pwmLeft, 255);
  analogWrite(pwmRight, 255);
}
 
void steerRight() {
  analogWrite(leftForward, 120);
  digitalWrite(rightForward, LOW);
  analogWrite(leftReverse, 80);
  digitalWrite(rightReverse, LOW);
  analogWrite(pwmLeft, 255);
  analogWrite(pwmRight, 255);
}
void steer90Right() {
  analogWrite(leftForward, 120);
  digitalWrite(rightForward, LOW);
  digitalWrite(leftReverse, LOW);
  digitalWrite(rightReverse, LOW);
  analogWrite(pwmLeft, 255);
  analogWrite(pwmRight, 255);
}
void sharpRight()
{
  analogWrite(leftForward, 70);
  digitalWrite(leftReverse, LOW);
  digitalWrite(rightForward, LOW);
  analogWrite(rightReverse, 70);
  analogWrite(pwmLeft, 255);
  analogWrite(pwmRight, 255);
}
void Speed(int value)
{
int x = map(value , 0 , 100 , 0 , 255);
analogWrite(pwmRight , x);
analogWrite(pwmLeft , x);
}

}
void setup()
{
  Serial.begin(9600);

  /*For UltraSonic*/
  pinMode (trig ,OUTPUT);
  pinMode (echo,INPUT );

 /*For IR Sensors*/
 pinMode(L1,INPUT);
 pinMode(L2,INPUT);
 pinMode(L3,INPUT);
 pinMode(R1,INPUT);
 pinMode(R2,INPUT);
 pinMode(R3,INPUT);

 /*Motor A*/
 pinMode(leftForward,OUTPUT);
 pinMode(leftReverse,OUTPUT);
 pinMode(pwmLeft,OUTPUT);

 /*Motor B*/
 pinMode(rightForward,OUTPUT);
 pinMode(rightReverse,OUTPUT);
 pinMode(pwmRight,OUTPUT);

}


/*
bool On_Line(int Right,int Left,int Middle)
{ 
if(Right == HIGH && Left == HIGH && Middle == LOW)
    return(true);  
    else
    return(false);  
}
*/

void loop()
{
    int val;
  if (Serial.available() > 0)
  {
    //take action when a byte is received
      val= Serial.read(); // read the byte
  } 

 /*If WHITE GROUND READINGS FROM IR SENSORS, THE CAR OBEYS YOUR BLUETOOTH CONTROLS*/
 /*(digitalRead(L1)==HIGH)&&(digitalRead(L2)==HIGH)&&(digitalRead(R1)==HIGH)&&(digitalRead(R2)==HIGH)&&(digitalRead(M)==HIGH)*/
 if(val=='x')
 {
  
  Move::allStop();

  /*Print Readings From Ultrasonic*/
  Serial.print(USReadings());
  Serial.print("\t");
  
  if(USReadings() > 30)
  {
    
  if(val=='F')
  { Move::allForward(); }
  
    else if(val=='P')
  { Move::allReverse(); }
  
    else if(val=='R')
  { Move::steerRight(); }
  
   else if(val=='L')
  { Move::steerLeft(); }

  else if( 0 <= val && val <= 100) 
  {
    { Move::Speed(val); }
  }

  else
  Move::steerRight(); 
  }
 }

 else if(val == 'X')
 {
  if(USReadings()>30)
  {
       if(digitalRead(L3)==HIGH && digitalRead(L2)==HIGH && digitalRead(L1)==HIGH && digitalRead(R1)==HIGH && digitalRead(R2)==HIGH && digitalRead(R3)==HIGH)
       {
        Move::allForward();
       }
       else if(digitalRead(L3)==LOW && digitalRead(L2)==HIGH && digitalRead(L1)==HIGH && digitalRead(R1)==HIGH && digitalRead(R2)==HIGH && digitalRead(R3)==LOW)
       {
        Move::allForward();
       }
       else if(digitalRead(L3)==LOW && digitalRead(L2)==LOW && digitalRead(L1)==LOW && digitalRead(R1)==LOW && digitalRead(R2)==LOW && digitalRead(R3)==LOW)
       {
        Move::allForward();
       }
       else if(digitalRead(L3)==HIGH && digitalRead(L2)==HIGH && digitalRead(L1)==LOW && digitalRead(R1)==HIGH && digitalRead(R2)==HIGH && digitalRead(R3)==HIGH)
        {
          Move::sharpLeft();
        }
       else if(digitalRead(L3)==HIGH && digitalRead(L2)==HIGH && digitalRead(L1)==HIGH && digitalRead(R1)==LOW && digitalRead(R2)==HIGH && digitalRead(R3)==HIGH)
        {
          Move::sharpRight();
        }
       else if(digitalRead(L3)==HIGH && digitalRead(L2)==HIGH && digitalRead(L1)==LOW && digitalRead(R1)==LOW && digitalRead(R2)==HIGH && digitalRead(R3)==HIGH)
        {
          Move::allForward();
        }
        else if(digitalRead(L3)==HIGH && digitalRead(L2)==LOW && digitalRead(L1)==LOW && digitalRead(R1)==LOW && digitalRead(R2)==LOW && digitalRead(R3)==HIGH)          
        {
          Move::allForward();
        }
        else if(digitalRead(L3)==LOW && digitalRead(L2)==LOW && digitalRead(L1)==LOW && digitalRead(R1)==HIGH && digitalRead(R2)==HIGH && digitalRead(R3)==HIGH)
         {
          Move::steer90Left();
         }
        else if(digitalRead(L3)==HIGH && digitalRead(L2)==HIGH && digitalRead(L1)==HIGH && digitalRead(R1)==LOW && digitalRead(R2)==LOW && digitalRead(R3)==LOW)
         {
          Move::steer90Right(); 
         }
        else if(digitalRead(L3)==HIGH && digitalRead(L2)==HIGH && digitalRead(L1)==HIGH && digitalRead(R1)==LOW && digitalRead(R2)==LOW && digitalRead(R3)==HIGH)
          {
            Move::steerRight();
          }
        else if(digitalRead(L3)==HIGH && digitalRead(L2)==LOW && digitalRead(L1)==LOW && digitalRead(R1)==HIGH && digitalRead(R2)==HIGH && digitalRead(R3)==HIGH)
          {
            Move::steerLeft();         
          }
        else if(digitalRead(L3)==LOW && digitalRead(L2)==HIGH && digitalRead(L1)==LOW && digitalRead(R1)==HIGH && digitalRead(R2)==HIGH && digitalRead(R3)==HIGH)
          {
            Move::sharpLeft();         
          }
        else if(digitalRead(L3)==HIGH && digitalRead(L2)==HIGH && digitalRead(L1)==HIGH && digitalRead(R1)==LOW && digitalRead(R2)==HIGH && digitalRead(R3)==LOW)
          {
            Move::sharpRight();
          }
        else if(digitalRead(L3)==HIGH && digitalRead(L2)==HIGH && digitalRead(L1)==HIGH && digitalRead(R1)==HIGH && digitalRead(R2)==HIGH && digitalRead(R3)==LOW)
          {
            Move::sharpRight();
          }
         else if(digitalRead(L3)==LOW && digitalRead(L2)==HIGH && digitalRead(L1)==HIGH && digitalRead(R1)==HIGH && digitalRead(R2)==HIGH && digitalRead(R3)==HIGH)
          {
            Move::sharpLeft();
          }
         else if(digitalRead(L3)==LOW && digitalRead(L2)==LOW && digitalRead(L1)==HIGH && digitalRead(R1)==HIGH && digitalRead(R2)==HIGH && digitalRead(R3)==HIGH)
          {
            Move::steer90Left();      
          }
         else if(digitalRead(L3)==HIGH && digitalRead(L2)==HIGH && digitalRead(L1)==HIGH && digitalRead(R1)==HIGH && digitalRead(R2)==LOW && digitalRead(R3)==LOW)
          {
            Move::steer90Right();
          }
                 else if(digitalRead(L3)==HIGH && digitalRead(L2)==HIGH && digitalRead(L1)==LOW && digitalRead(R1)==LOW && digitalRead(R2)==LOW && digitalRead(R3)==LOW)
          {
            Move::steer90Right();
          }
         else if(digitalRead(L3)==LOW && digitalRead(L2)==LOW && digitalRead(L1)==LOW && digitalRead(R1)==LOW && digitalRead(R2)==HIGH && digitalRead(R3)==HIGH)
          {
            Move::steer90Left();      
          }
         else if(digitalRead(L3)==LOW && digitalRead(L2)==LOW && digitalRead(L1)==HIGH && digitalRead(R1)==HIGH && digitalRead(R2)==LOW && digitalRead(R3)==LOW)
          {
            Move::allForward();
          }
  }
    else Move::allForward();   
 }
else
    Move::allStop();
  
 delay(50);
}


