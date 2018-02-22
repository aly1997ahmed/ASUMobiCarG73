
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
  delay(1000);
  digitalWrite (ledb,HIGH);
  delay(1000);
  digitalWrite (ledc,HIGH);
  delay(1000);
  digitalWrite (ledd,HIGH);
  delay(1000);
  digitalWrite (ledc,HIGH);
  delay(1000);
  digitalWrite (ledb,HIGH);
  delay(1000);
  
 }


