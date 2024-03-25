


#include "drv_usart_poll.h"
#include "sys.h"
#include "drv_gpio.h"


void Usart_Poll_Init(uint8_t bound)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;
    NVIC_InitTypeDef NVIC_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1, ENABLE);
    //Usart_TX端口配置
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Pin = USART1_TXD_PIN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART1_TXD_PORT, &GPIO_InitStruct);
    //Usart_RX端口配置
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStruct.GPIO_Pin = USART1_RXD_PIN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(USART1_RXD_PORT, &GPIO_InitStruct);
    //Usart 参数初始化
    USART_InitStruct.USART_BaudRate = bound;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStruct);

 #if EN_USART1_pool_RX //如果使能了接�?
    //⑤初始化 NVIC
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ; //抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //子优先级 3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ 通道使能
    NVIC_Init(&NVIC_InitStructure);
    USART_ITConfig(USART1, USART_FLAG_RXNE, ENABLE);
 #endif
    USART_Cmd(USART1, ENABLE);
}



