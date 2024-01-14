#include"drv_iic.h"
#include"delay.h"




void IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE );

    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin   = IIC_SCL_PIN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( IIC_SCL_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin   = IIC_SCL_PIN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( IIC_SCL_PORT, &GPIO_InitStruct);

    GPIO_SetBits(IIC_SCL);
    GPIO_SetBits(IIC_SDA);

}

void IIC_CHANGE_MODE(GPIOMode_TypeDef mode)
{
    GPIO_InitTypeDef  	GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin   = IIC_SDA_PIN;
    GPIO_InitStructure.GPIO_Mode  = mode;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(IIC_SDA_PORT, &GPIO_InitStructure);	
}



void IIC_Start(void)
{
    SDA_OUT();
    GPIO_SetBits(IIC_SDA);
    GPIO_SetBits(IIC_SCL);
    delay_us(4);
    GPIO_ResetBits(IIC_SDA);
    delay_us(4);
    GPIO_ResetBits(IIC_SCL);
}


void IIC_Stop(void)
{
    SDA_OUT();
    GPIO_ResetBits(IIC_SDA);
    GPIO_ResetBits(IIC_SCL);
    delay_us(4);
    GPIO_SetBits(IIC_SDA);
    GPIO_SetBits(IIC_SCL);
    delay_us(4);
}


uint8 IIC_Wait_Ack(void)
{
    uint8   ucErrTime = 0;
    SDA_IN();
    GPIO_SetBits(IIC_SDA);
    delay_us(1);
    GPIO_SetBits(IIC_SCL);
    delay_us(1);
    while(GPIO_ReadInputDataBit(IIC_SDA))
    {
        ucErrTime++;
        if(ucErrTime > 250)
        {
            IIC_Stop();
            return 1;
        }
    }
    GPIO_SetBits(IIC_SCL);
    return 0;
}


void IIC_Ack(void)
{
    GPIO_ResetBits(IIC_SCL);
    SDA_OUT();
    GPIO_ResetBits(IIC_SDA);
    delay_us(2);
    GPIO_SetBits(IIC_SCL);
    delay_us(2);
    GPIO_ResetBits(IIC_SCL);
}

void IIC_NoAck(void)
{
    GPIO_ResetBits(IIC_SCL);
    SDA_OUT();
    GPIO_SetBits(IIC_SDA);
    delay_us(2);
    GPIO_SetBits(IIC_SCL);
    delay_us(2);
    GPIO_ResetBits(IIC_SCL)
}


void IIC_Send_Bytes(uint8 txd)
{
    uint8   t;
    SDA_OUT();
    GPIO_ResetBits(IIC_SCL);
    for(t = 0; t < 8 ; t++)
    {
        if(data & (0x01 << (7-t))
        {
            SDA_H;
        }
        else
        {
            SDA_L;
        }
        delay_us(5);
        SCL_H;
        delay_us(5);
        SCL_L;
    }
}

uint8 IIC_Read_Byte(void)
{
    uint8 i;
    uint8 data = 0x00;

    IIC_SDA_IN();

    SCL_L;
    fot(i = 0; i < 8; i++)
    {
        delay_us(5);
        SCL_H;
        delay_us(5);
        if(SDA_IN() == 1)
        {
            data |= (0x01 << (7-i));
        }
        SCL_L;
    }
    return data;
}











