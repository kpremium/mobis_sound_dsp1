/****************************************************************************
Copyright (c), 2012-2015 - Analog Devices Inc. All Rights Reserved.
This software is proprietary & confidential to Analog Devices, Inc.
and its licensors.
*****************************************************************************
 * @file:    adi_ss_common.h
 * @brief:   Contains common structures and defines.
 * @version: $Revision$
 * @date:    $Date$
 * Developed by: Automotive Software and Systems team, Bangalore, India
*****************************************************************************/
/*! \addtogroup ADI_SS_FW_COMMON
 *  @{
 */

#ifndef _ADI_SS_COMMON_H_ 
#define _ADI_SS_COMMON_H_


/*================  I N C L U D E S  ================*/
#include <adi_types.h>


/*==============  D E F I N E S  ===============*/

#define ADI_SS_MAX_MEM_BLOCKS       (15)       		/*!< Maximum number of memory blocks */


#if defined(__ADSPSC5xx__)    /* __ADSPSC5xx__ */
#define MAX_NUMBER_OF_PROCESSORS    (3U)	   			/*!< Maximum number of processors */
#define E_PROCESSOR_ARM             (0)	   			/*!< Processor ARM */
#define E_PROCESSOR_SH0             (1)     		/*!< Processor SHARC Core 0 */
#define E_PROCESSOR_SH1             (2)     		/*!< Processor SHARC Core 1 */

#elif defined(__ADSP215xx__) && (__NUM_ARM_CORES__==0)

#ifdef __ADSP2156x__
#define NUMBER_PROCESSING_CORES		(1)				/*!< Total number of processing cores */
#define MAX_NUMBER_OF_PROCESSORS    (1)	   			/*!< Maximum number of processors */
#define E_PROCESSOR_SH0             (0)     		/*!< Processor SHARC Core 0 */
#else

#define MAX_NUMBER_OF_PROCESSORS    (2)	   			/*!< Maximum number of processors */
#define E_PROCESSOR_SH0             (0)     		/*!< Processor SHARC Core 0 */
#define E_PROCESSOR_SH1             (1)     		/*!< Processor SHARC Core 1 */

#endif
#endif
#ifndef __ADSP2156x__
#define NUMBER_PROCESSING_CORES		(2)				/*!< Total number of processing cores */
#endif
#define E_PROCESSOR_HOST            (0x70000000)    /*!< Processor x86 */

#define DELAY(nDelay)		        do{				   \
									      asm("nop");  \
									  }while(nDelay--)

#define TIMEOUT(nMs)                (((nMs)<(1000))?(0):(1))  /*!< This macro must return 0 upon timing out.
                                                               Right now there is no timeout if value passed
                                                               is < 1000 */


/*=============  D A T A    T Y P E S   =============*/

#if defined(_LANGUAGE_C)

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* C-specific definitions */


/*! \enum ADI_SS_PROC_ID
Enumeration for processor core id.
*/
typedef enum ADI_SS_PROC_ID
{
#if defined(__ADSPSC5xx__)
    PROCESSOR_ARM  = E_PROCESSOR_ARM,
#endif
    PROCESSOR_SH0  = E_PROCESSOR_SH0,
#ifndef __ADSP2156x__
    PROCESSOR_SH1  = E_PROCESSOR_SH1,
#endif
    PROCESSOR_NONE = E_PROCESSOR_HOST
}ADI_SS_PROC_ID;


/*! \struct ADI_SS_MEM_BLOCK
This structure contains the information of each memory block.
*/
typedef struct tMemBlock
{
    uint32_t nSize;        /*!< Size of the memory blocks */
    int32_t  nFlags;        /*!< Reserved */
    void    *pMem;          /*!< Start of the memory the block */ 
}ADI_SS_MEM_BLOCK; 
    

/*! \struct ADI_SS_MEM_MAP
This structure contains information about all memory blocks
which are to be used by this module.
*/
typedef struct tMemMap
{
    uint32_t           nMemBlocks;                         /*!< Number of memory blocks  */
    ADI_SS_MEM_BLOCK  *pMemBlocks[ADI_SS_MAX_MEM_BLOCKS];  /*!< Pointer to memory blocks */ 
}ADI_SS_MEM_MAP;

/*! \struct ADI_SS_MEM_SMAP
Forward definition for SMAP structure
*/
typedef struct SS_SMAP ADI_SS_MEM_SMAP;


#if !(defined (_TESSY_) || defined (_TESSY_COMPILER_DEPENDENT_) || defined(_QAC_))

#ifdef __ADSPSHARC__
#define PRAGMA(x)   _Pragma(#x)
#define SECTION(x)  PRAGMA(section (x))
#define ALIGN(x) 	PRAGMA(align x)
#else
#define SECTION(x) __attribute__((section(x)))
#define ALIGN(x) __attribute__((aligned(x)))
#endif    /* __ADSPSHARC__ */
#else
#define SECTION(x)
#define ALIGN(x)
#endif


#ifdef __cplusplus
}
#endif /* __cplusplus */

#else /* not _LANGUAGE_C */

/* Assembler-specific definitions */

#endif /* not _LANGUAGE_C */

#endif /* _ADI_SS_COMMON_H_ */

/*
** EOF: 
*/
