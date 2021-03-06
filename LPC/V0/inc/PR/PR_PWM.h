/*******************************************************************************************************************************//**
 *
 * @file		PR_PWM.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		13 nov. 2020
 * @author		R2002 - grupo2
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef PR_PR_PWM_H_
#define PR_PR_PWM_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <DR/DR_PWM.h>
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
enum {PWM1, PWM2, PWM3};
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
void InicializarPWM(void);
void setPWMDuty(uint8_t n, uint16_t val);
void setPWMOff(void);
uint8_t getPWMDuty(uint8_t n);

#endif /* PR_PR_PWM_H_ */
