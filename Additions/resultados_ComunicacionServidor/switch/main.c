/**
*	\file main.c
*	\brief Resumen del contenido del archivo
*	\details Descripcion detallada del archivo
*	\author JuanAgustinOtero
*	\date 19-12-2020 19:03:18
*/

#include "funciones.h"














extern int MensajeDeConexionRed;extern int LedRojo;extern int LedVerde;extern int LedVerde_P;extern int MensajeDeConexionCliente;extern int CaracterDeInicio;extern int MensajeDeDireccion;extern int f_conexionExitosa;extern int dato_rx;extern int f_movimiento;extern int chequeodata;extern int bufferMovimiento;extern int buffervelocidad1;extern int buffervelocidad2;


void main(void)
{

//declaracion de variables
//inicializacion de perifericos

	inicializar() ;


	while(1)
	{

		maquina_Conexion();

		maquina_Lectura();

		maquina_Movimiento();


	}
}
