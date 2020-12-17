/*******************************************************************************************************************************//**
 *
 * @file		infotronic.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		Sep 19, 2020
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef INFOTRONIC_H_
#define INFOTRONIC_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <DR/DR_Tipos.h>
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
//!< Salidas Digitales/Relays
#define		RELAY0_P			PORT2,0
#define		RELAY1_P			PORT0,23
#define		RELAY2_P			PORT0,21
#define		RELAY3_P			PORT0,27

//!< LED RGB
#define 	RGB_R			PORT2, 3 //PWM 1.4
#define 	RGB_G			PORT2, 2 //PWM 1.3
#define 	RGB_B			PORT2, 1 //PWM 1.2

//!<Buzzer
#define		BUZZER			PORT0,28

//!<Entradas analógicas
#define 	ADC0			PORT1, 31
#define 	ADC1			PORT0, 24
#define 	ADC2			PORT0, 25

#define 	POTENCIOMETRO	ADC0

//!< Entradas Digitales
#define 	IN0				PORT1,26
#define 	IN1				PORT4,29 //RXD3
#define 	IN2				PORT2,11

//!< Teclado
#define 	SW1_P 			PORT2, 10
#define 	SW2_P 			PORT0, 18
#define 	SW3_P 			PORT0, 11
#define 	SW4_P 			PORT2, 13
#define 	SW5_P 			PORT1, 26

//!Expansion
#define		EXPANSION0		PORT2, 7
#define		EXPANSION1		PORT1, 29
#define		EXPANSION2		PORT4, 28
#define		EXPANSION3		PORT1, 23
#define		EXPANSION4		PORT1, 20
#define		EXPANSION5		PORT0, 19 //SDA1
#define		EXPANSION6		PORT3, 26 //PWM 1.3
#define		EXPANSION7		PORT1, 25
#define		EXPANSION8		PORT1, 22
#define		EXPANSION9		PORT1, 19
#define		EXPANSION10		PORT0, 20 //SCL1
#define		EXPANSION11		PORT3, 25 //PWM 1.2
#define		EXPANSION12		PORT1, 27 //Motor1_A
#define		EXPANSION13		PORT1, 24 //Motor1_A
#define		EXPANSION14		PORT1, 21 //Motor2_B
#define		EXPANSION15		PORT1, 18 //Motor2_B
#define		EXPANSION16		PORT2, 8  //US_TRIG
#define		EXPANSION17		PORT2, 12 //US_ECHO, EINT2

#define 	EXPANSION18		PORT0, 16 //RX
#define 	EXPANSION19		PORT0, 15 //TX
#define 	EXPANSION20		PORT0, 22 //RTS
#define 	EXPANSION21		PORT0, 27 //CTS

//!ADC inputs
#define 	ADC_IN_1	PORT1, 31 //CANAL 5, FUNCION "11"
#define 	ADC_IN_2	PORT0, 24 //CANAL 1, FUNCION "01"
#define 	ADC_IN_3 	PORT0, 25 //CANAL 2, FUNCION "01"

//!< LCD
#define		LCD_D4			PORT0,5
#define		LCD_D5			PORT0,10
#define		LCD_D6			PORT2,4
#define		LCD_D7			PORT2,5
#define		LCD_RS			PORT2,6
#define		LCD_BF			PORT0,28
#define		LCD_EN			PORT0,4

//USB serial
#define 	USB_TX			PORT0, 2
#define 	USB_RX			PORT0, 3

#define 	SERIAL_TX		EXPANSION19
#define 	SERIAL_RX		EXPANSION18




//!< Display siete segmentos
#define    dg0       		PORT0,19    // exp 5
#define    dg1       		PORT1,20   	// exp 4
#define    dg2      		PORT1,23   	// exp 3
#define    dg3       		PORT4,28   	// exp 2
#define    dg4       		PORT1,29   	// exp1
#define    dg5       		PORT2,7    	// exp0

#define    seg_a        	PORT3,26 	// exp6 Correcto P3.26
#define    seg_b       	 	PORT1,18	// exp15
#define    seg_c        	PORT1,21	// exp14
#define    seg_d        	PORT1,24	// exp13
#define    seg_e        	PORT1,27	// exp12
#define    seg_f        	PORT3,25	// exp11
#define    seg_g        	PORT0,20	// exp10

#define    seg_dp        	PORT1,19// P1.19  exp9

#define    DIGITO_0         0
#define    DIGITO_1         1
#define    DIGITO_2         2
#define    DIGITO_3         3
#define    DIGITO_4         4
#define    DIGITO_5         5


//!< Teclas (teclado 4x1)
#define		KEY0			PORT2,10
#define		KEY1			PORT0,18
#define		KEY2			PORT0,11
#define		KEY3			PORT2,13		// EINT3






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

#endif /* INFOTRONIC_H_ */
