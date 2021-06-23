/*****************************************************************************
 * SYSTEM_PWR.h
 *****************************************************************************/

#ifndef __SYSTEM_PWR_H__
#define __SYSTEM_PWR_H__

/**********************************************************************************************
 *                      CGU Configuration Number 0
 **********************************************************************************************/

#define CFG0_BIT_CGU0_CLKIN                                24576000 /*!< Macro for SYS_CLKIN */
#define CFG0_BIT_CGU1_CLKIN                                25000000 /*!< Macro for SYS_CLKIN */
/* SPI(0-2) CLOCK SOURCE */
#define CFG0_BIT_CDU0_CFG0_SEL_VALUE                       0        /*!< Macro for CDU CFG0 Selection */
/* DDR CLOCK */
#define CFG0_BIT_CDU0_CFG1_SEL_VALUE                       0        /*!< Macro for CDU CFG1 Selection */

/**********************************************************************************************
 *                      CGU Configuration Number 0 Register Values
 **********************************************************************************************/
/*****************************************CGU0_CTL*********************************************/
#define CFG0_BIT_CGU0_CTL_DF                               0        /*!< Macro for CGU0 DF bit */
#define CFG0_BIT_CGU0_CTL_MSEL                             80       /*!< Macro for CGU0 MSEL field */
/*****************************************CGU0_DIV*********************************************/
#define CFG0_BIT_CGU0_DIV_CSEL                             2        /*!< Macro for CGU0 CSEL field */
#define CFG0_BIT_CGU0_DIV_SYSSEL                           4        /*!< Macro for CGU0 SYSSEL field */
#define CFG0_BIT_CGU0_DIV_S0SEL                            4        /*!< Macro for CGU0 S0SEL field */
#define CFG0_BIT_CGU0_DIV_S1SEL                            2        /*!< Macro for CGU0 S1SEL field */
#define CFG0_BIT_CGU0_DIV_DSEL                             4        /*!< Macro for CGU0 DSEL field */
#define CFG0_BIT_CGU0_DIV_OSEL                             16       /*!< Macro for CGU0 OSEL field */
/*****************************************CGU0_DIVEX*******************************************/
#define CFG0_BIT_CGU0_DIV_S1SELEX                          6        /*!< Macro for CGU0 S1SELEX field */
/**********************************************************************************************/

uint32_t SYSTEM_PWR_Init(void);

uint32_t GetSClk0PWR(void);

#endif /* __SYSTEM_PWR_H__ */
