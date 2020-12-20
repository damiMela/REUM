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
#define		CANT_CANALES	3  //SOlO SE USAN CANALES 1 y 2

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/
#define POWER_ADC_ON	PCONP |= (1 << PCADC)
#define POWER_ADC_OFF	PCONP &= ~(1 << PCADC)

#define 	ADC			((ADC_t *)(0x40034000UL))

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/
typedef struct _ADC_ctrl_t{
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

typedef struct _ADC_GlobalData_t{
	uint32_t _RESERVED0:4;
	uint32_t result:12;
	uint32_t _RESERVED1:8;
	uint32_t channel:3;
	uint32_t _RESERVED2:3;
	uint32_t overrun:1;
	uint32_t done:1;
}ADC_GlobalData_t;

typedef struct _ADC_IntEnable_t{
	uint32_t intEn:8;
	uint32_t globlalIntEnable:1;
	uint32_t _RESERVED0:23;
}ADC_IntEnable_t;

typedef struct _ADC_Data_t{
	uint32_t _RESERVED0:4;
	uint32_t result:12;
	uint32_t _RESERVED1:14;
	uint32_t overrun:1;
	uint32_t done:1;
}ADC_Data_t;

typedef struct _ADC_Status_t{
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

typedef struct _ADC_t{
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
static volatile uint32_t ADC_read_buffer[CANT_CANALES][ADC_BUFF_SIZE];
volatile uint32_t ADC_buffer[CANT_CANALES] = {0};
volatile uint8_t ADC_ready = 0;
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
void InicializarADC_DR(){
	POWER_ADC_ON; //macro para encender ADC
	ADC->ADCR.PDN = 1;

	// set ADC time. (max. 200kHz) f_ADC = (f_CPU / div_PCLKSEL) / ((div_ADC + 1) * 65)
	PCLKSEL0 &= ~(3 <<  PCLK_ADC);

	//ADC->ADCR.clkDiv = 1; //adc f = 192kHz
	ADC->ADCR.clkDiv = 37; //adc f = 10kHz

	ADC->ADCR.adcSel = 0;
	ADC->ADCR.adcSel |= (1 << 1);
	ADC->ADCR.adcSel |= (1 << 2);

	ADC-> ADINTEN.intEn = 0;
	ADC->ADINTEN.intEn |= (1 << 1);
	ADC->ADINTEN.intEn |= (1 << 2);

	ADC->ADCR.startMode = 0; //start must be 0 when burst is 1
	ADC->ADCR.burstMode = 1;

	//activo interrupción global
	ISER0 |= (1 << ISER_ADC);
}


/**
	\fn  ADC_IRQHandler
	\brief Handler del interrupt del ADC. Toma 32 muestras por valor
 	\author R2002 - Grupo2
 	\date Sep 28, 2020
*/
void ADC_IRQHandler(void){
	static uint32_t count_n = 0;

	if(count_n == ADC_BUFF_SIZE){
		count_n = 0;
		uint32_t sum0 = 0, sum1 = 0, sum2 = 0;

		for(uint8_t i = 0; i < ADC_BUFF_SIZE; i++){
			sum0 += ADC_read_buffer[0][i];
			sum1 += ADC_read_buffer[1][i];
			sum2 += ADC_read_buffer[2][i];
		}

		sum0 /= ADC_BUFF_SIZE;
		sum1 /= ADC_BUFF_SIZE;
		sum2 /= ADC_BUFF_SIZE;
		ADC_buffer[0] = sum0;
		ADC_buffer[1] = sum1;
		ADC_buffer[2] = sum2;

		ADC->ADCR.startMode = 0;
		ADC->ADCR.burstMode = 0;//terminate burst
		ADC_ready = 1;
	}

	if(ADC->ADSTAT.done1){
		ADC_read_buffer[1][count_n] = ADC->AD_data[1].result;
	}
	else if(ADC->ADSTAT.done2){
		ADC_read_buffer[2][count_n] = ADC->AD_data[2].result;
		count_n++; //incremento acá porque es la {ultima interrupción del cilo
	}
}


/**
	\fn  ADC_startConvertion
	\brief Comienza la conversion del ADC
 	\author R2002 - Grupo2
 	\date Sep 28, 2020
*/
void ADC_startConvertion(void){
	ADC->ADCR.startMode = 0;
	ADC->ADCR.burstMode = 1;//reestart burst
}
