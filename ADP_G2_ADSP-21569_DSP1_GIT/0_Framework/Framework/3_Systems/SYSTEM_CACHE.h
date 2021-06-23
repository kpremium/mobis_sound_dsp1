/*****************************************************************************
 * SYSTEM_CACHE.h
 *****************************************************************************/

#ifndef __SYSTEM_CACHE_H__
#define __SYSTEM_CACHE_H__

/* All caches are set for 16kB size */
#define DISABLE_I_D_CACHE					(0x404040)
#define ENABLE_I_D_CACHE					(0x414141)
#define ENABLE_I_CACHE_ONLY					(0x404041)
#define ENABLE_D_CACHE_ONLY					(0x414140)

#define L2_BW_START_ADDRESS					(0x20000000)
#define L2_BW_END_ADDRESS					(0x200BFFFF)
#define L2_BW_UNCACHED_START_ADDRESS		(0x200C0000)
#define L2_BW_UNCACHED_END_ADDRESS			(0x200FFFFF)
#define L2_SW_START_ADDRESS					(0x00B80000)
#define L2_SW_END_ADDRESS					(0x00BDFFFF)
#define L1_MP_START_ADDRESS					(0x28240000)
#define L1_MP_END_ADDRESS					(0x2839FFFF)
#define SPI2_MEM_UNCACHE_START_ADDRESS		(0x60000000)
#define SPI2_MEM_UNCACHE_END_ADDRESS		(0x6041FFFF)

int InitCache(void);
void ConfigCache(void);
void InvalidateCache(void);
void FlushCache(void *sAddr, void *eAddr, int fInv);

#endif /* __SYSTEM_CACHE_H__ */
