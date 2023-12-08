#ifndef __DRV_IIC_H
#define __DRV_IIC_H


/************** include ****************/
#include"sys.h"
#include"stm32f10x.h"


#define IIC_SDA_IN()        IIC_CHANGE_MODE(GPIO_Mode_IPU)
#define IIC_SDA_OUT()       IIC_CHANGE_MODE(GPIO_Mode_Out_PP)
#define SDA_IN()            GPIO_ReadInputDataBit(IIC_SDA)

#define SDA_H               GPIO_SetBits(IIC_SDA)
#define SDA_L               GPIO_ResetBits(IIC_SDA);

#define SCL_H               GPIO_SetBits(IIC_SCL)
#define SCL_L               GPIO_ResetBits(IIC_SCL);


/*************** struct ****************/





/**************************************/
void IIC_Init(void);





#endif

