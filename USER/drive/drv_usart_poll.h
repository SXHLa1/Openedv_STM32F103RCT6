#ifndef __DRV_USART_POLL_H
#define __DRV_USART_POLL_H
#include "sys.h"

#define TxPort  GPIOA
#define TxPin   GPIO_Pin_9
#define RxPort  GPIOA
#define RxPin   GPIO_Pin_10
#define BaudRate 9600
#define EN_USART1_RX 			0		//使能�?�?禁止�?）串�?接收
#define Tx_Buffer  6


void Usart_Poll_Init(void);
void Usart_SendChar(USART_TypeDef* USARTx,  char data);
char Usart_GetChar(USART_TypeDef* USARTx);



#endif
