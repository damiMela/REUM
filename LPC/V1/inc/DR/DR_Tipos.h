/*******************************************************************************************************************************//**
 *
 * @file		DR_Tipos.h
 * @brief		Definición de tipo de datos
 * @date		Sep 19, 2020
 * @author		R2002 - Grupo2
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef DR_DR_TIPOS_H_
#define DR_DR_TIPOS_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <infotronic.h>
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define PORT0	0
#define PORT1	1
#define PORT2	2
#define PORT3	3
#define PORT4	4

enum {DISABLE, ENABLE};
/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/
#define     __R             volatile const 	//< solo lectura
#define 	__W     		volatile 		//< solo escritura
#define 	__RW            volatile 		//< lectura / escritura
/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/
typedef	unsigned int		uint32_t;
typedef	int					int32_t;
typedef	short unsigned int	uint16_t;
typedef	short int			int16_t;
typedef	unsigned char		uint8_t ;
typedef	char				int8_t;
/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
// extern tipo nombreVariable;

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/

#endif /* DR_DR_TIPOS_H_ */
