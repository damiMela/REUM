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
#include "DR_Tipos.h"
#include "DR_GPIO.h"
#include "DR_Systick.h"
#include "DR_PLL.h"
#include "infotronic.h"

//#define MY_DEBUG

int main(void) {
	inicializarSystick();
	InicializarPLL();
	setDir(BUZZER, OUTPUT);

	int state = HIGH;
	setPin(BUZZER, state);

    while(1) {
        if(get_ticks() == 500){
        	reset_ticks();
        	state = !state;
			setPin(BUZZER, state);
        }

    }
}
