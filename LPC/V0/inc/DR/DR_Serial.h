/*******************************************************************************************************************************//**
 *
 * @file		DR_Serial.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		Oct 24, 2020
 * @author		R2002 - Grupo2
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef DR_DR_SERIAL_H_
#define DR_DR_SERIAL_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <DR/DR_Tipos.h>
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define TX_PIN
#define RX_PIN

#define 	RX_BUFF_SIZE		64
#define 	TX_BUFF_SIZE		64
/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
extern volatile uint8_t UART0_rx_buff[];
extern volatile uint32_t UART0_rx_in, UART0_rx_out;

extern volatile uint8_t UART0_tx_buff[];
extern volatile uint32_t UART0_tx_in, UART0_tx_out;

extern volatile uint8_t UART0_tx_flag;

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void InicializarUART0(void);

void UART0_pushRX(uint8_t dato);
int32_t UART0_popTX(void);

void UART0_forceTX(uint8_t dato);

#endif /* DR_DR_SERIAL_H_ */
