#include <stdint.h> // for integer types
#include <sys/ioctl.h> // for driver control
#include <linux/fb.h> // for framebuffer
#include <sys/types.h> // for open()
#include <sys/stat.h> // for open()
#include <fcntl.h> // for open()
#include <sys/mman.h> // for mmap
#include <string.h> // for memset

#include "framebuffer.h"
#include "bitmap.h"

static int fd;
static uint16_t *screen;
struct fb_copyarea rect;

// will open framebuffer driver and clear screen
void setupFB(void)
{
    fd = open("/dev/fb0", O_RDWR);

    screen = mmap(0, 320*240*2, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    clearScreen();
}

// tell the framebuffer to update screen on the given rectangle
void updateRect(int dx, int dy, int width, int height)
{
    rect.dx = dx;
    rect.dy = dy;
    rect.width = width;
    rect.height = height;
    ioctl(fd, 0x4680, &rect);
}

// clear the entire screen
void clearScreen(void)
{
    memset(screen, 0x00, 320*240*2);
    updateRect(0, 0, 320, 240);
}

// draw a rectangle of given size and color
void drawRect(int x0, int y0, int width, int height, uint16_t *col)
{
    int y;
    int x;
    for (y = y0; y <= y0+height; y++){
        for (x = x0; x <= x0+width; x++){
            screen[320*y+x] = *col;
        }
    }
    updateRect(x0, y0, width, height);
}

// draw a bitmap on screen in given color
void drawBitmap(int centerx, int centery, bitmap_t *bitmap, uint16_t *col)
{
    int x0 = centerx - bitmap->width / 2;
    int y0 = centery - bitmap->height / 2;

    int y;
    int x;
    for (y = 0; y <= bitmap->height; y++) {
        for (x = 0; x <= bitmap->width; x++) {
            if (bitmap->array[bitmap->width * y + x] == 1) {
                screen[320*(y0+y)+(x0+x)] = *col;
            }
        }
    }
    updateRect(x0, y0, bitmap->width, bitmap->height);
}
