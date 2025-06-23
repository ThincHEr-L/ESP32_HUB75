#ifndef _ALL_TASK_
#define _ALL_TASK_  

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <ESP_LOG.h>
#include <string.h>

#define ECHO_TASK_STACK_SIZE    (1024*4)
#define LIGHT_TASK_STACK_SIZE   (1024*4)
#define HUB75_TASK_STACK_SIZE   (1024*4)

extern QueueHandle_t xMyQueueHandle;

void uart1_echo_task(void *arg);
void power_light_task(void *arg);
void hub75_task(void *arg);

#endif
