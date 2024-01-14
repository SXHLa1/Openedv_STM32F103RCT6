#include"drv_key.h"



//按键初始化
void key_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
    
    GPIO_InitStruct.GPIO_Pin = KEY0_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY0_PORT , &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = KEY1_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY1_PORT , &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = KEY_UP_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY_UP_PORT , &GPIO_InitStruct);


}


//按键检测
uint8 Key_Scan(uint8 mode)
{
    static uint8 key_up = 1;
    if(mode)
    {
        key_up = 1;
    }
    if(key_up && (GPIO_ReadInputData(KEY0) == 0 || GPIO_ReadInputData(KEY1) == 0 || GPIO_ReadInputData(KEY_UP) == 1))
    {
        delay_ms(10);
        if(GPIO_ReadInputData(KEY0) == 0)
        {
            return KEY0_Pres;
        }
        else if(GPIO_ReadInputData(KEY1) == 0)
        {
            return KEY1_Pres;
        }
        else if(GPIO_ReadInputData(KEY_UP) == 1)
        {
            return KEY_UP_Pres;
        }
    }
    else if(GPIO_ReadInputData(KEY0) == 1 && GPIO_ReadInputData(KEY1) == 1 && GPIO_ReadInputData(KEY_UP) == 0)
    {
        key_up = 0;
    }
    return 0;
}












