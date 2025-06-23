#include <stdio.h>
#include <string.h>

#include "all_task.h"
#include "driver/gpio.h"
#include "driver/uart.h"

#include "my_cmd.h"

#define UART1_TX_BUF_SIZE 256    /* 256个字节 */
#define UART1_RX_BUF_SIZE 256    /* 256个字节 */
static const char *TAG = "UART section0";

static char buffer[UART1_RX_BUF_SIZE];   /* 暂时存储从串口接收到的字符串 */
void help_cb(char *str);
void hub75_emoji_cb(char *str);
void hub75_off_cb(char *str);
void mqtt_light_cb(char *str);
void hub75_holo_cb(char *str);

cmd_t cmd_list[] = {
	{"esp_help",help_cb},
    {"esp_hub75_emoji",hub75_emoji_cb},
    {"esp_hub75_off",hub75_off_cb},
    {"esp_hub75_holo",hub75_holo_cb},
    {"esp_mqtt_light",mqtt_light_cb},
};

void help_cb(char *str)
{
	int i,size = sizeof(cmd_list)/sizeof(cmd_t);
	for(i = 0;i < size;i++){
		printf("esp all cmd -- %s\n",cmd_list[i].cmd);
	}
}

void hub75_emoji_cb(char *str)
{
    char s[128] = {0};
    if(strstr(str,"view1")){
        sprintf(s,"emoji_%s",str);
        xQueueSend(xMyQueueHandle, s, 0);  /* 将字符串发送到队列中 */
    }
    // 这里可以添加处理hub75 emoji的代码
    printf("esp_online\n");
}

void hub75_off_cb(char *str)
{
    xQueueSend(xMyQueueHandle, "hub75_off", 0);  /* 将字符串发送到队列中 */
    // 这里可以添加处理hub75关闭的代码
    printf("esp_online\n");
}

void mqtt_light_cb(char *str)
{
    // 这里可以添加处理mqtt灯光打开的代码
    printf("esp_online\n");
}


void hub75_holo_cb(char *str)
{
    char s[128] = {0};
    if(strstr(str,"view1")){
        sprintf(s,"holo_%s",str);
        xQueueSend(xMyQueueHandle, s, 0);  /* 将字符串发送到队列中 */
    }
    // 这里可以添加处理hub75 holo的代码
    printf("esp_online\n");
}

/* 串口1的配置 */
const uart_config_t uart1_config = 
{
    .baud_rate = 115200,                   /* 通讯波特率 */
    .data_bits = UART_DATA_8_BITS,         /* 每一个数据是8位 */
    .parity    = UART_PARITY_DISABLE,      /* 关闭奇偶校验 */
    .stop_bits = UART_STOP_BITS_1,         /* 停止位是1位 */
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE, /* 软件控流 */
    .source_clk = UART_SCLK_APB,           /* APB时钟 */
};

void uart1_init(void)
{
    ESP_LOGI(TAG, "uart1_init");

    /* 设置串口1的参数 */
    ESP_ERROR_CHECK(uart_param_config(UART_NUM_1, &uart1_config));

    /* 设置串口的gpio口，esp32支持gpio口动态设置，这一次先使用默认的串口gpio */
    ESP_ERROR_CHECK(uart_set_pin(UART_NUM_1, GPIO_NUM_17, GPIO_NUM_18, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

    /* 启动串口1 */
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_1,         /* 串口1 */
                        UART1_TX_BUF_SIZE,  /* 发送FIFO的大小 */
                        UART1_RX_BUF_SIZE,  /* 接受FIFO的大小 */
                        0,                  /* 不使用queue */
                        NULL,               /* 因为不使用queue，所以NULL */
                        0)                  /* 不分配中断标志 */  
                    );                 
}

void uart1_echo_task(void *arg)
{
    uart1_init();
    while(1)
    {
        // char msg[] = "help\n";  /* 要发送的字符串 */
        // uart_write_bytes(UART_NUM_1,msg,strlen(msg));

        vTaskDelay(pdTICKS_TO_MS(10));   /* 延时10ms */

        int len = uart_read_bytes(UART_NUM_1,buffer,(UART1_RX_BUF_SIZE - 1), 20 / portTICK_PERIOD_MS);  /* 从串口1的RX_FIFO获取字符串 */

        /* 如果读到包的话 */
        if(len)
        {
            //buffer[len] = '\0';  /* 在结尾加入字符'\0'， */
            //uart_write_bytes(UART_NUM_1,msg,strlen(msg));
            cmd_proc((char *)buffer);
            memset(buffer,0,sizeof(buffer));  /* 清空内存，等待下一次的串口保文。 */
        }
    }
}

char *skip(char *buf)
{
	while(*buf == ' '){
		buf++;
	}
	return buf;
}
void cmd_proc(char* buffer){
	int i,size = sizeof(cmd_list)/sizeof(cmd_t);
	for(i = 0;i < size;i++){
		int len = strlen(cmd_list[i].cmd);
		if(strncmp(buffer,cmd_list[i].cmd,len) == 0){
			char *s = skip(buffer + len);
			cmd_list[i].cb(s); 
		}
	}
}

void cmd_err(void)
{
	printf("invalid cmd\n");
}

void uart1_printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char bf[128];
    vsnprintf(bf, sizeof(bf), fmt, args);
    uart_write_bytes(UART_NUM_1, bf, strlen(bf));
    va_end(args);
}
