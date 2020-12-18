/*******************************************************************************************************************************//**
 *
 * @file		PR_IntTime.c
 * @brief		Descripcion del modulo
 * @date		13 nov. 2020
 * @author		R2002 - grupo2
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <PR/PR_IntTime.h>
#include <DR/DR_ExtInt.h>
#include <DR/DR_Pinsel.h>
#include <DR/DR_Timer0.h>

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define INTERRUPT_N INTS
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
 	\author Ing. Marcelo Trujillo
 	\date 13 nov. 2020
 	\param [in] parametros de entrada
 	\param [out] parametros de salida
	\return tipo y descripcion de retorno
*/
void InicializarIntTime(void){
	setPinsel(EINT2_P, FUNCION_1);
	setDir(EINT2_P, INPUT);

	InicializarTimer0_DR();
	InicializarEINT_DR();

	TIMER0_rstTime();
	TIMER0_EnableCount(ENABLE);
}

void enableIntTime(uint8_t state){
	if(state){
		TIMER0_EnableCount(ENABLE);
		EINT_Enable(2, ENABLE);
	}
	else{
		TIMER0_EnableCount(DISABLE);
		EINT_Enable(2, DISABLE);
	}
}

uint32_t getIntTime(void){
	return intTime;
}
