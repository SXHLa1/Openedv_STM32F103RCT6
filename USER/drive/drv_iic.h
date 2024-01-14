#ifndef __DRV_IIC_H
#define __DRV_IIC_H


/************** include ****************/
#include"sys.h"
#include"stm32f10x.h"



#define SDA_IN()  {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=8<<12;}
#define SDA_OUT() {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=3<<12;}


#define IIC_SCL    PCout(12) //SCL
#define IIC_SDA    PCout(11) //SDA	 
#define READ_SDA   PCin(11)  //


/*************** struct ****************/





/**************************************/
void IIC_Init(void);
void IIC_CHANGE_MODE(GPIOMode_TypeDef mode);
void IIC_Start(void);
void IIC_Stop(void);
uint8_t IIC_Wait_Ack(void);
void IIC_Ack(void);
void IIC_NoAck(void);
void IIC_Send_Bytes(uint8_t txd);
uint8_t IIC_Read_Byte(uint8_t rxd);

#endif

