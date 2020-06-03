/*
Delay routines designed for Hi-Tech C v8.12PL1 and PIC18Cxxx or PIC18Fxxx.

These routines are written in assembler and thus give *precise* timing.

To use the delay routines, add 'delay.c' as a node to your project in MPLab, and 
the line #include "delay.h" in your project.

Alternatively, you can simply add the line #include "delay.c" to your project.

Regards,
Shane Tolmie
http://www.microchipC.com/
*/

//see readme.txt
#include <pic18.h>
#include "always.h"

#include "delay.h" 
#include "clk_freq.h" //make sure that PIC_CLK in this file is correctly defined

main()
{
  //unsigned int timeout_int;
  //unsigned char timeout_char;

  //dly250n;      //macro - delay constant 250ns at any clock speed (must uncomment defines in delay.h)
  //dly1u;        //macro - delay constant 1us at any clock speed

  breakpoint;     //see "always.h" - makes it easy to use Windows..Stopwatch to test timing

  DelayUs(40);  //do not do DelayUs(0) or else it bombs :)
  
  DelayUs(255); //delay 255us (this takes an unsigned char argument)
  DelayBigUs(65535); //delay 65,535us (this takes an unsigned integer argument)

  DelayMs(255); //delay 255ms (this takes an unsigned char argument)
  
  DelayBigMs(65535);  //delay 65,535ms (this takes an unsigned integer argument)

  DelayMs_interrupt(254); //if you ever use a delay in an interrupt function, use this one

  DelayS(12); //delay 12 seconds

  //these following functions are useful for timeouts (uncomment to use)
  /*
  timeout_char=timeout_char_us(575);  //at 16Mhz, a value higher than this will generate 'arithmetic overflow'
  while(timeout_char-- && (RA1==0));  //wait up to 1147us for port RA1 to go high - this is the max timeout

  timeout_int=timeout_int_us(262143); //at 16Mhz, a value higher than this will generate 'arithmetic overflow'
  while(timeout_int-- && (RA1==0));   //wait up to 491512us for port RA1 to go high - this is the max timeout
  */
}


