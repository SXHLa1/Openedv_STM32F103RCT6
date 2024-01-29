#ifndef __APP_TASK_H
#define __APP_TASK_H





//任务参数
#define InitStatus                        0
#define TimerTask_Usart                   10
#define TimerTask_FlashTest               20


static TASK_COMPONENTS TaskManage[] = 
{
    {InitStatus, TimerTask_Usart,     TimerTask_Usart,    Task_Usart    },
    {InitStatus, TimerTask_FlashTest, TimerTask_FlashTest,Task_FlashTest},

};



typedef enum _TaskList
{
    ListTask_Usart,
    ListTask_FlashTest,

    
    ListTask_Max
}TaskList;








//任务结构
typedef struct _TASK_COMPONENTS
{
    uint8_t run;                    //任务运行标记：0-不运行，1-运行
    uint8_t Timer;                  //计时器
    uint8_t ItvTime;                //任务运行间隔时间，即多久运行一次
    void (*TaskHook)(void);         //运行的任务函数
}TASK_COMPONENTS;









//对应任务的处理函数
void Task_Usart(void);
void Task_FlashTest(void);





void TaskMarks(void   );              //任务处理标志
void TaskProcess(void);                 //任务处理函数



#endif