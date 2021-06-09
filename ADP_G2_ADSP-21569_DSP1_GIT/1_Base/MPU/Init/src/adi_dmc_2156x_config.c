/*
 **
 ** Source file based on a file originally generated on August 27 2018.
 **
 ** Copyright (C) 2018-2019 Analog Devices Inc., All Rights Reserved.
 **
 */

/** @addtogroup Init_Preload_2156x Processor Initialization Code
 *  @{
 *
 */

/*!
 * @file     adi_dmc_2156x_config.c
 *
 * @brief    DMC controller configuration source.
 *
 * @version  2.9.2
 *
 * @date     12-Dec-2019
 *
 * @details  This is the source file for the DMC controller initialization
 */

#include <sys/platform.h>
#include <stdint.h>
#include "adi_dmc_2156x_config.h"

#if CONFIG_DMC0 == ISSI_8Gb_DDR3_500MHZ

/* DMC0 setup for the ADSP-21569 EZ-KIT :
 * - uses a single 8GB IS43TR16512BL-125KBL DDR3 chip configured for
 *   500 MHz DCLK.
 */

/*****************************************DMC_CTL**********************************************/
/*! enable DDR3 controller */
#define CFG0_BIT_DMC_CTL_DDR3EN                     1ul
/*! Constant value, should not be altered*/
#define CFG0_BIT_DMC_CTL_RDTOWR                     5ul

#define CFG0_REG_DMC_CTL_VALUE      ((CFG0_BIT_DMC_CTL_DDR3EN<<BITP_DMC_CTL_DDR3EN)|(BITM_DMC_CTL_INIT)|(CFG0_BIT_DMC_CTL_RDTOWR<<BITP_DMC_CTL_RDTOWR))

/*****************************************DMC_CFG**********************************************/
/*! DDR3 memory size selected */
#define CFG0_BIT_DMC_CFG_SDRSIZE                    (ENUM_DMC_CFG_SDRSIZE8G)

/*! Value for the DMC_CFG (DMC Configuration) register. */
#define CFG0_REG_DMC_CFG_VALUE \
  (ENUM_DMC_CFG_IFWID16     | /* Interface Width - always 16-bit */ \
   ENUM_DMC_CFG_SDRWID16    | /* SDRAM Width - always 16-bit */ \
   CFG0_BIT_DMC_CFG_SDRSIZE | /* SDRAM Size */ \
   ENUM_DMC_CFG_EXTBANK1)     /* External Banks - always 1 bank */

/*****************************************DMC_DLLCTL*******************************************/
/*! DLL Calibration RD Count */
#define ADI_DMC_PARAM_DLLCOUNT                    240ul

/*! Data Cycles - ceil( 15ns/DDRclock in Hz) */
#define CFG0_REG_DMC_DATACYC                        8ul

/*! Value for the DMC_DLLCTL (DMC DLL Control) register. */
#define CFG0_REG_DMC_DLLCTL_VALUE \
  ((ADI_DMC_PARAM_DLLCOUNT<<BITP_DMC_DLLCTL_DLLCALRDCNT) | \
   (CFG0_REG_DMC_DATACYC<<BITP_DMC_DLLCTL_DATACYC))

/*****************************************DMC_TR0**********************************************/
/*! Trcd value in DDR clock cycles*/
#define CFG0_BIT_DMC_TR0_TRCD                       7ul
/*! Twtr value in DDR clock cycles*/
#define CFG0_BIT_DMC_TR0_TWTR                       4ul
/*! Trp value in DDR clock cycles*/
#define CFG0_BIT_DMC_TR0_TRP                        7ul
/*! Tras value in DDR clock cycles*/
#define CFG0_BIT_DMC_TR0_TRAS                       19ul
/*! Trc value in DDR clock cycles*/
#define CFG0_BIT_DMC_TR0_TRC                        26ul
/*! Tmrd value in DDR clock cycles*/
#define CFG0_BIT_DMC_TR0_TMRD                       4ul

#define CFG0_REG_DMC_TR0_VALUE      ((CFG0_BIT_DMC_TR0_TRCD<<BITP_DMC_TR0_TRCD)|(CFG0_BIT_DMC_TR0_TWTR<<BITP_DMC_TR0_TWTR)|(CFG0_BIT_DMC_TR0_TRP<<BITP_DMC_TR0_TRP)|(CFG0_BIT_DMC_TR0_TRAS<<BITP_DMC_TR0_TRAS)|(CFG0_BIT_DMC_TR0_TRC<<BITP_DMC_TR0_TRC)|(CFG0_BIT_DMC_TR0_TMRD<<BITP_DMC_TR0_TMRD))

/*****************************************DMC_TR1**********************************************/
/*! Tref value in DDR clock cycles*/
#define CFG0_BIT_DMC_TR1_TREF                        3900ul
/*! Trfc value in DDR clock cycles*/
#define CFG0_BIT_DMC_TR1_TRFC                        175ul
/*! Trrd value in DDR clock cycles*/
#define CFG0_BIT_DMC_TR1_TRRD                        5ul

#define CFG0_REG_DMC_TR1_VALUE      ((CFG0_BIT_DMC_TR1_TREF<<BITP_DMC_TR1_TREF)|(CFG0_BIT_DMC_TR1_TRFC<<BITP_DMC_TR1_TRFC)|(CFG0_BIT_DMC_TR1_TRRD<<BITP_DMC_TR1_TRRD))

/*****************************************DMC_TR2**********************************************/

/*! Tfaw value in DDR clock cycles*/
#define CFG0_BIT_DMC_TR2_TFAW                          25ul
/*! Trtp value in DDR clock cycles*/
#define CFG0_BIT_DMC_TR2_TRTP                          4ul
/*! Twr value in DDR clock cycles*/
#define CFG0_BIT_DMC_TR2_TWR                           8ul
/*! Txp value in DDR clock cycles*/
#define CFG0_BIT_DMC_TR2_TXP                           4ul
/*! Tcke value in DDR clock cycles*/
#define CFG0_BIT_DMC_TR2_TCKE                          3ul

#define CFG0_REG_DMC_TR2_VALUE      ((CFG0_BIT_DMC_TR2_TFAW<<BITP_DMC_TR2_TFAW)|(CFG0_BIT_DMC_TR2_TRTP<<BITP_DMC_TR2_TRTP)|(CFG0_BIT_DMC_TR2_TWR<<BITP_DMC_TR2_TWR)|(CFG0_BIT_DMC_TR2_TXP<<BITP_DMC_TR2_TXP)|(CFG0_BIT_DMC_TR2_TCKE<<BITP_DMC_TR2_TCKE))

/****************************************DMC  DLLCTLCFG**********************************************/

/*! The DMC_CFG and DMC_DLLCTL values are combined for ulDDR_DLLCTLCFG field. */
#define CFG0_REG_DDR_DLLCTLCFG \
  (CFG0_REG_DMC_CFG_VALUE |    \
   (CFG0_REG_DMC_DLLCTL_VALUE<<16))

/****************************************DMC  MR0**********************************************/

/*! Constant value, should not be altered*/
#define CFG0_BIT_DMC_MR0_BLEN                           0ul
/*! CAS Read latency bit 0 value*/
#define CFG0_BIT_DMC_MR0_CL0                            0ul
/*! CAS Read latency [2:1] bits*/
#define CFG0_BIT_DMC_MR0_CL                             3ul
/*! Constant value, should not be altered*/
#define CFG0_BIT_DMC_MR0_DLLRST                         1ul
/*! Write recovery value*/
#define CFG0_BIT_DMC_MR0_WRRECOV                        4ul

#define CFG0_REG_DMC_MR0_VALUE             ((CFG0_BIT_DMC_MR0_BLEN<<BITP_DMC_MR_BLEN)|(CFG0_BIT_DMC_MR0_CL0<<BITP_DMC_MR_CL0)|(CFG0_BIT_DMC_MR0_CL<<BITP_DMC_MR_CL)|(CFG0_BIT_DMC_MR0_DLLRST<<BITP_DMC_MR_DLLRST)|(CFG0_BIT_DMC_MR0_WRRECOV<<BITP_DMC_MR_WRRECOV))

/****************************************DMC  MR1**********************************************/
/*! Constant value, should not be altered*/
#define CFG0_BIT_DMC_MR1_DLLEN                            0ul
/*! Bit 0 of the output DS*/
#define CFG0_BIT_DMC_MR1_DIC0                             0ul
/*! Bit 0 of the ODT*/
#define CFG0_BIT_DMC_MR1_RTT0                             0ul
/*! Additive latency setting*/
#define CFG0_BIT_DMC_MR1_AL                               0ul
/*! Bit 1 of the output DS*/
#define CFG0_BIT_DMC_MR1_DIC1                             0ul
/*! Bit 1 of the ODT*/
#define CFG0_BIT_DMC_MR1_RTT1                             1ul
/*! Bit 2 of the ODT*/
#define CFG0_BIT_DMC_MR1_RTT2                             0ul
#define CFG0_BIT_DMC_MR1_TDQS                             0ul
#define CFG0_BIT_DMC_MR1_QOFF                             0ul

#define CFG0_REG_DMC_MR1_VALUE       ((CFG0_BIT_DMC_MR1_DLLEN<<BITP_DMC_MR1_DLLEN)|(CFG0_BIT_DMC_MR1_DIC0<<BITP_DMC_MR1_DIC0)|(CFG0_BIT_DMC_MR1_RTT0<<BITP_DMC_MR1_RTT0)|(CFG0_BIT_DMC_MR1_AL<<BITP_DMC_MR1_AL)|(CFG0_BIT_DMC_MR1_DIC1<<BITP_DMC_MR1_DIC1)|(CFG0_BIT_DMC_MR1_RTT1<<BITP_DMC_MR1_RTT1)|(CFG0_BIT_DMC_MR1_RTT2<<BITP_DMC_MR1_RTT2)|(CFG0_BIT_DMC_MR1_TDQS<<BITP_DMC_MR1_TDQS)|(CFG0_BIT_DMC_MR1_QOFF<<BITP_DMC_MR1_QOFF))

/**************************************** DMC  MR2MR3**********************************************/
/*! CAS write latency*/
#define CFG0_BIT_DMC_MR2_CWL                              1ul
#define CFG0_REG_DMC_MR2MR3      (((CFG0_BIT_DMC_MR2_CWL<<BITP_DMC_MR2_CWL))<<16)

#define CFG0_REG_DMC_MRMR1        (CFG0_REG_DMC_MR1_VALUE|(CFG0_REG_DMC_MR0_VALUE<<16ul))

/*! Core clock and DCLK ratio*/
#define csel_dsel_r                                       10ul


/**
 * @brief    Initializes DMC controller.
 *
 * @return   Status
 *           - 0: Successful in initializing DMC controller.
 *           - 1: Error.
 */
uint32_t adi_dmc_cfg0_init(void)
{
    uint32_t status = 0u;

    static ADI_DMC_CONFIG config500 =
    {
            CFG0_REG_DDR_DLLCTLCFG,
            CFG0_REG_DMC_MR2MR3,
            CFG0_REG_DMC_CTL_VALUE,
            CFG0_REG_DMC_MRMR1,
            CFG0_REG_DMC_TR0_VALUE,
            CFG0_REG_DMC_TR1_VALUE,
            CFG0_REG_DMC_TR2_VALUE,
            0x00786464ul,
            0ul,
            0x70000000ul
    };

    /* Initialize DMC PHY registers */
    adi_dmc_phy_calibration(&config500, csel_dsel_r);

    /* Initialize DMC Controller */
    if(adi_dmc_ctrl_init(&config500, csel_dsel_r) != ADI_DMC_SUCCESS)
    {
       /* Assign error status return value */
       status = 1u;
    }

    return status;
}

#endif /* CONFIG_DMC0 == ISSI_8Gb_DDR3_500MHZ */
/*@}*/
