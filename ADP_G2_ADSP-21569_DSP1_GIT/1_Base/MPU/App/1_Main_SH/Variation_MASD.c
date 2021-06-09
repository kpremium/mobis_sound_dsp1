#include <services/int/adi_int.h>
#include <services/int/adi_sec.h>
#include <adi_types.h>
#include "common.h"
#include "MASD.h"
#include "SS4SH.h"
#include "Variation_MASD.h"

// Memory for storing Mips information
#ifdef USE_MEASURE_MIPS
ST_MIPS_INFO oMipsInfoAP_uL =
{
	.fAvgCycles = 0,
	.fAvgMips = 0,
	.fMaxCycles = 0,
	.fMaxMips = 0,
	.fMipsConst = (1.0f / (float32_t)(NUM_ANCASD_SAMPLES) * (float32_t)(SAMPLING_RATE_96) / 1000000.0f),
};

ST_MIPS_INFO oMipsInfoAP_uS =
{
	.fAvgCycles = 0,
	.fAvgMips = 0,
	.fMaxCycles = 0,
	.fMaxMips = 0,
	.fMipsConst = (1.0f / (float32_t)(NUM_A2B_SAMPLES) * (float32_t)(SAMPLING_RATE_48) / 1000000.0f),
};
#endif

volatile uint8_t gbBlockedAP = 0;

/******************************************************************************
    5. Variables
 ******************************************************************************/

/*******************************/
/* 1. Audio Processing Buffer  */
/*******************************/

#pragma align 8
#pragma section("seg_l1_block1")
float32_t fAP_ASD_I_Buf[NUM_IP_CHANNELS_ANCASD][NUM_ANCASD_SAMPLES];

#pragma align 8
#pragma section("seg_l1_block1")
float32_t fAP_ASD_O_Buf[NUM_OP_CHANNELS_ANCASD][NUM_ANCASD_SAMPLES];

#pragma align 8
#pragma section("seg_l1_block1")
float32_t fAP_AMP_I_Buf[NUM_IP_CHANNELS_A2B][NUM_A2B_SAMPLES];

#pragma align 8
#pragma section("seg_l1_block1")
float32_t fAP_AMP_O_Buf[NUM_OP_CHANNELS_A2B][NUM_A2B_SAMPLES];

#pragma align 8
#pragma section("seg_l1_block1")
float32_t fAP_ACC_I_Buf[NUM_IP_CHANNELS_ACC1][NUM_A2B_SAMPLES];

#pragma align 8
#pragma section("seg_l1_block1")
float32_t fAP_MIC_I_Buf[NUM_IP_CHANNELS_PMIC][NUM_A2B_SAMPLES];

#pragma align 8
#pragma section("seg_l1_block1")
float32_t fAP_IPC_I_Buf[NUM_IP_CHANNELS_DSP][NUM_A2B_SAMPLES];

#pragma align 8
#pragma section("seg_l1_block1")
float32_t fAP_IPC_O_Buf[NUM_OP_CHANNELS_DSP][NUM_A2B_SAMPLES];

#pragma align 8
#pragma section("seg_l1_block1")
float32_t fAP_VESSO_Buf[NUM_OP_CHANNELS_VESS][NUM_A2B_SAMPLES];

#pragma align 8
#pragma section("seg_l1_block1")
float32_t fAP_CAMPI_Buf[NUM_IP_CHANNELS_CAMPING][NUM_A2B_SAMPLES];

#pragma align 8
#pragma section("seg_l1_block1")
float32_t fAP_CAMPO_Buf[NUM_OP_CHANNELS_CAMPING][NUM_A2B_SAMPLES];


/*******************************/
/* 2. PDMA Buffer              */
/*******************************/

#pragma align 8
#pragma section("seg_l1_block1")
uint32_t sPDMA_AMP__I_Buf[NUM_IN_OUT_BLOCKS][NUM_IP_CHANNELS_A2B][NUM_A2B_SAMPLES];

#pragma align 8
#pragma section("seg_l1_block1")
uint32_t sPDMA_AMP__O_Buf[NUM_IN_OUT_BLOCKS][NUM_OP_CHANNELS_A2B][NUM_A2B_SAMPLES];

#pragma align 8
#pragma section("seg_l1_block1")
uint32_t sPDMA_ACC1_I_Buf[NUM_IN_OUT_BLOCKS][NUM_IP_CHANNELS_ACC1][NUM_A2B_SAMPLES];

#pragma align 8
#pragma section("seg_l1_block1")
uint32_t sPDMA_PMIC_I_Buf[NUM_IN_OUT_BLOCKS][NUM_IP_CHANNELS_PMIC][NUM_A2B_SAMPLES];

#pragma align 8
#pragma section("seg_l1_block1")
uint32_t sPDMA_IPC__I_Buf[NUM_IN_OUT_BLOCKS][NUM_IP_CHANNELS_DSP][NUM_A2B_SAMPLES];

#pragma align 8
#pragma section("seg_l1_block1")
uint32_t sPDMA_IPC__O_Buf[NUM_IN_OUT_BLOCKS][NUM_OP_CHANNELS_DSP][NUM_A2B_SAMPLES];

#pragma align 8
#pragma section("seg_l1_block1")
uint32_t sPDMA_VESS_O_Buf[NUM_IN_OUT_BLOCKS][NUM_OP_CHANNELS_VESS][NUM_A2B_SAMPLES];

#pragma align 8
#pragma section("seg_l1_block1")
uint32_t sPDMA_CAMP_I_Buf[NUM_IN_OUT_BLOCKS][NUM_IP_CHANNELS_CAMPING][NUM_A2B_SAMPLES];

#pragma align 8
#pragma section("seg_l1_block1")
uint32_t sPDMA_CAMP_O_Buf[NUM_IN_OUT_BLOCKS][NUM_OP_CHANNELS_CAMPING][NUM_A2B_SAMPLES];



volatile int32_t Pipo_I_ANCASD			= 1;
volatile int32_t Pipo_O_ANCASD			= 1;
volatile int32_t Pipo_I_AMP				= 1;
volatile int32_t Pipo_O_AMP				= 1;
volatile int32_t Pipo_I_ACC1			= 1;
volatile int32_t Pipo_I_PMIC			= 1;
volatile int32_t Pipo_I_DSP				= 1;
volatile int32_t Pipo_O_DSP				= 1;
volatile int32_t Pipo_O_VESS			= 1;
volatile int32_t Pipo_I_CAMPING			= 1;
volatile int32_t Pipo_O_CAMPING			= 1;



uint32_t MAIN_AudioProcessingInit(void)
{
#ifdef USE_MEASURE_MIPS
	CYCLES_RESET(oMipsInfoAP_uL.oCycleStats);
	CYCLES_INIT(oMipsInfoAP_uL.oCycleStats);

	CYCLES_RESET(oMipsInfoAP_uS.oCycleStats);
	CYCLES_INIT(oMipsInfoAP_uS.oCycleStats);
#endif

#if defined(USE_MASD)
	InitMASD();
#endif

#if defined(USE_SS4SH)
	InitSS4SH();
#endif

  return PASSED;
}

void DoneAudioProcessing(void)
{

#if defined(USE_MASD)
	DoneMASD();
#endif

#if defined(USE_SS4SH)
	DoneSS4SH();
#endif
}

void ExecAudioProcessing(void)
{

#if defined(USE_MASD)
	ExecMASD();
#endif

#if defined(USE_SS4SH)
	ExecSS4SH();
#endif
}

void MAIN_AudioProcessing_uL(unsigned int id, void* arg)
{
	int32_t iSample, iChannel;

#if (EZ_KIT_BOARD == 1u)
	SetGPIO_PB03();
#endif

#ifdef USE_MEASURE_MIPS
	CYCLES_START(oMipsInfoAP_uL.oCycleStats);
#endif

	ReadInputDataFromAMP();
	//ReadInputDataFromDSP();
	ReadInputDataFromACC1();
	ReadInputDataFromPMIC();

	// Add a custom code & algorithm
#if defined(USE_MASD)
	ProcMASD();
#endif

#if defined(USE_SS4SH)
//	if(!IsBlockedAudioProcessing())
//	{
		ProcSS4SH_SSn1();
//	}
#else
	ProcSPORT_uL();
#endif

#if (USE_DSP_CFG == 0u)
	WriteOutputDataToAMP();
#elif (USE_DSP_CFG == 1u)
	WriteOutputDataToDSP();
#endif
	WriteOutputDataToASRC();

#ifdef USE_MEASURE_MIPS
	CYCLES_STOP(oMipsInfoAP_uL.oCycleStats);
	oMipsInfoAP_uL.fAvgCycles = oMipsInfoAP_uL.oCycleStats._total_cycles/oMipsInfoAP_uL.oCycleStats._num_calls;
	oMipsInfoAP_uL.fMaxCycles = oMipsInfoAP_uL.oCycleStats._max_cycles;
	oMipsInfoAP_uL.fAvgMips = oMipsInfoAP_uL.fAvgCycles*oMipsInfoAP_uL.fMipsConst;
	oMipsInfoAP_uL.fMaxMips = oMipsInfoAP_uL.fMaxCycles*oMipsInfoAP_uL.fMipsConst;
	if(oMipsInfoAP_uL.oCycleStats._num_calls >= 1500)
	{
		CYCLES_RESET(oMipsInfoAP_uL.oCycleStats);
	}
#endif

#if (EZ_KIT_BOARD == 1u)
	ClrGPIO_PB03();
#endif
}

void MAIN_AudioProcessing_uS(unsigned int id, void* arg)
{
	int32_t iSample, iChannel;

#if (EZ_KIT_BOARD == 1u)
	SetGPIO_PB04();
#endif

#ifdef USE_MEASURE_MIPS
	CYCLES_START(oMipsInfoAP_uS.oCycleStats);
#endif

	ReadInputDataFromASRC();

#if defined(USE_SS4SH)
	if(!IsBlockedAudioProcessing())
	{
		ProcSS4SH_SSn2();
	}
#else
	ProcSPORT_uS();
#endif

	WriteOutputDataToVESS();

#ifdef USE_MEASURE_MIPS
	CYCLES_STOP(oMipsInfoAP_uS.oCycleStats);
	oMipsInfoAP_uS.fAvgCycles = oMipsInfoAP_uS.oCycleStats._total_cycles/oMipsInfoAP_uS.oCycleStats._num_calls;
	oMipsInfoAP_uS.fMaxCycles = oMipsInfoAP_uS.oCycleStats._max_cycles;
	oMipsInfoAP_uS.fAvgMips = oMipsInfoAP_uS.fAvgCycles*oMipsInfoAP_uS.fMipsConst;
	oMipsInfoAP_uS.fMaxMips = oMipsInfoAP_uS.fMaxCycles*oMipsInfoAP_uS.fMipsConst;
	if(oMipsInfoAP_uS.oCycleStats._num_calls >= 1500)
	{
		CYCLES_RESET(oMipsInfoAP_uS.oCycleStats);
	}
#endif

#if (EZ_KIT_BOARD == 1u)
	ClrGPIO_PB04();
#endif
}

uint8_t IsBlockedAudioProcessing(void)
{
	return gbBlockedAP;
}

void ChangeModeAudioProcessing(uint8_t bBlocked)
{
	gbBlockedAP = bBlocked;
}

#pragma optimize_for_speed

void ProcSPORT_uL(void)
{
	int32_t iChannel = 0;
	int32_t iSample = 0;

#ifndef USE_SS4SH
	for(iChannel =0; iChannel <NUM_IP_CHANNELS_A2B;iChannel++)
	{
		for(iSample =0; iSample <NUM_A2B_SAMPLES; iSample++)
		{
#if (USE_DSP_CFG == 0u)
			fAP_AMP_O_Buf[iChannel][iSample] = fAP_AMP_I_Buf[iChannel][iSample];
#elif (USE_DSP_CFG == 1u)
			fAP_IPC_O_Buf[iChannel][iSample] = fAP_AMP_I_Buf[iChannel][iSample];
#endif
		}
	}
#endif
}

void ProcSPORT_uS(void)
{
	int32_t iChannel = 0;
	int32_t iSample = 0;

#ifndef USE_SS4SH

	for(iChannel =0; iChannel <NUM_OP_CHANNELS_VESS;iChannel++)
	{
		for(iSample =0; iSample <NUM_A2B_SAMPLES; iSample++)
		{
			fAP_VESSO_Buf[iChannel][iSample] = fAP_CAMPI_Buf[iChannel][iSample];
		}
	}

#endif
}

// input(from AMP A2B#1), SPORT0A
void ReadInputDataFromAMP(void)
{
	int32_t iChannel = 0;
	int32_t iSample = 0;

	if ( (uint32_t)((uint32_t)*pREG_DMA0_ADDR_CUR) >= internal_to_system_address_translation((uint32_t)&sPDMA_AMP__I_Buf[1][0][0]))
		Pipo_I_AMP = 0;
	else
		Pipo_I_AMP = 1;

	for(iChannel=0; iChannel<NUM_IP_CHANNELS_A2B; iChannel++)
	{
		CopyFix2Float(&sPDMA_AMP__I_Buf[Pipo_I_AMP][iChannel][0], \
						&fAP_AMP_I_Buf[iChannel][0], NUM_A2B_SAMPLES, 0);
	}
}

// output(to AMP A2B#1), SPORT0B
void WriteOutputDataToAMP(void)
{
	int32_t iChannel = 0;
	int32_t iSample = 0;

	if ( (uint32_t)((uint32_t)*pREG_DMA1_ADDR_CUR) >= internal_to_system_address_translation((uint32_t)&sPDMA_AMP__O_Buf[1][0][0]) )
		Pipo_O_AMP = 0;
	else
		Pipo_O_AMP = 1;

	for(iChannel=0; iChannel<NUM_OP_CHANNELS_A2B; iChannel++)
	{
		CopyFloat2Fix(&fAP_AMP_O_Buf[iChannel][0], \
						&sPDMA_AMP__O_Buf[Pipo_O_AMP][iChannel][0], NUM_A2B_SAMPLES, 0);
	}
}

// Input(from DSP2), SPORT4B Primary& Secondary
void ReadInputDataFromDSP(void)
{
	int32_t iChannel = 0;
	int32_t iSample = 0;

	if ( (uint32_t)((uint32_t)*pREG_DMA11_ADDR_CUR) >= internal_to_system_address_translation((uint32_t)&sPDMA_IPC__I_Buf[1][0][0]) )
		Pipo_I_DSP = 0;
	else
		Pipo_I_DSP = 1;

	for(iChannel=0; iChannel<NUM_IP_CHANNELS_DSP; iChannel++)
	{
		CopyFix2Float(&sPDMA_IPC__I_Buf[Pipo_I_DSP][iChannel][0], \
						&fAP_IPC_I_Buf[iChannel][0], NUM_A2B_SAMPLES, 0);
	}
}

// Output(to DSP2), SPORT4A Primary& Secondary
void WriteOutputDataToDSP(void)
{
	int32_t iChannel = 0;
	int32_t iSample = 0;

	if ( (uint32_t)((uint32_t)*pREG_DMA10_ADDR_CUR) >= internal_to_system_address_translation((uint32_t)&sPDMA_IPC__O_Buf[1][0][0]) )
		Pipo_O_DSP = 0;
	else
		Pipo_O_DSP = 1;

	for(iChannel=0; iChannel<NUM_OP_CHANNELS_DSP; iChannel++)
	{
		CopyFloat2Fix(&fAP_IPC_O_Buf[iChannel][0], \
						&sPDMA_IPC__O_Buf[Pipo_O_DSP][iChannel][0], NUM_A2B_SAMPLES, 0);
	}
}

// Input(from Sensors A2B#3), SPORT2A/B(XL)
void ReadInputDataFromACC1(void)
{
	int32_t iChannel = 0;
	int32_t iSample = 0;

	if ( (uint32_t)((uint32_t)*pREG_DMA4_ADDR_CUR) >= internal_to_system_address_translation((uint32_t)&sPDMA_ACC1_I_Buf[1][0][0]) )
		Pipo_I_ACC1 = 0;
	else
		Pipo_I_ACC1 = 1;

	for(iChannel=0; iChannel<NUM_IP_CHANNELS_ACC1; iChannel++)
	{
		CopyFix2Float(&sPDMA_ACC1_I_Buf[Pipo_I_ACC1][iChannel][0], \
						&fAP_ACC_I_Buf[iChannel][0], NUM_A2B_SAMPLES, 0);
	}
}

// Input(from Sensors A2B#4), SPORT3A(PMIC)
void ReadInputDataFromPMIC(void)
{
	int32_t iChannel = 0;
	int32_t iSample = 0;

	if ( (uint32_t)((uint32_t)*pREG_DMA6_ADDR_CUR) >= internal_to_system_address_translation((uint32_t)&sPDMA_PMIC_I_Buf[1][0][0]) )
		Pipo_I_PMIC = 0;
	else
		Pipo_I_PMIC = 1;

	for(iChannel=0; iChannel<NUM_IP_CHANNELS_PMIC; iChannel++)
	{
		CopyFix2Float(&sPDMA_PMIC_I_Buf[Pipo_I_PMIC][iChannel][0], \
						&fAP_MIC_I_Buf[iChannel][0], NUM_A2B_SAMPLES, 0);
	}
}

// Output(To ASRC), SPORT6B
void WriteOutputDataToASRC(void)
{
	int32_t iChannel = 0;
	int32_t iSample = 0;

	if ( (uint32_t)((uint32_t)*pREG_DMA15_ADDR_CUR ) >= internal_to_system_address_translation((uint32_t)&sPDMA_CAMP_O_Buf[1][0][0]) )
		Pipo_O_CAMPING = 0;
	else
		Pipo_O_CAMPING = 1;

	for(iChannel=0; iChannel<NUM_OP_CHANNELS_CAMPING; iChannel++)
	{
		CopyFloat2Fix(&fAP_CAMPO_Buf[iChannel][0], \
						&sPDMA_CAMP_O_Buf[Pipo_O_CAMPING][iChannel][0], NUM_A2B_SAMPLES, 0);
	}
}

// Input(from ASRC), SPORT7B
void ReadInputDataFromASRC(void)
{
	int32_t iChannel = 0;
	int32_t iSample = 0;

	if ( (uint32_t)((uint32_t)*pREG_DMA17_ADDR_CUR) >= internal_to_system_address_translation((uint32_t)&sPDMA_CAMP_I_Buf[1][0][0]) )
		Pipo_I_CAMPING = 0;
	else
		Pipo_I_CAMPING = 1;

	for(iChannel=0; iChannel<NUM_IP_CHANNELS_CAMPING; iChannel++)
	{
		CopyFix2Float(&sPDMA_CAMP_I_Buf[Pipo_I_CAMPING][iChannel][0], \
						&fAP_CAMPI_Buf[iChannel][0], NUM_A2B_SAMPLES, 0);
	}
}

// Output(To Power IC), SPORT7A
void WriteOutputDataToVESS(void)
{
	int32_t iChannel = 0;
	int32_t iSample = 0;

	if ( (uint32_t)((uint32_t)*pREG_DMA16_ADDR_CUR) >= internal_to_system_address_translation((uint32_t)&sPDMA_VESS_O_Buf[1][0][0]) )
		Pipo_O_VESS = 0;
	else
		Pipo_O_VESS = 1;

	for(iChannel=0; iChannel<NUM_OP_CHANNELS_VESS; iChannel++)
	{
		CopyFloat2Fix(&fAP_VESSO_Buf[iChannel][0], \
						&sPDMA_VESS_O_Buf[Pipo_O_VESS][iChannel][0], NUM_A2B_SAMPLES, 0);
	}
}


