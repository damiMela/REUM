/*******************************************************************************************************************************//**
 *
 * @file		PR_Botones.c
 * @brief		Descripcion del modulo
 * @date		Oct 27, 2020
 * @author		R2002 - Grupo2
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <DR/DR_GPIO.h>
#include <PR/PR_Botones.h>
/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define CANT_ENTRADAS 5  //MAX:8. Sino cambiar el tipo de variable de buffer y lectura
#define CANT_ACEPT_CYCLES 3
/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
static uint8_t cycleCounter[CANT_ENTRADAS];
static uint8_t InputBuff = 0;
/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/
/**
	\fn  InicializarBotones
	\brief Inicializar botones como entradas y configuara pinmodes
 	\author R2002 - Grupo2
 	\date Oct 27, 2020
*/
void InicializarBotones(void){
	setDir(SW1_P, INPUT);
	setDir(SW2_P, INPUT);
	setDir(SW3_P, INPUT);
	setDir(SW4_P, INPUT);
	setDir(SW5_P, INPUT);


	setPinmode(SW1_P, MODE_PULLUP);
	setPinmode(SW2_P, MODE_PULLUP);
	setPinmode(SW3_P, MODE_PULLUP);
	setPinmode(SW4_P, MODE_PULLUP);
	setPinmode(SW5_P, MODE_PULLUP);
}


/**
	\fn  ReadInputs
	\brief lectura y debounce de entradas digitales. Debe estar en el loop
 	\author R2002 - Grupo2
 	\date Oct 27, 2020
*/
void ReadInputs(void){
	uint8_t lectura = 0, input_n, cambios;

	if(getPin(SW1_P, ON_LOW)) lectura = (1 << SW1);
	if(getPin(SW2_P, ON_LOW)) lectura |= (1 << SW2);
	if(getPin(SW3_P, ON_LOW)) lectura |= (1 << SW3);
	if(getPin(SW4_P, ON_LOW)) lectura |= (1 << SW4);
	if(getPin(SW5_P, ON_LOW)) lectura |= (1 << SW5);

	cambios = (InputBuff ^ lectura);

	if(cambios){
		for(input_n = 0; input_n < CANT_ENTRADAS; input_n++){
			if(cambios & (1 << input_n)){
				cycleCounter[input_n]++;	cycleCounter[input_n] %= CANT_ACEPT_CYCLES;

				if(!cycleCounter[input_n])
					InputBuff ^= (1 << input_n);
			}
			else cycleCounter[input_n] = 0;
		}
	}
	else{
		for(input_n=0; input_n < CANT_ENTRADAS; input_n++)
			cycleCounter[input_n] = 0;
	}
}

/**
	\fn  getBtn
	\brief devuelve el estado de uno de los botones (SWx_P)
 	\author R2002 - Grupo2
 	\date Oct 27, 2020
 	\param [in] número de botón (SWx)
	\return 1 o 0 según si el botón estaba presionado
*/
uint8_t getBtn(uint8_t n){
	return (InputBuff & (1 << n));
}
