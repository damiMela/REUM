/*******************************************************************************************************************************//**
 *
 * @file		DR_I2C.c
 * @brief		Descripcion del modulo
 * @date		10 dic. 2020
 * @author		R2002 - Melamed Damian
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <DR/DR_I2C.h>
#include <DR/DR_PLL.h>
/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define		 MAX_TIMEOUT	(0x00FFFFFF)
/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/
#define POWER_I2C1_ON (PCONP |= (1 << PI2C1))
#define POWER_I2C1_OFF (PCONP &= ~(1 << PI2C1))

#define 	I2C1	((I2C_t *)(0x4005C000UL))
/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/
typedef struct _I2C_CONSET_t{
	uint32_t RESERVED_0:2;
	uint32_t AssertAck_set:1;
	uint32_t SI_flag:1;
	uint32_t STOP_falg:1;
	uint32_t START_flag:1;
	uint32_t I2C_En:1;
	uint32_t RESERVED_1:25;
} I2C_CONSET_t;

typedef struct _I2C_CONCLR_t{
	uint32_t RESERVED_0: 2;
	uint32_t AssertAck_clr:1;
	uint32_t I2C_Int_clr:1;
	uint32_t RESERVED_1:1;
	uint32_t START_flag_clr:1;
	uint32_t I2C_Disable:1;
	uint32_t RESERVED_2:25;
}I2C_CONCLR_t;

typedef struct _I2C_MMCTRL_t{
	uint32_t MonitorMode_en:1;
	uint32_t SCL_out_en:1;
	uint32_t Match_Int_en:1;
	uint32_t RESERVED_0:29;
}I2C_MMCTRL_t;

typedef struct _I2C_t{
	__RW I2C_CONSET_t CONSET;
	__R  uint32_t STAT;
	__RW uint32_t DAT;
	__RW uint32_t ADR0;
	__RW uint32_t SCLH;
	__RW uint32_t SCLL;
	__W  I2C_CONCLR_t CONCLR;
	__RW uint32_t MMCTRL;
	__RW uint32_t ADR1;
	__RW uint32_t ADR2;
	__RW uint32_t ADR3;
	__R  uint32_t DATA_BUFF;
	__RW uint32_t MASK[4];
}I2C_t;
/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
volatile uint8_t I2C1_Master_buff[BUFF_SIZE];
volatile uint8_t I2C1_Slave_buff[BUFF_SIZE];
volatile uint32_t I2C1_read_idx = 0, I2C1_write_idx = 0;

volatile uint32_t I2C1_readLenght, I2C1_writeLenght;

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
static uint32_t timeout = 0;
static uint8_t I2C1_state = I2C_IDLE;
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
 	\author R2002 - Melamed Damian
 	\date 10 dic. 2020
 	\param [in] parametros de entrada
 	\param [out] parametros de salida
	\return tipo y descripcion de retorno
*/
void InicializarI2C_DR(void){
	POWER_I2C1_ON;
	PCLKSEL1 &= ~(3 << PCLK_I2C1);

	//hacer en PR PINSEL. PINMODE modo 0x02. PINMODE_OD en 0x01

	I2C1->CONCLR.AssertAck_clr = 1;
	I2C1->CONCLR.I2C_Int_clr = 1;
	I2C1->CONCLR.START_flag_clr = 1;
	I2C1->CONCLR.I2C_Disable = 1;

	//Fi2c = (F_CLK/PCLK)/(SCLH+SCLL) = 100kHz
	I2C1->SCLH=125;
	I2C1->SCLL=125;

	ISER0 |= (1 << ISER_I2C1);
	I2C1->CONSET.I2C_En = 1;
}

uint8_t I2C_Start(void){
	uint8_t result = 0;
	timeout = 0;

	I2C1->CONSET.START_flag = 1;

	while(timeout <= MAX_TIMEOUT){
		if(I2C1_state == I2C_STARTED){
			result = 1;
			break;
		}
		timeout++;
	}

	return result;
}

uint8_t I2C_engine(void){
	I2C1->CONSET.START_flag = 1;
	I2C1_state = I2C_BUSY;

	while(I2C1_state == I2C_BUSY){
		//I2C1_state se cambia en la interrupcion

		if(timeout >= MAX_TIMEOUT){
			I2C1_state = I2C_TIMEOUT;
			timeout = 0;
			break;
		}

		timeout++;
	}

	I2C1->CONCLR.START_flag_clr = 1;

	return(I2C1_state);
}

void I2C_Stop(void){
	I2C1->CONSET.STOP_falg = 1;
	I2C1->CONCLR.I2C_Int_clr=1;

	//---esperar a que se detecte el STOP---//
	while(I2C1->CONSET.STOP_falg);
}


void I2C1_IRQHandler(void){
	uint8_t statValue;
	timeout = 0;

	statValue = I2C1->STAT;
	switch(statValue){
		case 0x08:{ 	//Se emitió una condición de inicio
			I2C1_write_idx = 0;
			I2C1->DAT = I2C1_Master_buff[ I2C1_write_idx++];

			I2C1->CONCLR.I2C_Int_clr = 1;
			I2C1->CONCLR.START_flag_clr = 1;

			//I2C1_write_idx++;
			break;
		}

		case 0x10:{		//se emitió condicion de inicio repetidas veces
			I2C1_read_idx = 0;

			I2C1->DAT = I2C1_Master_buff[I2C1_write_idx++];

			I2C1->CONCLR.I2C_Int_clr = 1;
			I2C1->CONCLR.START_flag_clr = 1;

			//I2C1_write_idx++;
			break;
		}

		case 0x18:{ 	//SLA+W ha sido enviado. se recibió Acknowledge
			if(I2C1_writeLenght == 1){
				I2C1->CONSET.STOP_falg = 1;
				I2C1_state = I2C_NO_DATA;
			}
			else{
				I2C1->DAT = I2C1_Master_buff[ I2C1_write_idx++ ];
				//I2C1_write_idx++;
			}

			I2C1->CONCLR.I2C_Int_clr = 1;
			break;
		}

		case 0x28:{		//Los datos en DAT han sido enviados. se recibio Acknowledge
			if(I2C1_write_idx < I2C1_writeLenght){
				I2C1->DAT = I2C1_Master_buff[ I2C1_write_idx ++];
				//I2C1_write_idx++;
			}
			else{
				if(I2C1_readLenght != 0)
					I2C1->CONSET.START_flag = 1;

				else{
					I2C1->CONSET.STOP_falg = 1;
					I2C1_state = I2C_OK;
				}
			}

			I2C1->CONCLR.I2C_Int_clr = 1;
			break;
		}

		case 0x030:{	//Los datos en DAT han sido enviados. se recibió NOT Acknowledge
			I2C1->CONSET.STOP_falg = 1;
			I2C1_state = I2C_NACK_DATA;
			I2C1->CONCLR.I2C_Int_clr = 1;
		}

		case 0x40:{		//se recibió SLA_R. se recibió Acknowledge
			if( (I2C1_read_idx +1) < I2C1_readLenght)
				//va a ir al estado 0x50
				I2C1->CONSET.AssertAck_set = 1; //acknowledege de que se recibió el dato
			else
				//va a ir ale stado 0x58
				I2C1->CONCLR.AssertAck_clr = 1;

			I2C1->CONCLR.I2C_Int_clr;
			break;
		}

		case 0x50:{		//Se recibió 1 byte de datos. Se envió Acknowledge
			I2C1_Slave_buff[ I2C1_read_idx ++] = I2C1->DAT;
			//I2C1_read_idx++;

			if( (I2C1_read_idx +1) < I2C1_readLenght)
				I2C1->CONSET.AssertAck_set = 1;
			else
				I2C1->CONCLR.AssertAck_clr = 1;

			I2C1->CONCLR.I2C_Int_clr = 1;
			break;
		}

		case 0x58:{		//se recibió 1 byte de datis. se envió NOT Acknowledge
			I2C1_Slave_buff[ I2C1_read_idx++ ] = I2C1->DAT;
			//I2C1_read_idx++;
			I2C1_state = I2C_OK;
			I2C1->CONSET.STOP_falg = 1;
			I2C1->CONCLR.I2C_Int_clr = 1;
			break;
		}

		case 0x20:
		case 0x48:{		//se recibió SLA+R o SLA+W. Se recibió NOT Acknowledge
			I2C1->CONSET.STOP_falg = 1;
			I2C1_state = I2C_NACK_ADDRESS;
			I2C1->CONCLR.I2C_Int_clr = 1;
			break;
		}

		default:
			I2C1_state = I2C_ARBITRATION_LOST;
			I2C1->CONCLR.I2C_Int_clr = 1;
			break;

	}
	return;

}




