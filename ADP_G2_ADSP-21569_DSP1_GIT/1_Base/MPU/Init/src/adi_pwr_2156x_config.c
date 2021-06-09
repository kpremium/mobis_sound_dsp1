/*
 ** Copyright (C) 2018-2019 Analog Devices Inc., All Rights Reserved.
 **
 ** This file was originally generated based upon the options selected in
 ** the Basic Configuration of CGU Initialization configuration dialog.
 ** Subsequently it has been manually edited.
 */
/** @addtogroup Init_Preload_2156x Processor Initialization Code
 *  @{
 *
 */

/*!
* @file      adi_pwr_2156x_config.c
*
* @brief     power Service configuration file
*
* @details
*            power Service configuration file
*/

#include <sys/platform.h>
#include <stdint.h>
#include <stdlib.h>
#include <services/pwr/adi_pwr.h>

#include "adi_pwr_2156x_config.h"

#ifdef _MISRA_RULES
#pragma diag(push)
#pragma diag(suppress:misra_rule_14_7:"Allow functions to have multiple exits for better readability and optimized code")
#endif


/**********************************************************************************************
 *                     CGU Configuration Number 0
 **********************************************************************************************/
/*
Configuration Number    : 0
SDRAM Mode              : DDR3
SYS_CLKIN0 (MHz)        : 25
Use CGU1 ?              : No

//CDU Initialization Options
SPI(0-2) CLOCK SOURCE (CLKO0)  :   SCLK0_0      :   125 MHz
DDR CLOCK             (CLKO0)  :   DCLK0_0      :   500 MHz

//CGU0 Initialization Options
fPLL (Desired)          :   2000 MHz
fPLL (Actual)           :   2000.0 MHz
CCLK                    :   1000.0 MHz
SYSCLK                  :   500.0  MHz
SCLK0                   :   125.0 MHz
SCLK1(SPDIF RX)         :   333.3 MHz
DCLK                    :   500 MHz
OCLK (LP CLOCK)         :   125.0 MHz

MSEL                    :   80
Use DF?                 :   No
DF                      :   0
CSEL                    :   2
CCLK to SYSCLK Ratio    :   2:1
S0SEL                   :   4
S1SEL                   :   2
DSEL                    :   4
OSEL                    :   16
Use S1SELEX?            :   Yes
S1SELEX                 :   6

//CGU1 Initialization Options
--Not used--
*/
/**********************************************************************************************
 *                      CGU Configuration Number 0
 **********************************************************************************************/

#define CFG0_BIT_CGU0_CLKIN                                25000000 /*!< Macro for SYS_CLKIN */
#define CFG0_BIT_CGU1_CLKIN                                25000000 /*!< Macro for SYS_CLKIN */
/* SPI(0-2) CLOCK SOURCE */
#define CFG0_BIT_CDU0_CFG0_SEL_VALUE                       0        /*!< Macro for CDU CFG0 Selection */
/* DDR CLOCK */
#define CFG0_BIT_CDU0_CFG1_SEL_VALUE                       0        /*!< Macro for CDU CFG1 Selection */

/**********************************************************************************************
 *                     CGU Configuration Number 0 Register Values
 **********************************************************************************************/
/*****************************************CGU0_CTL**********************************************/
#define CFG0_BIT_CGU0_CTL_DF                               0        /*!< Macro for CGU0 DF bit */
#define CFG0_BIT_CGU0_CTL_MSEL                             80       /*!< Macro for CGU0 MSEL field */
/*****************************************CGU0_DIV**********************************************/
#define CFG0_BIT_CGU0_DIV_CSEL                             2        /*!< Macro for CGU0 CSEL field */
#define CFG0_BIT_CGU0_DIV_SYSSEL                           4        /*!< Macro for CGU0 SYSSEL field */
#define CFG0_BIT_CGU0_DIV_S0SEL                            4        /*!< Macro for CGU0 S0SEL field */
#define CFG0_BIT_CGU0_DIV_S1SEL                            2        /*!< Macro for CGU0 S1SEL field */
#define CFG0_BIT_CGU0_DIV_DSEL                             4        /*!< Macro for CGU0 DSEL field */
#define CFG0_BIT_CGU0_DIV_OSEL                             16       /*!< Macro for CGU0 OSEL field */
/*****************************************CGU0_DIVEX**********************************************/
#define CFG0_BIT_CGU0_DIV_S1SELEX                          6        /*!< Macro for CGU0 S1SELEX field */
/***********************************************************************************************/


/**
 * @brief    Initializes clocks, including CGU and CDU modules.
 *
 * @return   Status
 *           - 0: Successful in all the initializations.
 *           - 1: Error.
 */
uint32_t adi_pwr_cfg0_init(void)
{
    /* Structure pointer for CGU0 and CGU1 parameters*/
    ADI_PWR_CGU_PARAM_LIST pADI_CGU_Param_List;

    /* Structure pointer for CDU parameters*/
    ADI_PWR_CDU_PARAM_LIST pADI_CDU_Param_List;

    /* CDU Configuration*/
    pADI_CDU_Param_List.cdu_settings[0].cfg_SEL                     =       (ADI_PWR_CDU_CLKIN)CFG0_BIT_CDU0_CFG0_SEL_VALUE;
    pADI_CDU_Param_List.cdu_settings[0].cfg_EN                      =       true;

    pADI_CDU_Param_List.cdu_settings[1].cfg_SEL                     =       (ADI_PWR_CDU_CLKIN)CFG0_BIT_CDU0_CFG1_SEL_VALUE;
    pADI_CDU_Param_List.cdu_settings[1].cfg_EN                      =       true;

    /* CGU0 Configuration*/
    pADI_CGU_Param_List.cgu0_settings.clocksettings.ctl_MSEL        =       (uint32_t)CFG0_BIT_CGU0_CTL_MSEL;
    pADI_CGU_Param_List.cgu0_settings.clocksettings.ctl_DF          =       (uint32_t)CFG0_BIT_CGU0_CTL_DF;
    pADI_CGU_Param_List.cgu0_settings.clocksettings.div_CSEL        =       (uint32_t)CFG0_BIT_CGU0_DIV_CSEL;
    pADI_CGU_Param_List.cgu0_settings.clocksettings.div_SYSSEL      =       (uint32_t)CFG0_BIT_CGU0_DIV_SYSSEL;
    pADI_CGU_Param_List.cgu0_settings.clocksettings.div_S0SEL       =       (uint32_t)CFG0_BIT_CGU0_DIV_S0SEL;
    pADI_CGU_Param_List.cgu0_settings.clocksettings.div_S1SEL       =       (uint32_t)CFG0_BIT_CGU0_DIV_S1SEL;
    pADI_CGU_Param_List.cgu0_settings.clocksettings.divex_S1SELEX   =       (uint32_t)CFG0_BIT_CGU0_DIV_S1SELEX;
    pADI_CGU_Param_List.cgu0_settings.clocksettings.div_DSEL        =       (uint32_t)CFG0_BIT_CGU0_DIV_DSEL;
    pADI_CGU_Param_List.cgu0_settings.clocksettings.div_OSEL        =       (uint32_t)CFG0_BIT_CGU0_DIV_OSEL;
    pADI_CGU_Param_List.cgu0_settings.clkin                         =       (uint32_t)CFG0_BIT_CGU0_CLKIN;
    pADI_CGU_Param_List.cgu0_settings.enable_IDLE                   =       false;
    pADI_CGU_Param_List.cgu0_settings.enable_SCLK1ExDiv             =       true;

#if __ADI_HAS_CGU1__
    /* CGU1 Configuration --Not used--*/
    pADI_CGU_Param_List.cgu1_settings.clkin                         =       (uint32_t)0;
#endif

    /* Initialize all the clocks*/
    if(adi_pwr_ClockInit(&pADI_CGU_Param_List, &pADI_CDU_Param_List) != ADI_PWR_SUCCESS)
    {
       /* Return non-zero */
       return 1u;
    }

    /*Return zero as there are no errors*/
    return 0u;
}
#ifdef _MISRA_RULES
#pragma diag(pop)
#endif

/*@}*/

