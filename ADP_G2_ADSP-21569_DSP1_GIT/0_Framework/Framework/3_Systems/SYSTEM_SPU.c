/*******************************************************************************
Copyright (c) 2019 - Analog Devices Inc. All Rights Reserved.
This software is proprietary & confidential to Analog Devices, Inc.
and its licensors.
******************************************************************************/
#include <stdio.h>

#include <services/spu/adi_spu.h>
#include "common.h"

/* SPU memory */
static uint8_t gSpuMemory[ADI_SPU_MEMORY_SIZE];
/* SPU handle */
static ADI_SPU_HANDLE ghSpu;
/* SPU instance */
#define SPU_ID 0

int SYSTEM_SPU_Init(void)
{
    if(adi_spu_Init(SPU_ID, gSpuMemory, NULL, NULL, &ghSpu) != ADI_SPU_SUCCESS)
    {
        //printf("Failed to initialize SPU service \n");
        return FAILED;
    }
    /* Make SPI2 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_SPI2_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPI2 \n");
    	return FAILED;
    }
    /* Make SPI1 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_SPI1_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPI1 \n");
    	return FAILED;
    }
    /* Make SPI0 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_SPI0_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPI0 \n");
    	return FAILED;
    }
    /* Make LP0 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_LP0_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for LP0 \n");
    	return FAILED;
    }
    /* Make LP0 DMA30 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_DMA30_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for LP0 DMA30 \n");
    	return FAILED;
    }
    /* Make LP1 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_LP1_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for LP1 \n");
    	return FAILED;
    }
    /* Make LP1 DMA36 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_DMA36_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for LP1 DMA36 \n");
    	return FAILED;
    }
    /* Make GPIO Port A to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_PORTA_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for PORTA \n");
    	return FAILED;
    }
    /* Make GPIO Port B to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_PORTB_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for PORTB \n");
    	return FAILED;
    }
    /* Make GPIO Port C to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_PORTC_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for PORTC \n");
    	return FAILED;
    }
    /* Make SPT0A to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_SPORT0A_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT0A \n");
    	return FAILED;
    }
    /* Make SPT0A DMA0 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_DMA0_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT0A DMA0 \n");
    	return FAILED;
    }
    /* Make SPT0B to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_SPORT0B_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT0B \n");
    	return FAILED;
    }
    /* Make SPT0B DMA1 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_DMA1_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT0B DMA1 \n");
    	return FAILED;
    }
    /* Make SPT1A to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_SPORT1A_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT1A \n");
    	return FAILED;
    }
    /* Make SPT1A DMA2 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_DMA2_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT1A DMA2 \n");
    	return FAILED;
    }
    /* Make SPT1B to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_SPORT1B_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT1B \n");
    	return FAILED;
    }
    /* Make SPT1B DMA3 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_DMA3_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT1B DMA3 \n");
    	return FAILED;
    }
    /* Make SPT2A to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_SPORT2A_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT2A \n");
    	return FAILED;
    }
    /* Make SPT2A DMA4 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_DMA4_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT2A DMA4 \n");
    	return FAILED;
    }
    /* Make SPT2B to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_SPORT2B_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT2B \n");
    	return FAILED;
    }
    /* Make SPT2B DMA5 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_DMA5_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT2B DMA5 \n");
    	return FAILED;
    }
    /* Make SPT3A to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_SPORT3A_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT3A \n");
    	return FAILED;
    }
    /* Make SPT3A DMA6 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_DMA6_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT3A DMA6 \n");
    	return FAILED;
    }
    /* Make SPT3B to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_SPORT3B_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT3B \n");
    	return FAILED;
    }
    /* Make SPT3B DMA7 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_DMA7_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT3B DMA7 \n");
    	return FAILED;
    }
    /* Make MDMA0_SRC DMA8 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_DMA8_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for MDMA0_SRC DMA8 \n");
    	return FAILED;
    }
    /* Make MDMA0_DST DMA9 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_DMA9_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for MDMA0_DST DMA9 \n");
    	return FAILED;
    }
    /* Make MDMA1_SRC DMA18 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_DMA18_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for MDMA1_SRC DMA18 \n");
    	return FAILED;
    }
    /* Make MDMA1_DST DMA19 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_DMA19_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for MDMA1_DST DMA19 \n");
    	return FAILED;
    }
    /* Make SPT4A to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_SPORT4A_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT4A \n");
    	return FAILED;
    }
    /* Make SPT4A DMA10 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_DMA10_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT4A DMA10 \n");
    	return FAILED;
    }
    /* Make SPT4B to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_SPORT4B_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT4B \n");
    	return FAILED;
    }
    /* Make SPT4B DMA11 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_DMA11_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT4B DMA11 \n");
    	return FAILED;
    }
    /* Make SPT5A to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_SPORT5A_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT5A \n");
    	return FAILED;
    }
    /* Make SPT5A DMA12 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_DMA12_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT5A DMA12 \n");
    	return FAILED;
    }
    /* Make SPT5B to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_SPORT5B_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT5B \n");
    	return FAILED;
    }
    /* Make SPT5B DMA13 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_DMA13_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT5B DMA13 \n");
    	return FAILED;
    }
    /* Make SPT6A to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_SPORT6A_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT6A \n");
    	return FAILED;
    }
    /* Make SPT6A DMA14 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_DMA14_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT6A DMA14 \n");
    	return FAILED;
    }
    /* Make SPT6B to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_SPORT6B_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT6B \n");
    	return FAILED;
    }
    /* Make SPT6B DMA15 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_DMA15_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT6B DMA15 \n");
    	return FAILED;
    }
    /* Make SPT7A to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_SPORT7A_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT7A \n");
    	return FAILED;
    }
    /* Make SPT7A DMA16 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_DMA16_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT7A DMA16 \n");
    	return FAILED;
    }
    /* Make SPT7B to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_SPORT7B_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT7B \n");
    	return FAILED;
    }
    /* Make SPT7B DMA17 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_DMA17_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for SPORT7B DMA17 \n");
    	return FAILED;
    }
    /* Make UART1Tx DMA34 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_DMA34_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for UART1Tx DMA34 \n");
    	return FAILED;
    }
    /* Make UART1Rx DMA35 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_DMA35_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for UART1Rx DMA35 \n");
    	return FAILED;
    }
    /* Make UART2Tx DMA37 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_DMA37_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for UART2Tx DMA37 \n");
    	return FAILED;
    }
    /* Make UART2Rx DMA38 to generate secure transactions */
    if(adi_spu_EnableMasterSecure(ghSpu, ADI_SPU0_DMA38_ID, true) != ADI_SPU_SUCCESS)
    {
    	//printf("Failed to enable Master secure for UART2Rx DMA38 \n");
    	return FAILED;
    }
    return PASSED;
}

int DoneSPU(void)
{
    return PASSED;
}

