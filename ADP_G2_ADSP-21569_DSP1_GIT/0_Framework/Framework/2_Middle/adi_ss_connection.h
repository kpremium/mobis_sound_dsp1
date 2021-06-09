/****************************************************************************
Copyright (c), 2014 - Analog Devices Inc. All Rights Reserved.
This software is proprietary & confidential to Analog Devices, Inc.
and its licensors.
*****************************************************************************
 * @file:    adi_ss_connection.h
 * @brief:   Contains structures and defines that are required for
             setting up the physical connection for communication.
 * @version: $Revision$
 * @date:    $Date$
 * Developed by: Automotive Software and Systems team, Bangalore, India
*****************************************************************************/
/*! \addtogroup ADI_SS_CONNECTION
 *  @{
 */
#ifndef __ADI_SS_CONNECTION_H__
#define __ADI_SS_CONNECTION_H__


/*=============  I N C L U D E S   =============*/
#include <stddef.h>
#include "adi_ss_common.h"
#include "adi_ss_communication.h"


/*==============  D E F I N E S  ===============*/
#ifdef __ADSPSHARC__
#define ADI_SS_CONNECTION_MEMSIZE             (168u)    /*!< Memory required for connection component */
#else
#define ADI_SS_CONNECTION_MEMSIZE             (168u)    /*!< Memory required for connection component */
#endif

#define ADI_SS_SPI0_DEVICE                    (0u)
#define ADI_SS_SPI1_DEVICE                    (1u)

#define NUMBER_RX_BUFFERS                     (2u)

#define E_ADI_SS_CONNECTION_SUCCESS           (0u)          /*!< Connection success */
#define E_ADI_SS_CONNECTION_FAILED            (-1)          /*!< Connection failure */
#define E_ADI_SS_CONNECTION_INSUFF_MEM        (-2)          /*!< Connection failure because of insufficient memory */
#define E_ADI_SS_CONNECTION_INVALID_CONFIG    (-3)          /*!< Connection failure because of invalid configuration 
                                                                 parameters */

#define E_ADI_SS_CONNECTION_SPI               (0x70000000)  /*!< Connection type SPI */

#define E_ADI_SS_CONFIG_SPI_RX_DMA            (0u)          /*!< Config item for SPI Rx DMA */
#define E_ADI_SS_CONFIG_SPI_TX_DMA            (1u)          /*!< Config item for SPI Tx DMA */

/*=============  D A T A    T Y P E S   =============*/

#if defined(_LANGUAGE_C)

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*! \enum ADI_SS_CONNECTION_RESULT
Enumeration for connection result.
*/
typedef enum ADI_SS_CONNECTION_RESULT 
{  
    ADI_SS_CONNECTION_SUCCESS      = E_ADI_SS_CONNECTION_SUCCESS,
    ADI_SS_CONNECTION_FAILED       = E_ADI_SS_CONNECTION_FAILED,
    ADI_SS_CONNECTION_INSUFF_MEM   = E_ADI_SS_CONNECTION_INSUFF_MEM,
    ADI_SS_CONNECTION_INVALID_CONFIG  = E_ADI_SS_CONNECTION_INVALID_CONFIG
}ADI_SS_CONNECTION_RESULT;  

/*! \enum ADI_SS_CONNECTION_TYPE
Enumeration for connection type.
*/
typedef enum ADI_SS_CONNECTION_TYPE
{
    ADI_SS_CONNECTION_SPI = E_ADI_SS_CONNECTION_SPI
}ADI_SS_CONNECTION_TYPE;

/*! \enum ADI_SS_CONNECTION_CONFIG_ITEM
Enumeration for item to be reconfigured.
*/
typedef enum ADI_SS_CONNECTION_CONFIG_ITEM
{
    ADI_SS_CONFIG_SPI_RX_DMA = E_ADI_SS_CONFIG_SPI_RX_DMA,
    ADI_SS_CONFIG_SPI_TX_DMA = E_ADI_SS_CONFIG_SPI_TX_DMA
}ADI_SS_CONNECTION_CONFIG_ITEM;

typedef void* ADI_SS_CONNECTION_HANDLE;         /*!< Handle to connection component */
typedef void* CONN_ISR;

/*! \struct ADI_SS_CONNECTION_CONFIG
Configuration structure for connection component. This must be populated by the 
application before calling adi_ss_connection_init()
*/
typedef struct ADI_SS_CONNECTION_CONFIG 
{
    /* One time configurable items */
    ADI_SS_CONNECTION_TYPE  eConnectionType;      /*!< Device type */
    uint32_t                nDevId;               /*!< Device number */
    ADI_SS_PROC_ID          eProcID;              /*!< Processor ID  */
    
    CONN_ISR                pfISRRx;              /*!< Rx interrupt service routine function pointer */
    CONN_ISR                pfISRTx;              /*!< Tx interrupt service routine function pointer */
    
    /* Reconfigurable items */
    uint32_t                *pRxAddr;             /*!< Payload receive  address */
    uint32_t                nRxPayloadCnt;        /*!< Receive payload count */
    uint32_t                *pTxAddr;             /*!< Transmit address */
    uint32_t                nTxPayloadCnt;        /*!< Transmit payload count */
}ADI_SS_CONNECTION_CONFIG;

/*=======  P U B L I C   P R O T O T Y P E S  ========*/

/* Connection component API for creating and initializing a physical connection */
ADI_SS_CONNECTION_RESULT adi_ss_connection_Init(ADI_SS_MEM_BLOCK *pMemBlk, ADI_SS_CONNECTION_CONFIG *pConnectionConfig, ADI_SS_CONNECTION_HANDLE *phSSConnection);

/* This API passes a valid communication handle to the connection component */
ADI_SS_CONNECTION_RESULT adi_ss_connection_set_CommHandle(ADI_SS_CONNECTION_HANDLE hSSConnection, ADI_SS_COMM_HANDLE hSSComm);

/* This API enables the SPI Rx */
ADI_SS_CONNECTION_RESULT adi_ss_connection_Enable(ADI_SS_CONNECTION_HANDLE hSSConnection);

/* This API reconfigures the connection component based on the chosen config item */
ADI_SS_CONNECTION_RESULT adi_ss_connection_Reconfigure(ADI_SS_CONNECTION_HANDLE hSSConnection, 
                                                       ADI_SS_CONNECTION_CONFIG_ITEM eConfigItem,
                                                       ADI_SS_CONNECTION_CONFIG *pConnectionConfig
                                                       );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#else /* not _LANGUAGE_C */

/* Assembler-specific definitions */

#endif /* not _LANGUAGE_C */

#endif /* __ADI_SS_CONNECTION_H__ */
/*
 *
 * EOF: $URL:  $
 *
*/
