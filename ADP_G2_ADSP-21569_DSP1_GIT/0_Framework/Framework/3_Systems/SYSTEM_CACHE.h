/*****************************************************************************
 * SYSTEM_CACHE.h
 *****************************************************************************/

#ifndef __SYSTEM_CACHE_H__
#define __SYSTEM_CACHE_H__

int InitCache(void);
int DoneCache(void);
void ConfigCache(void);
void InvalidateCache(void);
void FlushCache(void *sAddr, void *eAddr, int fInv);

#endif /* __SYSTEM_CACHE_H__ */
