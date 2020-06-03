;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.0 #8981 (Apr  5 2014) (Linux)
; This file was generated Mon Sep  1 01:28:46 2014
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------

	.ident "SDCC version 3.4.0 #8981 [pic16 port]"
	.file	"prueba.c"
	list	p=18f4455
	radix	dec
	__config 0x300000, 0x24
	__config 0x300001, 0x0e
	__config 0x300002, 0x38
	__config 0x300003, 0x00
	__config 0x300005, 0x81
	__config 0x300006, 0x81
	__config 0x300008, 0xff
	__config 0x300009, 0xff
	__config 0x30000a, 0xff
	__config 0x30000b, 0xff
	__config 0x30000c, 0xff
	__config 0x30000d, 0xff


;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global	_rxBuffer
	global	_txBuffer
	global	_velocidad
	global	_HIDFeatureBuffer
	global	___ivt_high_int
	global	_high_int
	global	__tmr0_handler
	global	_uart_GetString
	global	_initializeTimer
	global	_ApplicationTasks
	global	_SetupOutputReport
	global	_SetOutputReport
	global	_SetupFeatureReport
	global	_SetFeatureReport
	global	_GetFeatureReport
	global	_GetInputReport
	global	_main

;--------------------------------------------------------
; extern variables in this module
;--------------------------------------------------------
	extern	__gptrget1
	extern	__gptrput1
	extern	_SPPCFGbits
	extern	_SPPEPSbits
	extern	_SPPCONbits
	extern	_UFRMLbits
	extern	_UFRMHbits
	extern	_UIRbits
	extern	_UIEbits
	extern	_UEIRbits
	extern	_UEIEbits
	extern	_USTATbits
	extern	_UCONbits
	extern	_UADDRbits
	extern	_UCFGbits
	extern	_UEP0bits
	extern	_UEP1bits
	extern	_UEP2bits
	extern	_UEP3bits
	extern	_UEP4bits
	extern	_UEP5bits
	extern	_UEP6bits
	extern	_UEP7bits
	extern	_UEP8bits
	extern	_UEP9bits
	extern	_UEP10bits
	extern	_UEP11bits
	extern	_UEP12bits
	extern	_UEP13bits
	extern	_UEP14bits
	extern	_UEP15bits
	extern	_PORTAbits
	extern	_PORTBbits
	extern	_PORTCbits
	extern	_PORTDbits
	extern	_PORTEbits
	extern	_LATAbits
	extern	_LATBbits
	extern	_LATCbits
	extern	_LATDbits
	extern	_LATEbits
	extern	_DDRAbits
	extern	_TRISAbits
	extern	_DDRBbits
	extern	_TRISBbits
	extern	_DDRCbits
	extern	_TRISCbits
	extern	_DDRDbits
	extern	_TRISDbits
	extern	_DDREbits
	extern	_TRISEbits
	extern	_OSCTUNEbits
	extern	_PIE1bits
	extern	_PIR1bits
	extern	_IPR1bits
	extern	_PIE2bits
	extern	_PIR2bits
	extern	_IPR2bits
	extern	_EECON1bits
	extern	_RCSTAbits
	extern	_TXSTAbits
	extern	_T3CONbits
	extern	_CMCONbits
	extern	_CVRCONbits
	extern	_CCP1ASbits
	extern	_ECCP1ASbits
	extern	_CCP1DELbits
	extern	_ECCP1DELbits
	extern	_BAUDCONbits
	extern	_BAUDCTLbits
	extern	_CCP2CONbits
	extern	_CCP1CONbits
	extern	_ECCP1CONbits
	extern	_ADCON2bits
	extern	_ADCON1bits
	extern	_ADCON0bits
	extern	_SSPCON2bits
	extern	_SSPCON1bits
	extern	_SSPSTATbits
	extern	_T2CONbits
	extern	_T1CONbits
	extern	_RCONbits
	extern	_WDTCONbits
	extern	_HLVDCONbits
	extern	_LVDCONbits
	extern	_OSCCONbits
	extern	_T0CONbits
	extern	_STATUSbits
	extern	_INTCON3bits
	extern	_INTCON2bits
	extern	_INTCONbits
	extern	_STKPTRbits
	extern	_stdin
	extern	_stdout
	extern	_deviceState
	extern	_selfPowered
	extern	_remoteWakeup
	extern	_currentConfiguration
	extern	_ep0Bo
	extern	_ep0Bi
	extern	_ep1Bo
	extern	_ep1Bi
	extern	_SetupPacket
	extern	_HIDRxBuffer
	extern	_HIDTxBuffer
	extern	_outPtr
	extern	_inPtr
	extern	_wCount
	extern	_hidRxLen
	extern	_SPPDATA
	extern	_SPPCFG
	extern	_SPPEPS
	extern	_SPPCON
	extern	_UFRM
	extern	_UFRML
	extern	_UFRMH
	extern	_UIR
	extern	_UIE
	extern	_UEIR
	extern	_UEIE
	extern	_USTAT
	extern	_UCON
	extern	_UADDR
	extern	_UCFG
	extern	_UEP0
	extern	_UEP1
	extern	_UEP2
	extern	_UEP3
	extern	_UEP4
	extern	_UEP5
	extern	_UEP6
	extern	_UEP7
	extern	_UEP8
	extern	_UEP9
	extern	_UEP10
	extern	_UEP11
	extern	_UEP12
	extern	_UEP13
	extern	_UEP14
	extern	_UEP15
	extern	_PORTA
	extern	_PORTB
	extern	_PORTC
	extern	_PORTD
	extern	_PORTE
	extern	_LATA
	extern	_LATB
	extern	_LATC
	extern	_LATD
	extern	_LATE
	extern	_DDRA
	extern	_TRISA
	extern	_DDRB
	extern	_TRISB
	extern	_DDRC
	extern	_TRISC
	extern	_DDRD
	extern	_TRISD
	extern	_DDRE
	extern	_TRISE
	extern	_OSCTUNE
	extern	_PIE1
	extern	_PIR1
	extern	_IPR1
	extern	_PIE2
	extern	_PIR2
	extern	_IPR2
	extern	_EECON1
	extern	_EECON2
	extern	_EEDATA
	extern	_EEADR
	extern	_RCSTA
	extern	_TXSTA
	extern	_TXREG
	extern	_RCREG
	extern	_SPBRG
	extern	_SPBRGH
	extern	_T3CON
	extern	_TMR3
	extern	_TMR3L
	extern	_TMR3H
	extern	_CMCON
	extern	_CVRCON
	extern	_CCP1AS
	extern	_ECCP1AS
	extern	_CCP1DEL
	extern	_ECCP1DEL
	extern	_BAUDCON
	extern	_BAUDCTL
	extern	_CCP2CON
	extern	_CCPR2
	extern	_CCPR2L
	extern	_CCPR2H
	extern	_CCP1CON
	extern	_ECCP1CON
	extern	_CCPR1
	extern	_CCPR1L
	extern	_CCPR1H
	extern	_ADCON2
	extern	_ADCON1
	extern	_ADCON0
	extern	_ADRES
	extern	_ADRESL
	extern	_ADRESH
	extern	_SSPCON2
	extern	_SSPCON1
	extern	_SSPSTAT
	extern	_SSPADD
	extern	_SSPBUF
	extern	_T2CON
	extern	_PR2
	extern	_TMR2
	extern	_T1CON
	extern	_TMR1
	extern	_TMR1L
	extern	_TMR1H
	extern	_RCON
	extern	_WDTCON
	extern	_HLVDCON
	extern	_LVDCON
	extern	_OSCCON
	extern	_T0CON
	extern	_TMR0
	extern	_TMR0L
	extern	_TMR0H
	extern	_STATUS
	extern	_FSR2L
	extern	_FSR2H
	extern	_PLUSW2
	extern	_PREINC2
	extern	_POSTDEC2
	extern	_POSTINC2
	extern	_INDF2
	extern	_BSR
	extern	_FSR1L
	extern	_FSR1H
	extern	_PLUSW1
	extern	_PREINC1
	extern	_POSTDEC1
	extern	_POSTINC1
	extern	_INDF1
	extern	_WREG
	extern	_FSR0L
	extern	_FSR0H
	extern	_PLUSW0
	extern	_PREINC0
	extern	_POSTDEC0
	extern	_POSTINC0
	extern	_INDF0
	extern	_INTCON3
	extern	_INTCON2
	extern	_INTCON
	extern	_PROD
	extern	_PRODL
	extern	_PRODH
	extern	_TABLAT
	extern	_TBLPTR
	extern	_TBLPTRL
	extern	_TBLPTRH
	extern	_TBLPTRU
	extern	_PC
	extern	_PCL
	extern	_PCLATH
	extern	_PCLATU
	extern	_STKPTR
	extern	_TOS
	extern	_TOSL
	extern	_TOSH
	extern	_TOSU
	extern	_printf
	extern	_usart_drdy
	extern	_usart_getc
	extern	_usart_putc
	extern	_EnableUSBModule
	extern	_ProcessUSBTransactions
	extern	_readEncoders
	extern	_initializeMotors
	extern	_getEncoderWidth
	extern	_motorSpeed
	extern	_setMotorsDebug
	extern	_setPidEnabled
	extern	_atoi

;--------------------------------------------------------
;	Equates to used internal registers
;--------------------------------------------------------
STATUS	equ	0xfd8
PCLATH	equ	0xffa
PCLATU	equ	0xffb
WREG	equ	0xfe8
BSR	equ	0xfe0
FSR0L	equ	0xfe9
FSR0H	equ	0xfea
FSR1L	equ	0xfe1
FSR2L	equ	0xfd9
POSTINC1	equ	0xfe6
POSTDEC1	equ	0xfe5
PREINC1	equ	0xfe4
PLUSW2	equ	0xfdb
PRODL	equ	0xff3
PRODH	equ	0xff4


	idata
_velocidad	db	0x00, 0x00
_checkEcho_bDebug_1_56	db	0x00
_checkEcho_giro_1_56	db	0x00, 0x00


; Internal registers
.registers	udata_ovr	0x0000
r0x00	res	1
r0x01	res	1
r0x02	res	1
r0x03	res	1
r0x04	res	1
r0x05	res	1
r0x06	res	1
r0x07	res	1
r0x08	res	1
r0x09	res	1

udata_prueba_0	udata
_txBuffer	res	32

udata_prueba_1	udata
_rxBuffer	res	32

udata_prueba_2	udata
_checkEcho_antDebug_1_56	res	1

udata_prueba_3	udata
_checkEcho_buffer_1_56	res	80

udata_prueba_4	udata
_HIDFeatureBuffer	res	32

;--------------------------------------------------------
; interrupt vector
;--------------------------------------------------------

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; ; Starting pCode block
S_prueba____ivt_high_int	code	0X000008
___ivt_high_int:
	goto _high_int 
; ; Starting pCode block
S_prueba__high_int	code
_high_int:
	btfsc _INTCON, 2, 0 
	goto __tmr0_handler 
	retfie 
; ; Starting pCode block
S_prueba___tmr0_handler	code
__tmr0_handler:
	.line	46; prueba.c	SIGHANDLER(_tmr0_handler)
	MOVFF	STATUS, POSTDEC1
	MOVFF	BSR, POSTDEC1
	MOVWF	POSTDEC1
	MOVFF	PRODL, POSTDEC1
	MOVFF	PRODH, POSTDEC1
	MOVFF	FSR0L, POSTDEC1
	MOVFF	FSR0H, POSTDEC1
	MOVFF	PCLATH, POSTDEC1
	MOVFF	PCLATU, POSTDEC1
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	48; prueba.c	readEncoders();
	CALL	_readEncoders
	.line	49; prueba.c	TMR0L  = 99;
	MOVLW	0x63
	MOVWF	_TMR0L
	.line	50; prueba.c	INTCON = 0x20;       // Set T0IE, clear T0IF    
	MOVLW	0x20
	MOVWF	_INTCON
	MOVFF	PREINC1, FSR2L
	MOVFF	PREINC1, PCLATU
	MOVFF	PREINC1, PCLATH
	MOVFF	PREINC1, FSR0H
	MOVFF	PREINC1, FSR0L
	MOVFF	PREINC1, PRODH
	MOVFF	PREINC1, PRODL
	MOVF	PREINC1, W
	MOVFF	PREINC1, BSR
	MOVFF	PREINC1, STATUS
	RETFIE	

; I code from now on!
; ; Starting pCode block
S_prueba__main	code
_main:
	BANKSEL	_deviceState
	.line	337; prueba.c	deviceState = DETACHED;
	CLRF	_deviceState, B
	BANKSEL	_remoteWakeup
	.line	338; prueba.c	remoteWakeup = 0x00;
	CLRF	_remoteWakeup, B
	BANKSEL	_selfPowered
	.line	339; prueba.c	selfPowered = 0x00;
	CLRF	_selfPowered, B
	BANKSEL	_currentConfiguration
	.line	340; prueba.c	currentConfiguration = 0x00;
	CLRF	_currentConfiguration, B
	.line	342; prueba.c	initializeUSART();
	CALL	_initializeUSART
	.line	343; prueba.c	initializeMotors();
	CALL	_initializeMotors
	.line	344; prueba.c	initializeTimer();
	CALL	_initializeTimer
	.line	347; prueba.c	printf("PIC Test\r\n");
	MOVLW	UPPER(___str_12)
	MOVWF	r0x02
	MOVLW	HIGH(___str_12)
	MOVWF	r0x01
	MOVLW	LOW(___str_12)
	MOVWF	r0x00
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_printf
	MOVLW	0x03
	ADDWF	FSR1L, F
	.line	348; prueba.c	printf ("long = %d\n\r",sizeof (long));
	MOVLW	UPPER(___str_13)
	MOVWF	r0x02
	MOVLW	HIGH(___str_13)
	MOVWF	r0x01
	MOVLW	LOW(___str_13)
	MOVWF	r0x00
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x04
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_printf
	MOVLW	0x05
	ADDWF	FSR1L, F
	BANKSEL	_SetupPacket
	.line	349; prueba.c	SetupPacket.bmRequestType=0;
	CLRF	_SetupPacket, B
_00307_DS_:
	.line	353; prueba.c	EnableUSBModule();
	CALL	_EnableUSBModule
	.line	357; prueba.c	if(UCFGbits.UTEYE != 1)
	CLRF	r0x00
	BTFSC	_UCFGbits, 7
	INCF	r0x00, F
	MOVF	r0x00, W
	XORLW	0x01
	BZ	_00305_DS_
	.line	358; prueba.c	ProcessUSBTransactions();
	CALL	_ProcessUSBTransactions
_00305_DS_:
	.line	360; prueba.c	ApplicationTasks();
	CALL	_ApplicationTasks
	BRA	_00307_DS_
	RETURN	

; ; Starting pCode block
S_prueba__GetInputReport	code
_GetInputReport:
	.line	304; prueba.c	void GetInputReport(byte reportID)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	.line	310; prueba.c	if (reportID == 0)
	MOVF	r0x00, W
	BTFSS	STATUS, 2
	BRA	_00299_DS_
	BANKSEL	_velocidad
	.line	312; prueba.c	HIDTxBuffer[0] = (velocidad & 0xff00)>>8;
	MOVF	_velocidad, W, B
	MOVWF	r0x00
	BANKSEL	(_velocidad + 1)
	MOVF	(_velocidad + 1), W, B
	MOVWF	r0x01
	CLRF	r0x00
	MOVF	r0x01, W
	MOVWF	r0x00
	CLRF	r0x01
	MOVF	r0x00, W
	BANKSEL	_HIDTxBuffer
	MOVWF	_HIDTxBuffer, B
	BANKSEL	_velocidad
	.line	313; prueba.c	HIDTxBuffer[1] = (velocidad & 0x00ff);
	MOVF	_velocidad, W, B
	MOVWF	r0x00
	CLRF	r0x01
	MOVF	r0x00, W
	BANKSEL	(_HIDTxBuffer + 1)
	MOVWF	(_HIDTxBuffer + 1), B
	.line	315; prueba.c	HIDTxBuffer[2] = (getEncoderWidth(MOTOR_1) & 0xff00)>>8;
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_getEncoderWidth
	MOVWF	r0x00
	MOVFF	PRODL, r0x01
	MOVF	POSTINC1, F
	CLRF	r0x00
	MOVF	r0x01, W
	MOVWF	r0x00
	CLRF	r0x01
	MOVF	r0x00, W
	BANKSEL	(_HIDTxBuffer + 2)
	MOVWF	(_HIDTxBuffer + 2), B
	.line	316; prueba.c	HIDTxBuffer[3] = (getEncoderWidth(MOTOR_1)&0x00ff);
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_getEncoderWidth
	MOVWF	r0x00
	MOVFF	PRODL, r0x01
	MOVF	POSTINC1, F
	CLRF	r0x01
	MOVF	r0x00, W
	BANKSEL	(_HIDTxBuffer + 3)
	MOVWF	(_HIDTxBuffer + 3), B
	.line	318; prueba.c	HIDTxBuffer[4] = (getEncoderWidth(MOTOR_2) & 0xff00)>>8;
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_getEncoderWidth
	MOVWF	r0x00
	MOVFF	PRODL, r0x01
	MOVF	POSTINC1, F
	CLRF	r0x00
	MOVF	r0x01, W
	MOVWF	r0x00
	CLRF	r0x01
	MOVF	r0x00, W
	BANKSEL	(_HIDTxBuffer + 4)
	MOVWF	(_HIDTxBuffer + 4), B
	.line	319; prueba.c	HIDTxBuffer[5] = (getEncoderWidth(MOTOR_2)&0x00ff);
	MOVLW	0x01
	MOVWF	POSTDEC1
	CALL	_getEncoderWidth
	MOVWF	r0x00
	MOVFF	PRODL, r0x01
	MOVF	POSTINC1, F
	CLRF	r0x01
	MOVF	r0x00, W
	BANKSEL	(_HIDTxBuffer + 5)
	MOVWF	(_HIDTxBuffer + 5), B
	BANKSEL	(_HIDTxBuffer + 6)
	.line	321; prueba.c	HIDTxBuffer[6] = 0;
	CLRF	(_HIDTxBuffer + 6), B
	BANKSEL	(_HIDTxBuffer + 7)
	.line	322; prueba.c	HIDTxBuffer[7] = 0;
	CLRF	(_HIDTxBuffer + 7), B
	.line	328; prueba.c	outPtr = (__data byte *)&HIDTxBuffer;
	MOVLW	HIGH(_HIDTxBuffer)
	BANKSEL	(_outPtr + 1)
	MOVWF	(_outPtr + 1), B
	MOVLW	LOW(_HIDTxBuffer)
	BANKSEL	_outPtr
	MOVWF	_outPtr, B
	MOVLW	0x80
	BANKSEL	(_outPtr + 2)
	MOVWF	(_outPtr + 2), B
	.line	329; prueba.c	wCount = HID_INPUT_REPORT_BYTES;
	MOVLW	0x20
	BANKSEL	_wCount
	MOVWF	_wCount, B
	BANKSEL	(_wCount + 1)
	CLRF	(_wCount + 1), B
_00299_DS_:
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_prueba__GetFeatureReport	code
_GetFeatureReport:
	.line	277; prueba.c	void GetFeatureReport(byte reportID)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	.line	284; prueba.c	if (reportID == 0)
	MOVF	r0x00, W
	BNZ	_00292_DS_
	.line	287; prueba.c	outPtr = (byte *)&HIDFeatureBuffer;
	MOVLW	HIGH(_HIDFeatureBuffer)
	BANKSEL	(_outPtr + 1)
	MOVWF	(_outPtr + 1), B
	MOVLW	LOW(_HIDFeatureBuffer)
	BANKSEL	_outPtr
	MOVWF	_outPtr, B
	MOVLW	0x80
	BANKSEL	(_outPtr + 2)
	MOVWF	(_outPtr + 2), B
	.line	294; prueba.c	wCount = HID_FEATURE_REPORT_BYTES-1;
	MOVLW	0x1f
	BANKSEL	_wCount
	MOVWF	_wCount, B
	BANKSEL	(_wCount + 1)
	CLRF	(_wCount + 1), B
_00292_DS_:
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_prueba__SetFeatureReport	code
_SetFeatureReport:
	.line	266; prueba.c	void SetFeatureReport(byte reportID)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	274; prueba.c	}
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_prueba__SetupFeatureReport	code
_SetupFeatureReport:
	.line	255; prueba.c	void SetupFeatureReport(byte reportID)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	.line	257; prueba.c	printf ("SetupFeatureReport\n\r");
	MOVLW	UPPER(___str_11)
	MOVWF	r0x03
	MOVLW	HIGH(___str_11)
	MOVWF	r0x02
	MOVLW	LOW(___str_11)
	MOVWF	r0x01
	MOVF	r0x03, W
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	CALL	_printf
	MOVLW	0x03
	ADDWF	FSR1L, F
	.line	258; prueba.c	if (reportID == 0)
	MOVF	r0x00, W
	BNZ	_00280_DS_
	.line	260; prueba.c	inPtr = (byte*)&HIDFeatureBuffer;
	MOVLW	HIGH(_HIDFeatureBuffer)
	BANKSEL	(_inPtr + 1)
	MOVWF	(_inPtr + 1), B
	MOVLW	LOW(_HIDFeatureBuffer)
	BANKSEL	_inPtr
	MOVWF	_inPtr, B
	MOVLW	0x80
	BANKSEL	(_inPtr + 2)
	MOVWF	(_inPtr + 2), B
_00280_DS_:
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_prueba__SetOutputReport	code
_SetOutputReport:
	.line	213; prueba.c	void SetOutputReport(byte reportID)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVFF	r0x05, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	.line	221; prueba.c	if (reportID != 0)
	MOVF	r0x00, W
	BZ	_00272_DS_
	.line	222; prueba.c	return;
	BRA	_00273_DS_
_00272_DS_:
	.line	228; prueba.c	velocidad=HIDRxBuffer[0]<<8;
	MOVFF	_HIDRxBuffer, r0x00
	CLRF	r0x01
	MOVF	r0x00, W
	BANKSEL	(_velocidad + 1)
	MOVWF	(_velocidad + 1), B
	BANKSEL	_velocidad
	CLRF	_velocidad, B
	.line	229; prueba.c	velocidad|=HIDRxBuffer[1];
	MOVFF	(_HIDRxBuffer + 1), r0x00
	CLRF	r0x01
	MOVF	r0x00, W
	BANKSEL	_velocidad
	IORWF	_velocidad, F, B
	MOVF	r0x01, W
	BANKSEL	(_velocidad + 1)
	IORWF	(_velocidad + 1), F, B
	.line	231; prueba.c	motorSpeed1 = HIDRxBuffer[2]<<8;
	MOVFF	(_HIDRxBuffer + 2), r0x00
	CLRF	r0x01
	MOVF	r0x00, W
	MOVWF	r0x03
	CLRF	r0x02
	.line	232; prueba.c	motorSpeed1 |= HIDRxBuffer[3];
	MOVFF	(_HIDRxBuffer + 3), r0x00
	CLRF	r0x01
	MOVF	r0x00, W
	IORWF	r0x02, F
	MOVF	r0x01, W
	IORWF	r0x03, F
	.line	234; prueba.c	motorSpeed2 = HIDRxBuffer[4]<<8;
	MOVFF	(_HIDRxBuffer + 4), r0x00
	CLRF	r0x01
	MOVF	r0x00, W
	MOVWF	r0x05
	CLRF	r0x04
	.line	235; prueba.c	motorSpeed2 |= HIDRxBuffer[5];
	MOVFF	(_HIDRxBuffer + 5), r0x00
	CLRF	r0x01
	MOVF	r0x00, W
	IORWF	r0x04, F
	MOVF	r0x01, W
	IORWF	r0x05, F
	.line	240; prueba.c	motorSpeed (motorSpeed1,MOTOR_1);
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVF	r0x03, W
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	CALL	_motorSpeed
	MOVLW	0x03
	ADDWF	FSR1L, F
	.line	241; prueba.c	motorSpeed (motorSpeed2,MOTOR_2);
	MOVLW	0x01
	MOVWF	POSTDEC1
	MOVF	r0x05, W
	MOVWF	POSTDEC1
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	CALL	_motorSpeed
	MOVLW	0x03
	ADDWF	FSR1L, F
	.line	243; prueba.c	bPid=HIDRxBuffer[6]<<8;
	MOVFF	(_HIDRxBuffer + 6), r0x00
	CLRF	r0x01
	MOVF	r0x00, W
	MOVWF	r0x03
	CLRF	r0x02
	.line	244; prueba.c	bPid|=HIDRxBuffer[7];
	MOVFF	(_HIDRxBuffer + 7), r0x00
	CLRF	r0x01
	MOVF	r0x00, W
	IORWF	r0x02, F
	MOVF	r0x01, W
	IORWF	r0x03, F
	.line	245; prueba.c	setPidEnabled ((char)bPid);
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	CALL	_setPidEnabled
	MOVF	POSTINC1, F
_00273_DS_:
	MOVFF	PREINC1, r0x05
	MOVFF	PREINC1, r0x04
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_prueba__SetupOutputReport	code
_SetupOutputReport:
	.line	201; prueba.c	void SetupOutputReport(byte reportID)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	.line	204; prueba.c	if (reportID == 0)
	MOVF	r0x00, W
	BNZ	_00266_DS_
	.line	206; prueba.c	inPtr = (byte*)&HIDRxBuffer;
	MOVLW	HIGH(_HIDRxBuffer)
	BANKSEL	(_inPtr + 1)
	MOVWF	(_inPtr + 1), B
	MOVLW	LOW(_HIDRxBuffer)
	BANKSEL	_inPtr
	MOVWF	_inPtr, B
	MOVLW	0x80
	BANKSEL	(_inPtr + 2)
	MOVWF	(_inPtr + 2), B
_00266_DS_:
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_prueba__ApplicationTasks	code
_ApplicationTasks:
	.line	185; prueba.c	void ApplicationTasks(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	.line	188; prueba.c	if ((deviceState < CONFIGURED) || (UCONbits.SUSPND==1))
	MOVLW	0x05
	BANKSEL	_deviceState
	SUBWF	_deviceState, W, B
	BNC	_00249_DS_
	CLRF	r0x00
	BTFSC	_UCONbits, 1
	INCF	r0x00, F
	MOVF	r0x00, W
	XORLW	0x01
	BNZ	_00250_DS_
_00249_DS_:
	.line	189; prueba.c	return;
	BRA	_00252_DS_
_00250_DS_:
	.line	191; prueba.c	checkEcho();
	CALL	_checkEcho
_00252_DS_:
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_prueba__checkEcho	code
_checkEcho:
	.line	117; prueba.c	static void checkEcho()
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVFF	r0x05, POSTDEC1
	MOVFF	r0x06, POSTDEC1
	.line	123; prueba.c	if (usart_drdy())
	CALL	_usart_drdy
	MOVWF	r0x00
	MOVF	r0x00, W
	BTFSC	STATUS, 2
	BRA	_00187_DS_
	.line	127; prueba.c	rxByte = usart_getc();
	CALL	_usart_getc
	MOVWF	r0x00
	.line	128; prueba.c	usart_putc(rxByte);
	MOVF	r0x00, W
	CALL	_usart_putc
	.line	130; prueba.c	switch (rxByte)
	MOVF	r0x00, W
	XORLW	0x20
	BZ	_00161_DS_
	MOVF	r0x00, W
	XORLW	0x58
	BNZ	_00228_DS_
	BRA	_00165_DS_
_00228_DS_:
	MOVF	r0x00, W
	XORLW	0x61
	BZ	_00162_DS_
	MOVF	r0x00, W
	XORLW	0x65
	BNZ	_00232_DS_
	BRA	_00164_DS_
_00232_DS_:
	MOVF	r0x00, W
	XORLW	0x7a
	BNZ	_00234_DS_
	BRA	_00163_DS_
_00234_DS_:
	BRA	_00187_DS_
_00161_DS_:
	BANKSEL	_checkEcho_bDebug_1_56
	.line	133; prueba.c	bDebug=!bDebug;
	MOVF	_checkEcho_bDebug_1_56, W, B
	BSF	STATUS, 0
	TSTFSZ	WREG
	BCF	STATUS, 0
	BANKSEL	_checkEcho_bDebug_1_56
	CLRF	_checkEcho_bDebug_1_56, B
	BANKSEL	_checkEcho_bDebug_1_56
	RLCF	_checkEcho_bDebug_1_56, F, B
	.line	134; prueba.c	printf ("\n\rDebug=%d ",bDebug);
	MOVFF	_checkEcho_bDebug_1_56, r0x00
	CLRF	r0x01
	BANKSEL	_checkEcho_bDebug_1_56
	BTFSC	_checkEcho_bDebug_1_56, 7, B
	SETF	r0x01
	MOVLW	UPPER(___str_0)
	MOVWF	r0x04
	MOVLW	HIGH(___str_0)
	MOVWF	r0x03
	MOVLW	LOW(___str_0)
	MOVWF	r0x02
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	MOVF	r0x03, W
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	CALL	_printf
	MOVLW	0x05
	ADDWF	FSR1L, F
	BANKSEL	_checkEcho_bDebug_1_56
	.line	135; prueba.c	setMotorsDebug (bDebug);
	MOVF	_checkEcho_bDebug_1_56, W, B
	MOVWF	POSTDEC1
	CALL	_setMotorsDebug
	MOVF	POSTINC1, F
	.line	136; prueba.c	break;
	BRA	_00187_DS_
_00162_DS_:
	BANKSEL	_velocidad
	.line	139; prueba.c	velocidad++;
	INCFSZ	_velocidad, F, B
	BRA	_10304_DS_
	BANKSEL	(_velocidad + 1)
	INCF	(_velocidad + 1), F, B
_10304_DS_:
	.line	140; prueba.c	motorSpeed (velocidad, MOTOR_1);
	MOVLW	0x00
	MOVWF	POSTDEC1
	BANKSEL	(_velocidad + 1)
	MOVF	(_velocidad + 1), W, B
	MOVWF	POSTDEC1
	BANKSEL	_velocidad
	MOVF	_velocidad, W, B
	MOVWF	POSTDEC1
	CALL	_motorSpeed
	MOVLW	0x03
	ADDWF	FSR1L, F
	.line	141; prueba.c	motorSpeed (velocidad, MOTOR_2);
	MOVLW	0x01
	MOVWF	POSTDEC1
	BANKSEL	(_velocidad + 1)
	MOVF	(_velocidad + 1), W, B
	MOVWF	POSTDEC1
	BANKSEL	_velocidad
	MOVF	_velocidad, W, B
	MOVWF	POSTDEC1
	CALL	_motorSpeed
	MOVLW	0x03
	ADDWF	FSR1L, F
	.line	142; prueba.c	break;
	BRA	_00187_DS_
_00163_DS_:
	.line	145; prueba.c	velocidad--;
	MOVLW	0xff
	BANKSEL	_velocidad
	ADDWF	_velocidad, F, B
	BANKSEL	(_velocidad + 1)
	ADDWFC	(_velocidad + 1), F, B
	.line	146; prueba.c	motorSpeed (velocidad, MOTOR_1);
	MOVLW	0x00
	MOVWF	POSTDEC1
	BANKSEL	(_velocidad + 1)
	MOVF	(_velocidad + 1), W, B
	MOVWF	POSTDEC1
	BANKSEL	_velocidad
	MOVF	_velocidad, W, B
	MOVWF	POSTDEC1
	CALL	_motorSpeed
	MOVLW	0x03
	ADDWF	FSR1L, F
	.line	147; prueba.c	motorSpeed (velocidad, MOTOR_2);
	MOVLW	0x01
	MOVWF	POSTDEC1
	BANKSEL	(_velocidad + 1)
	MOVF	(_velocidad + 1), W, B
	MOVWF	POSTDEC1
	BANKSEL	_velocidad
	MOVF	_velocidad, W, B
	MOVWF	POSTDEC1
	CALL	_motorSpeed
	MOVLW	0x03
	ADDWF	FSR1L, F
	.line	148; prueba.c	break;
	BRA	_00187_DS_
_00164_DS_:
	.line	151; prueba.c	antDebug=bDebug;
	MOVFF	_checkEcho_bDebug_1_56, _checkEcho_antDebug_1_56
	.line	152; prueba.c	setMotorsDebug (0);
	MOVLW	0x00
	MOVWF	POSTDEC1
	CALL	_setMotorsDebug
	MOVF	POSTINC1, F
	.line	153; prueba.c	printf ("\n\rEntre velocidad: ");
	MOVLW	UPPER(___str_1)
	MOVWF	r0x02
	MOVLW	HIGH(___str_1)
	MOVWF	r0x01
	MOVLW	LOW(___str_1)
	MOVWF	r0x00
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_printf
	MOVLW	0x03
	ADDWF	FSR1L, F
	.line	154; prueba.c	uart_GetString(buffer);
	MOVLW	HIGH(_checkEcho_buffer_1_56)
	MOVWF	r0x01
	MOVLW	LOW(_checkEcho_buffer_1_56)
	MOVWF	r0x00
	MOVLW	0x80
	MOVWF	r0x02
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_uart_GetString
	MOVLW	0x03
	ADDWF	FSR1L, F
	.line	155; prueba.c	velocidad = atoi (buffer);
	MOVLW	HIGH(_checkEcho_buffer_1_56)
	MOVWF	r0x01
	MOVLW	LOW(_checkEcho_buffer_1_56)
	MOVWF	r0x00
	MOVLW	0x80
	MOVWF	r0x02
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_atoi
	BANKSEL	_velocidad
	MOVWF	_velocidad, B
	MOVFF	PRODL, (_velocidad + 1)
	MOVLW	0x03
	ADDWF	FSR1L, F
	.line	156; prueba.c	printf ("\n\rVelocidad = %d",velocidad);
	MOVLW	UPPER(___str_2)
	MOVWF	r0x02
	MOVLW	HIGH(___str_2)
	MOVWF	r0x01
	MOVLW	LOW(___str_2)
	MOVWF	r0x00
	BANKSEL	(_velocidad + 1)
	MOVF	(_velocidad + 1), W, B
	MOVWF	POSTDEC1
	BANKSEL	_velocidad
	MOVF	_velocidad, W, B
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_printf
	MOVLW	0x05
	ADDWF	FSR1L, F
	.line	157; prueba.c	motorSpeed (velocidad, MOTOR_1);
	MOVLW	0x00
	MOVWF	POSTDEC1
	BANKSEL	(_velocidad + 1)
	MOVF	(_velocidad + 1), W, B
	MOVWF	POSTDEC1
	BANKSEL	_velocidad
	MOVF	_velocidad, W, B
	MOVWF	POSTDEC1
	CALL	_motorSpeed
	MOVLW	0x03
	ADDWF	FSR1L, F
	.line	158; prueba.c	motorSpeed (velocidad, MOTOR_2);
	MOVLW	0x01
	MOVWF	POSTDEC1
	BANKSEL	(_velocidad + 1)
	MOVF	(_velocidad + 1), W, B
	MOVWF	POSTDEC1
	BANKSEL	_velocidad
	MOVF	_velocidad, W, B
	MOVWF	POSTDEC1
	CALL	_motorSpeed
	MOVLW	0x03
	ADDWF	FSR1L, F
	BANKSEL	_checkEcho_antDebug_1_56
	.line	159; prueba.c	setMotorsDebug (antDebug);
	MOVF	_checkEcho_antDebug_1_56, W, B
	MOVWF	POSTDEC1
	CALL	_setMotorsDebug
	MOVF	POSTINC1, F
	.line	160; prueba.c	break;
	BRA	_00187_DS_
_00165_DS_:
	BANKSEL	_deviceState
	.line	163; prueba.c	if(deviceState == DETACHED)
	MOVF	_deviceState, W, B
	BNZ	_00182_DS_
	.line	164; prueba.c	printf("Detached\r\n");
	MOVLW	UPPER(___str_3)
	MOVWF	r0x02
	MOVLW	HIGH(___str_3)
	MOVWF	r0x01
	MOVLW	LOW(___str_3)
	MOVWF	r0x00
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_printf
	MOVLW	0x03
	ADDWF	FSR1L, F
	BRA	_00183_DS_
_00182_DS_:
	BANKSEL	_deviceState
	.line	165; prueba.c	else if(deviceState == ATTACHED)
	MOVF	_deviceState, W, B
	XORLW	0x01
	BNZ	_00179_DS_
	.line	166; prueba.c	printf("Attached\r\n");
	MOVLW	UPPER(___str_4)
	MOVWF	r0x02
	MOVLW	HIGH(___str_4)
	MOVWF	r0x01
	MOVLW	LOW(___str_4)
	MOVWF	r0x00
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_printf
	MOVLW	0x03
	ADDWF	FSR1L, F
	BRA	_00183_DS_
_00179_DS_:
	BANKSEL	_deviceState
	.line	167; prueba.c	else if(deviceState == POWERED)
	MOVF	_deviceState, W, B
	XORLW	0x02
	BNZ	_00176_DS_
	.line	168; prueba.c	printf("Powered\r\n");
	MOVLW	UPPER(___str_5)
	MOVWF	r0x02
	MOVLW	HIGH(___str_5)
	MOVWF	r0x01
	MOVLW	LOW(___str_5)
	MOVWF	r0x00
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_printf
	MOVLW	0x03
	ADDWF	FSR1L, F
	BRA	_00183_DS_
_00176_DS_:
	BANKSEL	_deviceState
	.line	169; prueba.c	else if(deviceState == DEFAULT)
	MOVF	_deviceState, W, B
	XORLW	0x03
	BNZ	_00173_DS_
	.line	170; prueba.c	printf("Default\r\n");
	MOVLW	UPPER(___str_6)
	MOVWF	r0x02
	MOVLW	HIGH(___str_6)
	MOVWF	r0x01
	MOVLW	LOW(___str_6)
	MOVWF	r0x00
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_printf
	MOVLW	0x03
	ADDWF	FSR1L, F
	BRA	_00183_DS_
_00173_DS_:
	BANKSEL	_deviceState
	.line	171; prueba.c	else if(deviceState == ADDRESS)
	MOVF	_deviceState, W, B
	XORLW	0x04
	BNZ	_00170_DS_
	.line	172; prueba.c	printf("Address\r\n");
	MOVLW	UPPER(___str_7)
	MOVWF	r0x02
	MOVLW	HIGH(___str_7)
	MOVWF	r0x01
	MOVLW	LOW(___str_7)
	MOVWF	r0x00
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_printf
	MOVLW	0x03
	ADDWF	FSR1L, F
	BRA	_00183_DS_
_00170_DS_:
	BANKSEL	_deviceState
	.line	173; prueba.c	else if(deviceState == CONFIGURED)
	MOVF	_deviceState, W, B
	XORLW	0x05
	BNZ	_00167_DS_
	.line	174; prueba.c	printf("Configured\r\n");
	MOVLW	UPPER(___str_8)
	MOVWF	r0x02
	MOVLW	HIGH(___str_8)
	MOVWF	r0x01
	MOVLW	LOW(___str_8)
	MOVWF	r0x00
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_printf
	MOVLW	0x03
	ADDWF	FSR1L, F
	BRA	_00183_DS_
_00167_DS_:
	.line	176; prueba.c	printf("Unknown state\r\n");
	MOVLW	UPPER(___str_9)
	MOVWF	r0x02
	MOVLW	HIGH(___str_9)
	MOVWF	r0x01
	MOVLW	LOW(___str_9)
	MOVWF	r0x00
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_printf
	MOVLW	0x03
	ADDWF	FSR1L, F
_00183_DS_:
	.line	178; prueba.c	printf("UCON: %x, UCFG: %x\r\n", UCON, UCFG);
	MOVFF	_UCFG, r0x00
	CLRF	r0x01
	MOVFF	_UCON, r0x02
	CLRF	r0x03
	MOVLW	UPPER(___str_10)
	MOVWF	r0x06
	MOVLW	HIGH(___str_10)
	MOVWF	r0x05
	MOVLW	LOW(___str_10)
	MOVWF	r0x04
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	MOVF	r0x03, W
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x06, W
	MOVWF	POSTDEC1
	MOVF	r0x05, W
	MOVWF	POSTDEC1
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	CALL	_printf
	MOVLW	0x07
	ADDWF	FSR1L, F
_00187_DS_:
	.line	181; prueba.c	}
	MOVFF	PREINC1, r0x06
	MOVFF	PREINC1, r0x05
	MOVFF	PREINC1, r0x04
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_prueba__initializeUSART	code
_initializeUSART:
	.line	90; prueba.c	static void initializeUSART(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	93; prueba.c	TRISC &= 0xBF; // Set RC6 as an output
	BCF	_TRISC, 6
	.line	94; prueba.c	TRISC |= 0x80; // Set RC7 as an input
	BSF	_TRISC, 7
	.line	95; prueba.c	RCSTA   = 0x90; // Enable serial port, enable receiver
	MOVLW	0x90
	MOVWF	_RCSTA
	.line	96; prueba.c	TXSTA   = 0x24; // Asynch, TSR empty, BRGH=1
	MOVLW	0x24
	MOVWF	_TXSTA
	.line	102; prueba.c	BAUDCON = 0x08; // BRG16=1
	MOVLW	0x08
	MOVWF	_BAUDCON
	.line	103; prueba.c	SPBRGH  = 0x00; // At 48MHz, SPBRGH=0, SPBRG=103 gives 115.2K Baud
	CLRF	_SPBRGH
	.line	105; prueba.c	SPBRG   = 103;  // For 48 MHz clock
	MOVLW	0x67
	MOVWF	_SPBRG
	BANKSEL	_stdin
	.line	111; prueba.c	stdin = STREAM_USART;
	CLRF	_stdin, B
	BANKSEL	(_stdin + 1)
	CLRF	(_stdin + 1), B
	MOVLW	0x20
	BANKSEL	(_stdin + 2)
	MOVWF	(_stdin + 2), B
	BANKSEL	_stdout
	.line	112; prueba.c	stdout = STREAM_USART;
	CLRF	_stdout, B
	BANKSEL	(_stdout + 1)
	CLRF	(_stdout + 1), B
	MOVLW	0x20
	BANKSEL	(_stdout + 2)
	MOVWF	(_stdout + 2), B
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_prueba__initializeTimer	code
_initializeTimer:
	.line	75; prueba.c	void initializeTimer(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	85; prueba.c	T0CON = 0xc3;      // assign prescaler to TMR0
	MOVLW	0xc3
	MOVWF	_T0CON
	.line	86; prueba.c	TMR0L = 99;
	MOVLW	0x63
	MOVWF	_TMR0L
	.line	87; prueba.c	INTCON = 0xa0;  // Enable TMRO interrupt
	MOVLW	0xa0
	MOVWF	_INTCON
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_prueba__uart_GetString	code
_uart_GetString:
	.line	54; prueba.c	int uart_GetString (char *str)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVFF	r0x05, POSTDEC1
	MOVFF	r0x06, POSTDEC1
	MOVFF	r0x07, POSTDEC1
	MOVFF	r0x08, POSTDEC1
	MOVFF	r0x09, POSTDEC1
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	MOVLW	0x04
	MOVFF	PLUSW2, r0x02
	.line	57; prueba.c	char *str_old = str;
	MOVFF	r0x00, r0x03
	MOVFF	r0x01, r0x04
	MOVFF	r0x02, r0x05
_00125_DS_:
	.line	58; prueba.c	while ( *(str-1)!=0x0d )
	MOVF	r0x00, W
	ADDLW	0xff
	MOVWF	r0x06
	MOVLW	0xff
	ADDWFC	r0x01, W
	MOVWF	r0x07
	MOVLW	0xff
	ADDWFC	r0x02, W
	MOVWF	r0x08
	MOVFF	r0x06, FSR0L
	MOVFF	r0x07, PRODL
	MOVF	r0x08, W
	CALL	__gptrget1
	MOVWF	r0x09
	MOVF	r0x09, W
	XORLW	0x0d
	BZ	_00127_DS_
	.line	60; prueba.c	if (usart_drdy())
	CALL	_usart_drdy
	MOVWF	r0x09
	MOVF	r0x09, W
	BZ	_00125_DS_
	.line	62; prueba.c	*str= usart_getc();
	CALL	_usart_getc
	MOVWF	r0x09
	MOVFF	r0x09, POSTDEC1
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, PRODL
	MOVF	r0x02, W
	CALL	__gptrput1
	.line	63; prueba.c	usart_putc (*str);
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, PRODL
	MOVF	r0x02, W
	CALL	__gptrget1
	MOVWF	r0x09
	MOVF	r0x09, W
	CALL	_usart_putc
	.line	65; prueba.c	if (*str==0x08)
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, PRODL
	MOVF	r0x02, W
	CALL	__gptrget1
	MOVWF	r0x09
	MOVF	r0x09, W
	XORLW	0x08
	BNZ	_00121_DS_
	.line	66; prueba.c	str--;
	MOVFF	r0x06, r0x00
	MOVFF	r0x07, r0x01
	MOVFF	r0x08, r0x02
	BRA	_00125_DS_
_00121_DS_:
	.line	68; prueba.c	str++;
	INCF	r0x00, F
	BNC	_00146_DS_
	INFSNZ	r0x01, F
	INCF	r0x02, F
_00146_DS_:
	BRA	_00125_DS_
_00127_DS_:
	.line	71; prueba.c	*str=0;
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, PRODL
	MOVF	r0x02, W
	CALL	__gptrput1
	.line	72; prueba.c	return (str-str_old);
	MOVF	r0x03, W
	SUBWF	r0x00, F
	MOVF	r0x04, W
	SUBWFB	r0x01, F
	MOVFF	r0x01, PRODL
	MOVF	r0x00, W
	MOVFF	PREINC1, r0x09
	MOVFF	PREINC1, r0x08
	MOVFF	PREINC1, r0x07
	MOVFF	PREINC1, r0x06
	MOVFF	PREINC1, r0x05
	MOVFF	PREINC1, r0x04
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
___str_0:
	DB	0x0a, 0x0d, 0x44, 0x65, 0x62, 0x75, 0x67, 0x3d, 0x25, 0x64, 0x20, 0x00
; ; Starting pCode block
___str_1:
	DB	0x0a, 0x0d, 0x45, 0x6e, 0x74, 0x72, 0x65, 0x20, 0x76, 0x65, 0x6c, 0x6f
	DB	0x63, 0x69, 0x64, 0x61, 0x64, 0x3a, 0x20, 0x00
; ; Starting pCode block
___str_2:
	DB	0x0a, 0x0d, 0x56, 0x65, 0x6c, 0x6f, 0x63, 0x69, 0x64, 0x61, 0x64, 0x20
	DB	0x3d, 0x20, 0x25, 0x64, 0x00
; ; Starting pCode block
___str_3:
	DB	0x44, 0x65, 0x74, 0x61, 0x63, 0x68, 0x65, 0x64, 0x0d, 0x0a, 0x00
; ; Starting pCode block
___str_4:
	DB	0x41, 0x74, 0x74, 0x61, 0x63, 0x68, 0x65, 0x64, 0x0d, 0x0a, 0x00
; ; Starting pCode block
___str_5:
	DB	0x50, 0x6f, 0x77, 0x65, 0x72, 0x65, 0x64, 0x0d, 0x0a, 0x00
; ; Starting pCode block
___str_6:
	DB	0x44, 0x65, 0x66, 0x61, 0x75, 0x6c, 0x74, 0x0d, 0x0a, 0x00
; ; Starting pCode block
___str_7:
	DB	0x41, 0x64, 0x64, 0x72, 0x65, 0x73, 0x73, 0x0d, 0x0a, 0x00
; ; Starting pCode block
___str_8:
	DB	0x43, 0x6f, 0x6e, 0x66, 0x69, 0x67, 0x75, 0x72, 0x65, 0x64, 0x0d, 0x0a
	DB	0x00
; ; Starting pCode block
___str_9:
	DB	0x55, 0x6e, 0x6b, 0x6e, 0x6f, 0x77, 0x6e, 0x20, 0x73, 0x74, 0x61, 0x74
	DB	0x65, 0x0d, 0x0a, 0x00
; ; Starting pCode block
___str_10:
	DB	0x55, 0x43, 0x4f, 0x4e, 0x3a, 0x20, 0x25, 0x78, 0x2c, 0x20, 0x55, 0x43
	DB	0x46, 0x47, 0x3a, 0x20, 0x25, 0x78, 0x0d, 0x0a, 0x00
; ; Starting pCode block
___str_11:
	DB	0x53, 0x65, 0x74, 0x75, 0x70, 0x46, 0x65, 0x61, 0x74, 0x75, 0x72, 0x65
	DB	0x52, 0x65, 0x70, 0x6f, 0x72, 0x74, 0x0a, 0x0d, 0x00
; ; Starting pCode block
___str_12:
	DB	0x50, 0x49, 0x43, 0x20, 0x54, 0x65, 0x73, 0x74, 0x0d, 0x0a, 0x00
; ; Starting pCode block
___str_13:
	DB	0x6c, 0x6f, 0x6e, 0x67, 0x20, 0x3d, 0x20, 0x25, 0x64, 0x0a, 0x0d, 0x00


; Statistics:
; code size:	 2304 (0x0900) bytes ( 1.76%)
;           	 1152 (0x0480) words
; udata size:	  177 (0x00b1) bytes ( 9.88%)
; access size:	   10 (0x000a) bytes


	end
