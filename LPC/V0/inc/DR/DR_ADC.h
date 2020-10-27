/*******************************************************************************************************************************//**
 *
 * @file		DR_ADC.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		Sep 28, 2020
 * @author		R2002 - Grupo2
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef DR_DR_ADC_H_
#define DR_DR_ADC_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <DR/DR_Tipos.h>
#include <DR/DR_PLL.h>
#include <DR/DR_Pinsel.h>
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
extern uint8_t ADC_inUse;

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void inicializarADC(void);
uint32_t ADC_getVal(void);
void ADC_startConvertion(void);

#endif /* DR_DR_ADC_H_ */
