#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "bitmap.h"

// COLOR(5 bit red, 6 bit green, 5 bit blue)
#define COLOR(red, green, blue) (red << 11) + (green << 5) + (blue)

void setupFB(void); // used to load framebuffer file and clear screen
void updateRect(int dx, int dy, int width, int height); // update screen on rectangle
void clearScreen(void); // clear the entire screen
void drawRect(int x0, int y0, int width, int height, uint16_t *col); // draw rectangle with color
void drawBitmap(int centerx, int centery, bitmap_t *bitmap, uint16_t *col); // draw bitmap

#endif
