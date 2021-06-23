#include "common.h"
#include "Variation_MASD.h"
#include "DRV_GPIO.h"
#include "DRV_UART.h"
#include "DRV_Interrupt.h"
#include "DRV_Timer.h"
#include "MASD.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// M A C R O
////////////////////////////////////////////////////////////////////////////////////////////////////

#define CP_DIR_R			0						// read (received)
#define CP_DIR_W			1						// write (sending)

#define CP_DATA_LENGTH		(20)					// 32 -> 20
#define CP_DMA_Q_SIZE		(40)					// 5 -> 40

#define CP_SPD_DSP			0x01
#define CP_SPD_MCU			0x02
#define CP_EPD_MCU			0x03
#define CP_EPD_DSP			0x04

#define CP_RQST_SSN_MIPS	0x62
#define CP_RQST_FILTER_STAT	0x63
#define CP_RQST_SPDIF_STAT	0x64
#define CP_RQST_FRMWRK_VER	0x65
#define CP_RQST_AUDIO_STAT	0x66
#define CP_RQST_SSN_STAT	0x67
#define CP_RQST_DSP_STAT	0x68
#define CP_RQST_DSP_MIPS	0x69
#define CP_RQST_DSP_VER		0x6A
#define CP_RQST_MASD_STAT	0x6B
#define CP_RQST_MASD_MIPS	0x6C
#define CP_RQST_MASD_VER	0x6D
#define CP_RQST_EASD_STAT	0x6E
#define CP_RQST_EASD_MIPS	0x6F
#define CP_RQST_EASD_VER	0x70
#define CP_RQST_MBBM_STAT	0x71
#define CP_RQST_MBBM_MIPS	0x72
#define CP_RQST_MBBM_VER	0x73
#define CP_RQST_ANC_STAT	0x77
#define CP_RQST_ANC_MIPS	0x78
#define CP_RQST_ANC_VER		0x79
#define CP_RQST_TUNING_MODE	0x7F
#define CP_RQST_ENGINE_INFO	0x80					/* RPM(4-bytes), Throttle(4-bytes), Torque(4-bytes), Speed(4-bytes) */
#define CP_RQST_CUSTOM_INFO	0x81					/* Gear(1-byte), Ignition(1-byte), MST Gain(1-bytes), Driving Mode(1-byte), Custom Volume Step(1-byte), dummy(11-bytes) */
#define CP_RQST_DOOR_INFO	0x8A					/* FL door(1-byte), FR door(1-byte), RL door(1-byte), RR door(1-byte), Trunk(1-byte), dummy(11-bytes) */
#define CP_RQST_WINDOW_INFO	0x8B					/* FL window(1-byte), FR window(1-byte), RL window(1-byte), RR window(1-byte), SunRoof(1-byte), dummy(11-bytes) */
#define CP_RQST_ACCEL_INFO	0x90					/* Accel.1(1-byte), Accel.2(1-byte), Accel.3(1-byte), Accel.4(1-byte), Accel.5(1-byte), Accel.6(1-byte), Accel.7(1-byte), Accel.8(1-byte), dummy(8-bytes) */
#define CP_RQST_P_MIC_INFO	0x91					/* P-Mic.1(1-byte), P-Mic.2(1-byte), P-Mic.3(1-byte), P-Mic.4(1-byte), P-Mic.5(1-byte), P-Mic.6(1-byte), P-Mic.7(1-byte), P-Mic.8(1-byte), dummy(8-bytes) */
#define CP_RQST_V_MIC_INFO	0x92					/* V-Mic.1(1-byte), V-Mic.2(1-byte), V-Mic.3(1-byte), V-Mic.4(1-byte), V-Mic.5(1-byte), V-Mic.6(1-byte), V-Mic.7(1-byte), V-Mic.8(1-byte), dummy(8-bytes) */
#define CP_RQST_SPKR_INFO	0x93					/* FL speaker(1-byte), FR speaker(1-byte), RL speaker(1-byte), RR speaker(1-byte), LFE speaker(1-byte), dummy(11-bytes) */
#define CP_RQST_FEED_INFO	0x94					/* FL feedback(1-byte), FR feedback(1-byte), RL feedback(1-byte), RR feedback(1-byte), LFE feedback(1-byte), dummy(11-bytes) */
#define CP_RQST_HOST_INFO	0x95
#define CP_RQST_HOST_PARAM	0x96
#define CP_RQST_MASD_INFO	0x99
#define CP_RQST_MASD_PARAM	0x9A
#define CP_RQST_EASD_INFO	0x9B					/* Signature(1-byte), Parameter(1-byte), dummy(14-bytes) */
#define CP_RQST_EASD_PARAM	0x9C
#define CP_RQST_MBBM_INFO	0x9D
#define CP_RQST_MBBM_PARAM	0x9E
#define CP_RQST_ECO_ORDER	0xA0
#define CP_RQST_NOR_ORDER	0xA1
#define CP_RQST_SPO_ORDER	0xA2
#define CP_RQST_SPP_ORDER	0xA3

#define CP_RSPS_SSN_MIPS	0xB2
#define CP_RSPS_FILTER_STAT	0xB3
#define CP_RSPS_SPDIF_STAT	0xB4
#define CP_RSPS_FRMWRK_VER	0xB5
#define CP_RSPS_AUDIO_STAT	0xB6
#define CP_RSPS_SSN_STAT	0xB7
#define CP_RSPS_DSP_STAT	0xB8
#define CP_RSPS_DSP_MIPS	0xB9
#define CP_RSPS_DSP_VER		0xBA
#define CP_RSPS_MASD_STAT	0xBB
#define CP_RSPS_MASD_MIPS	0xBC
#define CP_RSPS_MASD_VER	0xBD
#define CP_RSPS_EASD_STAT	0xBE
#define CP_RSPS_EASD_MIPS	0xBF
#define CP_RSPS_EASD_VER	0xC0
#define CP_RSPS_MBBM_STAT	0xC1
#define CP_RSPS_MBBM_MIPS	0xC2
#define CP_RSPS_MBBM_VER	0xC3
#define CP_RSPS_ANC_STAT	0xC7
#define CP_RSPS_ANC_MIPS	0xC8
#define CP_RSPS_ANC_VER		0xC9

////////////////////////////////////////////////////////////////////////////////////////////////////
// E N U M E R A T I O N S
////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum _CP_IPC_STAGE
{
	eCP_IPC_STAGE_1,								/* SPD & EPD */
	eCP_IPC_STAGE_2,								/* CMD */
	eCP_IPC_STAGE_3,								/* PKT */
	eCP_IPC_STAGE_4,								/* CKS */
	eCP_IPC_STAGE_MAX
}CP_IPC_STAGE;

typedef enum _CP_PKT_FIELD
{
	eCP_PKT_FIELD_SPD		= 0,					/* Start of Packet Data */
	eCP_PKT_FIELD_CMD		= 1,					/* Command Code */
	eCP_PKT_FIELD_DATA		= 2,					/* Packet Data */
	eCP_PKT_FIELD_CKS		= CP_DATA_LENGTH - 2,	/* Checksum */
	eCP_PKT_FIELD_EPD		= CP_DATA_LENGTH - 1	/* End of Packet Data */
}CP_PKT_FIELD;

typedef enum _CP_CMD_IDX
{
	eCP_CMD_IDX_MCU_0		= 0,
	eCP_CMD_IDX_MCU_1,
	eCP_CMD_IDX_MCU_2,
	eCP_CMD_IDX_MCU_3,
	eCP_CMD_IDX_MCU_4,
	eCP_CMD_IDX_MCU_5,
	eCP_CMD_IDX_MCU_6,
	eCP_CMD_IDX_MCU_7,
	eCP_CMD_IDX_MCU_8,
	eCP_CMD_IDX_MCU_9,
	eCP_CMD_IDX_DSP_0,
	eCP_CMD_IDX_DSP_1,
	eCP_CMD_IDX_DSP_2,
	eCP_CMD_IDX_DSP_3,
	eCP_CMD_IDX_DSP_4,
	eCP_CMD_IDX_DSP_5,
	eUART_CMD_MAX
}CP_CMD_IDX;

typedef enum _CP_CMD_SIZ							/* size in 1 byte unit */
{
	eCP_CMD_SIZ_MCU_0		= 16,
	eCP_CMD_SIZ_MCU_1		= 5,
	eCP_CMD_SIZ_MCU_2		= 2,
	eCP_CMD_SIZ_MCU_3		= 0,
	eCP_CMD_SIZ_MCU_4		= 8,
	eCP_CMD_SIZ_MCU_5		= 0,
	eCP_CMD_SIZ_MCU_6		= 0,
	eCP_CMD_SIZ_MCU_7		= 0,
	eCP_CMD_SIZ_MCU_8		= 0,
	eCP_CMD_SIZ_MCU_9		= 0,
	eCP_CMD_SIZ_DSP_0		= 4,
	eCP_CMD_SIZ_DSP_1		= 4,
	eCP_CMD_SIZ_DSP_2		= 16,
	eCP_CMD_SIZ_DSP_3		= 16,
	eCP_CMD_SIZ_DSP_4		= 8,
	eCP_CMD_SIZ_DSP_5		= 12
}CP_CMD_SIZ;

typedef enum _CP_COMMS_STATE
{
	eCP_COMMS_STATE_RUN		= 0,
	eCP_COMMS_STATE_RESET	= 1,
}CP_COMMS_STATE;

////////////////////////////////////////////////////////////////////////////////////////////////////
// S T R U C T U R E S
////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct _CP_IPC_PKT
{
	uint8_t	Idx;
	uint8_t	Siz;
	uint8_t	Cmd;
	void	(*pCbFunc)(uint8_t *, int32_t, int32_t);
	uint8_t	*pDataBuf;
	uint8_t	CheckSum;
}CP_IPC_PKT;

typedef struct _ST_UART_BUFP
{
	int8_t *base;
	int8_t *end;
	int8_t *read;
	int8_t *write;
	int32_t length;
}ST_UART_BUFP;

////////////////////////////////////////////////////////////////////////////////////////////////////
// P R O T O T Y P E S
////////////////////////////////////////////////////////////////////////////////////////////////////

static void receivedRqstCellStatCpkg(uint8_t * param, int32_t siz, int32_t len);
static void transmitRspsCellStatCpkg(uint8_t * param, int32_t siz, int32_t len);

static void receivedRqstAudioStatCpkg(uint8_t * param, int32_t siz, int32_t len);
static void transmitRspsAudioStatCpkg(uint8_t * param, int32_t siz, int32_t len);

static void receivedRqstDSPStatCpkg(uint8_t * param, int32_t siz, int32_t len);
static void transmitRspsDSPStatCpkg(uint8_t * param, int32_t siz, int32_t len);

static void receivedRqstEASDStatCpkg(uint8_t * param, int32_t siz, int32_t len);
static void transmitRspsEASDStatCpkg(uint8_t * param, int32_t siz, int32_t len);

static void receivedRqstEASDMipsCpkg(uint8_t * param, int32_t siz, int32_t len);
static void transmitRspsEASDMipsCpkg(uint8_t * param, int32_t siz, int32_t len);

static void receivedRqstEASDVerCpkg(uint8_t * param, int32_t siz, int32_t len);
static void transmitRspsEASDVerCpkg(uint8_t * param, int32_t siz, int32_t len);

static void receivedRqstTuningModeCpkg(uint8_t * param, int32_t siz, int32_t len);

static void loadDataCPkg(void);
static uint8_t *getDataCPkg(uint8_t nCmd);

static void setupUARTCPkg(int8_t *pBuffer, int32_t nSize);
static int32_t calcUARTCPkg(ST_UART_BUFP *bufp);
static void copyUARTCPkg(int8_t *pBuffer, int32_t nSize);

static void resetUARTCPkg(void);

////////////////////////////////////////////////////////////////////////////////////////////////////
// V A R I A B L E S
////////////////////////////////////////////////////////////////////////////////////////////////////

static uint8_t gCPkgMCU_0[eCP_CMD_SIZ_MCU_0];
static uint8_t gCPkgMCU_1[eCP_CMD_SIZ_MCU_1];
static uint8_t gCPkgMCU_2[eCP_CMD_SIZ_MCU_2];
//static uint8_t gCPkgMCU_3[eCP_CMD_SIZ_MCU_3];
static uint8_t gCPkgMCU_4[eCP_CMD_SIZ_MCU_4];
//static uint8_t gCPkgMCU_5[eCP_CMD_SIZ_MCU_5];
//static uint8_t gCPkgMCU_6[eCP_CMD_SIZ_MCU_6];
//static uint8_t gCPkgMCU_7[eCP_CMD_SIZ_MCU_7];
//static uint8_t gCPkgMCU_8[eCP_CMD_SIZ_MCU_8];
//static uint8_t gCPkgMCU_9[eCP_CMD_SIZ_MCU_9];

static uint8_t gCPkgDSP_0[eCP_CMD_SIZ_DSP_0];
static uint8_t gCPkgDSP_1[eCP_CMD_SIZ_DSP_1];
static uint8_t gCPkgDSP_2[eCP_CMD_SIZ_DSP_2];
static uint8_t gCPkgDSP_3[eCP_CMD_SIZ_DSP_3];
static uint8_t gCPkgDSP_4[eCP_CMD_SIZ_DSP_4];
static uint8_t gCPkgDSP_5[eCP_CMD_SIZ_DSP_5];

static volatile int32_t gCPkgIpcStage = eCP_IPC_STAGE_1;
static volatile int32_t gCPkgIpcIdx = 0;
static CP_IPC_PKT gCPkgIpcPkt[eUART_CMD_MAX] =
{
	{eCP_CMD_IDX_MCU_0,		eCP_CMD_SIZ_MCU_0,		CP_RQST_ENGINE_INFO,	NULL,							gCPkgMCU_0,		0},
	{eCP_CMD_IDX_MCU_1,		eCP_CMD_SIZ_MCU_1,		CP_RQST_CUSTOM_INFO,	NULL,							gCPkgMCU_1,		0},
	{eCP_CMD_IDX_MCU_2,		eCP_CMD_SIZ_MCU_2,		CP_RQST_EASD_INFO,		NULL,							gCPkgMCU_2,		0},
	{eCP_CMD_IDX_MCU_3,		eCP_CMD_SIZ_MCU_3,		CP_RQST_AUDIO_STAT,		receivedRqstAudioStatCpkg,		NULL,			0},
	{eCP_CMD_IDX_MCU_4,		eCP_CMD_SIZ_MCU_4,		CP_RQST_FILTER_STAT,	receivedRqstCellStatCpkg,		gCPkgMCU_4,		0},
	{eCP_CMD_IDX_MCU_5,		eCP_CMD_SIZ_MCU_5,		CP_RQST_DSP_STAT,		receivedRqstDSPStatCpkg,		NULL,			0},
	{eCP_CMD_IDX_MCU_6,		eCP_CMD_SIZ_MCU_6,		CP_RQST_EASD_STAT,		receivedRqstEASDStatCpkg,		NULL,			0},
	{eCP_CMD_IDX_MCU_7,		eCP_CMD_SIZ_MCU_7,		CP_RQST_EASD_MIPS,		receivedRqstEASDMipsCpkg,		NULL,			0},
	{eCP_CMD_IDX_MCU_8,		eCP_CMD_SIZ_MCU_8,		CP_RQST_EASD_VER,		receivedRqstEASDVerCpkg,		NULL,			0},
	{eCP_CMD_IDX_MCU_9,		eCP_CMD_SIZ_MCU_9,		CP_RQST_TUNING_MODE,	receivedRqstTuningModeCpkg,		NULL,			0},
	{eCP_CMD_IDX_DSP_0,		eCP_CMD_SIZ_DSP_0,		CP_RSPS_AUDIO_STAT,		transmitRspsAudioStatCpkg,		gCPkgDSP_0,		0},
	{eCP_CMD_IDX_DSP_1,		eCP_CMD_SIZ_DSP_1,		CP_RSPS_FILTER_STAT,	transmitRspsCellStatCpkg,		gCPkgDSP_1,		0},
	{eCP_CMD_IDX_DSP_2,		eCP_CMD_SIZ_DSP_2,		CP_RSPS_DSP_STAT,		transmitRspsDSPStatCpkg,		gCPkgDSP_2,		0},
	{eCP_CMD_IDX_DSP_3,		eCP_CMD_SIZ_DSP_3,		CP_RSPS_EASD_STAT,		transmitRspsEASDStatCpkg,		gCPkgDSP_3,		0},
	{eCP_CMD_IDX_DSP_4,		eCP_CMD_SIZ_DSP_4,		CP_RSPS_EASD_MIPS,		transmitRspsEASDMipsCpkg,		gCPkgDSP_4,		0},
	{eCP_CMD_IDX_DSP_5,		eCP_CMD_SIZ_DSP_5,		CP_RSPS_EASD_VER,		transmitRspsEASDVerCpkg,		gCPkgDSP_5,		0}
};

static uint8_t gCPkgRxData[CP_DATA_LENGTH];
static uint8_t gCPkgTxData[CP_DATA_LENGTH];

static uint8_t gCPkgRxQueUART[CP_DATA_LENGTH*CP_DMA_Q_SIZE];
static uint8_t gCPkgTxQueUART[CP_DATA_LENGTH*CP_DMA_Q_SIZE];

static int32_t gCPkgRxFlg = 0;
static int32_t gCPkgTxFlg = 1;

static int32_t gCPkgHandshakingFlg = 0;

uint8_t *gCPkgPtrVhclRpm		= NULL;
uint8_t *gCPkgPtrVhclThrottle	= NULL;
uint8_t *gCPkgPtrVhclTorque		= NULL;
uint8_t *gCPkgPtrVhclSpeed		= NULL;
uint8_t *gCPkgPtrVhclGear		= NULL;
uint8_t *gCPkgPtrVhclIgnition	= NULL;
uint8_t *gCPkgPtrVolStep		= NULL;
uint8_t *gCPkgPtrDrvMode		= NULL;
uint8_t *gCPkgPtrMstGain		= NULL;
uint8_t *gCPkgPtrSignature		= NULL;
uint8_t *gCPkgPtrParameter		= NULL;

static ST_UART_BUFP gUARTBufpRx;
static ST_UART_BUFP gUARTBufpTx;

////////////////////////////////////////////////////////////////////////////////////////////////////
// F U N C T I O N S
////////////////////////////////////////////////////////////////////////////////////////////////////

static int32_t parseStage1CPkg(int32_t rw)
{
	int32_t i = 0;

	// Finish STAGE if error
	gCPkgIpcStage = eCP_IPC_STAGE_MAX;

	if(rw == CP_DIR_R) {
		// Check if Head and Tail are correct
		if(gCPkgRxData[eCP_PKT_FIELD_SPD] == CP_SPD_MCU && gCPkgRxData[eCP_PKT_FIELD_EPD] == CP_EPD_MCU) {
			// If correct, move on to the next stage
			gCPkgIpcStage = eCP_IPC_STAGE_2;

			return 0;
		}
	}
	else {
		// Re-initialize tx buffer
		gCPkgTxData[eCP_PKT_FIELD_SPD] = CP_SPD_DSP;
		for(i = eCP_PKT_FIELD_CMD ; i < eCP_PKT_FIELD_EPD ; i++) {
			gCPkgTxData[i] = 0;
		}
		gCPkgTxData[eCP_PKT_FIELD_EPD] = CP_EPD_DSP;

		// Go to the next stage
		gCPkgIpcStage = eCP_IPC_STAGE_2;

		return 0;
	}

	return -1;
}

static int32_t parseStage2CPkg(int32_t rw)
{
	int32_t i = 0;

	// Finish STAGE if error
	gCPkgIpcStage = eCP_IPC_STAGE_MAX;

	if(rw == CP_DIR_R) {
		// Find command in the list
		for(i = 0 ; i < eCP_CMD_IDX_DSP_0 ; i++) {
			if(gCPkgRxData[eCP_PKT_FIELD_CMD] == gCPkgIpcPkt[i].Cmd) {
				// Calculate checksum
				gCPkgIpcPkt[i].CheckSum = gCPkgRxData[eCP_PKT_FIELD_CMD];

				// Get index of current packet and then use this index from the next stage
				gCPkgIpcIdx = i;

				// Exit immediately if command found
				break;
			}
		}
	}
	else {
		// Store tx command in tx packet
		gCPkgTxData[eCP_PKT_FIELD_CMD] = gCPkgIpcPkt[gCPkgIpcIdx].Cmd;

		// Calculate checksum
		gCPkgIpcPkt[gCPkgIpcIdx].CheckSum = gCPkgTxData[eCP_PKT_FIELD_CMD];
	}

	// Go to the next stage
	gCPkgIpcStage = eCP_IPC_STAGE_3;

	return 0;
}

static int32_t parseStage3CPkg(int32_t rw)
{
	int32_t i = 0;

	// Finish STAGE if error
	gCPkgIpcStage = eCP_IPC_STAGE_MAX;

	if(rw == CP_DIR_R) {
		// Store Data into following buffer
		if(gCPkgIpcPkt[gCPkgIpcIdx].pDataBuf) {
			for(i = 0 ; i < gCPkgIpcPkt[gCPkgIpcIdx].Siz ; i++) {
				gCPkgIpcPkt[gCPkgIpcIdx].pDataBuf[i] = gCPkgRxData[i + eCP_PKT_FIELD_DATA];
			}
		}

		// Calculate checksum
		for(i = eCP_PKT_FIELD_DATA ; i < eCP_PKT_FIELD_CKS ; i++) {
			gCPkgIpcPkt[gCPkgIpcIdx].CheckSum += gCPkgRxData[i];
		}
	}
	else {
		// Set up the data to be transferred to MCU
		if(gCPkgIpcPkt[gCPkgIpcIdx].pCbFunc != 0 && gCPkgIpcPkt[gCPkgIpcIdx].pDataBuf != 0) {
			// Do next process for registered function
			gCPkgIpcPkt[gCPkgIpcIdx].pCbFunc(gCPkgIpcPkt[gCPkgIpcIdx].pDataBuf, gCPkgIpcPkt[gCPkgIpcIdx].Siz, 0);

			for(i = 0 ; i < gCPkgIpcPkt[gCPkgIpcIdx].Siz ; i++) {
				// Copy the data to be transferred to the driver buffer
				gCPkgTxData[i + eCP_PKT_FIELD_DATA] = gCPkgIpcPkt[gCPkgIpcIdx].pDataBuf[i];

				// Calculate checksum
				gCPkgIpcPkt[gCPkgIpcIdx].CheckSum += gCPkgTxData[i];
			}
		}
	}

	// Go to the next stage
	gCPkgIpcStage = eCP_IPC_STAGE_4;

	return 0;
}

static int32_t parseStage4CPkg(int32_t rw)
{
	// Finish STAGE if error
	gCPkgIpcStage = eCP_IPC_STAGE_MAX;

	if(rw == CP_DIR_R) {
		// Check if checksum is correct
		if((gCPkgIpcPkt[gCPkgIpcIdx].CheckSum & 0x000000FF) == gCPkgRxData[eCP_PKT_FIELD_CKS]) {
			// Do next process for registered function
			if(gCPkgIpcPkt[gCPkgIpcIdx].pCbFunc) {
				gCPkgIpcPkt[gCPkgIpcIdx].pCbFunc(gCPkgIpcPkt[gCPkgIpcIdx].pDataBuf, gCPkgIpcPkt[gCPkgIpcIdx].Siz, 0);

				// In the case of a command requesting a response, data update is not performed in the algorithm
				return -1;
			}

			// Update the received data to each algorithm
			return rw;
		}
	}
	else {
		// Store the calculated checksum in txdata buffer
		gCPkgTxData[eCP_PKT_FIELD_CKS] = (gCPkgIpcPkt[gCPkgIpcIdx].CheckSum & 0x000000FF);

		// Config uart dma for tx data only
		ConfigUART_CAN(rw, &gCPkgTxData[0], (uint32_t)(CP_DATA_LENGTH));

		// In the case of a command requesting a response, data update is not performed in the algorithm
		return rw;
	}

	// Updates are not performed in an unknown situation
	return -1;
}

static void procCommsPkg(const int32_t rw)
{
	switch(gCPkgIpcStage)
	{
	case eCP_IPC_STAGE_1 :
		parseStage1CPkg(rw);
		break;
	case eCP_IPC_STAGE_2 :
		parseStage2CPkg(rw);
		break;
	case eCP_IPC_STAGE_3 :
		parseStage3CPkg(rw);
		break;
	case eCP_IPC_STAGE_4 :
		if(parseStage4CPkg(rw) == 0)
		{
#if defined(USE_EASD)
			CommsEASD();
#endif
#if defined(USE_ESEV)
			CommsESEV();
#endif
#if defined(USE_MASD)
			CommsMASD();
#endif
		}
		break;
	default :
		gCPkgIpcStage = eCP_IPC_STAGE_1;
		break;
	}
}

static void DATA4Bto1B(uint32_t input, uint8_t *output)
{
	if(output == 0) {
		return;
	}

	output[0] = (input & 0xFF000000) >> 24;
	output[1] = (input & 0x00FF0000) >> 16;
	output[2] = (input & 0x0000FF00) >> 8;
	output[3] = (input & 0x000000FF) >> 0;
}

static void DATA1Bto4B(uint8_t *input, uint32_t *output)
{
	if(input == 0 || output == 0) {
		return;
	}

	*output = (input[0] & 0x000000FF) << 24
			| (input[1] & 0x000000FF) << 16
			| (input[2] & 0x000000FF) << 8
			| (input[3] & 0x000000FF) << 0;
}

static void receivedRqstCellStatCpkg(uint8_t * param, int32_t siz, int32_t len)
{
	if(gCPkgHandshakingFlg) {
		gCPkgHandshakingFlg = 0;
		return;
	}
	gCPkgHandshakingFlg = 1;

	// Add code if needed

	gCPkgIpcIdx = eCP_CMD_IDX_DSP_1;
}

static void transmitRspsCellStatCpkg(uint8_t * param, int32_t siz, int32_t len)
{
	uint32_t uiStat = 0;

	// Add code if needed

	DATA4Bto1B(uiStat, param);
}

static void receivedRqstAudioStatCpkg(uint8_t * param, int32_t siz, int32_t len)
{
	if(gCPkgHandshakingFlg) {
		gCPkgHandshakingFlg = 0;
		return;
	}
	gCPkgHandshakingFlg = 1;

	// Add code if needed

	gCPkgIpcIdx = eCP_CMD_IDX_DSP_0;
}

static void transmitRspsAudioStatCpkg(uint8_t * param, int32_t siz, int32_t len)
{
	uint32_t uiStat = 0;

	/*
		1Byte : A2B
		1Byte : Algorithm Audio Processing Status(0:NOK, 1:OK)
	*/
	param[0] = 1;
#if defined(USE_EASD)
	param[1] = GetAudProcessingStatEASD();
#endif
}

static void receivedRqstDSPStatCpkg(uint8_t * param, int32_t siz, int32_t len)
{
	if(gCPkgHandshakingFlg) {
		gCPkgHandshakingFlg = 0;
		return;
	}
	gCPkgHandshakingFlg = 1;

	// Add code if needed

	gCPkgIpcIdx = eCP_CMD_IDX_DSP_2;
}

static void transmitRspsDSPStatCpkg(uint8_t * param, int32_t siz, int32_t len)
{
	/*
		CMD   : 0xB8
		4Byte : DSP Avg Mips
		4Byte : DSP Max Mips
		4Byte : Framework Version
		4Byte : DSP Status (0:NOK, 1:OK)
	*/
#ifdef USE_MEASURE_MIPS
	DATA4Bto1B((uint32_t)(oMipsInfoAP_uL.fAvgMips+oMipsInfoAP_uS.fAvgMips), param);
	DATA4Bto1B((uint32_t)(oMipsInfoAP_uL.fMaxMips+oMipsInfoAP_uS.fMaxMips), param + 4);
#else
	DATA4Bto1B(0, param);
	DATA4Bto1B(0, param + 4);
#endif
	DATA4Bto1B((uint32_t)FRAMEWORK_VERSION, param + 8);

	param[12] = 1;	//OK
}

static void receivedRqstEASDStatCpkg(uint8_t * param, int32_t siz, int32_t len)
{
	if(gCPkgHandshakingFlg) {
		gCPkgHandshakingFlg = 0;
		return;
	}
	gCPkgHandshakingFlg = 1;

	// Add code if needed

	gCPkgIpcIdx = eCP_CMD_IDX_DSP_3;
}

static void transmitRspsEASDStatCpkg(uint8_t * param, int32_t siz, int32_t len)
{
#if defined(USE_EASD)
	param[0] = GetInitStatEASD();
	param[1] = GetLoadStatEASD();
	param[2] = GetMstGainStatEASD();
	param[3] = GetCstVolStatEASD();
	param[4] = GetSigStatEASD();
	param[5] = GetParStatEASD();
	DATA4Bto1B((uint32_t)GetFlashStatEASD(), param + 6);
#endif
}

static void receivedRqstEASDMipsCpkg(uint8_t * param, int32_t siz, int32_t len)
{
	if(gCPkgHandshakingFlg) {
		gCPkgHandshakingFlg = 0;
		return;
	}
	gCPkgHandshakingFlg = 1;

	// Add code if needed

	gCPkgIpcIdx = eCP_CMD_IDX_DSP_4;
}

static void transmitRspsEASDMipsCpkg(uint8_t * param, int32_t siz, int32_t len)
{
#if defined(USE_EASD)
	DATA4Bto1B((uint32_t)GetAvgMipsEASD(), param);
	DATA4Bto1B((uint32_t)GetPeakMipsEASD(), param + 4);
#endif
}

static void receivedRqstEASDVerCpkg(uint8_t * param, int32_t siz, int32_t len)
{
	if(gCPkgHandshakingFlg) {
		gCPkgHandshakingFlg = 0;
		return;
	}
	gCPkgHandshakingFlg = 1;

	// Add code if needed

	gCPkgIpcIdx = eCP_CMD_IDX_DSP_5;
}

static void transmitRspsEASDVerCpkg(uint8_t * param, int32_t siz, int32_t len)
{
#if defined(USE_EASD)
	DATA4Bto1B((uint32_t)GetLibVerEASD(), param);
	DATA4Bto1B((uint32_t)GetTuneVerEASD(), param + 4);
	DATA4Bto1B((uint32_t)GetChainVerEASD(), param + 8);
#endif
}

static void receivedRqstTuningModeCpkg(uint8_t * param, int32_t siz, int32_t len)
{
#if defined(USE_EASD) || defined(USE_ESEV)
	InitUART_TUN(921600);
#endif
}

static void loadDataCPkg(void)
{
	gCPkgPtrVhclRpm			= getDataCPkg(CP_RQST_ENGINE_INFO);
	gCPkgPtrVhclThrottle	= getDataCPkg(CP_RQST_ENGINE_INFO)+4;
	gCPkgPtrVhclTorque		= getDataCPkg(CP_RQST_ENGINE_INFO)+8;
	gCPkgPtrVhclSpeed		= getDataCPkg(CP_RQST_ENGINE_INFO)+12;

	gCPkgPtrVhclGear		= getDataCPkg(CP_RQST_CUSTOM_INFO);
	gCPkgPtrVhclIgnition	= getDataCPkg(CP_RQST_CUSTOM_INFO)+1;
	gCPkgPtrMstGain			= getDataCPkg(CP_RQST_CUSTOM_INFO)+2;
	gCPkgPtrDrvMode			= getDataCPkg(CP_RQST_CUSTOM_INFO)+3;
	gCPkgPtrVolStep			= getDataCPkg(CP_RQST_CUSTOM_INFO)+4;

	gCPkgPtrSignature		= getDataCPkg(CP_RQST_EASD_INFO);
	gCPkgPtrParameter		= getDataCPkg(CP_RQST_EASD_INFO)+1;
}

static uint8_t *getDataCPkg(uint8_t nCmd)
{
	int32_t i;

	for(i=0; i<eUART_CMD_MAX; i++) {
		if(gCPkgIpcPkt[i].Cmd == nCmd) {
			return gCPkgIpcPkt[i].pDataBuf;
		}
	}

	return NULL;
}

static void setupUARTCPkg(int8_t *pBuffer, int32_t nSize)
{
	gUARTBufpRx.base = pBuffer;
	gUARTBufpRx.end = pBuffer + nSize;
	gUARTBufpRx.length = nSize;
	gUARTBufpRx.read = pBuffer;
	gUARTBufpRx.write = pBuffer;
}

static int32_t calcUARTCPkg(ST_UART_BUFP *bufp)
{
	int32_t diffByte;
	int8_t *pStart,*pEnd,*pRead,*pWrite;

	pStart = bufp->base;
	pEnd   = bufp->end;
	pRead  = bufp->read;
	pWrite = bufp->write;

	diffByte = (pWrite - pRead);

	if(diffByte >= 0)
		return diffByte;

	return (int32_t)(pEnd - pRead + pWrite - pStart);
}

static void copyUARTCPkg(int8_t *pBuffer, int32_t nSize)
{
	int32_t nAvailSize, i;

	gUARTBufpRx.write = (int8_t *)system_to_internal_address_translation((uint32_t)GetRxAddrUART_CAN());
	nAvailSize = calcUARTCPkg(&gUARTBufpRx);
	if(nAvailSize >= nSize)
	{
		for(i=0; i<nSize; i++)
		{
			*pBuffer++ = *gUARTBufpRx.read++;
			if(gUARTBufpRx.read>= gUARTBufpRx.end)
			{
				gUARTBufpRx.read = (gUARTBufpRx.read - gUARTBufpRx.end) + gUARTBufpRx.base;
			}
		}

		if(!gCPkgRxFlg) {
			gCPkgRxFlg = 1;
		}
	}
}

static void resetUARTCPkg(void)
{
	EnableINTR_UART_CAN(false);

	// Reset UART driver for CAN communication.
	ResetUART_CAN();

	// Initialize the UART driver with baudrate 115200.
	InitUART_CAN(115200);

	// Setup a circular queue for rx data only
	setupUARTCPkg((int8_t *)&gCPkgRxQueUART[0], (CP_DATA_LENGTH*CP_DMA_Q_SIZE));

	// Config UART DMA for rx buffer only.
	ConfigUART_CAN(CP_DIR_R, &gCPkgRxQueUART[0], (uint32_t)(CP_DATA_LENGTH*CP_DMA_Q_SIZE));

	EnableINTR_UART_CAN(true);
}

void InitCommsPkg(void)
{
	// Initialize the data that stores CAN information used by the algorithm.
	loadDataCPkg();

	// Reset UART driver for CAN communication.
	ResetUART_CAN();

	// Initialize the UART driver with baudrate 115200.
	InitUART_CAN(115200);

	// Setup a circular queue for rx data only
	setupUARTCPkg((int8_t *)&gCPkgRxQueUART[0], (CP_DATA_LENGTH*CP_DMA_Q_SIZE));

	// Config UART DMA for rx buffer only.
	ConfigUART_CAN(CP_DIR_R, &gCPkgRxQueUART[0], (uint32_t)(CP_DATA_LENGTH*CP_DMA_Q_SIZE));

	// Enroll UART DMA interrupt for tx & rx.
	InitINTR_UART_CAN();
}

void ExecCommsPkg(void)
{
	// This function will be called within unlimited loop.
	static volatile int32_t iStartCnt = 0, iCurCnt = 0;
	static volatile CP_COMMS_STATE eState = eCP_COMMS_STATE_RUN;

	switch(eState)
	{
		case eCP_COMMS_STATE_RUN:
			copyUARTCPkg((int8_t *)gCPkgRxData, CP_DATA_LENGTH);

			// When Rx data is received, this flag is set to 1.
			if(gCPkgRxFlg == 1) {									// MCU -> DSP
				gCPkgIpcStage = eCP_IPC_STAGE_1;
				do {
					procCommsPkg(CP_DIR_R);
				} while(gCPkgIpcStage != eCP_IPC_STAGE_MAX);

				gCPkgRxFlg = 0;
				iStartCnt = 0;
			}

			// When ready to send Tx data, this flag is set to 1.
			// And it transmits Tx data only when two-way communication is required.
			if(gCPkgTxFlg == 1 && gCPkgHandshakingFlg == 1) {		// DSP -> MCU
				gCPkgIpcStage = eCP_IPC_STAGE_1;
				do {
					procCommsPkg(CP_DIR_W);
				} while(gCPkgIpcStage != eCP_IPC_STAGE_MAX);

				gCPkgHandshakingFlg = 0;

				gCPkgTxFlg = 0;
			}

			if(iStartCnt == 0)
			{
				iStartCnt = GetgTmzC();
			}
			iCurCnt = GetgTmzC();
			if((iCurCnt - iStartCnt) > 600)	/* 5ms * 600 = 3000ms */
			{
				eState = eCP_COMMS_STATE_RESET;
				iStartCnt = 0;

				/* Set PB06 High */
				SetGPIO_PB06();
			}

			break;

		case eCP_COMMS_STATE_RESET:
			if(iStartCnt == 0)
			{
				iStartCnt = GetgTmzC();
			}
			iCurCnt = GetgTmzC();
			if((iCurCnt - iStartCnt) > 10)	/* 5ms * 10 = 50ms */
			{
				eState = eCP_COMMS_STATE_RUN;
				iStartCnt = 0;

				/* Reset DMA UART */
				resetUARTCPkg();

				/* Set PB06 Low */
				ClrGPIO_PB06();
			}

			break;

		default:
			break;
	}
}

void ISR_CommsPkg_Rx(unsigned int id, void* arg)
{
	DoneRxDMAIRQUART_CAN();

	if(!gCPkgRxFlg) {
		gCPkgRxFlg = 1;
	}

//	SetTxBusyUART_CAN(0);
}

void ISR_CommsPkg_Tx(unsigned int id, void* arg)
{
	DoneTxDMAIRQUART_CAN();

	if(!gCPkgTxFlg) {
		gCPkgTxFlg = 1;
	}

	SetTxBusyUART_CAN(0);
}

float32_t GetRpmCommsPkg(void)
{
	float32_t fRpm = 0.0;
	int32_t *nRpm = (int32_t *)&fRpm;

	if(gCPkgPtrVhclRpm != NULL) {
		*nRpm = (int32_t)((gCPkgPtrVhclRpm[0]<<24) | (gCPkgPtrVhclRpm[1]<<16) | (gCPkgPtrVhclRpm[2]<<8) | (gCPkgPtrVhclRpm[3]));
	}

	return fabsf(fRpm);
}

float32_t GetThrottleCommsPkg(void)
{
	float32_t fThrottle = 0.0;
	int32_t *nThrottle = (int32_t *)&fThrottle;

	if(gCPkgPtrVhclThrottle != NULL) {
		*nThrottle = (int32_t)( (gCPkgPtrVhclThrottle[0]<<24) | (gCPkgPtrVhclThrottle[1]<<16) | (gCPkgPtrVhclThrottle[2]<<8) | (gCPkgPtrVhclThrottle[3]) );
	}

	return fThrottle;
}

float32_t GetTorqueCommsPkg(void)
{
	float32_t fTorque = 0.0;
	int32_t *nTorque = (int32_t *)&fTorque;

	if(gCPkgPtrVhclTorque != NULL) {
		*nTorque = (int32_t)( (gCPkgPtrVhclTorque[0]<<24) | (gCPkgPtrVhclTorque[1]<<16) | (gCPkgPtrVhclTorque[2]<<8) | (gCPkgPtrVhclTorque[3]) );
	}

	return fabsf(fTorque);
}

float32_t GetSpeedCommsPkg(void)
{
	float32_t fSpeed = 0.0;
	int32_t *nSpeed = (int32_t *)&fSpeed;

	if(gCPkgPtrVhclSpeed != NULL) {
		*nSpeed = (int32_t)( (gCPkgPtrVhclSpeed[0]<<24) | (gCPkgPtrVhclSpeed[1]<<16) | (gCPkgPtrVhclSpeed[2]<<8) | (gCPkgPtrVhclSpeed[3]) );
	}

	return fSpeed;
}

float32_t GetGearCommsPkg(void)
{
	float32_t fGear = 0.0;
	uint32_t value;

	value = gCPkgPtrVhclGear[0];

	fGear = (float32_t)value;

	return fGear;
}

float32_t GetIgnitionCommsPkg(void)
{
	float32_t fIgnition = 0.0;
	uint32_t value;

	value = gCPkgPtrVhclIgnition[0];

	fIgnition = (float32_t)value;

	return fIgnition;
}

float32_t GetVolStepCommsPkg(void)
{
	float32_t fVolStep = 0.0;
	uint32_t value;

	value = gCPkgPtrVolStep[0];

	fVolStep = (float32_t)value;

	return fVolStep;
}

float32_t GetDrvModeCommsPkg(void)
{
	float32_t fDrvMode = 0.0;
	uint32_t value;

	value = gCPkgPtrDrvMode[0];

	fDrvMode = (float32_t)value;

	return fDrvMode;
}

float32_t GetMstGainCommsPkg(void)
{
	float32_t fVolStep = 0.0;
	uint32_t value;

	value = gCPkgPtrMstGain[0];

	fVolStep = (float32_t)value;

	return fVolStep;
}

float32_t GetSignatureCommsPkg(void)
{
	float32_t fSignature = 0.0;
	uint32_t value;

	value = (uint32_t)gCPkgPtrSignature[0];

	fSignature = (float32_t)value;

	return (fSignature-1.0);
}

float32_t GetParameterCommsPkg(void)
{
	float32_t fParameter = 0.0;
	uint32_t value;

	value = (uint32_t)gCPkgPtrParameter[0];

	fParameter = (float32_t)value;

	return (fParameter-1.0);
}

