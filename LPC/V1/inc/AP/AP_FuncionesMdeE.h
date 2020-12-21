
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
*	\file AP_FuncionesMdeE.h
*	\brief Resumen del archivo
*	\details Descripcion detallada del archivo
*	\author JuanAgustinOtero
*	\date 19-12-2020 19:03:18
*/
/*********************************************************************************************************************************
*** MODULO
**********************************************************************************************************************************/
#ifndef INC_AP_FUNCIONESMDEE_H_
#define INC_AP_FUNCIONESMDEE_H_

/*********************************************************************************************************************************
*** INCLUDES GLOBALES
**********************************************************************************************************************************/
#include <DR/DR_Tipos.h>
/*********************************************************************************************************************************
*** DEFINES GLOBALES
**********************************************************************************************************************************/
#define LED_V_BLINK_EV 	(0)
#define MOTOR_TIMEOUT_EV 	(1)
#define SEND_DATA_EV 	(2)
/*********************************************************************************************************************************
*** MACROS GLOBALES
**********************************************************************************************************************************/

/*********************************************************************************************************************************
*** TIPO DE DATOS GLOBALES
**********************************************************************************************************************************/

/*********************************************************************************************************************************
*** VARIABLES GLOBALES
**********************************************************************************************************************************/
extern uint8_t dir_timeout_f, send_data_f;
extern uint16_t ledV_Blink_t;
/*********************************************************************************************************************************
*** PROTOTIPOS DE FUNCIONES GLOBALES
**********************************************************************************************************************************/

//!< Prototipos de los Eventos

//!< Prototipos de las Acciones
void dir_timeout(void);
void LedV_Blink (void);
void send_data_timer(void);

uint8_t MOV_CHAR(char dato);
uint8_t COM_CHAR(char dato);
uint8_t START_CHAR(char dato);
uint8_t END_CHAR(char dato);
uint8_t NUM_CHAR(char dato);
#endif /* INC_AP_FUNCIONESMDEE_H_ */
