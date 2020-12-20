/*******************************************************************************************************************************//**
 *
 * @file		AP_BMP280.c
 * @brief		Descripcion del modulo
 * @date		Dec 19, 2020
 * @author		R2002 - Grupo2
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <AP/AP_BMP280.h>
#include <PR/PR_I2C.h>
#include <DR/DR_I2C.h>
#include <stdio.h>
/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define BMP280_ADDRESS (0x76)
#define BMP280_WRITE 	BMP280_ADDRESS * 2
#define BMP280_READ		BMP280_WRITE + 1
#define BMP280_CHIPID (0x58)

#define   BMP280_REG_DIG_T1 	 	0x88
#define   BMP280_REG_DIG_T2 	 	0x8A
#define   BMP280_REG_DIG_T3 	 	0x8C
#define   BMP280_REG_DIG_P1 	 	0x8E
#define   BMP280_REG_DIG_P2 	 	0x90
#define   BMP280_REG_DIG_P3 	 	0x92
#define   BMP280_REG_DIG_P4 	 	0x94
#define   BMP280_REG_DIG_P5 	 	0x96
#define   BMP280_REG_DIG_P6 	 	0x98
#define   BMP280_REG_DIG_P7 	 	0x9A
#define   BMP280_REG_DIG_P8 	 	0x9C
#define   BMP280_REG_DIG_P9 	 	0x9E
#define   BMP280_REG_CHIPID 	 	0xD0
#define   BMP280_REG_VERSION		0xD1
#define   BMP280_REG_SOFTRESET  	0xE0
#define   BMP280_REG_CAL26 	 		0xE1 /**< R calibration = 0xE1-0xF0 */
#define   BMP280_REG_STATUS 	 	0xF3
#define   BMP280_REG_CONTROL 	 	0xF4
#define   BMP280_REG_CONFIG 	 	0xF5
#define   BMP280_REG_PRESSUREDATA 	0xF7
#define   BMP280_REG_TEMPDATA 	 	0xFA



/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/
typedef struct {
  uint16_t dig_T1; /**< dig_T1 cal register. */
  int16_t dig_T2;  /**<  dig_T2 cal register. */
  int16_t dig_T3;  /**< dig_T3 cal register. */

  uint16_t dig_P1; /**< dig_P1 cal register. */
  int16_t dig_P2;  /**< dig_P2 cal register. */
  int16_t dig_P3;  /**< dig_P3 cal register. */
  int16_t dig_P4;  /**< dig_P4 cal register. */
  int16_t dig_P5;  /**< dig_P5 cal register. */
  int16_t dig_P6;  /**< dig_P6 cal register. */
  int16_t dig_P7;  /**< dig_P7 cal register. */
  int16_t dig_P8;  /**< dig_P8 cal register. */
  int16_t dig_P9;  /**< dig_P9 cal register. */
} bmp280_calib_data;

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/
enum bmp280_sampling {
    SAMPLING_NONE,	//no over-sampling
    SAMPLING_X1,	//1x over-sampling
    SAMPLING_X2,	//2x over-sampling
    SAMPLING_X4,	//4x over-sampling
    SAMPLING_X8,	//8x over-sampling
    SAMPLING_X16	//16x over-sampling
};

enum bmp280_mode {
   BMP_MODE_SLEEP,
   BMP_MODE_FORCED,
   BMP_MODE_FORCED_ALT,
   BMP_MODE_NORMAL,
   BMP_MODE_SOFT_RESET = 0xB6
};
enum bmp280_filter{
	FILTER_OFF,	//no filtering
	FILTER_X2,	//2x filtering
	FILTER_X4,	//4x filtering
	FILTER_X8,	//8x filtering
	FILTER_X16,	//16x filtering
};

enum bmp280_standbyDuration{
	STANDBY_MS_1,	//1ms standby
	STANDBY_MS_62,	//62.5ms standby
	STANDBY_MS_125,	//125ms standby
	STANDBY_MS_250,	//250ms standby
	STANDBY_MS_500,	//500ms standby
	STANDBY_MS_1000,//1000ms standby
	STANDBY_MS_2000,//2000ms standby
	STANDBY_MS_4000	//4000ms standby
};



/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
static uint8_t BMPinit_f = 0;
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
 	\date Dec 19, 2020
 	\param [in] parametros de entrada
 	\param [out] parametros de salida
	\return tipo y descripcion de retorno
*/
uint8_t InicializarBMP280(){
	InicializarI2C();
	uint8_t id_msg[1] = {BMP280_REG_CHIPID};
	uint8_t id_rcv[1];

	I2C_read(BMP280_ADDRESS, BMP280_REG_CHIPID, 1, id_rcv);
	//I2C_readWrite(BMP280_ADDRESS, 1, id_msg, 1, id_rcv);

	if(id_rcv[0] == BMP280_CHIPID){
		/**configuraciones
		 * modo: NORMAL
		 * sampling temp: X2
		 * sampling pres: X16
		 * filtro: X16
		 * standby t: 500ms
		 */
		uint8_t control = 0, config = 0;
		control |= (SAMPLING_X2 << 5) | (SAMPLING_X16 << 2) | (BMP_MODE_NORMAL << 0);
		config  |= (STANDBY_MS_500 << 5) | (FILTER_X16 << 2);

		uint8_t config_msg[4] = {
				BMP280_REG_CONTROL,
				control,
				BMP280_REG_CONFIG,
				config
		};
		if(I2C_write(BMP280_ADDRESS, 4, config_msg)) {
			BMPinit_f = 1;
			return 1;
		}
	}
	return 0;
}

uint32_t getBMP280_temp(){
	if(!BMPinit_f){
		InicializarBMP280();
	}
	else{
		uint8_t temp_res[3] = {0};
		uint8_t pres_res[3] = {0};

		I2C_read(BMP280_ADDRESS, BMP280_REG_TEMPDATA, 3, temp_res);
	}
}
