;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.4.0 #8981 (Apr  5 2014) (Linux)
; This file was generated Mon Sep  1 01:28:48 2014
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------

	.ident "SDCC version 3.4.0 #8981 [pic16 port]"
	.file	"usb.c"
	list	p=18f4455
	radix	dec


;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global	_deviceAddress
	global	_HIDTxReport
	global	_HIDRxReport
	global	_EnableUSBModule
	global	_ProcessUSBTransactions
	global	_deviceState
	global	_remoteWakeup
	global	_selfPowered
	global	_currentConfiguration
	global	_ctrlTransferStage
	global	_HIDPostProcess
	global	_requestHandled
	global	_outPtr
	global	_inPtr
	global	_wCount
	global	_hidIdleRate
	global	_hidProtocol
	global	_hidRxLen
	global	_ep0Bo
	global	_ep0Bi
	global	_ep1Bo
	global	_ep1Bi
	global	_SetupPacket
	global	_controlTransferBuffer
	global	_HIDRxBuffer
	global	_HIDTxBuffer
	global	_HIDInitEndpoint
	global	_HIDGetReport
	global	_HIDSetReport
	global	_ProcessHIDRequest
	global	_ProcessStandardRequest
	global	_InDataStage
	global	_OutDataStage
	global	_SetupStage
	global	_WaitForSetupStage
	global	_ProcessControlTransfer
	global	_UnSuspend
	global	_StartOfFrame
	global	_Stall
	global	_Suspend
	global	_BusReset
	global	_deviceDescriptor
	global	_configDescriptor
	global	_HIDReport
	global	_stringDescriptor0
	global	_stringDescriptor1
	global	_stringDescriptor2
	global	_dataEEPROM

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
	extern	_GetInputReport
	extern	_SetupOutputReport
	extern	_SetOutputReport
	extern	_GetFeatureReport
	extern	_SetupFeatureReport
	extern	_SetFeatureReport

;--------------------------------------------------------
;	Equates to used internal registers
;--------------------------------------------------------
STATUS	equ	0xfd8
WREG	equ	0xfe8
FSR0L	equ	0xfe9
FSR0H	equ	0xfea
FSR1L	equ	0xfe1
FSR2L	equ	0xfd9
INDF0	equ	0xfef
POSTINC1	equ	0xfe6
POSTDEC1	equ	0xfe5
PREINC1	equ	0xfe4
PLUSW2	equ	0xfdb
PRODL	equ	0xff3
PRODH	equ	0xff4


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


usbram5	udata
_HIDTxBuffer	res	32
_HIDRxBuffer	res	32
_SetupPacket	res	64
_controlTransferBuffer	res	32

udata_usb_0	udata
_deviceAddress	res	1

udata_usb_1	udata
_hidRxLen	res	1

udata_usb_2	udata
_requestHandled	res	1

udata_usb_3	udata
_outPtr	res	3

udata_usb_4	udata
_wCount	res	2

udata_usb_5	udata
_HIDPostProcess	res	1

udata_usb_6	udata
_hidIdleRate	res	1

udata_usb_7	udata
_hidProtocol	res	1

udata_usb_8	udata
_inPtr	res	3

udata_usb_9	udata
_selfPowered	res	1

udata_usb_10	udata
_remoteWakeup	res	1

udata_usb_11	udata
_deviceState	res	1

udata_usb_12	udata
_currentConfiguration	res	1

udata_usb_13	udata
_ctrlTransferStage	res	1


ustat_usb_00	udata	0X0400
_ep0Bo         	res	4
_ep0Bi         	res	4
_ep1Bo         	res	4
_ep1Bi         	res	4

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; ; Starting pCode block for absolute Ival
S_usb__dataEEPROM	code	0XF00000
_dataEEPROM:
	DB	0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x03, 0x00, 0x04, 0x00, 0x05, 0x00
	DB	0x06, 0x00, 0x07, 0x00, 0x30, 0x00, 0x31, 0x00, 0x32, 0x00, 0x33, 0x00
	DB	0x34, 0x00, 0x35, 0x00, 0x36, 0x00, 0x37, 0x00, 0x38, 0x00, 0x39, 0x00
	DB	0x61, 0x00, 0x62, 0x00, 0x63, 0x00, 0x64, 0x00, 0x65, 0x00, 0x66, 0x00

; I code from now on!
; ; Starting pCode block
S_usb__ProcessUSBTransactions	code
_ProcessUSBTransactions:
	.line	1109; usb.c	void ProcessUSBTransactions(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	BANKSEL	_deviceState
	.line	1113; usb.c	if(deviceState == DETACHED)
	MOVF	_deviceState, W, B
	.line	1114; usb.c	return;
	BZ	_00863_DS_
	.line	1117; usb.c	if(UIRbits.ACTVIF && UIEbits.ACTVIE)
	BTFSS	_UIRbits, 2
	BRA	_00839_DS_
	BTFSS	_UIEbits, 2
	BRA	_00839_DS_
	.line	1118; usb.c	UnSuspend();
	CALL	_UnSuspend
_00839_DS_:
	.line	1122; usb.c	if(UCONbits.SUSPND == 1)
	CLRF	r0x00
	BTFSC	_UCONbits, 1
	INCF	r0x00, F
	MOVF	r0x00, W
	XORLW	0x01
	.line	1123; usb.c	return;
	BZ	_00863_DS_
	.line	1126; usb.c	if (UIRbits.URSTIF && UIEbits.URSTIE)
	BTFSS	_UIRbits, 0
	BRA	_00844_DS_
	BTFSS	_UIEbits, 0
	BRA	_00844_DS_
	.line	1128; usb.c	BusReset();
	CALL	_BusReset
_00844_DS_:
	.line	1131; usb.c	if (UIRbits.IDLEIF && UIEbits.IDLEIE)
	BTFSS	_UIRbits, 4
	BRA	_00847_DS_
	BTFSS	_UIEbits, 4
	BRA	_00847_DS_
	.line	1134; usb.c	Suspend();
	CALL	_Suspend
_00847_DS_:
	.line	1136; usb.c	if (UIRbits.SOFIF && UIEbits.SOFIE)
	BTFSS	_UIRbits, 6
	BRA	_00850_DS_
	BTFSS	_UIEbits, 6
	BRA	_00850_DS_
	.line	1138; usb.c	StartOfFrame();
	CALL	_StartOfFrame
_00850_DS_:
	.line	1140; usb.c	if (UIRbits.STALLIF && UIEbits.STALLIE)
	BTFSS	_UIRbits, 5
	BRA	_00853_DS_
	BTFSS	_UIEbits, 5
	BRA	_00853_DS_
	.line	1142; usb.c	Stall();
	CALL	_Stall
_00853_DS_:
	.line	1145; usb.c	if (UIRbits.UERRIF && UIEbits.UERRIE)
	BTFSS	_UIRbits, 1
	BRA	_00856_DS_
	BTFSS	_UIEbits, 1
	BRA	_00856_DS_
	.line	1150; usb.c	UIRbits.UERRIF = 0;
	BCF	_UIRbits, 1
_00856_DS_:
	.line	1154; usb.c	if (deviceState < DEFAULT)
	MOVLW	0x03
	BANKSEL	_deviceState
	SUBWF	_deviceState, W, B
	.line	1155; usb.c	return;
	BNC	_00863_DS_
	.line	1158; usb.c	if(UIRbits.TRNIF && UIEbits.TRNIE)
	BTFSS	_UIRbits, 3
	BRA	_00863_DS_
	BTFSS	_UIEbits, 3
	BRA	_00863_DS_
	.line	1160; usb.c	ProcessControlTransfer();
	CALL	_ProcessControlTransfer
	.line	1163; usb.c	UIRbits.TRNIF = 0;
	BCF	_UIRbits, 3
_00863_DS_:
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb__BusReset	code
_BusReset:
	.line	1081; usb.c	void BusReset()
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	.line	1083; usb.c	UEIR  = 0x00;
	CLRF	_UEIR
	.line	1084; usb.c	UIR   = 0x00;
	CLRF	_UIR
	.line	1085; usb.c	UEIE  = 0x9f;
	MOVLW	0x9f
	MOVWF	_UEIE
	.line	1086; usb.c	UIE   = 0x7b;
	MOVLW	0x7b
	MOVWF	_UIE
	.line	1087; usb.c	UADDR = 0x00;
	CLRF	_UADDR
	.line	1090; usb.c	UEP0 = 0x16;
	MOVLW	0x16
	MOVWF	_UEP0
_00819_DS_:
	.line	1093; usb.c	while (UIRbits.TRNIF == 1)
	CLRF	r0x00
	BTFSC	_UIRbits, 3
	INCF	r0x00, F
	MOVF	r0x00, W
	XORLW	0x01
	BNZ	_00821_DS_
	.line	1094; usb.c	UIRbits.TRNIF = 0;
	BCF	_UIRbits, 3
	BRA	_00819_DS_
_00821_DS_:
	.line	1097; usb.c	UCONbits.PKTDIS = 0;
	BCF	_UCONbits, 4
	.line	1100; usb.c	WaitForSetupStage();
	CALL	_WaitForSetupStage
	BANKSEL	_remoteWakeup
	.line	1102; usb.c	remoteWakeup = 0;         // Remote wakeup is off by default
	CLRF	_remoteWakeup, B
	BANKSEL	_selfPowered
	.line	1103; usb.c	selfPowered = 0;          // Self powered is off by default
	CLRF	_selfPowered, B
	BANKSEL	_currentConfiguration
	.line	1104; usb.c	currentConfiguration = 0; // Clear active configuration
	CLRF	_currentConfiguration, B
	.line	1105; usb.c	deviceState = DEFAULT;
	MOVLW	0x03
	BANKSEL	_deviceState
	MOVWF	_deviceState, B
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb__Suspend	code
_Suspend:
	.line	1051; usb.c	void Suspend(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	1079; usb.c	}
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb__Stall	code
_Stall:
	.line	1036; usb.c	void Stall(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	.line	1041; usb.c	if(UEP0bits.EPSTALL == 1)
	CLRF	r0x00
	BTFSC	_UEP0bits, 0
	INCF	r0x00, F
	MOVF	r0x00, W
	XORLW	0x01
	BNZ	_00802_DS_
	.line	1044; usb.c	WaitForSetupStage();
	CALL	_WaitForSetupStage
	.line	1045; usb.c	UEP0bits.EPSTALL = 0;
	BCF	_UEP0bits, 0
_00802_DS_:
	.line	1047; usb.c	UIRbits.STALLIF = 0;
	BCF	_UIRbits, 5
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb__StartOfFrame	code
_StartOfFrame:
	.line	1029; usb.c	void StartOfFrame(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	1032; usb.c	UIRbits.SOFIF = 0;
	BCF	_UIRbits, 6
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb__UnSuspend	code
_UnSuspend:
	.line	1016; usb.c	void UnSuspend(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	1022; usb.c	UCONbits.SUSPND = 0;
	BCF	_UCONbits, 1
	.line	1023; usb.c	UIEbits.ACTVIE = 0;
	BCF	_UIEbits, 2
	.line	1024; usb.c	UIRbits.ACTVIF = 0;
	BCF	_UIRbits, 2
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb__EnableUSBModule	code
_EnableUSBModule:
	.line	983; usb.c	void EnableUSBModule(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	.line	987; usb.c	if(UCONbits.USBEN == 0)
	BTFSC	_UCONbits, 3
	BRA	_00770_DS_
	.line	992; usb.c	UCON = 0;
	CLRF	_UCON
	.line	993; usb.c	UIE = 0;
	CLRF	_UIE
	.line	994; usb.c	UCFGbits.UPUEN=1;
	BSF	_UCFGbits, 4
	.line	995; usb.c	UCFGbits.FSEN=1;
	BSF	_UCFGbits, 2
	.line	996; usb.c	UCONbits.USBEN = 1;
	BSF	_UCONbits, 3
	.line	997; usb.c	deviceState = ATTACHED;
	MOVLW	0x01
	BANKSEL	_deviceState
	MOVWF	_deviceState, B
_00770_DS_:
	BANKSEL	_deviceState
	.line	1002; usb.c	if ((deviceState == ATTACHED) && !UCONbits.SE0)
	MOVF	_deviceState, W, B
	XORLW	0x01
	BNZ	_00774_DS_
	BTFSC	_UCONbits, 5
	BRA	_00774_DS_
	.line	1004; usb.c	UIR = 0;
	CLRF	_UIR
	.line	1005; usb.c	UIE = 0;
	CLRF	_UIE
	.line	1006; usb.c	UIEbits.URSTIE = 1;
	BSF	_UIEbits, 0
	.line	1007; usb.c	UIEbits.IDLEIE = 1;
	BSF	_UIEbits, 4
	.line	1008; usb.c	deviceState = POWERED;
	MOVLW	0x02
	BANKSEL	_deviceState
	MOVWF	_deviceState, B
_00774_DS_:
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb__ProcessControlTransfer	code
_ProcessControlTransfer:
	.line	885; usb.c	void ProcessControlTransfer(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	.line	890; usb.c	if (USTAT == 0)
	MOVF	_USTAT, W
	BTFSS	STATUS, 2
	BRA	_00705_DS_
	.line	893; usb.c	byte PID = (ep0Bo.Stat & 0x3C) >> 2; // Pull PID from middle of BD0STAT
	MOVLW	0x3c
	BANKSEL	_ep0Bo
	ANDWF	_ep0Bo, W, B
	MOVWF	r0x00
	RRNCF	r0x00, W
	RRNCF	WREG, W
	ANDLW	0x3f
	MOVWF	r0x00
	.line	894; usb.c	if (PID == 0x0D)
	MOVF	r0x00, W
	XORLW	0x0d
	BNZ	_00689_DS_
	.line	896; usb.c	SetupStage();
	CALL	_SetupStage
	BRA	_00707_DS_
_00689_DS_:
	BANKSEL	_ctrlTransferStage
	.line	897; usb.c	else if (ctrlTransferStage == DATA_OUT_STAGE)
	MOVF	_ctrlTransferStage, W, B
	XORLW	0x01
	BNZ	_00686_DS_
	.line	901; usb.c	OutDataStage();
	CALL	_OutDataStage
	BANKSEL	_HIDPostProcess
	.line	905; usb.c	if (HIDPostProcess)
	MOVF	_HIDPostProcess, W, B
	BZ	_00681_DS_
	.line	908; usb.c	byte reportID = SetupPacket.wValue0;
	MOVFF	(_SetupPacket + 2), r0x00
	BANKSEL	(_SetupPacket + 3)
	.line	912; usb.c	if (SetupPacket.wValue1 == 0x02)
	MOVF	(_SetupPacket + 3), W, B
	XORLW	0x02
	BNZ	_00678_DS_
	.line	915; usb.c	SetOutputReport(reportID);
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_SetOutputReport
	MOVF	POSTINC1, F
	BRA	_00681_DS_
_00678_DS_:
	BANKSEL	(_SetupPacket + 3)
	.line	917; usb.c	else if (SetupPacket.wValue1 == 0x03)
	MOVF	(_SetupPacket + 3), W, B
	XORLW	0x03
	BNZ	_00681_DS_
	.line	920; usb.c	SetFeatureReport(reportID);
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_SetFeatureReport
	MOVF	POSTINC1, F
_00681_DS_:
	BANKSEL	_ep0Bo
	.line	929; usb.c	if(ep0Bo.Stat & DTS)
	BTFSS	_ep0Bo, 6, B
	BRA	_00683_DS_
	.line	930; usb.c	ep0Bo.Stat = UOWN | DTSEN;
	MOVLW	0x88
	BANKSEL	_ep0Bo
	MOVWF	_ep0Bo, B
	BRA	_00707_DS_
_00683_DS_:
	.line	932; usb.c	ep0Bo.Stat = UOWN | DTS | DTSEN;
	MOVLW	0xc8
	BANKSEL	_ep0Bo
	MOVWF	_ep0Bo, B
	BRA	_00707_DS_
_00686_DS_:
	.line	937; usb.c	WaitForSetupStage();
	CALL	_WaitForSetupStage
	BRA	_00707_DS_
_00705_DS_:
	.line	940; usb.c	else if(USTAT == 0x04)
	MOVF	_USTAT, W
	XORLW	0x04
	BNZ	_00707_DS_
	.line	943; usb.c	if ((UADDR == 0) && (deviceState == ADDRESS))
	MOVF	_UADDR, W
	BNZ	_00694_DS_
	BANKSEL	_deviceState
	MOVF	_deviceState, W, B
	XORLW	0x04
	BNZ	_00694_DS_
	.line	947; usb.c	UADDR = SetupPacket.wValue0;
	MOVFF	(_SetupPacket + 2), _UADDR
	.line	951; usb.c	if(UADDR == 0)
	MOVF	_UADDR, W
	BNZ	_00694_DS_
	.line	954; usb.c	deviceState = DEFAULT;
	MOVLW	0x03
	BANKSEL	_deviceState
	MOVWF	_deviceState, B
_00694_DS_:
	BANKSEL	_ctrlTransferStage
	.line	957; usb.c	if (ctrlTransferStage == DATA_IN_STAGE)
	MOVF	_ctrlTransferStage, W, B
	XORLW	0x02
	BNZ	_00700_DS_
	.line	960; usb.c	InDataStage();
	CALL	_InDataStage
	BANKSEL	_ep0Bi
	.line	963; usb.c	if(ep0Bi.Stat & DTS)
	BTFSS	_ep0Bi, 6, B
	BRA	_00697_DS_
	.line	964; usb.c	ep0Bi.Stat = UOWN | DTSEN;
	MOVLW	0x88
	BANKSEL	_ep0Bi
	MOVWF	_ep0Bi, B
	BRA	_00707_DS_
_00697_DS_:
	.line	966; usb.c	ep0Bi.Stat = UOWN | DTS | DTSEN;
	MOVLW	0xc8
	BANKSEL	_ep0Bi
	MOVWF	_ep0Bi, B
	BRA	_00707_DS_
_00700_DS_:
	.line	971; usb.c	WaitForSetupStage();
	CALL	_WaitForSetupStage
_00707_DS_:
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb__WaitForSetupStage	code
_WaitForSetupStage:
	.line	872; usb.c	void WaitForSetupStage(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	BANKSEL	_ctrlTransferStage
	.line	874; usb.c	ctrlTransferStage = SETUP_STAGE;
	CLRF	_ctrlTransferStage, B
	.line	875; usb.c	ep0Bo.Cnt = E0SZ;
	MOVLW	0x20
	BANKSEL	(_ep0Bo + 1)
	MOVWF	(_ep0Bo + 1), B
	.line	876; usb.c	ep0Bo.ADDR = PTR16(&SetupPacket);
	MOVLW	LOW(_SetupPacket)
	MOVWF	r0x00
	MOVLW	HIGH(_SetupPacket)
	MOVWF	r0x01
	CLRF	r0x02
	CLRF	r0x03
	CLRF	r0x02
	CLRF	r0x03
	MOVF	r0x00, W
	BANKSEL	(_ep0Bo + 2)
	MOVWF	(_ep0Bo + 2), B
	MOVF	r0x01, W
	BANKSEL	(_ep0Bo + 3)
	MOVWF	(_ep0Bo + 3), B
	.line	877; usb.c	ep0Bo.Stat = UOWN | DTSEN; // Give to SIE, enable data toggle checks
	MOVLW	0x88
	BANKSEL	_ep0Bo
	MOVWF	_ep0Bo, B
	BANKSEL	_ep0Bi
	.line	878; usb.c	ep0Bi.Stat = 0x00;         // Give control to CPU
	CLRF	_ep0Bi, B
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb__SetupStage	code
_SetupStage:
	.line	804; usb.c	void SetupStage(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	BANKSEL	_ep0Bi
	.line	808; usb.c	ep0Bi.Stat &= ~UOWN;
	MOVF	_ep0Bi, W, B
	MOVWF	r0x00
	BCF	r0x00, 7
	MOVF	r0x00, W
	BANKSEL	_ep0Bi
	MOVWF	_ep0Bi, B
	BANKSEL	_ep0Bo
	.line	809; usb.c	ep0Bo.Stat &= ~UOWN;
	MOVF	_ep0Bo, W, B
	MOVWF	r0x00
	BCF	r0x00, 7
	MOVF	r0x00, W
	BANKSEL	_ep0Bo
	MOVWF	_ep0Bo, B
	BANKSEL	_ctrlTransferStage
	.line	812; usb.c	ctrlTransferStage = SETUP_STAGE;
	CLRF	_ctrlTransferStage, B
	BANKSEL	_requestHandled
	.line	813; usb.c	requestHandled = 0; // Default is that request hasn't been handled
	CLRF	_requestHandled, B
	BANKSEL	_HIDPostProcess
	.line	814; usb.c	HIDPostProcess = 0; // Assume standard request until know otherwise
	CLRF	_HIDPostProcess, B
	BANKSEL	_wCount
	.line	815; usb.c	wCount = 0;         // No bytes transferred
	CLRF	_wCount, B
	BANKSEL	(_wCount + 1)
	CLRF	(_wCount + 1), B
	.line	818; usb.c	ProcessStandardRequest();
	CALL	_ProcessStandardRequest
	.line	821; usb.c	ProcessHIDRequest();
	CALL	_ProcessHIDRequest
	BANKSEL	_requestHandled
	.line	825; usb.c	if (!requestHandled)
	MOVF	_requestHandled, W, B
	BNZ	_00648_DS_
	.line	828; usb.c	ep0Bo.Cnt = E0SZ;
	MOVLW	0x20
	BANKSEL	(_ep0Bo + 1)
	MOVWF	(_ep0Bo + 1), B
	.line	829; usb.c	ep0Bo.ADDR = PTR16(&SetupPacket);
	MOVLW	LOW(_SetupPacket)
	MOVWF	r0x00
	MOVLW	HIGH(_SetupPacket)
	MOVWF	r0x01
	CLRF	r0x02
	CLRF	r0x03
	CLRF	r0x02
	CLRF	r0x03
	MOVF	r0x00, W
	BANKSEL	(_ep0Bo + 2)
	MOVWF	(_ep0Bo + 2), B
	MOVF	r0x01, W
	BANKSEL	(_ep0Bo + 3)
	MOVWF	(_ep0Bo + 3), B
	.line	830; usb.c	ep0Bo.Stat = UOWN | BSTALL;
	MOVLW	0x84
	BANKSEL	_ep0Bo
	MOVWF	_ep0Bo, B
	.line	831; usb.c	ep0Bi.Stat = UOWN | BSTALL;
	MOVLW	0x84
	BANKSEL	_ep0Bi
	MOVWF	_ep0Bi, B
	BRA	_00649_DS_
_00648_DS_:
	BANKSEL	_SetupPacket
	.line	833; usb.c	else if (SetupPacket.bmRequestType & 0x80)
	BTFSS	_SetupPacket, 7, B
	BRA	_00645_DS_
	BANKSEL	(_wCount + 1)
	.line	836; usb.c	if(SetupPacket.wLength < wCount)
	MOVF	(_wCount + 1), W, B
	BANKSEL	(_SetupPacket + 7)
	SUBWF	(_SetupPacket + 7), W, B
	BNZ	_00665_DS_
	BANKSEL	_wCount
	MOVF	_wCount, W, B
	BANKSEL	(_SetupPacket + 6)
	SUBWF	(_SetupPacket + 6), W, B
_00665_DS_:
	BC	_00643_DS_
	.line	837; usb.c	wCount = SetupPacket.wLength;
	MOVFF	(_SetupPacket + 6), _wCount
	MOVFF	(_SetupPacket + 7), (_wCount + 1)
_00643_DS_:
	.line	838; usb.c	InDataStage();
	CALL	_InDataStage
	.line	839; usb.c	ctrlTransferStage = DATA_IN_STAGE;
	MOVLW	0x02
	BANKSEL	_ctrlTransferStage
	MOVWF	_ctrlTransferStage, B
	.line	841; usb.c	ep0Bo.Cnt = E0SZ;
	MOVLW	0x20
	BANKSEL	(_ep0Bo + 1)
	MOVWF	(_ep0Bo + 1), B
	.line	842; usb.c	ep0Bo.ADDR = PTR16(&SetupPacket);
	MOVLW	LOW(_SetupPacket)
	MOVWF	r0x00
	MOVLW	HIGH(_SetupPacket)
	MOVWF	r0x01
	CLRF	r0x02
	CLRF	r0x03
	CLRF	r0x02
	CLRF	r0x03
	MOVF	r0x00, W
	BANKSEL	(_ep0Bo + 2)
	MOVWF	(_ep0Bo + 2), B
	MOVF	r0x01, W
	BANKSEL	(_ep0Bo + 3)
	MOVWF	(_ep0Bo + 3), B
	.line	843; usb.c	ep0Bo.Stat = UOWN;
	MOVLW	0x80
	BANKSEL	_ep0Bo
	MOVWF	_ep0Bo, B
	.line	846; usb.c	ep0Bi.ADDR = PTR16(&controlTransferBuffer);
	MOVLW	LOW(_controlTransferBuffer)
	MOVWF	r0x00
	MOVLW	HIGH(_controlTransferBuffer)
	MOVWF	r0x01
	CLRF	r0x02
	CLRF	r0x03
	CLRF	r0x02
	CLRF	r0x03
	MOVF	r0x00, W
	BANKSEL	(_ep0Bi + 2)
	MOVWF	(_ep0Bi + 2), B
	MOVF	r0x01, W
	BANKSEL	(_ep0Bi + 3)
	MOVWF	(_ep0Bi + 3), B
	.line	848; usb.c	ep0Bi.Stat = UOWN | DTS | DTSEN; 
	MOVLW	0xc8
	BANKSEL	_ep0Bi
	MOVWF	_ep0Bi, B
	BRA	_00649_DS_
_00645_DS_:
	.line	853; usb.c	ctrlTransferStage = DATA_OUT_STAGE;
	MOVLW	0x01
	BANKSEL	_ctrlTransferStage
	MOVWF	_ctrlTransferStage, B
	BANKSEL	(_ep0Bi + 1)
	.line	856; usb.c	ep0Bi.Cnt = 0;
	CLRF	(_ep0Bi + 1), B
	.line	857; usb.c	ep0Bi.Stat = UOWN | DTS | DTSEN;
	MOVLW	0xc8
	BANKSEL	_ep0Bi
	MOVWF	_ep0Bi, B
	.line	860; usb.c	ep0Bo.Cnt = E0SZ;
	MOVLW	0x20
	BANKSEL	(_ep0Bo + 1)
	MOVWF	(_ep0Bo + 1), B
	.line	861; usb.c	ep0Bo.ADDR = PTR16(&controlTransferBuffer);
	MOVLW	LOW(_controlTransferBuffer)
	MOVWF	r0x00
	MOVLW	HIGH(_controlTransferBuffer)
	MOVWF	r0x01
	CLRF	r0x02
	CLRF	r0x03
	CLRF	r0x02
	CLRF	r0x03
	MOVF	r0x00, W
	BANKSEL	(_ep0Bo + 2)
	MOVWF	(_ep0Bo + 2), B
	MOVF	r0x01, W
	BANKSEL	(_ep0Bo + 3)
	MOVWF	(_ep0Bo + 3), B
	.line	863; usb.c	ep0Bo.Stat = UOWN | DTS | DTSEN;
	MOVLW	0xc8
	BANKSEL	_ep0Bo
	MOVWF	_ep0Bo, B
_00649_DS_:
	.line	867; usb.c	UCONbits.PKTDIS = 0;
	BCF	_UCONbits, 4
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb__OutDataStage	code
_OutDataStage:
	.line	771; usb.c	void OutDataStage(void)
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
	.line	775; usb.c	bufferSize = ((0x03 & ep0Bo.Stat) << 8) | ep0Bo.Cnt;
	MOVLW	0x03
	BANKSEL	_ep0Bo
	ANDWF	_ep0Bo, W, B
	MOVWF	r0x00
	CLRF	r0x01
	MOVF	r0x00, W
	MOVWF	r0x03
	CLRF	r0x02
	MOVFF	(_ep0Bo + 1), r0x00
	CLRF	r0x01
	MOVF	r0x02, W
	IORWF	r0x00, F
	MOVF	r0x03, W
	IORWF	r0x01, F
	.line	782; usb.c	wCount = wCount + bufferSize;
	MOVF	r0x00, W
	BANKSEL	_wCount
	ADDWF	_wCount, F, B
	MOVF	r0x01, W
	BANKSEL	(_wCount + 1)
	ADDWFC	(_wCount + 1), F, B
	.line	784; usb.c	outPtr = (byte*)&controlTransferBuffer;
	MOVLW	HIGH(_controlTransferBuffer)
	BANKSEL	(_outPtr + 1)
	MOVWF	(_outPtr + 1), B
	MOVLW	LOW(_controlTransferBuffer)
	BANKSEL	_outPtr
	MOVWF	_outPtr, B
	MOVLW	0x80
	BANKSEL	(_outPtr + 2)
	MOVWF	(_outPtr + 2), B
	.line	788; usb.c	for (i=0;i<bufferSize;i++)
	CLRF	r0x02
	CLRF	r0x03
_00622_DS_:
	MOVF	r0x01, W
	SUBWF	r0x03, W
	BNZ	_00635_DS_
	MOVF	r0x00, W
	SUBWF	r0x02, W
_00635_DS_:
	BC	_00624_DS_
	.line	793; usb.c	*inPtr++ = *outPtr++;
	MOVFF	_inPtr, r0x04
	MOVFF	(_inPtr + 1), r0x05
	MOVFF	(_inPtr + 2), r0x06
	MOVFF	_outPtr, r0x07
	MOVFF	(_outPtr + 1), r0x08
	MOVFF	(_outPtr + 2), r0x09
	MOVFF	r0x07, FSR0L
	MOVFF	r0x08, PRODL
	MOVF	r0x09, W
	CALL	__gptrget1
	MOVWF	r0x07
	BANKSEL	_outPtr
	INCF	_outPtr, F, B
	BNC	_00636_DS_
	BANKSEL	(_outPtr + 1)
	INCFSZ	(_outPtr + 1), F, B
	BRA	_10836_DS_
	BANKSEL	(_outPtr + 2)
	INCF	(_outPtr + 2), F, B
_10836_DS_:
_00636_DS_:
	MOVFF	r0x07, POSTDEC1
	MOVFF	r0x04, FSR0L
	MOVFF	r0x05, PRODL
	MOVF	r0x06, W
	CALL	__gptrput1
	BANKSEL	_inPtr
	INCF	_inPtr, F, B
	BNC	_00637_DS_
	BANKSEL	(_inPtr + 1)
	INCFSZ	(_inPtr + 1), F, B
	BRA	_20837_DS_
	BANKSEL	(_inPtr + 2)
	INCF	(_inPtr + 2), F, B
_20837_DS_:
_00637_DS_:
	.line	788; usb.c	for (i=0;i<bufferSize;i++)
	INFSNZ	r0x02, F
	INCF	r0x03, F
	BRA	_00622_DS_
_00624_DS_:
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
S_usb__InDataStage	code
_InDataStage:
	.line	731; usb.c	void InDataStage(void)
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
	.line	739; usb.c	if(wCount < E0SZ)
	MOVLW	0x00
	BANKSEL	(_wCount + 1)
	SUBWF	(_wCount + 1), W, B
	BNZ	_00607_DS_
	MOVLW	0x20
	BANKSEL	_wCount
	SUBWF	_wCount, W, B
_00607_DS_:
	BC	_00589_DS_
	.line	740; usb.c	bufferSize = wCount;
	MOVFF	_wCount, r0x00
	MOVFF	(_wCount + 1), r0x01
	BRA	_00590_DS_
_00589_DS_:
	.line	742; usb.c	bufferSize = E0SZ;
	MOVLW	0x20
	MOVWF	r0x00
	CLRF	r0x01
_00590_DS_:
	BANKSEL	_ep0Bi
	.line	749; usb.c	ep0Bi.Stat &= ~(BC8 | BC9); // Clear BC8 and BC9
	MOVF	_ep0Bi, W, B
	MOVWF	r0x02
	MOVLW	0xfc
	ANDWF	r0x02, F
	MOVF	r0x02, W
	BANKSEL	_ep0Bi
	MOVWF	_ep0Bi, B
	.line	750; usb.c	ep0Bi.Stat |= (byte)((bufferSize & 0x0300) >> 8);
	CLRF	r0x02
	MOVLW	0x03
	ANDWF	r0x01, W
	MOVWF	r0x03
	MOVF	r0x03, W
	MOVWF	r0x02
	CLRF	r0x03
	BANKSEL	_ep0Bi
	MOVF	_ep0Bi, W, B
	IORWF	r0x02, F
	MOVF	r0x02, W
	BANKSEL	_ep0Bi
	MOVWF	_ep0Bi, B
	.line	751; usb.c	ep0Bi.Cnt = (byte)(bufferSize & 0xFF);
	MOVF	r0x00, W
	MOVWF	r0x02
	CLRF	r0x03
	MOVF	r0x02, W
	BANKSEL	(_ep0Bi + 1)
	MOVWF	(_ep0Bi + 1), B
	.line	752; usb.c	ep0Bi.ADDR = PTR16(&controlTransferBuffer);
	MOVLW	LOW(_controlTransferBuffer)
	MOVWF	r0x02
	MOVLW	HIGH(_controlTransferBuffer)
	MOVWF	r0x03
	CLRF	r0x04
	CLRF	r0x05
	CLRF	r0x04
	CLRF	r0x05
	MOVF	r0x02, W
	BANKSEL	(_ep0Bi + 2)
	MOVWF	(_ep0Bi + 2), B
	MOVF	r0x03, W
	BANKSEL	(_ep0Bi + 3)
	MOVWF	(_ep0Bi + 3), B
	.line	757; usb.c	wCount = wCount - bufferSize;
	MOVF	r0x00, W
	BANKSEL	_wCount
	SUBWF	_wCount, F, B
	MOVF	r0x01, W
	BANKSEL	(_wCount + 1)
	SUBWFB	(_wCount + 1), F, B
	.line	760; usb.c	inPtr = (byte *)&controlTransferBuffer;
	MOVLW	HIGH(_controlTransferBuffer)
	BANKSEL	(_inPtr + 1)
	MOVWF	(_inPtr + 1), B
	MOVLW	LOW(_controlTransferBuffer)
	BANKSEL	_inPtr
	MOVWF	_inPtr, B
	MOVLW	0x80
	BANKSEL	(_inPtr + 2)
	MOVWF	(_inPtr + 2), B
	.line	765; usb.c	for (i=0;i<bufferSize;i++)
	CLRF	r0x02
_00593_DS_:
	MOVFF	r0x02, r0x03
	CLRF	r0x04
	MOVF	r0x01, W
	SUBWF	r0x04, W
	BNZ	_00613_DS_
	MOVF	r0x00, W
	SUBWF	r0x03, W
_00613_DS_:
	BC	_00595_DS_
	.line	766; usb.c	*inPtr++ = *outPtr++;
	MOVFF	_inPtr, r0x03
	MOVFF	(_inPtr + 1), r0x04
	MOVFF	(_inPtr + 2), r0x05
	MOVFF	_outPtr, r0x06
	MOVFF	(_outPtr + 1), r0x07
	MOVFF	(_outPtr + 2), r0x08
	MOVFF	r0x06, FSR0L
	MOVFF	r0x07, PRODL
	MOVF	r0x08, W
	CALL	__gptrget1
	MOVWF	r0x06
	BANKSEL	_outPtr
	INCF	_outPtr, F, B
	BNC	_00614_DS_
	BANKSEL	(_outPtr + 1)
	INCFSZ	(_outPtr + 1), F, B
	BRA	_30838_DS_
	BANKSEL	(_outPtr + 2)
	INCF	(_outPtr + 2), F, B
_30838_DS_:
_00614_DS_:
	MOVFF	r0x06, POSTDEC1
	MOVFF	r0x03, FSR0L
	MOVFF	r0x04, PRODL
	MOVF	r0x05, W
	CALL	__gptrput1
	BANKSEL	_inPtr
	INCF	_inPtr, F, B
	BNC	_00615_DS_
	BANKSEL	(_inPtr + 1)
	INCFSZ	(_inPtr + 1), F, B
	BRA	_40839_DS_
	BANKSEL	(_inPtr + 2)
	INCF	(_inPtr + 2), F, B
_40839_DS_:
_00615_DS_:
	.line	765; usb.c	for (i=0;i<bufferSize;i++)
	INCF	r0x02, F
	BRA	_00593_DS_
_00595_DS_:
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
S_usb__ProcessStandardRequest	code
_ProcessStandardRequest:
	.line	622; usb.c	void ProcessStandardRequest(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	.line	624; usb.c	byte request = SetupPacket.bRequest;
	MOVFF	(_SetupPacket + 1), r0x00
	BANKSEL	_SetupPacket
	.line	626; usb.c	if((SetupPacket.bmRequestType & 0x60) != 0x00)
	MOVF	_SetupPacket, W, B
	ANDLW	0x60
	BZ	_00502_DS_
	.line	629; usb.c	return;
	BRA	_00534_DS_
_00502_DS_:
	.line	631; usb.c	if (request == SET_ADDRESS)
	MOVF	r0x00, W
	XORLW	0x05
	BNZ	_00532_DS_
	.line	640; usb.c	requestHandled = 1;
	MOVLW	0x01
	BANKSEL	_requestHandled
	MOVWF	_requestHandled, B
	.line	641; usb.c	deviceState = ADDRESS;
	MOVLW	0x04
	BANKSEL	_deviceState
	MOVWF	_deviceState, B
	.line	642; usb.c	deviceAddress = SetupPacket.wValue0;
	MOVFF	(_SetupPacket + 2), _deviceAddress
	BRA	_00534_DS_
_00532_DS_:
	.line	644; usb.c	else if (request == GET_DESCRIPTOR)
	MOVF	r0x00, W
	XORLW	0x06
	BNZ	_00529_DS_
	.line	646; usb.c	GetDescriptor();
	CALL	_GetDescriptor
	BRA	_00534_DS_
_00529_DS_:
	.line	648; usb.c	else if (request == SET_CONFIGURATION)
	MOVF	r0x00, W
	XORLW	0x09
	BNZ	_00526_DS_
	.line	653; usb.c	requestHandled = 1;
	MOVLW	0x01
	BANKSEL	_requestHandled
	MOVWF	_requestHandled, B
	.line	654; usb.c	currentConfiguration = SetupPacket.wValue0;
	MOVFF	(_SetupPacket + 2), _currentConfiguration
	BANKSEL	_currentConfiguration
	.line	657; usb.c	if (currentConfiguration == 0)
	MOVF	_currentConfiguration, W, B
	BNZ	_00504_DS_
	.line	660; usb.c	deviceState = ADDRESS;
	MOVLW	0x04
	BANKSEL	_deviceState
	MOVWF	_deviceState, B
	BRA	_00534_DS_
_00504_DS_:
	.line	664; usb.c	deviceState = CONFIGURED;
	MOVLW	0x05
	BANKSEL	_deviceState
	MOVWF	_deviceState, B
	.line	667; usb.c	HIDInitEndpoint();
	CALL	_HIDInitEndpoint
	BRA	_00534_DS_
_00526_DS_:
	.line	673; usb.c	else if (request == GET_CONFIGURATION)
	MOVF	r0x00, W
	XORLW	0x08
	BNZ	_00523_DS_
	.line	678; usb.c	requestHandled = 1;
	MOVLW	0x01
	BANKSEL	_requestHandled
	MOVWF	_requestHandled, B
	.line	679; usb.c	outPtr = (byte*)&currentConfiguration;
	MOVLW	HIGH(_currentConfiguration)
	BANKSEL	(_outPtr + 1)
	MOVWF	(_outPtr + 1), B
	MOVLW	LOW(_currentConfiguration)
	BANKSEL	_outPtr
	MOVWF	_outPtr, B
	MOVLW	0x80
	BANKSEL	(_outPtr + 2)
	MOVWF	(_outPtr + 2), B
	.line	680; usb.c	wCount = 1;
	MOVLW	0x01
	BANKSEL	_wCount
	MOVWF	_wCount, B
	BANKSEL	(_wCount + 1)
	CLRF	(_wCount + 1), B
	BRA	_00534_DS_
_00523_DS_:
	.line	682; usb.c	else if (request == GET_STATUS)
	MOVF	r0x00, W
	BNZ	_00520_DS_
	.line	684; usb.c	GetStatus();
	CALL	_GetStatus
	BRA	_00534_DS_
_00520_DS_:
	.line	686; usb.c	else if ((request == CLEAR_FEATURE) ||
	MOVF	r0x00, W
	XORLW	0x01
	BZ	_00515_DS_
	.line	687; usb.c	(request == SET_FEATURE))
	MOVF	r0x00, W
	XORLW	0x03
	BNZ	_00516_DS_
_00515_DS_:
	.line	689; usb.c	SetFeature();
	CALL	_SetFeature
	BRA	_00534_DS_
_00516_DS_:
	.line	691; usb.c	else if (request == GET_INTERFACE)
	MOVF	r0x00, W
	XORLW	0x0a
	BNZ	_00513_DS_
	.line	698; usb.c	requestHandled = 1;
	MOVLW	0x01
	BANKSEL	_requestHandled
	MOVWF	_requestHandled, B
	BANKSEL	_controlTransferBuffer
	.line	699; usb.c	controlTransferBuffer[0] = 0;
	CLRF	_controlTransferBuffer, B
	.line	700; usb.c	outPtr = (__data byte *)&controlTransferBuffer;
	MOVLW	HIGH(_controlTransferBuffer)
	BANKSEL	(_outPtr + 1)
	MOVWF	(_outPtr + 1), B
	MOVLW	LOW(_controlTransferBuffer)
	BANKSEL	_outPtr
	MOVWF	_outPtr, B
	MOVLW	0x80
	BANKSEL	(_outPtr + 2)
	MOVWF	(_outPtr + 2), B
	.line	701; usb.c	wCount = 1;
	MOVLW	0x01
	BANKSEL	_wCount
	MOVWF	_wCount, B
	BANKSEL	(_wCount + 1)
	CLRF	(_wCount + 1), B
	BRA	_00534_DS_
_00513_DS_:
	.line	703; usb.c	else if (request == SET_INTERFACE)
	MOVF	r0x00, W
	XORLW	0x0b
	BNZ	_00534_DS_
	.line	709; usb.c	requestHandled = 1;
	MOVLW	0x01
	BANKSEL	_requestHandled
	MOVWF	_requestHandled, B
_00534_DS_:
	.line	717; usb.c	else if (request == SYNCH_FRAME)
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb__SetFeature	code
_SetFeature:
	.line	573; usb.c	static void SetFeature(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVFF	r0x05, POSTDEC1
	.line	575; usb.c	byte recipient = SetupPacket.bmRequestType & 0x1F;
	MOVLW	0x1f
	BANKSEL	_SetupPacket
	ANDWF	_SetupPacket, W, B
	MOVWF	r0x00
	.line	576; usb.c	byte feature = SetupPacket.wValue0;
	MOVFF	(_SetupPacket + 2), r0x01
	.line	581; usb.c	if (recipient == 0x00)
	MOVF	r0x00, W
	BNZ	_00453_DS_
	.line	584; usb.c	if (feature == DEVICE_REMOTE_WAKEUP)
	MOVF	r0x01, W
	XORLW	0x01
	BZ	_00486_DS_
	BRA	_00455_DS_
_00486_DS_:
	.line	586; usb.c	requestHandled = 1;
	MOVLW	0x01
	BANKSEL	_requestHandled
	MOVWF	_requestHandled, B
	BANKSEL	(_SetupPacket + 1)
	.line	587; usb.c	if (SetupPacket.bRequest == SET_FEATURE)
	MOVF	(_SetupPacket + 1), W, B
	XORLW	0x03
	BNZ	_00435_DS_
	.line	588; usb.c	remoteWakeup = 1;
	MOVLW	0x01
	BANKSEL	_remoteWakeup
	MOVWF	_remoteWakeup, B
	BRA	_00455_DS_
_00435_DS_:
	BANKSEL	_remoteWakeup
	.line	590; usb.c	remoteWakeup = 0;
	CLRF	_remoteWakeup, B
	BRA	_00455_DS_
_00453_DS_:
	.line	594; usb.c	else if (recipient == 0x02)
	MOVF	r0x00, W
	XORLW	0x02
	BZ	_00490_DS_
	BRA	_00455_DS_
_00490_DS_:
	.line	597; usb.c	byte endpointNum = SetupPacket.wIndex0 & 0x0F;
	MOVLW	0x0f
	BANKSEL	(_SetupPacket + 4)
	ANDWF	(_SetupPacket + 4), W, B
	MOVWF	r0x00
	.line	598; usb.c	byte endpointDir = SetupPacket.wIndex0 & 0x80;
	MOVLW	0x80
	BANKSEL	(_SetupPacket + 4)
	ANDWF	(_SetupPacket + 4), W, B
	MOVWF	r0x02
	.line	599; usb.c	if ((feature == ENDPOINT_HALT) && (endpointNum != 0))
	MOVF	r0x01, W
	BTFSS	STATUS, 2
	BRA	_00455_DS_
	MOVF	r0x00, W
	BTFSC	STATUS, 2
	BRA	_00455_DS_
	.line	602; usb.c	requestHandled = 1;
	MOVLW	0x01
	BANKSEL	_requestHandled
	MOVWF	_requestHandled, B
	.line	605; usb.c	inPtr = (byte *)&ep0Bo + (endpointNum * 8);
	MOVLW	HIGH(_ep0Bo)
	MOVWF	r0x03
	MOVLW	LOW(_ep0Bo)
	MOVWF	r0x01
	MOVLW	0x80
	MOVWF	r0x04
; ;multiply lit val:0x08 by variable r0x00 and store in r0x00
	MOVF	r0x00, W
	MULLW	0x08
	MOVF	PRODH, W
	MOVWF	r0x05
	MOVFF	PRODL, r0x00
	MOVF	r0x00, W
	ADDWF	r0x01, W
	BANKSEL	_inPtr
	MOVWF	_inPtr, B
	MOVF	r0x05, W
	ADDWFC	r0x03, W
	BANKSEL	(_inPtr + 1)
	MOVWF	(_inPtr + 1), B
	CLRF	WREG
	BTFSC	r0x05, 7
	SETF	WREG
	ADDWFC	r0x04, W
	BANKSEL	(_inPtr + 2)
	MOVWF	(_inPtr + 2), B
	.line	606; usb.c	if (endpointDir)
	MOVF	r0x02, W
	BZ	_00440_DS_
	.line	607; usb.c	inPtr += 4;
	MOVLW	0x04
	BANKSEL	_inPtr
	ADDWF	_inPtr, F, B
	MOVLW	0x00
	BANKSEL	(_inPtr + 1)
	ADDWFC	(_inPtr + 1), F, B
	BANKSEL	(_inPtr + 2)
	ADDWFC	(_inPtr + 2), F, B
_00440_DS_:
	BANKSEL	(_SetupPacket + 1)
	.line	609; usb.c	if(SetupPacket.bRequest == SET_FEATURE)
	MOVF	(_SetupPacket + 1), W, B
	XORLW	0x03
	BNZ	_00445_DS_
	.line	610; usb.c	*inPtr = 0x84;
	MOVFF	_inPtr, r0x00
	MOVFF	(_inPtr + 1), r0x01
	MOVFF	(_inPtr + 2), r0x03
	MOVLW	0x84
	MOVWF	POSTDEC1
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, PRODL
	MOVF	r0x03, W
	CALL	__gptrput1
	BRA	_00455_DS_
_00445_DS_:
	.line	613; usb.c	if(endpointDir == 1)
	MOVF	r0x02, W
	XORLW	0x01
	BNZ	_00442_DS_
	.line	614; usb.c	*inPtr = 0x00;
	MOVFF	_inPtr, r0x00
	MOVFF	(_inPtr + 1), r0x01
	MOVFF	(_inPtr + 2), r0x02
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, PRODL
	MOVF	r0x02, W
	CALL	__gptrput1
	BRA	_00455_DS_
_00442_DS_:
	.line	616; usb.c	*inPtr = 0x88;
	MOVFF	_inPtr, r0x00
	MOVFF	(_inPtr + 1), r0x01
	MOVFF	(_inPtr + 2), r0x02
	MOVLW	0x88
	MOVWF	POSTDEC1
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, PRODL
	MOVF	r0x02, W
	CALL	__gptrput1
_00455_DS_:
	MOVFF	PREINC1, r0x05
	MOVFF	PREINC1, r0x04
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb__GetStatus	code
_GetStatus:
	.line	524; usb.c	static void GetStatus(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVFF	r0x05, POSTDEC1
	.line	527; usb.c	byte recipient = SetupPacket.bmRequestType & 0x1F;
	MOVLW	0x1f
	BANKSEL	_SetupPacket
	ANDWF	_SetupPacket, W, B
	MOVWF	r0x00
	BANKSEL	_controlTransferBuffer
	.line	531; usb.c	controlTransferBuffer[0] = 0;
	CLRF	_controlTransferBuffer, B
	BANKSEL	(_controlTransferBuffer + 1)
	.line	532; usb.c	controlTransferBuffer[1] = 0;
	CLRF	(_controlTransferBuffer + 1), B
	.line	535; usb.c	if (recipient == 0x00)
	MOVF	r0x00, W
	BNZ	_00390_DS_
	.line	538; usb.c	requestHandled = 1;
	MOVLW	0x01
	BANKSEL	_requestHandled
	MOVWF	_requestHandled, B
	BANKSEL	_selfPowered
	.line	540; usb.c	if (selfPowered)
	MOVF	_selfPowered, W, B
	BZ	_00377_DS_
	.line	541; usb.c	controlTransferBuffer[0] |= 0x01;
	MOVLW	0x01
	BANKSEL	_controlTransferBuffer
	IORWF	_controlTransferBuffer, W, B
	MOVWF	r0x01
	MOVF	r0x01, W
	BANKSEL	_controlTransferBuffer
	MOVWF	_controlTransferBuffer, B
_00377_DS_:
	BANKSEL	_remoteWakeup
	.line	542; usb.c	if (remoteWakeup)
	MOVF	_remoteWakeup, W, B
	BTFSC	STATUS, 2
	BRA	_00391_DS_
	.line	543; usb.c	controlTransferBuffer[0] |= 0x02;
	MOVLW	0x02
	BANKSEL	_controlTransferBuffer
	IORWF	_controlTransferBuffer, W, B
	MOVWF	r0x01
	MOVF	r0x01, W
	BANKSEL	_controlTransferBuffer
	MOVWF	_controlTransferBuffer, B
	BRA	_00391_DS_
_00390_DS_:
	.line	545; usb.c	else if (recipient == 0x01)
	MOVF	r0x00, W
	XORLW	0x01
	BNZ	_00387_DS_
	.line	548; usb.c	requestHandled = 1;
	MOVLW	0x01
	BANKSEL	_requestHandled
	MOVWF	_requestHandled, B
	BRA	_00391_DS_
_00387_DS_:
	.line	550; usb.c	else if (recipient == 0x02)
	MOVF	r0x00, W
	XORLW	0x02
	BZ	_00426_DS_
	BRA	_00391_DS_
_00426_DS_:
	.line	553; usb.c	byte endpointNum = SetupPacket.wIndex0 & 0x0F;
	MOVLW	0x0f
	BANKSEL	(_SetupPacket + 4)
	ANDWF	(_SetupPacket + 4), W, B
	MOVWF	r0x00
	.line	554; usb.c	byte endpointDir = SetupPacket.wIndex0 & 0x80;
	MOVLW	0x80
	BANKSEL	(_SetupPacket + 4)
	ANDWF	(_SetupPacket + 4), W, B
	MOVWF	r0x01
	.line	555; usb.c	requestHandled = 1;
	MOVLW	0x01
	BANKSEL	_requestHandled
	MOVWF	_requestHandled, B
	.line	558; usb.c	inPtr = (byte *)&ep0Bo + (endpointNum * 8);
	MOVLW	HIGH(_ep0Bo)
	MOVWF	r0x03
	MOVLW	LOW(_ep0Bo)
	MOVWF	r0x02
	MOVLW	0x80
	MOVWF	r0x04
; ;multiply lit val:0x08 by variable r0x00 and store in r0x00
	MOVF	r0x00, W
	MULLW	0x08
	MOVF	PRODH, W
	MOVWF	r0x05
	MOVFF	PRODL, r0x00
	MOVF	r0x00, W
	ADDWF	r0x02, W
	BANKSEL	_inPtr
	MOVWF	_inPtr, B
	MOVF	r0x05, W
	ADDWFC	r0x03, W
	BANKSEL	(_inPtr + 1)
	MOVWF	(_inPtr + 1), B
	CLRF	WREG
	BTFSC	r0x05, 7
	SETF	WREG
	ADDWFC	r0x04, W
	BANKSEL	(_inPtr + 2)
	MOVWF	(_inPtr + 2), B
	.line	559; usb.c	if (endpointDir)
	MOVF	r0x01, W
	BZ	_00381_DS_
	.line	560; usb.c	inPtr += 4;
	MOVLW	0x04
	BANKSEL	_inPtr
	ADDWF	_inPtr, F, B
	MOVLW	0x00
	BANKSEL	(_inPtr + 1)
	ADDWFC	(_inPtr + 1), F, B
	BANKSEL	(_inPtr + 2)
	ADDWFC	(_inPtr + 2), F, B
_00381_DS_:
	.line	561; usb.c	if(*inPtr & BSTALL)
	MOVFF	_inPtr, r0x00
	MOVFF	(_inPtr + 1), r0x01
	MOVFF	(_inPtr + 2), r0x02
	MOVFF	r0x00, FSR0L
	MOVFF	r0x01, PRODL
	MOVF	r0x02, W
	CALL	__gptrget1
	MOVWF	r0x00
	BTFSS	r0x00, 2
	BRA	_00391_DS_
	.line	562; usb.c	controlTransferBuffer[0] = 0x01;
	MOVLW	0x01
	BANKSEL	_controlTransferBuffer
	MOVWF	_controlTransferBuffer, B
_00391_DS_:
	BANKSEL	_requestHandled
	.line	565; usb.c	if (requestHandled)
	MOVF	_requestHandled, W, B
	BZ	_00394_DS_
	.line	567; usb.c	outPtr = (byte *)&controlTransferBuffer;
	MOVLW	HIGH(_controlTransferBuffer)
	BANKSEL	(_outPtr + 1)
	MOVWF	(_outPtr + 1), B
	MOVLW	LOW(_controlTransferBuffer)
	BANKSEL	_outPtr
	MOVWF	_outPtr, B
	MOVLW	0x80
	BANKSEL	(_outPtr + 2)
	MOVWF	(_outPtr + 2), B
	.line	568; usb.c	wCount = 2;
	MOVLW	0x02
	BANKSEL	_wCount
	MOVWF	_wCount, B
	BANKSEL	(_wCount + 1)
	CLRF	(_wCount + 1), B
_00394_DS_:
	MOVFF	PREINC1, r0x05
	MOVFF	PREINC1, r0x04
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb__GetDescriptor	code
_GetDescriptor:
	.line	456; usb.c	static void GetDescriptor(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	MOVFF	r0x04, POSTDEC1
	MOVFF	r0x05, POSTDEC1
	MOVFF	r0x06, POSTDEC1
	BANKSEL	_SetupPacket
	.line	461; usb.c	if(SetupPacket.bmRequestType == 0x80)
	MOVF	_SetupPacket, W, B
	XORLW	0x80
	BZ	_00363_DS_
	BRA	_00342_DS_
_00363_DS_:
	.line	463; usb.c	byte descriptorType  = SetupPacket.wValue1;
	MOVFF	(_SetupPacket + 3), r0x00
	.line	464; usb.c	byte descriptorIndex = SetupPacket.wValue0;
	MOVFF	(_SetupPacket + 2), r0x01
	.line	466; usb.c	if (descriptorType == DEVICE_DESCRIPTOR)
	MOVF	r0x00, W
	XORLW	0x01
	BNZ	_00338_DS_
	.line	469; usb.c	printf("DEVICE_DESCRIPTOR\r\n");
	MOVLW	UPPER(___str_5)
	MOVWF	r0x04
	MOVLW	HIGH(___str_5)
	MOVWF	r0x03
	MOVLW	LOW(___str_5)
	MOVWF	r0x02
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	MOVF	r0x03, W
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	CALL	_printf
	MOVLW	0x03
	ADDWF	FSR1L, F
	.line	471; usb.c	requestHandled = 1;
	MOVLW	0x01
	BANKSEL	_requestHandled
	MOVWF	_requestHandled, B
	.line	472; usb.c	outPtr = (byte *)&deviceDescriptor;
	MOVLW	UPPER(_deviceDescriptor)
	BANKSEL	(_outPtr + 2)
	MOVWF	(_outPtr + 2), B
	MOVLW	HIGH(_deviceDescriptor)
	BANKSEL	(_outPtr + 1)
	MOVWF	(_outPtr + 1), B
	MOVLW	LOW(_deviceDescriptor)
	BANKSEL	_outPtr
	MOVWF	_outPtr, B
	.line	473; usb.c	wCount = DEVICE_DESCRIPTOR_SIZE;
	MOVLW	0x12
	BANKSEL	_wCount
	MOVWF	_wCount, B
	BANKSEL	(_wCount + 1)
	CLRF	(_wCount + 1), B
	BRA	_00342_DS_
_00338_DS_:
	.line	475; usb.c	else if (descriptorType == CONFIGURATION_DESCRIPTOR)
	MOVF	r0x00, W
	XORLW	0x02
	BZ	_00367_DS_
	BRA	_00335_DS_
_00367_DS_:
	.line	478; usb.c	printf("CONFIGURATION_DESCRIPTOR: %d\r\n", descriptorIndex);
	MOVFF	r0x01, r0x02
	CLRF	r0x03
	MOVLW	UPPER(___str_6)
	MOVWF	r0x06
	MOVLW	HIGH(___str_6)
	MOVWF	r0x05
	MOVLW	LOW(___str_6)
	MOVWF	r0x04
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
	MOVLW	0x05
	ADDWF	FSR1L, F
	.line	480; usb.c	requestHandled = 1;
	MOVLW	0x01
	BANKSEL	_requestHandled
	MOVWF	_requestHandled, B
	.line	491; usb.c	outPtr = (byte *)&configDescriptor;
	MOVLW	UPPER(_configDescriptor)
	BANKSEL	(_outPtr + 2)
	MOVWF	(_outPtr + 2), B
	MOVLW	HIGH(_configDescriptor)
	BANKSEL	(_outPtr + 1)
	MOVWF	(_outPtr + 1), B
	MOVLW	LOW(_configDescriptor)
	BANKSEL	_outPtr
	MOVWF	_outPtr, B
	.line	493; usb.c	printf ("wCount = %d\n",sizeof (ConfigStruct));
	MOVLW	UPPER(___str_7)
	MOVWF	r0x04
	MOVLW	HIGH(___str_7)
	MOVWF	r0x03
	MOVLW	LOW(___str_7)
	MOVWF	r0x02
	MOVLW	0x00
	MOVWF	POSTDEC1
	MOVLW	0x29
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
	.line	494; usb.c	wCount = sizeof (ConfigStruct);
	MOVLW	0x29
	BANKSEL	_wCount
	MOVWF	_wCount, B
	BANKSEL	(_wCount + 1)
	CLRF	(_wCount + 1), B
	BRA	_00342_DS_
_00335_DS_:
	.line	500; usb.c	else if (descriptorType == STRING_DESCRIPTOR)
	MOVF	r0x00, W
	XORLW	0x03
	BZ	_00369_DS_
	BRA	_00332_DS_
_00369_DS_:
	.line	505; usb.c	requestHandled = 1;
	MOVLW	0x01
	BANKSEL	_requestHandled
	MOVWF	_requestHandled, B
	.line	506; usb.c	if (descriptorIndex == 0)
	MOVF	r0x01, W
	BNZ	_00329_DS_
	.line	507; usb.c	outPtr = (byte *)&stringDescriptor0;
	MOVLW	UPPER(_stringDescriptor0)
	BANKSEL	(_outPtr + 2)
	MOVWF	(_outPtr + 2), B
	MOVLW	HIGH(_stringDescriptor0)
	BANKSEL	(_outPtr + 1)
	MOVWF	(_outPtr + 1), B
	MOVLW	LOW(_stringDescriptor0)
	BANKSEL	_outPtr
	MOVWF	_outPtr, B
	BRA	_00330_DS_
_00329_DS_:
	.line	508; usb.c	else if (descriptorIndex == 1)
	MOVF	r0x01, W
	XORLW	0x01
	BNZ	_00326_DS_
	.line	509; usb.c	outPtr = (byte *)&stringDescriptor1;
	MOVLW	UPPER(_stringDescriptor1)
	BANKSEL	(_outPtr + 2)
	MOVWF	(_outPtr + 2), B
	MOVLW	HIGH(_stringDescriptor1)
	BANKSEL	(_outPtr + 1)
	MOVWF	(_outPtr + 1), B
	MOVLW	LOW(_stringDescriptor1)
	BANKSEL	_outPtr
	MOVWF	_outPtr, B
	BRA	_00330_DS_
_00326_DS_:
	.line	511; usb.c	outPtr = (byte *)&stringDescriptor2;
	MOVLW	UPPER(_stringDescriptor2)
	BANKSEL	(_outPtr + 2)
	MOVWF	(_outPtr + 2), B
	MOVLW	HIGH(_stringDescriptor2)
	BANKSEL	(_outPtr + 1)
	MOVWF	(_outPtr + 1), B
	MOVLW	LOW(_stringDescriptor2)
	BANKSEL	_outPtr
	MOVWF	_outPtr, B
_00330_DS_:
	.line	512; usb.c	wCount = *outPtr;
	MOVFF	_outPtr, r0x01
	MOVFF	(_outPtr + 1), r0x02
	MOVFF	(_outPtr + 2), r0x03
	MOVFF	r0x01, FSR0L
	MOVFF	r0x02, PRODL
	MOVF	r0x03, W
	CALL	__gptrget1
	MOVWF	r0x01
	MOVFF	r0x01, _wCount
	BANKSEL	(_wCount + 1)
	CLRF	(_wCount + 1), B
	BRA	_00342_DS_
_00332_DS_:
	.line	517; usb.c	printf("Unknown Descriptor: 0x%ux\r\n", (word)descriptorType);
	CLRF	r0x01
	MOVLW	UPPER(___str_8)
	MOVWF	r0x04
	MOVLW	HIGH(___str_8)
	MOVWF	r0x03
	MOVLW	LOW(___str_8)
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
_00342_DS_:
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
S_usb__ProcessHIDRequest	code
_ProcessHIDRequest:
	.line	336; usb.c	void ProcessHIDRequest(void)
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
	.line	341; usb.c	if((SetupPacket.bmRequestType & 0x1F) != 0x01 || (SetupPacket.wIndex0 != 0x00))
	MOVLW	0x1f
	BANKSEL	_SetupPacket
	ANDWF	_SetupPacket, W, B
	MOVWF	r0x00
	MOVF	r0x00, W
	XORLW	0x01
	BNZ	_00223_DS_
_00296_DS_:
	BANKSEL	(_SetupPacket + 4)
	MOVF	(_SetupPacket + 4), W, B
	BZ	_00224_DS_
_00223_DS_:
	.line	342; usb.c	return;
	BRA	_00256_DS_
_00224_DS_:
	.line	344; usb.c	bRequest = SetupPacket.bRequest;
	MOVFF	(_SetupPacket + 1), r0x00
	.line	346; usb.c	if (bRequest == GET_DESCRIPTOR)
	MOVF	r0x00, W
	XORLW	0x06
	BZ	_00298_DS_
	BRA	_00235_DS_
_00298_DS_:
	.line	349; usb.c	byte descriptorType  = SetupPacket.wValue1;
	MOVFF	(_SetupPacket + 3), r0x01
	.line	350; usb.c	if (descriptorType == HID_DESCRIPTOR)
	MOVF	r0x01, W
	XORLW	0x21
	BNZ	_00232_DS_
	.line	353; usb.c	printf("HID: HID_DESCRIPTOR\r\n");
	MOVLW	UPPER(___str_0)
	MOVWF	r0x04
	MOVLW	HIGH(___str_0)
	MOVWF	r0x03
	MOVLW	LOW(___str_0)
	MOVWF	r0x02
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	MOVF	r0x03, W
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	CALL	_printf
	MOVLW	0x03
	ADDWF	FSR1L, F
	.line	356; usb.c	requestHandled = 1;
	MOVLW	0x01
	BANKSEL	_requestHandled
	MOVWF	_requestHandled, B
	.line	357; usb.c	outPtr = (__data byte *)&configDescriptor.HIDDescriptor;
	MOVLW	LOW(_configDescriptor + 9)
	MOVWF	r0x02
	MOVLW	HIGH(_configDescriptor + 9)
	MOVWF	r0x03
	MOVF	r0x03, W
	BANKSEL	(_outPtr + 1)
	MOVWF	(_outPtr + 1), B
	MOVF	r0x02, W
	BANKSEL	_outPtr
	MOVWF	_outPtr, B
	MOVLW	0x80
	BANKSEL	(_outPtr + 2)
	MOVWF	(_outPtr + 2), B
	.line	358; usb.c	wCount = HID_HEADER_SIZE;
	MOVLW	0x09
	BANKSEL	_wCount
	MOVWF	_wCount, B
	BANKSEL	(_wCount + 1)
	CLRF	(_wCount + 1), B
	BRA	_00235_DS_
_00232_DS_:
	.line	360; usb.c	else if (descriptorType == REPORT_DESCRIPTOR)
	MOVF	r0x01, W
	XORLW	0x22
	BNZ	_00229_DS_
	.line	363; usb.c	printf("HID: REPORT_DESCRIPTOR\r\n");
	MOVLW	UPPER(___str_1)
	MOVWF	r0x04
	MOVLW	HIGH(___str_1)
	MOVWF	r0x03
	MOVLW	LOW(___str_1)
	MOVWF	r0x02
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	MOVF	r0x03, W
	MOVWF	POSTDEC1
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	CALL	_printf
	MOVLW	0x03
	ADDWF	FSR1L, F
	.line	366; usb.c	requestHandled = 1;
	MOVLW	0x01
	BANKSEL	_requestHandled
	MOVWF	_requestHandled, B
	.line	367; usb.c	outPtr = (__code byte *)HIDReport;
	MOVLW	UPPER(_HIDReport)
	BANKSEL	(_outPtr + 2)
	MOVWF	(_outPtr + 2), B
	MOVLW	HIGH(_HIDReport)
	BANKSEL	(_outPtr + 1)
	MOVWF	(_outPtr + 1), B
	MOVLW	LOW(_HIDReport)
	BANKSEL	_outPtr
	MOVWF	_outPtr, B
	.line	368; usb.c	wCount = HID_REPORT_SIZE;
	MOVLW	0x2f
	BANKSEL	_wCount
	MOVWF	_wCount, B
	BANKSEL	(_wCount + 1)
	CLRF	(_wCount + 1), B
	BRA	_00235_DS_
_00229_DS_:
	.line	370; usb.c	else if (descriptorType == PHYSICAL_DESCRIPTOR)
	MOVF	r0x01, W
	XORLW	0x23
	BNZ	_00235_DS_
	.line	373; usb.c	printf("HID: PHYSICAL_DESCRIPTOR\r\n");
	MOVLW	UPPER(___str_2)
	MOVWF	r0x03
	MOVLW	HIGH(___str_2)
	MOVWF	r0x02
	MOVLW	LOW(___str_2)
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
_00235_DS_:
	.line	385; usb.c	if ((SetupPacket.bmRequestType & 0x60) != 0x20)
	MOVLW	0x60
	BANKSEL	_SetupPacket
	ANDWF	_SetupPacket, W, B
	MOVWF	r0x01
	MOVF	r0x01, W
	XORLW	0x20
	BZ	_00237_DS_
	.line	388; usb.c	printf("Not CLASS request: 0x%x, 0x%x\r\n", (word)(SetupPacket.bmRequestType & 0x60), (word)SetupPacket.bRequest);
	MOVFF	(_SetupPacket + 1), r0x01
	CLRF	r0x02
	MOVLW	0x60
	BANKSEL	_SetupPacket
	ANDWF	_SetupPacket, W, B
	MOVWF	r0x03
	CLRF	r0x04
	MOVLW	UPPER(___str_3)
	MOVWF	r0x07
	MOVLW	HIGH(___str_3)
	MOVWF	r0x06
	MOVLW	LOW(___str_3)
	MOVWF	r0x05
	MOVF	r0x02, W
	MOVWF	POSTDEC1
	MOVF	r0x01, W
	MOVWF	POSTDEC1
	MOVF	r0x04, W
	MOVWF	POSTDEC1
	MOVF	r0x03, W
	MOVWF	POSTDEC1
	MOVF	r0x07, W
	MOVWF	POSTDEC1
	MOVF	r0x06, W
	MOVWF	POSTDEC1
	MOVF	r0x05, W
	MOVWF	POSTDEC1
	CALL	_printf
	MOVLW	0x07
	ADDWF	FSR1L, F
	.line	390; usb.c	return;
	BRA	_00256_DS_
_00237_DS_:
	.line	394; usb.c	if (bRequest == GET_REPORT)
	MOVF	r0x00, W
	XORLW	0x01
	BNZ	_00254_DS_
	.line	399; usb.c	HIDGetReport();
	CALL	_HIDGetReport
	BRA	_00256_DS_
_00254_DS_:
	.line	401; usb.c	else if (bRequest == SET_REPORT)
	MOVF	r0x00, W
	XORLW	0x09
	BNZ	_00251_DS_
	.line	406; usb.c	HIDPostProcess = 1;
	MOVLW	0x01
	BANKSEL	_HIDPostProcess
	MOVWF	_HIDPostProcess, B
	.line	407; usb.c	HIDSetReport();            
	CALL	_HIDSetReport
	BRA	_00256_DS_
_00251_DS_:
	.line	409; usb.c	else if (bRequest == GET_IDLE)
	MOVF	r0x00, W
	XORLW	0x02
	BNZ	_00248_DS_
	.line	414; usb.c	requestHandled = 1;
	MOVLW	0x01
	BANKSEL	_requestHandled
	MOVWF	_requestHandled, B
	.line	415; usb.c	outPtr = &hidIdleRate;
	MOVLW	HIGH(_hidIdleRate)
	BANKSEL	(_outPtr + 1)
	MOVWF	(_outPtr + 1), B
	MOVLW	LOW(_hidIdleRate)
	BANKSEL	_outPtr
	MOVWF	_outPtr, B
	MOVLW	0x80
	BANKSEL	(_outPtr + 2)
	MOVWF	(_outPtr + 2), B
	.line	416; usb.c	wCount = 1;
	MOVLW	0x01
	BANKSEL	_wCount
	MOVWF	_wCount, B
	BANKSEL	(_wCount + 1)
	CLRF	(_wCount + 1), B
	BRA	_00256_DS_
_00248_DS_:
	.line	418; usb.c	else if (bRequest == SET_IDLE)
	MOVF	r0x00, W
	XORLW	0x0a
	BNZ	_00245_DS_
	.line	423; usb.c	requestHandled = 1;
	MOVLW	0x01
	BANKSEL	_requestHandled
	MOVWF	_requestHandled, B
	.line	424; usb.c	hidIdleRate = SetupPacket.wValue1;
	MOVFF	(_SetupPacket + 3), _hidIdleRate
	BRA	_00256_DS_
_00245_DS_:
	.line	426; usb.c	else if (bRequest == GET_PROTOCOL)
	MOVF	r0x00, W
	XORLW	0x03
	BNZ	_00242_DS_
	.line	431; usb.c	requestHandled = 1;
	MOVLW	0x01
	BANKSEL	_requestHandled
	MOVWF	_requestHandled, B
	.line	432; usb.c	outPtr = &hidProtocol;
	MOVLW	HIGH(_hidProtocol)
	BANKSEL	(_outPtr + 1)
	MOVWF	(_outPtr + 1), B
	MOVLW	LOW(_hidProtocol)
	BANKSEL	_outPtr
	MOVWF	_outPtr, B
	MOVLW	0x80
	BANKSEL	(_outPtr + 2)
	MOVWF	(_outPtr + 2), B
	.line	433; usb.c	wCount = 1;
	MOVLW	0x01
	BANKSEL	_wCount
	MOVWF	_wCount, B
	BANKSEL	(_wCount + 1)
	CLRF	(_wCount + 1), B
	BRA	_00256_DS_
_00242_DS_:
	.line	435; usb.c	else if (bRequest == SET_PROTOCOL)
	MOVF	r0x00, W
	XORLW	0x0b
	BNZ	_00239_DS_
	.line	440; usb.c	requestHandled = 1;
	MOVLW	0x01
	BANKSEL	_requestHandled
	MOVWF	_requestHandled, B
	.line	441; usb.c	hidProtocol = SetupPacket.wValue0;
	MOVFF	(_SetupPacket + 2), _hidProtocol
	BRA	_00256_DS_
_00239_DS_:
	.line	446; usb.c	printf("HID: Unknown request: 0x%x\r\n", SetupPacket.bRequest);
	MOVFF	(_SetupPacket + 1), r0x00
	CLRF	r0x01
	MOVLW	UPPER(___str_4)
	MOVWF	r0x04
	MOVLW	HIGH(___str_4)
	MOVWF	r0x03
	MOVLW	LOW(___str_4)
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
_00256_DS_:
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
S_usb__HIDSetReport	code
_HIDSetReport:
	.line	320; usb.c	void HIDSetReport(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	.line	322; usb.c	byte reportID = SetupPacket.wValue0;
	MOVFF	(_SetupPacket + 2), r0x00
	BANKSEL	(_SetupPacket + 3)
	.line	328; usb.c	if (SetupPacket.wValue1 == 0x02)
	MOVF	(_SetupPacket + 3), W, B
	XORLW	0x02
	BNZ	_00204_DS_
	.line	329; usb.c	requestHandled = SetupOutputReport(reportID);
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_SetupOutputReport
	MOVWF	r0x01
	MOVFF	PRODL, r0x02
	MOVF	POSTINC1, F
	MOVF	r0x01, W
	BANKSEL	_requestHandled
	MOVWF	_requestHandled, B
_00204_DS_:
	BANKSEL	(_SetupPacket + 3)
	.line	331; usb.c	if (SetupPacket.wValue1 == 0x03)
	MOVF	(_SetupPacket + 3), W, B
	XORLW	0x03
	BNZ	_00207_DS_
	.line	332; usb.c	requestHandled = SetupFeatureReport(reportID);
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_SetupFeatureReport
	MOVWF	r0x00
	MOVFF	PRODL, r0x01
	MOVF	POSTINC1, F
	MOVF	r0x00, W
	BANKSEL	_requestHandled
	MOVWF	_requestHandled, B
_00207_DS_:
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb__HIDGetReport	code
_HIDGetReport:
	.line	304; usb.c	void HIDGetReport(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	.line	306; usb.c	byte reportID = SetupPacket.wValue0;
	MOVFF	(_SetupPacket + 2), r0x00
	BANKSEL	(_SetupPacket + 3)
	.line	312; usb.c	if (SetupPacket.wValue1 == 0x01)
	MOVF	(_SetupPacket + 3), W, B
	XORLW	0x01
	BNZ	_00184_DS_
	.line	313; usb.c	requestHandled = GetInputReport(reportID);
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_GetInputReport
	MOVWF	r0x01
	MOVFF	PRODL, r0x02
	MOVF	POSTINC1, F
	MOVF	r0x01, W
	BANKSEL	_requestHandled
	MOVWF	_requestHandled, B
_00184_DS_:
	BANKSEL	(_SetupPacket + 3)
	.line	315; usb.c	if (SetupPacket.wValue1 == 0x03)
	MOVF	(_SetupPacket + 3), W, B
	XORLW	0x03
	BNZ	_00187_DS_
	.line	316; usb.c	requestHandled = GetFeatureReport(reportID);
	MOVF	r0x00, W
	MOVWF	POSTDEC1
	CALL	_GetFeatureReport
	MOVWF	r0x00
	MOVFF	PRODL, r0x01
	MOVF	POSTINC1, F
	MOVF	r0x00, W
	BANKSEL	_requestHandled
	MOVWF	_requestHandled, B
_00187_DS_:
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb__HIDInitEndpoint	code
_HIDInitEndpoint:
	.line	283; usb.c	void HIDInitEndpoint(void)
	MOVFF	FSR2L, POSTDEC1
	MOVFF	FSR1L, FSR2L
	MOVFF	r0x00, POSTDEC1
	MOVFF	r0x01, POSTDEC1
	MOVFF	r0x02, POSTDEC1
	MOVFF	r0x03, POSTDEC1
	BANKSEL	_hidRxLen
	.line	285; usb.c	hidRxLen =0;
	CLRF	_hidRxLen, B
	.line	291; usb.c	UEP1 = 0x1E;
	MOVLW	0x1e
	MOVWF	_UEP1
	.line	293; usb.c	ep1Bo.Cnt = sizeof(HIDRxBuffer);
	MOVLW	0x20
	BANKSEL	(_ep1Bo + 1)
	MOVWF	(_ep1Bo + 1), B
	.line	294; usb.c	ep1Bo.ADDR = PTR16(&HIDRxBuffer);
	MOVLW	LOW(_HIDRxBuffer)
	MOVWF	r0x00
	MOVLW	HIGH(_HIDRxBuffer)
	MOVWF	r0x01
	CLRF	r0x02
	CLRF	r0x03
	CLRF	r0x02
	CLRF	r0x03
	MOVF	r0x00, W
	BANKSEL	(_ep1Bo + 2)
	MOVWF	(_ep1Bo + 2), B
	MOVF	r0x01, W
	BANKSEL	(_ep1Bo + 3)
	MOVWF	(_ep1Bo + 3), B
	.line	295; usb.c	ep1Bo.Stat = UOWN | DTSEN;
	MOVLW	0x88
	BANKSEL	_ep1Bo
	MOVWF	_ep1Bo, B
	.line	297; usb.c	ep1Bi.ADDR = PTR16(&HIDTxBuffer);
	MOVLW	LOW(_HIDTxBuffer)
	MOVWF	r0x00
	MOVLW	HIGH(_HIDTxBuffer)
	MOVWF	r0x01
	CLRF	r0x02
	CLRF	r0x03
	CLRF	r0x02
	CLRF	r0x03
	MOVF	r0x00, W
	BANKSEL	(_ep1Bi + 2)
	MOVWF	(_ep1Bi + 2), B
	MOVF	r0x01, W
	BANKSEL	(_ep1Bi + 3)
	MOVWF	(_ep1Bi + 3), B
	.line	298; usb.c	ep1Bi.Stat = DTS;
	MOVLW	0x40
	BANKSEL	_ep1Bi
	MOVWF	_ep1Bi, B
	MOVFF	PREINC1, r0x03
	MOVFF	PREINC1, r0x02
	MOVFF	PREINC1, r0x01
	MOVFF	PREINC1, r0x00
	MOVFF	PREINC1, FSR2L
	RETURN	

; ; Starting pCode block
S_usb__HIDRxReport	code
_HIDRxReport:
	.line	240; usb.c	byte HIDRxReport(byte *buffer, byte len)
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
	MOVLW	0x02
	MOVFF	PLUSW2, r0x00
	MOVLW	0x03
	MOVFF	PLUSW2, r0x01
	MOVLW	0x04
	MOVFF	PLUSW2, r0x02
	MOVLW	0x05
	MOVFF	PLUSW2, r0x03
	BANKSEL	_hidRxLen
	.line	242; usb.c	hidRxLen = 0;
	CLRF	_hidRxLen, B
	BANKSEL	_ep1Bo
	.line	249; usb.c	if(!(ep1Bo.Stat & UOWN))
	BTFSC	_ep1Bo, 7, B
	BRA	_00149_DS_
	.line	252; usb.c	if(len > ep1Bo.Cnt)
	MOVF	r0x03, W
	BANKSEL	(_ep1Bo + 1)
	SUBWF	(_ep1Bo + 1), W, B
	BC	_00143_DS_
	.line	253; usb.c	len = ep1Bo.Cnt;
	MOVFF	(_ep1Bo + 1), r0x03
_00143_DS_:
	BANKSEL	_hidRxLen
	.line	259; usb.c	for(hidRxLen = 0; hidRxLen < len; hidRxLen++)
	CLRF	_hidRxLen, B
_00151_DS_:
	MOVF	r0x03, W
	BANKSEL	_hidRxLen
	SUBWF	_hidRxLen, W, B
	BC	_00144_DS_
	BANKSEL	_hidRxLen
	.line	261; usb.c	buffer[hidRxLen] = HIDRxBuffer[hidRxLen];
	MOVF	_hidRxLen, W, B
	ADDWF	r0x00, W
	MOVWF	r0x04
	CLRF	WREG
	ADDWFC	r0x01, W
	MOVWF	r0x05
	CLRF	WREG
	ADDWFC	r0x02, W
	MOVWF	r0x06
	MOVLW	LOW(_HIDRxBuffer)
	BANKSEL	_hidRxLen
	ADDWF	_hidRxLen, W, B
	MOVWF	r0x07
	CLRF	r0x08
	MOVLW	HIGH(_HIDRxBuffer)
	ADDWFC	r0x08, F
	MOVFF	r0x07, FSR0L
	MOVFF	r0x08, FSR0H
	MOVFF	INDF0, r0x07
	MOVFF	r0x07, POSTDEC1
	MOVFF	r0x04, FSR0L
	MOVFF	r0x05, PRODL
	MOVF	r0x06, W
	CALL	__gptrput1
	BANKSEL	_hidRxLen
	.line	259; usb.c	for(hidRxLen = 0; hidRxLen < len; hidRxLen++)
	INCF	_hidRxLen, F, B
	BRA	_00151_DS_
_00144_DS_:
	.line	271; usb.c	ep1Bo.Cnt = sizeof(HIDRxBuffer);
	MOVLW	0x20
	BANKSEL	(_ep1Bo + 1)
	MOVWF	(_ep1Bo + 1), B
	BANKSEL	_ep1Bo
	.line	272; usb.c	if(ep1Bo.Stat & DTS)
	BTFSS	_ep1Bo, 6, B
	BRA	_00146_DS_
	.line	273; usb.c	ep1Bo.Stat = UOWN | DTSEN;
	MOVLW	0x88
	BANKSEL	_ep1Bo
	MOVWF	_ep1Bo, B
	BRA	_00149_DS_
_00146_DS_:
	.line	275; usb.c	ep1Bo.Stat = UOWN | DTS | DTSEN;
	MOVLW	0xc8
	BANKSEL	_ep1Bo
	MOVWF	_ep1Bo, B
_00149_DS_:
	BANKSEL	_hidRxLen
	.line	278; usb.c	return hidRxLen;
	MOVF	_hidRxLen, W, B
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
S_usb__HIDTxReport	code
_HIDTxReport:
	.line	203; usb.c	byte HIDTxReport(byte *buffer, byte len)
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
	MOVLW	0x05
	MOVFF	PLUSW2, r0x03
	BANKSEL	_ep1Bi
	.line	212; usb.c	if (ep1Bi.Stat & UOWN)
	BTFSS	_ep1Bi, 7, B
	BRA	_00106_DS_
	.line	213; usb.c	return 0;
	CLRF	WREG
	BRA	_00116_DS_
_00106_DS_:
	.line	216; usb.c	if(len > HID_INPUT_REPORT_BYTES)
	MOVLW	0x21
	SUBWF	r0x03, W
	BNC	_00121_DS_
	.line	217; usb.c	len = HID_INPUT_REPORT_BYTES;
	MOVLW	0x20
	MOVWF	r0x03
_00121_DS_:
	.line	223; usb.c	for (i = 0; i < len; i++)
	CLRF	r0x04
_00114_DS_:
	MOVF	r0x03, W
	SUBWF	r0x04, W
	BC	_00109_DS_
	.line	224; usb.c	HIDTxBuffer[i] = buffer[i];
	MOVLW	LOW(_HIDTxBuffer)
	ADDWF	r0x04, W
	MOVWF	r0x05
	CLRF	r0x06
	MOVLW	HIGH(_HIDTxBuffer)
	ADDWFC	r0x06, F
	MOVF	r0x04, W
	ADDWF	r0x00, W
	MOVWF	r0x07
	CLRF	WREG
	ADDWFC	r0x01, W
	MOVWF	r0x08
	CLRF	WREG
	ADDWFC	r0x02, W
	MOVWF	r0x09
	MOVFF	r0x07, FSR0L
	MOVFF	r0x08, PRODL
	MOVF	r0x09, W
	CALL	__gptrget1
	MOVWF	r0x07
	MOVFF	r0x05, FSR0L
	MOVFF	r0x06, FSR0H
	MOVFF	r0x07, INDF0
	.line	223; usb.c	for (i = 0; i < len; i++)
	INCF	r0x04, F
	BRA	_00114_DS_
_00109_DS_:
	.line	228; usb.c	ep1Bi.Cnt = len;
	MOVF	r0x03, W
	BANKSEL	(_ep1Bi + 1)
	MOVWF	(_ep1Bi + 1), B
	BANKSEL	_ep1Bi
	.line	229; usb.c	if(ep1Bi.Stat & DTS)
	BTFSS	_ep1Bi, 6, B
	BRA	_00111_DS_
	.line	230; usb.c	ep1Bi.Stat = UOWN | DTSEN;
	MOVLW	0x88
	BANKSEL	_ep1Bi
	MOVWF	_ep1Bi, B
	BRA	_00112_DS_
_00111_DS_:
	.line	232; usb.c	ep1Bi.Stat = UOWN | DTS | DTSEN;
	MOVLW	0xc8
	BANKSEL	_ep1Bi
	MOVWF	_ep1Bi, B
_00112_DS_:
	.line	234; usb.c	return len;
	MOVF	r0x03, W
_00116_DS_:
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

; ; Starting pCode block for Ival
	code
_deviceDescriptor:
	DB	0x12, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00, 0x20, 0xd8, 0x04, 0x41, 0x45
	DB	0x01, 0x00, 0x01, 0x02, 0x00, 0x01
; ; Starting pCode block for Ival
_configDescriptor:
	DB	0x09, 0x02, 0x29, 0x00, 0x01, 0x01, 0x00, 0xa0, 0x32, 0x09, 0x04, 0x00
	DB	0x00, 0x02, 0x03, 0x00, 0x00, 0x00, 0x09, 0x21, 0x01, 0x01, 0x00, 0x01
	DB	0x22, 0x2f, 0x00, 0x07, 0x05, 0x81, 0x03, 0x20, 0x00, 0x01, 0x07, 0x05
	DB	0x01, 0x03, 0x20, 0x00, 0x01
; ; Starting pCode block for Ival
_HIDReport:
	DB	0x06, 0xa0, 0xff, 0x09, 0x01, 0xa1, 0x01, 0x09, 0x02, 0x15, 0x00, 0x26
	DB	0x00, 0xff, 0x75, 0x08, 0x95, 0x20, 0x81, 0x02, 0x09, 0x02, 0x15, 0x00
	DB	0x26, 0x00, 0xff, 0x75, 0x08, 0x95, 0x20, 0x91, 0x02, 0x09, 0x01, 0x15
	DB	0x00, 0x26, 0x00, 0xff, 0x75, 0x08, 0x95, 0x20, 0xb1, 0x02, 0xc0
; ; Starting pCode block for Ival
_stringDescriptor0:
	DB	0x04, 0x03, 0x09, 0x04
; ; Starting pCode block for Ival
_stringDescriptor1:
	DB	0x18, 0x03, 0x4c, 0x00, 0x69, 0x00, 0x6e, 0x00, 0x75, 0x00, 0x78, 0x00
	DB	0x20, 0x00, 0x52, 0x00, 0x6f, 0x00, 0x62, 0x00, 0x6f, 0x00, 0x74, 0x00
; ; Starting pCode block for Ival
_stringDescriptor2:
	DB	0x26, 0x03, 0x55, 0x00, 0x53, 0x00, 0x42, 0x00, 0x20, 0x00, 0x52, 0x00
	DB	0x6f, 0x00, 0x62, 0x00, 0x6f, 0x00, 0x74, 0x00, 0x20, 0x00, 0x70, 0x00
	DB	0x72, 0x00, 0x6f, 0x00, 0x74, 0x00, 0x6f, 0x00, 0x63, 0x00, 0x6f, 0x00
	DB	0x6c, 0x00
; ; Starting pCode block
___str_0:
	DB	0x48, 0x49, 0x44, 0x3a, 0x20, 0x48, 0x49, 0x44, 0x5f, 0x44, 0x45, 0x53
	DB	0x43, 0x52, 0x49, 0x50, 0x54, 0x4f, 0x52, 0x0d, 0x0a, 0x00
; ; Starting pCode block
___str_1:
	DB	0x48, 0x49, 0x44, 0x3a, 0x20, 0x52, 0x45, 0x50, 0x4f, 0x52, 0x54, 0x5f
	DB	0x44, 0x45, 0x53, 0x43, 0x52, 0x49, 0x50, 0x54, 0x4f, 0x52, 0x0d, 0x0a
	DB	0x00
; ; Starting pCode block
___str_2:
	DB	0x48, 0x49, 0x44, 0x3a, 0x20, 0x50, 0x48, 0x59, 0x53, 0x49, 0x43, 0x41
	DB	0x4c, 0x5f, 0x44, 0x45, 0x53, 0x43, 0x52, 0x49, 0x50, 0x54, 0x4f, 0x52
	DB	0x0d, 0x0a, 0x00
; ; Starting pCode block
___str_3:
	DB	0x4e, 0x6f, 0x74, 0x20, 0x43, 0x4c, 0x41, 0x53, 0x53, 0x20, 0x72, 0x65
	DB	0x71, 0x75, 0x65, 0x73, 0x74, 0x3a, 0x20, 0x30, 0x78, 0x25, 0x78, 0x2c
	DB	0x20, 0x30, 0x78, 0x25, 0x78, 0x0d, 0x0a, 0x00
; ; Starting pCode block
___str_4:
	DB	0x48, 0x49, 0x44, 0x3a, 0x20, 0x55, 0x6e, 0x6b, 0x6e, 0x6f, 0x77, 0x6e
	DB	0x20, 0x72, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x3a, 0x20, 0x30, 0x78
	DB	0x25, 0x78, 0x0d, 0x0a, 0x00
; ; Starting pCode block
___str_5:
	DB	0x44, 0x45, 0x56, 0x49, 0x43, 0x45, 0x5f, 0x44, 0x45, 0x53, 0x43, 0x52
	DB	0x49, 0x50, 0x54, 0x4f, 0x52, 0x0d, 0x0a, 0x00
; ; Starting pCode block
___str_6:
	DB	0x43, 0x4f, 0x4e, 0x46, 0x49, 0x47, 0x55, 0x52, 0x41, 0x54, 0x49, 0x4f
	DB	0x4e, 0x5f, 0x44, 0x45, 0x53, 0x43, 0x52, 0x49, 0x50, 0x54, 0x4f, 0x52
	DB	0x3a, 0x20, 0x25, 0x64, 0x0d, 0x0a, 0x00
; ; Starting pCode block
___str_7:
	DB	0x77, 0x43, 0x6f, 0x75, 0x6e, 0x74, 0x20, 0x3d, 0x20, 0x25, 0x64, 0x0a
	DB	0x00
; ; Starting pCode block
___str_8:
	DB	0x55, 0x6e, 0x6b, 0x6e, 0x6f, 0x77, 0x6e, 0x20, 0x44, 0x65, 0x73, 0x63
	DB	0x72, 0x69, 0x70, 0x74, 0x6f, 0x72, 0x3a, 0x20, 0x30, 0x78, 0x25, 0x75
	DB	0x78, 0x0d, 0x0a, 0x00


; Statistics:
; code size:	 4458 (0x116a) bytes ( 3.40%)
;           	 2229 (0x08b5) words
; udata size:	  195 (0x00c3) bytes (10.88%)
; access size:	   10 (0x000a) bytes


	end
