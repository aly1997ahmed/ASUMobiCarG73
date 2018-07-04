
const byte MOTOR_A = 18;
const byte MOTOR_B = 19;


const float stepcount = 20.00;



const float wheeldiameter = 6.610;



volatile int counter_A = 0;
volatile int counter_B = 0;


// Motor A

int enA = 2;
int in1 = 23;
int in2 = 22;

// Motor B

int enB = 3;
int in3 = 24;
int in4 = 25;



// Motor A pulse count ISR
void ISR_countA()
{
  counter_A++;  // increment Motor A counter value
}

// Motor B pulse count ISR
void ISR_countB()
{
  counter_B++;  // increment Motor B counter value
}


int CMtoSteps(float cm) {

  int result;  // Final calculation result
  float circumference = (wheeldiameter * 3.14) ; // Calculate wheel circumference in cm
  float cm_step = circumference / stepcount;  // CM per Step

  float f_result = cm / cm_step;  // Calculate result as a float
  result = (int) f_result; // Convert to an integer (note this is NOT rounded)

  return result;  // End and return result

}

// Function to Move Forward
void MoveForward(int steps)
{
  counter_A = 0;  //  reset counter A to zero
  counter_B = 0;  //  reset counter B to zero

  // Set Motor A forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  // Set Motor B forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  // Go forward until step value is reached
  while (steps > counter_A && steps > counter_B)
  {

    if (steps > counter_A) {
      digitalWrite(enA, HIGH);
    } else {
      digitalWrite(enA, LOW);
    }
    if (steps > counter_B) {
      digitalWrite(enB, HIGH);
    } else {
      digitalWrite(enB, LOW);
    }
  }


  digitalWrite(enA, LOW);
  digitalWrite(enB, LOW);
  counter_A = 0;  //  reset counter A to zero
  counter_B = 0;  //  reset counter B to zero

}

// Function to Move in Reverse
void MoveReverse(int steps)
{
  counter_A = 0;
  counter_B = 0;

  // Set Motor A reverse
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  // Set Motor B reverse
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);


  while (steps > counter_A && steps > counter_B) {

    if (steps > counter_A) {
      digitalWrite(enA, HIGH);
    } else {
      digitalWrite(enA, LOW);
    }
    if (steps > counter_B) {
      digitalWrite(enB, HIGH);
    } else {
      digitalWrite(enB, LOW);
    }
  }


  digitalWrite(enA, LOW);
  digitalWrite(enB, LOW);

  counter_A = 0;
  counter_B = 0;

}

// Function to Spin Right
void SpinRight(int steps )
{
  counter_A = 0;  //  reset counter A to zero
  counter_B = 0;  //  reset counter B to zero

  // Set Motor A reverse
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  // Set Motor B forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  // Go until step value is reached
  while (steps > counter_A && steps > counter_B) {

    if (steps > counter_A) {
      digitalWrite(enA, HIGH);
    } else {
      digitalWrite(enA, LOW);
    }
    if (steps > counter_B) {
      digitalWrite(enB, HIGH);
    } else {
      digitalWrite(enB, LOW);
    }
  }


  digitalWrite(enA, LOW);
  digitalWrite(enB, LOW);

  counter_A = 0;
  counter_B = 0;

}

// Function to Spin Left
void SpinLeft(int steps )
{
  counter_A = 0;  //  reset counter A to zero
  counter_B = 0;  //  reset counter B to zero

  // Set Motor A forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  // Set Motor B reverse
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  // Go until step value is reached
  while (steps > counter_A && steps > counter_B) {

    if (steps > counter_A) {
      digitalWrite(enA, HIGH);
    } else {
      digitalWrite(enA, LOW);
    }
    if (steps > counter_B) {
      digitalWrite(enB, HIGH);
    } else {
      digitalWrite(enB, LOW);
    }
  }


  digitalWrite(enA, LOW);
  digitalWrite(enB, LOW);

  counter_A = 0;
  counter_B = 0;

}

void setup()
{

  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);

  pinMode(in2, OUTPUT);

  pinMode(in3, OUTPUT);

  pinMode(in4, OUTPUT);


  attachInterrupt(digitalPinToInterrupt(18), ISR_countA, RISING);
  attachInterrupt(digitalPinToInterrupt(19), ISR_countB, RISING);



}


void loop()
{


  int directions = 0;

  int value = 0;

    while (!directions)
    {

      directions = Serial.read();

    }


    while (!value)
    {

      value = Serial.read();

    }


    int stepss =  CMtoSteps(value);


    Serial.println("here");
    Serial.println(Serial.read());

    switch (directions)

    {

      case 'f' :  MoveForward(stepss); break ;

      case 's' :  MoveReverse(stepss); break ;

      case 'l' :   SpinLeft(stepss); break ;

      case 'r' :   SpinRight(stepss); break ;

    }

}
