/*******************************************************************************************************************************//**
 *
 * @file		DR_ExtInt.c
 * @brief		Descripcion del modulo
 * @date		13 nov. 2020
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <DR/DR_ExtInt.h>
#include <DR/DR_Timer0.h>

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define EINT0		(1<< 0)
#define EINT1		(1<< 1)
#define EINT2		(1<< 2)
#define EINT3		(1<< 3)

#define EINT0_EDGE	(1<< 0)
#define EINT1_EDGE	(1<< 1)
#define EINT2_EDGE	(1<< 2)
#define EINT3_EDGE	(1<< 3)

#define EINT0_POLAR	(1<< 0)
#define EINT1_POLAR	(1<< 1)
#define EINT2_POLAR	(1<< 2)
#define EINT3_POLAR	(1<< 3)

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/
#define	INT_EN_R2		(*(__RW uint32_t *) 0x400280B0UL) //rising interrupt enable
#define	INT_EN_F2		(*(__RW uint32_t *) 0x400280B4UL) //falling interrupt enable
#define	INT_STAT_R2		(*(__RW uint32_t *) 0x400280A4UL) //falling interrupt enable
#define	INT_STAT_F2		(*(__RW uint32_t *) 0x400280A8UL) //falling interrupt enable

#define EINT2_FALL_STAT	(INT_STAT_F2 & ( 1 << 12))
#define EINT2_RISE_STAT	(INT_STAT_R2 & ( 1 << 12))


#define EINT0_EN		(ISER0 |= (1 << ISER_EINT0))
#define EINT0_DIS		(ICER0 |= (1 << ICER_EINT0))
#define EINT2_EN		(ISER0 |= (1 << ISER_EINT2))
#define EINT2_DIS		(ICER0 |= (1 << ICER_EINT2))

#define EINT0_FALL_STAT	(INT_STAT_F2 & ( 1 << 10))
#define EINT0_RISE_STAT	(INT_STAT_R2 & ( 1 << 10))


#define EXT_INT			((ExtInt_t *) 0x400FC140UL)
/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
static uint32_t startTime = 0;
uint32_t intTime = 0;
/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
typedef struct _EXTINT_t{
	__RW uint32_t EXTINT;
	__RW uint32_t RESERVED_0;
	__RW uint32_t EXTMODE;
	__RW uint32_t EXTPOLAR;
} ExtInt_t;
 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/
/**
	\fn  Nombre de la Funcion
	\brief Descripcion
 	\author Ing. Marcelo Trujillo
 	\date 13 nov. 2020
 	\param [in] parametros de entrada
 	\param [out] parametros de salida
	\return tipo y descripcion de retorno
*/
void InicializarEINT_DR( void ){
  INT_EN_R2 |= (1 << 12); 	/* Port2.12 is rising & falling edge. */
  INT_EN_F2 |= (1 << 12);
  EXT_INT->EXTMODE = EINT2_EDGE;		/* INT2 edge trigger */
  EXT_INT->EXTPOLAR = 0;				/* INT2 is falling edge by default */

  EINT2_EN;
}

void EINT2_IRQHandler (void){
	if(EINT2_FALL_STAT){
		intTime =  startTime - TIMER0_getTime();
		TIMER0_rstTime();

		EXT_INT->EXTPOLAR |= EINT2_POLAR; //la proxima vez va a ser rising
	}
	if(	EINT2_RISE_STAT){
		startTime = TIMER0_getTime();

		EXT_INT->EXTPOLAR &= ~EINT2_POLAR; //la proxima vez va a ser falling
	}
	EXT_INT->EXTINT = EINT2;
}

void EINT_Enable(uint8_t n, uint8_t state){
	if(n > 3) return;
	if(state){
		ISER0 |= (1 << (ISER_EINT0 + n));
	}
	else{
		ICER0 |= (1 << (ICER_EINT0 + n));
	}
}
