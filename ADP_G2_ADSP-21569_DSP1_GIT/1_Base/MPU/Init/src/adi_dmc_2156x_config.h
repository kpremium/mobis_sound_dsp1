/*
 **
 ** Source file generated on August 27, 2018 at 12:04:48.
 **
 ** Copyright (C) 2018 Analog Devices Inc., All Rights Reserved.
 **
 ** This file is generated automatically based upon the options selected in
 ** the DMC Initialization configuration dialog. Changes to this configuration should be made by
 ** changing the appropriate options rather than editing this file.
 **
 */

/*!
 * @file     adi_dmc_2156x_config.h
 *
 * @brief    DMC controller configuration header file generated by plugin
 *
 * @version  $Revision: 0 $
 *
 * @date     $Date: 2018-04-01 08:18:37 -0400 (Fri, 01 Apr 2018) $
 *
 * @details
 *           This is the header file for the DMC controllers initialization
 */

#ifndef ADI_DMC_2156X_CONFIG_H
#define ADI_DMC_2156X_CONFIG_H

#include "config.h"
#include "adi_dmc.h"

#ifdef __cplusplus
extern "C" {
#endif

#if CONFIG_DMC0
/* Initializes DMC0 controller */
uint32_t adi_dmc_cfg0_init(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* ADI_DMC_2156X_CONFIG_H */
/*@}*/
