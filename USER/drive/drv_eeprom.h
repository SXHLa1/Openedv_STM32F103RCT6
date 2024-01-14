#ifndef __DRV_EEPROM_H
#define __DRV_EEPROM_H

#include"drv_iic.h"


#define AT24C01		127
#define AT24C02		255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	    8191
#define AT24C128	16383
#define AT24C256	32767  
//Mini STM32¿ª·¢°åÊ¹ÓÃµÄÊÇ24c02£¬ËùÒÔ¶¨ÒåEE_TYPEÎªAT24C02
#define EE_TYPE AT24C02


void AT24CXX_Init(void);
uint8_t EEProm_ReadOneByte(uint16_t ReadAddr);                              //读EEProm一个字节数据
void EEProm_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite);                 //写EEProm一个字节数据
void EEProm_WriteLenByte(uint16_t WriteAddr,uint32_t DataToWrite,uint8_t Len);//写指定长度的EEProm字节数据
uint32_t EEProm_ReadLenByte(uint16_t ReadAddr,uint8_t Len);                            //读指定长度的EEProm字节数据
uint8_t EEprom_Check(void);                                                  //检查EEProm是否正确
void EEprom_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead);               //从指定地址开始写入指定长度的数据
void EEProm_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite);            //从指定地址开始读出指定长度的数据
void EEprom_Init(void);                                                 //EEprom初始化

#endif