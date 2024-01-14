/*********************************************************







**********************************************************/

#include"drv_eeprom.h"
#include"drv_delay.h"



void AT24CXX_Init(void)
{
	IIC_Init();
}

/********************************************
*ReadAddr  :读取数据的目的地址
*********************************************/
uint8_t EEProm_ReadOneByte(uint16_t ReadAddr)
{
    uint8_t temp = 0;
    IIC_Start();
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Bytes(0XA0);	   //发送写命令
		IIC_Wait_Ack();
		IIC_Send_Bytes(ReadAddr>>8);//发送高地址
		IIC_Wait_Ack();		 
	}else 
    IIC_Send_Bytes(0XA0+((ReadAddr/256)<<1));   //发送器件地址0XA0,写数据 	 
    IIC_Wait_Ack();
    IIC_Send_Bytes(ReadAddr%256);   //发送低地址
    IIC_Wait_Ack();
    IIC_Start();
    IIC_Send_Bytes(0XA1);           //进入接收模式
    IIC_Wait_Ack();
    temp=IIC_Read_Byte(0);
    IIC_Stop();//产生一个停止条件
    return temp;
}

/********************************************
*WriteAddr  :写入数据的目的地址
*DataToWrite:要写入的数据
*********************************************/
void EEProm_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite)
{
    IIC_Start();
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Bytes(0XA0);	    //发送写命令
		IIC_Wait_Ack();
		IIC_Send_Bytes(WriteAddr>>8);//发送高地址
 	}else
	{
		IIC_Send_Bytes(0XA0+((WriteAddr/256)<<1));   //发送器件地址0XA0,写数据 
	}	 
    IIC_Wait_Ack();
    IIC_Send_Bytes(WriteAddr%256);   //发送低地址
    IIC_Wait_Ack();
    IIC_Send_Bytes(DataToWrite);     //发送字节
    IIC_Wait_Ack();
    IIC_Stop();//产生一个停止条件 
    delay_ms(10);
}

/***************************************************
*该函数用于写入16bit或者32bit的数据.
*WriteAddr  :开始写入的地址  
*DataToWrite:数据数组首地址
*Len        :要写入数据的长度2,4

***************************************************/
void EEProm_WriteLenByte(uint16_t WriteAddr,uint32_t DataToWrite,uint8_t Len)
{  
    uint8_t t;
    for(t=0;t<Len;t++)
    {
        EEProm_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
    }
}

/**************************************************
*在AT24CXX里面的指定地址开始读出长度为Len的数据   
*该函数用于读出16bit或者32bit的数据.
*ReadAddr   :开始读出的地址 
*返回值     :数据
*Len        :要读出数据的长度2,4
**************************************************/
uint32_t EEProm_ReadLenByte(uint16_t ReadAddr,uint8_t Len)
{
    uint8_t t;
    uint32_t temp=0;
    for(t=0;t<Len;t++)
    {
        temp<<=8;
        temp+=EEProm_ReadOneByte(ReadAddr+Len-t-1);
    }
    return temp;
}

/**************************************************
*检查EEprom是否正常
*这里用了EEprom的最后一个地址(255)来存储标志字.
*返回1:检测失败
*返回0:检测成功度为Len的数据   据.
**************************************************/
uint8_t EEprom_Check(void)
{
    uint8_t temp;
    temp=EEProm_ReadOneByte(255);           //避免每次开机都写
    if(temp==0X55)
    {
        return 0;
    }
    else                                    //排除第一次初始化的情况
    {
        EEProm_WriteOneByte(255,0X55);
        temp=EEProm_ReadOneByte(255);	  
        if(temp==0X55)
        {
            return 0;
        }
    }
    return 1;
}


/**************************************************
*指定地址开始读出指定个数的数据
*ReadAddr :开始读出的地址
*pBuffer  :数据数组首地址
*NumToRead:要读出数据的个数
**************************************************/
void EEprom_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead)
{
    while(NumToRead)
    {
        *pBuffer++=EEProm_ReadOneByte(ReadAddr++);	
        NumToRead--;
    }
}  

/**************************************************
*在EEprom里面的指定地址开始写入指定个数的数据
*WriteAddr :开始写入的地址 对24c02为0~255
*pBuffer   :数据数组首地址
*NumToWrite:要写入数据的个数
**************************************************/
void EEProm_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite)
{
    while(NumToWrite--)
    {
        EEProm_WriteOneByte(WriteAddr,*pBuffer);
        WriteAddr++;
        pBuffer++;
    }
}














