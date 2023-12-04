#include "app.h"
#include "drv_delay.h"




void App_Init()
{
    
    led_init();
    delay_init();






}




void App_Run()
{
    while(1)
    {
        led_set();
    }

}