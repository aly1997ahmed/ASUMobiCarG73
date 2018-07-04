#define f1 23                                            // motor a
#define b1 22
#define speeda 2

#define f2 24                                           // motor b
#define b2 25
#define speedb 3

#define trig 32                                         //UltraSonic
#define echo 33

#define encoder1 18                                     //encoders
#define encoder2 19
#define wheeldiameter 6.5
#define numberofsteps 20 
#define spacebetweenwheels 17.5

int bluetooth_var ;                                     // variables
long US_Distance ; 

int i ;                                                 // counter                   
 
const int L_F_Array[6] = {31,30,29,28,27,26};           //Line Follower
int C_Values = B00000000 ; 

int counter1;                                           //encoder counters
int counter2;

void forward();
void back();
void Stop();
void left();
void right();
void leftS();
void rightS();
void Speed(int s1, int s2);
long Ultra_Sonic_Reading();
void Ultra_Sonic_Action();
void Line_Scanning();
void Line_Tracking();
void wheel1();
void wheel2();
int CMTOSTEPS(float cm);
int ANGLETOSTEPS(float angle);
void accurate_forward();
void accurate_back();
void accurate_angle_L();
void accurate_angle_R();
void accurate_moving();

void setup() {
  Serial.begin(9600); 
  pinMode(f1,OUTPUT);
  pinMode(f2,OUTPUT);
  pinMode(b1,OUTPUT);
  pinMode(b2,OUTPUT);
  pinMode(trig ,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(speeda,OUTPUT);
  pinMode(speedb,OUTPUT);

  for( i=0 ; i<=5 ; i++)
  {
    pinMode(L_F_Array[i],INPUT);
  }

  attachInterrupt(digitalPinToInterrupt(encoder1),wheel1,RISING);
  attachInterrupt(digitalPinToInterrupt(encoder2),wheel2,RISING);
}

void loop() {
 if (Serial.available() > 0)
  {
    bluetooth_var = Serial.read();
    
    switch(bluetooth_var)
    {
      case 'F' : 
         Ultra_Sonic_Action();
                 break;
      case 'B' : back(); break;
      case 'L' : left(); break;
      case 'R' : right(); break;
      case 'S' : case 'D' : Stop(); break;                       // the same case
      case '0' : Speed(0,0); break;
      case '1' : Speed(10,10); break;
      case '2' : Speed(20,20); break;
      case '3' : Speed(30,30); break;
      case '4' : Speed(40,40); break;
      case '5' : Speed(50,50); break;
      case '6' : Speed(60,60); break;
      case '7' : Speed(70,70); break;
      case '8' : Speed(80,80); break;
      case '9' : Speed(90,90); break;
      case 'q' : Speed(100,100); break;
      case 'X' :
      Stop();
      while(1)
      {
        if(Serial.read() == 'x')
            break;
        else
        Line_Tracking();
      }
	  case 'A' : 
        accurate_moving();
     
      default : Stop();                  // if there`s no signal the car stops 
    }
    bluetooth_var = 0 ;
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
long Ultra_Sonic_Reading()
{
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  long duration = pulseIn(echo,HIGH);
  long distance = (duration/2)*0.034 ; 
  return distance;
}
void Ultra_Sonic_Action()
{
	US_Distance = Ultra_Sonic_Reading();
          if( US_Distance <= 25 )
             {
                Stop();
                delay(50);
                right();
                delay(500);
                Stop();
                delay(50);
             }
             else
             forward();
}
void Line_Scanning()
{
 for(i =0;i<=5;i++)
 {
  bitWrite(C_Values,i,!digitalRead(L_F_Array[i]));
 }
}
void Line_Tracking()
{
  Line_Scanning();
  switch(C_Values)
  {
    case B00000000: Speed(40,40); forward();     break; 
    case B00100000: Speed(60,60); left();        break;
    case B00010000: Speed(60,60);  left();        break;
    case B00001000: Speed(60,60);  left();        break;
    case B00000100: Speed(60,60); right();       break;
    case B00000010: Speed(60,60);  right();       break;
    case B00000001: Speed(60,60);  right();       break;
    
    case B00110000: Speed(60,60);  left();       break;
    case B00011000: Speed(60,60);  left();       break;
    case B00001100: Speed(40,40); forward();     break;
    case B00000110: Speed(60,60);  right();      break;
    case B00000011: Speed(60,60);  right();      break;
    
    case B00111000:  Speed(60,60);  left();       break;
    case B00011100:  Speed(60,60);  left();       break;
    case B00001110:  Speed(60,60);  right();      break;
    case B00000111:  Speed(60,60);  right();      break;
    
    case B00111100:  Speed(60,60);  left();       break;
    case B00011110:  Speed(40,40); forward();     break;
    case B00001111:  Speed(60,60);  right();      break;
    
    case B00111110:  Speed(60,60);  left();       break;
    case B00011111:  Speed(60,60);  right();      break;
    
    case B00111111: Speed(40,40); forward();     break;

    // extreme cases 
    case B00001101:  Speed(60,60);  right();      break;
    case B00011001:  Speed(60,60);  right();      break;
    case B00100110:  Speed(60,60);  left();       break;
    case B00101100:  Speed(60,60);  left();       break;
    
    case B00101000:  Speed(60,60);  left();       break;
    case B00000101:  Speed(60,60);  right();      break;
    
    default :Speed(40,40); forward();
  }
  }
void wheel1()
{
  while(encoder1 == HIGH);
  counter1++;
}
void wheel2()
{
  while(encoder2 == HIGH);
  counter2++;
}

int CMTOSTEPS(float cm)
{
  int result ;
  float mo7et = (wheeldiameter * 3.14);
  float cm_steps = mo7et /numberofsteps ;
  float resultx = cm/cm_steps ;
  result = (int) resultx ;
  return result ;
}
int ANGLETOSTEPS(float angle)
{
	float resultx ;
	float mo7et = (2* spacebetweenwheels * 3.14);
	float anglex = angle / 360 ;
	anglex = anglex * mo7et ;
	resultx = CMTOSTEPS(anglex)  ;
  int result = (int) resultx ;
	return (result) ;
}
void accurate_forward()
{
  counter1 = 0;
  counter2 = 0;
int distance_cm = 0;
int distance_steps = 0;
Serial.println("enter the distance");
while(1)
{
distance_cm = Serial.parseInt();
if(distance_cm >0)
break;
}
distance_cm = distance_cm * 5;
distance_steps = CMTOSTEPS(distance_cm);
Speed(100,100);
forward();

while(distance_steps >= counter1 && distance_steps >= counter2 )
{
forward();
}
Stop();	
  counter1 = 0;
  counter2 = 0;
}
void accurate_back()
{
  counter1 = 0;
  counter2 = 0;
int distance_cm = 0;
int distance_steps = 0;
Serial.println("enter the distance");
while(1)
{
distance_cm = Serial.parseInt();
if(distance_cm >0)
break;
}
distance_cm = distance_cm * 4.2;
distance_steps = CMTOSTEPS(distance_cm);
Speed(100,100);
back();
while(distance_steps >= counter1 && distance_steps >= counter2 )
{
back();
}	
Stop();
  counter1 = 0;
  counter2 = 0;
}
void accurate_angle_L()
{
  counter1 = 0;
  counter2 = 0;
  int angle_degree = 0;
int distance_steps = 0;
Serial.println("enter the angle");
while(1)
{
angle_degree = Serial.parseInt();
if(angle_degree >0)
break;
}
angle_degree = angle_degree * 1.95;
distance_steps = CMTOSTEPS(angle_degree);
Speed(100,100);
leftS();
while(distance_steps > counter1)
{
leftS();
}	
Stop();
  counter1 = 0;
  counter2 = 0;
}
void accurate_angle_R()
{  
  counter1 = 0;
  counter2 = 0;
int angle_degree = 0;
int distance_steps = 0;
Serial.println("enter the angle") ;
while(1)
{
angle_degree = Serial.parseInt();
if(angle_degree >0)
break;
}
angle_degree = angle_degree * 1.23;
distance_steps = CMTOSTEPS(angle_degree);
Speed(100,100);
rightS();
while(distance_steps > counter2)
{
rightS();
}	
Stop();
  counter1 = 0;
  counter2 = 0;
}
void accurate_forward_Fixed(int x)
{
  counter1 = 0;
  counter2 = 0;
int distance_steps = 0;
x = x* 4.2;
distance_steps = CMTOSTEPS(x);
Speed(100,100);
forward();

while(distance_steps >= counter1 && distance_steps >= counter2 )
{
 Serial.print(distance_steps);   Serial.print("  ");   Serial.print(counter1);   Serial.print("  ");   Serial.print(counter2);   Serial.println("  ");
forward();
}
Stop();	
  counter1 = 0;
  counter2 = 0;
}
void accurate_angle_R_Fixed(int x)
{  
  counter1 = 0;
  counter2 = 0;
int distance_steps = 0;
x = x * 1.33 ;
distance_steps = CMTOSTEPS(x);
Speed(100,100);
rightS();
while(distance_steps > counter2)
{
   Serial.print(distance_steps);   Serial.print("  ");   Serial.print(counter1);   Serial.print("  ");   Serial.print(counter2);   Serial.println("  ");
rightS();
}	
Stop();
  counter1 = 0;
  counter2 = 0;
}
void accurate_angle_L_Fixed(int x)
{  
  counter1 = 0;
  counter2 = 0;
int distance_steps = 0;
x = x * 1.45 ;
distance_steps = CMTOSTEPS(x);
Speed(100,100);
leftS();
while(distance_steps > counter1)
{
   Serial.print(distance_steps);   Serial.print("  ");   Serial.print(counter1);   Serial.print("  ");   Serial.print(counter2);   Serial.println("  ");
leftS();
}  
Stop();
  counter1 = 0;
  counter2 = 0;
}
void demo1()
{
accurate_forward_Fixed(100);
delay(300);
accurate_angle_R_Fixed(90);
delay(300);
accurate_forward_Fixed(100);
delay(300);
accurate_angle_R_Fixed(90);
delay(300);
accurate_forward_Fixed(100);
delay(300);
accurate_angle_R_Fixed(90);
delay(300);
accurate_forward_Fixed(100);
delay(300);
accurate_angle_R_Fixed(90);
}
void demo2()
{
Speed(100,100);
for(i=0 ;i<170;i++)
{
  accurate_forward_Fixed(2.5);
  accurate_angle_R_Fixed(3);
}

Stop();
}
void circle_R()
{
Speed(100,100);
for(i=0 ;i< 62;i++)
{
  accurate_forward_Fixed(2.5);
  accurate_angle_R_Fixed(4);
}
Stop();

}
void circle_L()
{
Speed(100,100);
for(i=0 ;i<62;i++)
{
  accurate_forward_Fixed(2.5);
  accurate_angle_L_Fixed(3);
}
Stop();
}
void demo3()
{
	accurate_forward_Fixed(141);
  delay(200);
	accurate_angle_L_Fixed(45);
 delay(200);
	circle_L();
 delay(200);
  accurate_angle_L_Fixed(45);
  delay(200);
	accurate_forward_Fixed(141);
  delay(200);
	accurate_angle_R_Fixed(90);
 delay(200);
	circle_R();
  Stop();
}
void accurate_moving()
{	
	counter1 = 0;
	counter2 = 0;

	Serial.println("enter the mod (F - B - R - L)");
  bluetooth_var = 0;
  while(1)
  {
    bluetooth_var = Serial.read();
    if(bluetooth_var >0)
    break;
  }
    switch(bluetooth_var)
    {
	 case 'F' : accurate_forward(); break;
	 case 'B' : accurate_back();    break;
	 case 'R' : accurate_angle_R(); break;
	 case 'L' : accurate_angle_L(); break;
  //case 'D' :demo3 ();            break;
   case 'D' : demo1(); delay(2000);  demo2();  delay(2000);  demo3(); break ;
	 default : Stop();
    }
 }
  



