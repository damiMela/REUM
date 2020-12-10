/*******************************************************************************************************************************//**
 *
 * @file		PR_Motor.c
 * @brief		Descripcion del modulo
 * @date		Nov 5, 2020
 * @author		R2002 - Grupo2
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <DR/DR_PWM.h>
#include <DR/DR_GPIO.h>
#include <AP/AP_Motores.h>

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define MOTOR1_A		PORT0, 0 //escribir puertos correspondientes
#define MOTOR1_B		PORT0, 1
#define MOTOR1_VEL_PIN	RGB_R
#define MOTOR1_VEL_CHN	2

#define MOTOR2_A		PORT0, 2
#define MOTOR2_B		PORT0, 3
#define MOTOR2_VEL_PIN	RGB_G
#define MOTOR2_VEL_CHN	3

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
 	\date Nov 5, 2020
 	\param [in] parametros de entrada
 	\param [out] parametros de salida
	\return tipo y descripcion de retorno
*/
void InicializarMotores(void){

	InicializarPWM_DR();

	setDir(MOTOR1_A, OUTPUT);
	setDir(MOTOR1_B, OUTPUT);
	setDir(MOTOR2_A, OUTPUT);
	setDir(MOTOR2_B, OUTPUT);

	PWM_setDutyCicle(MOTOR1_VEL_CHN, 0);
	PWM_setDutyCicle(MOTOR2_VEL_CHN, 0);
}

void setMotoresDir(uint8_t dir){
	switch(dir){
		case ADELANTE:
			setPin(MOTOR1_A, ON);
			setPin(MOTOR1_B, OFF);

			setPin(MOTOR2_A, ON);
			setPin(MOTOR2_B, OFF);
			break;

		case ATRAS:
			setPin(MOTOR1_A, OFF);
			setPin(MOTOR1_B, ON);

			setPin(MOTOR2_A, OFF);
			setPin(MOTOR2_B, ON);
			break;

		case IZQUIERDA:
			setPin(MOTOR1_A, ON);
			setPin(MOTOR1_B, OFF);

			setPin(MOTOR2_A, OFF);
			setPin(MOTOR2_B, ON);
			break;

		case DERECHA:
			setPin(MOTOR1_A, OFF);
			setPin(MOTOR1_B, ON);

			setPin(MOTOR2_A, ON);
			setPin(MOTOR2_B, OFF);
			break;

		case FRENO:
			setPin(MOTOR1_A, OFF);
			setPin(MOTOR1_B, OFF);

			setPin(MOTOR2_A, OFF);
			setPin(MOTOR2_B, OFF);
			break;
	}
}

void setMotoresVel(uint16_t vel){
	PWM_setDutyCicle(MOTOR1_VEL_CHN, vel);
	PWM_setDutyCicle(MOTOR2_VEL_CHN, vel);
}