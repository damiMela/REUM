/*******************************************************************************************************************************//**
 *
 * @file		PR_BMP280.c
 * @brief		Descripcion del modulo
 * @date		Dec 19, 2020
 * @author		R2002 - Grupo2
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <PR/PR_BMP280.h>
#include <PR/PR_I2C.h>
/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define CANT_DATA_REGS 6
#define CANT_CALIB_PARAMS 25

#define RD_BIT 0x01
#define WR_BIT 0x00

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

#define SPI3E_OFF 0x00
#define SPI3E_ON  0x01
/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

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


volatile struct bmp280_dev dev;
static uint32_t bmp280_temperature_data = 0;
static uint32_t bmp280_pressure_data = 0;

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
static uint8_t sensor_data[CANT_DATA_REGS] = {0};
static uint8_t calib_data[CANT_CALIB_PARAMS] = {0};
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
	\fn  InicializarBMP280
	\brief Inicializa el I2C y configura el sensor
 	\author R2002 - Grupo2
 	\date Dec 19, 2020
	\return (uint8_t) "1" si se configuró correctamente. "0" de lo contrario.
*/
uint8_t InicializarBMP280(void){
	InicializarI2C();

	I2C_beginTransmition(BMP280_ADDRESS);
	I2C_put(BMP280_REG_CONTROL);
	I2C_put((SAMPLING_X2 << 5) | (SAMPLING_X16<< 2) | (BMP_MODE_NORMAL));
	I2C_put(BMP280_REG_CONFIG);
	I2C_put((STANDBY_MS_500 << 5) | (FILTER_X16 << 2) | (SPI3E_OFF << 0));
	I2C_put(BMP280_REG_DIG_T1);
	I2C_put(BMP280_READ);
	I2C_get(CANT_CALIB_PARAMS);
	uint8_t ret = I2C_endTransmition();

	I2C_getData(CANT_CALIB_PARAMS, calib_data);

	if(ret){
		set_calib_param();
		return 1;
	}
	return 0;
}

/**
	\fn  BMP280_getData
	\brief Obtiene datos de temperatura y presion del sensor
 	\author R2002 - Grupo2
 	\date Dec 19, 2020
*/
uint8_t BMP280_getData(void){
	static uint8_t init_falg = 0;
	uint8_t ret = 0;
	if(!init_falg){
		init_falg =  InicializarBMP280();
	}
	else{
		I2C_beginTransmition(BMP280_ADDRESS);
		I2C_put(BMP280_REG_PRESSUREDATA);
		I2C_put(BMP280_READ);
		I2C_get(CANT_DATA_REGS);
		ret = I2C_endTransmition();

		I2C_getData(CANT_DATA_REGS, sensor_data);
		bmp280_get_uncomp_data(sensor_data);
	}
	return ret;
}

/**
	\fn  getBMP280_temp
	\brief convierte datos del sensor en temperatura en celcius
 	\author R2002 - Grupo2
 	\date Dec 19, 2020
 	\return (int32_t) temperatura en grados celcius *10 (25.3 C° --> 2530)
*/
int32_t getBMP280_temp(){
	return get_comp_temp(bmp280_temperature_data);
}

/**
	\fn  BMP280_getData
	\brief convierte datos del sensor en presion en Pascales
 	\author R2002 - Grupo2
 	\date Dec 19, 2020
 	\return (uint32_t) Presion en Pascales
*/
uint32_t getBMP280_pres(){
	return get_comp_pres(bmp280_pressure_data);
}



/*********************************************************************************************************************************/
/*********************************************************************************************************************************/
//---------- LAS SIGUIENTES FUNCIONES SON PROVISTAS POR BOSCH Y SIRVEN PARA CALIBRAR Y OBTENER LOS VALORES DEL SENSOR -----------//
/*********************************************************************************************************************************/
/*********************************************************************************************************************************/

/*!
 * @brief This API reads the temperature and pressure data registers.
 * It gives the raw temperature and pressure data .
 */
void bmp280_get_uncomp_data(uint8_t * data)
{
	bmp280_pressure_data =
		(int32_t) ((((uint32_t) (data[0])) << 12) | (((uint32_t) (data[1])) << 4) | ((uint32_t) data[2] >> 4));

	bmp280_temperature_data =
		(int32_t) ((((int32_t) (data[3])) << 12) | (((int32_t) (data[4])) << 4) | (((int32_t) (data[5])) >> 4));
}

/*!
 * @brief This API is used to get the compensated temperature from
 * uncompensated temperature. This API uses 32 bit integers.
 */
int32_t get_comp_temp(int32_t uncomp_temp)
{
    int32_t var1, var2, result;

    var1 =
		((((uncomp_temp / 8) - ((int32_t) dev.calib_param.dig_t1 << 1))) * ((int32_t) dev.calib_param.dig_t2)) / 2048;

	var2 =
		(((((uncomp_temp / 16) - ((int32_t) dev.calib_param.dig_t1)) *
		   ((uncomp_temp / 16) - ((int32_t) dev.calib_param.dig_t1))) / 4096) * ((int32_t) dev.calib_param.dig_t3)) / 16384;

	dev.calib_param.t_fine = var1 + var2;
	result = (dev.calib_param.t_fine * 5 + 128) / 256;
	return result;
}

/*!
 * @brief This API is used to get the compensated pressure from
 * uncompensated pressure. This API uses 32 bit integers.
 */
uint32_t get_comp_pres(uint32_t uncomp_pres)
{
    int32_t var1, var2, result;

	var1 = (((int32_t) dev.calib_param.t_fine) / 2) - (int32_t) 64000;
	var2 = (((var1 / 4) * (var1 / 4)) / 2048) * ((int32_t) dev.calib_param.dig_p6);
	var2 = var2 + ((var1 * ((int32_t) dev.calib_param.dig_p5)) * 2);
	var2 = (var2 / 4) + (((int32_t) dev.calib_param.dig_p4) * 65536);
	var1 =
		(((dev.calib_param.dig_p3 * (((var1 / 4) * (var1 / 4)) / 8192)) / 8) +
		 ((((int32_t) dev.calib_param.dig_p2) * var1) / 2)) / 262144;
	var1 = ((((32768 + var1)) * ((int32_t) dev.calib_param.dig_p1)) / 32768);
	result = (uint32_t)(((int32_t)(1048576 - uncomp_pres) - (var2 / 4096)) * 3125);

	/* Avoid exception caused by division with zero */
	if (var1 != 0)
	{
		/* Check for overflows against UINT32_MAX/2; if pres is left-shifted by 1 */
		if (result < 0x80000000)
		{
			result = (result << 1) / ((uint32_t) var1);
		}
		else
		{
			result = (result / (uint32_t) var1) * 2;
		}
		var1 = (((int32_t) dev.calib_param.dig_p9) * ((int32_t) (((result / 8) * (result / 8)) / 8192))) /
			   4096;
		var2 = (((int32_t) (result / 4)) * ((int32_t) dev.calib_param.dig_p8)) / 8192;
		result = (uint32_t) ((int32_t) result + ((var1 + var2 + dev.calib_param.dig_p7) / 16));
    }
	return result;
}

/*!
 * @brief This API is used to read the calibration parameters used
 * for calculating the compensated data.
 */
void set_calib_param(void){
    dev.calib_param.dig_t1=
        (uint16_t)(((uint16_t) calib_data[BMP280_DIG_T1_MSB_POS] << 8) | ((uint16_t) calib_data[BMP280_DIG_T1_LSB_POS]));
    dev.calib_param.dig_t2 =
        (int16_t) (((int16_t ) calib_data[BMP280_DIG_T2_MSB_POS] << 8) | ((int16_t ) calib_data[BMP280_DIG_T2_LSB_POS]));
    dev.calib_param.dig_t3 =
        (int16_t) (((int16_t ) calib_data[BMP280_DIG_T3_MSB_POS] << 8) | ((int16_t ) calib_data[BMP280_DIG_T3_LSB_POS]));
    dev.calib_param.dig_p1 =
        (uint16_t)(((uint16_t) calib_data[BMP280_DIG_P1_MSB_POS] << 8) | ((uint16_t) calib_data[BMP280_DIG_P1_LSB_POS]));
    dev.calib_param.dig_p2 =
        (int16_t) (((int16_t ) calib_data[BMP280_DIG_P2_MSB_POS] << 8) | ((int16_t ) calib_data[BMP280_DIG_P2_LSB_POS]));
    dev.calib_param.dig_p3 =
        (int16_t) (((int16_t ) calib_data[BMP280_DIG_P3_MSB_POS] << 8) | ((int16_t ) calib_data[BMP280_DIG_P3_LSB_POS]));
    dev.calib_param.dig_p4 =
        (int16_t) (((int16_t ) calib_data[BMP280_DIG_P4_MSB_POS] << 8) | ((int16_t ) calib_data[BMP280_DIG_P4_LSB_POS]));
    dev.calib_param.dig_p5 =
        (int16_t) (((int16_t ) calib_data[BMP280_DIG_P5_MSB_POS] << 8) | ((int16_t ) calib_data[BMP280_DIG_P5_LSB_POS]));
    dev.calib_param.dig_p6 =
        (int16_t) (((int16_t ) calib_data[BMP280_DIG_P6_MSB_POS] << 8) | ((int16_t ) calib_data[BMP280_DIG_P6_LSB_POS]));
    dev.calib_param.dig_p7 =
        (int16_t) (((int16_t ) calib_data[BMP280_DIG_P7_MSB_POS] << 8) | ((int16_t ) calib_data[BMP280_DIG_P7_LSB_POS]));
    dev.calib_param.dig_p8 =
        (int16_t) (((int16_t ) calib_data[BMP280_DIG_P8_MSB_POS] << 8) | ((int16_t ) calib_data[BMP280_DIG_P8_LSB_POS]));
    dev.calib_param.dig_p9 =
        (int16_t) (((int16_t ) calib_data[BMP280_DIG_P9_MSB_POS] << 8) | ((int16_t ) calib_data[BMP280_DIG_P9_LSB_POS]));
}
