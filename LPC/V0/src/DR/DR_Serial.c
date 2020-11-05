/*******************************************************************************************************************************//**
 *
 * @file		DR_Serial.c
 * @brief		Drivers de comunicación serial
 * @date		Nov 4, 2020
 * @author		R2002 - Grupo2
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <DR/DR_Serial.h>
#include <DR/DR_PLL.h>
#include <DR/DR_Pinsel.h>
/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define     UART0       ((UART_t *) 0x4000C000UL )

/*se puede usar la misma estructura de datos porque la parte de modem no
 * es usada y los bits y registros asociados al modem estan
 * como "reservados" */
#define     UART3       ((UART_t *) 0x4001C000UL )

/***********************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/
#define	POWER_UART0_ON		PCONP |= (1 << PUART0);
#define	POWER_UART0_OFF		PCONP &= ~(1 << PUART0);

#define	POWER_UART3_ON		PCONP |= (1 << PUART3);
#define	POWER_UART3_OFF		PCONP &= ~(1 << PUART3);
/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/
typedef struct _UART_LCR_t{
	uint8_t wordLength:2;
	uint8_t stopBit: 1;
	uint8_t parityEn: 1;
	uint8_t paritySel: 2;
	uint8_t breakCtrl: 1;
	uint8_t DLAB: 1;

}UART_LCR_t;

typedef struct _UART_IIR{
	uint32_t intStatus: 1;
	uint32_t intId: 3;
	uint32_t RESERVED_0: 2;
	uint32_t FIFOEn: 2;
	uint32_t ABEOInt: 1;
	uint32_t ABTOInt: 1;
	uint32_t RESERVED_1: 22;

}UART_IIR;

typedef struct _UART_IER_t{
	uint32_t RBR_intEn: 1;
	uint32_t THRE_intEn: 1;
	uint32_t RLS_intEn: 1;
	uint32_t RESERVED_0: 5;
	uint32_t ABEO_IntEn: 1;
	uint32_t ABTO_IntEn: 1;
	uint32_t RESERVED_1: 22;
}UART_IER_t;

typedef struct _UART_t{
    union {
    __R  uint8_t  RBR;
    __W  uint8_t  THR;
    __RW uint8_t  DLL;
        uint32_t RESERVED0;
    };
    union {
    __RW uint8_t  DLM;
    __RW UART_IER_t IER;
    };
    union {
    __R  UART_IIR IIR;
    __W  uint8_t  FCR;
    };
    __RW UART_LCR_t  LCR;
        uint8_t  RESERVED1[7];
    __R  uint8_t  LSR;
        uint8_t  RESERVED2[7];
    __RW uint8_t  SCR;
        uint8_t  RESERVED3[3];
    __RW uint32_t ACR;
    __RW uint8_t  ICR;
        uint8_t  RESERVED4[3];
    __RW uint8_t  FDR;
        uint8_t  RESERVED5[7];
    __RW uint8_t  TER;
        uint8_t  RESERVED6[39];
    __RW uint32_t FIFOLVL;
} UART_t;

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
volatile uint8_t UART0_rx_buff[RX_BUFF_SIZE];
volatile uint32_t UART0_rx_in, UART0_rx_out;

volatile uint8_t UART0_tx_buff[TX_BUFF_SIZE];
volatile uint32_t UART0_tx_in, UART0_tx_out;

volatile uint8_t UART0_tx_flag;


volatile uint8_t UART3_rx_buff[RX_BUFF_SIZE];
volatile uint32_t UART3_rx_in, UART3_rx_out;

volatile uint8_t UART3_tx_buff[TX_BUFF_SIZE];
volatile uint32_t UART3_tx_in, UART3_tx_out;

volatile uint8_t UART3_tx_flag;
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

//UART0
/**********************************************************************************************************************************/
/**
	\fn  InicializarUART0_DR
	\brief Inicializa comunicación serial en UART0 a 9600 baudios. 8 bits + 1 bit de stop. sin paridad.
 	\author R2002 - Grupo2
 	\date Nov 4, 2020
 	\param [in] parametros de entrada
 	\param [out] parametros de salida
	\return tipo y descripcion de retorno
*/
void InicializarUART0_DR(void){
	POWER_UART0_ON;

	//25MHz = PCLK_UART0
	PCLKSEL0 &= ~(0x03 << PCLK_UART0);
	PCLKSEL0 |= (0x00 << PCLK_UART0);

	//Registros de la UART
	UART0->LCR.DLAB = 1; //prender DLAB para configuraciones

	// baudrate = PCLK_UART0 / (16 * DIV)
	UART0->DLM = 0;//baudrate divider MSB
	UART0->DLL = 162; //baudrate divider LSB

	UART0->LCR.wordLength = 0x03; // Largo de 8 bits:
	UART0->LCR.stopBit = 0; // Bits de stop (1):
	UART0->LCR.parityEn = 0; // Sin paridad

	//Seleccion de funcion de pines se hace en el main

	UART0->LCR.DLAB = 0;

	//Habilitacion de interrupciones
	UART0->IER.RBR_intEn = 1;
	ISER0 |= (1 << ISER_UART0);
}


/**
	\fn  UART0_pushRX
	\brief pushea dato recivido al buffer de recepción
 	\author R2002 - Grupo2
 	\date Nov 4, 2020
 	\param [in] dato a cargar en buffer de recepción
*/
void UART0_pushRX(uint8_t dato){
	UART0_rx_buff[UART0_rx_in] = dato;
	UART0_rx_in++; 		UART0_rx_in %= RX_BUFF_SIZE;
}


/**
	\fn  UART0_popTX
	\brief pop del dato del buffer de recepción
 	\author R2002 - Grupo2
 	\date Nov 4, 2020
 	\return dato a transmitir
*/
int32_t UART0_popTX(void){
	if(UART0_tx_in == UART0_tx_out) return -1;
	else {
		int32_t result = UART0_tx_buff[UART0_tx_out];

		UART0_tx_out++;		UART0_tx_out %= TX_BUFF_SIZE;
		return result;
	}
}


/**
	\fn  UART0_forceTX
	\brief Fuerza la emisión de un dato sin necesidad de las interrupciones. Se usa para comenzar una transmición
 	\author R2002 - Grupo2
 	\date Nov 4, 2020
 	\param [in] dato a enviar
*/
void UART0_forceTX(uint8_t dato){
	UART0->IER.THRE_intEn = 1;
	UART0->THR = dato;
}

/**
	\fn  UART0_IRQHandler
	\brief Handler de interrupciones de UART0. Analiza el ipo de interrupción y actua en consecuencia
 	\author R2002 - Grupo2
 	\date Nov 4, 2020
*/
void UART0_IRQHandler(void) {
	uint32_t int_pending;
	int32_t dato;

	do {
		uint32_t interrupt_cause = UART0->IIR.intId;
		int_pending = !(UART0->IIR.intStatus);

		/* Analizar interrupciones y accionar en consecuencia */
		switch(interrupt_cause) {
		case 0x03:  // RLS
			// TODO: Handle this
			break;

		case 0x02:  // RDA
			UART0_pushRX(UART0->RBR);
			break;

		case 0x06:  // CTI
			// TODO: Handle this
			break;

		case 0x01: // THRE
			dato = UART0_popTX();

			if(dato != -1)
				UART0_forceTX(dato);
			else {
				UART0_tx_flag = 0;
				UART0->IER.THRE_intEn = 0;
			}
			break;
		}
	} while(int_pending);
}

//UART3
/**********************************************************************************************************************************/
/**
	\fn  InicializarUART3_DR
	\brief Inicializa comunicación serial en UART3 a 9600 baudios. 8 bits + 1 bit de stop. sin paridad.
 	\author R2002 - Grupo2
 	\date Nov 4, 2020
 	\param [in] parametros de entrada
 	\param [out] parametros de salida
	\return tipo y descripcion de retorno
*/
void InicializarUART3_DR(void){
	POWER_UART3_ON;

	//25MHz = PCLK_UART0
	PCLKSEL1 &= ~(0x03 << PCLK_UART3);
	PCLKSEL1 |= (0x00 << PCLK_UART3);

	//Registros de la UART
	UART3->LCR.DLAB = 1; //prender DLAB para configuraciones

	// baudrate = PCLK_UART3 / (16 * DIV)
	UART3->DLM = 0;//baudrate divider MSB
	UART3->DLL = 162; //baudrate divider LSB

	UART3->LCR.wordLength = 0x03; // Largo de 8 bits:
	UART3->LCR.stopBit = 0; // Bits de stop (1):
	UART3->LCR.parityEn = 0; // Sin paridad

	//Seleccion de funcion de pines se hace en el main

	UART3->LCR.DLAB = 0;

	//Habilitacion de interrupciones
	UART3->IER.RBR_intEn = 1;
	ISER0 |= (1 << ISER_UART3);
}


/**
	\fn  UART3_pushRX
	\brief pushea dato recivido al buffer de recepción
 	\author R2002 - Grupo2
 	\date Nov 4, 2020
 	\param [in] dato a cargar en buffer de recepción
*/
void UART3_pushRX(uint8_t dato){
	UART3_rx_buff[UART3_rx_in] = dato;
	UART3_rx_in++; 		UART3_rx_in %= RX_BUFF_SIZE;
}


/**
	\fn  UART3_popTX
	\brief pop del dato del buffer de recepción
 	\author R2002 - Grupo2
 	\date Nov 4, 2020
 	\return dato a transmitir
*/
int32_t UART3_popTX(void){
	if(UART3_tx_in == UART3_tx_out) return -1;
	else {
		int32_t result = UART3_tx_buff[UART3_tx_out];

		UART3_tx_out++;		UART3_tx_out %= TX_BUFF_SIZE;
		return result;
	}
}


/**
	\fn  UART3_forceTX
	\brief Fuerza la emisión de un dato sin necesidad de las interrupciones. Se usa para comenzar una transmición
 	\author R2002 - Grupo2
 	\date Nov 4, 2020
 	\param [in] dato a enviar
*/
void UART3_forceTX(uint8_t dato){
	UART3->IER.THRE_intEn = 1;
	UART3->THR = dato;
}

/**
	\fn  UART3_IRQHandler
	\brief Handler de interrupciones de UART3. Analiza el ipo de interrupción y actua en consecuencia
 	\author R2002 - Grupo2
 	\date Nov 4, 2020
*/
void UART3_IRQHandler(void) {
	uint32_t int_pending;
	int32_t dato;

	do {
		uint32_t interrupt_cause = UART3->IIR.intId;
		int_pending = !(UART3->IIR.intStatus);

		/* Analizar interrupciones y accionar en consecuencia */
		switch(interrupt_cause) {
		case 0x03:  // RLS
			// TODO: Handle this
			break;

		case 0x02:  // RDA
			UART0_pushRX(UART3->RBR);
			break;

		case 0x06:  // CTI
			// TODO: Handle this
			break;

		case 0x01: // THRE
			dato = UART3_popTX();

			if(dato != -1)
				UART3_forceTX(dato);
			else {
				UART3_tx_flag = 0;
				UART3->IER.THRE_intEn = 0;
			}
			break;
		}
	} while(int_pending);
}
