/* Arduino USB HID Keyboard Demo
 * Random Key/Random Delay
 */
#include <Wire.h>
#include "HIDKeyboard.h"
#include "circularbuffer.h"

#define SLAVE_ADDRESS 0x04

HIDKeyboard keyboard;

uint8_t buf[8] = {0};
CircularBuffer<uint8_t, 256> i2cbuffer;

void setup() 
{
  Serial.begin(9600);
  Wire.begin (SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
}

void sendKey (uint8_t keyval, uint8_t modifier, uint8_t fix)
{
    keyboard.pressKey(modifier,keyval);
    delay(50);
    if (fix == 0)
      keyboard.releaseKey();    
}

void sendSpecialKey (uint8_t keyval, uint8_t modifier, uint8_t fix)
{  
    keyboard.pressSpecialKey(modifier,keyval);
    delay(50);
    if (fix == 0)
      keyboard.releaseKey();    
}

void loop() 
{
  while (i2cbuffer.remain()) {
    uint8_t func    = i2cbuffer.pop();
    uint8_t keyval  = i2cbuffer.pop();
    uint8_t modifier= i2cbuffer.pop();
    uint8_t fix     = i2cbuffer.pop();
    
    switch (func) {
      case 0:
        sendKey (keyval, modifier, fix);
      break;
      
      case 1:
        sendSpecialKey (keyval,modifier,fix);
      break;
      
      case 2:
         keyboard.releaseKey();
      break;
    }
  }
}

void releaseKey() 
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8);	// Release key  
}

void receiveData (int byteCount)
{
  while (Wire.available()) {
    i2cbuffer.push (Wire.read());
  }
}

void sendData() 
{
}

