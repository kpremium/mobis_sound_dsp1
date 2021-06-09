/*****************************************************************************
 * DRV_DMA.h
 *****************************************************************************/

#ifndef __DRV_DMA_H__
#define __DRV_DMA_H__

#include <stdint.h>

/* for SPORT */
#define MEM_SPACE_SPORT_MASK            (0x003FFFFFu)
#define MEM_SPACE_SYS_OFFSET            (0x28000000u)

typedef struct _ST_DMA_DSCP
{
	struct ST_DMA_DSCP		*pNextDscp;		/*!< Pointer to next Initial Descriptor */
	void					*pStartAddr;	/*!< Start address of current buffer */
	uint32_t				Config;			/*!< DMA Configuration register */
	uint32_t				XCount;			/*!< XCOUNT - Inner loop count start value in number of MSIZE data transfers*/
	int32_t					XModify;		/*!< XMODIFY - Inner loop address increment, in bytes */
	uint32_t				YCount;			/*!< YCOUNT - Outer loop count start value (2D only), in number of rows*/
	int32_t					YModify;		/*!< YMODIFY - Outer loop address increment (2D only), in bytes*/
}ST_DMA_DSCP;


#define D_DRV_DMA0_SPORT0A_BASE_ADDR	0x31022000 // v
#define D_DRV_DMA1_SPORT0B_BASE_ADDR	0x31022080 // v
#define D_DRV_DMA2_SPORT1A_BASE_ADDR	0x31022100
#define D_DRV_DMA3_SPORT1B_BASE_ADDR	0x31022180
#define D_DRV_DMA4_SPORT2A_BASE_ADDR	0x31022200 // v
#define D_DRV_DMA5_SPORT2B_BASE_ADDR	0x31022280 // v
#define D_DRV_DMA6_SPORT3A_BASE_ADDR	0x31022300 // v
#define D_DRV_DMA7_SPORT3B_BASE_ADDR	0x31022380 // v
#define D_DRV_DMA8_MEMSRC0_BASE_ADDR	0x31028000
#define D_DRV_DMA9_MEMDST0_BASE_ADDR	0x31028080
#define D_DRV_DMA10_SPORT4A_BASE_ADDR	0x31024000
#define D_DRV_DMA11_SPORT4B_BASE_ADDR	0x31024080
#define D_DRV_DMA12_SPORT5A_BASE_ADDR	0x31024100
#define D_DRV_DMA13_SPORT5B_BASE_ADDR	0x31024180
#define D_DRV_DMA14_SPORT6A_BASE_ADDR	0x31024200
#define D_DRV_DMA15_SPORT6B_BASE_ADDR	0x31024280
#define D_DRV_DMA16_SPORT7A_BASE_ADDR	0x31024300
#define D_DRV_DMA17_SPORT7B_BASE_ADDR	0x31024380
#define D_DRV_DMA18_MEMSRC1_BASE_ADDR	0x31028100
#define D_DRV_DMA19_MEMDST1_BASE_ADDR	0x31028180
#define D_DRV_DMA20_UART0TX_BASE_ADDR	0x31026080
#define D_DRV_DMA21_UART0RX_BASE_ADDR	0x31026000
#define D_DRV_DMA22_SPI0TX_BASE_ADDR	0x31046000
#define D_DRV_DMA23_SPI0RX_BASE_ADDR	0x31046080
#define D_DRV_DMA24_SPI1TX_BASE_ADDR	0x31046100
#define D_DRV_DMA25_SPI1RX_BASE_ADDR	0x31046180
#define D_DRV_DMA26_SPI2TX_BASE_ADDR	0x31046200
#define D_DRV_DMA27_SPI3RX_BASE_ADDR	0x31046280
#define D_DRV_DMA28_EPPI0CH0_BASE_ADDR	0x31046300
#define D_DRV_DMA29_EPPI0CH1_BASE_ADDR	0x31046380
#define D_DRV_DMA30_LP0_BASE_ADDR		0x30FFF000
#define D_DRV_DMA31_HAE0TX_BASE_ADDR	0x3102A100
#define D_DRV_DMA32_HAE0RXCH0_BASE_ADDR	0x3102A000
#define D_DRV_DMA33_HAE0RXCH1_BASE_ADDR	0x3102A080
#define D_DRV_DMA34_UART1TX_BASE_ADDR	0x31026180
#define D_DRV_DMA35_UART1RX_BASE_ADDR	0x31026100
#define D_DRV_DMA36_LP1_BASE_ADDR		0x30FFF080
#define D_DRV_DMA37_UART2TX_BASE_ADDR	0x31026280
#define D_DRV_DMA38_UART2RX_BASE_ADDR	0x31026200
#define D_DRV_DMA39_MEMSRC2_BASE_ADDR	0x3109A000
#define D_DRV_DMA40_MEMDST2_BASE_ADDR	0x3109A080
#define D_DRV_DMA41_FFTA0TX_BASE_ADDR	0x3109C200
#define D_DRV_DMA42_FFTA0RX_BASE_ADDR	0x3109C400
#define D_DRV_DMA43_MEMSRC3_BASE_ADDR	0x3109B000
#define D_DRV_DMA44_MEMDST3_BASE_ADDR	0x3109B080

typedef struct _S_DRV_DMA_REGS_
{
	volatile uint32_t	DSCPTR_NXT;							/* Pointer to next Initial Descriptor */
	volatile uint32_t	ADDRSTART;							/* Start address of current buffer */
	volatile uint32_t	CFG;								/* Configuration register */
	volatile uint32_t	XCNT;								/* XCOUNT - Inner loop count start value in number of MSIZE data transfers*/
	volatile int32_t	XMOD;								/* XMODIFY - Inner loop address increment, in bytes */
	volatile uint32_t	YCNT;								/* YCOUNT - Outer loop count start value (2D only), in number of rows*/
	volatile int32_t	YMOD;								/* YMODIFY - Outer loop address increment (2D only), in bytes*/
	uint32_t			Padding0;
	uint32_t			Padding1;
	volatile uint32_t	DSCPTR_CUR;							/* Current Descriptor Pointer */
	volatile uint32_t	DSCPTR_PRV;							/* Previous Initial Descriptor Pointer */
	volatile uint32_t	ADDR_CUR;							/* Current Address */
	volatile uint32_t	STAT;								/* Status Register */
	volatile uint32_t	XCNT_CUR;							/* Current XCOUNT */
	volatile uint32_t	YCNT_CUR;							/* Current YCOUNT */
	uint32_t			Padding3;
	volatile uint32_t	BWLCNT;								/* Bandwidth Limit Count */
	volatile uint32_t	BWLCNT_CUR;							/* Bandwidth Limit Count Current */
	volatile uint32_t	BWMCNT;								/* Bandwidth Monitor Count */
	volatile uint32_t	BWMCNT_CUR;							/* Bandwidth Monitor Count Current */
} S_DRV_DMA_REGS;

typedef enum _E_DRV_DMA_DIR_
{
	E_DRV_DMA_DIR_RFM					= 0,				/* Read from memory */
	E_DRV_DMA_DIR_WTM					= 1,				/* Write to memory */
	E_DRV_DMA_DIR_EXT					= 2					/* It's for SW or GPIO Interrupt */
} E_DRV_DMA_DIR;

typedef struct _S_DRV_DMA_CFGS_
{
	volatile S_DRV_DMA_REGS * pDMARegs;						/* Pointer to DMA Memory Mapped Registers */
} S_DRV_DMA_CFGS; // 4-bytes

uint32_t DRV_DMA_Init(void);

void DmaMemcpy( const uint8_t *src, uint8_t *dest, uint32_t size, void (*cb)(void) );
//void ISR_MDMA1_DST(unsigned int id, void* arg);
uint32_t DRV_DMA_WhichSidePDMA(uint8_t ePeriId, uint32_t nBufAddr);

void ISR_DAI0_GRP0(unsigned int id, void* arg);
void ISR_DAI0_GRP1(unsigned int id, void* arg);
void ISR_DAI1_GRP0(unsigned int id, void* arg);
void ISR_DAI1_GRP1(unsigned int id, void* arg);


#endif /* __DRV_DMA_H__ */
