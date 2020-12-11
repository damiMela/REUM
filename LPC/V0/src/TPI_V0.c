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
#include <DR_ExtInt.h>

//primitivas
#include <PR/PR_Botones.h>
#include <PR/PR_Timers.h>
#include <PR/PR_Serial.h>
#include <PR/PR_Relays.h>
#include <PR/PR_PWM.h>
#include <PR/PR_ADC.h>


#include <AP/AP_Ultrasonido.h>


void func(void){
	invertRelay(RELAY0);
	TimerStart(0, 3, func, SEG);
}

int main(void) {
	InicializarSystick();
	InicializarPLL();

	InicializarADC();
//	InicializarSerial0();
	InicializarSerial1();

	InicializarBotones();
	InicializarRelays();
	InicilaizarPWM();

//	InicializarUS();
	InicializarEINT_DR();

	//-------------PRUEBA TIMERS------------//FUNCIONANDO
	TimerStart(0, 3, func, SEG);


	setDir(EXPANSION12, OUTPUT);
	setDir(EXPANSION13, OUTPUT);
	setDir(EXPANSION14, OUTPUT);
	setDir(EXPANSION15, OUTPUT);

	setPinmode_OP(RGB_R, MODE_OP_NLOW);
	setPinmode_OP(RGB_G, MODE_OP_NLOW);
	setPinmode_OP(RGB_B, MODE_OP_NLOW);

	//	TIMER0_EnableCount(1);


    while(1) {
    	//---agregar siempre---//
    	Timers_run();
    	ADC_run();
    	//---------------------//


    	//---------PRUEBA ADC-----------//FUNCIONANDO
    	static uint32_t prueba = 0;
    	prueba = getADC(ADC_2);
    	if(prueba > 1400) setRelay(RELAY3, ON);
    	else setRelay(RELAY3, OFF);


    	//----------PRUEBA BOTONES-----------//FUNCIONANDO
/*    	static uint8_t test_state = 0;
    	if(getBtn(SW4)){
    		test_state ^= 1;
    	}
    	if(test_state) setRelay(RELAY1, ON);
    	else setRelay(RELAY1, OFF);
*/

		//---------Prueba UART0 ------------//FUNCIONANDO
/*    	uint8_t hola [] = "hola\n";
    	uint8_t chau [] = "chau\n";
    	int32_t data = UART0_popRX();
		if(data != -1) {
			//UART0_pushTX((uint8_t) (data));
			if(data == 'h') UART0_SendString(hola);
			if(data == 'c') UART0_SendString(chau);
		}
*/


    	//--------PRUEBA UART1--------------//!!!
    	uint8_t hola [] = "hola\n";
		uint8_t chau [] = "chau\n";
		int32_t data = UART1_popRX();
		if(data != -1) {
			//UART0_pushTX((uint8_t) (data));
			if(data == 'h') UART1_SendString(hola);
			if(data == 'c') UART1_SendString(chau);
		}


    	//--------PRUEBA ULTRADSONIDO--------------//!!!



    	//---------PRUEBA MOTORES-----------//FUNCIONANDFO
/*    	setPin(EXPANSION12, ON);
    	setPin(EXPANSION13, OFF);
    	setPin(EXPANSION14, ON);
    	setPin(EXPANSION15, OFF);
    	setPWMDuty(PWM2, 60);
    	setPWMDuty(PWM3, 60);
*/

    }


}
