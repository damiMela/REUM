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

	setPinsel(USB_TX, FUNCION_1);
	setPinsel(USB_RX, FUNCION_1);

//----------------------------------//
	setDir(RELAY0, OUTPUT);
	setDir(RELAY1, OUTPUT);
	setDir(RELAY3, OUTPUT);
	setDir(IN0, INPUT);
	setDir(SW2, INPUT);
	setDir(SW3, INPUT);


	setPinmode(IN0, MODE_PULLUP);
	setPinmode(SW2, MODE_PULLUP);
	setPinmode(SW3, MODE_PULLUP);


	//para usar ADC flata en pinsel
	InicializarSystick();
	InicializarPLL();
	InicializarADC();
	InicializarPWM();
	InicializarSerial();

	setPin(RELAY0, state);
	setPin(RELAY1, OFF);
	setPin(RELAY3, OFF);

	TimerStart(0, 3, func, SEG);

    while(1) {
    	debounceRead();
    	TimerLunchEvent();

    	prueba = ADC_getVal();
    	if(prueba > 1400) setPin(RELAY3, ON);
    	else setPin(RELAY3, OFF);

    	if((InputBuff & (1 << 2)))
    		setPin(RELAY1, ON);
    	else setPin(RELAY1, OFF);

		PWM_setDutyCicle(2, 50);
		PWM_setDutyCicle(3, 600);
		PWM_setDutyCicle(4, 750);

		int32_t data = UART0_popRX();

		if(data != -1) {
			UART0_pushTX((uint8_t) (data));
		}
    }

}
