
/************************************************************************************************************************************
 * La Redistribuci�n y uso en formas de fuente y objeto con o sin modificaci�n, est�n permitidos siempre que se cumplan las 
 * siguientes condiciones:
 *
 * 1. Las redistribuciones del c�digo fuente deben conservar el aviso de copyright anterior, esta lista de condiciones y el siguiente
 * descargo de responsabilidad.
 *
 * 2. Las redistribuciones en formato objeto deben reproducir el aviso de copyright anterior, esta lista de condiciones y la siguiente
 * exenci�n de responsabilidad en la documentaci�n y / u otros materiales proporcionados con la distribuci�n.
 *
 * 3. Ni el nombre del titular de los derechos de autor ni los nombres de sus los contribuyentes pueden ser utilizados para respaldar 
 * o promocionar productos derivados de este software sin permiso escrito previo espec�fico.
 *
 * ESTE SOFTWARE ES PROPORCIONADO POR LOS TITULARES DE LOS DERECHOS DE AUTOR Y SUS COLABORADORES de uModelFactor y Y SE RENUNCIA 
 * A CUALQUIER GARANT�A EXPRESA O IMPL�CITA, INCLUIDAS, ENTRE OTRAS, LAS GARANT�AS IMPL�CITAS DE COMERCIABILIDAD E IDONEIDAD PARA 
 * UN PROP�SITO DETERMINADO. EN NING�N CASO EL TITULAR DE LOS DERECHOS DE AUTOR O LOS COMERCIANTES SER�N RESPONSABLES DE DA�OS DIRECTOS,
 * INDIRECTOS, INCIDENTALES, ESPECIALES, EJEMPLARES O CONSECUENCIALES (INCLUIDOS, ENTRE OTROS, LA ADQUISICI�N DE BIENES O SERVICIOS 
 * SUSTITUTIVOS, LA P�RDIDA DE USO, LOS DATOS O LAS GANANCIAS; O INTERRUPCI�N DEL NEGOCIO) SIN EMBARGO Y EN CUALQUIER TEOR�A DE 
 * RESPONSABILIDAD, YA SEA POR CONTRATO, RESPONSABILIDAD ESTRICTA O AGRAVIO (INCLUIDA LA NEGLIGENCIA O CUALQUIER OTRO) QUE SURJA DE
 * CUALQUIER MODO DEL USO DE ESTE SOFTWARE, AUN CUANDO SE ESTEVIENDO LA POSIBILIDAD DE DICHO DA�o
 *	
 * El contenido de este archivo es generado en forma automatica a partir del modelo planteado. Cualquier cambio realizado sobre el modelo
 * generara un nuevo codigo que eliminara todos los cambios realizados por el desarrollador en el fuente previamente generado
**************************************************************************************************************************************/

/**
*	\file AP_MdeE.c
*	\brief Implementacion switch-case
*	\details Descripcion detallada del archivo
*	\author JuanAgustinOtero
*	\date 19-12-2020 19:03:18
*/

/*********************************************************************************************************************************
 *** INCLUDES
**********************************************************************************************************************************/
#include  <AP/AP_MdeE.h>
#include  <AP/AP_FuncionesMdeE.h>

#include  <PR/PR_RGB.h>
#include  <PR/PR_Serial.h>
#include  <PR/PR_Timers.h>
#include  <PR/PR_Motores.h>
#include  <PR/PR_PWM.h>
#include  <PR/PR_BMP280.h>


#include <stdio.h>
/*********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
**********************************************************************************************************************************/

/*********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
**********************************************************************************************************************************/

/*********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
**********************************************************************************************************************************/

/*********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
**********************************************************************************************************************************/

/*********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
**********************************************************************************************************************************/

/*********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
**********************************************************************************************************************************/
static uint8_t com_confirmed_msg = 0;
static uint8_t confirmed_dir = 0;
static int8_t  confirmed_vel = -1;
static uint8_t connected_flag = 0;
/*********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
**********************************************************************************************************************************/

/*********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
**********************************************************************************************************************************/

/*********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
**********************************************************************************************************************************/
/**
*	\fn void maquina_conexion()
*	\brief Implementacion switch-case
*	\details 
*	\author Grupo2-2020
*	\date 20-12-2020 14:33:08
*/
uint8_t maquina_Conexion()
{
		static uint8_t estado = CONEXION_RESET;

		switch(estado)
		{
			case CONEXION_RESET:
				if(1){
					InicializarRGB();
					setRGB(1, 0, 0);
					connected_flag = 0;
					estado = SIN_CONEXION;
				}
			case SIN_CONEXION:{
				if(com_confirmed_msg == 0)
					break;
				if(com_confirmed_msg == 'M'){
					com_confirmed_msg = 0;

					setRGB(0, 1, 0);
					ledV_Blink_t = 1;
					TimerStart(LED_V_BLINK_EV, ledV_Blink_t, LedV_Blink, SEG);
					estado = ESP_ONLINE;
				}
				else estado = CONEXION_RESET;
				break;
			}

			case ESP_ONLINE:{
				if(com_confirmed_msg == 0)
					break;
				if(com_confirmed_msg == 'C'){
					com_confirmed_msg = 0;
					connected_flag = 1;

					ledV_Blink_t = 3;
					TimerStart(LED_V_BLINK_EV, ledV_Blink_t, LedV_Blink, SEG);
					estado = CLIENTE_CONECTADO;
				}
				else estado = CONEXION_RESET;
				break;
			}
			
			case CLIENTE_CONECTADO:{
				if(com_confirmed_msg == 0)
					break;
				if(com_confirmed_msg == 'T'){
					com_confirmed_msg = 0;
					TimerStop(LED_V_BLINK_EV);
					estado = CLIENTE_DESCONECTADO;
				}
				else estado = CONEXION_RESET;
				break;
			}

			case CLIENTE_DESCONECTADO:{
				connected_flag = 0;
				ledV_Blink_t = 1;
				TimerStart(LED_V_BLINK_EV, ledV_Blink_t, LedV_Blink, SEG);
				estado = ESP_ONLINE;
				break;
			}

			default: estado = SIN_CONEXION;
		}

		return estado;
}

/**
*	\fn void maquina_Lectura()
*	\brief Implementacion switch-case
*	\details 
*	\author JuanAgustinOtero
*	\date 19-12-2020 19:03:18
*/
uint8_t maquina_Lectura()
{
		static uint8_t estado = RESET_READ;

		int16_t data = UART1_popRX();
		static uint8_t com_msg = 0, dir_msg = 0, vel_msg = 0;

		switch(estado)
		{
			case RESET_READ:{
				if(1){
					InicializarSerial1();
					com_msg = 0;
					dir_msg = 0;
					vel_msg = 0;
					estado = WAIT_START;
				}
				break;
			}

			case WAIT_START:{
				if(START_CHAR(data))
					estado = WAIT_MSG_TYPE;
 				break;
			}

			case WAIT_MSG_TYPE:{
				if(data == -1)
					break;
				else if(COM_CHAR(data)){
					estado = WAIT_END;
					com_msg = data;
				}
				else if(MOV_CHAR(data)){
					estado = WAIT_MSG_VEL1;
					dir_msg = data;
				}
				else estado = RESET_READ;
				break;
			}

			case WAIT_MSG_VEL1:{
				if(data == -1)
					break;
				else if(NUM_CHAR(data) && (data == '0')){
					vel_msg = (data - '0');
					estado = WAIT_END;
				}
				else if(NUM_CHAR(data)){
					vel_msg = (data - '0') * 10;
					estado = WAIT_MSG_VEL2;
				}
				else estado = RESET_READ;
				break;
			}

			case WAIT_MSG_VEL2:{
				if(data == -1)
					break;
				else if(NUM_CHAR(data)){
					vel_msg += (data - '0');
					estado = WAIT_END;
				}
				else estado = RESET_READ;
				break;
			}

			case WAIT_END:
				if(data == -1)
					break;
				if(END_CHAR(data)){
					if(com_msg)
						com_confirmed_msg = com_msg;
					else{
						confirmed_dir = dir_msg;
						confirmed_vel = vel_msg;
					}
				}
				else
					estado = RESET_READ;
				break;

			default: estado = RESET_READ;
		}
		return estado;
}

/**
*	\fn void maquina_Movimiento()
*	\brief Implementacion switch-case
*	\details 
*	\author JuanAgustinOtero
*	\date 19-12-2020 19:03:18
*/
uint8_t maquina_Movimiento()
{
		static int estado = RESET_MOVIMIENTO;
		static uint8_t timeout_start = 0;

		switch(estado)
		{
			case RESET_MOVIMIENTO:{
				InicializarMotores();

				setMotoresDir(FRENO);
				setMotoresVel(0);

				confirmed_dir = 0;
				confirmed_vel = -1;
				timeout_start = 0;

				estado = SIN_MOVIMIENTO;
				break;
			}
			case SIN_MOVIMIENTO:
				if(!(connected_flag))
					estado = RESET_MOVIMIENTO;
				else if((confirmed_dir == 'F') && (connected_flag))
				{
					setMotoresDir(DIR_ADELANTE);
					setMotoresVel(confirmed_vel);
					confirmed_dir = 0;
					confirmed_vel = -1;
					estado = ADELANTE;	
				}
				else if((confirmed_dir == 'B') && (connected_flag))
				{
					setMotoresDir(DIR_ATRAS);
					setMotoresVel(confirmed_vel);
					confirmed_dir = 0;
					confirmed_vel = -1;
					estado = ATRAS;	
				}
				else if((confirmed_dir == 'R') && (connected_flag))
				{
					setMotoresDir(DIR_DERECHA);
					setMotoresVel(confirmed_vel);
					confirmed_dir = 0;
					confirmed_vel = -1;
					estado = DERECHA;
				}
				else if((confirmed_dir == 'L') && (connected_flag))
				{
					setMotoresDir(DIR_IZQUIERDA);
					setMotoresVel(confirmed_vel);
					confirmed_dir = 0;
					confirmed_vel = -1;
					estado = IZQUIERDA;
				}
				else if((confirmed_dir == 'S') && (connected_flag))
				{
					setMotoresDir(FRENO);
					setMotoresVel(confirmed_vel);
					confirmed_dir = 0;
					confirmed_vel = -1;
				}
 

				break;
			
			case ADELANTE:
				if(!connected_flag)
					estado = RESET_MOVIMIENTO;

				else if(!confirmed_dir){
					if(!timeout_start){
						timeout_start = 1;
						dir_timeout_f = 0;
						TimerStart(MOTOR_TIMEOUT_EV, 8, dir_timeout, SEG);
					}
					else break;
				}
				else if(dir_timeout_f){
					dir_timeout_f = 0;
					timeout_start = 0;
					estado = RESET_MOVIMIENTO;
				}
				else if((confirmed_dir != 'F'))
				{
					setMotoresDir(FRENO);
					setMotoresVel(0);
					TimerStop(MOTOR_TIMEOUT_EV);

					confirmed_dir = 0;
					confirmed_vel = -1;
					timeout_start = 0;
					dir_timeout_f = 0;

					estado = SIN_MOVIMIENTO;	
				}

				break;
			
			case ATRAS:
				if(!connected_flag)
					estado = RESET_MOVIMIENTO;

				else if(!confirmed_dir){
					if(!timeout_start){
						timeout_start = 1;
						dir_timeout_f = 0;
						TimerStart(MOTOR_TIMEOUT_EV, 8, dir_timeout, SEG);
					}
					else break;
				}
				else if(dir_timeout_f){
					dir_timeout_f = 0;
					timeout_start = 0;
					estado = RESET_MOVIMIENTO;
				}
				else if((confirmed_dir != 'B'))
				{
					setMotoresDir(FRENO);
					setMotoresVel(0);
					TimerStop(MOTOR_TIMEOUT_EV);

					confirmed_dir = 0;
					confirmed_vel = -1;
					timeout_start = 0;
					dir_timeout_f = 0;

					estado = SIN_MOVIMIENTO;	
				}
 

				break;
			
			case DERECHA:
				if(!connected_flag)
					estado = RESET_MOVIMIENTO;

				else if(!confirmed_dir){
					if(!timeout_start){
						timeout_start = 1;
						dir_timeout_f = 0;
						TimerStart(MOTOR_TIMEOUT_EV, 8, dir_timeout, SEG);
					}
					else break;
				}
				else if(dir_timeout_f){
					dir_timeout_f = 0;
					timeout_start = 0;
					estado = RESET_MOVIMIENTO;
				}
				else if((confirmed_dir != 'D'))
				{
					setMotoresDir(FRENO);
					setMotoresVel(0);
					TimerStop(MOTOR_TIMEOUT_EV);

					confirmed_dir = 0;
					confirmed_vel = -1;
					timeout_start = 0;
					dir_timeout_f = 0;

					estado = SIN_MOVIMIENTO;	
				}
 
				break;
			
			case IZQUIERDA:
				if(!connected_flag)
					estado = RESET_MOVIMIENTO;

				else if(!confirmed_dir){
					if(!timeout_start){
						timeout_start = 1;
						dir_timeout_f = 0;
						TimerStart(MOTOR_TIMEOUT_EV, 8, dir_timeout, SEG);
					}
					else break;
				}
				else if(dir_timeout_f){
					dir_timeout_f = 0;
					timeout_start = 0;
					estado = RESET_MOVIMIENTO;
				}
				else if((confirmed_dir != 'L'))
				{
					setMotoresDir(FRENO);
					setMotoresVel(0);
					TimerStop(MOTOR_TIMEOUT_EV);

					confirmed_dir = 0;
					confirmed_vel = -1;
					timeout_start = 0;
					dir_timeout_f = 0;

					estado = SIN_MOVIMIENTO;	
				}
 
				break;
			
			default: estado = RESET_MOVIMIENTO;
		}

		return estado;
}
enum estado_enivo_data_en{
	RESET_SENDING,
	WAIT_SENDING,
	SEND_DATA
};

uint8_t maquina_Envio_data(void){
	static uint8_t estado = RESET_SENDING;

	switch(estado){
		case RESET_SENDING:{
			InicializarBMP280();
			InicializarADC();
			InicializarBMP280();
			send_data_f = 0;
			estado = WAIT_SENDING;
			break;
		}

		case WAIT_SENDING:{
			if(connected_flag){
				TimerStart(SEND_DATA_EV, 3, send_data_timer, SEG);
				estado = SEND_DATA;
			}
			break;
		}

		case SEND_DATA:{
			if(send_data_f){
				send_data_f = 0;
				estado = WAIT_SENDING;

				#define CANT_PARAMS	3
				#define CANT_SPACES	4
				#define ARRAY_LENGHT	CANT_PARAMS * 3 + CANT_PARAMS * CANT_SPACES


				BMP280_getData();
				int16_t temp = getBMP280_temp();
				uint16_t pres = getBMP280_pres();
				uint16_t luz = getADC(ADC_2) * 100 /4095;

				char msg[ARRAY_LENGHT] = {0};
				sprintf(msg, "#t#%d.%d"
						"#p#%d"
						"#l#%d",
						temp/100, temp%100, pres, luz);

				UART1_SendString((uint8_t *)msg);
			}

		}
	}
	return estado;
}

