;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 3.3.0 #8604 (Dec 30 2013) (Linux)
; This file was generated Wed Aug 27 21:11:52 2014
;--------------------------------------------------------
; PIC16 port for the Microchip 16-bit core micros
;--------------------------------------------------------
	list	p=18f4550
	radix	dec


;--------------------------------------------------------
; public variables in this module
;--------------------------------------------------------
	global	___uflags
	global	__entry
	global	__startup

;--------------------------------------------------------
; extern variables in this module
;--------------------------------------------------------
	extern	_stack_end
	extern	_TBLPTRU
	extern	_TBLPTRH
	extern	_TBLPTRL
	extern	_FSR0L
	extern	_FSR0H
	extern	_TABLAT
	extern	_POSTINC0
	extern	_main
	extern	_cinit


	idata
___uflags	db	0x00

;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
; ; Starting pCode block
S_crt0i___entry	code	0X000000
__entry:
	goto __startup
	
; I code from now on!
; ; Starting pCode block
S_crt0i___startup	code
__startup:
	; Initialize the stack pointer
	lfsr 1, _stack_end
	lfsr 2, _stack_end
	; 1st silicon does not do this on POR
	clrf _TBLPTRU, 0
	; Initialize the flash memory access configuration.
	; This is harmless for non-flash devices, so we do it on all parts.
	bsf 0xa6, 7, 0 ; EECON1.EEPGD = 1, TBLPTR accesses program memory
	bcf 0xa6, 6, 0 ; EECON1.CFGS = 0, TBLPTR accesses program memory
	; TBLPTR = &cinit
	movlw low(_cinit)
	movwf _TBLPTRL, 0
	movlw high(_cinit)
	movwf _TBLPTRH, 0
	movlw upper(_cinit)
	movwf _TBLPTRU, 0
	; 0x05 = cinit.num_init
	tblrd*+
	movff _TABLAT, 0x05
	tblrd*+
	movff _TABLAT, (0x05 + 1)
	; while (0x05)
	bra entry_loop_dec
entry_loop:
	; Count down so we only have to look up the data in _cinit once.
	; At this point we know that TBLPTR points to the top of the current
	; entry in _cinit, so we can just start reading the from, to, and
	; size values.
	; Read the source address low.
	; 0x00 = 0x07 ->from;
	tblrd*+
	movff _TABLAT, 0x00
	; source address high
	tblrd*+
	movff _TABLAT, (0x00 + 1)
	; source address upper
	tblrd*+
	movff _TABLAT, (0x00 + 2)
	; Skip 0 byte since it is stored as 0 32bit int.
	tblrd*+
	; Read the destination address directly into FSR0
	; destination address low.
	; FSR0 = (unsigned short)0x07 ->to;
	tblrd*+
	movff _TABLAT, _FSR0L
	; destination address high
	tblrd*+
	movff _TABLAT, _FSR0H
	; Skip two bytes since it is stored as 0 32bit int.
	tblrd*+
	tblrd*+
	; Read the size of data to transfer to destination address.
	; 0x03 = (unsigned short)0x07 ->size;
	tblrd*+
	movff _TABLAT, 0x03
	tblrd*+
	movff _TABLAT, (0x03 + 1)
	; Skip two bytes since it is stored as 0 32bit int.
	tblrd*+
	tblrd*+
	; 0x00 = 0x07 ->from;
	; FSR0 = (unsigned short)0x07 ->to;
	; 0x03 = (unsigned short)0x07 ->size;
	; The table pointer now points to the next entry. Save it
	; off since we will be using the table pointer to do the copying
	; for the entry.
	; 0x07 = TBLPTR
	movff _TBLPTRL, 0x07
	movff _TBLPTRH, (0x07 + 1)
	movff _TBLPTRU, (0x07 + 2)
	; Now assign the source address to the table pointer.
	; TBLPTR = 0x00
	movff 0x00, _TBLPTRL
	movff (0x00 + 1), _TBLPTRH
	movff (0x00 + 2), _TBLPTRU
	bra copy_loop_dec
copy_loop:
	tblrd*+
	movff _TABLAT, _POSTINC0
copy_loop_dec:
	; while (--0x03);
	; Decrement and test the byte counter.
	; The cycle ends when the value of counter reaches the -1.
	decf 0x03, f, 0
	bc copy_loop
	decf (0x03 + 1), f, 0
	bc copy_loop
	; Restore the table pointer for the next entry.
	; TBLPTR = 0x07
	movff 0x07, _TBLPTRL
	movff (0x07 + 1), _TBLPTRH
	movff (0x07 + 2), _TBLPTRU
entry_loop_dec:
	; while (--0x05);
	; Decrement and test the entry counter.
	; The cycle ends when the value of counter reaches the -1.
	decf 0x05, f, 0
	bc entry_loop
	decf (0x05 + 1), f, 0
	bc entry_loop
	
;	.line	240; /usr/share/sdcc/lib/src/pic16/startup/crt0i.c	main ();
	CALL	_main
lockup:
	; Returning from main will lock up.
	bra lockup
	


; Statistics:
; code size:	  218 (0x00da) bytes ( 0.17%)
;           	  109 (0x006d) words
; udata size:	    0 (0x0000) bytes ( 0.00%)
; access size:	    0 (0x0000) bytes


	end
