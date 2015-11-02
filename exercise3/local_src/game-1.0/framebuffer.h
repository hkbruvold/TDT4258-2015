#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

typedef struct {
  uint16_t red : 5;
  uint16_t green : 6;
  uint16_t blue : 5;
} color_t;

void setupFB();
void updateRect(int dx, int dy, int width, int height);
void clearScreen();
void drawRect(int x0, int y0, int width, int height, color_t *col);

#endif
