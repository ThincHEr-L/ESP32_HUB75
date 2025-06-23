#include "all_task.h"

#include "hub75.h"
#include "hub75e/HUB75ELib.h"

static char QueueData[128];
bool fasthub75_init_flag = false;
bool hub75_init_flag = false;

void fasthub75_init(void)
{
    HUB75E_Init();
    HUB75E_setDisplayBrightness(BrightnessLevel1);
    HUB75E_setDisplayColor(Red);
}

void hub75_task(void *arg)
{
    hub75init(); // Initialize the HUB75 matrix panel
    hub75_init_flag = true;
    while (1)
    {
        xQueueReceive(xMyQueueHandle, QueueData, 0);
         
        char *pos = strchr(QueueData, '_');
        char init_data[32] = {0};
        if (pos != NULL)
        {
            strncpy(init_data, QueueData, pos - QueueData);
            init_data[pos - QueueData] = '\0';
        }
        if (strstr(init_data, "holo"))
        {
            if(fasthub75_init_flag == false)
            {
                fasthub75_init();
                fasthub75_init_flag = true;
                hub75_init_flag = false;
                printf("fasthub75_init finished\n");
            }
        }
        if (strstr(init_data, "emoji"))
        {
            if(hub75_init_flag == false)
            {
                hub75init();
                hub75_init_flag = true;
                fasthub75_init_flag = false;
                printf("hub75_init finished\n");
            }
        }
        if(strstr(QueueData, "hub75_off"))
        {
            if(fasthub75_init_flag == true)
            {
                HUB75E_DisplayOFF();
                printf("hub75_off finished\n");
            }
            if(hub75_init_flag == true)
            {
                dmahub75clear();
                printf("hub75_off finished\n");
            }
        }
        vTaskDelay(pdMS_TO_TICKS(20));
        // for (int j = 0; j < 10; j++)
        // {
        //     for (int i = 0; i < 32; i++)
        //     {
        //         drawHLine(1, i, 32, 255, 255, 255);
        //         drawHLine(33, i, 32, 255, 255, 255);
        //         vTaskDelay(pdMS_TO_TICKS(100));
        //     }
        //     fillscreen888(0, 0, 0); // Clear the screen   
        // }
        // vTaskDelay(pdMS_TO_TICKS(10));
         //drawimage((int*)epd_bitmap_allArray[148], 32, 0, 32, 32);
        // drawimage((int*)epd_bitmap_allArray[148], 0, 0, 32, 32);
    }
}

