#include <sru21569.h>

#include <adi_types.h>

#include "common.h"

#include "SYSTEM_PWR.h"

#include "DRV_GPIO.h"


#define REPEAT_PULSE_TMR_INSTANCE       1u
#define REPEAT_PULSE_TMR_PERIOD         (0.005f)	/* Ex.) 1.0 (1sec), 0.1(100ms), 0.001(1ms), 0.0001(100us) */
#define REPEAT_PULSE_TMR_FREQ			(200.0f)

#define DELAY_TMR_INSTANCE              2u
#define DELAY_TMR_PERIOD                (0.0f)	/* Not Used */

volatile int32_t gRepeatPulseTimerInit = 0;

volatile int32_t gDelayTimerInit = 0;

volatile int32_t gTmzC = 0;

#ifdef USE_DDR /* DDR TEST */
volatile int32_t gfDDR = 0;

#define DDR_T_NUM	(2)
#define DDR_T_SIZE	(1024*1024)

#pragma align 8
#pragma section("seg_sdram_noinit_data", NO_INIT)
int32_t gDDR_tData[DDR_T_NUM][DDR_T_SIZE];
#endif

static int32_t initRepeatPulseTimer(void)
{
	volatile uint32_t *pREG_TIMER0_TMR_CFG;
	volatile uint32_t *pREG_TIMER0_TMR_CNT;
	volatile uint32_t *pREG_TIMER0_TMR_PER;
	volatile uint32_t *pREG_TIMER0_TMR_WID;
	volatile uint32_t *pREG_TIMER0_TMR_DLY;

	volatile uint16_t TimerDataImsk;
	volatile uint16_t TimerRun;
	uint32_t uiTimerPeriod;
	uint32_t fsclk0 = 0u;

	fsclk0 = GetSClk0PWR();
	if(fsclk0 == 0u)
	{
		return FAILED;
	}
	uiTimerPeriod = (uint32_t)(REPEAT_PULSE_TMR_PERIOD*(float)(fsclk0));
#if(REPEAT_PULSE_TMR_INSTANCE == 0U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR0_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR0_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR0_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR0_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR0_DLY;
	TimerRun = BITM_TIMER_RUN_TMR00;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR00;
#elif(REPEAT_PULSE_TMR_INSTANCE == 1U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR1_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR1_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR1_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR1_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR1_DLY;
	TimerRun = BITM_TIMER_RUN_TMR01;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR01;
#elif(REPEAT_PULSE_TMR_INSTANCE == 2U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR2_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR2_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR2_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR2_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR2_DLY;
	TimerRun = BITM_TIMER_RUN_TMR02;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR02;
#elif(REPEAT_PULSE_TMR_INSTANCE == 3U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR3_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR3_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR3_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR3_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR3_DLY;
	TimerRun = BITM_TIMER_RUN_TMR03;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR03;
#elif(REPEAT_PULSE_TMR_INSTANCE == 4U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR4_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR4_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR4_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR4_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR4_DLY;
	TimerRun = BITM_TIMER_RUN_TMR04;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR04;
#elif(REPEAT_PULSE_TMR_INSTANCE == 5U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR5_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR5_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR5_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR5_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR5_DLY;
	TimerRun = BITM_TIMER_RUN_TMR05;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR05;
#elif(REPEAT_PULSE_TMR_INSTANCE == 6U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR6_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR6_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR6_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR6_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR6_DLY;
	TimerRun = BITM_TIMER_RUN_TMR06;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR06;
#elif(REPEAT_PULSE_TMR_INSTANCE == 7U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR7_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR7_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR7_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR7_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR7_DLY;
	TimerRun = BITM_TIMER_RUN_TMR07;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR07;
#elif(REPEAT_PULSE_TMR_INSTANCE == 8U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR8_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR8_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR8_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR8_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR8_DLY;
	TimerRun = BITM_TIMER_RUN_TMR08;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR08;
#elif(REPEAT_PULSE_TMR_INSTANCE == 9U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR9_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR9_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR9_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR9_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR9_DLY;
	TimerRun = BITM_TIMER_RUN_TMR09;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR09;
#else
#error "This timer instance is not supported"
#endif

	*pREG_TIMER0_TMR_CFG = ENUM_TIMER_TMR_CFG_PWMCONT_MODE | ENUM_TIMER_TMR_CFG_IRQMODE3
							| ENUM_TIMER_TMR_CFG_CLKSEL_SCLK | ENUM_TIMER_TMR_CFG_PADOUT_DIS
							| ENUM_TIMER_TMR_CFG_EMU_CNT;
	*pREG_TIMER0_TMR_CNT = 0;
	*pREG_TIMER0_TMR_PER = uiTimerPeriod;
	*pREG_TIMER0_TMR_WID = 1u; /* PERIOD > (WIDTH + DELAY)*/
	*pREG_TIMER0_TMR_DLY = 1u; /* PERIOD > (WIDTH + DELAY)*/
	*pREG_TIMER0_DATA_IMSK &= (~TimerDataImsk);
	*pREG_TIMER0_RUN_SET = TimerRun;

	gRepeatPulseTimerInit = 1;

	return PASSED;
}

static int32_t stopRepeatPulseTimer(void)
{
	volatile uint32_t *pREG_TIMER0_TMR_CFG;
	volatile uint32_t *pREG_TIMER0_TMR_CNT;
	volatile uint32_t *pREG_TIMER0_TMR_PER;
	volatile uint32_t *pREG_TIMER0_TMR_WID;
	volatile uint32_t *pREG_TIMER0_TMR_DLY;

	volatile uint16_t TimerDataImsk;
	volatile uint16_t TimerStop;

#if(REPEAT_PULSE_TMR_INSTANCE == 0U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR0_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR0_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR0_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR0_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR0_DLY;
	TimerStop = BITM_TIMER_RUN_TMR00;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR00;
#elif(REPEAT_PULSE_TMR_INSTANCE == 1U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR1_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR1_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR1_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR1_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR1_DLY;
	TimerStop = BITM_TIMER_RUN_TMR01;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR01;
#elif(REPEAT_PULSE_TMR_INSTANCE == 2U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR2_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR2_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR2_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR2_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR2_DLY;
	TimerStop = BITM_TIMER_RUN_TMR02;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR02;
#elif(REPEAT_PULSE_TMR_INSTANCE == 3U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR3_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR3_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR3_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR3_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR3_DLY;
	TimerStop = BITM_TIMER_RUN_TMR03;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR03;
#elif(REPEAT_PULSE_TMR_INSTANCE == 4U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR4_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR4_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR4_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR4_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR4_DLY;
	TimerStop = BITM_TIMER_RUN_TMR04;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR04;
#elif(REPEAT_PULSE_TMR_INSTANCE == 5U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR5_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR5_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR5_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR5_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR5_DLY;
	TimerStop = BITM_TIMER_RUN_TMR05;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR05;
#elif(REPEAT_PULSE_TMR_INSTANCE == 6U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR6_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR6_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR6_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR6_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR6_DLY;
	TimerStop = BITM_TIMER_RUN_TMR06;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR06;
#elif(REPEAT_PULSE_TMR_INSTANCE == 7U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR7_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR7_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR7_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR7_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR7_DLY;
	TimerStop = BITM_TIMER_RUN_TMR07;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR07;
#elif(REPEAT_PULSE_TMR_INSTANCE == 8U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR8_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR8_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR8_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR8_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR8_DLY;
	TimerStop = BITM_TIMER_RUN_TMR08;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR08;
#elif(REPEAT_PULSE_TMR_INSTANCE == 9U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR9_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR9_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR9_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR9_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR9_DLY;
	TimerStop = BITM_TIMER_RUN_TMR09;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR09;
#else
#error "This timer instance is not supported"
#endif

	*pREG_TIMER0_STOP_CFG_SET = TimerStop;
	*pREG_TIMER0_RUN_CLR = TimerStop;
	*pREG_TIMER0_DATA_IMSK |= TimerDataImsk;
	*pREG_TIMER0_TMR_CFG = 0;
	*pREG_TIMER0_TMR_CNT = 0;
	*pREG_TIMER0_TMR_PER = 0;
	*pREG_TIMER0_TMR_WID = 0;
	*pREG_TIMER0_TMR_DLY = 0;

	gRepeatPulseTimerInit = 0;

	return PASSED;
}

static int32_t initDelayTimer(void)
{
	volatile uint32_t *pREG_TIMER0_TMR_CFG;
	volatile uint32_t *pREG_TIMER0_TMR_CNT;
	volatile uint32_t *pREG_TIMER0_TMR_PER;
	volatile uint32_t *pREG_TIMER0_TMR_WID;
	volatile uint32_t *pREG_TIMER0_TMR_DLY;

	volatile uint16_t TimerDataImsk;
	volatile uint16_t TimerRun;

#if(DELAY_TMR_INSTANCE == 0U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR0_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR0_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR0_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR0_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR0_DLY;
	TimerRun = BITM_TIMER_RUN_TMR00;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR00;
#elif(DELAY_TMR_INSTANCE == 1U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR1_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR1_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR1_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR1_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR1_DLY;
	TimerRun = BITM_TIMER_RUN_TMR01;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR01;
#elif(DELAY_TMR_INSTANCE == 2U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR2_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR2_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR2_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR2_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR2_DLY;
	TimerRun = BITM_TIMER_RUN_TMR02;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR02;
#elif(DELAY_TMR_INSTANCE == 3U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR3_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR3_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR3_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR3_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR3_DLY;
	TimerRun = BITM_TIMER_RUN_TMR03;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR03;
#elif(DELAY_TMR_INSTANCE == 4U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR4_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR4_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR4_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR4_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR4_DLY;
	TimerRun = BITM_TIMER_RUN_TMR04;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR04;
#elif(DELAY_TMR_INSTANCE == 5U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR5_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR5_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR5_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR5_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR5_DLY;
	TimerRun = BITM_TIMER_RUN_TMR05;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR05;
#elif(DELAY_TMR_INSTANCE == 6U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR6_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR6_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR6_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR6_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR6_DLY;
	TimerRun = BITM_TIMER_RUN_TMR06;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR06;
#elif(DELAY_TMR_INSTANCE == 7U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR7_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR7_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR7_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR7_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR7_DLY;
	TimerRun = BITM_TIMER_RUN_TMR07;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR07;
#elif(DELAY_TMR_INSTANCE == 8U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR8_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR8_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR8_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR8_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR8_DLY;
	TimerRun = BITM_TIMER_RUN_TMR08;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR08;
#elif(DELAY_TMR_INSTANCE == 9U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR9_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR9_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR9_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR9_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR9_DLY;
	TimerRun = BITM_TIMER_RUN_TMR09;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR09;
#else
#error "This timer instance is not supported"
#endif

	*pREG_TIMER0_TMR_CFG = ENUM_TIMER_TMR_CFG_PWMCONT_MODE | ENUM_TIMER_TMR_CFG_IRQMODE3
							| ENUM_TIMER_TMR_CFG_CLKSEL_SCLK | ENUM_TIMER_TMR_CFG_PADOUT_DIS
							| ENUM_TIMER_TMR_CFG_EMU_CNT;
	*pREG_TIMER0_TMR_CNT = 0;
	*pREG_TIMER0_TMR_PER = 0xFFFFFFFF;
	*pREG_TIMER0_TMR_WID = 10u; /* PERIOD > (WIDTH + DELAY)*/
	*pREG_TIMER0_TMR_DLY = 10u; /* PERIOD > (WIDTH + DELAY)*/
	*pREG_TIMER0_DATA_IMSK &= (~TimerDataImsk);
	*pREG_TIMER0_RUN_SET = TimerRun;

	gDelayTimerInit = 1;

	return PASSED;
}

static int32_t stopDelayTimer(void)
{
	volatile uint32_t *pREG_TIMER0_TMR_CFG;
	volatile uint32_t *pREG_TIMER0_TMR_CNT;
	volatile uint32_t *pREG_TIMER0_TMR_PER;
	volatile uint32_t *pREG_TIMER0_TMR_WID;
	volatile uint32_t *pREG_TIMER0_TMR_DLY;

	volatile uint16_t TimerDataImsk;
	volatile uint16_t TimerStop;

#if(REPEAT_PULSE_TMR_INSTANCE == 0U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR0_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR0_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR0_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR0_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR0_DLY;
	TimerStop = BITM_TIMER_RUN_TMR00;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR00;
#elif(REPEAT_PULSE_TMR_INSTANCE == 1U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR1_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR1_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR1_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR1_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR1_DLY;
	TimerStop = BITM_TIMER_RUN_TMR01;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR01;
#elif(REPEAT_PULSE_TMR_INSTANCE == 2U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR2_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR2_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR2_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR2_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR2_DLY;
	TimerStop = BITM_TIMER_RUN_TMR02;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR02;
#elif(REPEAT_PULSE_TMR_INSTANCE == 3U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR3_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR3_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR3_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR3_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR3_DLY;
	TimerStop = BITM_TIMER_RUN_TMR03;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR03;
#elif(REPEAT_PULSE_TMR_INSTANCE == 4U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR4_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR4_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR4_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR4_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR4_DLY;
	TimerStop = BITM_TIMER_RUN_TMR04;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR04;
#elif(REPEAT_PULSE_TMR_INSTANCE == 5U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR5_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR5_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR5_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR5_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR5_DLY;
	TimerStop = BITM_TIMER_RUN_TMR05;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR05;
#elif(REPEAT_PULSE_TMR_INSTANCE == 6U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR6_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR6_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR6_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR6_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR6_DLY;
	TimerStop = BITM_TIMER_RUN_TMR06;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR06;
#elif(REPEAT_PULSE_TMR_INSTANCE == 7U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR7_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR7_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR7_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR7_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR7_DLY;
	TimerStop = BITM_TIMER_RUN_TMR07;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR07;
#elif(REPEAT_PULSE_TMR_INSTANCE == 8U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR8_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR8_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR8_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR8_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR8_DLY;
	TimerStop = BITM_TIMER_RUN_TMR08;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR08;
#elif(REPEAT_PULSE_TMR_INSTANCE == 9U)
	pREG_TIMER0_TMR_CFG = pREG_TIMER0_TMR9_CFG;
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR9_CNT;
	pREG_TIMER0_TMR_PER = pREG_TIMER0_TMR9_PER;
	pREG_TIMER0_TMR_WID = pREG_TIMER0_TMR9_WID;
	pREG_TIMER0_TMR_DLY = pREG_TIMER0_TMR9_DLY;
	TimerStop = BITM_TIMER_RUN_TMR09;
	TimerDataImsk = BITM_TIMER_DATA_IMSK_TMR09;
#else
#error "This timer instance is not supported"
#endif

	*pREG_TIMER0_STOP_CFG_SET = TimerStop;
	*pREG_TIMER0_RUN_CLR = TimerStop;
	*pREG_TIMER0_DATA_IMSK |= TimerDataImsk;
	*pREG_TIMER0_TMR_CFG = 0;
	*pREG_TIMER0_TMR_CNT = 0;
	*pREG_TIMER0_TMR_PER = 0;
	*pREG_TIMER0_TMR_WID = 0;
	*pREG_TIMER0_TMR_DLY = 0;

	gDelayTimerInit = 0;

	return PASSED;
}

uint32_t DRV_Timer_Init(void)
{
	int32_t result = PASSED;

	//InitINTR_TMZ();

	result = initRepeatPulseTimer();
	if(result == FAILED)
		return result;

	result = initDelayTimer();
	if(result == FAILED)
		return result;

	return result;
}

int32_t DoneTimer(void)
{
	int32_t result = PASSED;

	return result;
}

int32_t DelayTimer(float delay)
{
	volatile uint32_t *pREG_TIMER0_TMR_CNT;

	uint32_t refer, period = 0;
	uint32_t fsclk0 = 0u;

	fsclk0 = GetSClk0PWR();
	if(fsclk0 == 0u)
	{
		return FAILED;
	}
#if(DELAY_TMR_INSTANCE == 0U)
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR0_CNT;
#elif(DELAY_TMR_INSTANCE == 1U)
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR1_CNT;
#elif(DELAY_TMR_INSTANCE == 2U)
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR2_CNT;
#elif(DELAY_TMR_INSTANCE == 3U)
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR3_CNT;
#elif(DELAY_TMR_INSTANCE == 4U)
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR4_CNT;
#elif(DELAY_TMR_INSTANCE == 5U)
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR5_CNT;
#elif(DELAY_TMR_INSTANCE == 6U)
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR6_CNT;
#elif(DELAY_TMR_INSTANCE == 7U)
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR7_CNT;
#elif(DELAY_TMR_INSTANCE == 8U)
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR8_CNT;
#elif(DELAY_TMR_INSTANCE == 9U)
	pREG_TIMER0_TMR_CNT = (volatile uint32_t *)pREG_TIMER0_TMR9_CNT;
#else
#error "This timer instance is not supported"
#endif

	period = (uint32_t)(delay*(float)fsclk0);

	refer = *pREG_TIMER0_TMR_CNT;

	while(1)
	{
		if(refer < *pREG_TIMER0_TMR_CNT)
		{
			if((*pREG_TIMER0_TMR_CNT - refer) >= period)
			{
				asm("	nop;	");
				break;
			}
		}
		else
		{
			if(((0xFFFFFFFF - refer) + *pREG_TIMER0_TMR_CNT) >= period)
			{
				asm("	nop;	");
				break;
			}
		}
	}

	return PASSED;
}

int32_t ExecTimer(void)
{
	/* Send Watchdog Toggle Signal from DSP to MCU using GPIO FLAG (Freq = 100Hz(10ms))  */
	if(gTmzC & 0x02) {
#if (EZ_KIT_BOARD == 0u)
		ClrGPIO_PB04();
#endif
	}
	else {
#if (EZ_KIT_BOARD == 0u)
		SetGPIO_PB04();
#endif
	}

#ifdef USE_DDR /* DDR TEST */
	if(gfDDR != gTmzC) {
		int i, j;
		for(i=0; i<DDR_T_NUM; i++) {
			for(j=0; j<DDR_T_SIZE; j++) {
				gDDR_tData[i][j] = gDDR_tData[i][j] + gfDDR;
			}
		}
		gfDDR = gTmzC;
	}
#endif

	return PASSED;
}

/* Timer event handler */
void ISR_Timer(unsigned int id, void* arg)
{
#if(REPEAT_PULSE_TMR_INSTANCE == 0U)
    *pREG_TIMER0_DATA_ILAT = BITM_TIMER_DATA_ILAT_TMR00;
#elif(REPEAT_PULSE_TMR_INSTANCE == 1U)
    *pREG_TIMER0_DATA_ILAT = BITM_TIMER_DATA_ILAT_TMR01;
#elif(REPEAT_PULSE_TMR_INSTANCE == 2U)
    *pREG_TIMER0_DATA_ILAT = BITM_TIMER_DATA_ILAT_TMR02;
#elif(REPEAT_PULSE_TMR_INSTANCE == 3U)
    *pREG_TIMER0_DATA_ILAT = BITM_TIMER_DATA_ILAT_TMR03;
#elif(REPEAT_PULSE_TMR_INSTANCE == 4U)
    *pREG_TIMER0_DATA_ILAT = BITM_TIMER_DATA_ILAT_TMR04;
#elif(REPEAT_PULSE_TMR_INSTANCE == 5U)
    *pREG_TIMER0_DATA_ILAT = BITM_TIMER_DATA_ILAT_TMR05;
#elif(REPEAT_PULSE_TMR_INSTANCE == 6U)
    *pREG_TIMER0_DATA_ILAT = BITM_TIMER_DATA_ILAT_TMR06;
#elif(REPEAT_PULSE_TMR_INSTANCE == 7U)
    *pREG_TIMER0_DATA_ILAT = BITM_TIMER_DATA_ILAT_TMR07;
#elif(REPEAT_PULSE_TMR_INSTANCE == 8U)
    *pREG_TIMER0_DATA_ILAT = BITM_TIMER_DATA_ILAT_TMR08;
#elif(REPEAT_PULSE_TMR_INSTANCE == 9U)
    *pREG_TIMER0_DATA_ILAT = BITM_TIMER_DATA_ILAT_TMR09;
#else
#error "This timer instance is not supported"
#endif

    gTmzC++;	/* 5ms */
}

int32_t GetgTmzC(void)
{
	return gTmzC;
}

float32_t GetgTmz1Sec(void)
{
	return REPEAT_PULSE_TMR_FREQ;
}
