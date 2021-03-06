/*******************************************************************************************************************************//**
 *
 * @file		PR_LCD.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		Dec 21, 2020
 * @author		R2002 - Grupo2
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef PR_PR_LCD_H_
#define PR_PR_LCD_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <DR/DR_Tipos.h>
#include <DR/DR_LCD.h>
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define		LCD_CONTROL		0 /*!< Macro para cuando envio un comando de control*/
#define		LCD_DATA		1 /*!< Macro para cuando envio un dato*/
#define		RENGLON_1		0x00 /*!< Macro para indicar que quiero escribir en el renglon 1*/
#define		RENGLON_2		0x40 /*!< Macro para indicar que quiero escribir en el renglon 2*/
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
void Display_lcd( char *, char, char);
void Display_LCD( char *, char , char );
#endif /* PR_PR_LCD_H_ */
