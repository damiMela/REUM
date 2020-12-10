/*******************************************************************************************************************************//**
 *
 * @file		PR_PWM.c
 * @brief		Descripcion del modulo
 * @date		13 nov. 2020
 * @author		R2002 - Grupo2
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <PR/PR_PWM.h>
#include <DR/DR_Pinsel.h>
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
 	\author Ing. Marcelo Trujillo
 	\date 13 nov. 2020
 	\param [in] parametros de entrada
 	\param [out] parametros de salida
	\return tipo y descripcion de retorno
*/
void InicilaizarPWM(void){
	InicializarPWM_DR();

	setPinsel(EXPANSION11, FUNCION_3); //PWM chnl 2
	setPinsel(EXPANSION6, FUNCION_3); //PWM chnl 3
}


void setPWMDuty(uint8_t n, uint16_t val){
	PWM_buff[n] = val*10;
}

void setPWMOff(uint8_t n){
	for(uint8_t i = 0; i < CANT_PWM; i++){
		PWM_buff[i] = 0;
	}
}

uint16_t getPWMDuty(uint8_t n){
	return PWM_buff[n]/10;
}
