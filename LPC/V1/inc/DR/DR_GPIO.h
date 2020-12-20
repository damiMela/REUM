/*******************************************************************************************************************************//**
 *
 * @file		DR_GPIO.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		Sep 19, 2020
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef DR_DR_GPIO_H_
#define DR_DR_GPIO_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <DR/DR_Tipos.h>
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define	MODE_PULLUP		0
#define	MODE_REPEATER	1
#define	MODE_NONE		2
#define	MODE_PULLDOWN	3

#define	MODE_OD_NHIGH	0 //Normal HIGH. Prendido con 0v
#define	MODE_OD_NLOW	1 //Normal LOW.  Prendido con vcc

//para lectura.
#define ON_LOW 	0 //ON cuando hay un 0.
#define ON_HIGH 1 //ON cuando hay un 1.

#define INPUT	0
#define OUTPUT	1

//estados. Ambas opciones para comodidad y/o mejor uso.
#define LOW 	0
#define HIGH	1		//para escribir en pines

#define OFF		0
#define ON		1		//para leer estado de pines
/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
// extern tipo nombreVariable;

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void 	setPinmode(uint8_t port, uint8_t pin, uint8_t mode);
void 	setPinmode_OD(uint8_t port, uint8_t pin, uint8_t mode);
void 	setDir(uint8_t port, uint8_t pin, uint8_t mode);
void 	setPin(uint8_t port, uint8_t pin, uint8_t state);
uint8_t getPin(uint8_t port, uint8_t pin, uint8_t mode);
uint8_t getPin_raw(uint8_t port, uint8_t pin);

#endif /* DR_DR_GPIO_H_ */
