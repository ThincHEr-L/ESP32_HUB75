#ifndef _HUB75_H_
#define _HUB75_H_



#ifdef __cplusplus
    extern "C" {
#endif

#include <stdint-gcc.h>

void hub75init(void);
void WS2812B_DrawChar(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t chr,uint8_t r,uint8_t g,uint8_t b);
void drawpixel888(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b);
void fillscreen888(uint8_t ccccccccccr, uint8_t g, uint8_t b);
void drawimage(int *im,int16_t x, int16_t y,int16_t w, int16_t h);
void drawpixel565(int16_t x, int16_t y, uint16_t color);
void drawHLine(int16_t x, int16_t y, int16_t w, uint8_t r, uint8_t g, uint8_t b);
void dmahub75clear(void);

extern const int* epd_bitmap_allArray[150];
extern const unsigned char WS2812B_asc2_0808[][8];
#ifdef __cplusplus
    }
#endif

#endif // !_HUB75_H_

