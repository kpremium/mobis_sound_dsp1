
#include "common.h"
#include <sru21569.h>
#include "DRV_GPIO.h"

#define GPIO_PORTB_00  ((uint16_t) ((uint16_t) 1<<0))
#define GPIO_PORTB_01  ((uint16_t) ((uint16_t) 1<<1))
#define GPIO_PORTB_02  ((uint16_t) ((uint16_t) 1<<2))
#define GPIO_PORTB_03  ((uint16_t) ((uint16_t) 1<<3))
#define GPIO_PORTB_04  ((uint16_t) ((uint16_t) 1<<4))
#define GPIO_PORTB_05  ((uint16_t) ((uint16_t) 1<<5))
#define GPIO_PORTB_06  ((uint16_t) ((uint16_t) 1<<6))
#define GPIO_PORTB_07  ((uint16_t) ((uint16_t) 1<<7))
#define GPIO_PORTB_08  ((uint16_t) ((uint16_t) 1<<8))
#define GPIO_PORTB_09  ((uint16_t) ((uint16_t) 1<<9))
#define GPIO_PORTB_10  ((uint16_t) ((uint16_t) 1<<10))
#define GPIO_PORTB_11  ((uint16_t) ((uint16_t) 1<<11))
#define GPIO_PORTB_12  ((uint16_t) ((uint16_t) 1<<12))
#define GPIO_PORTB_13  ((uint16_t) ((uint16_t) 1<<13))
#define GPIO_PORTB_14  ((uint16_t) ((uint16_t) 1<<14))
#define GPIO_PORTB_15  ((uint16_t) ((uint16_t) 1<<15))

uint32_t DRV_GPIO_Init(void)
{
    *pREG_PORTB_FER_CLR  = GPIO_PORTB_04 | GPIO_PORTB_06 | GPIO_PORTB_07
                         | GPIO_PORTB_05;

    *pREG_PORTB_INEN_CLR = GPIO_PORTB_04 | GPIO_PORTB_06 | GPIO_PORTB_07;
    *pREG_PORTB_INEN_SET = GPIO_PORTB_05;
    *pREG_PORTB_DIR_SET  = GPIO_PORTB_04 | GPIO_PORTB_06 | GPIO_PORTB_07;

    *pREG_PORTB_DATA_CLR = GPIO_PORTB_04 | GPIO_PORTB_06 | GPIO_PORTB_07
                         | GPIO_PORTB_05;

    return PASSED;
}

void SetGPIO_PB04(void)
{
	*pREG_PORTB_DATA_SET = GPIO_PORTB_04;
}

void ClrGPIO_PB04(void)
{
	*pREG_PORTB_DATA_CLR = GPIO_PORTB_04;
}

void SetGPIO_PB06(void)
{
	*pREG_PORTB_DATA_SET = GPIO_PORTB_06;
}

void ClrGPIO_PB06(void)
{
	*pREG_PORTB_DATA_CLR = GPIO_PORTB_06;
}

