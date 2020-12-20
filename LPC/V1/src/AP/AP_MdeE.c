
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
#include "AP_MdeE.h" 
#include "AP_FuncionesMdeE.h" 
#include "PR_RGB.h"
#include "DR_GPIO.h"
#include "PR_Serial.h"
#include "PR_Timers.h"
#include "PR_Motores.h"
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
void maquina_conexion()
{
		static int estado = SIN_CONEXION;
		uint8_t aux = 0;
		switch(estado)
		{
			aux = UART0_popRX();
			case SIN_CONEXION:
				setRGB_r(ON);
				if( START_CHAR(aux) )
				{
					estado = ESPERA_MENSAJE_RED;
				}
				break;
			case ESPERA_MENSAJE_RED:
			
				if( aux != 'M' )
				{
					estado = SIN_CONEXION;	
				}
 
				if( aux == 'M' )
				{
					estado = ESPERA_MENSAJE_FIN_RED;	
				}
 

				break;
			
			case ESPERA_MENSAJE_FIN_RED:
			
				if( END_CHAR(aux) )
				{
					estado = SIN_CONEXION;	
				}
 
				if( END_CHAR(aux) )
				{
					LedV_Blink = 25;
					TimerStart ( 0 , LedV_Blink , LedBlink, CENTECIMAS);
					estado = ESPERA_MENSAJE_INICIO_CLIENTE;	
				}
 

				break;
			
			case ESPERA_MENSAJE_INICIO_CLIENTE:
			
				if( START_CHAR(aux) )
				{
					estado = ESPERA_MENSAJE_CLIENTE;	
				}
 

				break;
			
			case ESPERA_MENSAJE_CLIENTE:
			
				if( aux != 'C' )
				{
					estado = ESPERA_MENSAJE_INICIO_CLIENTE;	
				}
 
				if( aux == 'C' )
				{
					estado = ESPERA_MENSAJE_FIN_CLIENTE;	
				}
 

				break;
			
			case ESPERA_MENSAJE_FIN_CLIENTE:
			
				if( END_CHAR(aux) )
				{
					estado = ESPERA_MENSAJE_INICIO_CLIENTE;	
				}
 
				if( END_CHAR(aux) )
				{
					LedV_Blink = 2000;
					f_conexion_exitosa = TRUE;

					estado = CONEXION_EXITOSA;	
				}
 

				break;
			
			case CONEXION_EXITOSA:
			
				if( f_conexion_exitosa == FALSE )
				{
					estado = ESPERA_MENSAJE_INICIO_CLIENTE;	
				}
 

				break;
			
			default: estado = SIN_CONEXION;
		}


}

/**
*	\fn void maquina_Lectura()
*	\brief Implementacion switch-case
*	\details 
*	\author JuanAgustinOtero
*	\date 19-12-2020 19:03:18
*/
void maquina_Lectura()
{
		uint8_t aux = 0;
		static int estado = ESPERA_INICIO;

		switch(estado)
		{
			aux = UART0_popRX();
			case ESPERA_INICIO:
			
				
				if( START_CHAR( aux ) )
				{
					estado = ESPERA_MENSAJE_MOVIMIENTO;	
				}
 

				break;
			
			case ESPERA_MENSAJE_MOVIMIENTO:
			
				if( !MOV_CHAR(aux) )
				{
					f_error();
					estado = ESPERAR_MENSAJE_VELOCIDAD_1;	
				}
 
				if( MOV_CHAR(aux) )
				{
					indicador_movimiento = aux;
				
					estado = ESPERA_INICIO;	
				}
 

				break;
			
			case ESPERAR_MENSAJE_VELOCIDAD_1:
				if( aux >= '0' && aux <= '9' )
				{
					indicador_velocidad = (aux-48)*10;
					estado = ESPERAR_MENSAJE_VELOCIDAD_2;	
				}
				if( aux < '0' || aux > '9' )
				{
					f_error();
					estado = ESPERA_INICIO;	
				}

				break;
			
			case ESPERAR_MENSAJE_VELOCIDAD_2:
				if( aux >= '0' && aux <= '9' )
				{
					indicador_velocidad += (aux-48);
					estado = ESPERA_FIN;	
				}
				if( aux < '0' || aux > '9' )
				{
					f_error();
					estado = ESPERA_INICIO;	
				}

				break;

				case ESPERA_FIN:
			
				if( END_CHAR(aux) )
				{
					f_movimiento = TRUE;
					estado = ESPERA_MENSAJE_MOVIMIENTO;	
				}
				if(END_CHAR(aux))
				{
					f_error();
					estado = ESPERA_INICIO;
				}
 
				break;
			
			default: estado = ESPERA_INICIO;
		}


}

/**
*	\fn void maquina_Movimiento()
*	\brief Implementacion switch-case
*	\details 
*	\author JuanAgustinOtero
*	\date 19-12-2020 19:03:18
*/
void maquina_Movimiento()
{
		static int estado = SIN_MOVIMIENTO;

		switch(estado)
		{
			case SIN_MOVIMIENTO:
			
				if( f_movimiento == TRUE && indicador_movimiento == 'F' )
				{
					setMotoresDir(DIR_ADELANTE);
					setMotoresVel(indicador_velocidad);
					estado = ADELANTE;	
				}
				else if( f_movimiento == TRUE && indicador_movimiento == 'B' )
				{
					setMotoresDir(DIR_ATRAS);
					setMotoresVel(indicador_velocidad);
					estado = ATRAS;	
				}
				else if( f_movimiento == TRUE && indicador_movimiento == 'R' )
				{
					setMotoresDir(DIR_DERECHA);
					setMotoresVel(indicador_velocidad);
					estado = DERECHA;	
				}
				else if( f_movimiento == TRUE && indicador_movimiento == 'L' )
				{
					setMotoresDir(DIR_IZQUIERDA);
					setMotoresVel(indicador_velocidad);
				}
 

				break;
			
			case ADELANTE:
			
				if((f_movimiento == TRUE && indicador_movimiento != 'F') || f_movimiento == FALSE)
				{
					setMotoresDir(FRENO);
					setMotoresVel(0);
					estado = SIN_MOVIMIENTO;	
				}
				break;
			
			case ATRAS:
			
				if(f_movimiento == FALSE || (f_movimiento == TRUE && indicador_movimiento != 'B'))
				{
					setMotoresDir(FRENO);
					setMotoresVel(0);
					estado = SIN_MOVIMIENTO;	
				}
 

				break;
			
			case DERECHA:

				if(f_movimiento == FALSE || (f_movimiento == TRUE && indicador_movimiento != 'R'))
				{
					setMotoresDir(FRENO);
					setMotoresVel(0);
					estado = SIN_MOVIMIENTO;	
				}
 
			

				break;
			
			case IZQUIERDA:

				if(f_movimiento == FALSE || (f_movimiento == TRUE && indicador_movimiento != 'L'))
				{
					setMotoresDir(FRENO);
					setMotoresVel(0);
					estado = SIN_MOVIMIENTO;	
				}
 
				break;
			
			default: estado = SIN_MOVIMIENTO;
		}


}

