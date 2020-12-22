/*******************************************************************************************************************************//**
 *
 * @file		DR_LCD.c
 * @brief		Descripcion del modulo
 * @date		Dec 21, 2020
 * @author		R2002 - Grupo2
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <DR/DR_LCD.h>
#include <DR/DR_GPIO.h>
#include <DR/DR_Pinsel.h>
#include <PR/PR_LCD.h>


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
uint8_t	Demora_LCD; /*!< Variable para realizar las demoras necesarias en la inicializacion del LCD*/
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
	\fn  Nombre de la Funcion
	\brief Descripcion
 	\author R2002 - Grupo2
 	\date Dec 21, 2020
 	\param [in] parametros de entrada
 	\param [out] parametros de salida
	\return tipo y descripcion de retorno
*/

void InitLCD( void ){
	uint16_t i;

	setPinsel( LCD_D4 , 0 );
	setPinsel( LCD_D5 , 0 );
	setPinsel( LCD_D6 , 0 );
	setPinsel( LCD_D7 , 0 );
	setPinsel( LCD_RS , 0 );
	setPinsel( LCD_EN , 0 );

	setDir( LCD_D4 , OUTPUT );
	setDir( LCD_D5 , OUTPUT );
	setDir( LCD_D6 , OUTPUT );
	setDir( LCD_D7 , OUTPUT );
	setDir( LCD_RS , OUTPUT );
	setDir( LCD_EN , OUTPUT );

	setPin ( LCD_EN , OFF );
	Demora_LCD = 50;// 50
	while( Demora_LCD );

	for( i = 0 ; i < 3 ; i++ ){
		setPin ( LCD_D4 , ON );
		setPin ( LCD_D5 , ON );
		setPin ( LCD_D6 , OFF );
		setPin ( LCD_D7 , OFF );
		setPin ( LCD_RS , OFF );
		setPin ( LCD_EN , ON );
		setPin ( LCD_EN , OFF );

		Demora_LCD = 10;//10
		while( Demora_LCD );
	}

	setPin ( LCD_D4 , OFF );
	setPin ( LCD_D5 , ON );
	setPin ( LCD_D6 , OFF );
	setPin ( LCD_D7 , OFF );
	setPin ( LCD_RS , OFF );
	setPin ( LCD_EN , ON );
	setPin ( LCD_EN , OFF );

	Demora_LCD = 5;
	while( Demora_LCD );

	PushLCD( 0x28 , LCD_CONTROL );	//N = 1; 2 lineas; 5x7 puntos
	Demora_LCD = 4;
	while( Demora_LCD );
	PushLCD( 0x08 , LCD_CONTROL );	//Cursor off
	Demora_LCD = 4;
	while( Demora_LCD );
	PushLCD( 0x01 , LCD_CONTROL );	//Clear display
	Demora_LCD = 4;
	while( Demora_LCD );
	PushLCD( 0x06 , LCD_CONTROL );	//incrementa puntero
	Demora_LCD = 4;
	while( Demora_LCD );
	PushLCD( 0x0C , LCD_CONTROL );	//Activo LCD
	Demora_LCD = 4;
	while( Demora_LCD );
}

/**
 * @brief Funcion encargada de poner un dato en el LCD desde el buffer
 */

void Dato_LCD( void )
{
	int16_t data;

	if( ( data = PopLCD( ) ) == -1 )
		return;

	setPin ( LCD_D4 , ( ( (uint8_t) data ) >> 0 ) & 0x01 );
	setPin ( LCD_D5 , ( ( (uint8_t) data ) >> 1 ) & 0x01 );
	setPin ( LCD_D6 , ( ( (uint8_t) data ) >> 2 ) & 0x01 );
	setPin ( LCD_D7 , ( ( (uint8_t) data ) >> 3 ) & 0x01 );

	if( ( (uint8_t) data ) & 0x80 )
		setPin( LCD_RS , OFF );
	else
		setPin( LCD_RS , ON );

	setPin ( LCD_EN , ON );
	setPin ( LCD_EN , OFF );
}

/**
 * @brief Funcion encargada de sacar un dato del buffer del LCD
 * @return Devuelve el dato o -1 si no hay dato en el buffer
 */

int16_t PopLCD( void )
{
	int16_t dato;

	if( cantidadColaLCD == 0 )
		return -1;

	dato = Buffer_LCD[ inxOutLCD ];

	cantidadColaLCD--;

	inxOutLCD++;
	inxOutLCD %= TOPE_BUFFER_LCD;

	return dato;
}
