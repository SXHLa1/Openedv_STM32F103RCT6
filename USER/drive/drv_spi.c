#include"drv_spi.h"





/*
*
*
*
*/
void DRV_SPI_Init(void)
{
  SPI_InitTypeDef SPI_InitStruct;
  GPIO_InitTypeDef GPIO_InitStruct;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_SPI1, ENABLE);

  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_SetBits(GPIOA, GPIO_Pin_5);

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_SetBits(GPIOA, GPIO_Pin_6);
    
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_SetBits(GPIOA, GPIO_Pin_7);

  SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
  SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;

  SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
  SPI_InitStruct.SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, &SPI_InitStruct);
  SPI_Cmd(SPI1, ENABLE);
}

uint8 SPI_ReadWriteByte(uint8 TxData)
{
  uint8 retry = 0;
  while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
  {
    retry++;
    if(retry > 200)
       return 0;
  }
  SPI_I2S_SendData(SPI1, TxData);
  retry = 0;
  while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
  {
    retry++;
    if(retry > 200)
       return 0;
  }
  return SPI_I2S_ReceiveData(SPI1);  
}




