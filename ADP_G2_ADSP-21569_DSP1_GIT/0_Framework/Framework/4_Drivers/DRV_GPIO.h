/*****************************************************************************
 * DRV_GPIO.h
 *****************************************************************************/

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__


uint32_t DRV_GPIO_Init(void);

void ClrGPIO_PB02(void);
void SetGPIO_PB02(void);
void SetGPIO_PB04(void);
void ClrGPIO_PB04(void);
void SetGPIO_PB06(void);
void ClrGPIO_PB06(void);

#endif /* __DRV_GPIO_H__ */
