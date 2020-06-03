NOTE: these routines will NOT WORK if the project size is too large and Hi-Tech 
C starts to bank the delay variables in a different bank. It it recommended that 
you upgrade to v3 of the delay routines.

Delay and Timeout Routines for PIC18xxxx and Hi-Tech C (www.htsoft.com).

These routines are written in assembler and thus give *precise* timing.

To use the delay routines, add 'delay.c' as a node to your project in MPLab, and 
the line #include "delay.h" in your project.

Alternatively, you can simply add the line #include "delay.c" to your project.

Regards,
Shane Tolmie
http://www.microchipc.com/