
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
#include "AP_Depuracion.h" 

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
*	\fn void maquina_Conexion()
*	\brief Implementacion switch-case
*	\details 
*	\author JuanAgustinOtero
*	\date 19-12-2020 19:03:18
*/
void maquina_Conexion()
{
		static int estado = SIN_CONEXION;

		switch(estado)
		{
			case SIN_CONEXION:
			
				if( MensajeDeConexionRed == C( ) )
				{
					#ifdef DEPURAR
						Log( 0 , 0 , 0 );
					#endif

					ParpadeoLedV( );
					LedRojo = FALSE;

					estado = MODULO_EN_RED;	
				}
 

				break;
			
			case MODULO_EN_RED:
			
				if( MensajeDeConexionCliente == TRUE( ) )
				{
					#ifdef DEPURAR
						Log( 0 , 1 , 0 );
					#endif

					LedVerde = TRUE;
					f_conexionExitosa = TRUE;

					estado = CONECTADO;	
				}
 
				if( MensajeDeConexionRed == FALSE( ) )
				{
					#ifdef DEPURAR
						Log( 0 , 1 , 1 );
					#endif

					LedRojo = TRUE;
					estado = SIN_CONEXION;	
				}
 

				break;
			
			case CONECTADO:
			
				if( MensajeDeConexionCliente == FALSE( ) )
				{
					#ifdef DEPURAR
						Log( 0 , 2 , 0 );
					#endif

					f_conexionExitosa = FALSE;
					ParpadeoLedV( );
					LedVerde = FALSE;

					estado = MODULO_EN_RED;	
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
		static int estado = ESPERA_INICIO;

		switch(estado)
		{
			case ESPERA_INICIO:
			
				if( dato_rx == START_CHAR( ) )
				{
					#ifdef DEPURAR
						Log( 1 , 0 , 0 );
					#endif

					
					estado = ESPERA_MENSAJE_MOVIMIENTO;	
				}
 

				break;
			
			case ESPERA_MENSAJE_MOVIMIENTO:
			
				if( chequeodata == FALSE( ) )
				{
					#ifdef DEPURAR
						Log( 1 , 1 , 0 );
					#endif

					SinMovimiento( );
					f_movimiento = FALSE;

					estado = ESPERA_FIN;	
				}
 
				if( dato_rx == MOV_CHAR( ) )
				{
					#ifdef DEPURAR
						Log( 1 , 1 , 1 );
					#endif

					bufferMovimiento = dato_rx;
					estado = ESPERA_INICIO;	
				}
 

				break;
			
			case ESPERA_FIN:
			
				if( dato_rx == END_CHAR( ) )
				{
					#ifdef DEPURAR
						Log( 1 , 2 , 0 );
					#endif

					f_movimiento = TRUE;
					estado = ESPERA_MENSAJE_MOVIMIENTO;	
				}
 

				break;
			
			case ESPERAR_MENSAJE_VELOCIDAD_1:
			

				break;
			
			case ESPERAR_MENSAJE_VELOCIDAD_2:
			

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
			
				if( f_movimiento == TRUE && bufferMovimiento == F( ) )
				{
					#ifdef DEPURAR
						Log( 2 , 0 , 0 );
					#endif

					MovimientoFrontalOn();
					estado = ADELANTE;	
				}
 

				break;
			
			case ADELANTE:
			
				if((f_movimiento == TRUE && bufferMovimiento != F) || f_movimiento == FALSE)
				{
					#ifdef DEPURAR
						Log( 2 , 1 , 0 );
					#endif

					SinMovimiento();
					estado = ATRAS;	
				}
 
				if( -1( ) )
				{
					#ifdef DEPURAR
						Log( 2 , 1 , 1 );
					#endif

					-1;
					estado = SIN_MOVIMIENTO;	
				}
 

				break;
			
			case ATRAS:
			
				if(f_movimiento == FALSE || (f_movimiento == TRUE && bufferMovimiento != B))
				{
					#ifdef DEPURAR
						Log( 2 , 2 , 0 );
					#endif

					SinMovimiento();
					estado = ADELANTE;	
				}
 

				break;
			
			case DERECHA:
			

				break;
			
			case IZQUEIRDA:
			

				break;
			
			default: estado = SIN_MOVIMIENTO;
		}


}

