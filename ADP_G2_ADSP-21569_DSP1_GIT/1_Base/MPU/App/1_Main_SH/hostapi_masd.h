#ifndef SRC_HOSTAPI_MASD_H_
#define SRC_HOSTAPI_MASD_H_

#include <sys/platform.h>
#include <adi_types.h>
#define DO_CYCLE_COUNTS
#include <cycles.h>

#if defined(ENABLE_DEBUG_INFO)
#define DBG_MSG(VAL)							do{printf(VAL);}while(0)
#else
#define DBG_MSG(...)
#endif

#define USE_MEASURE_MIPS_MASD
#define SINE_WAVE_SIMULATION_MASD

#define CORE_FREQ					(48000U)	/* Hz */

#define NUM_MASD_SAMPLES            (16U)		/* Number of Samples for MASD (3kHz cycles @ 48kHz sampling rate) */

#define NUM_IP_CHANNELS_MASD		(0)			/* ESEV ASD I Channels */
#define NUM_OP_CHANNELS_MASD		(1)			/* ESEV ASD O Channels */

#define FLASH_SECTOR_SIZE			(0x1000)	/* 4 KBytes */

#ifndef M_PI
#define M_PI							(3.141592653589793238462643383279502884197169399375105820974944)
#endif

#define SINE_WAVE_SIMULATION_MASD

#define MASD_LOOP_REPEAT					3

#define MASD_SOUND_MAX						3
#define MASD_SOUND_OFFSET					0x1000

#define MASD_FLASH_STRTADD					(0x500000)
#define MASD_FLASH_ENDADD					(0x50A000)

#define MASD_ORDER_DESIGN_TABLE_MAX			(20)		/* Maximum number of order design table */
#define MASD_ORDER_DESIGN_GAIN_TABLE_MAX	(381)		/* Maximum number of order design gain table, each order design table has gain table(10*38) */

#define MASD_ORDER_PHASE_TABLE_MAX			(20)		/* Maximum number of phaase table */
#define MASD_ORDER_SELECTOR_TABLE_MAX		(20)		/* Maximum number of order selector table */
#define MASD_SPEED_TABLE_MAX				(21)		/* Maximum number of speed table */

#define MASD_APS_TYPE_TABLE_MAX				(3)			//To SKIP reading from the tuning data file
#define MASD_APS_GAIN_TABLE_MAX             (21)
#define MASD_APS_ORDER_TABLE_MAX            (20)

#define MASD_DRV_MODE_TABLE_MAX				(4)		/* eco, comfort, sport, sport+ */
#define MASD_DRV_GAIN_TABLE_MAX             (21)

#define MASD_MST_GAIN_TABLE_MAX				(4)			/* off weak, moderate, strong */
#define MASD_VOLUME_TABLE_MAX				(21)		/* 20 + 1(for on/off) */

#define MASD_TORQUE_GAIN_TABLE_MAX          (21)
#define MASD_GEAR_GAIN_TABLE_MAX			(8)

#define MASD_FLASH_DATA_MAX	    ((MASD_ORDER_DESIGN_TABLE_MAX * MASD_ORDER_DESIGN_GAIN_TABLE_MAX) + MASD_ORDER_PHASE_TABLE_MAX + MASD_ORDER_SELECTOR_TABLE_MAX +\
								(MASD_APS_ORDER_TABLE_MAX * MASD_APS_GAIN_TABLE_MAX) +  MASD_VOLUME_TABLE_MAX +  \
								(MASD_DRV_MODE_TABLE_MAX * MASD_DRV_GAIN_TABLE_MAX) + MASD_MST_GAIN_TABLE_MAX + (MASD_APS_TYPE_TABLE_MAX  * MASD_APS_GAIN_TABLE_MAX)  + \
								MASD_SPEED_TABLE_MAX + MASD_TORQUE_GAIN_TABLE_MAX + MASD_GEAR_GAIN_TABLE_MAX)

#define FFT_SIZE_2048


#ifdef FFT_SIZE_256
#define FFT_SIZE 256
#endif//FFT_SIZE_256

#ifdef FFT_SIZE_512
#define FFT_SIZE 512
#endif//FFT_SIZE_512

#ifdef FFT_SIZE_1024
#define FFT_SIZE 1024
#endif//FFT_SIZE_1024

#ifdef FFT_SIZE_2048
#define FFT_SIZE 2048
#endif//FFT_SIZE_2048

#ifdef FFT_SIZE_4096
#define FFT_SIZE 4096
#endif//FFT_SIZE_4096

typedef struct _ST_MIPS_INFO {
    cycle_stats_t oCycleStats;
    float fMipsConst;
    float fAvgCycles;
    float fMaxCycles;
    float fAvgMips;
    float fMaxMips;
} ST_MIPS_INFO;

typedef enum _ERROR_CODE
{
    NO_ERR,                 /* No Error */
    POLL_TIMEOUT,           /* Polling toggle bit failed */
    VERIFY_WRITE,           /* Verifying write to flash failed */
    INVALID_SECTOR,         /* Invalid Sector */
    INVALID_BLOCK,          /* Invalid Block */
    UNKNOWN_COMMAND,        /* Unknown Command */
    PROCESS_COMMAND_ERR,    /* Processing command */
    NOT_READ_ERROR,         /* Could not read memory from target */
    DRV_NOTAT_BREAK,        /* The application was not at AFP_BreakReady */
    BUFFER_IS_NULL,         /* Could not allocate storage for the buffer */
    NO_ACCESS_SECTOR,       /* Cannot access the sector( could be locked or something is stored there that should not be touched ) */
    WRITE_ERROR,            /* Error writing to memory */
    NO_MODE_SUPPORT,        /* Not a supported operating mode */
    SETUP_ERROR,            /* Error in setup */
    NUM_ERROR_CODES
}ERROR_CODE;

typedef struct _ST_ORDER_DESIGN_MASD
{
	float32_t MASDOrderDesignTable[MASD_ORDER_DESIGN_TABLE_MAX][MASD_ORDER_DESIGN_GAIN_TABLE_MAX];
	float32_t MASDOrderPhaseTable[MASD_ORDER_PHASE_TABLE_MAX];
	float32_t MASDOrderSelTable[MASD_ORDER_SELECTOR_TABLE_MAX];
	float32_t MASDSpeedTable[MASD_SPEED_TABLE_MAX];
	float32_t MASDMstGainTable[MASD_MST_GAIN_TABLE_MAX];
	float32_t MASDDrvGainTable[MASD_DRV_MODE_TABLE_MAX][MASD_DRV_GAIN_TABLE_MAX];
	float32_t MASDOrderAPSTable[MASD_APS_ORDER_TABLE_MAX][MASD_APS_GAIN_TABLE_MAX];
	float32_t MASDGearTable[MASD_GEAR_GAIN_TABLE_MAX];
	float32_t MASDTorqueTable[MASD_TORQUE_GAIN_TABLE_MAX];
}ST_ORDER_DESIGN_MASD;

typedef struct _ST_VHCL_DATA_MASD
{
	float	rpm;
	float	throttle;
	float	engine_load;
	float	speed;

	uint32_t SoundMode;									//
	uint32_t APSType;								//
	uint32_t MstGainStep;							//
	uint32_t DrvModeStep;							//
	uint32_t MainVolStep;							//
	float TotalGain;								//
	uint32_t Gear;
	uint32_t Ignition;
}ST_VHCL_DATA_MASD;

extern float32_t fBlock_OP_MASD[NUM_MASD_SAMPLES * NUM_OP_CHANNELS_MASD];

extern void DmaMemcpy( const uint8_t *src, uint8_t *dest, uint32_t size, void (*cb)(void) );
extern ERROR_CODE FlashRead(uint8_t *puDest, uint32_t uDataSize, uint32_t uDataOffset);
extern ERROR_CODE FlashErase( uint32_t uDataSize, uint32_t uDataOffset );
extern ERROR_CODE FlashWrite(uint8_t *puDest, uint32_t uDataSize, uint32_t uDataOffset);
extern void Sounder(void);

extern uint32_t FlashSectorSize(void);
extern void FlashChangeMode(int nMode);

extern void Sounder(void);

extern void InitINTR_UART_TUN(void);

extern void InitUART_TUN(uint32_t baudrate);
extern void PutsUART_TUN(uint8_t *pData, uint32_t nSize);
extern void GetsUART_TUN(uint8_t *pData, uint32_t nSize);
extern void PutcUART_TUN(uint8_t cByte);
extern uint8_t GetcUART_TUN(void);
extern void DisableRxUART_TUN(void);
extern void EnableRxUART_TUN(void);
extern void DisableTxUART_TUN(void);
extern void EnableTxUART_TUN(void);

void MASD_UART_Tuning_Send_Byte(uint8_t b);
void MASD_UART_Tuning_Send_Block(uint8_t *buf, int32_t siz);

extern float32_t GetSignatureCommsPkg(void);
extern float32_t GetParameterCommsPkg(void);
extern float32_t GetRpmCommsPkg(void);
extern float32_t GetThrottleCommsPkg(void);
extern float32_t GetTorqueCommsPkg(void);
extern float32_t GetSpeedCommsPkg(void);
extern float32_t GetMstGainCommsPkg(void);
extern float32_t GetVolStepCommsPkg(void);
extern float32_t GetDrvModeCommsPkg(void);
extern float32_t GetGearCommsPkg(void);
extern float32_t GetIgnitionCommsPkg(void);

void sineWavesGenerator(ST_ORDER_DESIGN_MASD *orderdesignMASD,ST_VHCL_DATA_MASD *oVhclDataMASD_ptr);
void SetOrderGainAndFrequency(void);
void SetOutputLevel(void);
void waveSmoothener(float *output);

#endif /* SRC_HOSTAPI_H_ */
