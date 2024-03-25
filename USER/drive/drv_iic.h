#ifndef __DRV_IIC_H
#define __DRV_IIC_H


/************** include ****************/
#include"sys.h"
#include"stm32f10x.h"



#define SDA_IN()        {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=8<<12;}
#define SDA_OUT()       {GPIOC->CRH&=0XFFFF0FFF;GPIOC->CRH|=3<<12;}

#define IIC_SCL         PCout(12) //SCL
#define IIC_SDA         PCout(11) //SDA
#define READ_SDA        PCin(11)  //

#define IIC_Delay       ()

/*************** struct ****************/





/**************************************/
void IIC_Init(void);        //IIC初始化
void IIC_CHANGE_MODE(GPIOMode_TypeDef mode);        //IIC引脚模式切换
void IIC_Start(void); //IIC开始
void IIC_Stop(void); //IIC结束
uint8_t IIC_Wait_Ack(void); //IIC等待ACK
void IIC_Ack(void);    //IIC发送ACK
void IIC_NoAck(void); //IIC无ACK
void IIC_Send_Bytes(uint8_t txd);       //IIC发送1Byte
uint8_t IIC_Read_Byte(uint8_t rxd); //IIC接收1Byte

#endif

