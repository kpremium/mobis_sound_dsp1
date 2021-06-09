
#include <hostapi_masd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#if defined(USE_MASD)

////////////////////////////////////////////////////////////////////////////////////////////////////
// D E F I N E S
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// M A C R O
////////////////////////////////////////////////////////////////////////////////////////////////////

#define MASD_INITIAL_CRC				0x4F81D143		// CRC value for flash downloading
#define MASD_INITIAL_GAIN_CRC			0x04C11DB7		// CRC value for flash downloading


////////////////////////////////////////////////////////////////////////////////////////////////////
// E N U M E R A T I O N S
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// S T R U C T U R E S
////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct _ST_SOUND_ORDER_DESIGN_MASD
{
	ST_ORDER_DESIGN_MASD sound1;

}ST_SOUND_ORDER_DESIGN_MASD;

typedef union _CP_UINT2FLOAT
{
	unsigned int	hex;
	float			var;
}CP_UINT2FLOAT;

#ifdef USE_MEASURE_MIPS_MASD
ST_MIPS_INFO oMipsInfoMASD =
{
	.fAvgCycles = 0,
	.fAvgMips = 0,
	.fMaxCycles = 0,
	.fMaxMips = 0,
	.fMipsConst = (1.0f / (float32_t)(NUM_MASD_SAMPLES) * (float32_t)(CORE_FREQ) / 1000000.0f),
};
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
// F U N C T I O N S (P R O T O T Y P E)
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
// V A R I A B L E S
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma align 8
#pragma section("seg_l1_block1")
float32_t fBlock_MASD_SinT_output[NUM_MASD_SAMPLES*NUM_OP_CHANNELS_MASD];

#pragma align 8
#pragma section("seg_l1_block1")
float32_t fBlock_OP_MASD[NUM_MASD_SAMPLES * NUM_OP_CHANNELS_MASD];

#pragma section("seg_l2_noinit_data", NO_INIT)
uint32_t MASDTuningFlash[MASD_FLASH_DATA_MAX +1];


ADI_CACHE_ALIGN uint8_t txTunBlk_Buf_masd[ADI_CACHE_ROUND_UP_SIZE(512, uint8_t)];
volatile uint32_t txTunBlk_Idx_masd = 0;
volatile uint32_t txTunBlk_Siz_masd = 0;

//#pragma section("arts_l1_block3_data")
//volatile uint32_t rxTunPrc_Dat = 0;

ST_SOUND_ORDER_DESIGN_MASD oSoundOrderDesignMASD;
ST_ORDER_DESIGN_MASD *orderdesignMASD;
ST_VHCL_DATA_MASD oVhclDataMASD;
ST_VHCL_DATA_MASD *oVhclDataMASD_ptr;


////////////////////////////////////////////////////////////////////////////////////////////////////
// F U N C T I O N S (C O D E)
////////////////////////////////////////////////////////////////////////////////////////////////////
void MASD_UART_Tuning_Send_Byte(uint8_t b)
{
	uint8_t txTunByte_Buf[1];
	txTunByte_Buf[0] = b;
	PutsUART_TUN(txTunByte_Buf, 1);
}

void MASD_UART_Tuning_Send_Block(uint8_t *buf, int32_t siz)
{
	if (buf == NULL || siz <= 0)
	{
		return;
	}
	if (siz > sizeof(txTunBlk_Buf_masd))
	{
		PutsUART_TUN(buf, siz);
	}
	else
	{
		int32_t i;
		for (i = 0; i < siz; i++)
		{
			txTunBlk_Buf_masd[i] = buf[i];
		}
		txTunBlk_Idx_masd = 0;
		txTunBlk_Siz_masd = siz;
		/* Unmask the Tx interrupt */
		EnableTxUART_TUN();
	}
}

void MASD_UART_Tuning_Proc_Data(uint32_t b)
{
	uint32_t data = 0;
	// b parameter is a byte received via UART
	data = b;
}

static uint32_t endianConversion32(uint32_t nData)
{
	return ((nData>>24)&0x000000FF) | ((nData>>8)&0x0000FF00) | ((nData<<8)&0x00FF0000) | ((nData<<24)&0xFF000000);
}


static int32_t loadMASDUserData(uint32_t SrcAddr, float32_t *DstAddr, uint32_t size)
{
	uint32_t crc = 0, crc_flash = 0, index = 0;

	int32_t i = 0, j = 0, result = 0, retry = 0;

	CP_UINT2FLOAT float_data;

	if(SrcAddr == 0 || size != MASD_FLASH_DATA_MAX) {
		return (-1);
	}

	if(SrcAddr == (uint32_t)(MASD_FLASH_STRTADD + (MASD_SOUND_OFFSET * 1))){
		orderdesignMASD = &(oSoundOrderDesignMASD.sound1);
	}

	do {
		result = FlashRead((uint8_t *)&MASDTuningFlash[0], ((size+1)*4u), SrcAddr);

		if(result != 0) {
			return (-2); // fail to read data
		}

		crc = MASD_INITIAL_GAIN_CRC;

		for(i = 0 ; i < size ; i++) {
			MASDTuningFlash[i] = endianConversion32(MASDTuningFlash[i]);
			crc ^= MASDTuningFlash[i];
		}

		result = FlashRead((uint8_t *)&crc_flash, 4u, (SrcAddr + size*4u));
		if(result != 0) {
			return (-3); // fail to read crc
		}

		crc_flash = endianConversion32(crc_flash);

		if(crc == crc_flash) {
			break; 		// matched CRC
		}

		if(++retry >= MASD_LOOP_REPEAT) {
			return (-4); // exceed to retry
		}

	}while(1);


	for(i = 0 ; i < MASD_ORDER_DESIGN_TABLE_MAX ; i++) {
		for(j = 0 ; j < MASD_ORDER_DESIGN_GAIN_TABLE_MAX ; j++) {
			float_data.hex = MASDTuningFlash[index++];
			orderdesignMASD->MASDOrderDesignTable[i][j] = float_data.var;
		}
	}

	for(i = 0 ; i < MASD_ORDER_PHASE_TABLE_MAX ; i++) {
		float_data.hex = MASDTuningFlash[index++];
		orderdesignMASD->MASDOrderPhaseTable[i] = float_data.var;
	}

	for(i = 0 ; i < MASD_ORDER_SELECTOR_TABLE_MAX ; i++) {
		float_data.hex = MASDTuningFlash[index++];
		orderdesignMASD->MASDOrderSelTable[i] = float_data.var;
	}


	for(i = 0 ; i < MASD_APS_ORDER_TABLE_MAX ; i++) {
			for(j = 0 ; j < MASD_APS_GAIN_TABLE_MAX ; j++) {
				float_data.hex = MASDTuningFlash[index++];
				orderdesignMASD->MASDOrderAPSTable[i][j] = float_data.var;
			}
		}

	///SKIP DATA NOT REQUIRED BY MASD (Volume Gain DATA)
	index = index + MASD_VOLUME_TABLE_MAX;

	for(i = 0 ; i < MASD_DRV_MODE_TABLE_MAX ; i++) {
		for(j = 0 ; j < MASD_DRV_GAIN_TABLE_MAX ; j++) {
				float_data.hex = MASDTuningFlash[index++];
				orderdesignMASD->MASDDrvGainTable[i][j] = float_data.var;
			}
	}

	for(i = 0 ; i < MASD_MST_GAIN_TABLE_MAX ; i++) {
			float_data.hex = MASDTuningFlash[index++];
			orderdesignMASD->MASDMstGainTable[i] = float_data.var;
		}

	///SKIP DATA NOT REQUIRED BY MASD (APS Response Gain DATA)
	index = index + MASD_APS_TYPE_TABLE_MAX*MASD_APS_GAIN_TABLE_MAX;


	for(i = 0 ; i < MASD_SPEED_TABLE_MAX ; i++) {
			float_data.hex = MASDTuningFlash[index++];
			orderdesignMASD->MASDSpeedTable[i] = float_data.var;
		}

	for(i = 0 ; i < MASD_TORQUE_GAIN_TABLE_MAX ; i++) {
				float_data.hex = MASDTuningFlash[index++];
				orderdesignMASD->MASDTorqueTable[i] = float_data.var;
			}

	for(i = 0 ; i < MASD_GEAR_GAIN_TABLE_MAX ; i++) {
				float_data.hex = MASDTuningFlash[index++];
				orderdesignMASD->MASDGearTable[i] = float_data.var;
			}

	return (0);
}


void InitMASD(void)
{
	int32_t result = 0;
#ifdef USE_MEASURE_MIPS_MASD
	CYCLES_RESET(oMipsInfoMASD.oCycleStats);
	CYCLES_INIT(oMipsInfoMASD.oCycleStats);
#endif

	result = loadMASDUserData((uint32_t)(MASD_FLASH_STRTADD + (MASD_SOUND_OFFSET * 1)), NULL, MASD_FLASH_DATA_MAX);

	// Initialize the UART driver with baudrate 921600.
	//InitUART_TUN(921600);

	// Enroll UART DMA interrupt for tx & rx.
	InitINTR_UART_TUN();


}

void DoneMASD(void)
{
	return;
}

int ExecMASD(void)
{
	//waveSmoothener(fBlock_MASD_SinT_output);

	return 0;
}


#pragma optimize_for_speed
int ProcMASD(void)
{
	int32_t iSample, iChannel;

#ifdef USE_MEASURE_MIPS_MASD
	CYCLES_START(oMipsInfoMASD.oCycleStats);
#endif


#ifdef SINE_WAVE_SIMULATION_MASD

		oVhclDataMASD_ptr = &oVhclDataMASD;
		//sineWavesGenerator(orderdesignMASD,oVhclDataMASD_ptr);

		for(iChannel=0; iChannel<NUM_OP_CHANNELS_MASD; iChannel++)
		{
			for(iSample=0; iSample<NUM_MASD_SAMPLES; iSample++)
			{
				fBlock_OP_MASD[(NUM_MASD_SAMPLES * (iChannel)) + iSample] = 10*fBlock_MASD_SinT_output[(NUM_MASD_SAMPLES * (iChannel)) + iSample];
			}
		}


#endif

#ifdef USE_MEASURE_MIPS_MASD
	CYCLES_STOP(oMipsInfoMASD.oCycleStats);
	oMipsInfoMASD.fAvgCycles = oMipsInfoMASD.oCycleStats._total_cycles/oMipsInfoMASD.oCycleStats._num_calls;
	oMipsInfoMASD.fMaxCycles = oMipsInfoMASD.oCycleStats._max_cycles;
	oMipsInfoMASD.fAvgMips = oMipsInfoMASD.fAvgCycles*oMipsInfoMASD.fMipsConst;
	oMipsInfoMASD.fMaxMips = oMipsInfoMASD.fMaxCycles*oMipsInfoMASD.fMipsConst;
	if(oMipsInfoMASD.oCycleStats._num_calls >= 1500)
	{
		CYCLES_RESET(oMipsInfoMASD.oCycleStats);
	}
#endif

	return 0;
}
#pragma optimize_as_cmd_line


int CommsMASD(void)
{
	/* MASD Sound resource : 0x00(sound 1) 0x01(sound 2) 0x02(sound 3) */
	oVhclDataMASD.SoundMode = (uint32_t)GetSignatureCommsPkg();

	/* APS Type : 0x00(Level 1) 0x01(Level 2) 0x02(Level 3) */
	oVhclDataMASD.APSType = (uint32_t)GetParameterCommsPkg();

	/* RPM : 0 ~ 19000 */
	oVhclDataMASD.rpm = GetRpmCommsPkg();

	/* Throttle : 0 ~ 100% */
	oVhclDataMASD.throttle = GetThrottleCommsPkg();

	/* Engine Load : 0 ~  */
	oVhclDataMASD.engine_load = GetTorqueCommsPkg();

	/* vehicle speed(Wheel Speed) : 0.0 ~  */
	oVhclDataMASD.speed = GetSpeedCommsPkg();

	/* master gain index : 0x00(off) 0x01(level1-weak) 0x02(level2-moderate) 0x03(level3-strong) */
	oVhclDataMASD.MstGainStep = GetMstGainCommsPkg();

	/* volume index: 0 ~ 20	*/
	oVhclDataMASD.MainVolStep = GetVolStepCommsPkg();

	/* driving mode : 0x00(Normal) 0x01(ECO) 0x02(Sports) 0x09(Snow) */
	oVhclDataMASD.DrvModeStep = (uint32_t)GetDrvModeCommsPkg();

	/* Gear : CAN Data P:0, R:7, N:6, D:5,
	   		 Algorithm P:0, R:1, N:2, D:3 */
	if(0 == (uint32_t)GetGearCommsPkg()){
		oVhclDataMASD.Gear = 0;
	}
	else if(7 == (uint32_t)GetGearCommsPkg()){
		oVhclDataMASD.Gear = 1;
	}
	else if(6 == (uint32_t)GetGearCommsPkg()){
		oVhclDataMASD.Gear = 2;
	}
	else if(5 == (uint32_t)GetGearCommsPkg()){
		oVhclDataMASD.Gear = 3;
	}

	/* Ignition(EvDrvRdy) : 0x00(None) 0x01(EV Drivable) */
	oVhclDataMASD.Ignition = (uint32_t)GetIgnitionCommsPkg();

	return 0;
}


int TuningMASD(void)
{
	return 0;
}

void ISR_MASD_Rx(unsigned int id, void* arg)
{
	/* Read the data from the UART Receive Buffer Register */
	MASD_UART_Tuning_Proc_Data((uint32_t)GetcUART_TUN());
}

void ISR_MASD_Tx(unsigned int id, void* arg)
{
	/* Check if there is any data there to be transmitted */
	if(txTunBlk_Idx_masd < txTunBlk_Siz_masd)
	{
		/* Keep writing each byte into the THR register until all the bytes are transmitted */
		PutcUART_TUN(txTunBlk_Buf_masd[txTunBlk_Idx_masd]);
		txTunBlk_Idx_masd++;
	}
	else
	{
		/* Disable the Tx UART */
		DisableTxUART_TUN();
		txTunBlk_Siz_masd = 0;
	}
}

uint32_t GetAvgMipsMASD(void)
{
#ifdef USE_MEASURE_MIPS_MASD
	return (uint32_t)oMipsInfoMASD.fAvgMips;
#else
	return 0;
#endif
}

uint32_t GetMaxMipsMASD(void)
{
#ifdef USE_MEASURE_MIPS_MASD
	return (uint32_t)oMipsInfoMASD.fMaxMips;
#else
	return 0;
#endif
}

//#endif

