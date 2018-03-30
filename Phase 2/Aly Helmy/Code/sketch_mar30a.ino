
/* The IR sensors arrangment is in order:
       L2    L1    M    R1    R2
       
  L1, M and R1 determine the track.....
  L2 and R2 is used for  sharp turns.
  
 "" I assumed that the IR sensor shows low when detetcting a black surface. ""

*/        


//Declaring Pins For IR Inputs//
#define L2 8
#define L1 7
#define M 5
#define R1 4
#define R2 3

//UltraSonic Pins
#define trig 22
#define echo 2

//Motor A
#define leftForward 11
#define leftReverse 9
#define pwmLeft 12


//Motor B
#define rightForward 10
#define rightReverse 6
#define pwmRight 13


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
  analogWrite(leftReverse, 30);
  digitalWrite(leftForward, LOW);
  analogWrite(rightForward, 110);
  digitalWrite(rightReverse, LOW);
  analogWrite(pwmLeft, 255);
  analogWrite(pwmRight, 255);
}
void sharpLeft() {
  digitalWrite(leftForward, LOW);
  analogWrite(leftReverse, 20);
  analogWrite(rightForward, 40);
  digitalWrite(rightReverse, LOW);
  analogWrite(pwmLeft, 255);
  analogWrite(pwmRight, 255);
}
 
void steerRight() {
  analogWrite(leftForward, 110);
  digitalWrite(rightForward, LOW);
  analogWrite(leftReverse, 30);
  digitalWrite(rightReverse, LOW);
  analogWrite(pwmLeft, 255);
  analogWrite(pwmRight, 255);
}
void sharpRight() {
  analogWrite(leftForward, 40);
  digitalWrite(leftReverse, LOW);
  digitalWrite(rightForward, LOW);
  analogWrite(rightReverse, 20);
  analogWrite(pwmLeft, 255);
  analogWrite(pwmRight, 255);
}
}
void setup()
{
  Serial.begin(9600);

  /*For UltraSonic*/
  pinMode (trig ,OUTPUT);
  pinMode (echo,INPUT );

 /*For IR Sensors*/
 pinMode(L2,INPUT);
 pinMode(L1,INPUT);
 pinMode(M,INPUT);
 pinMode(R2,INPUT);
 pinMode(R1,INPUT);

 /*Motor A*/
 pinMode(leftForward,OUTPUT);
 pinMode(leftReverse,OUTPUT);
 pinMode(pwmLeft,OUTPUT);

 /*Motor B*/
 pinMode(rightForward,OUTPUT);
 pinMode(rightReverse,OUTPUT);
 pinMode(pwmRight,OUTPUT);

}

/*bool On_Line(digitalRead(R1),digitalRead(L1),digitalRead(M))*/
bool On_Line(int Right,int Left,int Middle)
{ 
if(Right == HIGH && Left == HIGH && Middle == LOW)
    return(true);  
else
    return(false);  
}

void loop()
{

 /*If WHITE GROUND READINGS FROM IR SENSORS, THE CAR OBEYS YOUR BLUETOOTH CONTROLS*/
 if((digitalRead(L1)==HIGH)&&(digitalRead(L2)==HIGH)&&(digitalRead(R1)==HIGH)&&(digitalRead(R2)==HIGH)&&(digitalRead(M)==HIGH))
 {
  
  Move::allStop();
  int val;
  if (Serial.available() > 0)
  {
    //take action when a byte is received
      val= Serial.read(); // read the byte
  } 

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
  
  }
  else
  Move::steerRight(); 
 }
  

 else{
       //A black horizontal Line car Stops
       if((digitalRead(L1)==LOW)&&(digitalRead(R1)==LOW))
       {
        
          Move::allStop();
       }
      
       //Move forward
       else if((digitalRead(L1)==HIGH)&&(digitalRead(L2)==HIGH)&&(digitalRead(R1)==HIGH)&&(digitalRead(R2)==HIGH)&&(digitalRead(M)==LOW))
       {

          Move::allForward(); 
                    
       }
      
       //left turn
       else if(digitalRead(L1)==LOW && digitalRead(L2)==HIGH&&(digitalRead(R1)==HIGH)&&(digitalRead(R2)==HIGH)&&(digitalRead(M)==HIGH))
       {
          for(;;)
          {
          Move::steerLeft();
          if(On_Line(digitalRead(R1),digitalRead(L1),digitalRead(M)))
          {break;}
          }
          
       }

       //right turn
       else if(digitalRead(R1)==LOW && digitalRead(R2)==HIGH&&(digitalRead(L1)==HIGH)&&(digitalRead(L2)==HIGH)&&(digitalRead(M)==HIGH))
       {
          for(;;)
          {
          Move::steerRight();
          
          if(On_Line(digitalRead(R1),digitalRead(L1),digitalRead(M)))
          {break;}
          }
       }
       
       //Very sharp left turn
       else if(digitalRead(L2)==LOW && digitalRead(R1)==HIGH &&(digitalRead(R2)==HIGH)&&(digitalRead(M)==LOW))
       {
          for(;;)
          {
          Move::sharpLeft();
          
          if(On_Line(digitalRead(R1),digitalRead(L1),digitalRead(M)))
          {break;}  
          }
       }
  
       //Very sharp right turn
       else if(digitalRead(R2)==LOW &&(digitalRead(L1)==HIGH)&&(digitalRead(L2)==HIGH)&&(digitalRead(M)==LOW))
       {
           for(;;)
           {
           Move::sharpRight();
           
           if(On_Line(digitalRead(R1),digitalRead(L1),digitalRead(M)))
           {break;}   
           }    
       }
       
 }

  
 delay(50);
}


