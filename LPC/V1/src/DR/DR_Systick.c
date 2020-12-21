/*******************************************************************************************************************************//**
 *
 * @file		DR_Systick.h
 * @brief		Funciones para utilización systick timer
 * @date		Sep 19, 2020
 * @author		R2002 - Grupo2
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <DR/DR_Systick.h>
#include <DR/DR_PLL.h>
#include <PR/PR_Timers.h>
#include <DR/DR_ADC.h>
#include <DR/DR_PWM.h>
#include <DR/DR_Botones.h>
/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define ADC_T 10 //x2.5 ms
#define PWM_T 5 //x2.5 ms
#define BTN_T 5 //x2.5 ms
/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/
#define	SYSTICK	((systick_t*) 0xE000E010UL)
/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/
typedef struct{
	uint32_t Enable:1;
	uint32_t TickInt:1;
	uint32_t ClkSource:1;
	uint32_t __a:13;  //RESERVED
	uint32_t CountFlag:1;
	uint32_t __b:15;
}STCTRL_t;

typedef struct{
	__RW STCTRL_t STCTRL;
	__RW uint32_t STRELOAD;
	__RW uint32_t STCURR;
	__R  uint32_t STCALIB;
}systick_t;

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
uint8_t ADC_inUse = 0;
/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
static uint32_t systickCounter = 0;
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
	\fn  inicializarSystick
	\brief Inicializa el systick timer en 10ms
 	\author R2002 - Grupo2
 	\date Sep 19, 2020
*/
void InicializarSystick(void){
	SYSTICK->STRELOAD = SYSTICK->STCALIB/4 -1; //tick cada 2.5ms
	SYSTICK->STCTRL.ClkSource = 1; //clock interno
	SYSTICK->STCURR = 0;
	SYSTICK->STCTRL.TickInt = 1;
	SYSTICK->STCTRL.Enable = 1;
}

/**
	\fn  SysTick_Handler
	\brief handler de la interrupcion. Suma 1 al systickCounter
 	\author R2002 - Grupo2
 	\date Sep 19, 2020
*/
void SysTick_Handler(void){
	systickCounter++;
	scheduler_run();
}


/**
	\fn  get_ticks
	\brief fucnión para obtener la cantidad de ticks hechos
 	\author R2002 - Grupo2
 	\date Sep 19, 2020
 	\return valor guardado en systickCounter
*/
uint32_t get_ticks(void){
	return systickCounter;
}


/**
	\fn  get_ticks
	\brief función para resetear la cantidad de ticks
 	\author R2002 - Grupo2
 	\date Sep 19, 2020
 	\return valor guardado en systickCounter
*/
void reset_ticks(void){
	systickCounter = 0;
}


/**
	\fn  scheduler_run
	\brief scheduler del programa
 	\author R2002 - Grupo2
 	\date Nov 04, 2020
*/
void scheduler_run(void){
	//ADC está configurado en modo burst

	//counters
	static uint32_t pwm_counter = 0;
	static uint32_t btn_counter = 0;
	static uint32_t adc_counter = 0;

	//timer counter function
	TimerDiscount();

	//interations counter
	pwm_counter++; 	pwm_counter %= PWM_T;
	btn_counter++; 	btn_counter %= BTN_T;
	adc_counter++;	adc_counter %= ADC_T;

	if(!pwm_counter) PWM_update();
	if(!btn_counter) TecladoSW();
	if(!adc_counter) {
		//ADC_startConvertion();
		if(ADC_ready){
			ADC_startConvertion();
			ADC_ready = 0;
		}
	}


}
