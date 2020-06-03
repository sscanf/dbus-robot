
char ContadorC,ContadorB,ContadorA;

void delay_1ms (void)
{
// Código de retardo generado por PikLoops (vie nov-2009-13 00:45:06)
// Tiempo de retardo = 0.09999960  con  Osc = 20.00000000MHz
//movff   0xfe4, 0xfd9

	__asm

			; Código de retardo generado por PikLoops (sáb nov-2009-14 02:57:28)
			; Tiempo de retardo = 0.00099980  con  Osc = 20.00000000MHz

retraso_0.001_seg:
		movlw	D'7'
		movwf	_ContadorB
		movlw	D'124'
		movwf	_ContadorA
retraso_0.001_seg_bucle:
		decfsz	_ContadorA,1
		goto	retraso_0.001_seg_bucle
				
		decfsz	_ContadorB,1
		goto	retraso_0.001_seg_bucle
__endasm;
}

void delay_ms (unsigned long ms)
{
	for (;ms>0;ms--)
		delay_1ms();
}
