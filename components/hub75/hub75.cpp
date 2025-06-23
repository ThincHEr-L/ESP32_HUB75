#include <stdio.h>
#include "hub75.h"
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>
#include <ESP32-VirtualMatrixPanel-I2S-DMA.h>
#define R1_PIN 4
#define G1_PIN 5
#define B1_PIN 6
#define R2_PIN 7
#define G2_PIN 15
#define B2_PIN 16
#define A_PIN  38
#define B_PIN  8
#define C_PIN  3
#define D_PIN  42
#define E_PIN  39 // required for 1/32 scan panels, like 64x64. Any available pin would do, i.e. IO32
#define LAT_PIN 40
#define OE_PIN  2
#define CLK_PIN 41

HUB75_I2S_CFG::i2s_pins _pins={R1_PIN, G1_PIN, B1_PIN, R2_PIN, G2_PIN, B2_PIN, A_PIN, B_PIN, C_PIN, D_PIN, E_PIN, LAT_PIN, OE_PIN, CLK_PIN};
HUB75_I2S_CFG mxconfig(
	64, // Module width
	64, // Module height
	1, // chain length
	_pins, // pin mapping
	HUB75_I2S_CFG::SHIFTREG, // driver type
	false, // double buffer
	HUB75_I2S_CFG::HZ_20M // I2S clock speed
);

MatrixPanel_I2S_DMA *dma_display = nullptr;

void hub75init(void)
{
dma_display = new MatrixPanel_I2S_DMA(mxconfig);
dma_display->begin();
dma_display->setBrightness(100);
dma_display->clearScreen(); // Clear the screen
}

void WS2812B_DrawChar(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t chr,uint8_t r,uint8_t g,uint8_t b)
{
	uint8_t temp;
	uint8_t chr1 = chr - ' ';
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			// 璁＄畻褰撳墠鍍忕礌鍦ㄤ綅鍥炬暟鎹腑鐨勫瓧鑺傜储寮曞拰浣嶅亸绉?
			uint16_t byte_index = i * ((w + 7) / 8) + j / 8;
			uint8_t bit_offset = j % 8;
			temp = WS2812B_asc2_0808[chr1][byte_index];
			// 妫€鏌ュ綋鍓嶅儚绱犱綅鏄惁涓?0
			if ((temp & (1 << (7 - bit_offset))) == 0)
			{
				dma_display->drawPixelRGB888(x + j, y + i,r,g,b);
			}
			else
			{
				dma_display->drawPixelRGB888(x + j, y + i, 0, 0, 0);
			}
		}
	}
}
void drawpixel888(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b)
{
	dma_display->drawPixelRGB888(x, y, r, g, b);
}
void fillscreen888(uint8_t r, uint8_t g, uint8_t b)
{
	dma_display->fillScreenRGB888(r, g, b);
}
void drawpixel565(int16_t x, int16_t y, uint16_t color)
{
	dma_display->drawPixel(x, y,color);
}
void drawimage(int *im,int16_t x, int16_t y,int16_t w, int16_t h)
{
	dma_display->drawIcon(im,x,y,w,h);
}
void drawHLine(int16_t x, int16_t y, int16_t w, uint8_t r, uint8_t g, uint8_t b)
{
	dma_display->drawFastHLine(x,y,w,r,g,b);
}
void dmahub75clear(void)
{
 dma_display->clearScreen(); // Clear the screen
}
