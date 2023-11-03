#ifndef __DRV_SPI_H
#define __DRV_SPI_H
#include "sys.h"
#include "stm32f10x_spi.h"


void DRV_SPI_Init(void);
uint8 SPI_ReadWriteByte(uint8 TxData);


#endif
