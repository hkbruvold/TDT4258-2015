#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#define COLOR(red, green, blue) (red << 11) + (green << 5) + (blue)

void setupFB();
void updateRect(int dx, int dy, int width, int height);
void clearScreen();
void drawRect(int x0, int y0, int width, int height, uint16_t *col);

#endif
