#ifndef __DRV_USART_POLL_H
#define __DRV_USART_POLL_H
#include "sys.h"


#define EN_USART1_pool_RX               1       //使能接收中断使能
#define Tx_Buffer                       6       


void Usart_Poll_Init(uint8_t bound);
void Usart_Senddata(USART_TypeDef* USARTx,  uint8_t data);
uint8_t Usart_Getdata(USART_TypeDef* USARTx);



#endif
