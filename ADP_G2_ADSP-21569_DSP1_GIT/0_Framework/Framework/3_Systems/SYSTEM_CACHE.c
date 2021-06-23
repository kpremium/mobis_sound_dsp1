/*****************************************************************************
Copyright (c) 2016 - Analog Devices Inc. All Rights Reserved.
This software is proprietary & confidential to Analog Devices, Inc.
and its licensors.
******************************************************************************

Title: SigmaStudio for SHARC Application - Cache configuration

Description: Functions in this file configure the I and D cache

*****************************************************************************/

#include "common.h"
#include "SYSTEM_CACHE.h"

/*============================== D E F I N E S ==============================*/

#define NOP15                           \
    do{                                 \
		asm("nop;");					\
		asm("nop;");					\
		asm("nop;");					\
		asm("nop;");					\
		asm("nop;");					\
		asm("nop;");					\
		asm("nop;");					\
		asm("nop;");					\
		asm("nop;");					\
		asm("nop;");					\
		asm("nop;");					\
		asm("nop;");					\
		asm("nop;");					\
		asm("nop;");					\
		asm("nop;");					\
    }while (0) /* do-while-zero needed for Misra Rule 19.4 */

/*================================  D A T A  ================================*/

/*================================= C O D E =================================*/

/*!
   @brief        This function initializes the I and D cache
   @param        None
   @return       None

   <b> Global Variables Used: <b>

  @note            None.
*/
void adi_ss_config_I_D_cache(void)
{
    uint32_t nTemp;

    /* Enable caching and invalidate cache */
    *pREG_SHL1C0_CFG = ENABLE_I_D_CACHE;
    NOP15;

    /* Configure range registers for specifying non cacheable regions */
    *pREG_SHL1C0_CFG2 = 0x000003F0;
    NOP15;

    /* Configure an uncached L2 range in RR2 */
    *pREG_SHL1C0_RANGE_START2 = L2_BW_UNCACHED_START_ADDRESS;
    NOP15;
    *pREG_SHL1C0_RANGE_END2 = L2_BW_UNCACHED_END_ADDRESS;
    NOP15;

    /* Configure an uncached range for SHARC L1 MP addresses in RR3. */
    *pREG_SHL1C0_RANGE_START3 = L1_MP_START_ADDRESS;
    NOP15;
    *pREG_SHL1C0_RANGE_END3 = L1_MP_END_ADDRESS;
    NOP15;

    /* Configure non cache SPI2 memory space */
    *pREG_SHL1C0_RANGE_START4 = SPI2_MEM_UNCACHE_START_ADDRESS;
    NOP15;
    *pREG_SHL1C0_RANGE_END4 = SPI2_MEM_UNCACHE_END_ADDRESS;
    NOP15;

    /* For debugging */
    nTemp = *pREG_SHL1C0_CFG2;
    nTemp = *pREG_SHL1C0_RANGE_START4;
    nTemp = *pREG_SHL1C0_RANGE_END4;
    nTemp = *pREG_SHL1C0_RANGE_START5;
    nTemp = *pREG_SHL1C0_RANGE_END5;
    nTemp = *pREG_SHL1C0_RANGE_START6;
    nTemp = *pREG_SHL1C0_RANGE_END6;
}

/*!
   @brief        This function invalidates D and I cache
   @param        None
   @return       None

   <b> Global Variables Used: <b>

  @note            None.
*/
void adi_ss_invalidate_cache(void)
{
    uint32_t nTemp;

    *pREG_SHL1C0_CFG |= 0x404040;

    /* For debugging */
    nTemp = *pREG_SHL1C0_CFG;
}

/*!
   @brief        This function flushes and invalidates data cache
   @param        None
   @return       None

   <b> Global Variables Used: <b>

  @note            None.
*/
void adi_ss_flush_invalidate_Dcache(void)
{
    uint32_t nTemp;

    *pREG_SHL1C0_CFG |= 0xC0C000;

    /* For debugging */
    nTemp = *pREG_SHL1C0_CFG;
}

int InitCache(void)
{
	adi_ss_config_I_D_cache();

	return PASSED;
}

void ConfigCache(void)
{
	adi_ss_config_I_D_cache();
}

void InvalidateCache(void)
{
	adi_ss_invalidate_cache();
}

void FlushCache(void *sAddr, void *eAddr, int fInv)
{
	flush_data_buffer(sAddr, eAddr, fInv);
}

