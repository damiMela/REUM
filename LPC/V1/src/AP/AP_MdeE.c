
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
#include  <DR/DR_GPIO.h>
#include  <PR/PR_Serial.h>
#include  <PR/PR_Timers.h>
#include  <PR/PR_Motores.h>
#include  <PR/PR_Relays.h>
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
					setRGB(1, 0, 0);
					estado = SIN_CONEXION;
				}
			case SIN_CONEXION:{
				if(com_confirmed_msg == 0)
					break;
				if(com_confirmed_msg == 'M'){
					com_confirmed_msg = 0;
					estado = ESP_ONLINE;

					setRGB(0, 1, 0);
					ledV_Blink_t = 1;
					TimerStart(LED_V_BLINK_EV, ledV_Blink_t, LedV_Blink, SEG);
				}
				else estado = CONEXION_RESET;
				break;
			}

			case ESP_ONLINE:{
				if(com_confirmed_msg == 0)
					break;
				if(com_confirmed_msg == 'C'){
					com_confirmed_msg = 0;

					estado = CLIENTE_CONECTADO;
					ledV_Blink_t = 3;
					TimerStart(LED_V_BLINK_EV, ledV_Blink_t, LedV_Blink, SEG);
				}
				else estado = CONEXION_RESET;
				break;
			}
			
			case CLIENTE_CONECTADO:{
				if(com_confirmed_msg == 0)
					break;
				if(com_confirmed_msg == 'T'){
					com_confirmed_msg = 0;

					estado = CLIENTE_DESCONECTADO;
					//TimerStop(LED_V_BLINK_EV);
				}
				else estado = CONEXION_RESET;
				break;
			}

			case CLIENTE_DESCONECTADO:{
					ledV_Blink_t = 1;
					estado = ESP_ONLINE;
					TimerStart(LED_V_BLINK_EV, ledV_Blink_t, LedV_Blink, SEG);
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
		static int estado = SIN_MOVIMIENTO;

		switch(estado)
		{
			case SIN_MOVIMIENTO:
				setRelay(RELAY0, OFF);
				setRelay(RELAY1, OFF);
				setRelay(RELAY2, OFF);
				setRelay(RELAY3, OFF);
			
				if( confirmed_dir == 'F' )
				{
					setMotoresDir(DIR_ADELANTE);
					setMotoresVel(confirmed_vel);
					confirmed_dir = 0;
					confirmed_vel = -1;
					estado = ADELANTE;	
					setRelay(RELAY0, ON);
				}
				else if( confirmed_dir == 'B' )
				{
					setMotoresDir(DIR_ATRAS);
					setMotoresVel(confirmed_vel);
					confirmed_dir = 0;
					confirmed_vel = -1;
					estado = ATRAS;	
					setRelay(RELAY1, ON);
				}
				else if( confirmed_dir == 'R' )
				{
					setMotoresDir(DIR_DERECHA);
					setMotoresVel(confirmed_vel);
					confirmed_dir = 0;
					confirmed_vel = -1;
					estado = DERECHA;
					setRelay(RELAY2, ON);
				}
				else if( confirmed_dir == 'L' )
				{
					setMotoresDir(DIR_IZQUIERDA);
					setMotoresVel(confirmed_vel);
					confirmed_dir = 0;
					confirmed_vel = -1;
					estado = IZQUIERDA;
					setRelay(RELAY3, ON);
				}
 

				break;
			
			case ADELANTE:
				if(confirmed_dir == 0)
					break;
				if(confirmed_dir != 'F')
				{
					setMotoresDir(FRENO);
					setMotoresVel(0);
					confirmed_dir = 0;
					confirmed_vel = -1;
					estado = SIN_MOVIMIENTO;	
				}
				break;
			
			case ATRAS:
				if(confirmed_dir == 0)
					break;
				if(confirmed_dir != 'B')
				{
					setMotoresDir(FRENO);
					setMotoresVel(0);
					confirmed_dir = 0;
					confirmed_vel = -1;
					estado = SIN_MOVIMIENTO;	
				}
 

				break;
			
			case DERECHA:
				if(confirmed_dir == 0)
					break;
				if(confirmed_dir != 'R')
				{
					setMotoresDir(FRENO);
					setMotoresVel(0);
					confirmed_dir = 0;
					confirmed_vel = -1;
					estado = SIN_MOVIMIENTO;	
				}
 
				break;
			
			case IZQUIERDA:
				if(confirmed_dir == 0)
					break;
				if(confirmed_dir != 'L')
				{
					setMotoresDir(FRENO);
					setMotoresVel(0);
					confirmed_dir = 0;
					confirmed_vel = -1;
					estado = SIN_MOVIMIENTO;	
				}
 
				break;
			
			default: estado = SIN_MOVIMIENTO;
		}

		return estado;
}

