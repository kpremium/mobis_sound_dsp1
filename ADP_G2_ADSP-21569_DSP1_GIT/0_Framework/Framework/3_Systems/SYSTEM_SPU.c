/*******************************************************************************
Copyright (c) 2019 - Analog Devices Inc. All Rights Reserved.
This software is proprietary & confidential to Analog Devices, Inc.
and its licensors.
******************************************************************************/
#include <stdio.h>

#include <services/spu/adi_spu.h>
#include "common.h"
#include "SYSTEM_SPU.h"

// The System Protection Unit (SPU) instance number to be initialized
#define D_SYS_SPU_DEV_ID				(0)

#define CheckResult(result)				\
if (result != ADI_SPU_SUCCESS) {		\
	printf("SPU failure\n");			\
	return FAILED;						\
}

static ADI_SPU_HANDLE shSpu;

static uint8_t saiSpuMemory[ADI_SPU_MEMORY_SIZE * 4];

uint8_t saiSpuPidMap[E_SYS_SPU_PID_MAX] =
{
    D_SYS_SPU_WP_SPORT0A,
    D_SYS_SPU_WP_SPORT0B,
    D_SYS_SPU_WP_SPORT1A,
    D_SYS_SPU_WP_SPORT1B,
    D_SYS_SPU_WP_SPORT2A,
    D_SYS_SPU_WP_SPORT2B,
    D_SYS_SPU_WP_SPORT3A,
    D_SYS_SPU_WP_SPORT3B,
    D_SYS_SPU_WP_SPORT4A,
    D_SYS_SPU_WP_SPORT4B,
    D_SYS_SPU_WP_SPORT5A,
    D_SYS_SPU_WP_SPORT5B,
    D_SYS_SPU_WP_SPORT6A,
    D_SYS_SPU_WP_SPORT6B,
    D_SYS_SPU_WP_SPORT7A,
    D_SYS_SPU_WP_SPORT7B,    
    D_SYS_SPU_WP_LP0,    
    D_SYS_SPU_WP_LP1,
    D_SYS_SPU_WP_LP0_DMA30,
    D_SYS_SPU_WP_LP1_DMA36,
    D_SYS_SPU_WP_PORTA,
    D_SYS_SPU_WP_PORTB,
    D_SYS_SPU_WP_PORTC,    
    D_SYS_SPU_WP_SPORT0A_DMA0,   
    D_SYS_SPU_WP_SPORT0B_DMA1,
    D_SYS_SPU_WP_SPORT1A_DMA2,    
    D_SYS_SPU_WP_SPORT1B_DMA3,    
    D_SYS_SPU_WP_SPORT2A_DMA4,    
    D_SYS_SPU_WP_SPORT2B_DMA5,    
    D_SYS_SPU_WP_SPORT3A_DMA6,    
    D_SYS_SPU_WP_SPORT3B_DMA7,
    D_SYS_SPU_WP_SPORT4A_DMA10,    
    D_SYS_SPU_WP_SPORT4B_DMA11,    
    D_SYS_SPU_WP_SPORT5A_DMA12,    
    D_SYS_SPU_WP_SPORT5B_DMA13,    
    D_SYS_SPU_WP_SPORT6A_DMA14,    
    D_SYS_SPU_WP_SPORT6B_DMA15,    
    D_SYS_SPU_WP_SPORT7A_DMA16,
    D_SYS_SPU_WP_SPORT7B_DMA17,
    D_SYS_SPU_WP_UART1_TX_DMA34,
    D_SYS_SPU_WP_UART1_RX_DMA35,
    D_SYS_SPU_WP_UART2_TX_DMA37,
    D_SYS_SPU_WP_UART2_RX_DMA38,
    D_SYS_SPU_WP_MDMA0_DDE0_DMA8, 
    D_SYS_SPU_WP_MDMA0_DDE1_DMA9,
    D_SYS_SPU_WP_MDMA1_DDE0_DMA18,
    D_SYS_SPU_WP_MDMA1_DDE1_DMA19,
    D_SYS_SPU_WP_SPI0,
    D_SYS_SPU_WP_SPI1,
    D_SYS_SPU_WP_SPI2
};

uint32_t SYSTEM_SPU_Init(void)
{
	ADI_SPU_RESULT result;
	int aa = 0;

	result = adi_spu_Init(D_SYS_SPU_DEV_ID, saiSpuMemory, NULL, NULL, &shSpu);
	CheckResult(result);

	for(aa = 0; aa < E_SYS_SPU_PID_MAX; aa++) {
		result = adi_spu_EnableMasterSecure(shSpu, saiSpuPidMap[aa], true);
		CheckResult(result);
	}

	return PASSED;
}
