#include "app.h"
#include "drv_delay.h"
#include "drv_iic.h"
#include "drv_usart.h"
#include "drv_eeprom.h"
#include "drv_key.h"
#include "drv_lcd.h"
<<<<<<< HEAD
#include "drv_iwdg.h"
=======
#include "drv_led.h"
>>>>>>> branch


const uint8_t TEXT_Buffer[]={"MiniSTM32 IIC TEST"};
#define SIZE sizeof(TEXT_Buffer)

void App_Init()
{
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    IWDG_Init();
    led_init();
    delay_init();
    key_init();
    Usart1_Init(9600);
    AT24CXX_Init();
    LCD_Init();
    
}

void App_Run()
{
    led_test();
    uint8_t key,i = 0;
    uint8_t datatemp[SIZE] = {0};
    POINT_COLOR = RED;//设置字体为红色 
    LCD_ShowString(60,50,200,16,16,"Mini STM32");   
    LCD_ShowString(60,70,200,16,16,"IIC TEST"); 
    LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
    LCD_ShowString(60,110,200,16,16,"2014/3/9");    
    LCD_ShowString(60,130,200,16,16,"WK_UP:Write  KEY0:Read");
    while(EEprom_Check())
    {
        LCD_ShowString(60,150,200,16,16,"24C02 Check Failed!");
        delay_ms(500);
        LCD_ShowString(60,150,200,16,16,"Please Check!      ");
        delay_ms(500);
        FailLED();
    }
    LCD_ShowString(60,150,200,16,16,"24C02 Ready!");    
    POINT_COLOR = BLUE;//设置字体为蓝色
    while(1)
    {
        key = Key_Scan(1);
        if(key == KEY0_Pres)
        {
            LCD_Fill(0,170,239,319,WHITE);//清除半屏    
            LCD_ShowString(60,170,200,16,16,"Start Write 24C02....");
            //AT24CXX_Write(0,(uint8_t*)TEXT_Buffer,SIZE);
            EEProm_Write(0,(uint8_t*)TEXT_Buffer,SIZE);
            LCD_ShowString(60,170,200,16,16,"24C02 Write Finished!");
        }
        if(key == KEY1_Pres)
        {
            uint8 SuccessCR = 0;
            uint8 i;
            LCD_ShowString(60,170,200,16,16,"Start Read 24C02.... ");
            //AT24CXX_Read(0,datatemp,SIZE);
            EEprom_Read(0,datatemp,SIZE);
            LCD_ShowString(60,170,200,16,16,"The Data Readed Is:  ");//提示传送完成
            LCD_ShowString(60,190,200,16,16,datatemp);
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
        i++;
        delay_ms(10);
        if(i==20)
        {
            SuccessLED();//提示系统正在运行 
            i=0;
        }
        
        IWDG_Clr();
    }

}