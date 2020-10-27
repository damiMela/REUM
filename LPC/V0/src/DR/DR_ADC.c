/*******************************************************************************************************************************//**
 *
 * @file		DR_ADC.c
 * @brief		Descripcion del modulo
 * @date		Sep 28, 2020
 * @author		R2002 - Grupo2
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <DR/DR_ADC.h>
/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define		ADC_BUFF_SIZE	16

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/
#define POWER_ADC_ON	PCONP |= (1 << PCADC)
#define POWER_ADC_OFF	PCONP &= ~(1 << PCADC)

#define 	ADC			((ADC_t *)(0x40034000UL))
#define		ISER0		(*(uint32_t *)(0xE000E100UL))

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/
typedef struct {
	uint32_t adcSel:8;
	uint32_t clkDiv:8;
	uint32_t burstMode:1;
	uint32_t _RESERVED0:4;
	uint32_t PDN:1;
	uint32_t _RESERVED1:2;
	uint32_t startMode:3;
	uint32_t edgeSelect:1;
	uint32_t _RESERVED2:4;
} ADC_ctrl_t;

typedef struct{
	uint32_t _RESERVED0:4;
	uint32_t result:12;
	uint32_t _RESERVED1:8;
	uint32_t channel:3;
	uint32_t _RESERVED2:3;
	uint32_t overrun:1;
	uint32_t done:1;
}ADC_GlobalData_t;

typedef struct{
	uint32_t intEn0:1;
	uint32_t intEn1:1;
	uint32_t intEn2:1;
	uint32_t intEn3:1;
	uint32_t intEn4:1;
	uint32_t intEn5:1;
	uint32_t intEn6:1;
	uint32_t intEn7:1;
	uint32_t globlalIntEnable:1;
	uint32_t _RESERVED0:23;
}ADC_IntEnable_t;

typedef struct{
	uint32_t _RESERVED0:4;
	uint32_t result:12;
	uint32_t _RESERVED1:14;
	uint32_t overrun:1;
	uint32_t done:1;
}ADC_Data_t;

typedef struct{
	uint32_t done0:1;
	uint32_t done1:1;
	uint32_t done2:1;
	uint32_t done3:1;
	uint32_t done4:1;
	uint32_t done5:1;
	uint32_t done6:1;
	uint32_t done7:1;
	uint32_t overrun0:1;
	uint32_t overrun1:1;
	uint32_t overrun2:1;
	uint32_t overrun3:1;
	uint32_t overrun4:1;
	uint32_t overrun5:1;
	uint32_t overrun6:1;
	uint32_t overrun7:1;
	uint32_t ADInt:1;
	uint32_t _RESERVED0:15;
}ADC_Status_t;

typedef struct{
	__RW ADC_ctrl_t ADCR;
	__RW ADC_GlobalData_t ADGDR;
	__RW uint32_t RESERVED_0;
	__RW ADC_IntEnable_t ADINTEN;
	__R ADC_Data_t AD_data[8];
	__R ADC_Status_t ADSTAT;
}ADC_t;
/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
static volatile uint32_t ADC_buffer[ADC_BUFF_SIZE];
static volatile uint32_t ADC_buffer_index = 0;
static volatile uint32_t ADC_average = 0;
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
	\fn  inicializarADC
	\brief Inicializa el ADC con frecuencia de muestro 192kHz
 	\author R2002 - Grupo2
 	\date Sep 28, 2020
*/
void inicializarADC()
{

	POWER_ADC_ON; //macro para encender ADC

	// set ADC time. (max. 200kHz) f_ADC = (f_CPU / div_PCLKSEL) / ((div_ADC + 1) * 65) = 192KHz
	PCLKSEL0 &= ~(3 <<  PCLK_ADC);

	ADC->ADCR.PDN = 1;
	setPinsel(1, 31, 3);
	ADC->ADCR.startMode = 0;

	ADC->ADCR.clkDiv = 1;

	ADC->ADCR.adcSel = (1<<5);

	ADC->ADINTEN.intEn0 = 0;
	ADC->ADINTEN.intEn1 = 0;
	ADC->ADINTEN.intEn2 = 0;
	ADC->ADINTEN.intEn3 = 0;
	ADC->ADINTEN.intEn4 = 0;
	ADC->ADINTEN.intEn5 = 1;
	ADC->ADINTEN.intEn6 = 0;
	ADC->ADINTEN.intEn7 = 0;
	ADC->ADINTEN.globlalIntEnable = 0;


	ISER0 |= (1 << 22);
	ADC_inUse = 1;
}


/**
	\fn  ADC_IRQHandler
	\brief Handler del interrupt del ADC. Toma 32 muestras por valor
 	\author R2002 - Grupo2
 	\date Sep 28, 2020
*/
void ADC_IRQHandler(void)
{
	static uint32_t acummulator = 0;

	ADC_Data_t ADC5 = ADC->AD_data[5];

	ADC_buffer[ADC_buffer_index] = ADC5.result;
	acummulator += ADC_buffer[ADC_buffer_index];

	ADC_buffer_index++;
	ADC_buffer_index %= ADC_BUFF_SIZE;

	if(!ADC_buffer_index)
	{
		ADC_average = acummulator / ADC_BUFF_SIZE;
		acummulator = 0;
	}
}


/**
	\fn  ADC_getVal
	\brief Devuelve el valor promedio de 32 lecturas de ADC
 	\author R2002 - Grupo2
 	\date Sep 28, 2020
	\return uint32_t con el valor leido
*/
uint32_t ADC_getVal(void)
{
	return ADC_average;
}


/**
	\fn  ADC_startConvertion
	\brief Comienza la conversion del ADC
 	\author R2002 - Grupo2
 	\date Sep 28, 2020
*/
void ADC_startConvertion(void)
{
	ADC->ADCR.startMode = 1;
}
