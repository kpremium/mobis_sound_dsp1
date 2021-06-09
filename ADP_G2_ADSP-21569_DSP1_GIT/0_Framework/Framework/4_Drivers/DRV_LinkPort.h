/*****************************************************************************
 * initLinkPort.h
 *****************************************************************************/

#ifndef __DRV_LINKPORT_H__
#define __DRV_LINKPORT_H__

#include <adi_types.h>

void InitLinkPort0Rx(void);
void InitLinkPort1Rx(void);
void InitLinkPort0Tx(void);
void InitLinkPort1Tx(void);
void ISR_Linkport0(unsigned int id, void* arg);
void ISR_Linkport1(unsigned int id, void* arg);


#endif /* __DRV_LINKPORT_H__ */
