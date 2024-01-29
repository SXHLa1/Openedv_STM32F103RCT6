#include"drv_key.h"
#include"drv_gpio.h"


//按键初始化
void key_init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

    GPIO_InitStruct.GPIO_Pin = KEY0_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(KEY0_PORT , &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = KEY1_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(KEY1_PORT , &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = KEY_UP_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(KEY_UP_PORT , &GPIO_InitStruct);


}


//按键检测
uint8_t Key_Scan(uint8_t mode)
{
    static uint8_t key_up = 1;
    if(mode)
    {
        key_up = 1;
    }
    if(key_up && (KEY0_Status == 0 || KEY1_Status == 0 || WK_UP_Status == 1))
    {
        delay_ms(10);
        if(KEY0_Status == 0)
        {
            return KEY0_Pres;
        }
        else if(GPIO_ReadInputDataBit(KEY1) == 0)
        {
            return KEY1_Pres;
        }
        else if(GPIO_ReadInputDataBit(KEY_UP) == 1)
        {
            return KEY_UP_Pres;
        }
    }
    else if(KEY0_Status == 1 && KEY1_Status == 1 && WK_UP_Status == 0)
    {
        key_up = 0;
    }
    return 0;
}












