/*****************************************************************************
 * DRV_DAI.h
 *****************************************************************************/

#ifndef __DRV_DAI_H__
#define __DRV_DAI_H__

/* DAI SPT & INT Configuration */
#define USE_DAI_GROUP_SPT_EN
#define USE_DAI_GROUP_INT_EN

static void Disable_DAI_SRU(void);
static void Setup_DAI_SRU(void);
static void DRV_DAI_InitPAD(void);
uint32_t DRV_DAI_InitSRU(void);


#endif /* __DRV_DAI_H__ */
