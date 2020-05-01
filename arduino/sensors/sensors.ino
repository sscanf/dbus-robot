#include <Wire.h>

#define SLAVE_ADDRESS 0x30
#define ECHO  6
#define TRIG  7

long duration;
int distance;

void setup()
{
  Wire.begin(SLAVE_ADDRESS);
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(receiveData);
//  Serial.begin(9600);
  
  pinMode (TRIG,OUTPUT);
  pinMode (ECHO,INPUT);
}

void loop()
{
  digitalWrite (TRIG,LOW);
  delayMicroseconds (2);
  digitalWrite (TRIG,HIGH);
  delayMicroseconds (10);
  digitalWrite (TRIG,LOW);
  
  duration = pulseIn (ECHO, HIGH);
//  pulseIn(ECHO,LOW);
  distance = duration * 0.034 / 2;
//  Serial.print ("Distance: ");
//  Serial.println (distance);
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
  Wire.write (distance);
}

void receiveData(int byteCount)
{
}
