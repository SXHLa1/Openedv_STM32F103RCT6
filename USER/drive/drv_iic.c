/**********************************************************
*
*文 件 名：drv_iic.c
*
功    能：IIC驱动
*作     者：dehongyi
*
***********************************************************/
#include"drv_iic.h"
#include"drv_delay.h"
#include"drv_gpio.h"




/***********************************************************
*函 数 名：IIC_Init
* Input  ：None
* Output ：None
*功能描述：IIC初始化
***********************************************************/
void IIC_Init(void)
{                        
    GPIO_InitTypeDef GPIO_InitStructure;
   
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE ); 
    GPIO_InitStructure.GPIO_Pin = IIC_SCL_PIN|IIC_SDA_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(IIC_PORT, &GPIO_InitStructure);
    
    IIC_SCL=1;
    IIC_SDA=1;

}

void IIC_CHANGE_MODE(GPIOMode_TypeDef mode)
{
    GPIO_InitTypeDef    GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin   = IIC_SDA_PIN;
    GPIO_InitStructure.GPIO_Mode  = mode;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(IIC_PORT, &GPIO_InitStructure);   
}



void IIC_Start(void)
{
    SDA_OUT();
    IIC_SDA=1;
    IIC_SCL=1;
    delay_us(4);
    IIC_SDA=0;
    delay_us(4);
    IIC_SCL=0;
}


void IIC_Stop(void)
{
    SDA_OUT();
    IIC_SCL=0;
    IIC_SDA=0;
    delay_us(4);
    IIC_SCL=1;
    IIC_SDA=1;
    delay_us(4);
}


uint8_t IIC_Wait_Ack(void)
{
    uint8_t ucErrTime=0;
    SDA_IN();
    IIC_SDA=1;delay_us(1);
    IIC_SCL=1;delay_us(1);
    while(READ_SDA)
    {
        ucErrTime++;
        if(ucErrTime>250)
        {
            IIC_Stop();
            return 1;
        }
    }
    IIC_SCL=0;//Ê±ÖÓÊä³ö0      
    return 0;  
}


void IIC_Ack(void)
{
    IIC_SCL=0;
    SDA_OUT();
    IIC_SDA=0;
    delay_us(2);
    IIC_SCL=1;
    delay_us(2);
    IIC_SCL=0;
}

void IIC_NoAck(void)
{
    IIC_SCL=0;
    SDA_OUT();
    IIC_SDA=1;
    delay_us(2);
    IIC_SCL=1;
    delay_us(2);
    IIC_SCL=0;
}

void IIC_Send_Bytes(uint8_t txd)
{
    uint8_t t;   
    SDA_OUT();      
    IIC_SCL=0;
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1;      
        delay_us(2);   
        IIC_SCL=1;
        delay_us(2); 
        IIC_SCL=0;  
        delay_us(2);
    }   
}

uint8_t IIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    SDA_IN();
    for(i=0;i<8;i++ )
    {
        IIC_SCL=0; 
        delay_us(2);
        IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;
        delay_us(1); 
    }
    if (!ack)
        IIC_NoAck();
    else
        IIC_Ack();
    return receive;
}