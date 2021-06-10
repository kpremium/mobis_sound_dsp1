#include <services/int/adi_int.h>

#include <stdio.h>
#include "common.h"

#include "Variation_MASD.h"

#include "DRV_DAI.h"
#include "DRV_DMA.h"

extern uint32_t sPDMA_AMP__I_Buf[PINGPONG_BUF*AP_A2B_BLKSIZ*AP_AMP_I_CH];
extern uint32_t sPDMA_AMP__O_Buf[PINGPONG_BUF*AP_A2B_BLKSIZ*AP_AMP_O_CH];
extern uint32_t sPDMA_ACC1_I_Buf[PINGPONG_BUF*AP_A2B_BLKSIZ*AP_ACC_I_CH];
extern uint32_t sPDMA_PMIC_I_Buf[PINGPONG_BUF*AP_A2B_BLKSIZ*AP_MIC_I_CH];
extern uint32_t sPDMA_IPC__I_Buf[PINGPONG_BUF*AP_A2B_BLKSIZ*AP_IPC_I_CH];
extern uint32_t sPDMA_IPC__O_Buf[PINGPONG_BUF*AP_A2B_BLKSIZ*AP_IPC_O_CH];
extern uint32_t sPDMA_VESS_O_Buf[PINGPONG_BUF*AP_A2B_BLKSIZ*AP_VES_O_CH];
extern uint32_t sPDMA_CAMP_I_Buf[PINGPONG_BUF*AP_A2B_BLKSIZ*AP_CAM_I_CH];
extern uint32_t sPDMA_CAMP_O_Buf[PINGPONG_BUF*AP_A2B_BLKSIZ*AP_CAM_O_CH];

static void config_SPORT0A_DMADescript( ST_DMA_DSCP *pDmaDscp);
static void config_SPORT0B_DMADescript( ST_DMA_DSCP *pDmaDscp);
static void config_SPORT2A_DMADescript( ST_DMA_DSCP *pDmaDscp);
static void config_SPORT2B_DMADescript( ST_DMA_DSCP *pDmaDscp);
static void config_SPORT3A_DMADescript( ST_DMA_DSCP *pDmaDscp);
static void config_SPORT3B_DMADescript( ST_DMA_DSCP *pDmaDscp);
static void config_SPORT4A_DMADescript( ST_DMA_DSCP *pDmaDscp);
static void config_SPORT4B_DMADescript( ST_DMA_DSCP *pDmaDscp);
static void config_SPORT6A_DMADescript( ST_DMA_DSCP *pDmaDscp);
static void config_SPORT6B_DMADescript( ST_DMA_DSCP *pDmaDscp);
static void config_SPORT7A_DMADescript( ST_DMA_DSCP *pDmaDscp);
static void config_SPORT7B_DMADescript( ST_DMA_DSCP *pDmaDscp);
  
volatile uint32_t gDai0Grp0Cnt			= 0;
volatile uint32_t gDai0Grp0Rdy			= 0;
volatile uint32_t gDai0Grp1Cnt			= 0;
volatile uint32_t gDai0Grp1Rdy			= 0;
volatile uint32_t gDai1Grp0Cnt			= 0;
volatile uint32_t gDai1Grp0Rdy			= 0;
volatile uint32_t gDai1Grp1Cnt			= 0;
volatile uint32_t gDai1Grp1Rdy			= 0;

/* Rx from AMP via A2B#1 */
ST_DMA_DSCP gSPORT0ADscp[2] =
{
	{
		.pNextDscp = (void *)((uint32_t)&gSPORT0ADscp[1] + MEM_SPACE_SYS_OFFSET),
		.pStartAddr = (uint32_t *)((uint32_t)&sPDMA_AMP__I_Buf[0] + MEM_SPACE_SYS_OFFSET),
		.Config = ENUM_DMA_CFG_DSCLIST | ENUM_DMA_CFG_FETCH07 | ENUM_DMA_CFG_ADDR2D | ENUM_DMA_CFG_YCNT_INT | ENUM_DMA_CFG_PSIZE04 | ENUM_DMA_CFG_MSIZE04 | ENUM_DMA_CFG_WRITE |ENUM_DMA_CFG_EN,
		.XCount = AP_AMP_I_CH,
		.XModify = AP_A2B_BLKSIZ*4,
		.YCount = AP_A2B_BLKSIZ,
		.YModify = ( ((-1)*AP_A2B_BLKSIZ*(AP_AMP_I_CH-1))+1)*4,
	},
	{
		.pNextDscp = (void *)((uint32_t)&gSPORT0ADscp[0]+ MEM_SPACE_SYS_OFFSET),
		.pStartAddr = (uint32_t *)((uint32_t)&sPDMA_AMP__I_Buf[AP_A2B_BLKSIZ*AP_AMP_I_CH] + MEM_SPACE_SYS_OFFSET),
		.Config = ENUM_DMA_CFG_DSCLIST | ENUM_DMA_CFG_FETCH07 | ENUM_DMA_CFG_ADDR2D | ENUM_DMA_CFG_YCNT_INT | ENUM_DMA_CFG_PSIZE04 | ENUM_DMA_CFG_MSIZE04 | ENUM_DMA_CFG_WRITE |ENUM_DMA_CFG_EN,
		.XCount = AP_AMP_I_CH,
		.XModify = AP_A2B_BLKSIZ*4,
		.YCount = AP_A2B_BLKSIZ,
		.YModify = ( ((-1)*AP_A2B_BLKSIZ*(AP_AMP_I_CH-1))+1)*4,
	}
};

/* Tx to AMP via A2B#1 */
ST_DMA_DSCP gSPORT0BDscp[2] =
{
	{
		.pNextDscp = (void *)((uint32_t)&gSPORT0BDscp[1] + MEM_SPACE_SYS_OFFSET),
		.pStartAddr = (uint32_t *)((uint32_t)&sPDMA_AMP__O_Buf[0] + MEM_SPACE_SYS_OFFSET),
		.Config = ENUM_DMA_CFG_DSCLIST | ENUM_DMA_CFG_FETCH07 | ENUM_DMA_CFG_ADDR2D | ENUM_DMA_CFG_YCNT_INT | ENUM_DMA_CFG_PSIZE04 | ENUM_DMA_CFG_MSIZE04 | ENUM_DMA_CFG_EN,
		.XCount = AP_AMP_O_CH,
		.XModify = AP_A2B_BLKSIZ*4,
		.YCount = AP_A2B_BLKSIZ,
		.YModify = ( ((-1)*AP_A2B_BLKSIZ*(AP_AMP_O_CH-1))+1)*4,
	},
	{
		.pNextDscp = (void *)((uint32_t)&gSPORT0BDscp[0]+ MEM_SPACE_SYS_OFFSET),
		.pStartAddr = (uint32_t *)((uint32_t)&sPDMA_AMP__O_Buf[AP_A2B_BLKSIZ*AP_AMP_O_CH] + MEM_SPACE_SYS_OFFSET),
		.Config = ENUM_DMA_CFG_DSCLIST | ENUM_DMA_CFG_FETCH07 | ENUM_DMA_CFG_ADDR2D | ENUM_DMA_CFG_YCNT_INT | ENUM_DMA_CFG_PSIZE04 | ENUM_DMA_CFG_MSIZE04 | ENUM_DMA_CFG_EN,
		.XCount = AP_AMP_O_CH,
		.XModify = AP_A2B_BLKSIZ*4,
		.YCount = AP_A2B_BLKSIZ,
		.YModify = ( ((-1)*AP_A2B_BLKSIZ*(AP_AMP_O_CH-1))+1)*4,
	}
};

/* A2B ACC1 Rx */
ST_DMA_DSCP gSPORT2ADscp[2] =
{
	{
		.pNextDscp = (void *)((uint32_t)&gSPORT2ADscp[1] + MEM_SPACE_SYS_OFFSET),
		.pStartAddr = (uint32_t *)((uint32_t)&sPDMA_ACC1_I_Buf[0] + MEM_SPACE_SYS_OFFSET),
		.Config = ENUM_DMA_CFG_DSCLIST | ENUM_DMA_CFG_FETCH07 | ENUM_DMA_CFG_ADDR2D | ENUM_DMA_CFG_YCNT_INT | ENUM_DMA_CFG_PSIZE04 | ENUM_DMA_CFG_MSIZE04 | ENUM_DMA_CFG_WRITE |ENUM_DMA_CFG_EN,
		.XCount = AP_ACC_I_CH,
		.XModify = AP_A2B_BLKSIZ*4,
		.YCount = AP_A2B_BLKSIZ,
		.YModify = ( ((-1)*AP_A2B_BLKSIZ*(AP_ACC_I_CH-1))+1)*4,
	},
	{
		.pNextDscp = (void *)((uint32_t)&gSPORT2ADscp[0]+ MEM_SPACE_SYS_OFFSET),
		.pStartAddr = (uint32_t *)((uint32_t)&sPDMA_ACC1_I_Buf[AP_A2B_BLKSIZ*AP_ACC_I_CH] + MEM_SPACE_SYS_OFFSET),
		.Config = ENUM_DMA_CFG_DSCLIST | ENUM_DMA_CFG_FETCH07 | ENUM_DMA_CFG_ADDR2D | ENUM_DMA_CFG_YCNT_INT | ENUM_DMA_CFG_PSIZE04 | ENUM_DMA_CFG_MSIZE04 | ENUM_DMA_CFG_WRITE |ENUM_DMA_CFG_EN,
		.XCount = AP_ACC_I_CH,
		.XModify = AP_A2B_BLKSIZ*4,
		.YCount = AP_A2B_BLKSIZ,
		.YModify = ( ((-1)*AP_A2B_BLKSIZ*(AP_ACC_I_CH-1))+1)*4,
	}
};

/* A2B PMIC Rx */
ST_DMA_DSCP gSPORT3ADscp[2] =
{
	{
		.pNextDscp = (void *)((uint32_t)&gSPORT3ADscp[1] + MEM_SPACE_SYS_OFFSET),
		.pStartAddr = (uint32_t *)((uint32_t)&sPDMA_PMIC_I_Buf[0] + MEM_SPACE_SYS_OFFSET),
		.Config = ENUM_DMA_CFG_DSCLIST | ENUM_DMA_CFG_FETCH07 | ENUM_DMA_CFG_ADDR2D | ENUM_DMA_CFG_YCNT_INT | ENUM_DMA_CFG_PSIZE04 | ENUM_DMA_CFG_MSIZE04 | ENUM_DMA_CFG_WRITE |ENUM_DMA_CFG_EN,
		.XCount = AP_MIC_I_CH,
		.XModify = AP_A2B_BLKSIZ*4,
		.YCount = AP_A2B_BLKSIZ,
		.YModify = ( ((-1)*AP_A2B_BLKSIZ*(AP_MIC_I_CH-1))+1)*4,
	},
	{
		.pNextDscp = (void *)((uint32_t)&gSPORT3ADscp[0] + MEM_SPACE_SYS_OFFSET),
		.pStartAddr = (uint32_t *)((uint32_t)&sPDMA_PMIC_I_Buf[AP_A2B_BLKSIZ*AP_MIC_I_CH] + MEM_SPACE_SYS_OFFSET),
		.Config = ENUM_DMA_CFG_DSCLIST | ENUM_DMA_CFG_FETCH07 | ENUM_DMA_CFG_ADDR2D | ENUM_DMA_CFG_YCNT_INT | ENUM_DMA_CFG_PSIZE04 | ENUM_DMA_CFG_MSIZE04 | ENUM_DMA_CFG_WRITE |ENUM_DMA_CFG_EN,
		.XCount = AP_MIC_I_CH,
		.XModify = AP_A2B_BLKSIZ*4,
		.YCount = AP_A2B_BLKSIZ,
		.YModify = ( ((-1)*AP_A2B_BLKSIZ*(AP_MIC_I_CH-1))+1)*4,
	}
};

/* TX to DSP2 for ANCASD */
ST_DMA_DSCP gSPORT4ADscp[2] =
{
	{
		.pNextDscp = (void *)((uint32_t)&gSPORT4ADscp[1] + MEM_SPACE_SYS_OFFSET),
		.pStartAddr = (uint32_t *)((uint32_t)&sPDMA_IPC__O_Buf[0] + MEM_SPACE_SYS_OFFSET),
		.Config = ENUM_DMA_CFG_DSCLIST | ENUM_DMA_CFG_FETCH07 | ENUM_DMA_CFG_ADDR2D | ENUM_DMA_CFG_YCNT_INT | ENUM_DMA_CFG_PSIZE04 | ENUM_DMA_CFG_MSIZE04 | ENUM_DMA_CFG_EN,
		.XCount = AP_IPC_O_CH,
		.XModify = AP_A2B_BLKSIZ*4,
		.YCount = AP_A2B_BLKSIZ,
		.YModify = ( ((-1)*AP_A2B_BLKSIZ*(AP_IPC_O_CH-1))+1)*4,
	},
	{
		.pNextDscp = (void *)((uint32_t)&gSPORT4ADscp[0] + MEM_SPACE_SYS_OFFSET),
		.pStartAddr = (uint32_t *)((uint32_t)&sPDMA_IPC__O_Buf[AP_A2B_BLKSIZ*AP_IPC_O_CH] + MEM_SPACE_SYS_OFFSET),
		.Config = ENUM_DMA_CFG_DSCLIST | ENUM_DMA_CFG_FETCH07 | ENUM_DMA_CFG_ADDR2D | ENUM_DMA_CFG_YCNT_INT | ENUM_DMA_CFG_PSIZE04 | ENUM_DMA_CFG_MSIZE04 | ENUM_DMA_CFG_EN,
		.XCount = AP_IPC_O_CH,
		.XModify = AP_A2B_BLKSIZ*4,
		.YCount = AP_A2B_BLKSIZ,
		.YModify = ( ((-1)*AP_A2B_BLKSIZ*(AP_IPC_O_CH-1))+1)*4,
	}
};

/* RX from DSP2 for ANCASD */
ST_DMA_DSCP gSPORT4BDscp[2] =
{
	{
		.pNextDscp = (void *)((uint32_t)&gSPORT4BDscp[1] + MEM_SPACE_SYS_OFFSET),
		.pStartAddr = (uint32_t *)((uint32_t)&sPDMA_IPC__I_Buf[0] + MEM_SPACE_SYS_OFFSET),
		.Config = ENUM_DMA_CFG_DSCLIST | ENUM_DMA_CFG_FETCH07 | ENUM_DMA_CFG_ADDR2D | ENUM_DMA_CFG_YCNT_INT | ENUM_DMA_CFG_PSIZE04 | ENUM_DMA_CFG_MSIZE04 | ENUM_DMA_CFG_WRITE |ENUM_DMA_CFG_EN,
		.XCount = AP_IPC_I_CH,
		.XModify = AP_A2B_BLKSIZ*4,
		.YCount = AP_A2B_BLKSIZ,
		.YModify = ( ((-1)*AP_A2B_BLKSIZ*(AP_IPC_I_CH-1))+1)*4,
	},
	{
		.pNextDscp = (void *)((uint32_t)&gSPORT4BDscp[0] + MEM_SPACE_SYS_OFFSET),
		.pStartAddr = (uint32_t *)((uint32_t)&sPDMA_IPC__I_Buf[AP_A2B_BLKSIZ*AP_IPC_I_CH] + MEM_SPACE_SYS_OFFSET),
		.Config = ENUM_DMA_CFG_DSCLIST | ENUM_DMA_CFG_FETCH07 | ENUM_DMA_CFG_ADDR2D | ENUM_DMA_CFG_YCNT_INT | ENUM_DMA_CFG_PSIZE04 | ENUM_DMA_CFG_MSIZE04 | ENUM_DMA_CFG_WRITE |ENUM_DMA_CFG_EN,
		.XCount = AP_IPC_I_CH,
		.XModify = AP_A2B_BLKSIZ*4,
		.YCount = AP_A2B_BLKSIZ,
		.YModify = ( ((-1)*AP_A2B_BLKSIZ*(AP_IPC_I_CH-1))+1)*4,
	}
};

/* TX for Camping Scenario */
ST_DMA_DSCP gSPORT6BDscp[2] =
{
	{
		.pNextDscp = (void *)((uint32_t)&gSPORT6BDscp[1] + MEM_SPACE_SYS_OFFSET),
		.pStartAddr = (uint32_t *)((uint32_t)&sPDMA_CAMP_O_Buf[0] + MEM_SPACE_SYS_OFFSET),
		.Config = ENUM_DMA_CFG_DSCLIST | ENUM_DMA_CFG_FETCH07 | ENUM_DMA_CFG_ADDR2D | /*ENUM_DMA_CFG_YCNT_INT |*/ ENUM_DMA_CFG_PSIZE04 | ENUM_DMA_CFG_MSIZE04 | ENUM_DMA_CFG_SYNC | ENUM_DMA_CFG_EN,
		.XCount = AP_CAM_O_CH,
		.XModify = AP_A2B_BLKSIZ*4,
		.YCount = AP_A2B_BLKSIZ,
		.YModify = ( ((-1)*AP_A2B_BLKSIZ*(AP_CAM_O_CH-1))+1)*4,
	},
	{
		.pNextDscp = (void *)((uint32_t)&gSPORT6BDscp[0] + MEM_SPACE_SYS_OFFSET),
		.pStartAddr = (uint32_t *)((uint32_t)&sPDMA_CAMP_O_Buf[AP_A2B_BLKSIZ*AP_CAM_O_CH] + MEM_SPACE_SYS_OFFSET),
		.Config = ENUM_DMA_CFG_DSCLIST | ENUM_DMA_CFG_FETCH07 | ENUM_DMA_CFG_ADDR2D | /*ENUM_DMA_CFG_YCNT_INT |*/ ENUM_DMA_CFG_PSIZE04 | ENUM_DMA_CFG_MSIZE04 | ENUM_DMA_CFG_SYNC | ENUM_DMA_CFG_EN,
		.XCount = AP_CAM_O_CH,
		.XModify = AP_A2B_BLKSIZ*4,
		.YCount = AP_A2B_BLKSIZ,
		.YModify = ( ((-1)*AP_A2B_BLKSIZ*(AP_CAM_O_CH-1))+1)*4,
	}
};

/* VESS TX */
ST_DMA_DSCP gSPORT7ADscp[2] =
{
	{
		.pNextDscp = (void *)((uint32_t)&gSPORT7ADscp[1] + MEM_SPACE_SYS_OFFSET),
		.pStartAddr = (uint32_t *)((uint32_t)&sPDMA_VESS_O_Buf[0] + MEM_SPACE_SYS_OFFSET),
		.Config = ENUM_DMA_CFG_DSCLIST | ENUM_DMA_CFG_FETCH07 | ENUM_DMA_CFG_ADDR2D | ENUM_DMA_CFG_YCNT_INT | ENUM_DMA_CFG_PSIZE04 | ENUM_DMA_CFG_MSIZE04 | ENUM_DMA_CFG_SYNC | ENUM_DMA_CFG_EN,
		.XCount = AP_VES_O_CH,
		.XModify = AP_A2B_BLKSIZ*4,
		.YCount = AP_A2B_BLKSIZ,
		.YModify = ( ((-1)*AP_A2B_BLKSIZ*(AP_VES_O_CH-1))+1)*4,
	},
	{
		.pNextDscp = (void *)((uint32_t)&gSPORT7ADscp[0] + MEM_SPACE_SYS_OFFSET),
		.pStartAddr = (uint32_t *)((uint32_t)&sPDMA_VESS_O_Buf[AP_A2B_BLKSIZ*AP_VES_O_CH] + MEM_SPACE_SYS_OFFSET),
		.Config = ENUM_DMA_CFG_DSCLIST | ENUM_DMA_CFG_FETCH07 | ENUM_DMA_CFG_ADDR2D | ENUM_DMA_CFG_YCNT_INT | ENUM_DMA_CFG_PSIZE04 | ENUM_DMA_CFG_MSIZE04 | ENUM_DMA_CFG_SYNC | ENUM_DMA_CFG_EN,
		.XCount = AP_VES_O_CH,
		.XModify = AP_A2B_BLKSIZ*4,
		.YCount = AP_A2B_BLKSIZ,
		.YModify = ( ((-1)*AP_A2B_BLKSIZ*(AP_VES_O_CH-1))+1)*4,
	}
};

/* ASRC RX for Camping Scenario */
ST_DMA_DSCP gSPORT7BDscp[2] =
{
	{
		.pNextDscp = (void *)((uint32_t)&gSPORT7BDscp[1] + MEM_SPACE_SYS_OFFSET),
		.pStartAddr = (uint32_t *)((uint32_t)&sPDMA_CAMP_I_Buf[0] + MEM_SPACE_SYS_OFFSET),
		.Config = ENUM_DMA_CFG_DSCLIST | ENUM_DMA_CFG_FETCH07 | ENUM_DMA_CFG_ADDR2D | ENUM_DMA_CFG_YCNT_INT | ENUM_DMA_CFG_PSIZE04 | ENUM_DMA_CFG_MSIZE04 | ENUM_DMA_CFG_WRITE | ENUM_DMA_CFG_SYNC | ENUM_DMA_CFG_EN,
		.XCount = AP_CAM_I_CH,
		.XModify = AP_A2B_BLKSIZ*4,
		.YCount = AP_A2B_BLKSIZ,
		.YModify = ( ((-1)*AP_A2B_BLKSIZ*(AP_CAM_I_CH-1))+1)*4,
	},
	{
		.pNextDscp = (void *)((uint32_t)&gSPORT7BDscp[0] + MEM_SPACE_SYS_OFFSET),
		.pStartAddr = (uint32_t *)((uint32_t)&sPDMA_CAMP_I_Buf[AP_A2B_BLKSIZ*AP_CAM_I_CH] + MEM_SPACE_SYS_OFFSET),
		.Config = ENUM_DMA_CFG_DSCLIST | ENUM_DMA_CFG_FETCH07 | ENUM_DMA_CFG_ADDR2D | ENUM_DMA_CFG_YCNT_INT | ENUM_DMA_CFG_PSIZE04 | ENUM_DMA_CFG_MSIZE04 | ENUM_DMA_CFG_WRITE | ENUM_DMA_CFG_SYNC | ENUM_DMA_CFG_EN,
		.XCount = AP_CAM_I_CH,
		.XModify = AP_A2B_BLKSIZ*4,
		.YCount = AP_A2B_BLKSIZ,
		.YModify = ( ((-1)*AP_A2B_BLKSIZ*(AP_CAM_I_CH-1))+1)*4,
	}
};


/* Rx from AMP via A2B#1 */
void config_SPORT0A_DMADescript( ST_DMA_DSCP *pDmaDscp)
{
	/* DMA0 : SPORT0A DMA */
	*pREG_DMA0_DSCPTR_NXT = (void *)internal_to_system_address_translation((uint32_t)pDmaDscp->pNextDscp);
	*pREG_DMA0_CFG = pDmaDscp->Config;
}

/* Tx to AMP via A2B#1 */
void config_SPORT0B_DMADescript( ST_DMA_DSCP *pDmaDscp)
{
	/* DMA1 : SPORT0B DMA */
	*pREG_DMA1_DSCPTR_NXT = (void *)internal_to_system_address_translation((uint32_t)pDmaDscp->pNextDscp);
	*pREG_DMA1_CFG = pDmaDscp->Config;
}

/* A2B ACC1 Rx */
void config_SPORT2A_DMADescript( ST_DMA_DSCP *pDmaDscp)
{
	/* DMA4 : SPORT2A DMA */
	*pREG_DMA4_DSCPTR_NXT = (void *)internal_to_system_address_translation((uint32_t)pDmaDscp->pNextDscp);
	*pREG_DMA4_CFG = pDmaDscp->Config;
}

void config_SPORT2B_DMADescript( ST_DMA_DSCP *pDmaDscp)
{
	/* DMA5 : SPORT2B DMA */
	*pREG_DMA5_DSCPTR_NXT = (void *)internal_to_system_address_translation((uint32_t)pDmaDscp->pNextDscp);
	*pREG_DMA5_CFG = pDmaDscp->Config;
}

/* A2B PMIC Rx */
void config_SPORT3A_DMADescript( ST_DMA_DSCP *pDmaDscp)
{
	/* DMA6 : SPORT3A DMA */
	*pREG_DMA6_DSCPTR_NXT = (void *)internal_to_system_address_translation((uint32_t)pDmaDscp->pNextDscp);
	*pREG_DMA6_CFG = pDmaDscp->Config;
}

void config_SPORT3B_DMADescript( ST_DMA_DSCP *pDmaDscp)
{
	/* DMA7 : SPORT3B DMA */
	*pREG_DMA7_DSCPTR_NXT = (void *)internal_to_system_address_translation((uint32_t)pDmaDscp->pNextDscp);
	*pREG_DMA7_CFG = pDmaDscp->Config;
}

/* TX to DSP2 for ANCASD */
void config_SPORT4A_DMADescript( ST_DMA_DSCP *pDmaDscp)
{
	/* DMA10 : SPORT4A DMA */
	*pREG_DMA10_DSCPTR_NXT = (void *)internal_to_system_address_translation((uint32_t)pDmaDscp->pNextDscp);
	*pREG_DMA10_CFG = pDmaDscp->Config;
}

/* RX from DSP2 for ANCASD */
void config_SPORT4B_DMADescript( ST_DMA_DSCP *pDmaDscp)
{
	/* DMA11 : SPORT4B DMA */
	*pREG_DMA11_DSCPTR_NXT = (void *)internal_to_system_address_translation((uint32_t)pDmaDscp->pNextDscp);
	*pREG_DMA11_CFG = pDmaDscp->Config;
}

void config_SPORT6A_DMADescript( ST_DMA_DSCP *pDmaDscp)
{
	/* DMA14 : SPORT6A DMA */
	*pREG_DMA14_DSCPTR_NXT = (void *)internal_to_system_address_translation((uint32_t)pDmaDscp->pNextDscp);
	*pREG_DMA14_CFG = pDmaDscp->Config;
}

/* TX for Camping Scenario */
void config_SPORT6B_DMADescript( ST_DMA_DSCP *pDmaDscp)
{
	/* DMA15 : SPORT6B DMA */
	*pREG_DMA15_DSCPTR_NXT = (void *)internal_to_system_address_translation((uint32_t)pDmaDscp->pNextDscp);
	*pREG_DMA15_CFG = pDmaDscp->Config;
}

/* VESS TX */
void config_SPORT7A_DMADescript( ST_DMA_DSCP *pDmaDscp)
{
	/* DMA16 : SPORT7A DMA */
	*pREG_DMA16_DSCPTR_NXT = (void *)internal_to_system_address_translation((uint32_t)pDmaDscp->pNextDscp);
	*pREG_DMA16_CFG = pDmaDscp->Config;
}

/* ASRC RX for Camping Scenario */
void config_SPORT7B_DMADescript( ST_DMA_DSCP *pDmaDscp)
{
	/* DMA17 : SPORT7B DMA */
	*pREG_DMA17_DSCPTR_NXT = (void *)internal_to_system_address_translation((uint32_t)pDmaDscp->pNextDscp);
	*pREG_DMA17_CFG = pDmaDscp->Config;
}

#pragma optimize_as_cmd_line

// Rx/Tx for ANC/ASD(AMP)
void ISR_DAI0_GRP0(unsigned int id, void* arg)
{
#if (EZ_KIT_BOARD == 1u)
#endif

	*pREG_DMA0_STAT |= ENUM_DMA_STAT_IRQDONE;	/* SPORT 0A Rx from AMP(A2B#1) */

#if (USE_DSP_CFG == 0u)
	*pREG_DMA1_STAT |= ENUM_DMA_STAT_IRQDONE;	/* SPORT 0B Tx to AMP(A2B#1) */
#endif

	gDai0Grp0Cnt++;
	gDai0Grp0Rdy = 1;

	adi_sec_Raise(INTR_SYS_SOFT0_INT);

#if (EZ_KIT_BOARD == 1u)
#endif
}

// Rx for Acc & Mic
void ISR_DAI0_GRP1(unsigned int id, void* arg)
{
	*pREG_DMA4_STAT |= ENUM_DMA_STAT_IRQDONE;	/* SPORT 2A, Rx from ACC */
	*pREG_DMA6_STAT |= ENUM_DMA_STAT_IRQDONE;	/* SPORT 3A, Rx from PMIC */

	gDai0Grp1Cnt++;
	gDai0Grp1Rdy = 1;
}

// Rx/Tx for DSP2
void ISR_DAI1_GRP0(unsigned int id, void* arg)
{
	*pREG_DMA10_STAT |= ENUM_DMA_STAT_IRQDONE;	/* SPORT 4A Tx to DSP2 */
//	*pREG_DMA11_STAT |= ENUM_DMA_STAT_IRQDONE;	/* SPORT 4B Rx from DSP2 */

	gDai1Grp0Cnt++;
	gDai1Grp0Rdy = 1;
}

// Tx for VESS
void ISR_DAI1_GRP1(unsigned int id, void* arg)
{
#if (EZ_KIT_BOARD == 1u)
#endif

	*pREG_DMA16_STAT |= ENUM_DMA_STAT_IRQDONE;
	*pREG_DMA17_STAT |= ENUM_DMA_STAT_IRQDONE;

	gDai1Grp1Cnt++;
	gDai1Grp1Rdy = 1;

	adi_sec_Raise(INTR_SYS_SOFT1_INT);

#if (EZ_KIT_BOARD == 1u)
#endif
}

uint32_t DRV_DMA_Init(void)
{
   config_SPORT0A_DMADescript(&gSPORT0ADscp[0]);	/* Rx from AMP via A2B#1 */
	config_SPORT2A_DMADescript(&gSPORT2ADscp[0]);	/* A2B ACC1 Rx */
	config_SPORT3A_DMADescript(&gSPORT3ADscp[0]);	/* A2B PMIC Rx */
	config_SPORT6B_DMADescript(&gSPORT6BDscp[0]);	/* TX for Camping Scenario */
	config_SPORT7A_DMADescript(&gSPORT7ADscp[0]);	/* VESS TX */
	config_SPORT7B_DMADescript(&gSPORT7BDscp[0]);	/* ASRC RX for Camping Scenario */
#if (USE_DSP_CFG == 0u)
	config_SPORT0B_DMADescript(&gSPORT0BDscp[0]);	/* Tx to AMP via A2B#1 */
#elif (USE_DSP_CFG == 1u)
	config_SPORT4A_DMADescript(&gSPORT4ADscp[0]);	/* TX to DSP2 for ANCASD */
#endif

 return PASSED;
}
