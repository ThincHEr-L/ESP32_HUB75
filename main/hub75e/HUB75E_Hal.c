/*
 * HUB75E_Hal.c
 *
 *  Created on: May 28, 2020
 *      Author: raeeskattali
 */
#include "HUB75E_Hal.h"
#include "driver/gpio.h"

#define P2_LED_PWR_Pin		12
#define HUB75E_OE_Pin		2
#define HUB75E_LATCH_Pin	40
#define HUB75E_CLK_Pin		41
#define HUB75E_ADDR_D_Pin	42
#define HUB75E_ADDR_C_Pin	3
#define HUB75E_ADDR_B_Pin	8
#define HUB75E_ADDR_A_Pin	38
#define HUB75E_ADDR_E_Pin	39
#define HUB75E_G2_Pin		15
#define HUB75E_B2_Pin		16
#define HUB75E_R2_Pin		7
#define HUB75E_G1_Pin		5
#define HUB75E_B1_Pin		6
#define HUB75E_R1_Pin		4

void HUB75E_GPIO_Init(void) {
	gpio_reset_pin(HUB75E_LATCH_Pin);
	gpio_reset_pin(HUB75E_CLK_Pin);
	gpio_reset_pin(HUB75E_ADDR_D_Pin);
	gpio_reset_pin(HUB75E_ADDR_E_Pin);

	gpio_reset_pin(HUB75E_OE_Pin);
	gpio_reset_pin(HUB75E_ADDR_C_Pin);
	gpio_reset_pin(HUB75E_ADDR_B_Pin);
	gpio_reset_pin(HUB75E_ADDR_A_Pin);
	gpio_reset_pin(HUB75E_G2_Pin);
	gpio_reset_pin(HUB75E_B2_Pin);
	gpio_reset_pin(HUB75E_R2_Pin);
	gpio_reset_pin(HUB75E_G1_Pin);
	gpio_reset_pin(HUB75E_B1_Pin);
	gpio_reset_pin(HUB75E_R1_Pin);
	gpio_set_direction(P2_LED_PWR_Pin, GPIO_MODE_DEF_OUTPUT);
	gpio_set_direction(HUB75E_OE_Pin, GPIO_MODE_DEF_OUTPUT);
	gpio_set_direction(HUB75E_LATCH_Pin, GPIO_MODE_DEF_OUTPUT);
	gpio_set_direction(HUB75E_CLK_Pin, GPIO_MODE_DEF_OUTPUT);
	gpio_set_direction(HUB75E_ADDR_D_Pin, GPIO_MODE_DEF_OUTPUT);
	gpio_set_direction(HUB75E_ADDR_C_Pin, GPIO_MODE_DEF_OUTPUT);
	gpio_set_direction(HUB75E_ADDR_B_Pin, GPIO_MODE_DEF_OUTPUT);
	gpio_set_direction(HUB75E_ADDR_A_Pin, GPIO_MODE_DEF_OUTPUT);
	gpio_set_direction(HUB75E_ADDR_E_Pin, GPIO_MODE_DEF_OUTPUT);
	gpio_set_direction(HUB75E_G2_Pin, GPIO_MODE_DEF_OUTPUT);
	gpio_set_direction(HUB75E_B2_Pin, GPIO_MODE_DEF_OUTPUT);
	gpio_set_direction(HUB75E_R2_Pin, GPIO_MODE_DEF_OUTPUT);
	gpio_set_direction(HUB75E_G1_Pin, GPIO_MODE_DEF_OUTPUT);
	gpio_set_direction(HUB75E_B1_Pin, GPIO_MODE_DEF_OUTPUT);
	gpio_set_direction(HUB75E_R1_Pin, GPIO_MODE_DEF_OUTPUT);
	//     gpio_config_t io_cfg = {
    //     .pin_bit_mask = 1 << GPIO_NUM_40,
    //     .mode = GPIO_MODE_OUTPUT,
    //     .pull_up_en = 0,
    //     .pull_down_en = 0,
    //     .intr_type = GPIO_INTR_DISABLE,
    // };
    // gpio_config(&io_cfg);
}

void HUB75E_DelayUs(int us) {
	for(int i = 0; i < (us * 10); i++);
	//DWT_Delay(us);
}

void HUB75E_setPin(HUB75EPin p, int state) {

	 switch (p)	 {
	 	 case PinRed1:
	 		gpio_set_level(HUB75E_R1_Pin, state);
	 		 break;
	 	case PinRed2:
	 		gpio_set_level(HUB75E_R2_Pin, state);
	 		break;
	 	case PinGreen1:
	 		gpio_set_level(HUB75E_G1_Pin, state);
	 		break;
	 	case PinGreen2:
	 		gpio_set_level(HUB75E_G2_Pin, state);
	 		break;
	 	case PinBlue1:
	 		gpio_set_level(HUB75E_B1_Pin, state);
	 		break;
	 	case PinBlue2:
	 		gpio_set_level(HUB75E_B2_Pin, state);
	 		break;
	 	case PinADDRA:
	 		gpio_set_level(HUB75E_ADDR_A_Pin, state);
	 		break;
	 	case PinADDRB:
	 		gpio_set_level(HUB75E_ADDR_B_Pin, state);
	 		break;
	 	case PinADDRC:
	 		gpio_set_level(HUB75E_ADDR_C_Pin, state);
	 		break;
	 	case PinADDRD:
	 		gpio_set_level(HUB75E_ADDR_D_Pin, state);
	 		break;
	 	case PinADDRE:
	 		gpio_set_level(HUB75E_ADDR_E_Pin, state);
	 		break;
	 	case PinCLK:
	 		gpio_set_level(HUB75E_CLK_Pin, state);
	 		break;
	 	case PinLATCH:
	 		gpio_set_level(HUB75E_LATCH_Pin, state);
	 		break;
	 	case PinOE:
	 		gpio_set_level(HUB75E_OE_Pin, state);
	 		break;
	 	default:
	 		break;
	 }

}
