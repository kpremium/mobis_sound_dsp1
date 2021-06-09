/*
 **
 ** Source file generated on 5¿ù 3, 2021 at 17:20:43.	
 **
 ** Copyright (C) 2011-2021 Analog Devices Inc., All Rights Reserved.
 **
 ** This file is generated automatically based upon the options selected in 
 ** the Pin Multiplexing configuration editor. Changes to the Pin Multiplexing
 ** configuration should be made by changing the appropriate options rather
 ** than editing this file.
 **
 ** Selected Peripherals
 ** --------------------
 ** LP1 (ACK, CLK, D0, D1, D2, D3, D4, D5, D6, D7)
 ** SPI0 (CLK, MISO, MOSI, SEL1)
 ** SPI1 (CLK, MISO, MOSI, SEL1)
 ** SPI2 (CLK, D2, D3, MISO, MOSI, SEL1)
 ** UART1 (RX, TX)
 ** UART2 (RX, TX)
 **
 ** GPIO (unavailable)
 ** ------------------
 ** PA00, PA01, PA02, PA03, PA04, PA05, PA06, PA07, PA08, PA09, PA10, PA11, PA12,
 ** PA13, PA14, PA15, PB02, PB11, PB12, PB15, PC00, PC01, PC02, PC03, PC04, PC05,
 ** PC06, PC07
 */

#include <sys/platform.h>
#include <stdint.h>

#define LP1_ACK_PORTB_MUX  ((uint16_t) ((uint16_t) 2<<4))
#define LP1_CLK_PORTC_MUX  ((uint16_t) ((uint16_t) 0<<14))
#define LP1_D0_PORTB_MUX  ((uint32_t) ((uint32_t) 0<<30))
#define LP1_D1_PORTC_MUX  ((uint16_t) ((uint16_t) 0<<0))
#define LP1_D2_PORTC_MUX  ((uint16_t) ((uint16_t) 0<<2))
#define LP1_D3_PORTC_MUX  ((uint16_t) ((uint16_t) 0<<4))
#define LP1_D4_PORTC_MUX  ((uint16_t) ((uint16_t) 0<<6))
#define LP1_D5_PORTC_MUX  ((uint16_t) ((uint16_t) 0<<8))
#define LP1_D6_PORTC_MUX  ((uint16_t) ((uint16_t) 0<<10))
#define LP1_D7_PORTC_MUX  ((uint16_t) ((uint16_t) 0<<12))
#define SPI0_CLK_PORTA_MUX  ((uint16_t) ((uint16_t) 0<<12))
#define SPI0_MISO_PORTA_MUX  ((uint16_t) ((uint16_t) 0<<14))
#define SPI0_MOSI_PORTA_MUX  ((uint32_t) ((uint32_t) 0<<16))
#define SPI0_SEL1_PORTA_MUX  ((uint32_t) ((uint32_t) 0<<18))
#define SPI1_CLK_PORTA_MUX  ((uint32_t) ((uint32_t) 1<<20))
#define SPI1_MISO_PORTA_MUX  ((uint32_t) ((uint32_t) 1<<22))
#define SPI1_MOSI_PORTA_MUX  ((uint32_t) ((uint32_t) 1<<24))
#define SPI1_SEL1_PORTA_MUX  ((uint32_t) ((uint32_t) 1<<26))
#define SPI2_CLK_PORTA_MUX  ((uint16_t) ((uint16_t) 0<<8))
#define SPI2_D2_PORTA_MUX  ((uint16_t) ((uint16_t) 0<<4))
#define SPI2_D3_PORTA_MUX  ((uint16_t) ((uint16_t) 0<<6))
#define SPI2_MISO_PORTA_MUX  ((uint16_t) ((uint16_t) 0<<0))
#define SPI2_MOSI_PORTA_MUX  ((uint16_t) ((uint16_t) 0<<2))
#define SPI2_SEL1_PORTA_MUX  ((uint16_t) ((uint16_t) 0<<10))
#define UART1_RX_PORTA_MUX  ((uint32_t) ((uint32_t) 2<<28))
#define UART1_TX_PORTA_MUX  ((uint32_t) ((uint32_t) 2<<30))
#define UART2_RX_PORTB_MUX  ((uint32_t) ((uint32_t) 3<<22))
#define UART2_TX_PORTB_MUX  ((uint32_t) ((uint32_t) 3<<24))

#define LP1_ACK_PORTB_FER  ((uint16_t) ((uint16_t) 1<<2))
#define LP1_CLK_PORTC_FER  ((uint16_t) ((uint16_t) 1<<7))
#define LP1_D0_PORTB_FER  ((uint32_t) ((uint32_t) 1<<15))
#define LP1_D1_PORTC_FER  ((uint16_t) ((uint16_t) 1<<0))
#define LP1_D2_PORTC_FER  ((uint16_t) ((uint16_t) 1<<1))
#define LP1_D3_PORTC_FER  ((uint16_t) ((uint16_t) 1<<2))
#define LP1_D4_PORTC_FER  ((uint16_t) ((uint16_t) 1<<3))
#define LP1_D5_PORTC_FER  ((uint16_t) ((uint16_t) 1<<4))
#define LP1_D6_PORTC_FER  ((uint16_t) ((uint16_t) 1<<5))
#define LP1_D7_PORTC_FER  ((uint16_t) ((uint16_t) 1<<6))
#define SPI0_CLK_PORTA_FER  ((uint16_t) ((uint16_t) 1<<6))
#define SPI0_MISO_PORTA_FER  ((uint16_t) ((uint16_t) 1<<7))
#define SPI0_MOSI_PORTA_FER  ((uint32_t) ((uint32_t) 1<<8))
#define SPI0_SEL1_PORTA_FER  ((uint32_t) ((uint32_t) 1<<9))
#define SPI1_CLK_PORTA_FER  ((uint32_t) ((uint32_t) 1<<10))
#define SPI1_MISO_PORTA_FER  ((uint32_t) ((uint32_t) 1<<11))
#define SPI1_MOSI_PORTA_FER  ((uint32_t) ((uint32_t) 1<<12))
#define SPI1_SEL1_PORTA_FER  ((uint32_t) ((uint32_t) 1<<13))
#define SPI2_CLK_PORTA_FER  ((uint16_t) ((uint16_t) 1<<4))
#define SPI2_D2_PORTA_FER  ((uint16_t) ((uint16_t) 1<<2))
#define SPI2_D3_PORTA_FER  ((uint16_t) ((uint16_t) 1<<3))
#define SPI2_MISO_PORTA_FER  ((uint16_t) ((uint16_t) 1<<0))
#define SPI2_MOSI_PORTA_FER  ((uint16_t) ((uint16_t) 1<<1))
#define SPI2_SEL1_PORTA_FER  ((uint16_t) ((uint16_t) 1<<5))
#define UART1_RX_PORTA_FER  ((uint32_t) ((uint32_t) 1<<14))
#define UART1_TX_PORTA_FER  ((uint32_t) ((uint32_t) 1<<15))
#define UART2_RX_PORTB_FER  ((uint32_t) ((uint32_t) 1<<11))
#define UART2_TX_PORTB_FER  ((uint32_t) ((uint32_t) 1<<12))

int32_t adi_initpinmux(void);

/*
 * Initialize the Port Control MUX and FER Registers
 */
int32_t adi_initpinmux(void) {
    /* PORTx_MUX registers */
    *pREG_PORTA_MUX = SPI0_CLK_PORTA_MUX | SPI0_MISO_PORTA_MUX
     | SPI0_MOSI_PORTA_MUX | SPI0_SEL1_PORTA_MUX | SPI1_CLK_PORTA_MUX
     | SPI1_MISO_PORTA_MUX | SPI1_MOSI_PORTA_MUX | SPI1_SEL1_PORTA_MUX
     | SPI2_CLK_PORTA_MUX | SPI2_D2_PORTA_MUX | SPI2_D3_PORTA_MUX
     | SPI2_MISO_PORTA_MUX | SPI2_MOSI_PORTA_MUX | SPI2_SEL1_PORTA_MUX
     | UART1_RX_PORTA_MUX | UART1_TX_PORTA_MUX;
    *pREG_PORTB_MUX = LP1_ACK_PORTB_MUX | LP1_D0_PORTB_MUX
     | UART2_RX_PORTB_MUX | UART2_TX_PORTB_MUX;
    *pREG_PORTC_MUX = LP1_CLK_PORTC_MUX | LP1_D1_PORTC_MUX
     | LP1_D2_PORTC_MUX | LP1_D3_PORTC_MUX | LP1_D4_PORTC_MUX
     | LP1_D5_PORTC_MUX | LP1_D6_PORTC_MUX | LP1_D7_PORTC_MUX;

    /* PORTx_FER registers */
    *pREG_PORTA_FER = SPI0_CLK_PORTA_FER | SPI0_MISO_PORTA_FER
     | SPI0_MOSI_PORTA_FER | SPI0_SEL1_PORTA_FER | SPI1_CLK_PORTA_FER
     | SPI1_MISO_PORTA_FER | SPI1_MOSI_PORTA_FER | SPI1_SEL1_PORTA_FER
     | SPI2_CLK_PORTA_FER | SPI2_D2_PORTA_FER | SPI2_D3_PORTA_FER
     | SPI2_MISO_PORTA_FER | SPI2_MOSI_PORTA_FER | SPI2_SEL1_PORTA_FER
     | UART1_RX_PORTA_FER | UART1_TX_PORTA_FER;
    *pREG_PORTB_FER = LP1_ACK_PORTB_FER | LP1_D0_PORTB_FER
     | UART2_RX_PORTB_FER | UART2_TX_PORTB_FER;
    *pREG_PORTC_FER = LP1_CLK_PORTC_FER | LP1_D1_PORTC_FER
     | LP1_D2_PORTC_FER | LP1_D3_PORTC_FER | LP1_D4_PORTC_FER
     | LP1_D5_PORTC_FER | LP1_D6_PORTC_FER | LP1_D7_PORTC_FER;
    return 0;
}

