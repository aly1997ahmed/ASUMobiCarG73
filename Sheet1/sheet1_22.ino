
int leda = 4;
int ledb = 5;
int ledc = 6;
int ledd = 7;
int i,j ;

void setup()
{
 pinMode (leda , OUTPUT );
 pinMode (ledb , OUTPUT ); 
 pinMode (ledc , OUTPUT );
 pinMode (ledd , OUTPUT );

}

void loop()
{
  digitalWrite (leda,HIGH);
  digitalWrite (ledb,LOW);
  digitalWrite (ledc,LOW);
  digitalWrite (ledd,LOW);
  delay(1000);
  digitalWrite (ledb,HIGH);
  digitalWrite (leda,LOW);
  digitalWrite (ledc,LOW);
  digitalWrite (ledd,LOW);
  delay(1000);
  digitalWrite (ledc,HIGH);
  digitalWrite (leda,LOW);
  digitalWrite (ledb,LOW);
  digitalWrite (ledd,LOW);
  delay(1000);
  digitalWrite (ledd,HIGH);
  digitalWrite (leda,LOW);
  digitalWrite (ledb,LOW);
  digitalWrite (ledc,LOW);
  delay(1000);
  digitalWrite (ledc,HIGH);
  digitalWrite (leda,LOW);
  digitalWrite (ledb,LOW);
  digitalWrite (ledd,LOW);
  delay(1000);
  digitalWrite (ledb,HIGH);
  digitalWrite (leda,LOW);
  digitalWrite (ledb,LOW);
  digitalWrite (ledc,LOW);
  delay(1000);
  
 }


