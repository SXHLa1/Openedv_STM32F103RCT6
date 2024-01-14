#include"drv_eeprom.h"



uint8 EEProm_ReadOneByte(uint16 ReadAddr)
{
    uint8 temp = 0;
    IIC_Start();
    IIC_Send_Bytes(0x0A+((ReadAddr/256) << 1));
    IIC_Wait_Ack();

}












