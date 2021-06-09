/*****************************************************************************
 * DRV_Interrupt.h
 *****************************************************************************/

#ifndef __DRV_INTERRUPT_H__
#define __DRV_INTERRUPT_H__


uint32_t DRV_Interrupt_Init(void);
void DRV_Interrupt_Enable_UART(bool enableRx, bool enableTx);
void EnableINTR_UART_CAN(bool bEn);
void InitINTR_UART_CAN(void);
void InitINTR_LinkPort(void);

void RegisterBackupA(void);
void RegisterRecoveryA(void);
void RegisterBackupB(void);
void RegisterRecoveryB(void);


#endif /* __DRV_INTERRUPT_H__ */
