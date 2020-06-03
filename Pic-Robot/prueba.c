/* ----------------------------------------------------------------------- */
/* Plantilla generada por Piklab */

// Note: there are timing related problems associated with GET_FEATURE
// when run at less than 48 MHz
#define CLK_48MHZ 1

#include <pic18f4455.h>
#include <stdio.h>
#include <usart.h>
#include <signal.h>
#include "usb.h"
#include "motores.h"	
#include "common.h"
/* ----------------------------------------------------------------------- */

__code char __at 0x300000 CONFIG1L = 0x24; // USB, /2 post (48MHz), /5 pre (20 MHz)
__code char __at 0x300001 CONFIG1H = 0x0e; // IESO=0, FCMEN=0, HS-PLL (40MHz)
__code char __at 0x300002 CONFIG2L = 0x38; // Brown out off, PWRT On
__code char __at 0x300003 CONFIG2H = 0x00; // WDT off
__code char __at 0x300004 CONFIG3L = 0xff; // Unused configuration bits
__code char __at 0x300005 CONFIG3H = 0x81; // MCLR, PORTB digital, CCP2 - RC1
__code char __at 0x300006 CONFIG4L = 0x81; // ICD off, ext off, LVP off, stk ovr off
__code char __at 0x300007 CONFIG4H = 0xff; // Unused configuration bits
__code char __at 0x300008 CONFIG5L = 0xff; // No code read protection
__code char __at 0x300009 CONFIG5H = 0xff; // No data/boot read protection
__code char __at 0x30000A CONFIG6L = 0xff; // No code write protection
__code char __at 0x30000B CONFIG6H = 0xff; // No data/boot/table protection
__code char __at 0x30000C CONFIG7L = 0xff; // No table read protection
__code char __at 0x30000D CONFIG7H = 0xff; // No boot table protection

int velocidad=0;

volatile unsigned char HIDFeatureBuffer[HID_FEATURE_REPORT_BYTES];

// Allocate buffers in RAM for storage of bytes that have either just
// come in from the SIE or are waiting to go out to the SIE.
char txBuffer[HID_INPUT_REPORT_BYTES];
char rxBuffer[HID_OUTPUT_REPORT_BYTES];

//Definitions for using Timer0 interrupts
DEF_INTHIGH(high_int)
DEF_HANDLER(SIG_TMR0, _tmr0_handler)
END_DEF

SIGHANDLER(_tmr0_handler)
{
   readEncoders();
   TMR0L  = 99;
   INTCON = 0x20;       // Set T0IE, clear T0IF    
   
}

int uart_GetString (char *str)
{
	int pos=0;
	char *str_old = str;
	while ( *(str-1)!=0x0d )
	{
		if (usart_drdy())
		{
			*str= usart_getc();
			usart_putc (*str);
			
			if (*str==0x08)
				str--;
			else
				str++;
		}
	}
	*str=0;
	return (str-str_old);
}

void initializeTimer(void)
{
   //Calculado para 0.5 ms
   //Con la aplicación Timer_Calculator_V0_3.exe
   //Configuracion:
   // Timer Module: Timer 0
   // Pic and Clock speed: PIC18 / 48,00000000 MHzb
   // Output in ms: 0,5 ms
   // Counter Time Out = 1

   T0CON = 0xc3;      // assign prescaler to TMR0
   TMR0L = 99;
   INTCON = 0xa0;  // Enable TMRO interrupt
}

static void initializeUSART(void)
{

    TRISC &= 0xBF; // Set RC6 as an output
    TRISC |= 0x80; // Set RC7 as an input
    RCSTA   = 0x90; // Enable serial port, enable receiver
    TXSTA   = 0x24; // Asynch, TSR empty, BRGH=1

    // Baud rate formula for BRG16=1, BRGH=1: Baud Rate = Fosc/(4 (n + 1)),
    // or n = (Fosc / (4 * BaudRate)) - 1
    // At 48 MHz, for 115.2K Baud:
    //     SPBRGH:SPBRG = n = Fosc / (4 * 115200) - 1 = 103.17
    BAUDCON = 0x08; // BRG16=1
    SPBRGH  = 0x00; // At 48MHz, SPBRGH=0, SPBRG=103 gives 115.2K Baud
#if CLK_48MHZ
    SPBRG   = 103;  // For 48 MHz clock
#else
    SPBRG   = 52;   // For 24 MHz clock
#endif

    // Assign standard input and output to the USART
    stdin = STREAM_USART;
    stdout = STREAM_USART;
}

// Regardless of what the USB is up to, we check the USART to see
// if there's something we should be doing.
static void checkEcho()
{
	static char bDebug=0, antDebug;
	static int giro=0;
	char buffer[80];
	
	if (usart_drdy())
	{
			// Have a character to huh
		unsigned char rxByte;
		rxByte = usart_getc();
		usart_putc(rxByte);
		
		switch (rxByte)
		{
			case ' ':
				bDebug=!bDebug;
				printf ("\n\rDebug=%d ",bDebug);
				setMotorsDebug (bDebug);
			break;

			case 'a':
				velocidad++;
				motorSpeed (velocidad, MOTOR_1);
				motorSpeed (velocidad, MOTOR_2);
			break;

			case 'z':
				velocidad--;
				motorSpeed (velocidad, MOTOR_1);
				motorSpeed (velocidad, MOTOR_2);
			break;
			
			case 'e':
				antDebug=bDebug;
				setMotorsDebug (0);
				printf ("\n\rEntre velocidad: ");
				uart_GetString(buffer);
				velocidad = atoi (buffer);
				printf ("\n\rVelocidad = %d",velocidad);
				motorSpeed (velocidad, MOTOR_1);
				motorSpeed (velocidad, MOTOR_2);
				setMotorsDebug (antDebug);
				break;
			
			case 'X':
				if(deviceState == DETACHED)
					printf("Detached\r\n");
				else if(deviceState == ATTACHED)
					printf("Attached\r\n");
				else if(deviceState == POWERED)
					printf("Powered\r\n");
				else if(deviceState == DEFAULT)
					printf("Default\r\n");
				else if(deviceState == ADDRESS)
					printf("Address\r\n");
				else if(deviceState == CONFIGURED)
					printf("Configured\r\n");
				else
					printf("Unknown state\r\n");
		
				printf("UCON: %x, UCFG: %x\r\n", UCON, UCFG);
			break;
			
		}
	}
}

void ApplicationTasks(void)
{
    // User Application USB tasks
    if ((deviceState < CONFIGURED) || (UCONbits.SUSPND==1))
        return;
	 
	 checkEcho();
    
}

// Handle control out.  This might be an alternate way of processing
// an output report, so all that's needed is to point the output
// pointer to the output buffer
// Initialization for a SET_REPORT request.  This routine will be
// invoked during the setup stage and is used to set up the buffer
// for receiving data from the host
void SetupOutputReport(byte reportID)
{
//	printf ("SetupOutputReport\n\r");
	if (reportID == 0)
	{
		inPtr = (byte*)&HIDRxBuffer;
	}
}

// Post processing for a SET_REPORT request.  After all the data has
// been delivered from host to device, this will be invoked to perform
// application specific processing.
void SetOutputReport(byte reportID)
{
	//short  n;
	short bPid;
	short motorSpeed1, motorSpeed2;

//	printf ("SetOuputReport\n\r");
	// Currently only handling report 0, ignore any others.
	if (reportID != 0)
		return;
	
/*	for (n=0;n<8;n++)
		printf ("%x ",HIDRxBuffer[n]);
	printf ("\n\r");*/

	velocidad=HIDRxBuffer[0]<<8;
	velocidad|=HIDRxBuffer[1];

	motorSpeed1 = HIDRxBuffer[2]<<8;
	motorSpeed1 |= HIDRxBuffer[3];
		
	motorSpeed2 = HIDRxBuffer[4]<<8;
	motorSpeed2 |= HIDRxBuffer[5];

//	motorSpeed (velocidad,MOTOR_1);
//	motorSpeed (velocidad,MOTOR_2);
		
	motorSpeed (motorSpeed1,MOTOR_1);
	motorSpeed (motorSpeed2,MOTOR_2);

	bPid=HIDRxBuffer[6]<<8;
	bPid|=HIDRxBuffer[7];
	setPidEnabled ((char)bPid);
//	motorGira(giro);

//	printf ("velocidad=%x\n\r",velocidad);
	
}

// Initialization for a SET_FEATURE request.  This routine will be
// invoked during the setup stage and is used to set up the buffer
// for receiving data from the host
void SetupFeatureReport(byte reportID)
{
	printf ("SetupFeatureReport\n\r");
	if (reportID == 0)
	{
		inPtr = (byte*)&HIDFeatureBuffer;
	}
}
// Post processing for a SET_FEATURE request.  After all the data has
// been delivered from host to device, this will be invoked to perform
// application specific processing.
void SetFeatureReport(byte reportID)
{
	
/*	if (reportID == 0)
	{		
		velocidad=HIDFeatureBuffer[0]<<8;
		velocidad|=HIDFeatureBuffer[1];
   }*/
}

// Handle a feature report request on the control pipe
void GetFeatureReport(byte reportID)
{
   //char n;
//	printf("GetFeatureReport(0x%uhx): 0x%hx, 0x%hx\r\n",
//		(byte)reportID, (byte)HIDFeatureBuffer[0],
//		(byte)HIDFeatureBuffer[1]);

	if (reportID == 0)
	{
		// Handle report #0
		outPtr = (byte *)&HIDFeatureBuffer;
		
//		printf ("motor1=%x:%x\n\r",HIDFeatureBuffer[0],HIDFeatureBuffer[1]);
//      HIDFeatureBuffer[2] = getEncoderDir(MOTOR_2);
//      HIDFeatureBuffer[3] = getEncoderWidth(MOTOR_2);
      
		// HIDFeatureBuffer[HID_FEATURE_REPORT_BYTES-1] = 0x2C;
		wCount = HID_FEATURE_REPORT_BYTES-1;

//		for (n=0;n<HID_FEATURE_REPORT_BYTES-1;n++)
//			printf ("%x ",HIDFeatureBuffer[n]);
//		printf ("\n\r");

	}
}

// Handle a control input report
void GetInputReport(byte reportID)
{
	//short n;
//#if DEBUG_PRINT
//	printf("GetInputReport: 0x%uhx\r\n", reportID);
//#endif
	if (reportID == 0)
	{
		HIDTxBuffer[0] = (velocidad & 0xff00)>>8;
		HIDTxBuffer[1] = (velocidad & 0x00ff);
		
		HIDTxBuffer[2] = (getEncoderWidth(MOTOR_1) & 0xff00)>>8;
		HIDTxBuffer[3] = (getEncoderWidth(MOTOR_1)&0x00ff);
		
		HIDTxBuffer[4] = (getEncoderWidth(MOTOR_2) & 0xff00)>>8;
		HIDTxBuffer[5] = (getEncoderWidth(MOTOR_2)&0x00ff);

		HIDTxBuffer[6] = 0;
		HIDTxBuffer[7] = 0;

//		for (n=0;n<HID_FEATURE_REPORT_BYTES;n++)
//			printf ("%x ",HIDTxBuffer[n]);
//		printf ("\n\r");

		outPtr = (__data byte *)&HIDTxBuffer;
		wCount = HID_INPUT_REPORT_BYTES;
	}
}



void main() 
{
   deviceState = DETACHED;
   remoteWakeup = 0x00;
   selfPowered = 0x00;
   currentConfiguration = 0x00;
   
   initializeUSART();
   initializeMotors();
   initializeTimer();
	
   
	printf("PIC Test\r\n");
	printf ("long = %d\n\r",sizeof (long));
	SetupPacket.bmRequestType=0;
	for (;;)
	{
      // Ensure USB module is available
		EnableUSBModule();

		// As long as we aren't in test mode (UTEYE), process
		// USB transactions.
		if(UCFGbits.UTEYE != 1)
			ProcessUSBTransactions();
		
        ApplicationTasks();
	}
}
