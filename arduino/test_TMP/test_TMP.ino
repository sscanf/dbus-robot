#include <Wire.h>

#define SLAVE_ADDRESS 0x30
#define TOTAL_SENSORS 3

#define TRIG  7
#define ECHO1 6
#define ECHO2 5
#define ECHO3 4

unsigned long maxloops;

long timesStart[TOTAL_SENSORS];
long timesStop[TOTAL_SENSORS];
int  distances[TOTAL_SENSORS];
uint8_t bits[TOTAL_SENSORS];

void setup()
{
  Wire.begin(SLAVE_ADDRESS);
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(receiveData);
  Serial.begin(9600);
  
  DDRD = 0x80; //All bits as INPUT except TRIG (7)  
  for (int n=0;n<TOTAL_SENSORS;n++) {
    bits[n] = 0x40 >> n;
  }
  maxloops = microsecondsToClockCycles(500);
}

void loop()
{      
  memset (timesStart, 0, sizeof(timesStart));
  memset (timesStop, 0, sizeof(timesStop));
  
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  unsigned long numloops=0;
  uint8_t val;
  uint8_t count=0;
  
  while (count < TOTAL_SENSORS && numloops < maxloops) {
    val= *portInputRegister(digitalPinToPort(ECHO1));
    for (int n=0;n<TOTAL_SENSORS; n++) {
      if ( (val & bits[n]) == LOW ) {
        if ( timesStart[n] == 0) {          
          timesStop[n]=0;
        } else if (timesStop[n] == 0) { 
            timesStop[n]=micros()-timesStart[n];
            count++;          
          }        
      } else if (timesStart[n]==0) {  //HIGH        
          timesStart[n]=micros();
      }
    }
    numloops++;
  };

  Serial.print ("Distance : ");
  for (int n=0; n<TOTAL_SENSORS; n++) {
    distances[n] = (timesStop[n] * 0.034) / 2;
    Serial.print (distances[n]);
    Serial.print (" ");
  }  
  Serial.println (" ");
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
  for (int n=0; n<TOTAL_SENSORS; n++)
    Wire.write (distances[n]);
    
}

void receiveData(int byteCount)
{
}