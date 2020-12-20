/*******************************************************************************************************************************//**
 *
 * @file		PR_BMP280.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		Dec 19, 2020
 * @author		R2002 - Grupo2
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef PR_PR_BMP280_H_
#define PR_PR_BMP280_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <DR/DR_Tipos.h>
#include <BMP280_definitions.h>
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
// extern tipo nombreVariable;

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
uint8_t BMP280_init();
void BMP280_getValues(void);

int32_t get_temp();
uint32_t get_pres();

//--bosch provided functions--//
void set_calib_param(void);
void bmp280_get_uncomp_data(uint8_t * data);
void get_comp_temp(int32_t *comp_temp, int32_t uncomp_temp);
void get_comp_pres(uint32_t *comp_pres, uint32_t uncomp_pres);

#endif /* PR_PR_BMP280_H_ */
