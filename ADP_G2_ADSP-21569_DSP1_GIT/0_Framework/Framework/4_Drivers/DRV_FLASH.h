
#ifndef _DRV_FLASH_H_
#define _DRV_FLASH_H_

#define FLASH_SIZE_MBYTES	64							// 64Mbytes, 16,384 Sectors, 1,024 Blocks
#define FLASH_ACCESS_CONTROL
#define FLASH_ACCESS_START_OFFSET		(0x00300000)

#if defined(USE_MASD) || defined(USE_ESEV)
#define FLASH_ACCESS_END_OFFSET			(0x00509FFF)
#else
#define FLASH_ACCESS_END_OFFSET			(0x004FFFFF)
#endif

#define FLASH_NUM_SECTORS		(256*FLASH_SIZE_MBYTES)
#define FLASH_NUM_BLOCKS		(16*FLASH_SIZE_MBYTES)
#define FLASH_SECTOR_SIZE		0x1000		// 4 KBytes
#define FLASH_BLOCK_SIZE		0x10000		// 64 KBytes
#define FLASH_PAGE_SIZE			256			// 256 Bytes

/* Tested with Micron, Macronix Chip (for MT25QL512ABB, MX25L12835F, MX25L3233F) */
#define USE_QUAD				1		// Use Quad mode for write

/* spi Device Info */
#define SPI_DEVICE_NUM			2u
#define SPI_SELECT_NUM			ENUM_SPI_SLVSEL_SSEL1_EN

/* Size info */
#define PROLOGUE_SIZE			8u
#define SECTOR_SIZE				256u
#define JEDEC_SIZE				3u
#define STATUS_SIZE				1u

/* status bits */
#define MAX_TIMEOUT				0xffffffu  /* wait-on-busy */
#define SR1_BUSY_BIT			0x01u	/* S0 in SR1 */
#define SR1_WEL_BIT				0x02u	/* S1 in SR1 */
#define SR1_QE_BIT				0x40u	/* S6 in SR1 */
#define SR2_QE_BIT				0x02u	/* S9 in SR2 */

/* Select SPI Flash Commands */
#define CMD_RESET_ENABLE		0x66u
#define CMD_RESET_DEVICE		0x99u

#define CMD_SR1_READ			0x05u
#define CMD_SR2_READ			0x35u

#define CMD_SR1_WRITE			0x01u
#define CMD_SR2_WRITE			0x31u

#define CMD_JEDEC_READ			0x9fu
#define CMD_SECTOR_ERASE		0x20u
#define CMD_BLOCK_ERASE			0xD8u
#define CMD_CHIP_ERASE			0xC7u
#define CMD_WRITE_ENABLE		0x06u

#define CMD_SINGLE_MODE_WRITE	0x02u
#define CMD_SINGLE_MODE_READ	0x03u

#define CMD_DUAL_MODE_READ		0x3bu
#define CMD_QUAD_MODE_WRITE		0x32u
#define CMD_QUAD_MODE_READ		0x6bu
#define CMD_ENABLE_RESET		0x66u
#define CMD_RESET_DEVICE		0x99u

#define SPI2_FLASH_READ			1
#define SPI2_FLASH_WRITE		2

typedef enum _FLASH_ERROR_CODE
{
    NO_ERR,                 /* No Error */
    POLL_TIMEOUT,           /* Polling toggle bit failed */
    VERIFY_WRITE,           /* Verifying write to flash failed */
    INVALID_SECTOR,         /* Invalid Sector */
    INVALID_BLOCK,          /* Invalid Block */
    UNKNOWN_COMMAND,        /* Unknown command */
    PROCESS_COMMAND_ERR,    /* Processing command */
    NOT_READ_ERROR,         /* Could not read memory from target */
    DRV_NOTAT_BREAK,        /* The application was not at AFP_BreakReady */
    BUFFER_IS_NULL,         /* Could not allocate storage for the buffer */
    WRONG_ACCESS,           /* Cannot access the sector or block( could be locked or something is stored there that should not be touched ) */
    WRITE_ERROR,            /* Error writing to memory */
    NO_MODE_SUPPORT,        /* Not a supported operating mode */
    SETUP_ERROR,            /* Error in setup */
    NUM_ERROR_CODES
}FLASH_ERROR_CODE;

FLASH_ERROR_CODE FlashEraseAll( void );
FLASH_ERROR_CODE FlashEraseSector( int nSector );
FLASH_ERROR_CODE FlashEraseBlock( int nBlock );
FLASH_ERROR_CODE FlashRead(uint8_t *puDest, uint32_t uDataSize, uint32_t uDataOffset);
FLASH_ERROR_CODE FlashWrite(uint8_t *puDest, uint32_t uDataSize, uint32_t uDataOffset);
FLASH_ERROR_CODE FlashErase(uint32_t uDataSize, uint32_t uDataOffset);
uint32_t FlashSectorSize(void);
uint32_t FlashBlockSize(void);
void FlashChangeMode(int nMode, void *sAddr, void *eAddr); /* 0 : General QSPI Mode, 1: Memory Mapped Mode */

void EraseFlashSector(uint32_t address);
void EraseFlashBlock(uint32_t address);
int8_t ReadFlashData(uint8_t *data, uint32_t address, uint32_t count);
int8_t WriteFlashData(uint8_t *data, uint32_t address, uint32_t count);


#endif /* _DRV_FLASH_H_ */

