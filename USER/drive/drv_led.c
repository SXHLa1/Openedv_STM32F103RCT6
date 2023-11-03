#include"drv_led.h"
#include"sys.h"
#include"drv_delay.h"


void led_init()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD,  ENABLE);//打开LED对应GPIO外设时钟
    
    //LED0_PA8初始化
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = LED0_PIN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED0_PORT, &GPIO_InitStruct);
    GPIO_SetBits(LED0_PORT, LED0_PIN);

    //LED1_PD2初始化 
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = LED1_PIN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED1_PORT, &GPIO_InitStruct);
    GPIO_SetBits(LED1_PORT, LED1_PIN);
    
}

void led_set()
{
        GPIO_ResetBits(LED0_PORT,LED0_PIN);
        GPIO_SetBits(LED1_PORT,LED1_PIN);
        delay_ms(300);
        GPIO_SetBits(LED0_PORT,LED0_PIN);
        GPIO_ResetBits(LED1_PORT,LED1_PIN);
        delay_ms(300);
}

