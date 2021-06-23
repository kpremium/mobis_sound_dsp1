#include "common.h"
#include "DRV_FLASH.h"
#include "Variation_MASD.h"

extern float32_t fAP_AMP_I_Buf[AP_AMP_I_CH][AP_A2B_BLKSIZ];
extern float32_t fAP_AMP_O_Buf[AP_AMP_O_CH][AP_A2B_BLKSIZ];
extern float32_t fAP_CAMPO_Buf[AP_CAM_O_CH][AP_A2B_BLKSIZ];
extern float32_t fAP_CAMPI_Buf[AP_CAM_I_CH][AP_A2B_BLKSIZ];
extern float32_t fAP_VESSO_Buf[AP_VES_O_CH][AP_A2B_BLKSIZ];
extern float32_t fAP_IPC_O_Buf[AP_IPC_O_CH][AP_A2B_BLKSIZ];

#if defined(USE_SS4SH)

////////////////////////////////////////////////////////////////////////////////////////////////////
// I N C L U D E S
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "adi_ss_smap.h"

/* Defining Backchannel info structure. Will be populated by the framework */
typedef struct ADI_SS_BACKCH_INFO
{
    float32_t   fPeakMIPS[ADI_SS_FW_MAX_PROC_BLOCKS];   /*!< Peak MIPS for all process blocks */
    float32_t   fAvgMIPS[ADI_SS_FW_MAX_PROC_BLOCKS];    /*!< Average MIPS for all process blocks */
    uint32_t    nVersionInfo;                           /*!< Target library API version */
    uint32_t    nSSnDownloadStatus;                     /*!< Current download status of SSn within all process blocks */
}ADI_SS_BACKCH_INFO;

#include "adi_ss_connection.h"
#include "adi_ss_communication.h"
#include "adi_ss_ssn.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// D E F I N E S
////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined(LOAD_SS4SH_FROM_FLASH)
/* The address below should be the same as the contents in the batch file that performs the mergy tool. */
//========== SHARC Code & Parameter Flash Address Memory Map ==========//
#define	pFlashAddrSSn1						0x00040000		// for SSn1 TxMetaBuffer
#define	pFlashAddrSSn2						0x00060000		// for SSn2 TxMetaBuffer
#define	pFlashAddrSSn3						0x00080000		// for SSn3 TxMetaBuffer
//=====================================================================//
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
// M A C R O
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// E N U M E R A T I O N S
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// S T R U C T U R E S
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// V A R I A B L E S
////////////////////////////////////////////////////////////////////////////////////////////////////

/* Memory for SigmaStudio for Griffin libraries */
/* Connection Instance Memories */
#pragma align(4)
#pragma section("ss_app_data0_fast")
uint8_t adi_ss_connection_mem[ADI_SS_CONNECTION_MEMSIZE];

/* Connenction Component Handle */
ADI_SS_CONNECTION_HANDLE hConnHandle = 0;

/* Communication Instance Memories */
#pragma align(4)
#pragma section("ss_app_data0_fast")
uint8_t adi_ss_comm_mem[ADI_SS_COMM_MEMSIZE];

/* Communication Component Handle */
ADI_SS_COMM_HANDLE hCommHandle = 0;

/* SMAP */
#pragma align(4)
#pragma section("seg_l2_noinit_data", NO_INIT)
ADI_SS_MEM_SMAP oMemSMap;

/* Wait for SMAP to be received */
volatile uint32_t fReceivedSMap = 0;

/* Backchannel info */
ADI_SS_BACKCH_INFO oBkChnlInfo;

/*============= For 1st SSn '1' =============*/
// Elements for SigmaStudio instance for SSn 1
ADI_SS_RESULT eSSn1Res;
ADI_SS_SSN_HANDLE hSSn1Handle;
ADI_SS_SSNPROPERTIES oSSn1Properties;
#if defined(LOAD_SS4SH_FROM_FLASH)
uint8_t *pSSn1CodeMem = NULL, *pSSn1ParamMem = NULL;
#endif

// IO buffers which is connected with SSn '1'
#pragma align 8
#pragma section("seg_l1_block1")
float32_t fBlock_IP_SSn1[NUM_SSn1_BLOCK_SAMPLES]; // Zero-based buffer to save memory for SSn1 input
#pragma align 8
#pragma section("seg_l1_block1")
float32_t fBlock_OP_SSn1[NUM_SSn1_BLOCK_SAMPLES]; // Zero-based buffer to save memory for SSn1 output

/* I/O buffer and pointers for SSn '1' instance */
float32_t *ip_data_SSn1[AP_SSN1_I_CH];
float32_t *op_data_SSn1[AP_SSN1_O_CH];

/*============= For 2nd SSn '2' =============*/
// Elements for SigmaStudio instance for SSn 2
ADI_SS_RESULT eSSn2Res;
ADI_SS_SSN_HANDLE hSSn2Handle;
ADI_SS_SSNPROPERTIES oSSn2Properties;
#if defined(LOAD_SS4SH_FROM_FLASH)
uint8_t *pSSn2CodeMem = NULL, *pSSn2ParamMem = NULL;
#endif

// IO buffers which is connected with SSn '2'
#pragma align 8
#pragma section("seg_l1_block1")
float32_t fBlock_IP_SSn2[NUM_SSn2_BLOCK_SAMPLES]; // Zero-based buffer to save memory for SSn2 input
#pragma align 8
#pragma section("seg_l1_block1")
float32_t fBlock_OP_SSn2[NUM_SSn2_BLOCK_SAMPLES]; // Zero-based buffer to save memory for SSn2 output

/* I/O buffer and pointers for SSn '2' instance */
float32_t *ip_data_SSn2[AP_SSN2_I_CH];
float32_t *op_data_SSn2[AP_SSN2_O_CH];

// Memory for storing Mips information
#ifdef USE_MEASURE_MIPS_SSN
ST_MIPS_INFO oMipsInfoSSn1 =
{
	.fAvgCycles = 0,
	.fAvgMips = 0,
	.fMaxCycles = 0,
	.fMaxMips = 0,
	.fMipsConst = (1.0f / (float32_t)(AP_IPC_BLKSIZ) * (float32_t)(SAMPLING_RATE_96) / 1000000.0f),
};

ST_MIPS_INFO oMipsInfoSSn2 =
{
	.fAvgCycles = 0,
	.fAvgMips = 0,
	.fMaxCycles = 0,
	.fMaxMips = 0,
	.fMipsConst = (1.0f / (float32_t)(AP_A2B_BLKSIZ) * (float32_t)(SAMPLING_RATE_48) / 1000000.0f),
};
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
// F U N C T I O N S (P R O T O T Y P E)
////////////////////////////////////////////////////////////////////////////////////////////////////

void adi_ss_comm_callback_cmd4(uint32_t *pCommPayloadBuff, int32_t nPayloadCount, ADI_SS_SSN_HANDLE hSSn);
void adi_ss_comm_callback_smap(ADI_SS_PROC_ID eCoreID);

////////////////////////////////////////////////////////////////////////////////////////////////////
// F U N C T I O N S (C O D E)
////////////////////////////////////////////////////////////////////////////////////////////////////

void adi_ss_comm_callback_cmd4(uint32_t *pCommPayloadBuff, int32_t nPayloadCount, ADI_SS_SSN_HANDLE hSSn)
{
	while(1)
	{
		asm volatile("	nop;	");
	}
}

void adi_ss_comm_callback_smap(ADI_SS_PROC_ID eCoreID)
{
	if(eCoreID==PROCESSOR_SH0)
	{
		fReceivedSMap = 1;
		/* If SS4G Schematic uses L2 or L3 memory, below code should be alive */
		//InvalidateCache();
	}
}

static volatile int32_t aRegStorageSSn1[5][16];

static void pushRegsDAG_SSn1(void)
{
	asm volatile("%0 = m0;":  "=d"(aRegStorageSSn1[1][0]) : :);
	asm volatile("%0 = m1;":  "=d"(aRegStorageSSn1[1][1]) : :);
	asm volatile("%0 = m2;":  "=d"(aRegStorageSSn1[1][2]) : :);
	asm volatile("%0 = m3;":  "=d"(aRegStorageSSn1[1][3]) : :);
	asm volatile("%0 = m4;":  "=d"(aRegStorageSSn1[1][4]) : :);
	asm volatile("%0 = m5;":  "=d"(aRegStorageSSn1[1][5]) : :);
	asm volatile("%0 = m6;":  "=d"(aRegStorageSSn1[1][6]) : :);
	asm volatile("%0 = m7;":  "=d"(aRegStorageSSn1[1][7]) : :);
	asm volatile("%0 = m8;":  "=d"(aRegStorageSSn1[1][8]) : :);
	asm volatile("%0 = m9;":  "=d"(aRegStorageSSn1[1][9]) : :);
	asm volatile("%0 = m10;":  "=d"(aRegStorageSSn1[1][10]) : :);
	asm volatile("%0 = m11;":  "=d"(aRegStorageSSn1[1][11]) : :);
	asm volatile("%0 = m12;":  "=d"(aRegStorageSSn1[1][12]) : :);
	asm volatile("%0 = m13;":  "=d"(aRegStorageSSn1[1][13]) : :);
	asm volatile("%0 = m14;":  "=d"(aRegStorageSSn1[1][14]) : :);
	asm volatile("%0 = m15;":  "=d"(aRegStorageSSn1[1][15]) : :);

	asm volatile("%0 = b0;":  "=d"(aRegStorageSSn1[2][0]) : :);
	asm volatile("%0 = b1;":  "=d"(aRegStorageSSn1[2][1]) : :);
	asm volatile("%0 = b2;":  "=d"(aRegStorageSSn1[2][2]) : :);
	asm volatile("%0 = b3;":  "=d"(aRegStorageSSn1[2][3]) : :);
	asm volatile("%0 = b4;":  "=d"(aRegStorageSSn1[2][4]) : :);
	asm volatile("%0 = b5;":  "=d"(aRegStorageSSn1[2][5]) : :);
	/*
	asm volatile("%0 = b6;":  "=d"(aRegStorageSSn1[2][6]) : :);
	asm volatile("%0 = b7;":  "=d"(aRegStorageSSn1[2][7]) : :);
	*/
	asm volatile("%0 = b8;":  "=d"(aRegStorageSSn1[2][8]) : :);
	asm volatile("%0 = b9;":  "=d"(aRegStorageSSn1[2][9]) : :);
	asm volatile("%0 = b10;":  "=d"(aRegStorageSSn1[2][10]) : :);
	asm volatile("%0 = b11;":  "=d"(aRegStorageSSn1[2][11]) : :);
	asm volatile("%0 = b12;":  "=d"(aRegStorageSSn1[2][12]) : :);
	asm volatile("%0 = b13;":  "=d"(aRegStorageSSn1[2][13]) : :);
	asm volatile("%0 = b14;":  "=d"(aRegStorageSSn1[2][14]) : :);
	asm volatile("%0 = b15;":  "=d"(aRegStorageSSn1[2][15]) : :);

	asm volatile("%0 = l0;":  "=d"(aRegStorageSSn1[3][0]) : :);
	asm volatile("%0 = l1;":  "=d"(aRegStorageSSn1[3][1]) : :);
	asm volatile("%0 = l2;":  "=d"(aRegStorageSSn1[3][2]) : :);
	asm volatile("%0 = l3;":  "=d"(aRegStorageSSn1[3][3]) : :);
	asm volatile("%0 = l4;":  "=d"(aRegStorageSSn1[3][4]) : :);
	asm volatile("%0 = l5;":  "=d"(aRegStorageSSn1[3][5]) : :);
	/*
	asm volatile("%0 = l6;":  "=d"(aRegStorageSSn1[3][6]) : :);
	asm volatile("%0 = l7;":  "=d"(aRegStorageSSn1[3][7]) : :);
	*/
	asm volatile("%0 = l8;":  "=d"(aRegStorageSSn1[3][8]) : :);
	asm volatile("%0 = l9;":  "=d"(aRegStorageSSn1[3][9]) : :);
	asm volatile("%0 = l10;":  "=d"(aRegStorageSSn1[3][10]) : :);
	asm volatile("%0 = l11;":  "=d"(aRegStorageSSn1[3][11]) : :);
	asm volatile("%0 = l12;":  "=d"(aRegStorageSSn1[3][12]) : :);
	asm volatile("%0 = l13;":  "=d"(aRegStorageSSn1[3][13]) : :);
	asm volatile("%0 = l14;":  "=d"(aRegStorageSSn1[3][14]) : :);
	asm volatile("%0 = l15;":  "=d"(aRegStorageSSn1[3][15]) : :);

	/*  Clear L registers */
	asm volatile("l0 = 0;");
	asm volatile("l1 = 0;");
	asm volatile("l2 = 0;");
	asm volatile("l3 = 0;");
	asm volatile("l4 = 0;");
	asm volatile("l5 = 0;");
	asm volatile("l8 = 0;");
	asm volatile("l9 = 0;");
	asm volatile("l10 = 0;");
	asm volatile("l11 = 0;");
	asm volatile("l12 = 0;");
	asm volatile("l13 = 0;");
	asm volatile("l14 = 0;");
	asm volatile("l15 = 0;");

	asm volatile("%0 = i0;":  "=d"(aRegStorageSSn1[0][0]) : :);
	asm volatile("%0 = i1;":  "=d"(aRegStorageSSn1[0][1]) : :);
	asm volatile("%0 = i2;":  "=d"(aRegStorageSSn1[0][2]) : :);
	asm volatile("%0 = i3;":  "=d"(aRegStorageSSn1[0][3]) : :);
	asm volatile("%0 = i4;":  "=d"(aRegStorageSSn1[0][4]) : :);
	asm volatile("%0 = i5;":  "=d"(aRegStorageSSn1[0][5]) : :);
	/*
	asm volatile("%0 = i6;":  "=d"(aRegStorageSSn1[0][6]) : :);
	asm volatile("%0 = i7;":  "=d"(aRegStorageSSn1[0][7]) : :);
	*/
	asm volatile("%0 = i8;":  "=d"(aRegStorageSSn1[0][8]) : :);
	asm volatile("%0 = i9;":  "=d"(aRegStorageSSn1[0][9]) : :);
	asm volatile("%0 = i10;":  "=d"(aRegStorageSSn1[0][10]) : :);
	asm volatile("%0 = i11;":  "=d"(aRegStorageSSn1[0][11]) : :);
	asm volatile("%0 = i12;":  "=d"(aRegStorageSSn1[0][12]) : :);
	asm volatile("%0 = i13;":  "=d"(aRegStorageSSn1[0][13]) : :);
	asm volatile("%0 = i14;":  "=d"(aRegStorageSSn1[0][14]) : :);
	asm volatile("%0 = i15;":  "=d"(aRegStorageSSn1[0][15]) : :);
}

static void popRegsDAG_SSn1(void)
{
	asm volatile("m0 = %0;":   :"d"(aRegStorageSSn1[1][0]):);
	asm volatile("m1 = %0;":   :"d"(aRegStorageSSn1[1][1]):);
	asm volatile("m2 = %0;":   :"d"(aRegStorageSSn1[1][2]):);
	asm volatile("m3 = %0;":   :"d"(aRegStorageSSn1[1][3]):);
	asm volatile("m4 = %0;":   :"d"(aRegStorageSSn1[1][4]):);
	asm volatile("m5 = %0;":   :"d"(aRegStorageSSn1[1][5]):);
	asm volatile("m6 = %0;":   :"d"(aRegStorageSSn1[1][6]):);
	asm volatile("m7 = %0;":   :"d"(aRegStorageSSn1[1][7]):);
	asm volatile("m8 = %0;":   :"d"(aRegStorageSSn1[1][8]):);
	asm volatile("m9 = %0;":   :"d"(aRegStorageSSn1[1][9]):);
	asm volatile("m10 = %0;":   :"d"(aRegStorageSSn1[1][10]):);
	asm volatile("m11 = %0;":   :"d"(aRegStorageSSn1[1][11]):);
	asm volatile("m12 = %0;":   :"d"(aRegStorageSSn1[1][12]):);
	asm volatile("m13 = %0;":   :"d"(aRegStorageSSn1[1][13]):);
	asm volatile("m14 = %0;":   :"d"(aRegStorageSSn1[1][14]):);
	asm volatile("m15 = %0;":   :"d"(aRegStorageSSn1[1][15]):);

	asm volatile("b0 = %0;":   :"d"(aRegStorageSSn1[2][0]):);
	asm volatile("b1 = %0;":   :"d"(aRegStorageSSn1[2][1]):);
	asm volatile("b2 = %0;":   :"d"(aRegStorageSSn1[2][2]):);
	asm volatile("b3 = %0;":   :"d"(aRegStorageSSn1[2][3]):);
	asm volatile("b4 = %0;":   :"d"(aRegStorageSSn1[2][4]):);
	asm volatile("b5 = %0;":   :"d"(aRegStorageSSn1[2][5]):);
	/*
	asm volatile("b6 = %0;":   :"d"(aRegStorageSSn1[2][6]):);
	asm volatile("b7 = %0;":   :"d"(aRegStorageSSn1[2][7]):);
	*/
	asm volatile("b8 = %0;":   :"d"(aRegStorageSSn1[2][8]):);
	asm volatile("b9 = %0;":   :"d"(aRegStorageSSn1[2][9]):);
	asm volatile("b10 = %0;":   :"d"(aRegStorageSSn1[2][10]):);
	asm volatile("b11 = %0;":   :"d"(aRegStorageSSn1[2][11]):);
	asm volatile("b12 = %0;":   :"d"(aRegStorageSSn1[2][12]):);
	asm volatile("b13 = %0;":   :"d"(aRegStorageSSn1[2][13]):);
	asm volatile("b14 = %0;":   :"d"(aRegStorageSSn1[2][14]):);
	asm volatile("b15 = %0;":   :"d"(aRegStorageSSn1[2][15]):);

	asm volatile("l0 = %0;":   :"d"(aRegStorageSSn1[3][0]):);
	asm volatile("l1 = %0;":   :"d"(aRegStorageSSn1[3][1]):);
	asm volatile("l2 = %0;":   :"d"(aRegStorageSSn1[3][2]):);
	asm volatile("l3 = %0;":   :"d"(aRegStorageSSn1[3][3]):);
	asm volatile("l4 = %0;":   :"d"(aRegStorageSSn1[3][4]):);
	asm volatile("l5 = %0;":   :"d"(aRegStorageSSn1[3][5]):);
	/*
	asm volatile("l6 = %0;":   :"d"(aRegStorageSSn1[3][6]):);
	asm volatile("l7 = %0;":   :"d"(aRegStorageSSn1[3][7]):);
	*/
	asm volatile("l8 = %0;":   :"d"(aRegStorageSSn1[3][8]):);
	asm volatile("l9 = %0;":   :"d"(aRegStorageSSn1[3][9]):);
	asm volatile("l10 = %0;":   :"d"(aRegStorageSSn1[3][10]):);
	asm volatile("l11 = %0;":   :"d"(aRegStorageSSn1[3][11]):);
	asm volatile("l12 = %0;":   :"d"(aRegStorageSSn1[3][12]):);
	asm volatile("l13 = %0;":   :"d"(aRegStorageSSn1[3][13]):);
	asm volatile("l14 = %0;":   :"d"(aRegStorageSSn1[3][14]):);
	asm volatile("l15 = %0;":   :"d"(aRegStorageSSn1[3][15]):);

	asm volatile("i0 = %0;":   :"d"(aRegStorageSSn1[0][0]):);
	asm volatile("i1 = %0;":   :"d"(aRegStorageSSn1[0][1]):);
	asm volatile("i2 = %0;":   :"d"(aRegStorageSSn1[0][2]):);
	asm volatile("i3 = %0;":   :"d"(aRegStorageSSn1[0][3]):);
	asm volatile("i4 = %0;":   :"d"(aRegStorageSSn1[0][4]):);
	asm volatile("i5 = %0;":   :"d"(aRegStorageSSn1[0][5]):);
	/*
	asm volatile("i6 = %0;":   :"d"(aRegStorageSSn1[0][6]):);
	asm volatile("i7 = %0;":   :"d"(aRegStorageSSn1[0][7]):);
	*/
	asm volatile("i8 = %0;":   :"d"(aRegStorageSSn1[0][8]):);
	asm volatile("i9 = %0;":   :"d"(aRegStorageSSn1[0][9]):);
	asm volatile("i10 = %0;":   :"d"(aRegStorageSSn1[0][10]):);
	asm volatile("i11 = %0;":   :"d"(aRegStorageSSn1[0][11]):);
	asm volatile("i12 = %0;":   :"d"(aRegStorageSSn1[0][12]):);
	asm volatile("i13 = %0;":   :"d"(aRegStorageSSn1[0][13]):);
	asm volatile("i14 = %0;":   :"d"(aRegStorageSSn1[0][14]):);
	asm volatile("i15 = %0;":   :"d"(aRegStorageSSn1[0][15]):);
}

static volatile int32_t aRegStorageSSn2[5][16];

static void pushRegsDAG_SSn2(void)
{
	asm volatile("%0 = m0;":  "=d"(aRegStorageSSn2[1][0]) : :);
	asm volatile("%0 = m1;":  "=d"(aRegStorageSSn2[1][1]) : :);
	asm volatile("%0 = m2;":  "=d"(aRegStorageSSn2[1][2]) : :);
	asm volatile("%0 = m3;":  "=d"(aRegStorageSSn2[1][3]) : :);
	asm volatile("%0 = m4;":  "=d"(aRegStorageSSn2[1][4]) : :);
	asm volatile("%0 = m5;":  "=d"(aRegStorageSSn2[1][5]) : :);
	asm volatile("%0 = m6;":  "=d"(aRegStorageSSn2[1][6]) : :);
	asm volatile("%0 = m7;":  "=d"(aRegStorageSSn2[1][7]) : :);
	asm volatile("%0 = m8;":  "=d"(aRegStorageSSn2[1][8]) : :);
	asm volatile("%0 = m9;":  "=d"(aRegStorageSSn2[1][9]) : :);
	asm volatile("%0 = m10;":  "=d"(aRegStorageSSn2[1][10]) : :);
	asm volatile("%0 = m11;":  "=d"(aRegStorageSSn2[1][11]) : :);
	asm volatile("%0 = m12;":  "=d"(aRegStorageSSn2[1][12]) : :);
	asm volatile("%0 = m13;":  "=d"(aRegStorageSSn2[1][13]) : :);
	asm volatile("%0 = m14;":  "=d"(aRegStorageSSn2[1][14]) : :);
	asm volatile("%0 = m15;":  "=d"(aRegStorageSSn2[1][15]) : :);

	asm volatile("%0 = b0;":  "=d"(aRegStorageSSn2[2][0]) : :);
	asm volatile("%0 = b1;":  "=d"(aRegStorageSSn2[2][1]) : :);
	asm volatile("%0 = b2;":  "=d"(aRegStorageSSn2[2][2]) : :);
	asm volatile("%0 = b3;":  "=d"(aRegStorageSSn2[2][3]) : :);
	asm volatile("%0 = b4;":  "=d"(aRegStorageSSn2[2][4]) : :);
	asm volatile("%0 = b5;":  "=d"(aRegStorageSSn2[2][5]) : :);
	/*
	asm volatile("%0 = b6;":  "=d"(aRegStorageSSn2[2][6]) : :);
	asm volatile("%0 = b7;":  "=d"(aRegStorageSSn2[2][7]) : :);
	*/
	asm volatile("%0 = b8;":  "=d"(aRegStorageSSn2[2][8]) : :);
	asm volatile("%0 = b9;":  "=d"(aRegStorageSSn2[2][9]) : :);
	asm volatile("%0 = b10;":  "=d"(aRegStorageSSn2[2][10]) : :);
	asm volatile("%0 = b11;":  "=d"(aRegStorageSSn2[2][11]) : :);
	asm volatile("%0 = b12;":  "=d"(aRegStorageSSn2[2][12]) : :);
	asm volatile("%0 = b13;":  "=d"(aRegStorageSSn2[2][13]) : :);
	asm volatile("%0 = b14;":  "=d"(aRegStorageSSn2[2][14]) : :);
	asm volatile("%0 = b15;":  "=d"(aRegStorageSSn2[2][15]) : :);

	asm volatile("%0 = l0;":  "=d"(aRegStorageSSn2[3][0]) : :);
	asm volatile("%0 = l1;":  "=d"(aRegStorageSSn2[3][1]) : :);
	asm volatile("%0 = l2;":  "=d"(aRegStorageSSn2[3][2]) : :);
	asm volatile("%0 = l3;":  "=d"(aRegStorageSSn2[3][3]) : :);
	asm volatile("%0 = l4;":  "=d"(aRegStorageSSn2[3][4]) : :);
	asm volatile("%0 = l5;":  "=d"(aRegStorageSSn2[3][5]) : :);
	/*
	asm volatile("%0 = l6;":  "=d"(aRegStorageSSn2[3][6]) : :);
	asm volatile("%0 = l7;":  "=d"(aRegStorageSSn2[3][7]) : :);
	*/
	asm volatile("%0 = l8;":  "=d"(aRegStorageSSn2[3][8]) : :);
	asm volatile("%0 = l9;":  "=d"(aRegStorageSSn2[3][9]) : :);
	asm volatile("%0 = l10;":  "=d"(aRegStorageSSn2[3][10]) : :);
	asm volatile("%0 = l11;":  "=d"(aRegStorageSSn2[3][11]) : :);
	asm volatile("%0 = l12;":  "=d"(aRegStorageSSn2[3][12]) : :);
	asm volatile("%0 = l13;":  "=d"(aRegStorageSSn2[3][13]) : :);
	asm volatile("%0 = l14;":  "=d"(aRegStorageSSn2[3][14]) : :);
	asm volatile("%0 = l15;":  "=d"(aRegStorageSSn2[3][15]) : :);

	/*  Clear L registers */
	asm volatile("l0 = 0;");
	asm volatile("l1 = 0;");
	asm volatile("l2 = 0;");
	asm volatile("l3 = 0;");
	asm volatile("l4 = 0;");
	asm volatile("l5 = 0;");
	asm volatile("l8 = 0;");
	asm volatile("l9 = 0;");
	asm volatile("l10 = 0;");
	asm volatile("l11 = 0;");
	asm volatile("l12 = 0;");
	asm volatile("l13 = 0;");
	asm volatile("l14 = 0;");
	asm volatile("l15 = 0;");

	asm volatile("%0 = i0;":  "=d"(aRegStorageSSn2[0][0]) : :);
	asm volatile("%0 = i1;":  "=d"(aRegStorageSSn2[0][1]) : :);
	asm volatile("%0 = i2;":  "=d"(aRegStorageSSn2[0][2]) : :);
	asm volatile("%0 = i3;":  "=d"(aRegStorageSSn2[0][3]) : :);
	asm volatile("%0 = i4;":  "=d"(aRegStorageSSn2[0][4]) : :);
	asm volatile("%0 = i5;":  "=d"(aRegStorageSSn2[0][5]) : :);
	/*
	asm volatile("%0 = i6;":  "=d"(aRegStorageSSn2[0][6]) : :);
	asm volatile("%0 = i7;":  "=d"(aRegStorageSSn2[0][7]) : :);
	*/
	asm volatile("%0 = i8;":  "=d"(aRegStorageSSn2[0][8]) : :);
	asm volatile("%0 = i9;":  "=d"(aRegStorageSSn2[0][9]) : :);
	asm volatile("%0 = i10;":  "=d"(aRegStorageSSn2[0][10]) : :);
	asm volatile("%0 = i11;":  "=d"(aRegStorageSSn2[0][11]) : :);
	asm volatile("%0 = i12;":  "=d"(aRegStorageSSn2[0][12]) : :);
	asm volatile("%0 = i13;":  "=d"(aRegStorageSSn2[0][13]) : :);
	asm volatile("%0 = i14;":  "=d"(aRegStorageSSn2[0][14]) : :);
	asm volatile("%0 = i15;":  "=d"(aRegStorageSSn2[0][15]) : :);
}

static void popRegsDAG_SSn2(void)
{
	asm volatile("m0 = %0;":   :"d"(aRegStorageSSn2[1][0]):);
	asm volatile("m1 = %0;":   :"d"(aRegStorageSSn2[1][1]):);
	asm volatile("m2 = %0;":   :"d"(aRegStorageSSn2[1][2]):);
	asm volatile("m3 = %0;":   :"d"(aRegStorageSSn2[1][3]):);
	asm volatile("m4 = %0;":   :"d"(aRegStorageSSn2[1][4]):);
	asm volatile("m5 = %0;":   :"d"(aRegStorageSSn2[1][5]):);
	asm volatile("m6 = %0;":   :"d"(aRegStorageSSn2[1][6]):);
	asm volatile("m7 = %0;":   :"d"(aRegStorageSSn2[1][7]):);
	asm volatile("m8 = %0;":   :"d"(aRegStorageSSn2[1][8]):);
	asm volatile("m9 = %0;":   :"d"(aRegStorageSSn2[1][9]):);
	asm volatile("m10 = %0;":   :"d"(aRegStorageSSn2[1][10]):);
	asm volatile("m11 = %0;":   :"d"(aRegStorageSSn2[1][11]):);
	asm volatile("m12 = %0;":   :"d"(aRegStorageSSn2[1][12]):);
	asm volatile("m13 = %0;":   :"d"(aRegStorageSSn2[1][13]):);
	asm volatile("m14 = %0;":   :"d"(aRegStorageSSn2[1][14]):);
	asm volatile("m15 = %0;":   :"d"(aRegStorageSSn2[1][15]):);

	asm volatile("b0 = %0;":   :"d"(aRegStorageSSn2[2][0]):);
	asm volatile("b1 = %0;":   :"d"(aRegStorageSSn2[2][1]):);
	asm volatile("b2 = %0;":   :"d"(aRegStorageSSn2[2][2]):);
	asm volatile("b3 = %0;":   :"d"(aRegStorageSSn2[2][3]):);
	asm volatile("b4 = %0;":   :"d"(aRegStorageSSn2[2][4]):);
	asm volatile("b5 = %0;":   :"d"(aRegStorageSSn2[2][5]):);
	/*
	asm volatile("b6 = %0;":   :"d"(aRegStorageSSn2[2][6]):);
	asm volatile("b7 = %0;":   :"d"(aRegStorageSSn2[2][7]):);
	*/
	asm volatile("b8 = %0;":   :"d"(aRegStorageSSn2[2][8]):);
	asm volatile("b9 = %0;":   :"d"(aRegStorageSSn2[2][9]):);
	asm volatile("b10 = %0;":   :"d"(aRegStorageSSn2[2][10]):);
	asm volatile("b11 = %0;":   :"d"(aRegStorageSSn2[2][11]):);
	asm volatile("b12 = %0;":   :"d"(aRegStorageSSn2[2][12]):);
	asm volatile("b13 = %0;":   :"d"(aRegStorageSSn2[2][13]):);
	asm volatile("b14 = %0;":   :"d"(aRegStorageSSn2[2][14]):);
	asm volatile("b15 = %0;":   :"d"(aRegStorageSSn2[2][15]):);

	asm volatile("l0 = %0;":   :"d"(aRegStorageSSn2[3][0]):);
	asm volatile("l1 = %0;":   :"d"(aRegStorageSSn2[3][1]):);
	asm volatile("l2 = %0;":   :"d"(aRegStorageSSn2[3][2]):);
	asm volatile("l3 = %0;":   :"d"(aRegStorageSSn2[3][3]):);
	asm volatile("l4 = %0;":   :"d"(aRegStorageSSn2[3][4]):);
	asm volatile("l5 = %0;":   :"d"(aRegStorageSSn2[3][5]):);
	/*
	asm volatile("l6 = %0;":   :"d"(aRegStorageSSn2[3][6]):);
	asm volatile("l7 = %0;":   :"d"(aRegStorageSSn2[3][7]):);
	*/
	asm volatile("l8 = %0;":   :"d"(aRegStorageSSn2[3][8]):);
	asm volatile("l9 = %0;":   :"d"(aRegStorageSSn2[3][9]):);
	asm volatile("l10 = %0;":   :"d"(aRegStorageSSn2[3][10]):);
	asm volatile("l11 = %0;":   :"d"(aRegStorageSSn2[3][11]):);
	asm volatile("l12 = %0;":   :"d"(aRegStorageSSn2[3][12]):);
	asm volatile("l13 = %0;":   :"d"(aRegStorageSSn2[3][13]):);
	asm volatile("l14 = %0;":   :"d"(aRegStorageSSn2[3][14]):);
	asm volatile("l15 = %0;":   :"d"(aRegStorageSSn2[3][15]):);

	asm volatile("i0 = %0;":   :"d"(aRegStorageSSn2[0][0]):);
	asm volatile("i1 = %0;":   :"d"(aRegStorageSSn2[0][1]):);
	asm volatile("i2 = %0;":   :"d"(aRegStorageSSn2[0][2]):);
	asm volatile("i3 = %0;":   :"d"(aRegStorageSSn2[0][3]):);
	asm volatile("i4 = %0;":   :"d"(aRegStorageSSn2[0][4]):);
	asm volatile("i5 = %0;":   :"d"(aRegStorageSSn2[0][5]):);
	/*
	asm volatile("i6 = %0;":   :"d"(aRegStorageSSn2[0][6]):);
	asm volatile("i7 = %0;":   :"d"(aRegStorageSSn2[0][7]):);
	*/
	asm volatile("i8 = %0;":   :"d"(aRegStorageSSn2[0][8]):);
	asm volatile("i9 = %0;":   :"d"(aRegStorageSSn2[0][9]):);
	asm volatile("i10 = %0;":   :"d"(aRegStorageSSn2[0][10]):);
	asm volatile("i11 = %0;":   :"d"(aRegStorageSSn2[0][11]):);
	asm volatile("i12 = %0;":   :"d"(aRegStorageSSn2[0][12]):);
	asm volatile("i13 = %0;":   :"d"(aRegStorageSSn2[0][13]):);
	asm volatile("i14 = %0;":   :"d"(aRegStorageSSn2[0][14]):);
	asm volatile("i15 = %0;":   :"d"(aRegStorageSSn2[0][15]):);
}

void InitSS4SH(void)
{
	ADI_SS_MEM_BLOCK oConnMemBlk, *pConnMemBlk;
	ADI_SS_CONNECTION_CONFIG oConnConfig, *pConnConfig;
	ADI_SS_CONNECTION_RESULT eConnRet = ADI_SS_CONNECTION_FAILED;

	ADI_SS_MEM_BLOCK oCommMemBlk, *pCommMemBlk;
	ADI_SS_COMM_CONFIG oCommConfig, *pCommConfig;
	ADI_SS_COMM_RESULT eCommRet = ADI_SS_COMM_FAILED;

	SS_SMAP_SSN_INFO *pSSnInfo;
	ADI_SS_MEM_MAP oSSnMemMap;
	ADI_SS_COMM_PROPERTIES oCommProp;
	ADI_SS_CONFIG oSSnConfig;

#if defined(LOAD_SS4SH_FROM_FLASH)
	uint32_t nFlashAddrSSn1;

	volatile int32_t szSMap = 0;
	volatile int32_t szCodeSSn1 = 0;
	volatile int32_t szParamSSn1 = 0;

	uint32_t nFlashAddrSSn2;

	volatile int32_t szCodeSSn2 = 0;
	volatile int32_t szParamSSn2 = 0;
#endif

	int32_t i;

#ifdef USE_MEASURE_MIPS_SSN
	CYCLES_RESET(oMipsInfoSSn1.oCycleStats);
	CYCLES_INIT(oMipsInfoSSn1.oCycleStats);

	CYCLES_RESET(oMipsInfoSSn2.oCycleStats);
	CYCLES_INIT(oMipsInfoSSn2.oCycleStats);
#endif

	/* SigmaStudio for SHARC (ADSP-SC5xx/ADSP-215xx) library integration */

	/* Connection component Initialization */
	pConnConfig = &oConnConfig;
	pConnConfig->eConnectionType = ADI_SS_CONNECTION_SPI;
	pConnConfig->nDevId = ADI_SS_SPI1_DEVICE;
	pConnConfig->eProcID = PROCESSOR_SH0;

	pConnMemBlk = &oConnMemBlk;
	pConnMemBlk->nSize = ADI_SS_CONNECTION_MEMSIZE;
	pConnMemBlk->pMem = adi_ss_connection_mem;

	eConnRet = adi_ss_connection_Init(pConnMemBlk, pConnConfig, &hConnHandle);
	if(eConnRet != ADI_SS_CONNECTION_SUCCESS)
	{
		printf("\nConnection component initialization failed");
		return;
	}

	/* Communication component initialization */
	pCommConfig = &oCommConfig;
	pCommConfig->bCRCBypass = false;
	pCommConfig->bFullPacketCRC = true;
	pCommConfig->pfCommCmd4CallBack = (ADI_SS_COMM_CMD4_CB) adi_ss_comm_callback_cmd4;
	pCommConfig->pfCommSMAPCallBack = (ADI_SS_COMM_SMAP_CB) adi_ss_comm_callback_smap;
	pCommConfig->hConnectionHandle = hConnHandle;
	pCommConfig->pMemSMap[PROCESSOR_SH0] = &oMemSMap;
	pCommConfig->pBkChnlInfo[PROCESSOR_SH0] = &oBkChnlInfo;

	pCommMemBlk = &oCommMemBlk;
	pCommMemBlk->nSize = ADI_SS_COMM_MEMSIZE;
	pCommMemBlk->pMem = adi_ss_comm_mem;

	eCommRet = adi_ss_comm_Init(pCommMemBlk, pCommConfig, &hCommHandle);
	if(eCommRet != ADI_SS_COMM_SUCCESS)
	{
		printf("\nCommunication component initialization failed");
		return;
	}

#if defined(LOAD_SS4SH_FROM_FLASH)
	nFlashAddrSSn1 = (pFlashAddrSSn1);
	ReadFlashData((uint8_t *)&szSMap, nFlashAddrSSn1, 4);

	nFlashAddrSSn1 += (26);
	ReadFlashData((uint8_t *)&oMemSMap, nFlashAddrSSn1, (szSMap-2));

	fReceivedSMap = 1;
#endif

	/* Wait for SMAP to be received from host */
	while(!fReceivedSMap)
	{
		asm volatile("	nop;	");
	}

	/*=============== For 1st SSn ===============*/
	/* Populating memory addresses of different blocks from SMAP */
	pSSnInfo = &oMemSMap.oSSnInfo[0];
	oSSnMemMap.nMemBlocks = oMemSMap.oSSnInfo[0].nNumSSnBuffers;
	for(i=0; i<oSSnMemMap.nMemBlocks; i++)
	{
		oSSnMemMap.pMemBlocks[i] = &pSSnInfo->oSSnBuff[i];
	}

#if defined(LOAD_SS4SH_FROM_FLASH)
	pSSn1CodeMem = (uint8_t *)oSSnMemMap.pMemBlocks[1]->pMem;
	pSSn1ParamMem = (uint8_t *)oSSnMemMap.pMemBlocks[5]->pMem;

	nFlashAddrSSn1 = (pFlashAddrSSn1+12);
	ReadFlashData((uint8_t *)&szCodeSSn1, nFlashAddrSSn1, 4);
	nFlashAddrSSn1 += (4);
	ReadFlashData((uint8_t *)&szParamSSn1, nFlashAddrSSn1, 4);

	nFlashAddrSSn1 += (22+szSMap);
	ReadFlashData(pSSn1CodeMem, nFlashAddrSSn1, (szCodeSSn1-2));
	nFlashAddrSSn1 += (szCodeSSn1);
	ReadFlashData(pSSn1ParamMem, nFlashAddrSSn1, (szParamSSn1-2));
#endif

	/* Create an instance of SSn1 */
	eSSn1Res = adi_ss_create(&hSSn1Handle, &oSSnMemMap);
	if(hSSn1Handle == NULL)
	{
		printf("\n SSn instance creation failed");
		return;
	}

	/* Provide SSn handles to communication component using the adi_ss_comm_SetProperties() API */
	oCommProp.haSSnHandle[PROCESSOR_SH0][0] = hSSn1Handle;
	oCommProp.nNumProcBlocks = NUM_SSN;
	oCommProp.nProcId = PROCESSOR_SH0;
	eCommRet = adi_ss_comm_SetProperties(hCommHandle,ADI_COMM_PROP_SSN_HANDLE,&oCommProp);
	if(eCommRet != ADI_SS_COMM_SUCCESS)
	{
		printf("\nError in Communication component");
		return;
	}

	/* Initialize the SSn1 instance */
	oSSnConfig.hSSComm = hCommHandle;
	oSSnConfig.nBlockSize = NUM_SSn1_BLOCK_SAMPLES;
	oSSnConfig.nInChannels = AP_SSN1_I_CH;
	oSSnConfig.nOutChannels = AP_SSN1_O_CH;
	oSSnConfig.bSkipProcessOnCRCError = 0;
#if defined(LOAD_SS4SH_FROM_FLASH)
	oSSnConfig.bSkipInitialDownload = 1U;
	oSSnConfig.nInitNoWait = 1;
#else
	oSSnConfig.bSkipInitialDownload = 0U;
	oSSnConfig.nInitNoWait = 0;
#endif
	oSSnConfig.eProcID = PROCESSOR_SH0;
	oSSnConfig.bClearUnusedOutput = 1;

	eSSn1Res = adi_ss_init(hSSn1Handle, &oSSnConfig);
	if(eSSn1Res != ADI_SS_SUCCESS)
	{
		printf("\nSSn instance initialization failed");
		return;
	}
	/*============= End of 1st SSn ==============*/

	/*=============== For 2nd SSn ===============*/
	/* Populating memory addresses of different blocks from SMAP */
	pSSnInfo = &oMemSMap.oSSnInfo[1];
	oSSnMemMap.nMemBlocks = oMemSMap.oSSnInfo[1].nNumSSnBuffers;
	for(i=0; i<oSSnMemMap.nMemBlocks; i++)
	{
		oSSnMemMap.pMemBlocks[i] = &pSSnInfo->oSSnBuff[i];
	}

#if defined(LOAD_SS4SH_FROM_FLASH)
	pSSn2CodeMem = (uint8_t *)oSSnMemMap.pMemBlocks[1]->pMem;
	pSSn2ParamMem = (uint8_t *)oSSnMemMap.pMemBlocks[5]->pMem;

	nFlashAddrSSn2 = (pFlashAddrSSn2+8);
	ReadFlashData((uint8_t *)&szCodeSSn2, nFlashAddrSSn2, 4);
	nFlashAddrSSn2 += (4);
	ReadFlashData((uint8_t *)&szParamSSn2, nFlashAddrSSn2, 4);

	nFlashAddrSSn2 += (22);
	ReadFlashData(pSSn2CodeMem, nFlashAddrSSn2, (szCodeSSn2-2));
	nFlashAddrSSn2 += (szCodeSSn2);
	ReadFlashData(pSSn2ParamMem, nFlashAddrSSn2, (szParamSSn2-2));
#endif

	/* Create an instance of SSn2 */
	eSSn2Res = adi_ss_create(&hSSn2Handle, &oSSnMemMap);
	if(hSSn2Handle == NULL)
	{
		printf("\n SSn instance creation failed");
		return;
	}

	/* Provide SSn handles to communication component using the adi_ss_comm_SetProperties() API */
	oCommProp.haSSnHandle[PROCESSOR_SH0][1] = hSSn2Handle;
	oCommProp.nNumProcBlocks = NUM_SSN;
	oCommProp.nProcId = PROCESSOR_SH0;
	eCommRet = adi_ss_comm_SetProperties(hCommHandle,ADI_COMM_PROP_SSN_HANDLE,&oCommProp);
	if(eCommRet != ADI_SS_COMM_SUCCESS)
	{
		printf("\nError in Communication component");
		return;
	}

	/* Initialize the SSn2 instance */
	oSSnConfig.hSSComm = hCommHandle;
	oSSnConfig.nBlockSize = NUM_SSn2_BLOCK_SAMPLES;
	oSSnConfig.nInChannels = AP_SSN2_I_CH;
	oSSnConfig.nOutChannels = AP_SSN2_O_CH;
	oSSnConfig.bSkipProcessOnCRCError = 0;
#if defined(LOAD_SS4SH_FROM_FLASH)
	oSSnConfig.bSkipInitialDownload = 1U;
	oSSnConfig.nInitNoWait = 1;
#else
	oSSnConfig.bSkipInitialDownload = 0U;
	oSSnConfig.nInitNoWait = 0;
#endif
	oSSnConfig.eProcID = PROCESSOR_SH0;
	oSSnConfig.bClearUnusedOutput = 1;

	eSSn2Res = adi_ss_init(hSSn2Handle, &oSSnConfig);
	if(eSSn2Res != ADI_SS_SUCCESS)
	{
		printf("\nSSn instance initialization failed");
		return;
	}
	/*============= End of 2nd SSn ==============*/

	/************************************************/
	/* Initialize SigmaStudio I/O Pointers for SSn1 */
	/************************************************/

	// 0(FL_ASD), 1(FR_ASD), 2(RL_ASD), 3(RR_ASD), 4(LFE_ASD), 5(CTR_ASD)
#if defined(USE_EASD)
	for(i=0; i<(4); i++)
	{
		ip_data_SSn1[i+0] = (float32_t *)&fBlock_OP_EASD[i][0];
	}
	for(i=0; i<(2); i++)
	{
		ip_data_SSn1[i+4] = &fBlock_IP_SSn1[0];
	}
#elif defined(USE_MASD)
	for(i=0; i<(6); i++)
	{
		ip_data_SSn1[i+0] = &fBlock_IP_SSn1[0];
	}
#elif defined(USE_ESEV)
	for(i=0; i<(1); i++)
	{
		ip_data_SSn1[i+0] = &fBlock_OP_ESEV[0];
	}
	for(i=0; i<(5); i++)
	{
		ip_data_SSn1[i+1] = &fBlock_IP_SSn1[0];
	}
#else
	for(i=0; i<(6); i++)
	{
		ip_data_SSn1[i+0] = &fBlock_IP_SSn1[0];
	}
#endif

	// 6(Not used), 7(Not used)
	for(i=0; i<(2); i++)
	{
		ip_data_SSn1[i+6] = &fBlock_IP_SSn1[0];
	}

	// 8(FL_ANCe), 9(FR_ANCe), 10(RL_ANCe), 11(RR_ANCe), 12(LFE_ANCe), 13(CTR_ANCe)
#if defined(USE_MBBM)
	for(i=0; i<(6); i++)
	{
		ip_data_SSn1[i+8] = &fBlock_IP_SSn1[0];
	}
#else
	for(i=0; i<(6); i++)
	{
		ip_data_SSn1[i+8] = &fBlock_IP_SSn1[0];
	}
#endif

	// 14~21(Audio In0 ~ In7 from AMP A2B)
	for(i=0;i<(8);i++)
	{
		ip_data_SSn1[i+14] = &fAP_AMP_I_Buf[i][0];
	}

	// 22~25(Reserved In0 ~ In3)
	for(i=0;i<(4);i++)
	{
		ip_data_SSn1[i+22] = &fBlock_IP_SSn1[0];
	}

	// 0~7(Audio Out0 ~ Out7 to AMP A2B or DSP2)
	for(i=0; i<(8); i++)
	{
		op_data_SSn1[i+0] = &fAP_AMP_O_Buf[i][0];
	}

	// 8(Camping Out0), 9(Campling Out1)
#if defined(USE_CAMPING)
	for(i=0; i<(2); i++)
	{
		op_data_SSn1[i+8] = &fAP_CAMPO_Buf[i][0];
	}
#else
	for(i=0; i<(2); i++)
	{
		op_data_SSn1[i+8] = &fBlock_OP_SSn1[0];
	}
#endif

	/************************************************/
	/* End of initialization I/O pointers for SSn1  */
	/************************************************/

	/************************************************/
	/* Initialize SigmaStudio I/O Pointers for SSn2 */
	/************************************************/

	// 0(Camping In0), 1(Campling In1)
#if defined(USE_CAMPING)
	for(i=0; i<(2);i++)
	{
		ip_data_SSn2[i] = &fAP_CAMPI_Buf[i][0];
	}
#else
	for(i=0; i<(2);i++)
	{
		ip_data_SSn2[i] = &fBlock_IP_SSn2[0];
	}
#endif

	// 0(VESS Out0), 1(VESS Out1)
	for(i=0; i<(2); i++)
	{
		op_data_SSn2[i] = &fAP_VESSO_Buf[i][0];
	}

	/************************************************/
	/* End of initialization I/O pointers for SSn2  */
	/************************************************/

	/* Populating hardcoded values for readback */
	for(i=0; i<NUM_SSN; i++)
	{
		oBkChnlInfo.fAvgMIPS[i] = 0.0f;
		oBkChnlInfo.fPeakMIPS[i] = 0.0f;
		oBkChnlInfo.nVersionInfo = adi_ss_module_info.nVersionum;
	}

	return;
}

int ProcSS4SH_SSn1(void)
{
	uint32_t iSample, iChannel;

#ifdef USE_MEASURE_MIPS_SSN
	CYCLES_START(oMipsInfoSSn1.oCycleStats);
#endif

	/* Call to the schematic processing */
	pushRegsDAG_SSn1();
	eSSn1Res = adi_ss_schematic_process(hSSn1Handle, NUM_SSn1_BLOCK_SAMPLES, (adi_ss_sample_t **)ip_data_SSn1, (adi_ss_sample_t **)op_data_SSn1, &oSSn1Properties);
	popRegsDAG_SSn1();

#if (USE_DSP_CFG == 0u)
	/* Up-Sampling, Output to AMP A2B */
	for(iChannel=0; iChannel<(AP_AMP_O_CH>>1); iChannel++)
	{
		for(iSample=0; iSample<NUM_SSn1_BLOCK_SAMPLES; iSample++)
		{
			fAP_AMP_O_Buf[iChannel+(AP_AMP_O_CH>>1)][iSample] = fAP_AMP_O_Buf[iChannel][iSample];
		}
	}
#elif (USE_DSP_CFG == 1u)
	/* Up-Sampling, Output to DSP2 */
	for(iChannel=0; iChannel<(AP_IPC_O_CH>>1); iChannel++)
	{
		for(iSample=0; iSample<NUM_SSn1_BLOCK_SAMPLES; iSample++)
		{
			fAP_IPC_O_Buf[iChannel][iSample] = fAP_AMP_O_Buf[iChannel][iSample];
			fAP_IPC_O_Buf[iChannel+(AP_IPC_O_CH>>1)][iSample] = fAP_AMP_O_Buf[iChannel][iSample];
		}
	}
#endif

#ifdef USE_MEASURE_MIPS_SSN
	CYCLES_STOP(oMipsInfoSSn1.oCycleStats);
	oMipsInfoSSn1.fAvgCycles = oMipsInfoSSn1.oCycleStats._total_cycles/oMipsInfoSSn1.oCycleStats._num_calls;
	oMipsInfoSSn1.fMaxCycles = oMipsInfoSSn1.oCycleStats._max_cycles;
	oMipsInfoSSn1.fAvgMips = oMipsInfoSSn1.fAvgCycles*oMipsInfoSSn1.fMipsConst;
	oMipsInfoSSn1.fMaxMips = oMipsInfoSSn1.fMaxCycles*oMipsInfoSSn1.fMipsConst;
	if(oMipsInfoSSn1.oCycleStats._num_calls >= 1500)
	{
		CYCLES_RESET(oMipsInfoSSn1.oCycleStats);
	}

	oBkChnlInfo.fAvgMIPS[0] = oMipsInfoSSn1.fAvgMips;
	oBkChnlInfo.fPeakMIPS[0] = oMipsInfoSSn1.fMaxMips;
#endif

	return 0;
}

int ProcSS4SH_SSn2(void)
{
	uint32_t iSample, iChannel;

#ifdef USE_MEASURE_MIPS_SSN
	CYCLES_START(oMipsInfoSSn2.oCycleStats);
#endif

#ifdef USE_SPI2_MM_FLASH
	/* Call to the schematic processing */
	pushRegsDAG_SSn2();
	eSSn2Res = adi_ss_schematic_process(hSSn2Handle, NUM_SSn2_BLOCK_SAMPLES, (adi_ss_sample_t **)ip_data_SSn2, (adi_ss_sample_t **)op_data_SSn2, &oSSn2Properties);
	popRegsDAG_SSn2();
#endif

#ifdef USE_MEASURE_MIPS_SSN
	CYCLES_STOP(oMipsInfoSSn2.oCycleStats);
	oMipsInfoSSn2.fAvgCycles = oMipsInfoSSn2.oCycleStats._total_cycles/oMipsInfoSSn2.oCycleStats._num_calls;
	oMipsInfoSSn2.fMaxCycles = oMipsInfoSSn2.oCycleStats._max_cycles;
	oMipsInfoSSn2.fAvgMips = oMipsInfoSSn2.fAvgCycles*oMipsInfoSSn2.fMipsConst;
	oMipsInfoSSn2.fMaxMips = oMipsInfoSSn2.fMaxCycles*oMipsInfoSSn2.fMipsConst;
	if(oMipsInfoSSn2.oCycleStats._num_calls >= 1500)
	{
		CYCLES_RESET(oMipsInfoSSn2.oCycleStats);
	}
#endif

	return 0;
}

#endif

