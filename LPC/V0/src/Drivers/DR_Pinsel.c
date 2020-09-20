/*******************************************************************************************************************************//**
 *
 * @file		DR_Pinsel.c
 * @brief		Drivers para utilización del registro PINSEL
 * @date		Sep 19, 2020
 * @author		R2002 - Grupo2
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_Pinsel.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/
#define  PINSEL  ((__RW uint32_t* ) 0x4002C000)
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
	\fn  setPinsel
	\brief Setea un pin determinado para ser utilizado con el modo especificado.
 	\author R2002 - Grupo2
 	\date Sep 19, 2020
 	\param [in] Número de puerto.
 	\param [in] Número de pin.
 	\param [in] Número de función. USAR DEFINES "FUNCION_N"
 */
void setPinsel(uint8_t port, uint8_t pin, uint8_t f_number){
	PINSEL[port*2 + pin/16] &= ~(3 << (pin%16)*2); //"limpiar" bits en los que se va a escribir
	PINSEL[port*2 + pin/16] |=  f_number << (( pin % 16) * 2);
}
