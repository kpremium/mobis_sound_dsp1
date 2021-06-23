
#ifndef _COMMSUART_H_
#define _COMMSUART_H_

void InitCommsPkg(void);
void ExecCommsPkg(void);
void ISR_CommsPkg_Rx(unsigned int id, void* arg);
void ISR_CommsPkg_Tx(unsigned int id, void* arg);

float32_t GetRpmCommsPkg(void);
float32_t GetThrottleCommsPkg(void);
float32_t GetTorqueCommsPkg(void);
float32_t GetSpeedCommsPkg(void);
float32_t GetGearCommsPkg(void);
float32_t GetIgnitionCommsPkg(void);
float32_t GetVolStepCommsPkg(void);
float32_t GetDrvModeCommsPkg(void);
float32_t GetMstGainCommsPkg(void);
float32_t GetSignatureCommsPkg(void);
float32_t GetParameterCommsPkg(void);

#endif /* _COMMSUART_H_ */

