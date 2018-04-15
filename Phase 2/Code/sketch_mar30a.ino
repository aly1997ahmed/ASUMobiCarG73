
/* The IR sensors arrangment is in order:
      L3   L2    L1    R1    R2    R3

  L1, M and R1 determine the track.....
  L2 and R2 is used for  sharp turns.

 "" I assumed that the IR sensor shows low when detetcting a black surface. ""

*/
// int number = map(input,0,255,inital scale, final scale); //

//Declaring Pins For IR Inputs//
#define L3 26
#define L2 27
#define L1 28

#define R1 29
#define R2 30
#define R3 31

//UltraSonic Pins
#define trig 5
#define echo 6

//Motor A
#define leftForward 24
#define leftReverse 25
#define pwmLeft 3


//Motor B
#define rightForward 23
#define rightReverse 22
#define pwmRight 2


/*UltraSonic Readings*/

long USReadings()
{
  long duration, distance;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = (duration / 2) * 0.034 ;
  return (distance);
}

//////////////Move Functions////////////////
namespace Move {
void allStop() {
  digitalWrite(leftForward, LOW);
  digitalWrite(leftReverse, LOW);
  digitalWrite(rightForward, LOW);
  digitalWrite(rightReverse, LOW);
  analogWrite(pwmLeft, 0);
  analogWrite(pwmRight, 0);
}

void allForward(int right , int left) {
  digitalWrite(leftForward, HIGH);
  digitalWrite(leftReverse, LOW);
  digitalWrite(rightForward, HIGH);
  digitalWrite(rightReverse, LOW);
  analogWrite(pwmLeft, left);
  analogWrite(pwmRight, right);
}

void allReverse(int right , int left) {
  digitalWrite(leftForward, LOW);
  digitalWrite(leftReverse, HIGH);
  digitalWrite(rightForward, LOW);
  digitalWrite(rightReverse, HIGH);
  analogWrite(pwmLeft, left);
  analogWrite(pwmRight, right);
}

void steerLeft(int right , int left) {
  digitalWrite(leftReverse, HIGH);
  digitalWrite(leftForward, LOW);
  digitalWrite(rightForward, HIGH);
  digitalWrite(rightReverse, LOW);
  analogWrite(pwmLeft, left);
  analogWrite(pwmRight, right);
}
void steer90Left() {
  digitalWrite(leftReverse, LOW);
  digitalWrite(leftForward, LOW);
  analogWrite(rightForward, 120);
  digitalWrite(rightReverse, LOW);
  analogWrite(pwmLeft, 0);
  analogWrite(pwmRight, 255);
}

void sharpLeft() {
  digitalWrite(leftForward, LOW);
  digitalWrite(leftReverse, HIGH);
  digitalWrite(rightForward, HIGH);
  digitalWrite(rightReverse, LOW);
  analogWrite(pwmLeft, 70);
  analogWrite(pwmRight, 70);
}

void steerRight(int right , int left) {
  digitalWrite(leftForward, HIGH);
  digitalWrite(rightForward, LOW);
  digitalWrite(leftReverse, LOW);
  digitalWrite(rightReverse, HIGH);
  analogWrite(pwmLeft, left);
  analogWrite(pwmRight, right);
}
void steer90Right() {
  digitalWrite(leftForward, HIGH);
  digitalWrite(rightForward, LOW);
  digitalWrite(leftReverse, LOW);
  digitalWrite(rightReverse, LOW);
  analogWrite(pwmLeft, 120);
  analogWrite(pwmRight, 0);
}
void sharpRight()
{
  digitalWrite(leftForward, HIGH);
  digitalWrite(leftReverse, LOW);
  digitalWrite(rightForward, LOW);
  digitalWrite(rightReverse, HIGH);
  analogWrite(pwmLeft, 70);
  analogWrite(pwmRight, 70);
}
int Speed(int value)
{
  int x = map(value , 0 , 10 , 0 , 255);
  return (x);
}

}
void setup()
{
  Serial.begin(9600);

  /*For UltraSonic*/
  pinMode (trig , OUTPUT);
  pinMode (echo, INPUT );

  /*For IR Sensors*/
  pinMode(L1, INPUT);
  pinMode(L2, INPUT);
  pinMode(L3, INPUT);
  pinMode(R1, INPUT);
  pinMode(R2, INPUT);
  pinMode(R3, INPUT);

  /*Motor A*/
  pinMode(leftForward, OUTPUT);
  pinMode(leftReverse, OUTPUT);
  pinMode(pwmLeft, OUTPUT);

  /*Motor B*/
  pinMode(rightForward, OUTPUT);
  pinMode(rightReverse, OUTPUT);
  pinMode(pwmRight, OUTPUT);

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

int val;
int left = 255 ;
int right = 255;
void loop()
{

  if (Serial.available() > 0)
  {
    //take action when a byte is received
    val = Serial.read(); // read the byte
    Serial.println(val);

    switch (val)
    {
      case 'F':
        Move::allForward(right, left);
        break;
      case 'B':
        Move::allReverse(right, left);
        break;
      case 'L':
        Move::steerLeft(right, left);
        break;
      case 'R':
        Move::steerRight(right, left);
        break;
      case 'S':
        Move::allStop();
        break;

      /*Print Readings From Ultrasonic*/
      /*Serial.print(USReadings());*/

      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        right =  Move::Speed(val); left =  Move::Speed(val); break;
      case 'q': right =  Move::Speed(10); left =  Move::Speed(10); break;

      //////////////////////////////////////////////////////////////////*LINE FOLLOWER*/////////////////////////////////////////////////////////////////////////////////////////
      case 'X':

        while (1)

        {
          val = Serial.read();
          if (val == 'x')
          {
            break;
          }

          if (digitalRead(L3) == HIGH && digitalRead(L2) == HIGH && digitalRead(L1) == HIGH && digitalRead(R1) == HIGH && digitalRead(R2) == HIGH && digitalRead(R3) == HIGH)
          {
            Move::allForward(255, 255);  Serial.println("all high");
          }
          if (digitalRead(L3) == LOW && digitalRead(L2) == HIGH && digitalRead(L1) == HIGH && digitalRead(R1) == HIGH && digitalRead(R2) == HIGH && digitalRead(R3) == LOW)
          {
            Move::allForward(255, 255);
          }
          if (digitalRead(L3) == LOW && digitalRead(L2) == LOW && digitalRead(L1) == LOW && digitalRead(R1) == LOW && digitalRead(R2) == LOW && digitalRead(R3) == LOW)
          {
            Move::allForward(255, 255);   Serial.println("all low");
          }
          if (digitalRead(L3) == HIGH && digitalRead(L2) == HIGH && digitalRead(L1) == LOW && digitalRead(R1) == HIGH && digitalRead(R2) == HIGH && digitalRead(R3) == HIGH)
          {
            Move::sharpLeft();
          }
          if (digitalRead(L3) == HIGH && digitalRead(L2) == HIGH && digitalRead(L1) == HIGH && digitalRead(R1) == LOW && digitalRead(R2) == HIGH && digitalRead(R3) == HIGH)
          {
            Move::sharpRight();
          }
          if (digitalRead(L3) == HIGH && digitalRead(L2) == HIGH && digitalRead(L1) == LOW && digitalRead(R1) == LOW && digitalRead(R2) == HIGH && digitalRead(R3) == HIGH)
          {
            Move::allForward(255, 255);
          }
          if (digitalRead(L3) == HIGH && digitalRead(L2) == LOW && digitalRead(L1) == LOW && digitalRead(R1) == LOW && digitalRead(R2) == LOW && digitalRead(R3) == HIGH)
          {
            Move::allForward(255, 255);
          }
          if (digitalRead(L3) == LOW && digitalRead(L2) == LOW && digitalRead(L1) == LOW && digitalRead(R1) == HIGH && digitalRead(R2) == HIGH && digitalRead(R3) == HIGH)
          {
            Move::steer90Left();
          }
          if (digitalRead(L3) == HIGH && digitalRead(L2) == HIGH && digitalRead(L1) == HIGH && digitalRead(R1) == LOW && digitalRead(R2) == LOW && digitalRead(R3) == LOW)
          {
            Move::steer90Right();
          }
          if (digitalRead(L3) == HIGH && digitalRead(L2) == HIGH && digitalRead(L1) == HIGH && digitalRead(R1) == LOW && digitalRead(R2) == LOW && digitalRead(R3) == HIGH)
          {
            Move::steerRight(120, 80);
          }
          if (digitalRead(L3) == HIGH && digitalRead(L2) == LOW && digitalRead(L1) == LOW && digitalRead(R1) == HIGH && digitalRead(R2) == HIGH && digitalRead(R3) == HIGH)
          {
            Move::steerLeft(82, 120);
          }
          if (digitalRead(L3) == LOW && digitalRead(L2) == HIGH && digitalRead(L1) == LOW && digitalRead(R1) == HIGH && digitalRead(R2) == HIGH && digitalRead(R3) == HIGH)
          {
            Move::sharpLeft();
          }
          if (digitalRead(L3) == HIGH && digitalRead(L2) == HIGH && digitalRead(L1) == HIGH && digitalRead(R1) == LOW && digitalRead(R2) == HIGH && digitalRead(R3) == LOW)
          {
            Move::sharpRight();
          }
          if (digitalRead(L3) == HIGH && digitalRead(L2) == HIGH && digitalRead(L1) == HIGH && digitalRead(R1) == HIGH && digitalRead(R2) == HIGH && digitalRead(R3) == LOW)
          {
            Move::sharpRight();
          }
          if (digitalRead(L3) == LOW && digitalRead(L2) == HIGH && digitalRead(L1) == HIGH && digitalRead(R1) == HIGH && digitalRead(R2) == HIGH && digitalRead(R3) == HIGH)
          {
            Move::sharpLeft();
          }
          else if (digitalRead(L3) == LOW && digitalRead(L2) == LOW && digitalRead(L1) == HIGH && digitalRead(R1) == HIGH && digitalRead(R2) == HIGH && digitalRead(R3) == HIGH)
          {
            Move::steer90Left();
          }
          if (digitalRead(L3) == HIGH && digitalRead(L2) == HIGH && digitalRead(L1) == HIGH && digitalRead(R1) == HIGH && digitalRead(R2) == LOW && digitalRead(R3) == LOW)
          {
            Move::steer90Right();
          }
          if (digitalRead(L3) == HIGH && digitalRead(L2) == HIGH && digitalRead(L1) == LOW && digitalRead(R1) == LOW && digitalRead(R2) == LOW && digitalRead(R3) == LOW)
          {
            Move::steer90Right();
          }
          if (digitalRead(L3) == LOW && digitalRead(L2) == LOW && digitalRead(L1) == LOW && digitalRead(R1) == LOW && digitalRead(R2) == HIGH && digitalRead(R3) == HIGH)
          {
            Move::steer90Left();
          }
          if (digitalRead(L3) == LOW && digitalRead(L2) == LOW && digitalRead(L1) == HIGH && digitalRead(R1) == HIGH && digitalRead(R2) == LOW && digitalRead(R3) == LOW)
          {
            Move::allForward(255, 255);
          }

          else Move::allStop();
        }
        break;
    }


  }
}




