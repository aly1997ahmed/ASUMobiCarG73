//Motor A
#define leftForward 24
#define leftReverse 25
#define pwmLeft 2
const byte motorA =18;
unsigned int counter1 =0;

//Motor B
#define rightForward 23
#define rightReverse 22
#define pwmRight 3
const byte motorB =19;
unsigned int counter2 =0;


int counts =0;

void FORWARD()
{
  digitalWrite(leftForward , HIGH );
  digitalWrite(leftReverse,LOW);
  digitalWrite(rightForward , HIGH );
  digitalWrite(rightReverse,LOW);
  SPEED(100,100);
}

void FORWARD_FIXED()
{
   counts=NoOfCountsFromDis(200);
               while (1)
                {
                    if (counter1 >= counts && counter2 >=counts )
                        {
                           STOP();
                           break ;
                        }
                     else 
                        {
                          FORWARD();   
                        }
                }
                counter1=0;
                counter2=0;
}

void REVERSE()
{
  digitalWrite(leftForward , LOW);
  digitalWrite(leftReverse,HIGH);
  digitalWrite(rightForward , LOW );
  digitalWrite(rightReverse,HIGH);
  SPEED(100,100);
}

void RIGHT()
{
  digitalWrite(leftForward , LOW );
  digitalWrite(leftReverse,HIGH);
  digitalWrite(rightForward , HIGH );
  digitalWrite(rightReverse,LOW);
  SPEED(100,100);
}

void RIGHT_FIXED()
{
  counts=NoOfCountsFromAngle(90);
  while (1)
  { 
    if (counter1 >=counts && counter2 >=counts )
    {
      STOP();
      break ;
    }
    else 
    {
      RIGHT();  
    }
  }
  counter1=0;
  counter2=0;  
}

void LEFT()
{
  digitalWrite(leftForward , HIGH );
  digitalWrite(leftReverse,LOW);
  digitalWrite(rightForward , LOW );
  digitalWrite(rightReverse,HIGH);
  SPEED(100,100);
}

void STOP()
{
  digitalWrite(leftForward , LOW );
  digitalWrite(leftReverse,LOW);
  digitalWrite(rightForward , LOW );
  digitalWrite(rightReverse,LOW);
  SPEED(0,0);
}
void SPEED(int s1,int s2)
{
  s1=map (s1,0,100,0,255);
  s2=map(s2,0,100,0,255);
  analogWrite(pwmLeft,s1);
  analogWrite(pwmRight,s2);
}

int wheeldiameter=6.3 ;  //cm
float elmo7et=wheeldiameter*3.14;
float slots =20;
int result1=0;
int NoOfCountsFromDis(float distance)
{
  result1 = (slots*distance)/elmo7et;
  return result1 ;
} 

int result2=0;
int NoOfCountsFromAngle(int angle)
{
  result2=(elmo7et*angle)/360;
  return result2;
}


void ISR_COUNT1()
{
 counter1 ++;
}

void ISR_COUNT2()
{
  counter2 ++;
}


void setup()
{
  Serial.begin(9600);
  /*Motor A*/
  pinMode(leftForward, OUTPUT);
  pinMode(leftReverse, OUTPUT);
  pinMode(pwmLeft,OUTPUT );
  pinMode(motorA ,INPUT);
  /*Motor B*/
  pinMode(rightForward, OUTPUT);
  pinMode(rightReverse, OUTPUT);
  pinMode(pwmRight,OUTPUT );
  pinMode(motorB ,INPUT ); 
  attachInterrupt(digitalPinToInterrupt (motorA), ISR_COUNT1, RISING); 
  attachInterrupt(digitalPinToInterrupt (motorB), ISR_COUNT2, RISING);  
}


void loop() 
{
float distance =0;
int angle =0;
 while(1)
 {
  int directions=Serial.read();
  switch (directions)
  {
    case 'F' :Serial.println("Enter the distance");
              while (1)
              {
                distance=Serial.read();
                if ( distance > 0)
                break;
              }
               counts=NoOfCountsFromDis(distance);
               while (1)
                {
                    if (counter1 >= counts && counter2 >=counts )
                        {
                           STOP();
                           break ;
                        }
                     else 
                        {
                          FORWARD();   
                        }
                }
                counter1=0;
                counter2=0;
                break;
     case 'B' : Serial.println("Enter the distance");
                while (1)
                 {
                   distance=Serial.read();
                   if ( distance > 0)
                   break;
                 }
                counts=NoOfCountsFromDis(distance);
                while (1)
                {
                    if (counter1 >=counts && counter2 >=counts )
                        {
                           STOP();
                           break ;
                        }
                     else 
                        {
                          REVERSE();   
                        }
                }
                counter1=0;
                counter2=0;
                break;
      case 'R' :   Serial.println("Enter the angle");
                   while (1)
                    {
                      angle=Serial.read();
                      if ( angle > 0)
                      break;
                    }
                   counts=NoOfCountsFromAngle(angle);
                   while (1)
                     {
                       if (counter1 >=counts && counter2 >=counts )
                        {
                           STOP();
                           break ;
                        }
                       else 
                        {
                          RIGHT();   
                        }
                     }
                     counter1=0;
                     counter2=0;
                     break;      
      case 'L' :   Serial.println("Enter the angle");
                    while (1)
                     {
                       angle=Serial.read();
                       if ( angle > 0)
                       break;
                     }
                   counts=NoOfCountsFromAngle(angle);
                   while (1)
                     {
                       if (counter1 >=counts && counter2 >=counts )
                        {
                           STOP();
                           break ;
                        }
                       else 
                        {
                          LEFT();   
                        }
                     }
                     counter1=0;
                     counter2=0;
                     break; 
     case 'D' :   FORWARD_FIXED();
                   delay (100);
                   RIGHT_FIXED();
                   delay(100);
                   FORWARD_FIXED();
                   delay (100);
                   RIGHT_FIXED();
                   delay (100);
                   FORWARD_FIXED();
                   delay(100);
                   RIGHT_FIXED();
                   delay(100);
                   FORWARD_FIXED();
                   delay(100);
                   RIGHT_FIXED();
                   break;                                     
 }
}
}

