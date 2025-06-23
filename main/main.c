#include <stdio.h>
#include "all_task.h"

QueueHandle_t xMyQueueHandle;

void app_main(void)
{
    xMyQueueHandle = xQueueCreate(3,sizeof(char)*128);
    xTaskCreate(uart1_echo_task, "Uart0_task", ECHO_TASK_STACK_SIZE, NULL, 12, NULL);
    xTaskCreate(power_light_task, "Power_task", LIGHT_TASK_STACK_SIZE, NULL, 20, NULL);
    xTaskCreate(hub75_task, "Hub75_task", HUB75_TASK_STACK_SIZE, NULL, 10, NULL);

}

