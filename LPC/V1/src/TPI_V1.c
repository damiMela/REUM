/*
===============================================================================
 Name        : TPI_V1.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include <DR/DR_Tipos.h>

//systick and timer drivers
#include <DR/DR_Systick.h>
#include <DR/DR_PLL.h>

//primitivas
#include <PR/PR_Timers.h>

#include <AP/AP_MdeE.h>
#include <AP/AP_FuncionesMdeE.h>


int main(void) {
	InicializarSystick();
	InicializarPLL();



    while(1) {
    	//---agregar siempre---//
    	Timers_run();
    	//---------------------//

    	maquina_Lectura();
    	maquina_Conexion();
		maquina_Movimiento();
		maquina_Envio_data();
    }

}
