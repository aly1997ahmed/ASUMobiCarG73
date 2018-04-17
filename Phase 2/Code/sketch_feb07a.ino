#define f1 23                                            // motor a
#define b1 22
#define speeda 2

#define f2 24                                           // motor b
#define b2 25
#define speedb 3

#define trig 32                                         //UltraSonic
#define echo 33

int bluetooth_var ;                                     // variables
long US_Distance ; 

int i ;                                                 // counter                   
 
const int L_F_Array[6] = {31,30,29,28,27,26};           //Line Follower
int C_Values = B00000000 ; 

void forward();
void back();
void Stop();
void left();
void right();
void leftS();
void rightS();
void Speed(int s1, int s2);
long Ultra_Sonic_Reading();
void Line_Scanning();
void Line_Tracking();

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
}

void loop() {
 if (Serial.available() > 0)
  {
    bluetooth_var = Serial.read();
    
    switch(bluetooth_var)
    {
      case 'F' : 
          /*US_Distance = Ultra_Sonic_Reading();
          if( US_Distance <= 25 )
             {
                Stop();
                delay(50);
                right();
                delay(500);
                Stop();
                delay(50);
             }
         else*/
         forward(); break;
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

