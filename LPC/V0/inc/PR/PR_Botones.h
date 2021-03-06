/*******************************************************************************************************************************//**
 *
 * @file		PR_Botones.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		Oct 27, 2020
 * @author		R2002 - Grupo2
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef PR_PR_BOTONES_H_
#define PR_PR_BOTONES_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <DR/DR_Tipos.h>
#include <DR/DR_GPIO.h>
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
enum btn{SW1, SW2, SW3, SW4, SW5};
/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/


/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void InicializarBotones(void);
void ReadInputs(void);
uint8_t getBtn(uint8_t n);

#endif /* PR_PR_BOTONES_H_ */
