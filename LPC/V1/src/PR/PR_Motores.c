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
#include <PR/PR_Motores.h>
#include <PR/PR_PWM.h>
#include <DR/DR_GPIO.h>

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define MOTOR1_A		EXPANSION12 //escribir puertos correspondientes
#define MOTOR1_B		EXPANSION13
#define MOTOR1_VEL_PIN	EXPANSION6
#define MOTOR1_VEL_CHN	PWM2

#define MOTOR2_A		EXPANSION14
#define MOTOR2_B		EXPANSION15
#define MOTOR2_VEL_PIN	EXPANSION11
#define MOTOR2_VEL_CHN	PWM3

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
	\fn  InicializarMotores
	\brief Inicializa los pines y el pwm
 	\author R2002 - Grupo2
 	\date Nov 5, 2020
*/
void InicializarMotores(void){
	InicializarPWM();

	setDir(MOTOR1_A, OUTPUT);
	setDir(MOTOR1_B, OUTPUT);
	setDir(MOTOR2_A, OUTPUT);
	setDir(MOTOR2_B, OUTPUT);

	setPWMDuty(MOTOR1_VEL_CHN, 0);
	setPWMDuty(MOTOR2_VEL_CHN, 0);
}

/**
	\fn  setMotoresDir
	\brief setea los piens de los motores para que el robot se mueva de acuerdo a la direccione ingresada
 	\author R2002 - Grupo2
 	\date Nov 5, 2020
 	\param [in] dirección a mover el robot
 */
void setMotoresDir(uint8_t dir){
	switch(dir){
		case 'F':
		case DIR_ADELANTE:
			setPin(MOTOR1_A, ON);
			setPin(MOTOR1_B, OFF);

			setPin(MOTOR2_A, ON);
			setPin(MOTOR2_B, OFF);
			break;


		case 'B':
		case DIR_ATRAS:
			setPin(MOTOR1_A, OFF);
			setPin(MOTOR1_B, ON);

			setPin(MOTOR2_A, OFF);
			setPin(MOTOR2_B, ON);
			break;


		case 'L':
		case DIR_IZQUIERDA:
			setPin(MOTOR1_A, ON);
			setPin(MOTOR1_B, OFF);

			setPin(MOTOR2_A, OFF);
			setPin(MOTOR2_B, ON);
			break;


		case 'R':
		case DIR_DERECHA:
			setPin(MOTOR1_A, OFF);
			setPin(MOTOR1_B, ON);

			setPin(MOTOR2_A, ON);
			setPin(MOTOR2_B, OFF);
			break;


		case 'S':
		case FRENO:{
			setPin(MOTOR1_A, OFF);
			setPin(MOTOR1_B, OFF);

			setPin(MOTOR2_A, OFF);
			setPin(MOTOR2_B, OFF);
			break;
		}

		default:
			dir = FRENO;
	}
}


/**
	\fn  setMotoresVel
	\brief setea la velocidad (0 al 100)
 	\author R2002 - Grupo2
 	\date Nov 5, 2020
 	\param [in] velocidad
 */
void setMotoresVel(uint8_t vel){
	setPWMDuty(MOTOR1_VEL_CHN, vel);
	setPWMDuty(MOTOR2_VEL_CHN, vel);
}
