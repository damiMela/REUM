/*******************************************************************************************************************************//**
 *
 * @file		PR_Serial.c
 * @brief		Descripcion del modulo
 * @date		Nov 4, 2020
 * @author		R2002 - Grupo2
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <DR/DR_Pinsel.h>
#include <DR/DR_Serial.h>
#include <PR/PR_Serial.h>


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
	\fn  InicializarSerial
	\brief Inicializa la UART elegida
 	\author R2002 - Grupo2
 	\date Nov 4, 2020
 	\param [in] Número de UART a inicializar
*/
void InicializarSerial0() {
	InicializarUART0_DR();
	setPinsel(USB_TX, FUNCION_1);
	setPinsel(USB_RX, FUNCION_1);
}
void InicializarSerial3() {
	InicializarUART3_DR();
	setPinsel(SERIAL_TX, FUNCION_3);
	setPinsel(SERIAL_RX, FUNCION_3);
}


/**
	\fn  UART0_popRX
	\brief Pop del buffer de recepción
 	\author R2002 - Grupo2
 	\date Nov 4, 2020
	\return valor leído del buffer
*/
int32_t UART0_popRX(void) {
	int32_t ret = -1;
	if(UART0_rx_in != UART0_rx_out){
		ret = UART0_rx_buff[UART0_rx_out];
		UART0_rx_out++; 	UART0_rx_out%=RX_BUFF_SIZE;
	}
	return ret;
}


/**
	\fn  UART0_pushTX
	\brief push al buffer de transmición para luego ser enviado
 	\author R2002 - Grupo2
 	\date Nov 4, 2020
 	\param [in] dato para poner el la cola de envío
*/
void UART0_pushTX(uint8_t dato) {
	if(!UART0_tx_flag) {
		UART0_forceTX(dato);
		UART0_tx_flag = 1;
	}
	else {
		UART0_tx_buff[UART0_tx_in] = dato;
		UART0_tx_in++;
		if(UART0_tx_in == TX_BUFF_SIZE)  UART0_tx_in = 0;
	}
}


/**
	\fn  UART0_SendString
	\brief envio de un String a través de la UART0
 	\author R2002 - Grupo2
 	\date Nov 4, 2020
 	\param [in] String a enviar
*/
void UART0_SendString(uint8_t* msj){
	uint32_t i = 0;
	while(msj[i] > 0){
		if(i == 0) {
			UART0_forceTX(msj[i]);
		}
		else{
			UART0_pushTX(msj[i]);
		}
		i++;
	}
}

/**********************************************************************************************************************************/
/**
	\fn  UART3_popRX
	\brief Pop del buffer de recepción
 	\author R2002 - Grupo2
 	\date Nov 4, 2020
	\return valor leído del buffer
*/
int32_t UART3_popRX(void) {
	uint32_t ret = -1;
	if(UART3_rx_in != UART3_rx_out){
		ret = UART3_rx_buff[UART3_rx_out];
		UART3_rx_out++; 	UART3_rx_out%=RX_BUFF_SIZE;
	}
	return ret;
}

/**
	\fn  UART3_pushTX
	\brief push al buffer de transmición para luego ser enviado
 	\author R2002 - Grupo2
 	\date Nov 4, 2020
 	\param [in] dato para poner el la cola de envío
*/
void UART3_pushTX(uint8_t dato) {
	if(UART3_tx_flag) {
 		UART3_tx_buff[UART3_tx_in] = dato;
		UART3_tx_in++;		UART3_tx_in %= TX_BUFF_SIZE;
	} else {
		UART3_forceTX(dato);
		UART3_tx_flag = 1;
	}
}

/**
	\fn  UART3_SendString
	\brief envio de un String a través de la UART3
 	\author R2002 - Grupo2
 	\date Nov 4, 2020
 	\param [in] String a enviar
*/
void UART3_SendString(uint8_t* msj){
	uint32_t i = 0;
	while(msj[i] > 0){
		if(i == 0) {
			UART3_forceTX(msj[i]);
		}
		else{
			UART3_pushTX(msj[i]);
		}
		i++;
	}
}
