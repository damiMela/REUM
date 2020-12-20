/*******************************************************************************************************************************//**
 *
 * @file		PW_Serial.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		Nov 4, 2020
 * @author		R2002 - Grupo2
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef PR_PR_SERIAL_H_
#define PR_PR_SERIAL_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/

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
// extern tipo nombreVariable;

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void InicializarSerial0();
int32_t UART0_popRX(void);
void UART0_pushTX(uint8_t dato);
uint8_t UART0_popString(void);
void UART0_SendString(uint8_t* msj);

void InicializarSerial1();
int32_t UART1_popRX(void);
void UART1_pushTX(uint8_t dato);
uint8_t UART1_popString(void) ;
void UART1_SendString(uint8_t* msj);

#endif /* PR_PR_SERIAL_H_ */
