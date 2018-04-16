#define MotorR1 23
#define MotorR2 22
#define MotorL1 24
#define MotorL2 25
#define Speed1  2
#define Speed2  3
#define Trig    6
#define Echo    7
int Motor_Motion;
      float US_Distance(){
        float Time;
        digitalWrite(Trig,LOW);
        delayMicroseconds(2);
        digitalWrite(Trig,HIGH);
        delayMicroseconds(10);
        digitalWrite(Trig,LOW);
        Time = pulseIn(Echo,HIGH);
        return ((Time/2.0)*0.034);
        
        
        }
      void Motor_Speed(int Mspeed){
         int y  = map(Mspeed,0,100,0,255);
         analogWrite(Speed1,y);
         analogWrite(Speed2,y);
        } 
      void Motor_Forward(){
        digitalWrite(MotorR1,HIGH);
        digitalWrite(MotorR2,LOW);
        digitalWrite(MotorL1,HIGH);
        digitalWrite(MotorL2,LOW);
        }
      void Motor_Backward(){
        digitalWrite(MotorR2,HIGH);
        digitalWrite(MotorR1,LOW);
        digitalWrite(MotorL2,HIGH);
        digitalWrite(MotorL1,LOW); 
        }
      void Motor_Left(){
        digitalWrite(MotorR2,HIGH);
        digitalWrite(MotorR1,LOW);
        digitalWrite(MotorL1,HIGH);
        digitalWrite(MotorL2,LOW);
        }
      void Motor_Right(){
        digitalWrite(MotorR1,HIGH);
        digitalWrite(MotorR2,LOW);
        digitalWrite(MotorL2,HIGH);
        digitalWrite(MotorL1,LOW);
        }
      void Motor_Stop(){
        digitalWrite(MotorR1,LOW);
        digitalWrite(MotorR2,LOW);
        digitalWrite(MotorL2,LOW);
        digitalWrite(MotorL1,LOW);
        }        
void setup() {
  // put your setup code here, to run once:
  pinMode(MotorR1,OUTPUT);
  pinMode(MotorR2,OUTPUT);
  pinMode(MotorL1,OUTPUT);
  pinMode(MotorL2,OUTPUT);
  pinMode(Speed1,OUTPUT);
  pinMode(Speed2,OUTPUT);
  pinMode(Trig,OUTPUT);
  pinMode(Echo,INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(Motor_Motion);
  // put your main code here, to run repeatedly
while(Serial.available()){ 
  Motor_Motion = Serial.read();
  

  switch(Motor_Motion){
    case'F': if(US_Distance()>30){ 
    Motor_Forward();  
    }
   else{Motor_Right();
      }   
     break;
    case'B': Motor_Backward(); break;
    case'R': Motor_Right();    break;
    case'L': Motor_Left();     break;
    case'0': Motor_Speed(0);   break;
    case'1': Motor_Speed(10);   break;
    case'2': Motor_Speed(20);   break;
    case'3': Motor_Speed(30);   break; 
    case'4': Motor_Speed(40);   break;
    case'5': Motor_Speed(50);   break;
    case'6': Motor_Speed(60);   break;
    case'7': Motor_Speed(70);   break;
    case'8': Motor_Speed(80);   break;
    case'9': Motor_Speed(90);   break;
    case'q': Motor_Speed(100);  break;
    default: Motor_Stop();       
    }
    Motor_Motion = 0 ;
    
  }
}
