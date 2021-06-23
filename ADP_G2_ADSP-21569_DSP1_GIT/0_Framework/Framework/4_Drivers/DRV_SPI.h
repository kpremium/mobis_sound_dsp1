/*****************************************************************************
 * DRV_SPI.h
 *****************************************************************************/

#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

/* for Memory Mapped SPI mode */
#define USE_SPI2_MM_FLASH

void ISR_SPI0_RX(unsigned int id, void* arg);
void ISR_SPI0_TX(unsigned int id, void* arg);

void InitSPI2(void);
void DisableSPI2(void);

int8_t SPI2_Read(uint8_t *data, int32_t count);
int8_t SPI2_Write(uint8_t *data, int32_t count);
void SPI2_Select(void);
void SPI2_Deselect(void);

void SetupSPI2MM(void);

//void SPI0_RX_ISR(void);
//void SPI0_TX_ISR(void);
//void SPI1_RX_ISR(void);
//void SPI1_TX_ISR(void);
int DRV_SPI_Init(void);

void select_SPI2_flash(void);
void deselect_SPI2_flash(void);


#endif /* __DRV_SPI_H__ */
