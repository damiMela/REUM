/*******************************************************************************************************************************//**
 *
 * @file		PR_Timers.c
 * @brief		Descripcion del modulo
 * @date		Sep 28, 2020
 * @author		R2002 - Grupo2
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <PR/PR_Timers.h>

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
uint32_t TmrRun[ N_TIMERS ];
void (*TmrFunciones[ N_TIMERS ])(void);
uint8_t TmrFlags[ N_TIMERS+1 ];
uint8_t TmrPause[ N_TIMERS ];
uint8_t TmrBase[ N_TIMERS ];

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

//<<<<<<<<<<<<<<<<<funciones para el usuario>>>>>>>>>>>>>>>>>>>//

/**
	\fn  TimerStart
	\brief incializa un contador de tiempo con una funcion a ejecutar cuando este termina.
 	\author R2002 - Grupo2
 	\date Sep 28, 2020
 	\param [in] número de evento/contador.
 	\param [in] tiempo a contar (en décimas, segundos o minutos).
 	\param [in] fúncion a ejecutar cuando haya pasado el tiempo especificado.
 	\param [in] base de tiempo. USAR DEFINES "DEC", "SEG" y "MIN".
	\return -1 si algo salió mal
*/
int8_t TimerStart ( uint8_t event_n , uint32_t t , void (* f_event )(void), uint8_t base )
{
	uint8_t salida = 0;

	switch(base){
		case CENT: 	TmrRun[event_n] = t * CENTECIMAS;	break;
		case DEC: 	TmrRun[event_n] = t * DECIMAS;		break;
		case SEG: 	TmrRun[event_n] = t * SEGUNDOS;		break;
		case MIN: 	TmrRun[event_n] = t * MINUTOS;		break;
		default:	salida = -1;
	}

	TmrFunciones[event_n] = f_event;
	TmrBase[event_n] = base;

	return salida;
}


/**
	\fn  TimerPause
	\brief Pausa el conteo del tiempo del número de contador especificado
 	\author R2002 - Grupo2
 	\date Sep 28, 2020
 	\param [in] número de evento/contador.
 	\param [in] modo. USAR DEFINES "PAUSE" y "PLAY".
	\return -1 si el contador especificado no existe
*/
int8_t TimerPause ( uint8_t event_n , uint8_t modo )
{
	uint8_t salida = -1;

	if(event_n < N_TIMERS)
	{
		TmrPause[event_n] = modo;
		salida = 0;
	}
	return salida;
}



/**
	\fn  TimerStop
	\brief elimina el contador especificado
 	\author R2002 - Grupo2
 	\date Sep 28, 2020
 	\param [in] número de evento/contador
	\return -1 si el contador especificado no existe
*/
int8_t TimerStop ( uint8_t event_n  ){
	uint8_t salida = -1;

	if(event_n < N_TIMERS){
		TmrRun[event_n] = 0;
		TmrFlags[event_n] = 0;
		TmrBase[event_n] = 0;
		TmrPause[event_n] = 0;
		TmrFunciones[event_n] = (void *) 0;

		salida = 0;
	}
	return salida;
}


/**
	\fn  TimerSet
	\brief setea un nuevo tiempo de conteo a un contador ya creado
 	\author R2002 - Grupo2
 	\date Sep 28, 2020
 	\param [in] número de evento/contador.
 	\param [in] nuevo tiempo
	\return -1 si el contador especificado no existe o no fue creado con TimerStart()
*/
int8_t TimerSet ( uint8_t event_n , uint32_t t ){
	uint8_t salida = -1;

	if((event_n < N_TIMERS) && TmrRun[event_n]){
		salida = 0;

		switch(TmrBase[event_n]){
			case CENT: 	TmrRun[event_n] = t * CENTECIMAS;	break;
			case DEC: 	TmrRun[event_n] = t * DECIMAS;		break;
			case SEG: 	TmrRun[event_n] = t * SEGUNDOS;		break;
			case MIN: 	TmrRun[event_n] = t * MINUTOS;		break;
			default:	salida = -1;
		}
	}
	return salida;
}


/**
	\fn  TimerGet
	\brief getea el tiempo restante para que termine el contador
 	\author R2002 - Grupo2
 	\date Sep 28, 2020
 	\param [in] número de evento/contador.
 	\param [out] tiempo restante para que termine el contador
	\return -1 si el contador especificado no existe o no fue creado con TimerStart()
*/
int8_t TimerGet ( uint8_t event_n , uint32_t *t )
{
	uint8_t salida = -1;

	if((event_n < N_TIMERS) && TmrRun[event_n])
	{
		salida = 0;

		switch(TmrBase[event_n])
		{
			case CENT: 	*t = TmrRun[event_n] * CENTECIMAS;	break;
			case DEC: 	*t = TmrRun[event_n] * DECIMAS;		break;
			case SEG: 	*t = TmrRun[event_n] * SEGUNDOS;	break;
			case MIN: 	*t = TmrRun[event_n] * MINUTOS;		break;
			default:	salida = -1;
		}
	}
	return salida;
}


/**
	\fn  TimerClose
	\brief termina con todos los timers.
 	\author R2002 - Grupo2
 	\date Sep 28, 2020
*/
void TimerClose ( void )
{
	for(uint8_t i = 0; i < N_TIMERS; i++)
		TimerStop(i);

	return;
}

//<<<<<<<<<<<<<<<<<funciones para funcionamiento>>>>>>>>>>>>>>>>>>>//

/**
	\fn  TimerDiscount
	\brief descuenta 1 a los valors restantes de tiempo de los contadores.
 	\author R2002 - Grupo2
 	\date Sep 28, 2020
*/
void TimerDiscount ( void )
{
	for(uint8_t i = 0; i < N_TIMERS; i ++){
		if(TmrRun[i]){
			if(!TmrPause[i]){
				TmrRun[i]--;
				if(!TmrRun[i])
					TmrFlags[i] = 1;
			}
		}
	}
}

/**
	\fn  TimerLunchEvent
	\brief ejecuta la funcion correpondiente cuando termina el contador llega a 0
 	\author R2002 - Grupo2
 	\date Sep 28, 2020
*/
void Timers_run ( void ){
	uint8_t i;

	for ( i = 0 ; i < N_TIMERS ; i ++){
		if (TmrFlags[ i ] == 1){
			TmrFlags[ i ] = 0;
			TmrFunciones[ i ]();
		}
	}
}




