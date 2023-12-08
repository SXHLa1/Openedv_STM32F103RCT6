#ifndef __DRV_KEY_H
#define __DRV_KEY_H


/************** include ****************/
#include"drv_gpio.h"



/*************** struct ****************/

typedef struct
{
  uint8_t    level              : 1;    /* 当前电平 */
  uint8_t    valid_level        : 1;    /* 有效电平，按键激活判断 */
  uint8_t    reserve            : 2;    /* 保留 */
  uint8_t    click_cnt          : 4;    /* 连击次数 */
  uint8_t    filter_limit;              /* 电平滤波阈值 */
  uint16_t   tick;                      /* 按键扫描计时 */
  uint16_t   double_click_limit;        /* 双击时间的阈值 */
  uint16_t   long_limit;                /* 长按的阈值 */
  uint16_t   long_long_limit;           /* 超长按的阈值 */
  uint8_t    (*get_level)(void);        /* 电平获取，函数指针 */
}key_scan_t;








#endif

