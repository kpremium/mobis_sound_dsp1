#include <interrupt.h>
#include <services/int/adi_int.h>
#include <services/int/adi_sec.h>

#include "common.h"

#include "DRV_DMA.h"
#include "DRV_DAI.h"
#include "DRV_SPI.h"
#include "DRV_Timer.h"
#include "DRV_LinkPort.h"

#include "commsuart.h" //todo

#include "Variation_MASD.h"

static void InitINTR_MDMA(void);
static void InitINTR_SPORT(void);
static void InitINTR_USER(void);
static void InitINTR_TMZ(void);
static void InitINTR_UART(void);


uint32_t DRV_Interrupt_Init(void)
{
	//InitINTR_MDMA();
	InitINTR_SPORT();
	InitINTR_USER();
	InitINTR_TMZ();
	//InitINTR_UART();

	return PASSED;
}

void InitINTR_SPORT(void)
{
	/* SPORT Interrupt Configuration */
	adi_sec_SetPriority(INTR_DAI0_GBL_SPORT_INT0,INTR_DAI0_GBL_SPORT_INT0);
	adi_sec_SetPriority(INTR_DAI0_GBL_SPORT_INT1,INTR_DAI0_GBL_SPORT_INT1);
	adi_sec_SetPriority(INTR_DAI1_GBL_SPORT_INT0,INTR_DAI1_GBL_SPORT_INT0);
	adi_sec_SetPriority(INTR_DAI1_GBL_SPORT_INT1,INTR_DAI1_GBL_SPORT_INT1);

	adi_int_InstallHandler(INTR_DAI0_GBL_SPORT_INT0, (ADI_INT_HANDLER_PTR)ISR_DAI0_GRP0, 0, true);
	adi_int_InstallHandler(INTR_DAI0_GBL_SPORT_INT1, (ADI_INT_HANDLER_PTR)ISR_DAI0_GRP1, 0, true);
	adi_int_InstallHandler(INTR_DAI1_GBL_SPORT_INT0, (ADI_INT_HANDLER_PTR)ISR_DAI1_GRP0, 0, true);
	adi_int_InstallHandler(INTR_DAI1_GBL_SPORT_INT1, (ADI_INT_HANDLER_PTR)ISR_DAI1_GRP1, 0, true);
}

void InitINTR_USER(void)
{
	adi_sec_SetPriority(INTR_SYS_SOFT0_INT,INTR_DAI1_GBL_SPORT_INT1+2);
	adi_sec_SetPriority(INTR_SYS_SOFT1_INT,INTR_DAI1_GBL_SPORT_INT1+2);

	/* USER Interrupt Configuration */
	adi_int_InstallHandler(INTR_SYS_SOFT0_INT, (ADI_INT_HANDLER_PTR)MAIN_AudioProcessing_uL, 0, true);
	adi_int_InstallHandler(INTR_SYS_SOFT1_INT, (ADI_INT_HANDLER_PTR)MAIN_AudioProcessing_uS, 0, true);
	//adi_int_InstallHandler(ADI_CID_SFT0I, (ADI_INT_HANDLER_PTR)ISR_AudioProcessing_uL, 0, true);
	//adi_int_InstallHandler(ADI_CID_SFT1I, (ADI_INT_HANDLER_PTR)ISR_AudioProcessing_uS, 0, true);
}

void InitINTR_UART_CAN(void)
{
	/* UART Interrupt Configuration */
	adi_sec_SetPriority(INTR_UART2_TXDMA, INTR_UART2_TXDMA);
	adi_sec_SetPriority(INTR_UART2_RXDMA, INTR_UART2_RXDMA);

	adi_int_InstallHandler(INTR_UART2_TXDMA, (ADI_INT_HANDLER_PTR)ISR_CommsPkg_Tx, 0, true);
	adi_int_InstallHandler(INTR_UART2_RXDMA, (ADI_INT_HANDLER_PTR)ISR_CommsPkg_Rx, 0, true);
}

void EnableINTR_UART_CAN(bool bEn)
{
	adi_sec_EnableInterrupt(INTR_UART2_TXDMA, bEn);
	adi_sec_EnableInterrupt(INTR_UART2_RXDMA, bEn);
}

void InitINTR_UART_TUN(void)
{
	/* UART Interrupt Configuration */
#if defined(USE_EASD)

#if (EZ_KIT_BOARD == 1u)
	adi_sec_SetPriority(INTR_UART0_TXDMA, INTR_UART0_TXDMA);
	adi_sec_SetPriority(INTR_UART0_RXDMA, INTR_UART0_RXDMA);

    adi_int_InstallHandler((uint32_t)INTR_UART0_RXDMA, ISR_EASD_Rx, 0, true);
    adi_int_InstallHandler((uint32_t)INTR_UART0_TXDMA, ISR_EASD_Tx, 0, true);
#else
	adi_sec_SetPriority(INTR_UART1_TXDMA, INTR_UART1_TXDMA);
	adi_sec_SetPriority(INTR_UART1_RXDMA, INTR_UART1_RXDMA);

    adi_int_InstallHandler((uint32_t)INTR_UART1_RXDMA, ISR_EASD_Rx, 0, true);
    adi_int_InstallHandler((uint32_t)INTR_UART1_TXDMA, ISR_EASD_Tx, 0, true);
#endif

#endif

#if defined(USE_ESEV)

	adi_sec_SetPriority(INTR_UART1_TXDMA, INTR_UART1_TXDMA);
	adi_sec_SetPriority(INTR_UART1_RXDMA, INTR_UART1_RXDMA);

    adi_int_InstallHandler((uint32_t)INTR_UART1_RXDMA, ISR_ESEV_Rx, 0, true);
    adi_int_InstallHandler((uint32_t)INTR_UART1_TXDMA, ISR_ESEV_Tx, 0, true);

#endif
}

void EnableINTR_UART_TUN(bool bEn)
{
#if defined(USE_EASD)

#if (EZ_KIT_BOARD == 1u)
	adi_sec_EnableInterrupt(INTR_UART0_TXDMA, bEn);
	adi_sec_EnableInterrupt(INTR_UART0_RXDMA, bEn);
#else
	adi_sec_EnableInterrupt(INTR_UART1_TXDMA, bEn);
	adi_sec_EnableInterrupt(INTR_UART1_RXDMA, bEn);
#endif

#endif
}

void InitINTR_TMZ(void)
{
	/* Timer Interrupt Configuration */
	adi_sec_SetPriority(INTR_TIMER0_TMR1, (ADI_INTR_BASE + 200));

	adi_int_InstallHandler(INTR_TIMER0_TMR1, (ADI_INT_HANDLER_PTR)ISR_Timer, 0, true);
}

void InitINTR_LinkPort(void)
{
	/* LinkPort Interrupt Configuration */
	adi_sec_SetPriority(INTR_LP1_DMA,INTR_LP1_DMA);
	adi_int_InstallHandler(INTR_LP1_DMA, (ADI_INT_HANDLER_PTR)ISR_Linkport1, 0, true);

	adi_sec_SetPriority(INTR_LP0_DMA,INTR_LP0_DMA);
	adi_int_InstallHandler(INTR_LP0_DMA, (ADI_INT_HANDLER_PTR)ISR_Linkport0, 0, true);
}

