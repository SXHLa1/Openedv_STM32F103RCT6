#include"app_task.h"








void TaskMarks(void)
{
    uint8_t i;

    for(i = 0; i < ListTask_Max; i++)
    {
        if(TaskManage[i].Timer)
        {
            TaskManage[i].Timer--;
            if(TaskManage[i].Timer == 0)
            {
                TaskManage[i].Timer = TaskManage[i].ItvTime;
                TaskManage[i].run = 1;
            }
        }
    }
}



void TaskProcess(void)
{
    uint8_t i = 0;
    for(i = 0; i < ListTask_Max; i++)
    {
        if(TaskManage[i].run)
        {
            TaskManage[i].TaskHook();
            TaskManage[i].run = 0;
        }
    }
}


void Task_Usart(void)
{
    


}

void Task_FlashTest(void)
{

}







