/*******************************************************************************************************************************//**
 *
 * @file		PR_RGB.c
 * @brief		Primitiva para controlar led rgb (sin pwm)
 * @date		Dec 19, 2020
 * @author		R2002 - Grupo2
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <PR/PR_RGB.h>
#include <DR/DR_GPIO.h>

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

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
	\fn  Nombre de la Funcion
	\brief Descripcion
 	\author R2002 - Grupo2
 	\date Dec 19, 2020
 	\param [in] parametros de entrada
*/
void InicializarRGB(void){
	setPinmode_OD(RGB_R, MODE_OD_NLOW);
	setPinmode_OD(RGB_G, MODE_OD_NLOW);
	setPinmode_OD(RGB_B, MODE_OD_NLOW);

	setDir(RGB_R, OUTPUT);
	setDir(RGB_G, OUTPUT);
	setDir(RGB_B, OUTPUT);

	setPin(RGB_R, LOW); //rojo
	setPin(RGB_G, LOW);
	setPin(RGB_B, LOW); //azul
}

/**
	\fn  setRGB
	\brief prende o apaga los leds del RGB
 	\author R2002 - Grupo2
 	\date Dec 19, 2020
 	\param [in] estado del led rojo
	\param [in] estado del led verde
	\param [in] estado del led azul
*/
void setRGB(uint8_t r, uint8_t g, uint8_t b){
	if(r > 1) r = 1;
	if(g > 1) g = 1;
	if(b > 1) b = 1;

	setPin(RGB_R, r);
	setPin(RGB_G, g);
	setPin(RGB_B, b);
}


/**
	\fn  setRGB_r
	\brief setea el led rojo en ON/OFF
 	\author R2002 - Grupo2
 	\date Dec 19, 2020
 	\param [in] estado de led rojo
*/
void setRGB_r(uint8_t state){
	if(state > 1) state = 1;
	setPin(RGB_R, state);
}


/**
	\fn  setRGB_g
	\brief setea el led verde en ON/OFF
 	\author R2002 - Grupo2
 	\date Dec 19, 2020
 	\param [in] estado de led verde
*/
void setRGB_g(uint8_t state){
	if(state > 1) state = 1;
	setPin(RGB_R, state);
}


/**
	\fn  setRGB_b
	\brief setea el led azul en ON/OFF
 	\author R2002 - Grupo2
 	\date Dec 19, 2020
 	\param [in] estado de led azul
*/
void setRGB_b(uint8_t state){
	if(state > 1) state = 1;
	setPin(RGB_R, state);
}


/**
	\fn  toggleRGB_r
	\brief invierte el estado del led rojo
 	\author R2002 - Grupo2
 	\date Dec 19, 2020
*/
void toggleRGB_r(){
	setPin(RGB_R, !getPin_raw(RGB_R));
}


/**
	\fn  toggleRGB_g
	\brief invierte el estado del led verde
 	\author R2002 - Grupo2
 	\date Dec 19, 2020
*/
void toggleRGB_g(){
	setPin(RGB_G, !getPin_raw(RGB_G));
}


/**
	\fn  toggleRGB_b
	\brief invierte el estado del led azul
 	\author R2002 - Grupo2
 	\date Dec 19, 2020
*/
void toggleRGB_b(){
	setPin(RGB_B, !getPin_raw(RGB_B));
}
