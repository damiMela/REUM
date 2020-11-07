/*******************************************************************************************************************************//**
 *
 * @file		DR_Timer0.c
 * @brief		Descripcion del modulo
 * @date		6 nov. 2020
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <DR/DR_Timer0.h>

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/
#define POWER_TIM0_ON	(PCONP |=  (1<< PTIM0))
#define POWER_TIM0_OFF	(PCONP &=  ~(1 << PTIM0))

#define TIM0	((TIM_t *)(0x40004000UL))
/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/
typedef struct _TIM_IR_t{
	uint32_t MR0_Int: 1;
	uint32_t MR1_Int: 1;
	uint32_t MR2_Int: 1;
	uint32_t MR3_Int: 1;
	uint32_t CR0_Int: 1;
	uint32_t CR1_Int: 1;
	uint32_t RESERVED_0: 26;
} TIM_IR_t;

typedef struct _TIM_TCR_t{
	uint32_t CounterEn: 1;
	uint32_t CounterRst: 1;
	uint32_t RESERVED_0: 30;
}TIM_TCR_t;

typedef struct _TIM_CTCR_t{
	uint32_t TimerMode: 2;
	uint32_t CountInputSel: 2;
	uint32_t RESERVED_0: 28;
}TIM_CTCR_t;

typedef struct _TIM_MCR_t{
	uint32_t MR0: 3;  //MR0_I, MR0_R, MR0_S
	uint32_t MR1: 3;
	uint32_t MR2: 3;
	uint32_t MR3: 3;
	uint32_t RESERVED_0: 18;
}TIM_MCR_t;

typedef struct _TIM_CCR_t{
	uint32_t Cap0RE: 1;
	uint32_t Cap0FE: 1;
	uint32_t Cap0I: 1;
	uint32_t Cap1RE: 1;
	uint32_t Cap1FE: 1;
	uint32_t Cap1I: 1;
	uint32_t RESERVED_0: 26;
}TIM_CCR_t;

typedef struct _TIM_EMR_t{
	uint32_t EM0: 1;
	uint32_t EM1: 1;
	uint32_t EM2: 1;
	uint32_t EM3: 1;
	uint32_t EMC0: 1;
	uint32_t EMC1: 1;
	uint32_t EMC2: 1;
	uint32_t EMC3: 1;
	uint32_t RESERVED_0: 24;
} TIM_EMR_t;

typedef struct _TIM_t{
	__RW TIM_IR_t IR;
	__RW TIM_TCR_t TCR;
	__RW uint32_t TC;
	__RW uint32_t PR;
	__RW uint32_t PC;
	__RW TIM_MCR_t MCR;
	__RW uint32_t MR0;
	__RW uint32_t MR1;
	__RW uint32_t MR2;
	__RW uint32_t MR3;
	__RW TIM_CCR_t CCR;
	__R uint32_t CR0;
	__R uint32_t CR1;
	__R uint32_t RESERVED_0[2];
	__RW TIM_EMR_t EMR;
	__R uint32_t RESERVED_1[12];
	__RW TIM_CTCR_t CTCR;
} TIM_t;

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/
enum {TIM_I, TIM_R, TIM_S};
/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
uint32_t TIM0_count = 0;

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
 	\author Ing. Marcelo Trujillo
 	\date 6 nov. 2020
 	\param [in] parametros de entrada
 	\param [out] parametros de salida
	\return tipo y descripcion de retorno
*/
void InicializarTimer0_DR(void){
	POWER_TIM0_ON;

	PCLKSEL0 &= ~(0x03 << PCLK_TIM0);
	PCLKSEL0 |= (0x01 << PCLK_TIM0);

	TIM0->CTCR.CountInputSel = 0;
	TIM0->CTCR.TimerMode = 0;

	TIM0->PR = 10; //100ns

	TIM0->MR0 = 10;//10*100ns = 1us;

	TIM0->MCR.MR0 = (1 << TIM_I) | (1 << TIM_R);
	TIM0->TCR.CounterRst = 1;

	ISER0 |= (1<< ISER_TIM0);
	TIM0->TCR.CounterRst = 0;
}

void TIMER0_EnableCount(uint8_t en){
	if(en){
		TIM0->TCR.CounterRst = 1;
		TIM0->TCR.CounterRst = 0;
		TIM0->TCR.CounterEn = 1;
	}
	else
		TIM0->TCR.CounterEn = 0;
}


uint8_t TIMER0_getTime(){
	return TIM0_count;
}

void TIMER0_rstTime(){
	TIM0_count = 0;
}

void TIMER0_IRQHandler(void){
	TIM0->IR.MR0_Int = 1;
	TIM0_count++;
}
