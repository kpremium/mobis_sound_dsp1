/****************************************************************************
Copyright (c), 2014-2015 - Analog Devices Inc. All Rights Reserved.
This software is proprietary & confidential to Analog Devices, Inc.
and its licensors.
*****************************************************************************
 * @file:    adi_ss_communication.h
 * @brief:   Contains structures and defines that are required for
             setting up the communication between SigmaStudio host 
             and Griffin. This component handles the protocol parsing and 
             the actual physical communication is part of 
             adi_ss_connection.h
 * @version: $Revision$
 * @date:    $Date$
 * Developed by: Automotive Software and Systems team, Bangalore, India
*****************************************************************************/
/*! \addtogroup ADI_SS_COMM
 *  @{
 */
#ifndef __ADI_SS_COMMUNICATION_H__
#define __ADI_SS_COMMUNICATION_H__


/*=============  I N C L U D E S   =============*/
#include "adi_ss_common.h"

/*==============  D E F I N E S  ===============*/
#ifdef __ADSPSHARC__
#define ADI_SS_COMM_MEMSIZE             (370u)     /*!< Memory required for communication component */
#else
#define ADI_SS_COMM_MEMSIZE             (370u)     /*!< Memory required for communication component */
#endif

#define E_ADI_SS_COMM_SUCCESS           (0)         /*!< Communication success */
#define E_ADI_SS_COMM_FAILED            (-1)        /*!< Communication failure */
#define E_ADI_SS_COMM_INSUFF_MEMORY     (-2)        /*!< Insufficient memory for creation of communication component */
#define E_ADI_SS_COMM_CRC_ERROR         (-3)        /*!< CRC error */

#define E_ADI_COMM_PROP_SSN_HANDLE      (0x70000001U) /*!<Enumeration for setting SSN handle property */
/*=============  D A T A    T Y P E S   =============*/
#if defined(_LANGUAGE_C)

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*! \enum ADI_SS_COMM_RESULT
Enumeration for communication result.
*/
typedef enum ADI_SS_COMM_RESULT 
{  
    ADI_SS_COMM_SUCCESS               = E_ADI_SS_COMM_SUCCESS,
    ADI_SS_COMM_FAILED                = E_ADI_SS_COMM_FAILED,
    ADI_SS_COMM_INSUFFICIENT_MEMORY   = E_ADI_SS_COMM_INSUFF_MEMORY,
    ADI_SS_COMM_CRC_ERROR             = E_ADI_SS_COMM_CRC_ERROR
}ADI_SS_COMM_RESULT;  


/*! \enum ADI_COMM_PROPERTY_ID
Enumeration for setting communication properties.
*/
typedef enum ADI_COMM_PROPERTY_ID
{
	ADI_COMM_PROP_SSN_HANDLE              = E_ADI_COMM_PROP_SSN_HANDLE
}ADI_COMM_PROPERTY_ID;


typedef void *ADI_SS_COMM_HANDLE;                                   /*!< Communication component handle */
typedef void (*ADI_SS_COMM_APP_ISR_CB)(ADI_SS_COMM_HANDLE hSSComm); /*!< Type define for application ISR callback 
                                                                         if registered */
typedef void (*ADI_SS_COMM_CMD4_CB)();                              /*!< Type define for CMD4 callback */
typedef void (*ADI_SS_COMM_SMAP_CB)(ADI_SS_PROC_ID eProcID);              /*!< Type define for callback on receiving SMAP */

/*! \struct ADI_SS_COMM_CONFIG
SigmaStudio Communication component configuration Structure
*/
typedef struct ADI_SS_COMM_CONFIG 
{
    bool                	bCRCBypass;                   	 /*!< Boolean flag to indicate bypassing of CRC check */
    bool                    bFullPacketCRC;                      /*!< Boolean flag to indicate whether CRC is required 
                                                                      for the entire packet */
    ADI_SS_COMM_CMD4_CB 	pfCommCmd4CallBack;           	 /*!< CMD 4 call back function */
    ADI_SS_COMM_APP_ISR_CB  pfSPIRxIsrCallBack;                  /*!< Application ISR callback for Rx. Only if this is 
                                                                      not NULL */
    ADI_SS_COMM_APP_ISR_CB  pfSPITxIsrCallBack;                  /*!< Application ISR callback for Tx. Only if this is 
                                                                      not NULL */
    ADI_SS_COMM_SMAP_CB     pfCommSMAPCallBack;       	     /*!< Application callback on receiving SMAP */
    void*				    hConnectionHandle;		  		 	/*!< Handle to the Connection Internal Structure */
    ADI_SS_MEM_SMAP         *pMemSMap[MAX_NUMBER_OF_PROCESSORS];	/*!< SMAP pointers for each of the cores */
    ADI_SS_BACKCH_INFO		*pBkChnlInfo[MAX_NUMBER_OF_PROCESSORS]; /*!< Pointers to IPC Backchannel info */
}ADI_SS_COMM_CONFIG;

/*! \struct ADI_SS_COMM_BACKCH_INFO
BackChannel information structure which needs to be populated
*/
typedef struct ADI_SS_COMM_BACKCH_INFO
{
    uint32_t            nProc;                        /*!< Processor ID for which this back channel data belongs. 
                                                           This field is currently ignored */
    uint32_t            nCommandName;                 /*!< Back channel command */
    uint32_t            *pInData;                     /*!< Pointer to back channel data */    
    uint32_t            nInDataSize;                  /*!< Size of the back channel payload data in words */
    uint32_t            *pOutPacket;                  /*!< Pointer to back channel packet which should be transmitted */
}ADI_SS_COMM_BACKCH_INFO; 

/*! \struct ADI_SS_COMM_PROPERTIES
SigmaStudio Communication component properties Structure
*/
typedef struct ADI_SS_COMM_PROPERTIES
{
	/* These variables are used by the GetProperties function to get communication properties */
    bool                       bCommError;            /*!< Flag indicating communication error */
    bool                       bCustomCmdRcvd;        /*!< This flag indicates that a custom command is received */
    uint32_t                   *pSSnBuf;              /*!< This pointer contains the data received via custom command */
    ADI_SS_MEM_SMAP            *pMemSMap;             /*!< Pointer to SMAP structure obtained as a packet */

    /*These variables are used by the SetProperties function to set communication properties */
    uint32_t                  nProcId;               /*!< Processsor ID */
    uint32_t                  nNumProcBlocks;        /*!< Number of instances/processor blocks. */
    void*                     haSSnHandle[MAX_NUMBER_OF_PROCESSORS][ADI_SS_FW_MAX_PROC_BLOCKS]; /*!< Handle to SSn properties*/
}ADI_SS_COMM_PROPERTIES;

/*=======  P U B L I C   P R O T O T Y P E S  ========*/

/* SigmaStudio Communication Module creation and initialization Initialization */
ADI_SS_COMM_RESULT adi_ss_comm_Init(ADI_SS_MEM_BLOCK *pMemBlk, ADI_SS_COMM_CONFIG *pCommConfig, ADI_SS_COMM_HANDLE *phSSComm);

/* This function parses a single communication word obtained from the host and updates an internal state. */
ADI_SS_COMM_RESULT adi_ss_comm_Parse(ADI_SS_COMM_HANDLE hSSComm, uint32_t nData);

/* SigmaStudio Communication Module Reset */
ADI_SS_COMM_RESULT adi_ss_comm_Reset(ADI_SS_COMM_HANDLE hSSComm);

/* API for getting current communication properties */
ADI_SS_COMM_RESULT adi_ss_comm_GetProperties(ADI_SS_COMM_HANDLE hSSComm, ADI_SS_COMM_PROPERTIES *pCommProperties);

/* This API packetizes the back-channel data for transmission */
ADI_SS_COMM_RESULT adi_ss_comm_Packetize(ADI_SS_COMM_HANDLE hSSComm, 
                                         ADI_SS_COMM_BACKCH_INFO *pBkChInfo, 
                                         uint32_t *pPacketSzInWords
                                         );
/* API for setting communication properties */
ADI_SS_COMM_RESULT adi_ss_comm_SetProperties(ADI_SS_COMM_HANDLE hSSComm, ADI_COMM_PROPERTY_ID ePropId, ADI_SS_COMM_PROPERTIES *pCommProperties);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#else /* not _LANGUAGE_C */

/* Assembler-specific definitions */

#endif /* not _LANGUAGE_C */

#endif /* __ADI_SS_COMMUNICATION_H__ */
/*
 *
 * EOF: $URL: $
 *
*/
