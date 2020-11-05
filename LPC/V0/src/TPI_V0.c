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

//timer drivers
#include <DR/DR_Systick.h>
#include <DR/DR_PLL.h>

//pin select drivers
#include <DR/DR_Pinsel.h>
#include <DR/DR_GPIO.h>

//other drivers
#include <DR/DR_ADC.h>
#include <DR/DR_PWM.h>

//primitivas
#include <PR/PR_Botones.h>
#include <PR/PR_Timers.h>
#include <PR/PR_Serial.h>


int state = HIGH;

void func(void){
	state = !state;
	setPin(RELAY0, state);
	TimerStart(0, 3, func, SEG);
}

int main(void) {
	uint32_t prueba = 0;

/*	//apagar el maldito RGB
	setPinmode_OP(RGB_R, MODE_OP_NLOW);
	setPinmode_OP(RGB_G, MODE_OP_NLOW);
	setPinmode_OP(RGB_B, MODE_OP_NLOW);
*/
//----------------------------------//
	setPinsel(ADC0, FUNCION_3);

	setPinsel(RGB_R, FUNCION_1);
	setPinsel(RGB_G, FUNCION_1);
	setPinsel(RGB_B, FUNCION_1);
//----------------------------------//
	setDir(RELAY0, OUTPUT);
	setDir(RELAY1, OUTPUT);
	setDir(RELAY3, OUTPUT);

	setDir(SW1, INPUT);
	setDir(SW2, INPUT);
	setDir(SW3, INPUT);
	setDir(SW4, INPUT);
	setDir(SW5, INPUT);


	setPinmode(SW1, MODE_PULLUP);
	setPinmode(SW2, MODE_PULLUP);
	setPinmode(SW3, MODE_PULLUP);
	setPinmode(SW4, MODE_PULLUP);
	setPinmode(SW5, MODE_PULLUP);


	InicializarSystick();
	InicializarPLL();
	InicializarADC_DR();
	InicializarPWM();
	InicializarSerial(0);

	setPin(RELAY0, state);
	setPin(RELAY1, OFF);
	setPin(RELAY3, OFF);

	TimerStart(0, 3, func, SEG);

    while(1) {
    	//---agregar siempre---//
    	ReadInputs();
    	TimerLunchEvent();
    	//---------------------//

    	//**Prueba ADC
    	prueba = ADC_getVal();
    	if(prueba > 1400) setPin(RELAY3, ON);
    	else setPin(RELAY3, OFF);

    	//**Prueba entradas digitales
    	if(getBtn(BTN5))
    		setPin(RELAY1, ON);
    	else setPin(RELAY1, OFF);

    	//**Prueba PWM
		PWM_setDutyCicle(2, 50);
		PWM_setDutyCicle(3, 600);
		PWM_setDutyCicle(4, 750);


		//**Prueba UART0
		int32_t data = UART0_popRX();
		if(data != -1) {
			UART0_pushTX((uint8_t) (data));
		}
    }

}
