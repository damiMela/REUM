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

//systick and timer drivers
#include <DR/DR_Systick.h>
#include <DR/DR_PLL.h>
#include <DR/DR_Timer0.h>

//pin select drivers
#include <DR/DR_Pinsel.h>

//other drivers
#include <DR/DR_ExtInt.h>

//primitivas
#include <PR/PR_Botones.h>
#include <PR/PR_Timers.h>
#include <PR/PR_Serial.h>
#include <PR/PR_Relays.h>
#include <PR/PR_PWM.h>
#include <PR/PR_ADC.h>
#include <PR/PR_RGB.h>
#include <PR/PR_BMP280.h>
#include <PR/PR_AM2320.h>

#include <AP/AP_Ultrasonido.h>



void func(void){
	toggleRGB_r();
	TimerStart(0, 3, func, SEG);
}

int main(void) {
	InicializarSystick();
	InicializarPLL();

//	InicializarADC();
	InicializarSerial0();
	InicializarSerial1();
//	InicializarI2C();

	InicializarBotones();
	InicializarRelays();
	InicializarPWM();

//	InicializarUS();
	InicializarEINT_DR();

	InicializarRGB();

	//-------------PRUEBA TIMERS------------//FUNCIONANDO
	TimerStart(0, 3, func, SEG);

	//setRGB(0, 0, 0);


	setDir(EXPANSION12, OUTPUT);
	setDir(EXPANSION13, OUTPUT);
	setDir(EXPANSION14, OUTPUT);
	setDir(EXPANSION15, OUTPUT);

	//	TIMER0_EnableCount(1);
	InicializarAM2320();

	setRelay(RELAY1, OFF);
	setRelay(RELAY2, OFF);
	setRelay(RELAY3, OFF);

    while(1) {
    	//---agregar siempre---//
    	Timers_run();
    	ADC_run();
    	//---------------------//


    	//---------PRUEBA ADC-----------//FUNCIONANDO
/*    	static uint32_t prueba = 0;
    	prueba = getADC(ADC_2);
    	if(prueba > 1400) setRelay(RELAY3, ON);
    	else setRelay(RELAY3, OFF);
*/

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
		int16_t data = UART1_popRX();

		if(data != -1) {
			UART0_pushTX((uint8_t) (data));
			if(data == 'c') setPin(RGB_G, ON);
			if(data == 's') {
				setRelay(RELAY0, OFF);
				setRelay(RELAY1, OFF);
				setRelay(RELAY2, OFF);
				setRelay(RELAY3, OFF);
			}
			if(data == 'f') setRelay(RELAY0, ON);
			if(data == 'b') setRelay(RELAY1, ON);
			if(data == 'l') setRelay(RELAY2, ON);
			if(data == 'r') setRelay(RELAY3, ON);
			if(data == 's') UART1_pushTX('s');

		}

		uint8_t temp1 [] = "#t#25";
		uint8_t temp2 [] = "#t#12";
		uint8_t humed [] = "#h#42";
		uint8_t pres1 [] = "#p#20";
		uint8_t pres2 [] = "#p#60";

		if(getBtn(SW5)) UART1_SendString(temp1);
		if(getBtn(SW4)) UART1_SendString(temp2);
		if(getBtn(SW3)) UART1_SendString(humed);
		if(getBtn(SW2)) UART1_SendString(pres1);
		if(getBtn(SW1)) UART1_SendString(pres2);



    	//--------PRUEBA ULTRADSONIDO--------------//!!!



    	//---------PRUEBA MOTORES-----------//FUNCIONANDFO
/*    	setPin(EXPANSION12, ON);
    	setPin(EXPANSION13, OFF);
    	setPin(EXPANSION14, ON);
    	setPin(EXPANSION15, OFF);
    	setPWMDuty(PWM2, 60);
    	setPWMDuty(PWM3, 60);
*/

    	//--------PRUEBA I2C-----------------//FUNCIONANDO - descomentar BMP280_run()
/*		uint32_t temp = 0, pres = 0;
		BMP280_getData();
		temp =  getBMP280_temp();
		pres =  getBMP280_pres();

		if(temp >= 2820) setRelay(RELAY2, ON);
		else setRelay(RELAY2, OFF);
*/
		//AM2320_getData();


    }


}
