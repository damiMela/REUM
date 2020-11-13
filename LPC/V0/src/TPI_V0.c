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
#include <DR/DR_Timer0.h>

//pin select drivers
#include <DR/DR_Pinsel.h>

//other drivers
#include <DR/DR_ADC.h>
#include <DR_ExtInt.h>

//primitivas
#include <PR/PR_Botones.h>
#include <PR/PR_Timers.h>
#include <PR/PR_Serial.h>
#include <PR/PR_Relays.h>
#include <PR/PR_PWM.h>
#include <PR/PR_Ultrasonido.h>


void func(void){
	invertRelay(RELAY0);
	TimerStart(0, 3, func, SEG);
}

int main(void) {
//----------------------------------//
	setPinsel(ADC0, FUNCION_3);
//----------------------------------//
	InicializarSystick();
	InicializarPLL();

	InicializarADC_DR();

//	InicializarBotones();
	InicializarRelays();
	InicializarSerial(0);
	InicilaizarPWM();

	InicializarTimer0_DR();
	InicializarUs();
	EINTInit();


//	TimerStart(0, 3, func, SEG);
//	TIMER0_EnableCount(1);

    while(1) {
    	//---agregar siempre---//
 //   	ReadInputs();
    	TimerLunchEvent();
    	readUS();
    	//---------------------//


    	//**Prueba ADC
    	static uint32_t prueba = 0;
    	prueba = ADC_getVal();
    	if(prueba > 1400) setRelay(RELAY3, ON);
    	else setRelay(RELAY3, OFF);


    	//**Prueba entradas digitales
/*    	if(getBtn(SW4))
    		setRelay(RELAY1, ON);
    	else setRelay(RELAY1, OFF);
*/

		//**Prueba UART0
		/*int32_t data = UART0_popRX();
		if(data != -1) {
			UART0_pushTX((uint8_t) (data));
		}*/

		//**Motores (sin probar)**//
		//setMotoresDir(ADELANTE);
		//setPWMDuty(PWM2, 0);
		//setPWMDuty(PWM3, 80);

/*    	if(TIMER0_getTime() >= 100){
    		invertRelay(RELAY2);
    		TIMER0_rstTime();
    	}*/
    	/*if(US_result > 20){
    		invertRelay(RELAY2);
    	}*/

    }


}
