#ifndef __DRV_GPIO_H
#define __DRV_GPIO_H

#include"stm32f10x.h"


/*********** 外接模块类型配置 *************/
#define SPI_FLASH   1
#define SD_CARD     2
#define NRF24L01    3

#ifndef Module_Type
#define Module_Type      SPI_FLASH
#endif



/******** GPIO 引脚分配 *********/
//LED引脚
#define LED0_PORT                       GPIOA
#define LED0_PIN                        GPIO_Pin_8
#define LED0                            GPIOA,GPIO_Pin_8            //红色

#define LED1_PORT                       GPIOD
#define LED1_PIN                        GPIO_Pin_2
#define LED1                            GPIOD,GPIO_Pin_2            //绿色
//按键引脚
#define KEY_UP_PORT                     GPIOA
#define KEY_UP_PIN                      GPIO_Pin_0
#define KEY_UP                          GPIOA,GPIO_Pin_0

#define KEY1_PORT                       GPIOA
#define KEY1_PIN                        GPIO_Pin_15
#define KEY1                            GPIOA,GPIO_Pin_15

#define KEY0_PORT                       GPIOC
#define KEY0_PIN                        GPIO_Pin_5
#define KEY0                            GPIOC,GPIO_Pin_5
//LCD引脚
#define LCD_D0_PORT                     GPIOB
#define LCD_D0_PIN                      GPIO_Pin_0
#define LCD_D0                          GPIOB,GPIO_Pin_0

#define LCD_D1_PORT                     GPIOB
#define LCD_D1_PIN                      GPIO_Pin_1
#define LCD_D1                          GPIOB,GPIO_Pin_1

#define LCD_D2_PORT                     GPIOB
#define LCD_D2_PIN                      GPIO_Pin_2
#define LCD_D2                          GPIOB,GPIO_Pin_2

#define LCD_D3_PORT                     GPIOB
#define LCD_D3_PIN                      GPIO_Pin_3
#define LCD_D3                          GPIOB,GPIO_Pin_3

#define LCD_D4_PORT                     GPIOB
#define LCD_D4_PIN                      GPIO_Pin_4
#define LCD_D4                          GPIOB,GPIO_Pin_4

#define LCD_D5_PORT                     GPIOB
#define LCD_D5_PIN                      GPIO_Pin_5
#define LCD_D5                          GPIOB,GPIO_Pin_5

#define LCD_D6_PORT                     GPIOB
#define LCD_D6_PIN                      GPIO_Pin_6
#define LCD_D6                          GPIOB,GPIO_Pin_6

#define LCD_D7_PORT                     GPIOB
#define LCD_D7_PIN                      GPIO_Pin_7
#define LCD_D7                          GPIOB,GPIO_Pin_7

#define LCD_D8_PORT                     GPIOB
#define LCD_D8_PIN                      GPIO_Pin_8
#define LCD_D8                          GPIOB,GPIO_Pin_8

#define LCD_D9_PORT                     GPIOB
#define LCD_D9_PIN                      GPIO_Pin_9
#define LCD_D9                          GPIOB,GPIO_Pin_9

#define LCD_D10_PORT                    GPIOB
#define LCD_D10_PIN                     GPIO_Pin_10
#define LCD_D10                         GPIOB,GPIO_Pin_10

#define LCD_D11_PORT                    GPIOB
#define LCD_D11_PIN                     GPIO_Pin_11
#define LCD_D11                         GPIOB,GPIO_Pin_11

#define LCD_D12_PORT                    GPIOB
#define LCD_D12_PIN                     GPIO_Pin_12
#define LCD_D12                         GPIOB,GPIO_Pin_12

#define LCD_D13_PORT                    GPIOB
#define LCD_D13_PIN                     GPIO_Pin_13
#define LCD_D13                         GPIOB,GPIO_Pin_13

#define LCD_D14_PORT                    GPIOB
#define LCD_D14_PIN                     GPIO_Pin_14
#define LCD_D14                         GPIOB,GPIO_Pin_14

#define LCD_D15_PORT                    GPIOB
#define LCD_D15_PIN                     GPIO_Pin_15
#define LCD_D15                         GPIOB,GPIO_Pin_15

#define T_SCK_PORT                      GPIOC
#define T_SCK_PIN                       GPIO_Pin_0
#define T_SCK                           GPIOC,GPIO_Pin_0

#define T_PEN_PORT                      GPIOC
#define T_PEN_PIN                       GPIO_Pin_1
#define T_PEN                           GPIOC,GPIO_Pin_1

#define T_MISO_PORT                     GPIOC
#define T_MISO_PIN                      GPIO_Pin_2
#define T_MISO                          GPIOC,GPIO_Pin_2

#define T_MOSI_PORT                     GPIOC
#define T_MOSI_PIN                      GPIO_Pin_3
#define T_MOSI                          GPIOC,GPIO_Pin_3

#define LCD_RD_PORT                     GPIOC
#define LCD_RD_PIN                      GPIO_Pin_6
#define LCD_RD                          GPIOC,GPIO_Pin_6

#define LCD_WR_PORT                     GPIOC
#define LCD_WR_PIN                      GPIO_Pin_7
#define LCD_WR                          GPIOC,GPIO_Pin_7

#define LCD_RS_PORT                     GPIOC
#define LCD_RS_PIN                      GPIO_Pin_8
#define LCD_RS                          GPIOC,GPIO_Pin_8

#define LCD_CS_PORT                     GPIOC
#define LCD_CS_PIN                      GPIO_Pin_9
#define LCD_CS                          GPIOC,GPIO_Pin_9

#define LCD_BL_PORT                     GPIOC
#define LCD_BL_PIN                      GPIO_Pin_10
#define LCD_BL                          GPIOC,GPIO_Pin_10

#define T_CS_PORT                       GPIOC
#define T_CS_PIN                        GPIO_Pin_13
#define T_CS                            GPIOC,GPIO_Pin_13

//IIC
#define IIC_PORT                        GPIOC
#define IIC_SCL_PIN                     GPIO_Pin_12
#define IIC_SCL_IO                      GPIOC,GPIO_Pin_12
#define IIC_SDA_PIN                     GPIO_Pin_11
#define IIC_SDA_IO                      GPIOC,GPIO_Pin_11

//SPI
#if Module_Type == SPI_FLASH
#define SPI1_SCK_PORT                   GPIOA
#define SPI1_SCK_PIN                    GPIO_Pin_5
#define SPI1_SCK                        GPIOA,GPIO_Pin_5

#define SPI1_MISO_PORT                  GPIOA
#define SPI1_MISO_PIN                   GPIO_Pin_6
#define SPI1_MISO                       GPIOA,GPIO_Pin_6

#define SPI1_MOSI_PORT                  GPIOA
#define SPI1_MOSI_PIN                   GPIO_Pin_7
#define SPI1_MOSI                       GPIOA,GPIO_Pin_7

#define SPI1_CS_PORT                    GPIOA
#define SPI1_CS_PIN                     GPIO_Pin_2
#define SPI1_CS                         GPIOA,GPIO_Pin_2

#elif Module_Type == SD_CARD
#define SPI1_SCK_PORT                   GPIOA
#define SPI1_SCK_PIN                    GPIO_Pin_5
#define SPI1_SCK                        GPIOA,GPIO_Pin_5

#define SPI1_MISO_PORT                  GPIOA
#define SPI1_MISO_PIN                   GPIO_Pin_6
#define SPI1_MISO                       GPIOA,GPIO_Pin_6

#define SPI1_MOSI_PORT                  GPIOA
#define SPI1_MOSI_PIN                   GPIO_Pin_7
#define SPI1_MOSI                       GPIOA,GPIO_Pin_7

#define SD_CS_PORT                      GPIOA
#define SD_CS_PIN                       GPIO_Pin_3
#define SD_CS                           GPIOA,GPIO_Pin_3

#else                   //Module_Type == NRF24L01
#define SPI1_SCK_PORT                   GPIOA
#define SPI1_SCK_PIN                    GPIO_Pin_5
#define SPI1_SCK                        GPIOA,GPIO_Pin_5

#define SPI1_MISO_PORT                  GPIOA
#define SPI1_MISO_PIN                   GPIO_Pin_6
#define SPI1_MISO                       GPIOA,GPIO_Pin_6

#define SPI1_MOSI_PORT                  GPIOA
#define SPI1_MOSI_PIN                   GPIO_Pin_7
#define SPI1_MOSI                       GPIOA,GPIO_Pin_7

#define NRF_CS_PORT                     GPIOC
#define NRF_CS_PIN                      GPIO_Pin_4
#define NRF_CS                          GPIOC,GPIO_Pin_4

#define NRF_CE_PORT                     GPIOA
#define NRF_CE_PIN                      GPIO_Pin_4
#define NRF_CE                          GPIOA,GPIO_Pin_4

#define NRF_IRQ_PORT                    GPIOA
#define NRF_IRQ_PIN                     GPIO_Pin_1
#define NRF_IRQ                         GPIOA,GPIO_Pin_1
#endif

//串口引脚
#define USART1_TXD_PORT                  GPIOA
#define USART1_TXD_PIN                   GPIO_Pin_9
#define USART1_TXD                       GPIOA,GPIO_Pin_9

#define USART1_RXD_PORT                  GPIOA
#define USART1_RXD_PIN                   GPIO_Pin_10
#define USART1_RXD                       GPIOA,GPIO_Pin_10

//USB引脚
#define USB_UP_PORT                     GPIOA
#define USB_UP_PIN                      GPIO_Pin_12             //USB  D+
#define USB_UP                          GPIOA,GPIO_Pin_12

#define USB_DOWN_PORT                   GPIOA
#define USB_DOWN_PIN                    GPIO_Pin_11             //USB  D-
#define USB_DOWN                        GPIOA,GPIO_Pin_11

//SWD引脚
#define SWDIO_PORT                      GPIOA
#define SWDIO_PIN                       GPIO_Pin_13
#define SWDIO                           GPIOA,GPIO_Pin_13

#define SWDCLK_PORT                     GPIOA
#define SWDCLK_PIN                      GPIO_Pin_14
#define SWDCLK                          GPIOA,GPIO_Pin_14


#endif


