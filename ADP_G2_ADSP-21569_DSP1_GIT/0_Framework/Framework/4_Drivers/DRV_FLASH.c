
#include "common.h"
#include "DRV_FLASH.h"
#include "SYSTEM_CACHE.h"
#include "Variation_MASD.h"
#include "DRV_SPI.h"
#include "DRV_Timer.h"

#define FLASH_MM_ADDR 0x60000000

FLASH_ERROR_CODE GetSectorStartEnd( unsigned long *ulStartOff, unsigned long *ulEndOff, int nSector )
{
	unsigned long ulSectorSize = FLASH_SECTOR_SIZE;

	if( ( nSector >= 0 ) && ( nSector < FLASH_NUM_SECTORS ) ) // 1024 sectors
	{
		*ulStartOff = nSector * ulSectorSize;
		*ulEndOff = ( (*ulStartOff) + ulSectorSize - 1 );
	}
	else
		return INVALID_SECTOR;

	// ok
	return NO_ERR;
}

FLASH_ERROR_CODE GetBlockStartEnd( unsigned long *ulStartOff, unsigned long *ulEndOff, int nBlock )
{
	unsigned long ulBlockSize = FLASH_BLOCK_SIZE;

	if( ( nBlock >= 0 ) && ( nBlock < FLASH_NUM_BLOCKS ) ) // 64 blocks
	{
		*ulStartOff = nBlock * ulBlockSize;
		*ulEndOff = ( (*ulStartOff) + ulBlockSize - 1 );
	}
	else
		return INVALID_BLOCK;

	// ok
	return NO_ERR;
}

//#pragma section("seg_l2_swco")
void FlashCommand(uint8_t Inst)
{
	uint8_t bufferInst;

	bufferInst = Inst;
	SPI2_Write(&bufferInst, 1);
}

//#pragma section("seg_l2_swco")
uint8_t FlashRegister(int8_t rw, uint8_t Inst, uint8_t data)
{
	uint8_t bufferInst;
	uint8_t bufferData;

	bufferInst = Inst;
	bufferData = data;

	SPI2_Select();

	SPI2_Write(&bufferInst, 1);
	if(rw == SPI2_FLASH_WRITE)
		SPI2_Write(&bufferData, 1);
	else if (rw ==  SPI2_FLASH_READ)
		SPI2_Read(&bufferData, 1);

	SPI2_Deselect();

	return bufferData;
}

//#pragma section("seg_l2_swco")
void GetFlashInfo(uint8_t *ManID, uint16_t *DevID)
{
	uint8_t buffer;

	SPI2_Select();

	buffer = 0x9F;
	SPI2_Write(&buffer, 1);
	SPI2_Read(ManID, 1);
	SPI2_Read(&buffer, 1);
	*DevID = (buffer<<8);
	SPI2_Read(&buffer, 1);
	*DevID |= buffer;

	SPI2_Deselect();
}

FLASH_ERROR_CODE FlashEraseAll( void )
{
	uint8_t Stat1Reg;
	volatile int32_t nRdTmzC = 0, nDiffTmzC = 0;

	SPI2_Select();
	FlashCommand(CMD_WRITE_ENABLE);
	SPI2_Deselect();

	SPI2_Select();
	nRdTmzC = GetgTmzC();
	do {
		Stat1Reg = FlashRegister(SPI2_FLASH_READ, CMD_SR1_READ, 0);
		nDiffTmzC = GetgTmzC()-nRdTmzC;
		if(nDiffTmzC>1 ) /* past 5ms ~10ms */
		{
			return POLL_TIMEOUT;
		}
	} while( !(Stat1Reg & SR1_WEL_BIT) );
	SPI2_Deselect();

	SPI2_Select();
	FlashCommand(CMD_CHIP_ERASE);
	SPI2_Deselect();
	nRdTmzC = GetgTmzC();
	do {
		Stat1Reg = FlashRegister(SPI2_FLASH_READ, CMD_SR1_READ, 0);
		/* Add Check timer and return with error if the status is not changed after 30s */
		nDiffTmzC = GetgTmzC()-nRdTmzC;
		if(nDiffTmzC>(int32_t)(GetgTmz1Sec()*30.0f) ) /* past approximately 30s */
		{
			return POLL_TIMEOUT;
		}
	} while(Stat1Reg & SR1_BUSY_BIT);

	return POLL_TIMEOUT;
}

FLASH_ERROR_CODE FlashEraseSector( int nSector )
{
	unsigned long ulSecStart = 0x0;		//stores the sector start offset
	unsigned long ulSecEnd   = 0x0;		//stores the sector end offset(however we do not use it here)

	uint8_t addr[3];
	uint8_t Stat1Reg;
	volatile int32_t nRdTmzC = 0, nDiffTmzC = 0;
	// Get the sector start offset
	// we get the end offset too however we do not actually use it for Erase sector
#ifdef FLASH_ACCESS_CONTROL
	if( (nSector < (FLASH_ACCESS_START_OFFSET/FLASH_SECTOR_SIZE)) || (nSector > (FLASH_ACCESS_END_OFFSET/FLASH_SECTOR_SIZE)) )
	{
		return WRONG_ACCESS;
	}
#endif
	GetSectorStartEnd( &ulSecStart, &ulSecEnd, nSector );
	addr[0] = (ulSecStart>>16)&0xFF;
	addr[1] = (ulSecStart>>8)&0xFF;
	addr[2] = ulSecStart&0xFF;

	SPI2_Select();
	FlashCommand(CMD_WRITE_ENABLE);
	SPI2_Deselect();

	SPI2_Select();
	nRdTmzC = GetgTmzC();
	do {
		Stat1Reg = FlashRegister(SPI2_FLASH_READ, CMD_SR1_READ, 0);
		nDiffTmzC = GetgTmzC()-nRdTmzC;
		if(nDiffTmzC>1 ) /* past 5ms ~10ms */
		{
			return POLL_TIMEOUT;
		}
	} while( !(Stat1Reg & SR1_WEL_BIT) );
	SPI2_Deselect();

	SPI2_Select();
	FlashCommand(CMD_SECTOR_ERASE);
	SPI2_Write(addr, 3);
	SPI2_Deselect();

	SPI2_Select();
	nRdTmzC = GetgTmzC();
	do {
		Stat1Reg = FlashRegister(SPI2_FLASH_READ, CMD_SR1_READ, 0);
		/* Add Check timer and return with error if the status is not changed after 200ms */
		nDiffTmzC = GetgTmzC()-nRdTmzC;
		if(nDiffTmzC>(int32_t)(GetgTmz1Sec()*0.2f) ) /* past approximately 200ms */
		{
			return POLL_TIMEOUT;
		}
	} while(Stat1Reg & SR1_BUSY_BIT);
	SPI2_Deselect();

	return NO_ERR;
}

FLASH_ERROR_CODE FlashEraseBlock( int nBlock )
{
	unsigned long ulBlkStart = 0x0;		//stores the block start offset
	unsigned long ulBlkEnd   = 0x0;		//stores the block end offset(however we do not use it here)

	uint8_t addr[3];
	uint8_t Stat1Reg;
	volatile int32_t nRdTmzC = 0, nDiffTmzC = 0;
	// Get the block start offset
	// we get the end offset too however we do not actually use it for Erase block
#ifdef FLASH_ACCESS_CONTROL
	if( (nBlock < (FLASH_ACCESS_START_OFFSET/FLASH_BLOCK_SIZE)) || (nBlock > (FLASH_ACCESS_END_OFFSET/FLASH_BLOCK_SIZE)) )
	{
		return WRONG_ACCESS;
	}
#endif
	GetBlockStartEnd( &ulBlkStart, &ulBlkEnd, nBlock );
	addr[0] = (ulBlkStart>>16)&0xFF;
	addr[1] = (ulBlkStart>>8)&0xFF;
	addr[2] = ulBlkStart&0xFF;

	SPI2_Select();
	FlashCommand(CMD_WRITE_ENABLE);
	SPI2_Deselect();

	SPI2_Select();
	nRdTmzC = GetgTmzC();
	do {
		Stat1Reg = FlashRegister(SPI2_FLASH_READ, CMD_SR1_READ, 0);
		nDiffTmzC = GetgTmzC()-nRdTmzC;
		if(nDiffTmzC>1 ) /* past 5ms ~10ms */
		{
			return POLL_TIMEOUT;
		}
	} while( !(Stat1Reg & SR1_WEL_BIT) );
	SPI2_Deselect();

	SPI2_Select();
	FlashCommand(CMD_BLOCK_ERASE);
	SPI2_Write(addr, 3);
	SPI2_Deselect();

	SPI2_Select();
	nRdTmzC = GetgTmzC();
	do {
		Stat1Reg = FlashRegister(SPI2_FLASH_READ, CMD_SR1_READ, 0);
		/* Add Check timer and return with error if the status is not changed after 1s */
		nDiffTmzC = GetgTmzC()-nRdTmzC;
		if(nDiffTmzC>(int32_t)(GetgTmz1Sec()*1.0f) ) /* past approximately 1s */
		{
			return POLL_TIMEOUT;
		}
	} while(Stat1Reg & SR1_BUSY_BIT);
	SPI2_Deselect();

	return NO_ERR;
}

FLASH_ERROR_CODE FlashRead(uint8_t *puDest, uint32_t uDataSize, uint32_t uDataOffset)
{
	uint32_t i=0;

#ifdef FLASH_ACCESS_CONTROL
	if( (uDataOffset < (FLASH_ACCESS_START_OFFSET)) || (uDataOffset > (FLASH_ACCESS_END_OFFSET)) )
	{
		return WRONG_ACCESS;
	}
#endif

	if((*pREG_SPI2_CTL&ENUM_SPI_CTL_MM_EN) == ENUM_SPI_CTL_MM_EN)
	{
		for(i=0; i<uDataSize; i++)
		{
			puDest[i] = *((int8_t *)FLASH_MM_ADDR + uDataOffset + i);
		}
	}
	else
	{
		uint8_t addr[3];
		addr[0] = (uDataOffset>>16)&0xFF;
		addr[1] = (uDataOffset>>8)&0xFF;
		addr[2] = uDataOffset&0xFF;
		SPI2_Select();
		FlashCommand(CMD_SINGLE_MODE_READ);
		SPI2_Write(addr, 3);
		SPI2_Read(puDest, uDataSize);
		SPI2_Deselect();
	}

	return NO_ERR;
}

FLASH_ERROR_CODE FlashWrite(uint8_t *puDest, uint32_t uDataSize, uint32_t uDataOffset)
{
	uint8_t addr[3];
	uint8_t Stat1Reg;
	int32_t NumPage=0,i;
	volatile int32_t nRdTmzC = 0, nDiffTmzC = 0;
	volatile int32_t nStatCnt1 = 0, nStatCnt2=0;

#ifdef FLASH_ACCESS_CONTROL
	if( (uDataOffset < (FLASH_ACCESS_START_OFFSET)) || (uDataOffset > (FLASH_ACCESS_END_OFFSET)) )
	{
		return WRONG_ACCESS;
	}
#endif

	NumPage = (uDataSize&0xFFFFFF00)>>8;
	if(uDataSize&0xFF)
	{
		NumPage += 1;
	}

	for(i=0; i<NumPage; i++)
	{
		addr[0] = (uDataOffset>>16)&0xFF;
		addr[1] = (uDataOffset>>8)&0xFF;
		addr[2] = uDataOffset&0xFF;

		SPI2_Select();
		FlashCommand(CMD_WRITE_ENABLE);
		SPI2_Deselect();

		SPI2_Select();
		nRdTmzC = GetgTmzC();
		do {
			Stat1Reg = FlashRegister(SPI2_FLASH_READ, CMD_SR1_READ, 0);
			nDiffTmzC = GetgTmzC()-nRdTmzC;
			if(nDiffTmzC>1 ) /* past 5ms ~10ms */
			{
				return POLL_TIMEOUT;
			}
		} while( !(Stat1Reg & SR1_WEL_BIT) );
		SPI2_Deselect();

		SPI2_Select();
		FlashCommand(CMD_SINGLE_MODE_WRITE);
		SPI2_Write(addr, 3);
		if(uDataSize<FLASH_PAGE_SIZE)
		{
			SPI2_Write((puDest+i*FLASH_PAGE_SIZE), uDataSize);
		}
		else
		{
			SPI2_Write((puDest+i*FLASH_PAGE_SIZE), FLASH_PAGE_SIZE);
		}
		SPI2_Deselect();

		SPI2_Select();
		nRdTmzC = GetgTmzC();
		do {
			Stat1Reg = FlashRegister(SPI2_FLASH_READ, CMD_SR1_READ, 0);
			/* Add Check timer and return with error if the status is not changed after 1.2ms */
			nDiffTmzC = GetgTmzC()-nRdTmzC;
			if(nDiffTmzC>1 ) /* past 5ms ~10ms */
			{
				return POLL_TIMEOUT;
			}
		} while( Stat1Reg & SR1_BUSY_BIT );
		SPI2_Deselect();

		uDataSize -= FLASH_PAGE_SIZE;
		uDataOffset += FLASH_PAGE_SIZE;
	}
	return NO_ERR;
}

FLASH_ERROR_CODE FlashErase(uint32_t uDataSize, uint32_t uDataOffset)
{
	int32_t FlashAddress;
	int32_t FlashDataSize;
	int32_t FlashEraseNo = uDataOffset/ FLASH_SECTOR_SIZE;
	FLASH_ERROR_CODE nErrorCode = NO_ERR;

#ifdef FLASH_ACCESS_CONTROL
	if( (uDataOffset < (FLASH_ACCESS_START_OFFSET)) || (uDataOffset > (FLASH_ACCESS_END_OFFSET)) )
	{
		return WRONG_ACCESS;
	}
	else if( (uDataOffset+uDataSize-1) > (FLASH_ACCESS_END_OFFSET) )
	{
		return WRONG_ACCESS;
	}
#endif

	FlashAddress = uDataOffset;
	FlashDataSize = uDataSize;
	do {
		FlashEraseNo = FlashAddress/ FLASH_SECTOR_SIZE;
		nErrorCode = FlashEraseSector(FlashEraseNo);
		if(nErrorCode != NO_ERR)
		{
			return nErrorCode;
		}
		FlashAddress += FLASH_SECTOR_SIZE;
		FlashDataSize -= FLASH_SECTOR_SIZE;
	} while(FlashDataSize > 0);

	return nErrorCode;
}

uint32_t FlashSectorSize(void)
{
	return FLASH_SECTOR_SIZE;
}

uint32_t FlashBlockSize(void)
{
	return FLASH_BLOCK_SIZE;
}

void FlashChangeMode(int nMode, void *sAddr, void *eAddr)
{
	if (nMode)
	{/* Memory Mapped Mode */
#ifdef USE_SPI2_MM_FLASH
		DisableSPI2();
		SetupSPI2MM();
		FlushCache(sAddr, eAddr, ADI_FLUSH_DATA_INV);
#endif
		ChangeModeAudioProcessing(0); /* restart */
	}
	else
	{/* General QSPI Mode */
		ChangeModeAudioProcessing(1); /* blocked */
#ifdef USE_SPI2_MM_FLASH
		FlushCache(sAddr, eAddr, ADI_FLUSH_DATA_INV);
		DisableSPI2();
		InitSPI2();
#endif
	}
}

//#pragma section("seg_l2_swco")
void EraseFlashSector(uint32_t address)
{
	uint8_t Stat1Reg;
	uint8_t addr[3];
	addr[0] = (address>>16)&0xFF;
	addr[1] = (address>>8)&0xFF;
	addr[2] = address&0xFF;

	SPI2_Select();
	FlashCommand(CMD_WRITE_ENABLE);
	SPI2_Deselect();

	SPI2_Select();
	do {
		Stat1Reg = FlashRegister(SPI2_FLASH_READ, CMD_SR1_READ, 0);
	} while( !(Stat1Reg & SR1_WEL_BIT) );
	SPI2_Deselect();

	SPI2_Select();
	FlashCommand(CMD_SECTOR_ERASE);
	SPI2_Write(addr, 3);
	SPI2_Deselect();

	SPI2_Select();
	do {
		Stat1Reg = FlashRegister(SPI2_FLASH_READ, CMD_SR1_READ, 0);
	} while(Stat1Reg & SR1_BUSY_BIT);

	SPI2_Deselect();
}

//#pragma section("seg_l2_swco")
void EraseFlashBlock(uint32_t address)
{
	uint8_t Stat1Reg;
	uint8_t addr[3];
	addr[0] = (address>>16)&0xFF;
	addr[1] = (address>>8)&0xFF;
	addr[2] = address&0xFF;

	SPI2_Select();
	FlashCommand(CMD_WRITE_ENABLE);
	SPI2_Deselect();

	SPI2_Select();
	do {
		Stat1Reg = FlashRegister(SPI2_FLASH_READ, CMD_SR1_READ, 0);
	} while( !(Stat1Reg & SR1_WEL_BIT) );
	SPI2_Deselect();

	SPI2_Select();
	FlashCommand(CMD_BLOCK_ERASE);
	SPI2_Write(addr, 3);
	SPI2_Deselect();

	SPI2_Select();
	do {
		Stat1Reg = FlashRegister(SPI2_FLASH_READ, CMD_SR1_READ, 0);
	} while(Stat1Reg & SR1_BUSY_BIT);

	SPI2_Deselect();
}

//#pragma section("seg_l2_swco")
int8_t ReadFlashData(uint8_t *data, uint32_t address, uint32_t count)
{
	int8_t nRet = 0;
	uint32_t i=0;

	if((*pREG_SPI2_CTL&ENUM_SPI_CTL_MM_EN) == ENUM_SPI_CTL_MM_EN)
	{
		for(i=0; i<count; i++)
		{
			data[i] = *((int8_t *)FLASH_MM_ADDR + address + i);
		}
	}
	else
	{
		uint8_t addr[3];
		addr[0] = (address>>16)&0xFF;
		addr[1] = (address>>8)&0xFF;
		addr[2] = address&0xFF;
		SPI2_Select();
		FlashCommand(CMD_SINGLE_MODE_READ);
		nRet = SPI2_Write(addr, 3);
		if(nRet < 0)
		{
			SPI2_Deselect();
			return nRet;
		}
		nRet = SPI2_Read(data, count);
		if(nRet < 0)
		{
			SPI2_Deselect();
			return nRet;
		}
		SPI2_Deselect();
	}

	return nRet;
}

//#pragma section("seg_l2_swco")
int8_t WriteFlashData(uint8_t *data, uint32_t address, uint32_t count)
{
	int8_t nRet = 0;
	uint8_t Stat1Reg;
	uint8_t addr[3];
	int32_t NumPage=0,i;

	NumPage = (count&0xFFFFFF00)>>8;
	if(count&0xFF)
	{
		NumPage += 1;
	}

	for(i=0; i<NumPage; i++)
	{
		addr[0] = (address>>16)&0xFF;
		addr[1] = (address>>8)&0xFF;
		addr[2] = address&0xFF;

		SPI2_Select();
		FlashCommand(CMD_WRITE_ENABLE);
		SPI2_Deselect();

		SPI2_Select();
		do {
			Stat1Reg = FlashRegister(SPI2_FLASH_READ, CMD_SR1_READ, 0);
		} while( !(Stat1Reg & SR1_WEL_BIT) );
		SPI2_Deselect();

		SPI2_Select();
		FlashCommand(CMD_SINGLE_MODE_WRITE);
		nRet = SPI2_Write(addr, 3);
		if(nRet < 0)
		{
			SPI2_Deselect();
			return nRet;
		}
		if(count<FLASH_PAGE_SIZE)
		{
			nRet = SPI2_Write((data+i*FLASH_PAGE_SIZE), count);
		}
		else
		{
			nRet = SPI2_Write((data+i*FLASH_PAGE_SIZE), FLASH_PAGE_SIZE);
		}
		if(nRet < 0)
		{
			SPI2_Deselect();
			return nRet;
		}
		SPI2_Deselect();

		SPI2_Select();
		do {
			Stat1Reg = FlashRegister(SPI2_FLASH_READ, CMD_SR1_READ, 0);
		} while( Stat1Reg & SR1_BUSY_BIT );
		SPI2_Deselect();

		count -= FLASH_PAGE_SIZE;
		address += FLASH_PAGE_SIZE;
	}
	return nRet;
}

