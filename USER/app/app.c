#include "app.h"
#include "drv_delay.h"
#include "drv_iic.h"
#include "drv_eeprom.h"
#include "drv_key.h"

const uint8_t TEXT_Buffer[]={"MiniSTM32 IIC TEST"};
#define SIZE sizeof(TEXT_Buffer)

void App_Init()
{
    
    led_init();
    delay_init();
    key_init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    AT24CXX_Init();
    
}

void App_Run()
{
    led_test();
    uint8_t key;
    uint8_t datatemp[SIZE] = {0};
    while(EEprom_Check())
	{
        FailLED();
	}
    while(1)
    {
        key = Key_Scan(1);
        if(key == KEY0_Pres)
        {
            //AT24CXX_Write(0,(uint8_t*)TEXT_Buffer,SIZE);
            EEProm_Write(0,(uint8_t*)TEXT_Buffer,SIZE);
        }
        if(key == KEY1_Pres)
        {
            uint8 SuccessCR = 0;
            uint8 i;
            //AT24CXX_Read(0,datatemp,SIZE);
            EEprom_Read(0,datatemp,SIZE);
            for(i = 0; i < SIZE; i++)
            {
                if(datatemp[i] == TEXT_Buffer[i])
                {
                    SuccessCR++;
                }
            
            }
            if(SIZE == SuccessCR)
            {
                SuccessLED();
            }
            else
            {
                FailLED();
            }
        }
//        if(datatemp == (uint8*)TEXT_Buffer))
//        {
//            SuccessLED();
//        }
//        else
//        {
//            FailLED();
//        }
    }

}