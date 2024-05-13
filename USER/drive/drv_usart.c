


#include "drv_usart.h"
#include "sys.h"
#include "drv_gpio.h"

<<<<<<< HEAD
=======
//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
//#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
>>>>>>> branch


void Usart1_Init(uint32_t Bound)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    USART_InitTypeDef USART_InitStruct;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    //閰嶇疆Usart TX绠¤剼
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;    //澶嶇敤鎺ㄦ尳杈撳嚭  TX
    GPIO_InitStruct.GPIO_Pin  = USART1_TXD_PIN;
    GPIO_Init(USART1_TXD_PORT, &GPIO_InitStruct);
    //閰嶇疆USART RX绠¤剼
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;      //RX
    GPIO_InitStruct.GPIO_Pin  = USART1_RXD_PIN;
    GPIO_Init(USART1_RXD_PORT, &GPIO_InitStruct);

    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

//Usart 閰嶇疆 8 N 1 
    USART_InitStruct.USART_BaudRate = Bound;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART1, &USART_InitStruct);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART1, ENABLE);
    
}

void USART1_IRQHandler()
{
    uint8_t temp;
    
    if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET)
    {
        temp = USART_ReceiveData(USART1);
        
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}

void USART1_SendData(uint8_t data)
{
    USART_SendData(USART1, data);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE));
}



