/*
===============================================================================
 Name        : TPI_V1.c
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

//systick and timer drivers
#include <DR/DR_Systick.h>
#include <DR/DR_PLL.h>

//pin select drivers
#include <DR/DR_Pinsel.h>
#include <DR/DR_GPIO.h>

//primitivas
#include <PR/PR_Botones.h>
#include <PR/PR_Timers.h>
#include <PR/PR_Serial.h>
#include <PR/PR_Relays.h>
#include <PR/PR_PWM.h>
#include <PR/PR_ADC.h>
#include <PR/PR_I2C.h>

int main(void) {
	InicializarSystick();
	InicializarPLL();

	InicializarADC();
	InicializarSerial0();
	InicializarSerial1();

	InicializarBotones();
	InicializarRelays();
	InicializarPWM();

    // TODO: insert code here
	//setDir(EXPANSION12, OUTPUT); -- ejemplo de uso

    while(1) {
    	//---agregar siempre---//
    	Timers_run();
    	ADC_run();
    	//---------------------//
    }

}