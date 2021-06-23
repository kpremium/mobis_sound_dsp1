#ifndef __COMMON_H__
#define __COMMON_H__

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include <interrupt.h>
#include <services/pwr/adi_pwr.h>
#include <services/spu/adi_spu.h>
#include <services/int/adi_int.h>
#include <services/int/adi_sec.h>
#include <sys/platform.h>
#include <sys/cache.h>
#include <sru21569.h>
#define DO_CYCLE_COUNTS
#include <cycles.h>

#include "adi_initialize.h"

#define FAILED		1
#define PASSED		0

#define FRAMEWORK_VERSION   0x01220101

/* for MOBIS ASD */
#define USE_MASD

/* for SS4SH */
#define USE_SS4SH

#ifdef USE_SS4SH
#define LOAD_SS4SH_FROM_FLASH
#endif

/* for Memory Mapped SPI mode */
#define USE_SPI2_MM_FLASH

#define USE_MEASURE_MIPS

#define EZ_KIT_BOARD	(0u)
#define TARGET_BOARD	(1u)
#define USE_DSP_CFG		(1u)	// Output to AMP: 0, Output to DSP2: 1

typedef struct _ST_MIPS_INFO
{
    cycle_stats_t oCycleStats;
    float fMipsConst;
    float fAvgCycles;
    float fMaxCycles;
    float fAvgMips;
    float fMaxMips;
}ST_MIPS_INFO;

typedef struct ASRCInfo_tag
{
	uint8_t  AsrcIdx;
	uint8_t  IsUsed;
	uint8_t  PeriId;
	uint8_t  AutoMute;
	uint8_t  IFormat;
	uint8_t  OFormat;
	uint8_t  WordLen;
	uint8_t  MuteOut;
}ASRCInfo_t; // 8 bytes

typedef enum DriverIndex_tag
{
	Driver_INTERRUPT,
	Driver_PDMA,
	Driver_SPORT,
	Driver_ASRC,
	Driver_SPDIF,
	Driver_PCG,
	Driver_MAX
}DriverIndex_t;

/* adi_ss_fw_utility.asm */
void CopyFix2Float(volatile uint32_t *pInBuffer, volatile float32_t *pOutBuffer, uint32_t nBlockSize, uint32_t nShiftFlag);
uint32_t CopyFloat2Fix(volatile float32_t *pInBuffer, volatile uint32_t *pOutBuffer, uint32_t nBlockSize, uint32_t nShiftFlag);
int32_t IsNanInf(float32_t *pStateBuf, uint32_t nBufLen);

/* utility.c */
uint32_t internal_to_system_address_translation(uint32_t nMemAddr);
uint32_t system_to_internal_address_translation(uint32_t nMemAddr);

#endif /* __COMMON_H__ */
