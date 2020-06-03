
#include <pic18fregs.h>
#include <stdio.h>
#include "motores.h"
#include <string.h>
#include "common.h"
#include "delay.h"

#define BIN(x)                              \
  (  ((0x##x##L & 0x00000001L) ? 0x01 : 0)  \
   | ((0x##x##L & 0x00000010L) ? 0x02 : 0)  \
   | ((0x##x##L & 0x00000100L) ? 0x04 : 0)  \
   | ((0x##x##L & 0x00001000L) ? 0x08 : 0)  \
   | ((0x##x##L & 0x00010000L) ? 0x10 : 0)  \
   | ((0x##x##L & 0x00100000L) ? 0x20 : 0)  \
   | ((0x##x##L & 0x01000000L) ? 0x40 : 0)  \
   | ((0x##x##L & 0x10000000L) ? 0x80 : 0))

void (*current_state)();

unsigned char TimerTimeout;
char bDebug=1;

static struct encoder_t encoder[2];
static char bPidEnabled=TRUE;


int abs(int j)
{
	return (j >= 0) ? j : -j;
}

static void stAveraged(void);

void stSampling(void)
{
	static char enc_states[] = {0,1,-1,0,-1,0,0,1,1,0,0,-1,0,-1,1,0};
	static int width1=0;
	static int width2=0;
	static int enc_position_a=0;
	static int enc_position_b=0;
	static int tiempo=0;

	enc_position_a <<=2;
	enc_position_a |= ((PORTD & 0x0c)>>2);
	width1+=enc_states[ (enc_position_a & 0x0f)];

	enc_position_b <<=2;
	enc_position_b |= (PORTD & 0x03);
	width2+=enc_states[ (enc_position_b & 0x0f)];
		
	if (++tiempo>=120) // 120 milisegundos = 480
	{
/*		if (width1==0 && encoder[MOTOR_1].outSpeed>0)
		{
			encoder[MOTOR_1].time_collision++;
			if (encoder[MOTOR_1].time_collision==30)
			{
				encoder[MOTOR_1].time_collision=0;
				motorInvertDir(MOTOR_1);
			}
		}
		else
			encoder[MOTOR_1].time_collision=0;
					
		if (width2==0 && encoder[MOTOR_2].outSpeed>0)
		{
			encoder[MOTOR_2].time_collision++;
			if (encoder[MOTOR_2].time_collision==30)
			{
				encoder[MOTOR_2].time_collision=0;
				motorInvertDir(MOTOR_2);
			}
		}
		else
			encoder[MOTOR_2].time_collision=0;
*/
		encoder[MOTOR_1].inSpeed=abs(width1);
		encoder[MOTOR_2].inSpeed=abs(width2);
		tiempo=0;
		width1=0;
		width2=0;
		
		current_state=&stAveraged;
	}
	else
		current_state=&stSampling;
}

/* Esperamos a que el motor se pare antes
	de invertir la dirección */
void stWaitForMotor1Bak(void)
{
	if (encoder[MOTOR_1].inSpeed==0)
		motorChangeDir (ATRAS,MOTOR_1);
		
	current_state=&stSampling;
//	encoder[MOTOR_1].inSpeed=0;
}

/* Esperamos a que el motor se pare antes
	de invertir la dirección */
void stWaitForMotor2Bak(void)
{
	if (encoder[MOTOR_2].inSpeed==0)
		motorChangeDir (ATRAS,MOTOR_2);
		
	current_state=&stSampling;
//	encoder[MOTOR_2].inSpeed=0;
}

/* Esperamos a que el motor se pare antes
	de invertir la dirección */
void stWaitForMotor1Forward(void)
{
	if (encoder[MOTOR_1].inSpeed==0)
		motorChangeDir (ADELANTE,MOTOR_1);
		
	current_state=&stSampling;
//	encoder[MOTOR_1].inSpeed=0;
}

/* Esperamos a que el motor se pare antes
	de invertir la dirección */
void stWaitForMotor2Forward(void)
{
	if (encoder[MOTOR_2].inSpeed==0)
		motorChangeDir (ADELANTE,MOTOR_2);
	
	current_state=&stSampling;
//	encoder[MOTOR_2].inSpeed=0;
}

void stAveraged(void)
{
	static int errors1[TOTAL_ERRORS];
	static int errors2[TOTAL_ERRORS];
	static int nErrors=0;
	int outSpeed1, outSpeed2,n,err1,err2;
	int width1;
	int width2;

	width1=encoder[MOTOR_1].inSpeed;
	width2=encoder[MOTOR_2].inSpeed;
	
	outSpeed1=(encoder[MOTOR_1].outSpeed);
	outSpeed2=(encoder[MOTOR_2].outSpeed);

	if  (outSpeed1 < 0 )
	{
		outSpeed1*=-1;
		if (motorDir(MOTOR_1)==ADELANTE)
		{
			CCPR1L=0;
			nErrors=0;
			current_state=&stWaitForMotor1Bak;
			return;
		}
	}
	else if (outSpeed1>0 && motorDir(MOTOR_1)==ATRAS)
	{
		CCPR1L=0;
		nErrors=0;
		current_state=&stWaitForMotor1Forward;
		return;
	}
				
	if  (outSpeed2 < 0 )
	{
		outSpeed2*=-1;
		if (motorDir(MOTOR_2)==ADELANTE)
		{
			CCPR2L=0;
			nErrors=0;
			current_state=&stWaitForMotor2Bak;
			return;
		}
	}
	else if ( outSpeed2>0 && motorDir(MOTOR_2)==ATRAS)
	{
		CCPR2L=0;
		nErrors=0;
		current_state=&stWaitForMotor2Forward;
		return;
	}

	err1 = outSpeed1-width1;
	errors1[nErrors]=err1;

	err2 = outSpeed2-width2;
	errors2[nErrors]=err2;

	if (++nErrors == TOTAL_ERRORS)
	{
		nErrors=0;
		for (n=0;n<TOTAL_ERRORS;n++)
		{
			err1+=errors1[n];
			err2+=errors2[n];
		}

		err1/=TOTAL_ERRORS;
		err2/=TOTAL_ERRORS;

		if (err1<0 && err1<-LIMIT)	err1=-LIMIT;
		if (err2<0 && err2<-LIMIT)	err2=-LIMIT;
		if (err1 > LIMIT)	err1=LIMIT;
		if (err2 > LIMIT)	err2=LIMIT;

		CCPR1L = ( outSpeed1==0 ) ? 0 : CCPR1L+err1;
		CCPR2L = ( outSpeed2==0 ) ? 0 : CCPR2L+err2;
	}
	current_state=&stSampling;
}

void readEncoders(void)
{
	static unsigned char counter=0;  // Increment value of cnt on every interrupt
	//Una muestra cada milisegundo/4
	if (++counter>=TimerTimeout)
	{
		(*current_state)();
		counter=0;
	}
} 

void initializeMotors(void)
{

   ADCON1 |= 0x0F; // Set all I/O pins to digital
   UCFG = 0x14; // Enable pullup resistors; full speed mode
   PORTEbits.RDPU=1;    //Resistencias pull-up en PORTD activas

   MOTOR1_DIR_TRIS=0;   //Bits de direccion motor 1 salidas
   MOTOR1_PWM_TRIS=0;   //Canal PWM motor 1 salidas
   MOTOR1_CHANA_TRIS=1;
   MOTOR1_CHANB_TRIS=1;
   
   MOTOR2_DIR_TRIS=0;   //Bits de direccion motor 2 salidas
   MOTOR2_PWM_TRIS=0;   //Canal PWM motor 2 salidas
   MOTOR2_CHANA_TRIS=1;
   MOTOR2_CHANB_TRIS=1;

   /*
   * PWM registers configuration
   * Fosc = 20000000 Hz
   * Fpwm = 10000.00 Hz (Requested : 10000.00 Hz)
   * Duty Cycle = 100 %
   * Resolution is 10 bits
   * Prescaler is 4
   */
   PR2 = BIN(01111100) ;
//   T2CON = 0b00000101 ;
   T2CON = BIN(00000101);
   CCPR1L = 0;
   CCPR2L = 0;
   CCP1CON = BIN(00111100) ;
   CCP2CON = BIN(00111100) ;
   
   memset (encoder,0,sizeof (encoder)*TOTAL_MOTORES);
   TimerTimeout=1;
   encoder[MOTOR_1].AntChana=MOTOR1_CHANA;
   encoder[MOTOR_2].AntChana=MOTOR2_CHANA;
	
	motorChangeDir (ADELANTE,MOTOR_1);
	motorChangeDir (ADELANTE,MOTOR_2);
	
	current_state=&stSampling;
	printf ("Initialize Motors %x\n\r",(void *)current_state);
}

void setPidEnabled (char enabled)
{
	bPidEnabled = enabled;
}
void motorSpeed (int speed, unsigned char motor)
{
 //  speed&=0x7f;
  encoder[motor].outSpeed=(speed*2);
}

void setMotorsDebug (char debug)
{
	bDebug=debug;
}

unsigned char motorDir (unsigned char motor)
{
	unsigned char ret=0;
	
	switch (motor)
	{
		case MOTOR_1:
			ret=!MOTOR1_DIR;
		break;
      
		case MOTOR_2:
			ret=MOTOR2_DIR;
		break;
	}

	return ret;
}

int motorInvertDir (unsigned char motor)
{
	int ret=0;

	printf ("motorInvertDir\n\r");
	switch (motor)
	{
		case MOTOR_1:
			MOTOR1_DIR=~MOTOR1_DIR;
		break;
      
		case MOTOR_2:
			MOTOR2_DIR=~MOTOR2_DIR;
		break;
      
		default:
			ret=1;
		break;
	}
	return ret;
}

int motorChangeDir (unsigned char dir, unsigned char motor)
{
   int ret=0;

	printf ("motorChangeDir\n\r");
	switch (motor)
   {
      case MOTOR_1:
			MOTOR1_DIR=!dir;
      break;
      
      case MOTOR_2:
			MOTOR2_DIR=dir;
      break;
      
      default:
         ret=1;
		break;
   }
   return ret;
}

int getEncoderWidth(unsigned char motor)
{
   return encoder[motor].inSpeed;
}

unsigned char getEncoderDir(unsigned char motor)
{
   return encoder[motor].pulseDir;
}
