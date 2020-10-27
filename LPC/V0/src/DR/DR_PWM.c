/*******************************************************************************************************************************//**
 *
 * @file		DR_PWM.c
 * @brief		Descripcion del modulo
 * @date		Oct 24, 2020
 * @author		R2002 - Grupo2
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <DR/DR_PWM.h>

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define 	PWM1			((PWM_t *)(0x40018000UL))
#define		ISER0		(*(uint32_t *)(0xE000E100UL))

enum {PWMM_I, PWMM_R, PWMM_S};
enum {RAISING, FALLING, EVENT};

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/
#define POWER_PWM_ON	PCONP |= (1 << PCPWM1)
#define POWER_PWM_OFF	PCONP &= ~(1 << PCPWM1)
/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/
typedef struct{
	uint32_t PWMMR_flags0: 4;
	uint32_t PWMCAP_flag: 2;
	uint32_t RESERVED_0: 2;
	uint32_t PWMMR_flags2: 3;
	uint32_t RESERVED_1: 21;
}PWM1_IR_t;

typedef struct{
	uint32_t CounterEn: 1;
	uint32_t CounterRst: 1;
	uint32_t RESERVED_0: 1;
	uint32_t PWMEn: 1;
	uint32_t RESERVED_1: 28;
}PWM_TimerCtrl_t;

typedef struct{
	uint32_t CounterMode: 2;
	uint32_t InSelect: 2;
	uint32_t RESERVED_0: 28;
}PWM_CountCtrl_t;

typedef struct{
	uint32_t PWMMR0: 3;//	1:PWMR0i	2:PWMR0r	3:PWMR0s
	uint32_t PWMMR1: 3;
	uint32_t PWMMR2: 3;
	uint32_t PWMMR3: 3;
	uint32_t PWMMR4: 3;
	uint32_t PWMMR5: 3;
	uint32_t PWMMR6: 3;
	uint32_t RESERVED_0: 11;
}PWM_MatchCtrl_t;

typedef struct{
	uint32_t PWM_CAP0: 3; //	1:rising	2:falling	3:event
	uint32_t PWM_CAP1: 3;
	uint32_t RESERVED_0: 26;
}PWM_CaptureCtrl_t;

typedef struct{
	uint32_t RESERVED_0: 2;
	uint32_t PWMSel: 5;// PWMSEL2-PWMSEL6
	uint32_t RESERVED_1: 2;
	uint32_t PWM_En: 6;
	uint32_t RESERVED_2: 17;
}PWM_ctrl_t;

typedef struct{
	uint32_t MatchLatchEn: 7;
	uint32_t RESERVED_0: 25;
}PWM_LatchEn_t;

typedef struct{
	__RW PWM1_IR_t Interrupts;
	__RW PWM_TimerCtrl_t TimerCtrl;
	__RW uint32_t TimerCounter;
	__RW uint32_t PLLReg;
	__RW uint32_t PLLCounter;
	__RW PWM_MatchCtrl_t MatchCtrl;
	__RW uint32_t MatchReg_1[4];
	__RW PWM_CaptureCtrl_t CaptureCtrl;
	__R  uint32_t CaptureReg[4];
	__R	 uint32_t RESERVED_0;
	__RW uint32_t MatchReg_2[3];
	__RW PWM_ctrl_t PWMCtrl;
	__RW PWM_LatchEn_t LatchEn;
	__R  uint32_t RESERVED_1[7];
	__RW PWM_CountCtrl_t CountCtrl;
}PWM_t;
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
	\fn  Nombre de la Funcion
	\brief Descripcion
 	\author R2002 - Grupo2
 	\date Oct 24, 2020
 	\param [in] parametros de entrada
 	\param [out] parametros de salida
	\return tipo y descripcion de retorno
*/
void InicializarPWM(void){
	POWER_PWM_ON;

	PCLKSEL0 &= ~(3 << PCLK_PWM1);

	PWM1->PWMCtrl.PWMSel = 0;
	PWM1->PLLReg= 24;

	PWM1->MatchReg_1[0] = 1000;
	PWM1->MatchReg_1[1] = 800;
	PWM1->MatchReg_1[2] = 800; //pwm2
	PWM1->MatchReg_1[3] = 800; //pwm3
	PWM1->MatchReg_2[0] = 800; //pwm4

	PWM1->MatchCtrl.PWMMR0 |= (1 << PWMM_R);

	PWM1->LatchEn.MatchLatchEn |= (1 << 0) | (1 << 2) | (1 << 3) | (1 << 4);
	PWM1->PWMCtrl.PWM_En |= (1 << 1) | (1 << 2) | (1 << 3);

	PWM1->TimerCtrl.CounterRst = 1;
	PWM1->TimerCtrl.CounterEn = 1;
	PWM1->TimerCtrl.PWMEn = 1;



}

void PWM_setDutyCicle(uint8_t PWM_n, uint16_t val){
	if(!PWM_n || (val > 1000)) return;
	if(PWM_n > 3){
		PWM1->MatchReg_2[PWM_n%4] = val;
	}
	else{
		PWM1->MatchReg_1[PWM_n] = val;
	}
	PWM1->LatchEn.MatchLatchEn |= (1 << (PWM_n));
}

