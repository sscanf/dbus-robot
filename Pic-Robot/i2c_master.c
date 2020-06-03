#include "i2c_master.h"

#include <pic18fregs.h>

#ifdef DEBUG
#include <stdio.h>
#endif

  /* TODO:
    - no nack is generated in i2c_readstr
  */

void i2c_open(unsigned char mode, unsigned char slew, unsigned char addr_brd) {
  SSPSTAT &= 0x3f;
  SSPCON1 = 0;
  SSPCON2 = 0;
  SSPCON1 |= mode;
  SSPSTAT |= slew;

#if defined(pic18f2455) || defined (pic18f2550) \
|| defined(pic18f4455) || defined (pic18f4550)
  TRISBbits.TRISB1 = 1;
  TRISBbits.TRISB0 = 1;
#elif defined(pic18f2220) || defined(pic18f2320) \
|| defined(piv18f4220) || defined(pic18f4320)
  TRISCbits.TRISC4 = 1;
  TRISCbits.TRISC3 = 1;
#else                                 /* all other devices */
  TRISCbits.TRISC3 = 1;
  TRISCbits.TRISC2 = 1;
#endif

  SSPADD = addr_brd;

  SSPCON1 |= 0x20;
}


void i2c_start(void) {
  PIR1bits.SSPIF = 0;
  SSPCON2bits.SEN = 1;
  i2c_wait();
}


void i2c_stop(void) {
  PIR1bits.SSPIF = 0;
  SSPCON2bits.PEN = 1;
  i2c_wait();
}


void i2c_restart(void) {
  SSPCON2bits.RSEN = 1;
  i2c_wait();
}


void i2c_ack(void) {
  SSPCON2bits.ACKDT = 0;
  SSPCON2bits.ACKEN = 1;
  i2c_wait();
}

void i2c_nack(void) {
  SSPCON2bits.ACKDT = 1;
  SSPCON2bits.ACKEN = 1;
  i2c_wait();
}


void i2c_wait(void) {
  while (!PIR1bits.SSPIF) ;
  PIR1bits.SSPIF = 0;
}


unsigned char i2c_readchar(void) {
  SSPCON2bits.RCEN = 1;		// Enable receive
  i2c_wait();
  return SSPBUF;
}


  /*
   */
char i2c_readstr(unsigned char *ptr, unsigned char len) {
  unsigned char count=0;
  while( len-- ) {
#ifdef DEBUG
    printf("i2c_readstr len: 0x%x",len);
#endif
    *ptr = i2c_readchar();
 #ifdef DEBUG
    printf("read 0x%x \r\n", *ptr);
#endif
    if (len) i2c_ack();
    ptr++;
    count++;
  }
  return count;
}


  /**
  writes one byte to i2c bus and waits until it was send
  @param dat Byte to send
  Note: No Start/Stop bit is generated
  **/
char i2c_writechar(unsigned char dat) {
  SSPBUF = dat;
  i2c_wait();
  return 0;
}


char i2c_writestr(unsigned char *ptr, unsigned char len) {
  while( len-- ) {                      // now send out the string
#ifdef DEBUG
    printf("do write chr 0x%x",*ptr);
#endif
    i2c_writechar(*ptr);
#ifdef DEBUG
    printf(" -> char written \r\n");
#endif
    ptr++;
  }
  return 0;
}
