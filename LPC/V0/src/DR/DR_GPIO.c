/*******************************************************************************************************************************//**
 *
 * @file		DR_GPIO.c
 * @brief		Funciones para utilizacion de GPIO
 * @date		Sep 19, 2020
 * @author		R2002 - Grupo2
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <DR/DR_GPIO.h>

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/
#define	PINMODE		((__RW uint32_t *) 0x4002C040UL)
#define PINMODE_OP	((__RW uint32_t *) 0x4002C068UL)
#define  GPIO (( gpio_t* ) 0x2009C000UL)
/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/
typedef struct _gpio_t{
	uint32_t FIODIR;
	uint32_t _RESERVED[3];
	uint32_t FIOMASK;
	uint32_t FIOPIN;
	uint32_t FIOSET;
	uint32_t FIOCLR;
}gpio_t;



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
	\fn  setPinmode
	\brief Setea el modo de lectura del pin
 	\author R2002 - Grupo2
 	\date Sep 19, 2020
 	\param [in] Número de puerto.
 	\param [in] Número de pin.
  	\param [in] modo de lectura. USAR DEFINES "MODO_nombre"
*/
void setPinmode(uint8_t port, uint8_t pin, uint8_t mode){
	PINMODE[port*2 + pin/16] &= ~(3 << ((pin%16)*2)); //"limpiar" bits en los que se va a escribir
	PINMODE[port*2 + pin/16] |= mode << ((pin%16)*2);
}


/**
	\fn  setPinmode_OP
	\brief Setea el modo de escritura del pin
 	\author R2002 - Grupo2
 	\date Sep 19, 2020
 	\param [in] Número de puerto.
 	\param [in] Número de pin.
  	\param [in] modo de lectura. USAR DEFINES "MODO_OP_nombre"
*/
void setPinmode_OP(uint8_t port, uint8_t pin, uint8_t mode){
	PINMODE_OP[port] &= ~(1 << pin);
	PINMODE_OP[port] |= (mode << pin);
}


/**
	\fn  setDir
	\brief Setea el un pin en salida o entrada
 	\author R2002 - Grupo2
 	\date Sep 19, 2020
 	\param [in] Número de puerto.
 	\param [in] Número de pin.
  	\param [in] modo de uso. USAR DEFINES "INPUT"/"OUTPUT"
*/
void setDir(uint8_t port, uint8_t pin, uint8_t mode){
	if(mode)
		GPIO[port].FIODIR |= (1 << pin);
	else
		GPIO[port].FIODIR &= ~(1 << pin);
}


/**
	\fn  setPin
	\brief Setea el un pin en HIGH o LOW
 	\author R2002 - Grupo2
 	\date Sep 19, 2020
 	\param [in] Número de puerto.
 	\param [in] Número de pin.
  	\param [in] estado. USAR DEFINES "HIGH"/"LOW"
*/
void setPin(uint8_t port, uint8_t pin, uint8_t state){
	if((PINMODE_OP[port] >> pin) == MODE_OP_NLOW){
		//active HIGH
		if(state == HIGH)
			GPIO[port].FIOSET |= (1 << pin);
		else
			GPIO[port].FIOCLR |= (1 << pin);
	}
	else{
		//active LOW
		if(state == HIGH)
			GPIO[port].FIOCLR |= (1 << pin);
		else
			GPIO[port].FIOSET |= (1 << pin);
	}
}

/**
	\fn  getPin
	\brief devuelve el estado actual de un pin. se puede setear para que devuelva ON si lee '0' o '1'
 	\author R2002 - Grupo2
 	\date Sep 19, 2020
 	\param [in] Número de puerto.
 	\param [in] Número de pin.
  	\param [in] modo. configura si '0' es activo o inactivo. USAR DEFINES "ON_HIGH"/"ON_LOW"
  	\return devuelve 1 o 0 según corresponda. usar los defines "ON" y "OFF"
*/
uint8_t getPin(uint8_t port, uint8_t pin, uint8_t mode){
	uint8_t in = (GPIO[port].FIOPIN >> 1) & (0x00000001);
	return (mode == 1 ? in : !in);
}


/**
	\fn  getPin
	\brief devuelve el estado actual de un pin.
 	\author R2002 - Grupo2
 	\date Sep 19, 2020
 	\param [in] Número de puerto.
 	\param [in] Número de pin.
  	\return devuelve 1 o 0 según corresponda.
*/
uint8_t getPin_raw(uint8_t port, uint8_t pin){
	return (GPIO[port].FIOPIN >> 1) & (0x00000001);
}
