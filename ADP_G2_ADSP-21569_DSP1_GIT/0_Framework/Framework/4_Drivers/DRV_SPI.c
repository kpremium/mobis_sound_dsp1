
#include <sru21569.h>
//#include "w25q128fv.h"

#include "common.h"

#include "DRV_DMA.h"
#include "DRV_SPI.h"


#ifndef pREG_SPI0_CTL
#define pREG_SPI0_CTL (volatile void *)0x1
#endif

#ifndef pREG_SPI1_CTL
#define pREG_SPI1_CTL (volatile void *)0x1
#endif

#ifndef pREG_SPI2_CTL
#define pREG_SPI2_CTL (volatile void *)0x1
#endif

static void configMasterSPI2(void)
{
	*pREG_SPI2_CTL = 0;
	*pREG_SPI2_CLK				= 4;
	*pREG_SPI2_DLY				= 0;		//((1 << BITP_SPI_DLY_STOP) & BITM_SPI_DLY_STOP) ;
	*pREG_SPI2_SLVSEL= ENUM_SPI_SLVSEL_SSEL1_HI | ENUM_SPI_SLVSEL_SSEL1_EN;
	*pREG_SPI2_SLVSEL= ENUM_SPI_SLVSEL_SSEL1_HI | ENUM_SPI_SLVSEL_SSEL1_EN;

	*pREG_SPI2_CTL	 = ENUM_SPI_CTL_MASTER ;
	*pREG_SPI2_TXCTL = ENUM_SPI_TXCTL_TTI_EN | ENUM_SPI_TXCTL_TWC_EN | ENUM_SPI_TXCTL_ZERO ;
	*pREG_SPI2_RXCTL = ENUM_SPI_RXCTL_OVERWRITE ;
}

void InitSPI2(void)
{
	configMasterSPI2();

	*pREG_SPI2_TXCTL |= ENUM_SPI_TXCTL_TX_EN;				//			  enable Tx SPI
	*pREG_SPI2_RXCTL |= ENUM_SPI_RXCTL_RX_EN;				//			  enable Rx SPI
	*pREG_SPI2_CTL	 |= ENUM_SPI_CTL_EN;
}

void DisableSPI2(void)
{
	*pREG_SPI2_CTL	 = 0x00;
}

int DRV_SPI_Init(void)
{
#ifndef USE_SPI2_MM_FLASH
	InitSPI2();
#else
	SetupSPI2MM();
#endif

	return PASSED;
}

int8_t SPI2_Read(uint8_t *data, int32_t count)
{
	int32_t word_count,i,loop_count=0;
	uint8_t temp;
	int8_t res = 0;
	volatile uint32_t stat;

	word_count = count;
	while(word_count>0)
	{
		int twc;

		twc = word_count < BITM_SPI_TWC_VALUE ? word_count : BITM_SPI_TWC_VALUE;
		*pREG_SPI2_TWC = twc;
		*pREG_SPI2_TXCTL = ENUM_SPI_TXCTL_TTI_EN | ENUM_SPI_TXCTL_TWC_EN | ENUM_SPI_TXCTL_TX_EN ;
		*pREG_SPI2_RXCTL = ENUM_SPI_RXCTL_RX_EN;

		for(i=0; i<twc; i++)
		{
			while (*pREG_SPI2_STAT & BITM_SPI_STAT_TFF);
			*pREG_SPI2_TFIFO = 0x00;
			while (*pREG_SPI2_STAT & BITM_SPI_STAT_RFE);
			*(data+i) = *pREG_SPI2_RFIFO;
		}

		loop_count = 0;
		do
		{
			stat = *pREG_SPI2_STAT;
			if ((stat & BITM_SPI_STAT_TF) == ENUM_SPI_TF_HI)
				break;

			loop_count++;
			if(loop_count == 1000000)
			{
				printf("SPI Status Error\n");
				res = -1;
				break;
			}
		}
		while (1);

		/* clear the transfer finish indication */
		*pREG_SPI2_STAT = ENUM_SPI_TF_HI;

		*pREG_SPI2_TXCTL = 0;
		*pREG_SPI2_RXCTL = 0;

		word_count -= twc;
		data += twc;
	}

	return res;
}

int8_t SPI2_Write(uint8_t *data, int32_t count)
{
	int32_t word_count,i,loop_count=0;
	uint8_t temp;
	int8_t res = 0;
	volatile uint32_t stat;

	word_count = count;
	while(word_count>0)
	{
		int twc;

		twc = word_count < BITM_SPI_TWC_VALUE ? word_count : BITM_SPI_TWC_VALUE;
		*pREG_SPI2_TWC = twc;
		*pREG_SPI2_TXCTL = ENUM_SPI_TXCTL_TTI_EN | ENUM_SPI_TXCTL_TWC_EN | ENUM_SPI_TXCTL_TX_EN ;
		*pREG_SPI2_RXCTL = ENUM_SPI_RXCTL_RX_EN;

		for(i=0; i<twc; i++)
		{
			while (*pREG_SPI2_STAT & BITM_SPI_STAT_TFF);
			*pREG_SPI2_TFIFO = data[i];
			while (*pREG_SPI2_STAT & BITM_SPI_STAT_RFE);
			temp = *pREG_SPI2_RFIFO;
		}

		loop_count = 0;
		do
		{
			stat = *pREG_SPI2_STAT;
			if ((stat & BITM_SPI_STAT_TF) == ENUM_SPI_TF_HI)
				break;

			loop_count++;
			if(loop_count == 1000000)
			{
				printf("SPI Status Error\n");
				res = -1;
				break;
			}
		}
		while (1);

		/* clear the transfer finish indication */
		*pREG_SPI2_STAT = ENUM_SPI_TF_HI;

		*pREG_SPI2_TXCTL = 0;
		*pREG_SPI2_RXCTL = 0;

		word_count -= twc;
		data += twc;
	}

	return res;
}

void SPI2_Select(void)
{
	*pREG_SPI2_SLVSEL= ENUM_SPI_SLVSEL_SSEL1_LO | ENUM_SPI_SLVSEL_SSEL1_EN;
	*pREG_SPI2_SLVSEL= ENUM_SPI_SLVSEL_SSEL1_LO | ENUM_SPI_SLVSEL_SSEL1_EN;
}

void SPI2_Deselect(void)
{
	*pREG_SPI2_SLVSEL= ENUM_SPI_SLVSEL_SSEL1_HI | ENUM_SPI_SLVSEL_SSEL1_EN;
	*pREG_SPI2_SLVSEL= ENUM_SPI_SLVSEL_SSEL1_HI | ENUM_SPI_SLVSEL_SSEL1_EN;
}

void SetupSPI2MM(void)
{
	*pREG_SPI2_CLK = 0x01;	/* SSCLK/(Baud+1) = 122.88/2 = 61.44Mbps */
	*pREG_SPI2_DLY = (((3 << BITP_SPI_DLY_STOP) & BITM_SPI_DLY_STOP) |
					((1 << BITP_SPI_DLY_LEADX) & BITM_SPI_DLY_LEADX) |
					((1 << BITP_SPI_DLY_LAGX) & BITM_SPI_DLY_LAGX));
	*pREG_SPI2_CTL = (ENUM_SPI_CTL_MM_EN |
					ENUM_SPI_CTL_MASTER |
					ENUM_SPI_CTL_HW_SSEL |
					//ENUM_SPI_CTL_ASSRT_SSEL |
					ENUM_SPI_CTL_SIZE32 |
					ENUM_SPI_CTL_MSB_FIRST |
					ENUM_SPI_CTL_FAST_EN |
					((1 << BITP_SPI_CTL_CPHA) & BITM_SPI_CTL_CPHA) |
					((1 << BITP_SPI_CTL_CPOL) & BITM_SPI_CTL_CPOL) |
					ENUM_SPI_CTL_MIO_QUAD);
	*pREG_SPI2_TXCTL = ( BITM_SPI_TXCTL_TTI | BITM_SPI_TXCTL_TEN );
	*pREG_SPI2_RXCTL = ( BITM_SPI_RXCTL_REN );

	*pREG_SPI2_MMRDH = (((0xEB	<< BITP_SPI_MMRDH_OPCODE	) & BITM_SPI_MMRDH_OPCODE)	|
						((3		<< BITP_SPI_MMRDH_ADRSIZE	) & BITM_SPI_MMRDH_ADRSIZE)	|
						((1		<< BITP_SPI_MMRDH_ADRPINS	) & BITM_SPI_MMRDH_ADRPINS)	|

						((5		<< BITP_SPI_MMRDH_DMYSIZE	) & BITM_SPI_MMRDH_DMYSIZE)	|
 
						((0x00	<< BITP_SPI_MMRDH_MODE		) & BITM_SPI_MMRDH_MODE)	|
						((0		<< BITP_SPI_MMRDH_TRIDMY	) & BITM_SPI_MMRDH_TRIDMY)	|
						((0		<< BITP_SPI_MMRDH_MERGE		) & BITM_SPI_MMRDH_MERGE)	|
						((0		<< BITP_SPI_MMRDH_WRAP		) & BITM_SPI_MMRDH_WRAP)	|
						((0		<< BITP_SPI_MMRDH_CMDSKIP	) & BITM_SPI_MMRDH_CMDSKIP)	|
						((0		<< BITP_SPI_MMRDH_CMDPINS	) & BITM_SPI_MMRDH_CMDPINS));
	*pREG_SPI2_MMTOP = 0x7FFFFFFF;
	*pREG_SPI2_SLVSEL = ENUM_SPI_SLVSEL_SSEL1_HI | ENUM_SPI_SLVSEL_SSEL1_EN;
	*pREG_SPI2_SLVSEL = ENUM_SPI_SLVSEL_SSEL1_HI | ENUM_SPI_SLVSEL_SSEL1_EN;

	*pREG_SPI2_CTL |= BITM_SPI_CTL_EN;
}

