/*****************************************************************************
 * DRV_UART.h
 *****************************************************************************/

#ifndef __DRV_UART_H__
#define __DRV_UART_H__

void InitUART_CAN(uint32_t baudrate);
void ResetUART_CAN(void);
void SetTxBusyUART_CAN(int32_t flag);


void ConfigUART_CAN(int rw, unsigned char *address, unsigned int size);
void DoneRxDMAIRQUART_CAN(void);
void DoneTxDMAIRQUART_CAN(void);
int32_t GetRxAddrUART_CAN(void);

#endif /* __DRV_UART_H__ */
