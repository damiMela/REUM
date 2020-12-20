/*******************************************************************************************************************************//**
 *
 * @file		PR_Relays.c
 * @brief		Descripcion del modulo
 * @date		Nov 5, 2020
 * @author		R2002 - Grupo2
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <PR/PR_Relays.h>
#include <DR/DR_Pinsel.h>
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
	\fn InicializarRelay
	\brief Inicialización de las salidas de los realys.
 	\author R2002 - Grupo2
 	\date Nov 5, 2020
*/
void InicializarRelays(void){
	setDir(RELAY0_P, OUTPUT);
	setDir(RELAY1_P, OUTPUT);
	setDir(RELAY2_P, OUTPUT);
	setDir(RELAY3_P, OUTPUT);

	setPinmode_OD(RELAY0_P, MODE_OD_NHIGH);
	setPinmode_OD(RELAY1_P, MODE_OD_NHIGH);
	setPinmode_OD(RELAY2_P, MODE_OD_NHIGH);
	setPinmode_OD(RELAY3_P, MODE_OD_NHIGH);

	setPin(RELAY0_P, !OFF);
	setPin(RELAY1_P, !OFF);
	setPin(RELAY2_P, !OFF);
	setPin(RELAY3_P, !OFF);
}


/**
	\fn setRelay
	\brief Setea el relay seleccionado en el estado recivido
 	\author R2002 - Grupo2
 	\date Nov 5, 2020
 	\param [in] Relay al cual se le va a signar un estado
 	\param [in] estado a asignar (ON - OFF)
*/
void setRelay(uint8_t n, uint8_t state){
	switch(n){
		case RELAY0:	setPin(RELAY0_P, !state);	break;
		case RELAY1:	setPin(RELAY1_P, !state);	break;
		case RELAY2:	setPin(RELAY2_P, !state);	break;
		case RELAY3:	setPin(RELAY3_P, !state);	break;
	}
}

void invertRelay(uint8_t n){
	uint8_t state;
	switch(n){
			case RELAY0:
				state = getPin(RELAY0_P, ON_LOW);
				setPin(RELAY0_P, !state);
				break;
			case RELAY1:
				state = getPin(RELAY1_P, ON_LOW);
				setPin(RELAY1_P, !state);
				break;
			case RELAY2:
				state = getPin(RELAY2_P, ON_LOW);
				setPin(RELAY2_P, !state);
				break;
			case RELAY3:
				state = getPin(RELAY3_P, ON_LOW);
				setPin(RELAY3_P, !state);
				break;
		}
}
