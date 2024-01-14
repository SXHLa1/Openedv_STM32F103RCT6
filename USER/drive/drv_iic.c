#include"drv_iic.h"
#include"drv_delay.h"
#include"drv_gpio.h"



//void IIC_Init()
//{
//    GPIO_InitTypeDef GPIO_InitStructure;
//
//    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE );
//
//    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
//    GPIO_InitStructure.GPIO_Pin   = IIC_SCL_PIN;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init( IIC_SCL_PORT, &GPIO_InitStructure);
//
//    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
//    GPIO_InitStructure.GPIO_Pin   = IIC_SDA_PIN;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init( IIC_SDA_PORT, &GPIO_InitStructure);
//
//    IIC_SCL=1;
//    IIC_SDA=1;
//
//}

void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	//RCC->APB2ENR|=1<<4;//��ʹ������IO PORTCʱ�� 
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOC, ENABLE );	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
 
	IIC_SCL=1;
	IIC_SDA=1;

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
    SDA_OUT();     //sdaÏßÊä³ö
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//Ç¯×¡I2C×ÜÏß£¬×¼±¸·¢ËÍ»ò½ÓÊÕÊý¾Ý 
}


void IIC_Stop(void)
{
    SDA_OUT();//sdaÏßÊä³ö
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//·¢ËÍI2C×ÜÏß½áÊøÐÅºÅ
	delay_us(4);
}


uint8_t IIC_Wait_Ack(void)
{
    uint8_t ucErrTime=0;
	SDA_IN();      //SDAÉèÖÃÎªÊäÈë  
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