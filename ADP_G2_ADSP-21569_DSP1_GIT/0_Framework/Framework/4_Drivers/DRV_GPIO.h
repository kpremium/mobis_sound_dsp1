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

#if (EZ_KIT_BOARD == 1u)
void SetGPIO_PB03(void);
void ClrGPIO_PB03(void);
void TglGPIO_PB03(void);
#endif

#endif /* __DRV_GPIO_H__ */
