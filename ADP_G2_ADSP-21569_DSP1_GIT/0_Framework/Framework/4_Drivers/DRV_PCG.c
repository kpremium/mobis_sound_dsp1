#include <sru21569.h>

#include "common.h"
#include "DRV_PCG.h"

uint32_t DRV_PCG_Init(void)
{
	*pREG_PCG0_SYNC2 = 0x00;
	*pREG_PCG0_PW2 = (0);
	*pREG_PCG0_CTLC1 = BITM_PCG_CTLC1_FSSRC| BITM_PCG_CTLC1_CLKSRC| 8 | (4<<20);	// I2S
	*pREG_PCG0_CTLC0 = BITM_PCG_CTLC0_FSEN | BITM_PCG_CTLC0_CLKEN | (512);			// 48kHz

	*pREG_PCG0_PW2 |= (0<<16);
	*pREG_PCG0_CTLD1 = 8 | (4<<20);													// I2S
	*pREG_PCG0_CTLD0 = BITM_PCG_CTLD0_FSEN | BITM_PCG_CTLD0_CLKEN | (512);			// 48kHz

	return PASSED;
}
