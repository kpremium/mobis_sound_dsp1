/****************************************************************************
Copyright (c), 2013-2015 - Analog Devices Inc. All Rights Reserved.
This software is proprietary & confidential to Analog Devices, Inc.
and its licensors.
*****************************************************************************

Title: SigmaStudio for SHARC API

Description: Contains structures and defines that are applicable/useful for 
linking the SigmaStudio module to the application

*****************************************************************************/


#ifndef  __ADI_SS_SSN_H__
#define  __ADI_SS_SSN_H__


/*=============  I N C L U D E S   =============*/

#include <adi_types.h>
#include "adi_ss_communication.h"


/*==============  D E F I N E S  ===============*/

/* Define to link header file and library */
#define adi_ss_create                   (adi_ss_create_4_6)


/* Generic Constants usable in both C and ASM */
#define E_ADI_SS_SUCCESS                (0U) 
#define E_ADI_SS_FAILED                 (1U) 
#define E_ADI_SS_INSUFFICIENT_MEMORY    (2U)
#define E_ADI_SS_PAUSED                 (3U)
#define E_ADI_SS_INVALID_SCHEMATIC      (4U)
#define E_ADI_SS_PROCESS_SKIP           (5U)


#define E_ADI_SSN_STATE_CREATED         (0x70000000)
#define E_ADI_SSN_STATE_INITED          (0x70000001)
#define E_ADI_SSN_STATE_CODE_READY      (0x70000002)
#define E_ADI_SSN_STATE_ERROR           (0x70000003)
#define E_ADI_SSN_STATE_PROGRESSING     (0x70000004)
#define E_ADI_SSN_STATE_PARAM_READY     (0x70000005)

#define SS_MEM_BLOCK_SSN_PVT		    (0U)		/*!< Memory Block for the SSN Private Structure elements */
#define SS_MEM_BLOCK_CODE			    (1U)		/*!< Memory Block for Code Memory from the SMAP */
#define SS_MEM_BLOCK_COMMN			    (2U)		/*!< Memory Block for Communication handling */
#define SS_MEM_BLOCK_PARAM_SL		    (3U)		/*!< Memory Block for temporary storage of the Safeload parameters */
#define SS_MEM_BLOCK_STATE			    (4U)		/*!< Memory Block for State Memory from the SMAP */
#define SS_MEM_BLOCK_PARAM_NSL		    (5U)		/*!< Memory Block for Parameter Memory from the SMAP */
#define SS_MEM_BLOCK_EXT_PRE_STATE	    (6U)		/*!< Memory Block for Extended Precision State Memory from the SMAP */
#define SS_MEM_BLOCK_CODE_B			    (7U)		/*!< Memory Block for CodeB Memory from the SMAP */
#define SS_MEM_BLOCK_STATE_B		    (8U)		/*!< Memory Block for StateB Memory from the SMAP */
#define SS_MEM_BLOCK_STATE_C		    (9U)		/*!< Memory Block for StateC Memory from the SMAP */
#define SS_MEM_BLOCK_SHARED_STATE	    (10U)	    /*!< Memory Block for Shared State Memory from the SMAP */


/*=============  D A T A    T Y P E S   =============*/

#if defined(_LANGUAGE_C)

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* C-specific definitions  */

typedef float32_t   adi_ss_sample_t;    
typedef uint32_t    adi_ss_bitstream_t;    
typedef void*       ADI_SS_SSN_HANDLE;  


/*
**  Enumeration: __SSResult
**  Return error types
*/
        
    typedef enum __SSResult 
    {  
        ADI_SS_SUCCESS             = E_ADI_SS_SUCCESS,
        ADI_SS_FAILED              = E_ADI_SS_FAILED,
        ADI_SS_INSUFFICIENT_MEMORY = E_ADI_SS_INSUFFICIENT_MEMORY,
        ADI_SS_PAUSED              = E_ADI_SS_PAUSED,
        ADI_SS_INVALID_SCHEMATIC   = E_ADI_SS_INVALID_SCHEMATIC,
        ADI_SS_PROCESS_SKIP        = E_ADI_SS_PROCESS_SKIP  
              
    } ADI_SS_RESULT;  
    
/*
**  Enumeration: __SSState
**  Return internal states
*/

    typedef enum __SSState 
    { 
        ADI_SSN_STATE_CREATED      = E_ADI_SSN_STATE_CREATED,
        ADI_SSN_STATE_INITED       = E_ADI_SSN_STATE_INITED,
        ADI_SSN_STATE_CODE_READY   = E_ADI_SSN_STATE_CODE_READY,
        ADI_SSN_STATE_ERROR        = E_ADI_SSN_STATE_ERROR,
        ADI_SSN_STATE_PROGRESSING  = E_ADI_SSN_STATE_PROGRESSING,
        ADI_SSN_STATE_PARAM_READY  = E_ADI_SSN_STATE_PARAM_READY

    } ADI_SS_STATE;

/*
**  Structure: __SSnConfig
**  SigmaStudioModule configuration structure
*/

    typedef struct __SSnConfig
    {
        uint32_t               nBlockSize;
        uint32_t               nInChannels;
        uint32_t               nOutChannels;
        uint32_t               bSkipProcessOnCRCError;
        uint32_t               bSkipInitialDownload;
        ADI_SS_COMM_HANDLE     hSSComm;
#if defined(__ADSP215xx__)
        uint32_t               nInitNoWait;
        bool				   bClearUnusedOutput;
        ADI_SS_PROC_ID         eProcID;
#endif        
    } ADI_SS_CONFIG;

/*
**  Structure: __SSnBackChannel
**  SigmaStudioModule Back Channel structure
*/

    typedef struct __SSnBackChannel
    {
        uint32_t               nDatSize;
        uint32_t               nCommandName;
        uint32_t               nData;    
        uint32_t               nStateOffset; 
        
    } ADI_SSN_BKCHNL_BLOCK; 
   
/*
**  Structure: __SSnProperties
**  SigmaStudioModule configuration structure
*/

    typedef struct __SSnProperties
    {
        int32_t                bSSnUpdate;
        uint32_t               nSSnCodeSize;
        uint32_t               nStatusField;
#ifndef __ADSP215xx__
        int32_t                bCommErrStatus;
        uint32_t               bCustomCmdRcvd;        
        uint32_t              *pSSnBuf;
        uint32_t               nNumBkChnlInfo;
        ADI_SSN_BKCHNL_BLOCK  *pSSnBkChnlInfo;
#endif        
        uint32_t               nSSBlockSize;
        uint32_t               nSSInChannels;
        uint32_t               nSSOutChannels;
        
    } ADI_SS_SSNPROPERTIES;
    
/*
**  Structure: __SSnVersion
**  SigmaStudioModule Library version information accessible at run-time.
*/    
    typedef struct __SSnVersion
    {
        unsigned int nVersionum;
        unsigned int nAPIVersionum;
    } ADI_SS_SSNVERSION_INFO;

    extern ADI_SS_SSNVERSION_INFO adi_ss_module_info;
    
/*=======  P U B L I C   P R O T O T Y P E S  ========*/
    
/* SigmaStudio Module Creation */

ADI_SS_RESULT adi_ss_create(ADI_SS_SSN_HANDLE           *phSSn,
                            const ADI_SS_MEM_MAP        *pMemMap);


/* SigmaStudio Module Initialization */

ADI_SS_RESULT adi_ss_init(ADI_SS_SSN_HANDLE              hSSn, 
                          const ADI_SS_CONFIG           *pConfig);


/* SigmaStudio Module Processing */

ADI_SS_RESULT adi_ss_schematic_process(ADI_SS_SSN_HANDLE           hSSn,
                             int32_t                     num_input_samples_per_chan,
                             adi_ss_sample_t            *input_data[],
                             adi_ss_sample_t            *output_data[],
                             ADI_SS_SSNPROPERTIES       *pProperties);


/* SigmaStudio Module Extracting Properties */

ADI_SS_RESULT adi_ss_getProperties(ADI_SS_SSN_HANDLE     hSSn, 
                                   ADI_SS_SSNPROPERTIES *pProperties);
                             

/* SigmaStudio Module Reseting */
                             
ADI_SS_RESULT adi_ss_reset(ADI_SS_SSN_HANDLE             hSSn, 
                           const  ADI_SS_CONFIG         *pConfig);   
                           
                           
/* SigmaStudio Module Clear State Memory */
                             
ADI_SS_RESULT adi_ss_clearState(ADI_SS_SSN_HANDLE        hSSn);  


/* API for updating SSn parameters */
ADI_SS_RESULT adi_ss_updateParam(ADI_SS_SSN_HANDLE        hSSn,
                                 uint32_t                 *pParamDataAddr,
                                 uint32_t                 nSSnParamMemOffset,
                                 uint32_t                 nNumParams);                                                                                
                             
/* API for reading SSn parameters */
ADI_SS_RESULT adi_ss_readParam(ADI_SS_SSN_HANDLE        hSSn,
                               uint32_t                 *pBuffer,
                               uint32_t                 nSSnParamMemOffset,
                               uint32_t                 nNumParams);                                 
                             
#ifdef __cplusplus
}
#endif /* __cplusplus */

#else /* not _LANGUAGE_C */

/* Assembler-specific definitions */

#endif /* not _LANGUAGE_C */
    
#endif /* __ADI_SS_SSN_H__ */

/*
** EOF:
*/

