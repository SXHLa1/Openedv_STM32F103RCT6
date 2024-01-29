#ifdef __DRV_USART_H
#define __DRV_USART_H



#define RX_BUF_LEN      200
extern uint8_t RX_Buffer[RX_BUF_LEN];

void Usart1_Init(uint8_t bound);

#endif