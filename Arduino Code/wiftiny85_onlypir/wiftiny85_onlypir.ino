/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 0;
int pir = 2;
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);  
  pinMode(pir, INPUT);  
}

// the loop routine runs over and over again forever:
void loop() {
  int pir_status ;
  pir_status=digitalRead(pir);
  if(pir_status==1)
  {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000); 
  } 
  else if(pir_status==0)
  // wait for a second
  {
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000); 
  }  // wait for a second
}
