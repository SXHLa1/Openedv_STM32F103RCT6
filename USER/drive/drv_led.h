#ifndef __DRV_LED_H
#define __DRV_LED_H

#include"sys.h"
#include"drv_gpio.h"


#define LED_RED             
#define LED_GREEN           

void led_init(void);                    //led初始�?
void led_test(void);                    //led测试
void FailLED(void);                     //执行失败时闪烁3次红色LED
void SuccessLED(void);                  //执行成功时闪烁3次绿色LED



#endif