/*****************************************************************************
 * DRV_ASRC.c
 *****************************************************************************/
#include <sru21569.h>
#include "common.h"
#include "DRV_ASRC.h"
#include "Variation_MASD.h"

#if 1

/******************************************************************************
	1. Macros
 ******************************************************************************/

#ifdef CORE1
//#define _DEBUG_ASRC_
#endif

#ifdef CORE2
//#define _DEBUG_ASRC_
#endif

#ifdef _DEBUG_ASRC_
#define DBG_TRACE(x) printf x
#else
#define DBG_TRACE(x) (void)0
#endif

/******************************************************************************
	2. Enumerations
 ******************************************************************************/


/******************************************************************************
	3. Typedefs
 ******************************************************************************/


/******************************************************************************
	4. Functions
 ******************************************************************************/

static uint32_t DRV_ASRC_Config(uint8_t ePeriId, uint8_t fAutoMute, uint8_t eIFormat, uint8_t eOFormat, uint8_t eWordLen, uint8_t fMuteOut);

/******************************************************************************
	5. Variables
 ******************************************************************************/

/* ASRC Configuration Structure */
static S_DRV_ASRC_CFGS saoAsrcCfgs[E_DRV_ASRC_PERI_MAX] =
{
	(S_DRV_ASRC_REGS *)D_DRV_ASRC0123_BASE_ADDR,
	(S_DRV_ASRC_REGS *)D_DRV_ASRC0123_BASE_ADDR,
	(S_DRV_ASRC_REGS *)D_DRV_ASRC0123_BASE_ADDR,
	(S_DRV_ASRC_REGS *)D_DRV_ASRC0123_BASE_ADDR,
	(S_DRV_ASRC_REGS *)D_DRV_ASRC4567_BASE_ADDR,
	(S_DRV_ASRC_REGS *)D_DRV_ASRC4567_BASE_ADDR,
	(S_DRV_ASRC_REGS *)D_DRV_ASRC4567_BASE_ADDR,
	(S_DRV_ASRC_REGS *)D_DRV_ASRC4567_BASE_ADDR
};

/* ==================================================================================================================================================== */
/* ==================================================================================================================================================== */
uint32_t DRV_ASRC_Init(void)
{
	uint32_t aa;
	uint32_t result = PASSED; // FAILED or PASSED

	ASRCInfo_t *ASRCInfo = (ASRCInfo_t *)GetDriverVariationPtr(Driver_ASRC);

	for(aa = 0; aa < ASRC_MAX; aa++) {

		// Validation Code
		if(ASRCInfo[aa].AsrcIdx != aa) {
			return FAILED;
		}

		if(ASRCInfo[aa].IsUsed) {
			result |= DRV_ASRC_Config(ASRCInfo[aa].PeriId, ASRCInfo[aa].AutoMute, ASRCInfo[aa].IFormat, ASRCInfo[aa].OFormat, ASRCInfo[aa].WordLen, ASRCInfo[aa].MuteOut);
		}
	}

	// Validation Code
	if(ASRCInfo[aa - 1].AsrcIdx != (ASRC_MAX - 1)) {
		return FAILED;
	}

	return result;
}


static uint32_t DRV_ASRC_Config(uint8_t ePeriId, uint8_t fAutoMute, uint8_t eIFormat, uint8_t eOFormat, uint8_t eWordLen, uint8_t fMuteOut)
{
	S_DRV_ASRC_CFGS * poAsrcCfgs;
	// Temporary Register Values
	uint32_t nRegMute;
	uint32_t nRegCtl;

	if (ePeriId >= E_DRV_ASRC_PERI_MAX) {
		DBG_TRACE(("|ASRC| INVALID PERI %d\n", ePeriId));
		return (FAILED);
	}

	poAsrcCfgs = &saoAsrcCfgs[ePeriId];
	if (poAsrcCfgs == NULL) {
		DBG_TRACE(("|ASRC| INVALID CFGS %d\n", ePeriId));
		return (FAILED);
	}

	DBG_TRACE(("|ASRC| CONFIG PERI %d\n", ePeriId));

	switch (ePeriId) {
		case E_DRV_ASRC0:
		case E_DRV_ASRC4:
			/* Configure MUTE Register of ASRC 0/4 */
			nRegMute = poAsrcCfgs->pASRCRegs->MUTE & ~(BITM_ASRC_MUTE_MUTE0);
			DBG_TRACE(("|ASRC| OLD regMUTE %08x\n", nRegMute));
			nRegMute = nRegMute | (fMuteOut << BITP_ASRC_MUTE_MUTE0);
			DBG_TRACE(("|ASRC| NEW regMUTE %08x\n", nRegMute));
			poAsrcCfgs->pASRCRegs->MUTE = nRegMute;

			/* Configure CTL01 Register of ASRC 0/4 */
			nRegCtl = poAsrcCfgs->pASRCRegs->CTL01 & 0xFFFF0000;
			DBG_TRACE(("|ASRC| OLD regCTL %08x\n", nRegCtl));
			nRegCtl = nRegCtl |
					( (fAutoMute << BITP_ASRC_CTL01_AUTOMUTE0)
					| (eIFormat << BITP_ASRC_CTL01_SMODEIN0)
					| (eOFormat << BITP_ASRC_CTL01_SMODEOUT0)
					| (eWordLen << BITP_ASRC_CTL01_LENOUT0)
					| /*(fEnable << BITP_ASRC_CTL01_EN0)*/BITM_ASRC_CTL01_EN0 );
			DBG_TRACE(("|ASRC| NEW regCTL %08x\n", nRegCtl));
			poAsrcCfgs->pASRCRegs->CTL01 = nRegCtl;
			break;

		case E_DRV_ASRC1:
		case E_DRV_ASRC5:
			/* Configure MUTE Register of ASRC 1/5 */
			nRegMute = poAsrcCfgs->pASRCRegs->MUTE & ~(BITM_ASRC_MUTE_MUTE1);
			DBG_TRACE(("|ASRC| OLD regMUTE %08x\n", nRegMute));
			nRegMute = nRegMute | (fMuteOut << BITP_ASRC_MUTE_MUTE1);
			DBG_TRACE(("|ASRC| NEW regMUTE %08x\n", nRegMute));
			poAsrcCfgs->pASRCRegs->MUTE = nRegMute;

			/* Configure CTL01 Register of ASRC 1/5 */
			nRegCtl = poAsrcCfgs->pASRCRegs->CTL01 & 0x0000FFFF;
			DBG_TRACE(("|ASRC| OLD regCTL %08x\n", nRegCtl));
			nRegCtl = nRegCtl |
					( (fAutoMute << BITP_ASRC_CTL01_AUTOMUTE1)
					| (eIFormat << BITP_ASRC_CTL01_SMODEIN1)
					| (eOFormat << BITP_ASRC_CTL01_SMODEOUT1)
					| (eWordLen << BITP_ASRC_CTL01_LENOUT1)
					| /*(fEnable << BITP_ASRC_CTL01_EN1)*/BITM_ASRC_CTL01_EN1 );
			DBG_TRACE(("|ASRC| NEW regCTL %08x\n", nRegCtl));
			poAsrcCfgs->pASRCRegs->CTL01 = nRegCtl;
			break;

		case E_DRV_ASRC2:
		case E_DRV_ASRC6:
			/* Configure MUTE Register of ASRC 2/6 */
			nRegMute = poAsrcCfgs->pASRCRegs->MUTE & ~(BITM_ASRC_MUTE_MUTE2);
			DBG_TRACE(("|ASRC| OLD regMUTE %08x\n", nRegMute));
			nRegMute = nRegMute | (fMuteOut << BITP_ASRC_MUTE_MUTE2);
			DBG_TRACE(("|ASRC| NEW regMUTE %08x\n", nRegMute));
			poAsrcCfgs->pASRCRegs->MUTE = nRegMute;

			/* Configure CTL23 Register of ASRC 2/6 */
			nRegCtl = poAsrcCfgs->pASRCRegs->CTL23 & 0xFFFF0000;
			DBG_TRACE(("|ASRC| OLD regCTL %08x\n", nRegCtl));
			nRegCtl = nRegCtl |
					( (fAutoMute << BITP_ASRC_CTL23_AUTOMUTE2)
					| (eIFormat << BITP_ASRC_CTL23_SMODEIN2)
					| (eOFormat << BITP_ASRC_CTL23_SMODEOUT2)
					| (eWordLen << BITP_ASRC_CTL23_LENOUT2)
					| /*(fEnable << BITP_ASRC_CTL23_EN2)*/BITM_ASRC_CTL23_EN2 );
			DBG_TRACE(("|ASRC| NEW regCTL %08x\n", nRegCtl));
			poAsrcCfgs->pASRCRegs->CTL23 = nRegCtl;
			break;

		case E_DRV_ASRC3:
		case E_DRV_ASRC7:
			/* Configure MUTE Register of ASRC 3/7 */
			nRegMute = poAsrcCfgs->pASRCRegs->MUTE & ~(BITM_ASRC_MUTE_MUTE3);
			DBG_TRACE(("|ASRC| OLD regMUTE %08x\n", nRegMute));
			nRegMute = nRegMute | (fMuteOut << BITP_ASRC_MUTE_MUTE3);
			DBG_TRACE(("|ASRC| NEW regMUTE %08x\n", nRegMute));
			poAsrcCfgs->pASRCRegs->MUTE = nRegMute;

			/* Configure CTL23 Register of ASRC 3/7 */
			nRegCtl = poAsrcCfgs->pASRCRegs->CTL23 & 0x0000FFFF;
			DBG_TRACE(("|ASRC| OLD regCTL %08x\n", nRegCtl));
			nRegCtl = nRegCtl |
					( (fAutoMute << BITP_ASRC_CTL23_AUTOMUTE3)
					| (eIFormat << BITP_ASRC_CTL23_SMODEIN3)
					| (eOFormat << BITP_ASRC_CTL23_SMODEOUT3)
					| (eWordLen << BITP_ASRC_CTL23_LENOUT3)
					| /*(fEnable << BITP_ASRC_CTL23_EN3)*/BITM_ASRC_CTL23_EN3 );
			DBG_TRACE(("|ASRC| NEW regCTL %08x\n", nRegCtl));
			poAsrcCfgs->pASRCRegs->CTL23 = nRegCtl;
			break;

		default:
			DBG_TRACE(("|ASRC| INVALID PERI %d\n", ePeriId));
			return (FAILED);
	}

	return (PASSED);
}





#else

uint32_t DRV_ASRC_Init(void)
{
	*pREG_ASRC1_MUTE = (0<<BITP_ASRC_MUTE_MUTE0) | (0<<BITP_ASRC_MUTE_MUTE1) | (0<<BITP_ASRC_MUTE_MUTE2) | (0<<BITP_ASRC_MUTE_MUTE3);
	*pREG_ASRC1_CTL01 = (1<<BITP_ASRC_CTL01_EN0) | (0<<BITP_ASRC_CTL01_LENOUT0) | (1<<BITP_ASRC_CTL01_SMODEOUT0) | (1<<BITP_ASRC_CTL01_SMODEIN0) | (0<<BITP_ASRC_CTL01_AUTOMUTE0);

	return PASSED;
}

#endif

