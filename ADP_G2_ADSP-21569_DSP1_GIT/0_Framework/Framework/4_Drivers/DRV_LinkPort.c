#include "common.h"
#include "DRV_Interrupt.h"
#include "Variation_MASD.h"

#define DEF_LP_TX 0
#define DEF_LP_RX 1

#pragma align 8
#pragma section("seg_l1_block1")
float32_t fBlock_IP_LP[AP_IPC_BLKSIZ*AP_IPC_I_CH*3];

#pragma align 8
#pragma section("seg_l1_block1")
float32_t fBlock_OP_LP[AP_IPC_BLKSIZ*AP_IPC_O_CH*3];

void config_LP0(uint32_t dir)
{
	*pREG_LP0_CTL = ENUM_LP_CTL_RX_OVF_EN | ENUM_LP_CTL_RRQ_EN | ENUM_LP_CTL_TRQ_EN;
	if(dir == DEF_LP_TX)
	{
		*pREG_LP0_CTL |= ENUM_LP_CTL_TX;
		/* IF DIV = 0, LCLK = OCLK */
		/* ELSE LCLK = OCLK/(2 x DIV) */
		*pREG_LP0_DIV = 0;
	}
}

void config_LP1(uint32_t dir)
{
	*pREG_PADS0_PCFG0 |= BITM_PADS_PCFG0_FAULT_DIS;

	*pREG_LP1_CTL = ENUM_LP_CTL_RX_OVF_EN | ENUM_LP_CTL_RRQ_EN | ENUM_LP_CTL_TRQ_EN;
	if(dir == DEF_LP_TX)
	{
		*pREG_LP1_CTL |= ENUM_LP_CTL_TX;
		/* IF DIV = 0, LCLK = OCLK */
		/* ELSE LCLK = OCLK/(2 x DIV) */
		*pREG_LP1_DIV = 4;
	}
}

void enableLP0(void)
{
	*pREG_LP0_CTL |= ENUM_LP_CTL_EN;
}

void enableLP1(void)
{
	*pREG_LP1_CTL |= ENUM_LP_CTL_EN;
}

void config_LP0_DMA(uint32_t dir,uint32_t *buff, uint32_t xcount, uint32_t xmod, uint32_t ycount, uint32_t ymod)
{
	/* DMA30 : LP0 DMA */
	*pREG_DMA30_ADDRSTART = (void *)internal_to_system_address_translation((uint32_t)buff);
	*pREG_DMA30_XCNT = xcount;
	*pREG_DMA30_XMOD = xmod;
	*pREG_DMA30_YCNT = ycount;
	*pREG_DMA30_YMOD = ymod;
	*pREG_DMA30_CFG = ENUM_DMA_CFG_STOP | ENUM_DMA_CFG_XCNT_INT |ENUM_DMA_CFG_PSIZE01 | ENUM_DMA_CFG_MSIZE04;
	if(dir == DEF_LP_RX)
	{
		*pREG_DMA30_CFG |= 	ENUM_DMA_CFG_WRITE;
	}
	*pREG_DMA30_CFG |= 	ENUM_DMA_CFG_EN;
}

void config_LP1_DMA(uint32_t dir, uint32_t *buff, uint32_t xcount, uint32_t xmod, uint32_t ycount, uint32_t ymod)
{
	/* DMA36 : LP1 DMA */
	*pREG_DMA36_ADDRSTART = (void *)internal_to_system_address_translation((uint32_t)buff);
	*pREG_DMA36_XCNT = xcount;
	*pREG_DMA36_XMOD = xmod;
	*pREG_DMA36_YCNT = ycount;
	*pREG_DMA36_YMOD = ymod;
	*pREG_DMA36_CFG = ENUM_DMA_CFG_STOP | ENUM_DMA_CFG_XCNT_INT |ENUM_DMA_CFG_PSIZE01 | ENUM_DMA_CFG_MSIZE04;
	if(dir == DEF_LP_RX)
	{
		*pREG_DMA36_CFG |= 	ENUM_DMA_CFG_WRITE;
	}
	*pREG_DMA36_CFG |= 	ENUM_DMA_CFG_EN;
}

void InitLPBuffer(void)
{
	uint32_t iSample, iChannel;
	for(iChannel=0; iChannel<AP_IPC_O_CH*3; iChannel++)
	{
		for(iSample=0;iSample<AP_IPC_BLKSIZ;iSample++)
		{
			fBlock_OP_LP[AP_IPC_BLKSIZ*iChannel + iSample] = (float32_t)iSample;
		}
	}
}

void InitLinkPort0Rx(void)
{
	config_LP0(DEF_LP_RX);
	InitINTR_LinkPort();
	config_LP0_DMA(DEF_LP_RX, (uint32_t *)fBlock_IP_LP, AP_IPC_BLKSIZ*AP_IPC_O_CH*3, 4, 0, 0);
	enableLP0();
}

void InitLinkPort0Tx(void)
{
	InitLPBuffer();
	config_LP0(DEF_LP_TX);
	InitINTR_LinkPort();
	config_LP0_DMA(DEF_LP_TX, (uint32_t *)fBlock_OP_LP, AP_IPC_BLKSIZ*AP_IPC_O_CH*3, 4, 0, 0);
	enableLP0();
}

void InitLinkPort1Rx(void)
{
	config_LP1(DEF_LP_RX);
	InitINTR_LinkPort();
	config_LP1_DMA(DEF_LP_RX, (uint32_t *)fBlock_IP_LP, AP_IPC_BLKSIZ*AP_IPC_O_CH*3, 4, 0, 0);
	enableLP1();
}

void InitLinkPort1Tx(void)
{
	InitLPBuffer();
	config_LP1(DEF_LP_TX);
	InitINTR_LinkPort();
	config_LP1_DMA(DEF_LP_TX, (uint32_t *)fBlock_OP_LP, AP_IPC_BLKSIZ*AP_IPC_O_CH*3, 4, 0, 0);
	enableLP1();
}

void WriteDatatoDSP_LP1(void)
{
	config_LP1_DMA(DEF_LP_TX, (uint32_t *)fBlock_OP_LP, AP_IPC_BLKSIZ*AP_IPC_O_CH*3, 4, 0, 0);
}

void ISR_Linkport0(unsigned int id, void* arg)
{
	*pREG_DMA30_STAT |= ENUM_DMA_STAT_IRQDONE;
}

void ISR_Linkport1(unsigned int id, void* arg)
{
	*pREG_DMA36_STAT |= ENUM_DMA_STAT_IRQDONE;
}

