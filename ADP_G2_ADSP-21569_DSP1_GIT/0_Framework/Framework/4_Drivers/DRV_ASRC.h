/*****************************************************************************
 * DRV_ASRC.h
 *****************************************************************************/

#ifndef __DRV_ASRC_H__
#define __DRV_ASRC_H__

/*==============  D E F I N E S  ===============*/

typedef enum _E_DRV_ASRC_PERI_
{
	E_DRV_ASRC0							= 0,				/* ASRC0 for DAI0 */
	E_DRV_ASRC1,											/* ASRC1 for DAI0 */
	E_DRV_ASRC2,											/* ASRC2 for DAI0 */
	E_DRV_ASRC3,											/* ASRC3 for DAI0 */
	E_DRV_ASRC4,											/* ASRC4 for DAI1 */
	E_DRV_ASRC5,											/* ASRC5 for DAI1 */
	E_DRV_ASRC6,											/* ASRC6 for DAI1 */
	E_DRV_ASRC7,											/* ASRC7 for DAI1 */
	E_DRV_ASRC_PERI_MAX
} E_DRV_ASRC_PERI;

#define D_DRV_ASRC0123_BASE_ADDR		0x310C9240//0x310C9240
#define D_DRV_ASRC4567_BASE_ADDR		0x310CA240//0x310CB240

typedef struct _S_DRV_ASRC_REGS_
{
	volatile uint32_t	CTL01;								/* ASRC Control Register for ASRC 0 and 1 */
	volatile uint32_t	CTL23;								/* ASRC Control Register for ASRC 2 and 3 */
	volatile uint32_t	MUTE;								/* ASRC Mute Register */
	volatile uint32_t	RAT01;								/* ASRC Ratio Register for ASRC 0 and 1 */
	volatile uint32_t	RAT23;								/* ASRC Ratio Register for ASRC 2 and 3 */
} S_DRV_ASRC_REGS;

typedef enum _E_DRV_ASRC_I_FORMAT_
{
	E_DRV_ASRC_I_LT_JUST				= 0,				/* Default, input format is left-justified */
	E_DRV_ASRC_I_I2S					= 1,				/* I2S mode */
	E_DRV_ASRC_I_TDM					= 2,				/* TDM mode */
	E_DRV_ASRC_I_24BIT_RT_JUST			= 4,				/* 24-bit right-justified */
	E_DRV_ASRC_I_20BIT_RT_JUST			= 5,				/* 20-bit right-justified */
	E_DRV_ASRC_I_18BIT_RT_JUST			= 6,				/* 18-bit right-justified */
	E_DRV_ASRC_I_16BIT_RT_JUST			= 7,				/* 16-bit right-justified */
	E_DRV_ASRC_I_NONE					= 8					/* No format */
} E_DRV_ASRC_I_FORMAT;

typedef enum _E_DRV_ASRC_O_FORMAT_
{
	E_DRV_ASRC_O_LT_JUST				= 0,				/* Default, output format is left-justified */
	E_DRV_ASRC_O_I2S					= 1,				/* I2S mode */
	E_DRV_ASRC_O_TDM					= 2,				/* TDM mode */
	E_DRV_ASRC_O_RT_JUST				= 3,				/* Right-justified */
	E_DRV_ASRC_O_NONE					= 4					/* No format */
} E_DRV_ASRC_O_FORMAT;

typedef enum _E_DRV_ASRC_WORD_LEN_
{
	E_DRV_ASRC_WORD_LENGTH_24			= 0,				/* 24-bit */
	E_DRV_ASRC_WORD_LENGTH_20			= 1,				/* 20-bit */
	E_DRV_ASRC_WORD_LENGTH_18			= 2,				/* 18-bit */
	E_DRV_ASRC_WORD_LENGTH_16			= 3,				/* 16-bit */
	E_DRV_ASRC_WORD_LENGTH_NONE			= 4					/* None */
} E_DRV_ASRC_WORD_LEN;

typedef struct _S_DRV_ASRC_CFGS_
{
	volatile S_DRV_ASRC_REGS * pASRCRegs;					/* Pointer to ASRC Memory Mapped Registers */
} S_DRV_ASRC_CFGS; // 4-bytes

/*===========  P R O T O T Y P E S  ============*/
uint32_t DRV_ASRC_Init(void);

#endif /* __DRV_ASRC_H__ */
