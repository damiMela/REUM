/*******************************************************************************************************************************//**
 *
 * @file		I2C.c
 * @brief		Contiene las definiciones de las funciones del modulo
 * @date		3 oct. 2020
 * @author		Nicolás Taurozzi
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <DR/DR_I2C.h>
#include <DR/DR_Pinsel.h>
#include <DR/DR_GPIO.h>
/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define I2CONSET_I2EN       (1<<6)  /* I2C Control Set Register */
#define I2CONSET_AA         (1<<2)
#define I2CONSET_SI         (1<<3)
#define I2CONSET_STO        (1<<4)
#define I2CONSET_STA        (1<<5)

#define I2CONCLR_AAC        (1<<2)  /* I2C Control clear Register */
#define I2CONCLR_SIC        (1<<3)
#define I2CONCLR_STAC       (1<<5)
#define I2CONCLR_I2ENC      (1<<6)
/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/
#define I2C1 ((I2C_t*)0x4005C000UL)
/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/
typedef struct{
  __RW uint32_t CONSET;                     /*!< Offset: 0x000 (R/W)  I2C Control Set Register */
  __R  uint32_t STAT;                       /*!< Offset: 0x004 (R/ )  I2C Status Register */
  __RW uint32_t DAT;                        /*!< Offset: 0x008 (R/W)  I2C Data Register */
  __RW uint32_t ADR0;                       /*!< Offset: 0x00C (R/W)  I2C Slave Address Register 0 */
  __RW uint32_t SCLH;                       /*!< Offset: 0x010 (R/W)  SCH Duty Cycle Register High Half Word */
  __RW uint32_t SCLL;                       /*!< Offset: 0x014 (R/W)  SCL Duty Cycle Register Low Half Word */
  __RW uint32_t CONCLR;                     /*!< Offset: 0x018 (R/W)  I2C Control Clear Register */
  __RW uint32_t MMCTRL;                     /*!< Offset: 0x01C (R/W)  Monitor mode control register */
  __RW uint32_t ADR1           ;                       /*!< Offset: 0x020 (R/W)  I2C Slave Address Register 1 */
  __RW uint32_t ADR2;                       /*!< Offset: 0x024 (R/W)  I2C Slave Address Register 2 */
  __RW uint32_t ADR3;            /*!< Offset: 0x028 (R/W)  I2C Slave Address Register 3 */
  __R  uint32_t DATA_BUFFER;                /*!< Offset: 0x02C (R/ )  Data buffer Register */
  __RW uint32_t MASK[4];
} I2C_t;
/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
volatile uint32_t I2C1_State = I2C_IDLE;
volatile uint32_t I2C1_timeout = 0;

volatile uint8_t I2C1_MasterBuff[BUFSIZE];
volatile uint8_t I2C1_SlaveBuff[BUFSIZE];

volatile uint32_t I2C1_ReadLen;
volatile uint32_t I2C1_WriteLen;

volatile uint32_t I2C1_RdIdx = 0;
volatile uint32_t I2C1_WrIdx = 0;

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
	\fn      void Init_I2C1(void)
	\brief   Inicializacion del i2C1
 	\author  Nicolas Taurozzi
 	\date 	 3 oct. 2020
	\return  No hay retorno
*/
void InicializarI2C_DR(void)
{
	PCONP |= (1 << 19); //Energizo el I2C

	PCLKSEL1 &= ~(0x03 << 6); //Activo el clock

	//Configuro los pins
	setPinsel(SDA1,FUNCION_3); //SDA
	setPinsel(SCL1,FUNCION_3);  //SCL

	setPinmode(SDA1, MODE_NONE);
	setPinmode(SCL1, MODE_NONE); //Seteo el Open-drain mode

	setPinmode_OD(SDA1, MODE_OD_NLOW);
	setPinmode_OD(SCL1, MODE_OD_NLOW); //Seteo el Open-drain mode

	//Limpio los flags
	I2C1->CONCLR = I2CONCLR_AAC | I2CONCLR_SIC | I2CONCLR_STAC | I2CONCLR_I2ENC;

	I2C1->SCLH = 60;
	I2C1->SCLL = 60;

	ISER0 |= (1 << 11); //Habilito interrupciones

	I2C1->CONSET = I2CONSET_I2EN; //Habilito el I2C
}

/**
	\fn      void I2C1_IRQHandler(void)
	\brief   Handler de las interrupciones
 	\author  Nicolas Taurozzi
 	\date 	 3 oct. 2020
	\return  No hay retorno
*/
void I2C1_IRQHandler(void)
{
  uint8_t StatValue;
  I2C1_timeout = 0;
  /* this handler deals with master read and master write only */
  StatValue = I2C1->STAT;

  switch ( StatValue )
  {
	case 0x08:			/* A Start condition is issued. */
		I2C1_WrIdx = 0;
		I2C1->DAT = I2C1_MasterBuff[I2C1_WrIdx++];
		I2C1->CONCLR = (I2CONCLR_SIC | I2CONCLR_STAC);
		break;

	case 0x10:			/* A repeated started is issued */
		I2C1_RdIdx = 0;
		I2C1->DAT = I2C1_MasterBuff[I2C1_WrIdx++]; 		/* Send SLA with R bit set*/
		I2C1->CONCLR = (I2CONCLR_SIC | I2CONCLR_STAC);
		break;

	case 0x18:			/* SLA+W has been transmitted; ACK has been received. */
		if ( I2C1_WriteLen == 1 )
		{
		  I2C1->CONSET = I2CONSET_STO;      /* Set Stop flag */
		  I2C1_State = I2C_NO_DATA;
		}
		else
		{
		  I2C1->DAT = I2C1_MasterBuff[I2C1_WrIdx++];
		}
		I2C1->CONCLR = I2CONCLR_SIC;
		break;

	case 0x28:	/* Data byte has been transmitted, regardless ACK or NACK */
		if ( I2C1_WrIdx < I2C1_WriteLen )
		{
		  I2C1->DAT = I2C1_MasterBuff[I2C1_WrIdx++]; /* this should be the last one */
		}
		else
		{
		  if ( I2C1_ReadLen != 0 )
		  {
			I2C1->CONSET = I2CONSET_STA;	/* Set Repeated-start flag */
		  }
		  else
		  {
			I2C1->CONSET = I2CONSET_STO;      /* Set Stop flag */
			I2C1_State = I2C_OK;
		  }
		}
		I2C1->CONCLR = I2CONCLR_SIC;
		break;

	case 0x30:
		I2C1->CONSET = I2CONSET_STO;      /* Set Stop flag */
		I2C1_State = I2C_NACK_DATA;
		I2C1->CONCLR = I2CONCLR_SIC;
		break;

	case 0x40:	/* Master Receive, SLA_R has been sent */
		if ( (I2C1_RdIdx + 1) < I2C1_ReadLen )
		{
		  /* Will go to State 0x50 */
		  I2C1->CONSET = I2CONSET_AA;	/* assert ACK after data is received */
		}
		else
		{
		  /* Will go to State 0x58 */
		  I2C1->CONCLR = I2CONCLR_AAC;	/* assert NACK after data is received */
		}
		I2C1->CONCLR = I2CONCLR_SIC;
		break;

	case 0x50:	/* Data byte has been received, regardless following ACK or NACK */
		I2C1_SlaveBuff[I2C1_RdIdx++] = I2C1->DAT;
		if ( (I2C1_RdIdx + 1) < I2C1_ReadLen )
		{
		  I2C1->CONSET = I2CONSET_AA;	/* assert ACK after data is received */
		}
		else
		{
		  I2C1->CONCLR = I2CONCLR_AAC;	/* assert NACK on last byte */
		}
		I2C1->CONCLR = I2CONCLR_SIC;
		break;

	case 0x58:
		I2C1_SlaveBuff[I2C1_RdIdx++] = I2C1->DAT;
		I2C1_State = I2C_OK;
		I2C1->CONSET = I2CONSET_STO;	/* Set Stop flag */
		I2C1->CONCLR = I2CONCLR_SIC;	/* Clear SI flag */
		break;

	case 0x20:		/* SLA+W has been transmitted; NOT ACK has been received. */
	case 0x48:
		I2C1->CONSET = I2CONSET_STO;      /* Set Stop flag */
		I2C1_State = I2C_NACK_ADDRESS;
		I2C1->CONCLR = I2CONCLR_SIC;
		break;

	case 0x38:		/* Arbitration lost, in this example, we don't
					deal with multiple master situation */
	default:
		I2C1_State = I2C_ARBITRATION_LOST;
		I2C1->CONCLR = I2CONCLR_SIC;
		break;
  }
  return;
}

/**
	\fn      uint8_t I2CStop( uint32_t portNum )
	\brief   Setea las condiciones de stop del I2C y termina solo cuando se detuvo
 	\author  Nicolas Taurozzi
 	\date 	 3 oct. 2020
 	\param 	 [in] uint32_t portNum: Numero de canal del I2C del micro
	\return  TRUE
*/

void I2C1_Stop(void)
{
  I2C1->CONSET = I2CONSET_STO;      /* Set Stop flag */
  I2C1->CONCLR = I2CONCLR_SIC;  /* Clear SI flag */

  /*--- Wait for STOP detected ---*/
  while( I2C1->CONSET & I2CONSET_STO );
}

/**
	\fn      uint8_t I2CStop( uint32_t portNum )
	\brief   Rutina para completar una comunicacion I2C de inicio a fin.
			 Los estados intermedios son resueltos por el handler y antes
			 de que sea llamada se deben setear la cantidad de veces que
			 se va a leer y escribir
 	\author  Nicolas Taurozzi
 	\date 	 3 oct. 2020
 	\param 	 [in] uint32_t portNum: Numero de canal del I2C del micro
	\return  Estado del master al terminar
*/
uint8_t I2C1_Engine()
{
  /*--- Issue a start condition ---*/
  I2C1->CONSET = I2CONSET_STA;	/* Set Start flag */

  I2C1_State = I2C_BUSY;

  while ( I2C1_State == I2C_BUSY )
  {
	if ( I2C1_timeout >= MAX_TIMEOUT )
	{
	  I2C1_State = I2C_TIMEOUT;
	  break;
	}
	I2C1_timeout++;
  }
  I2C1->CONCLR = I2CONCLR_STAC;

  I2C1_Stop();

  return ( I2C1_State );
}
