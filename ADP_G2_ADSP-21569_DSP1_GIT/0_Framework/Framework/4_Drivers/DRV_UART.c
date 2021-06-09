#include "common.h"
#include "SYSTEM_PWR.h"

#define CAN_UART_INSTANCE				2u

#if (EZ_KIT_BOARD == 1u)
#define TUN_UART_INSTANCE				0u
#else
#define TUN_UART_INSTANCE				1u
#endif

volatile int32_t gUARTBusyRxFlg = 0;
volatile int32_t gUARTBusyRxNum = 0;
volatile int32_t gUARTBusyTxFlg = 0;
volatile int32_t gUARTBusyTxNum = 0;

int InitUART(void)
{
	return PASSED;
}

int DoneUART(void)
{
	return PASSED;
}

int ExecUART(void)
{
	return PASSED;
}

void InitUART_CAN(uint32_t baudrate)
{
#if(CAN_UART_INSTANCE == 0u)
	volatile uint32_t *pREG_UART_CTL = pREG_UART0_CTL;
	volatile uint32_t *pREG_UART_STAT = pREG_UART0_STAT;
	volatile uint32_t *pREG_UART_IMSK = pREG_UART0_IMSK;
	volatile uint32_t *pREG_DMA_RX_CFG = pREG_DMA21_CFG;
	volatile uint32_t *pREG_DMA_TX_CFG = pREG_DMA20_CFG;
	volatile uint32_t *pREG_DMA_RX_STAT = pREG_DMA21_STAT;
	volatile uint32_t *pREG_DMA_TX_STAT = pREG_DMA20_STAT;
	volatile uint32_t *pREG_UART_CLK = pREG_UART0_CLK;
#elif(CAN_UART_INSTANCE == 1u)
	volatile uint32_t *pREG_UART_CTL = pREG_UART1_CTL;
	volatile uint32_t *pREG_UART_STAT = pREG_UART1_STAT;
	volatile uint32_t *pREG_UART_IMSK = pREG_UART1_IMSK;
	volatile uint32_t *pREG_DMA_RX_CFG = pREG_DMA35_CFG;
	volatile uint32_t *pREG_DMA_TX_CFG = pREG_DMA34_CFG;
	volatile uint32_t *pREG_DMA_RX_STAT = pREG_DMA35_STAT;
	volatile uint32_t *pREG_DMA_TX_STAT = pREG_DMA34_STAT;
	volatile uint32_t *pREG_UART_CLK = pREG_UART1_CLK;
#elif(CAN_UART_INSTANCE == 2u)
	volatile uint32_t *pREG_UART_CTL = pREG_UART2_CTL;
	volatile uint32_t *pREG_UART_STAT = pREG_UART2_STAT;
	volatile uint32_t *pREG_UART_IMSK = pREG_UART2_IMSK;
	volatile uint32_t *pREG_DMA_RX_CFG = pREG_DMA38_CFG;
	volatile uint32_t *pREG_DMA_TX_CFG = pREG_DMA37_CFG;
	volatile uint32_t *pREG_DMA_RX_STAT = pREG_DMA38_STAT;
	volatile uint32_t *pREG_DMA_TX_STAT = pREG_DMA37_STAT;
	volatile uint32_t *pREG_UART_CLK = pREG_UART2_CLK;
#else
#error "This UART instance is not supported"
#endif

	uint32_t fsclk0 = 0u;

	fsclk0 = GetSClk0PWR();
	if(fsclk0 == 0u)
		return;

	*pREG_UART_CTL = 0;
	*pREG_UART_STAT = 0xFFFFFFFF;

	*pREG_UART_IMSK = 0;

	*pREG_DMA_TX_CFG = 0;
	*pREG_DMA_RX_CFG = 0;
	*pREG_DMA_TX_STAT = 0xFFFFFFFF;
	*pREG_DMA_RX_STAT = 0xFFFFFFFF;

	*pREG_UART_CLK = ( (fsclk0)/(baudrate) ) | (ENUM_UART_CLK_EN_DIV_BY_ONE);
	*pREG_UART_CTL = ENUM_UART_CTL_CLK_EN | ENUM_UART_CTL_WL8BITS;
}

void ConfigUART_CAN(int rw, unsigned char *address, unsigned int size)
{
#if(CAN_UART_INSTANCE == 0u)
	volatile uint32_t *pREG_UART_IMSK_SET = pREG_UART0_IMSK_SET;
	volatile uint32_t *pREG_DMA_RX_CFG = pREG_DMA21_CFG;
	volatile uint32_t *pREG_DMA_TX_CFG = pREG_DMA20_CFG;
	void *volatile *pREG_DMA_RX_ADDRSTART = pREG_DMA21_ADDRSTART;
	void *volatile *pREG_DMA_TX_ADDRSTART = pREG_DMA20_ADDRSTART;
	volatile uint32_t *pREG_DMA_RX_XCNT = pREG_DMA21_XCNT;
	volatile uint32_t *pREG_DMA_TX_XCNT = pREG_DMA20_XCNT;
	volatile int32_t *pREG_DMA_RX_XMOD = pREG_DMA21_XMOD;
	volatile int32_t *pREG_DMA_TX_XMOD = pREG_DMA20_XMOD;
#elif(CAN_UART_INSTANCE == 1u)
	volatile uint32_t *pREG_UART_IMSK_SET = pREG_UART1_IMSK_SET;
	volatile uint32_t *pREG_DMA_RX_CFG = pREG_DMA35_CFG;
	volatile uint32_t *pREG_DMA_TX_CFG = pREG_DMA34_CFG;
	void *volatile *pREG_DMA_RX_ADDRSTART = pREG_DMA35_ADDRSTART;
	void *volatile *pREG_DMA_TX_ADDRSTART = pREG_DMA34_ADDRSTART;
	volatile uint32_t *pREG_DMA_RX_XCNT = pREG_DMA35_XCNT;
	volatile uint32_t *pREG_DMA_TX_XCNT = pREG_DMA34_XCNT;
	volatile int32_t *pREG_DMA_RX_XMOD = pREG_DMA35_XMOD;
	volatile int32_t *pREG_DMA_TX_XMOD = pREG_DMA34_XMOD;
#elif(CAN_UART_INSTANCE == 2u)
	volatile uint32_t *pREG_UART_IMSK_SET = pREG_UART2_IMSK_SET;
	volatile uint32_t *pREG_DMA_RX_CFG = pREG_DMA38_CFG;
	volatile uint32_t *pREG_DMA_TX_CFG = pREG_DMA37_CFG;
	void *volatile *pREG_DMA_RX_ADDRSTART = pREG_DMA38_ADDRSTART;
	void *volatile *pREG_DMA_TX_ADDRSTART = pREG_DMA37_ADDRSTART;
	volatile uint32_t *pREG_DMA_RX_XCNT = pREG_DMA38_XCNT;
	volatile uint32_t *pREG_DMA_TX_XCNT = pREG_DMA37_XCNT;
	volatile int32_t *pREG_DMA_RX_XMOD = pREG_DMA38_XMOD;
	volatile int32_t *pREG_DMA_TX_XMOD = pREG_DMA37_XMOD;
#else
#error "This UART instance is not supported"
#endif

	if(address == NULL || size == 0)
	{
		return;
	}

	if(rw == 0)
	{
//		if (gUARTBusyRxFlg == 0)
//		{
			/*UART Rx DMA */
			*pREG_DMA_RX_CFG = 0;
			*pREG_DMA_RX_ADDRSTART = (void *)internal_to_system_address_translation((uint32_t)address);
			*pREG_DMA_RX_XCNT = size;
			*pREG_DMA_RX_XMOD = 1;
			//*pREG_DMA_RX_CFG = ENUM_DMA_CFG_XCNT_INT | ENUM_DMA_CFG_AUTO | ENUM_DMA_CFG_WRITE | ENUM_DMA_CFG_EN;
			*pREG_DMA_RX_CFG = ENUM_DMA_CFG_AUTO | ENUM_DMA_CFG_WRITE | ENUM_DMA_CFG_EN;
			*pREG_UART_IMSK_SET = (ENUM_UART_ERBFI_HI);

//			gUARTBusyRxFlg = 1;
//		}
//		else
//		{
//			gUARTBusyRxNum++;
//		}
	}
	else
	{
		if (gUARTBusyTxFlg == 0)
		{
			/* UART Tx DMA */
			//*pREG_DMA_TX_CFG = 0;
			*pREG_DMA_TX_ADDRSTART = (void *)internal_to_system_address_translation((uint32_t)address);
			*pREG_DMA_TX_XCNT = size;
			*pREG_DMA_TX_XMOD = 1;
			*pREG_DMA_TX_CFG = ENUM_DMA_CFG_XCNT_INT | ENUM_DMA_CFG_STOP | ENUM_DMA_CFG_SYNC | ENUM_DMA_CFG_EN;
			*pREG_UART_IMSK_SET = (ENUM_UART_ETBEI_HI);

			gUARTBusyTxFlg = 1;
		}
		else
		{
			gUARTBusyTxNum++;
		}
	}
}

void ResetUART_CAN(void)
{
#if(CAN_UART_INSTANCE == 0u)
	*pREG_UART0_CTL = 0;
#elif(CAN_UART_INSTANCE == 1u)
	*pREG_UART1_CTL = 0;
#elif(CAN_UART_INSTANCE == 2u)
	*pREG_UART2_CTL = 0;
#else
#error "This UART instance is not supported"
#endif
}

int32_t GetRxBusyUART_CAN(void)
{
	return gUARTBusyRxFlg;
}

void SetRxBusyUART_CAN(int32_t flag)
{
	gUARTBusyRxFlg = flag;
}

int32_t GetTxBusyUART_CAN(void)
{
	return gUARTBusyTxFlg;
}

void SetTxBusyUART_CAN(int32_t flag)
{
	gUARTBusyTxFlg = flag;
}

void DoneRxDMAIRQUART_CAN(void)
{
#if(CAN_UART_INSTANCE == 0u)
	*pREG_DMA21_STAT |= ENUM_DMA_STAT_IRQDONE;
#elif(CAN_UART_INSTANCE == 1u)
	*pREG_DMA35_STAT |= ENUM_DMA_STAT_IRQDONE;
#elif(CAN_UART_INSTANCE == 2u)
	*pREG_DMA38_STAT |= ENUM_DMA_STAT_IRQDONE;
#else
#error "This UART instance is not supported"
#endif
}

int32_t GetRxAddrUART_CAN(void)
{
#if(CAN_UART_INSTANCE == 0u)
	return (int32_t)(*pREG_DMA21_ADDR_CUR);
#elif(CAN_UART_INSTANCE == 1u)
	return (int32_t)(*pREG_DMA35_ADDR_CUR);
#elif(CAN_UART_INSTANCE == 2u)
	return (int32_t)(*pREG_DMA38_ADDR_CUR);
#else
#error "This UART instance is not supported"
#endif
}

void DoneTxDMAIRQUART_CAN(void)
{
#if(CAN_UART_INSTANCE == 0u)
	*pREG_DMA20_STAT |= ENUM_DMA_STAT_IRQDONE;
#elif(CAN_UART_INSTANCE == 1u)
	*pREG_DMA34_STAT |= ENUM_DMA_STAT_IRQDONE;
#elif(CAN_UART_INSTANCE == 2u)
	*pREG_DMA37_STAT |= ENUM_DMA_STAT_IRQDONE;
#else
#error "This UART instance is not supported"
#endif
}

int32_t GetTxAddrUART_CAN(void)
{
#if(CAN_UART_INSTANCE == 0u)
	return (int32_t)(*pREG_DMA20_ADDR_CUR);
#elif(CAN_UART_INSTANCE == 1u)
	return (int32_t)(*pREG_DMA34_ADDR_CUR);
#elif(CAN_UART_INSTANCE == 2u)
	return (int32_t)(*pREG_DMA37_ADDR_CUR);
#else
#error "This UART instance is not supported"
#endif
}

void InitUART_TUN(uint32_t baudrate)
{
#if(TUN_UART_INSTANCE == 0u)
	volatile uint32_t *pREG_UART_CTL = pREG_UART0_CTL;
	volatile uint32_t *pREG_UART_STAT = pREG_UART0_STAT;
	volatile uint32_t *pREG_UART_IMSK = pREG_UART0_IMSK;
	volatile uint32_t *pREG_UART_IMSK_SET = pREG_UART0_IMSK_SET;
	volatile uint32_t *pREG_DMA_RX_CFG = pREG_DMA21_CFG;
	volatile uint32_t *pREG_DMA_TX_CFG = pREG_DMA20_CFG;
	volatile uint32_t *pREG_DMA_RX_STAT = pREG_DMA21_STAT;
	volatile uint32_t *pREG_DMA_TX_STAT = pREG_DMA20_STAT;
	volatile uint32_t *pREG_UART_CLK = pREG_UART0_CLK;
#elif(TUN_UART_INSTANCE == 1u)
	volatile uint32_t *pREG_UART_CTL = pREG_UART1_CTL;
	volatile uint32_t *pREG_UART_STAT = pREG_UART1_STAT;
	volatile uint32_t *pREG_UART_IMSK = pREG_UART1_IMSK;
	volatile uint32_t *pREG_UART_IMSK_SET = pREG_UART1_IMSK_SET;
	volatile uint32_t *pREG_DMA_RX_CFG = pREG_DMA35_CFG;
	volatile uint32_t *pREG_DMA_TX_CFG = pREG_DMA34_CFG;
	volatile uint32_t *pREG_DMA_RX_STAT = pREG_DMA35_STAT;
	volatile uint32_t *pREG_DMA_TX_STAT = pREG_DMA34_STAT;
	volatile uint32_t *pREG_UART_CLK = pREG_UART1_CLK;
#elif(TUN_UART_INSTANCE == 2u)
	volatile uint32_t *pREG_UART_CTL = pREG_UART2_CTL;
	volatile uint32_t *pREG_UART_STAT = pREG_UART2_STAT;
	volatile uint32_t *pREG_UART_IMSK = pREG_UART2_IMSK;
	volatile uint32_t *pREG_UART_IMSK_SET = pREG_UART2_IMSK_SET;
	volatile uint32_t *pREG_DMA_RX_CFG = pREG_DMA38_CFG;
	volatile uint32_t *pREG_DMA_TX_CFG = pREG_DMA37_CFG;
	volatile uint32_t *pREG_DMA_RX_STAT = pREG_DMA38_STAT;
	volatile uint32_t *pREG_DMA_TX_STAT = pREG_DMA37_STAT;
	volatile uint32_t *pREG_UART_CLK = pREG_UART2_CLK;
#else
#error "This UART instance is not supported"
#endif

	uint32_t fsclk0 = 0u;

	fsclk0 = GetSClk0PWR();
	if(fsclk0 == 0u)
		return;

	*pREG_UART_CTL = 0;
	*pREG_UART_STAT = 0xFFFFFFFF;

	*pREG_UART_IMSK = 0;

	*pREG_DMA_TX_CFG = 0;
	*pREG_DMA_RX_CFG = 0;
	*pREG_DMA_TX_STAT = 0xFFFFFFFF;
	*pREG_DMA_RX_STAT = 0xFFFFFFFF;

	*pREG_UART_CLK = ( (fsclk0)/(baudrate) ) | (ENUM_UART_CLK_EN_DIV_BY_ONE);
	*pREG_UART_CTL = ENUM_UART_CTL_CLK_EN | ENUM_UART_CTL_WL8BITS;

	*pREG_UART_IMSK_SET = ENUM_UART_IMSK_ERBFI_HI;
}

void PutsUART_TUN(uint8_t *pData, uint32_t nSize)
{
	uint32_t count, i;

	for(i=0; i< nSize; i++)
	{
		count = 0;
		do {
#if(TUN_UART_INSTANCE == 0u)
			if( (*pREG_UART0_STAT & ENUM_UART_STAT_TX_EMPTY) )
#elif(TUN_UART_INSTANCE == 1u)
			if( (*pREG_UART1_STAT & ENUM_UART_STAT_TX_EMPTY) )
#elif(TUN_UART_INSTANCE == 2u)
			if( (*pREG_UART2_STAT & ENUM_UART_STAT_TX_EMPTY) )
#else
#error "This UART instance is not supported"
#endif
			{
#if(TUN_UART_INSTANCE == 0u)
				*pREG_UART0_THR = pData[i];
#elif(TUN_UART_INSTANCE == 1u)
				*pREG_UART1_THR = pData[i];
#elif(TUN_UART_INSTANCE == 2u)
				*pREG_UART2_THR = pData[i];
#else
#error "This UART instance is not supported"
#endif

				count = 0x5000;
			}
			else
			{
				count++;
			}
		} while( count < 0x5000 );
	}
}

void GetsUART_TUN(uint8_t *pData, uint32_t nSize)
{
	// will be implemented...
}

void PutcUART_TUN(uint8_t cByte)
{
#if(TUN_UART_INSTANCE == 0u)
	*pREG_UART0_THR = cByte;
#elif(TUN_UART_INSTANCE == 1u)
	*pREG_UART1_THR = cByte;
#elif(TUN_UART_INSTANCE == 2u)
	*pREG_UART2_THR = cByte;
#else
#error "This UART instance is not supported"
#endif
}

uint8_t GetcUART_TUN(void)
{
#if(TUN_UART_INSTANCE == 0u)
	return (uint8_t)((*pREG_UART0_RBR) & 0xFFu);
#elif(TUN_UART_INSTANCE == 1u)
	return (uint8_t)((*pREG_UART1_RBR) & 0xFFu);
#elif(TUN_UART_INSTANCE == 2u)
	return (uint8_t)((*pREG_UART2_RBR) & 0xFFu);
#else
#error "This UART instance is not supported"
#endif
}

void DisableRxUART_TUN(void)
{
	/* Rx UART Interrupt is unmasked */
#if(TUN_UART_INSTANCE == 0u)
	*pREG_UART0_IMSK_CLR = (uint32_t)ENUM_UART_IMSK_ERBFI_HI;
#elif(TUN_UART_INSTANCE == 1u)
	*pREG_UART1_IMSK_CLR = (uint32_t)ENUM_UART_IMSK_ERBFI_HI;
#elif(TUN_UART_INSTANCE == 2u)
	*pREG_UART2_IMSK_CLR = (uint32_t)ENUM_UART_IMSK_ERBFI_HI;
#else
#error "This UART instance is not supported"
#endif
}

void EnableRxUART_TUN(void)
{
	/* Rx UART Interrupt is unmasked */
#if(TUN_UART_INSTANCE == 0u)
	*pREG_UART0_IMSK_SET = (uint32_t)ENUM_UART_IMSK_ERBFI_HI;
#elif(TUN_UART_INSTANCE == 1u)
	*pREG_UART1_IMSK_SET = (uint32_t)ENUM_UART_IMSK_ERBFI_HI;
#elif(TUN_UART_INSTANCE == 2u)
	*pREG_UART2_IMSK_SET = (uint32_t)ENUM_UART_IMSK_ERBFI_HI;
#else
#error "This UART instance is not supported"
#endif
}

void DisableTxUART_TUN(void)
{
	/* Tx UART Interrupt is unmasked */
#if(TUN_UART_INSTANCE == 0u)
	*pREG_UART0_IMSK_CLR = (uint32_t)ENUM_UART_IMSK_ETBEI_HI;
#elif(TUN_UART_INSTANCE == 1u)
	*pREG_UART1_IMSK_CLR = (uint32_t)ENUM_UART_IMSK_ETBEI_HI;
#elif(TUN_UART_INSTANCE == 2u)
	*pREG_UART2_IMSK_CLR = (uint32_t)ENUM_UART_IMSK_ETBEI_HI;
#else
#error "This UART instance is not supported"
#endif
}

void EnableTxUART_TUN(void)
{
	/* Tx UART Interrupt is unmasked */
#if(TUN_UART_INSTANCE == 0u)
	*pREG_UART0_IMSK_SET = (uint32_t)ENUM_UART_IMSK_ETBEI_HI;
#elif(TUN_UART_INSTANCE == 1u)
	*pREG_UART1_IMSK_SET = (uint32_t)ENUM_UART_IMSK_ETBEI_HI;
#elif(TUN_UART_INSTANCE == 2u)
	*pREG_UART2_IMSK_SET = (uint32_t)ENUM_UART_IMSK_ETBEI_HI;
#else
#error "This UART instance is not supported"
#endif
}

