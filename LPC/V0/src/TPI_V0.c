/*
===============================================================================
 Name        : TPI_V0.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include <DR/DR_Tipos.h>
#include <DR/DR_GPIO.h>
#include <DR/DR_Systick.h>
#include <DR/DR_PLL.h>
#include <DR/DR_ADC.h>
#include "infotronic.h"

//#define MY_DEBUG
int state = HIGH;

void func(void){
	state = !state;
	setPin(RELAY0, state);
	TimerStart(0, 5, func, SEG);
}

int main(void) {
	//para usar ADC flata en pinsel
	inicializarSystick();
	InicializarPLL();

	//apagar el maldito RGB
	setPinmode_OP(RGB_R, MODE_OP_NLOW);
	setPinmode_OP(RGB_G, MODE_OP_NLOW);
	setPinmode_OP(RGB_B, MODE_OP_NLOW);

	setDir(RELAY0, OUTPUT);
	setPin(RELAY0, state);

	TimerStart(0, 5, func, SEG);

    while(1) {
    	TimerLunchEvent();
    }
}
