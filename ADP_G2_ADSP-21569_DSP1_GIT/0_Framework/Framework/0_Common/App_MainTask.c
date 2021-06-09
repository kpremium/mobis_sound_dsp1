/**
 * @file		App_MainTask.c
 * @brief		This file contains the API definitions for the SHARC framework
 * @author		-
 * @date		2021-05-18
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "adi_initialize.h"

#include "common.h"

#include <sys/platform.h>
#include <adi_types.h>
#include "DRV_DMA.h"
#include "DRV_SPORT.h"
#include "DRV_interrupt.h"
#include "DRV_ASRC.h"
#include "DRV_DAI.h"
#include "DRV_GPIO.h"
#include "DRV_PCG.h"
#include "DRV_SPDIF.h"
#include "DRV_Timer.h"
#include "DRV_SPI.h"
#include "DRV_UART.h"
#include "commsuart.h"

#include "SYSTEM_SPU.h"
#include "SYSTEM_PWR.h"

#include "Variation_MASD.h"


/******************************************************************************
    4. Functions
 ******************************************************************************/

static uint32_t MAIN_Memory_Initialize(void);
static uint32_t MAIN_SYSTEM_Initialize(void);
static uint32_t MAIN_DRIVER_First_Initialize(void);
static uint32_t MAIN_DRIVER_Second_Initialize(void);

static void CheckResult_Application(uint32_t result, uint32_t Compare, char *AssertFile, long unsigned int AssertLine);


int main(int argc, char *argv[])
{
	uint32_t result = PASSED; // FAILED or PASSED
	
	adi_initComponents();


    result = MAIN_Memory_Initialize();
    CheckResult_Application(result, PASSED, __FILE__, __LINE__);

    /***************************************************************************************
     * 1. First Initializing
     ***************************************************************************************/
	
   /* Initialize SYSTEM Module */
	result = MAIN_SYSTEM_Initialize();
   	CheckResult_Application(result, PASSED, __FILE__, __LINE__);
        
   /* Initialize Driver Module */
	result = MAIN_DRIVER_First_Initialize();
   	CheckResult_Application(result, PASSED, __FILE__, __LINE__);
                    

    result = MAIN_DRIVER_Second_Initialize();
    CheckResult_Application(result, PASSED, __FILE__, __LINE__);
  

	/* main process loop */
	for(;;)
	{
		/* nop to avoid only while loop checking inside an infinite loop */
		asm("nop;");
		asm("nop;");
		asm("nop;");

		ExecTimer();

		ExecCommsPkg();

		ExecAudioProcessing();

		ExecUART();
	}

}

static uint32_t MAIN_Memory_Initialize(void)
{
    uint32_t result = PASSED;

    return PASSED;
}


/**
  * @brief initializing the system
  *
  * - Concept
  *
  *
  * - Sequence
  *
  * -# initializing SPU
  * -# initializing system power service
  * -# initialize the various clocks in the system including the core and system clocks
  *
  * @param None
  * @return PASSED/FAILED
  * @remark None
  *
  * @FuncID 
  * @Reentrancy No
  * @GlobalVar no|no
  * @FuncExeTime 
  * @ASIL QM
  * @SWVer 0.1
  */
static uint32_t MAIN_SYSTEM_Initialize(void)
{
    uint32_t result = PASSED; // FAILED or PASSED

    result = SYSTEM_PWR_Init();
    if(result != PASSED) {
        return FAILED;
    }

    result = SYSTEM_SPU_Init();
    if(result != PASSED) {
        return FAILED;
    }


    return result;
}

/**
  * @brief First initialization of the driver
  *
  * - Concept
  *
  *
  * - Sequence
  *
  * -# initializing Uart (baud rates 115200)
  * -# initialize DAI0 and DAI1 Configuration (Digital Audio Interface)
  * -# initialize DAI0 and DAI1 PAD (Digital Audio Interface)
  * -# initialize PCGs (precision clock generator)
  * -# initialize SPDIF 
  * -# initialize ASRC (Asynchronous Sample Rate Converter)
  * -# initialize SIC for DAI0
  * -# initialize Timer 
  * -# initialize PDMA
  * -# initialize SPORT
  * -# initialize GPIO
  * -# initialize TWI(2-Wire Controller Interface)
  *
  * @param None
  * @return PASSED/FAILED
  * @remark None
  *
  * @FuncID 
  * @Reentrancy No
  * @GlobalVar no|no
  * @FuncExeTime 
  * @ASIL QM
  * @SWVer 0.1
  */
static uint32_t MAIN_DRIVER_First_Initialize(void)
{
    uint32_t result = PASSED; // FAILED or PASSED

	result = DRV_DAI_InitSRU(); //InitSRUDAI
	result |= DRV_PCG_Init(); //InitPCG
	result |= DRV_SPDIF_Init(); //InitDIR
	result |= DRV_ASRC_Init(); //InitASRC
	result |= DRV_GPIO_Init(); //InitGPIO
   result |= DRV_SPI_Init(); //InitSPI
	result |= DRV_Timer_Init(); //InitTimer  

    if(result != PASSED) {
        return FAILED;
    }

    return result;
}


static uint32_t MAIN_DRIVER_Second_Initialize(void)
{
    uint32_t result = PASSED; // FAILED or PASSED

	//--------------------------------------------------
	// Initialize Communication Package via UART (included with Vehicle Information from CAN)
	//--------------------------------------------------
	 InitCommsPkg();

    result = MAIN_AudioProcessingInit();

    result |= DRV_Interrupt_Init();
    result |= DRV_DMA_Init();
    result |= DRV_SPORT_Init();
    //DoneSPORT();

    return result;
}

 /**
  * @brief checking application result
  *
  * - Concept
  *  
  *
  * - Sequence
  *
  * -# if the result is not equal to the Compare parameter, print Assertion Exit
  * -# excute exit
  *
  * @param result/Compare/AssertFile/AssertLine
  * @return None
  * @remark None
  *
  * @FuncID 
  * @Reentrancy No
  * @GlobalVar no|no
  * @FuncExeTime 
  * @ASIL QM
  * @SWVer 0.1
  */
static void CheckResult_Application(uint32_t result, uint32_t Compare, char* AssertFile, long unsigned int AssertLine)
{
    if(result != Compare) {
    	if(AssertFile != NULL) {
    		printf("Assertion Exit [%s] : %lu\n", AssertFile, AssertLine);
    		exit(0);
    	}
    }
}

