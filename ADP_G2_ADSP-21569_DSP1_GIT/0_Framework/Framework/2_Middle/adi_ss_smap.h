/****************************************************************************
Copyright (c), 2014-2015 - Analog Devices Inc. All Rights Reserved.
This software is proprietary & confidential to Analog Devices, Inc.
and its licensors.
*****************************************************************************
 * @file:    adi_ss_smap.h
 * @brief:   Contains SMAP structure.
 * @version: $Revision$
 * @date:    $Date$
 * Developed by: Automotive Software and Systems team, Bangalore, India
*****************************************************************************/
/*! \addtogroup ADI_SS_SMAP
 *  @{
 */
#ifndef __ADI_SS_SMAP_H__
#define __ADI_SS_SMAP_H__

/*=============  I N C L U D E S   =============*/
#include "adi_ss_common.h"

/*==============  D E F I N E S  ===============*/
/* Build time configurable macros */
#define ADI_SS_FW_MAX_PROC_BLOCKS        (3U)            /*!< Maximum number of processing blocks (instances) supported */
#define ADI_SS_FW_MIN_PROC_BLOCKS        (1U)            /*!< Minimum number of processing blocks (instances) supported */

/* Other macros */
#define ADI_SS_MAX_SOURCES       		 (8U)			 /*!< Maximum number of data sources that is ever possible */
#define ADI_SS_MAX_SINKS        		 (8U)			 /*!< Maximum number of data sinks that is ever possible */

#define MAX_SMAP_FW_INDICES				 (1U)            /*!< Maximum framework indices  */
#define MAX_SMAP_INDICES            	 (ADI_SS_FW_MAX_PROC_BLOCKS+MAX_SMAP_FW_INDICES)  /*!< Maximum SMAP indices. Includes
                                                                                          maximum SSn instances + fw 
                                                                                          instance */

#define MAX_SMAP_FW_BUFFERS				(3U)	         /*!< Maximum number of framework buffers within SMAP framework
                                                              memory section */
#define MAX_SMAP_SSN_BUFFERS			(11U)	         /*!< Maximum number of buffers within an SMAP SSn memory section */

#define ADI_SS_FW_MAX_NUM_IN_CHANNELS_SMAP  (128)         /*!< Maximum number of input channels for SMAP */
#define ADI_SS_FW_MAX_NUM_OUT_CHANNELS_SMAP (128)         /*!< Maximum number of output channels for SMAP */

																						 
/* Defines for DAI pin enumerations */
#define E_ADI_SS_DAI_NONE               (0x70000000U)    /*!< Enumeration definition for virtual pin
                                                               for peripheral data sharing */
#define E_ADI_SS_DAI_PIN01              (0x00000000U)    /*!< Enumeration definition for DAI PIN01 */
#define E_ADI_SS_DAI_PIN02              (0x00000001U)    /*!< Enumeration definition for DAI PIN02 */
#define E_ADI_SS_DAI_PIN03              (0x00000002U)    /*!< Enumeration definition for DAI PIN03 */
#define E_ADI_SS_DAI_PIN04              (0x00000003U)    /*!< Enumeration definition for DAI PIN04 */
#define E_ADI_SS_DAI_PIN05              (0x00000004U)    /*!< Enumeration definition for DAI PIN05 */
#define E_ADI_SS_DAI_PIN06              (0x00000005U)    /*!< Enumeration definition for DAI PIN06 */
#define E_ADI_SS_DAI_PIN07              (0x00000006U)    /*!< Enumeration definition for DAI PIN07 */
#define E_ADI_SS_DAI_PIN08              (0x00000007U)    /*!< Enumeration definition for DAI PIN08 */
#define E_ADI_SS_DAI_PIN09              (0x00000008U)    /*!< Enumeration definition for DAI PIN09 */
#define E_ADI_SS_DAI_PIN10              (0x00000009U)    /*!< Enumeration definition for DAI PIN10 */
#define E_ADI_SS_DAI_PIN11              (0x0000000AU)    /*!< Enumeration definition for DAI PIN11 */
#define E_ADI_SS_DAI_PIN12              (0x0000000BU)    /*!< Enumeration definition for DAI PIN12 */
#define E_ADI_SS_DAI_PIN13              (0x0000000CU)    /*!< Enumeration definition for DAI PIN13 */
#define E_ADI_SS_DAI_PIN14              (0x0000000DU)    /*!< Enumeration definition for DAI PIN14 */
#define E_ADI_SS_DAI_PIN15              (0x0000000EU)    /*!< Enumeration definition for DAI PIN15 */
#define E_ADI_SS_DAI_PIN16              (0x0000000FU)    /*!< Enumeration definition for DAI PIN16 */
#define E_ADI_SS_DAI_PIN17              (0x00000010U)    /*!< Enumeration definition for DAI PIN17 */
#define E_ADI_SS_DAI_PIN18              (0x00000011U)    /*!< Enumeration definition for DAI PIN18 */
#define E_ADI_SS_DAI_PIN19              (0x00000012U)    /*!< Enumeration definition for DAI PIN19 */
#define E_ADI_SS_DAI_PIN20              (0x00000013U)    /*!< Enumeration definition for DAI PIN20 */

/* Defines for ADI_SS_FW_PROCESS_MODE enumeration type */
#define E_ADI_SS_FW_PROCESSMODE_SINGLE   (0x70000000)     /*!< Single instance */
#define E_ADI_SS_FW_PROCESSMODE_SERIAL   (0x70000001)     /*!< Multi instance serial SSn */
#define E_ADI_SS_FW_PROCESSMODE_PARALLEL (0x70000002)     /*!< Multi instance parallel SSn */
#define E_ADI_SS_FW_PROCESSMODE_HYBRID1  (0x70000003)     /*!< Multi instance hybrid SSn of type 1 */
#define E_ADI_SS_FW_PROCESSMODE_HYBRID2  (0x70000004)     /*!< Multi instance hybrid SSn of type 2 */

/* Defines for ADI_SS_FW_DATA_PERI_TYPE enumeration type */
#define E_ADI_SS_PERI_TYPE_SPORT_PCM     (0x70000000U)  /*!< PCM data type from SPORT */
#define E_ADI_SS_PERI_TYPE_SPORT_PCMX    (0x70000001U)  /*!< PCMx data type from SPORT */
#define E_ADI_SS_PERI_TYPE_SM            (0x70000002U)  /*!< Data from shared memory */
#define E_ADI_SS_PERI_TYPE_LP            (0x70000003U)  /*!< Data from link port */

/* Defines for ADI_SS_FW_AUDIOMODE enumeration type */
#define E_ADI_SS_FW_ADCOEXIST           (0x70000000U)     /*!< Analog digital co-existence mode */
#define E_ADI_SS_FW_ADCOEXIST_DIGICLOCK (0x70000001U)     /*!< Analog digital co-existence digital clock mode */

/* Defines for ADI_SS_FW_MULTICORE_MODE enumeration type */
#define E_ADI_SS_FW_MULTICOREMODE_INDEPENDENT	(0x70000000) /*!< Indicates an independent signal flow for each of the cores */
#define E_ADI_SS_FW_MULTICOREMODE_DUAL			(0x70000001) /*!< Indicates a single signal flow for all the cores */

/* Defines for ADI_SS_FW_SPORT_NUM enumeration type */
#define E_ADI_SS_FW_SPORT_NUM_0	(0x70000000U)
#define E_ADI_SS_FW_SPORT_NUM_1	(0x70000001U)
#define E_ADI_SS_FW_SPORT_NUM_2	(0x70000002U)
#define E_ADI_SS_FW_SPORT_NUM_3	(0x70000003U)
#define E_ADI_SS_FW_SPORT_NUM_4	(0x70000004U)
#define E_ADI_SS_FW_SPORT_NUM_5	(0x70000005U)
#define E_ADI_SS_FW_SPORT_NUM_6	(0x70000006U)
#define E_ADI_SS_FW_SPORT_NUM_7	(0x70000007U)

/* Defines for ADI_SS_FW_SPORT_HALF enumeration type */
#define E_ADI_SS_FW_SPORT_HALF_A	(0x70000000U)
#define E_ADI_SS_FW_SPORT_HALF_B	(0x70000001U)

/* Defines for ADI_SS_FW_SPORT_CLK_FS_POL enumeration type */
#define E_ADI_SS_FW_SPORT_CLK_FS_POL_RISING_EDGE	(0x70000000U)
#define E_ADI_SS_FW_SPORT_CLK_FS_POL_FALLING_EDGE	(0x70000001U)

/* Defines for ADI_SS_FW_SPORT_MODE enumeration type */
#define E_ADI_SS_FW_SPORT_MODE_I2S	 (0x70000000U)
#define E_ADI_SS_FW_SPORT_MODE_TDM4	 (0x70000001U)
#define E_ADI_SS_FW_SPORT_MODE_TDM8	 (0x70000002U)
#define E_ADI_SS_FW_SPORT_MODE_TDM16 (0x70000003U)

/* Defines for ADI_SS_FW_DAI_PIN_GROUP enumeration type */
#define E_ADI_SS_FW_DAI_PIN_GROUP_0	 (0x70000000U)
#define E_ADI_SS_FW_DAI_PIN_GROUP_1	 (0x70000001U)

																						 
/*=============  D A T A    T Y P E S   =============*/
#if defined(_LANGUAGE_C)

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*! \enum ADI_SS_FW_DATA_PERI_TYPE
Enumeration for data peripheral type.
*/
typedef enum ADI_SS_FW_DATA_PERI_TYPE
{
    ADI_SS_PERI_TYPE_SPORT_PCM   = E_ADI_SS_PERI_TYPE_SPORT_PCM,   /*!< Pin configured to use SPORT for I/O operation.
                                                                      PCM type of data is Tx/Rx by SPORT */
    ADI_SS_PERI_TYPE_SPORT_PCMX  = E_ADI_SS_PERI_TYPE_SPORT_PCMX,  /*!< Pin configured to use SPORT for I/O operation.
                                                                      PCMx type of data is Tx/Rx by SPORT */
    ADI_SS_PERI_TYPE_SM          = E_ADI_SS_PERI_TYPE_SM,          /*!< Pin configured to use Shared Memory for I/O
                                                                      operation. */
    ADI_SS_PERI_TYPE_LP          = E_ADI_SS_PERI_TYPE_LP           /*!< Pin configured to use Link Port for I/O
                                                                      operation. */
}ADI_SS_FW_DATA_PERI_TYPE;

/*! \enum ADI_SS_FW_DAI_PIN_GROUP
Enumeration for DAI pin group.
*/
typedef enum ADI_SS_FW_DAI_PIN_GROUP
{
	ADI_SS_FW_DAI_PIN_GROUP_0 = E_ADI_SS_FW_DAI_PIN_GROUP_0,	/*!<    DAI 0   */
	ADI_SS_FW_DAI_PIN_GROUP_1 = E_ADI_SS_FW_DAI_PIN_GROUP_1		/*!<    DAI 1   */
}ADI_SS_FW_DAI_PIN_GROUP;

/*! \enum ADI_SS_FW_DAI_PIN
Enumeration for DAI Pins.
*/
typedef enum ADI_SS_FW_DAI_PIN
{
    ADI_SS_DAI_PIN01   =   E_ADI_SS_DAI_PIN01 ,           /*!<    DAI PIN01     */
    ADI_SS_DAI_PIN02   =   E_ADI_SS_DAI_PIN02 ,           /*!<    DAI PIN02     */
    ADI_SS_DAI_PIN03   =   E_ADI_SS_DAI_PIN03 ,           /*!<    DAI PIN03     */
    ADI_SS_DAI_PIN04   =   E_ADI_SS_DAI_PIN04 ,           /*!<    DAI PIN04     */
    ADI_SS_DAI_PIN05   =   E_ADI_SS_DAI_PIN05 ,           /*!<    DAI PIN05     */
    ADI_SS_DAI_PIN06   =   E_ADI_SS_DAI_PIN06 ,           /*!<    DAI PIN06     */
    ADI_SS_DAI_PIN07   =   E_ADI_SS_DAI_PIN07 ,           /*!<    DAI PIN07     */
    ADI_SS_DAI_PIN08   =   E_ADI_SS_DAI_PIN08 ,           /*!<    DAI PIN08     */
    ADI_SS_DAI_PIN09   =   E_ADI_SS_DAI_PIN09 ,           /*!<    DAI PIN09     */
    ADI_SS_DAI_PIN10   =   E_ADI_SS_DAI_PIN10 ,           /*!<    DAI PIN10     */
    ADI_SS_DAI_PIN11   =   E_ADI_SS_DAI_PIN11 ,           /*!<    DAI PIN11     */
    ADI_SS_DAI_PIN12   =   E_ADI_SS_DAI_PIN12 ,           /*!<    DAI PIN12     */
    ADI_SS_DAI_PIN13   =   E_ADI_SS_DAI_PIN13 ,           /*!<    DAI PIN13     */
    ADI_SS_DAI_PIN14   =   E_ADI_SS_DAI_PIN14 ,           /*!<    DAI PIN14     */
    ADI_SS_DAI_PIN15   =   E_ADI_SS_DAI_PIN15 ,           /*!<    DAI PIN15     */
    ADI_SS_DAI_PIN16   =   E_ADI_SS_DAI_PIN16 ,           /*!<    DAI PIN16     */
    ADI_SS_DAI_PIN17   =   E_ADI_SS_DAI_PIN17 ,           /*!<    DAI PIN17     */
    ADI_SS_DAI_PIN18   =   E_ADI_SS_DAI_PIN18 ,           /*!<    DAI PIN18     */
    ADI_SS_DAI_PIN19   =   E_ADI_SS_DAI_PIN19 ,           /*!<    DAI PIN19     */
    ADI_SS_DAI_PIN20   =   E_ADI_SS_DAI_PIN20 ,           /*!<    DAI PIN20     */
    ADI_SS_DAI_NONE     =  E_ADI_SS_DAI_NONE              /*!<    No DAI PIN    */
}ADI_SS_FW_DAI_PIN;

/*! \enum ADI_SS_FW_PROCESS_MODE
Enumeration for processing mode for the different process blocks.
*/
typedef enum ADI_SS_FW_PROCESS_MODE
{
    ADI_SS_FW_PROCESSMODE_SINGLE   = E_ADI_SS_FW_PROCESSMODE_SINGLE,
    ADI_SS_FW_PROCESSMODE_SERIAL   = E_ADI_SS_FW_PROCESSMODE_SERIAL,
    ADI_SS_FW_PROCESSMODE_PARALLEL = E_ADI_SS_FW_PROCESSMODE_PARALLEL,
    ADI_SS_FW_PROCESSMODE_HYBRID1  = E_ADI_SS_FW_PROCESSMODE_HYBRID1,
    ADI_SS_FW_PROCESSMODE_HYBRID2  = E_ADI_SS_FW_PROCESSMODE_HYBRID2
}ADI_SS_FW_PROCESS_MODE;

/*! \enum ADI_SS_FW_AUDIOMODE
Enumeration for audio mode
*/
typedef enum ADI_SS_FW_AUDIOMODE
{
    ADI_SS_FW_ADCOEXIST             = E_ADI_SS_FW_ADCOEXIST,            /*!< Analog digital coexistence mode */
    ADI_SS_FW_ADCOEXIST_DIGICLOCK   = E_ADI_SS_FW_ADCOEXIST_DIGICLOCK   /*!< Analog digital coexistence digital
                                                                             clock mode */
}ADI_SS_FW_AUDIOMODE;

/*! \enum ADI_SS_FW_MULTICORE_MODE
Enumeration for different types of signal flows designed in Host for multicore mode.
*/
typedef enum ADI_SS_FW_MULTICORE_MODE
{
    ADI_SS_FW_MULTICOREMODE_INDEPENDENT = E_ADI_SS_FW_MULTICOREMODE_INDEPENDENT,
    ADI_SS_FW_MULTICOREMODE_DUAL		= E_ADI_SS_FW_MULTICOREMODE_DUAL
}ADI_SS_FW_MULTICORE_MODE;


/*! \enum ADI_SS_FW_SPORT_NUM
Enumeration for SPORT numbers.
*/
typedef enum ADI_SS_FW_SPORT_NUM
{
	ADI_SS_FW_SPORT_NUM_0 = E_ADI_SS_FW_SPORT_NUM_0,
	ADI_SS_FW_SPORT_NUM_1 = E_ADI_SS_FW_SPORT_NUM_1,
	ADI_SS_FW_SPORT_NUM_2 = E_ADI_SS_FW_SPORT_NUM_2,
	ADI_SS_FW_SPORT_NUM_3 = E_ADI_SS_FW_SPORT_NUM_3,
	ADI_SS_FW_SPORT_NUM_4 = E_ADI_SS_FW_SPORT_NUM_4,
	ADI_SS_FW_SPORT_NUM_5 = E_ADI_SS_FW_SPORT_NUM_5,
	ADI_SS_FW_SPORT_NUM_6 = E_ADI_SS_FW_SPORT_NUM_6,
	ADI_SS_FW_SPORT_NUM_7 = E_ADI_SS_FW_SPORT_NUM_7
}ADI_SS_FW_SPORT_NUM;

/*! \enum ADI_SS_FW_SPORT_HALF
Enumeration for SPORT half.
*/
typedef enum ADI_SS_FW_SPORT_HALF
{
	ADI_SS_FW_SPORT_HALF_A = E_ADI_SS_FW_SPORT_HALF_A,
	ADI_SS_FW_SPORT_HALF_B = E_ADI_SS_FW_SPORT_HALF_B
}ADI_SS_FW_SPORT_HALF;

/*! \enum ADI_SS_FW_SPORT_CLK_POL
Enumeration for SPORT clock polarity.
*/
typedef enum ADI_SS_FW_SPORT_CLK_FS_POL
{
	ADI_SS_FW_SPORT_CLK_FS_POL_RISING_EDGE = E_ADI_SS_FW_SPORT_CLK_FS_POL_RISING_EDGE,
	ADI_SS_FW_SPORT_CLK_FS_POL_FALLING_EDGE = E_ADI_SS_FW_SPORT_CLK_FS_POL_FALLING_EDGE
}ADI_SS_FW_SPORT_CLK_FS_POL;

/*! \enum ADI_SS_FW_SPORT_MODE
Enumeration for SPORT mode.
*/
typedef enum ADI_SS_FW_SPORT_MODE
{
	ADI_SS_FW_SPORT_MODE_I2S = E_ADI_SS_FW_SPORT_MODE_I2S,
	ADI_SS_FW_SPORT_MODE_TDM4 = E_ADI_SS_FW_SPORT_MODE_TDM4,
	ADI_SS_FW_SPORT_MODE_TDM8 = E_ADI_SS_FW_SPORT_MODE_TDM8,
	ADI_SS_FW_SPORT_MODE_TDM16 = E_ADI_SS_FW_SPORT_MODE_TDM16
}ADI_SS_FW_SPORT_MODE;


/*! \struct ADI_SS_FW_SPORT_CONFIG
SPORT configuration parameters received from host if host configuration is
enabled (ADI_SS_ARM_FW_CONFIG::bHostConfigEn==TRUE).if ADI_SS_ARM_FW_CONFIG::
bHostConfigEn==FALSE, this structure is to be configured by the application.
*/
typedef struct ADI_SS_FW_SPORT_CONFIG
{
    ADI_SS_FW_SPORT_NUM		 	eSportNum;	    	/*!< SPORT number  */
    ADI_SS_FW_SPORT_HALF	 	eSportHalf;    		/*!< SPORT Half */
    ADI_SS_FW_SPORT_CLK_FS_POL 	eSportClkPol;  		/*!< SPORT clock polarity */
    ADI_SS_FW_SPORT_CLK_FS_POL 	eSportFsPol;   		/*!< SPORT frame sync polarity */
    ADI_SS_FW_SPORT_MODE	 	eSportMode;    		/*!< SPORT operation mode */
    uint32_t				 	nSportWordLen;  	/*!< SPORT word length */
}ADI_SS_FW_SPORT_CONFIG;


/*! \struct ADI_SS_FW_DATA_PERI_CONFIG
Peripheral configuration parameters received from host if host configuration is
enabled (ADI_SS_ARM_FW_CONFIG::bHostConfigEn==TRUE). if ADI_SS_ARM_FW_CONFIG::
bHostConfigEn==FALSE, this structure is to be configured by the application.
*/
typedef struct ADI_SS_FW_DATA_PERI_CONFIG
{
    ADI_SS_FW_DAI_PIN_GROUP	 	eDataDAIPinGroup; 	/*!< Primary in/out DAI pin group for a source or sink */
    ADI_SS_FW_DAI_PIN    	 	eDataDAIPin;  		/*!< Primary in/out DAI pin number for a source or sink */
    uint32_t					nEnSecChannel;		/*<! Flag indicating whether secondary channel of the peripheral
    													 is enabld or not */
    ADI_SS_FW_DAI_PIN_GROUP	 	eDataDAIPinGroupSec;/*!< Secondary in/out DAI pin group for a source or sink */
    ADI_SS_FW_DAI_PIN    	 	eDataDAIPinSec;  	/*!< Secondary in/out DAI pin number for a source or sink */
    uint32_t            	    nChannels;     		/*!< Number of audio channels from/to the peripheral */
    ADI_SS_FW_SPORT_CONFIG      oSPORTPeriConfig;	/*!< SPORT peripheral configuration */

    /* Add other peripheral configurations below this line */
}ADI_SS_FW_DATA_PERI_CONFIG;

/*! \struct ADI_SS_FW_HOST_CONFIG
Host configurable framework parameters. The framework parameters in this structure is configured by the host if
ADI_SS_ARM_FW_CONFIG::bHostConfigEn==TRUE. if ADI_SS_ARM_FW_CONFIG::bHostConfigEn==FALSE,
the parameters in this structure is to be configured by the application.
*/
typedef struct ADI_SS_FW_HOST_CONFIG
{
    uint32_t                   nBlockSize;                 /*!< Processing Block size */
    uint32_t                   nInInterfaceBuffSz;         /*!< Total input interface buffer size reserved by host
                                                              for all pins.This has to be a multiple of nBlockSize.
                                                              This field will be used for input buff size validation */
    uint32_t                   nNumInInterfaceBuff;        /*!< Number of input interface buffers of size
                                                              nBlockSize */
    uint32_t                   nOutInterfaceBuffSz;        /*!< Total output interface buffer size reserved by host.
                                                              for all pins.This has to be a multiple of nBlockSize.
                                                              This field will be used for output buff size validation */
    uint32_t                   nNumOutInterfaceBuff;       /*!< Number of output interface buffers of size
                                                              nBlockSize */
    uint32_t                   nOutputPreroll;             /*!< Output preroll as a multiple of nBlockSize */
    uint32_t                   nInSamplingRate;            /*!< Input sampling rate */
    uint32_t                   nOutSamplingRate;           /*!< Output sampling rate */
    ADI_SS_FW_AUDIOMODE        eAudioMode;                 /*!< Audio mode*/
    ADI_SS_FW_MULTICORE_MODE   eFwMultiCoreMode;		   /*!< Parameter for different types of signal flows designed
    														    in Host for multicore mode */
    uint32_t        	       nPeripheralIOBuffSz;        /*!< Total Peripheral i/o buffer size for all pins
     	 	 	 	 	 	 	 	 	 	 	 	 	 	  including input and output.This field is currently
     	 	 	 	 	 	 	 	 	 	 	 	 	 	  not used  */
    uint32_t        	       nNumPeripheralIOBuff;       /*!< Number of peripheral i/o buffers.This field is currently
                                                              not used */
    /* Information corresponding to the data Sources */
    uint32_t                   nNumSources;				               /*!< Number of data sources  */
    ADI_SS_FW_DATA_PERI_TYPE   eSourcePeriType[ADI_SS_MAX_SOURCES];    /*!< Source peripheral type enumeration for each
                                                                          of the sources */
    ADI_SS_FW_DATA_PERI_CONFIG oSourcePeriConfig[ADI_SS_MAX_SOURCES];  /*!< SPORT configuration for each of the sources
    																	  received from the host */
    /* Information corresponding to the data Sinks */
    uint32_t                   nNumSinks;					           /*!< Number of data sinks */
    ADI_SS_FW_DATA_PERI_TYPE   eSinkPeriType[ADI_SS_MAX_SINKS];        /*!< Sink peripheral type enumeration for each
                                                                          of the sink */
    ADI_SS_FW_DATA_PERI_CONFIG oSinkPeriConfig[ADI_SS_MAX_SINKS];     /*!< SPORT configuration for each of the sinks
    																	  received from the host */
}ADI_SS_FW_HOST_CONFIG;


/*! \struct SS_SMAP_FW_INFO
Framework info structure within SMAP
*/
typedef struct SS_SMAP_FW_INFO
{
    ADI_SS_FW_HOST_CONFIG  oFwHostConfig;			            /*!< Host configurable parameters for framework */
	uint32_t 		       nNumFwBuffers;                       /*!< Number of buffers required for framework */
	ADI_SS_MEM_BLOCK       oFwBuff[MAX_SMAP_FW_BUFFERS];        /*!< Array of mem blocks for the framework buffers */
}SS_SMAP_FW_INFO;

/*! \struct SMAP_HOST2TGT_INFO
SSn information which has to be communicated to target framework.
*/
typedef struct SMAP_HOST2TGT_INFO
{
    uint32_t         nInPhyChannels;                            /*!< Number of physical input channels.This field is
                                                                     used for total input channel count validation */
    uint32_t         nOutPhyChannels;                           /*!< Number of physical output channels.This field is
                                                                     used for total output channel count validation */
    int32_t          aInChMap[ADI_SS_FW_MAX_NUM_IN_CHANNELS_SMAP];  /*!< Array indicating the indices of the input
                                                                     channels used within the SSn. Rest must be -1. */
    int32_t          aOutChMap[ADI_SS_FW_MAX_NUM_OUT_CHANNELS_SMAP];/*!< Array indicating the indices of the output
                                                                     channels used within the SSn. Rest must be -1. */
}SMAP_HOST2TGT_INFO;

/*! \struct SS_SMAP_SSN_INFO
SSn info structure within SMAP
*/
typedef struct SS_SMAP_SSN_INFO
{
	SMAP_HOST2TGT_INFO	oHostInfo;						/*!< SSn information which has to be communicated to target framework */
	uint32_t 		 	nNumSSnBuffers;                 /*!< Number of buffers required for SSn target library */
	ADI_SS_MEM_BLOCK 	oSSnBuff[MAX_SMAP_SSN_BUFFERS]; /*!< Array of mem blocks for the SSn buffers */
}SS_SMAP_SSN_INFO;


/*! \struct SS_SMAP
SMAP structure
*/
struct SS_SMAP
{
	SS_SMAP_FW_INFO			  	oFwInfo;                              /*!< Instance of framework structure */
	uint32_t 					nNumSSn;                              /*!< Number of SSn instances */
    ADI_SS_FW_PROCESS_MODE      eProcessMode;                         /*!< SSn Processing mode */
	SS_SMAP_SSN_INFO      		oSSnInfo[ADI_SS_FW_MAX_PROC_BLOCKS];  /*!< Array of SSn info */
};

/*=======  P U B L I C   P R O T O T Y P E S  ========*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#else /* not _LANGUAGE_C */

/* Assembler-specific definitions */

#endif /* not _LANGUAGE_C */

#endif    /* __ADI_SS_SMAP_H__ */

/*
 *  @}
 */
