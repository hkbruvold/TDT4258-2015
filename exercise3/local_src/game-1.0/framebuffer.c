#include <stdint.h> // for integer types
#include <sys/ioctl.h> // for driver control
#include <linux/fb.h> // for framebuffer
#include <sys/types.h> // for open()
#include <sys/stat.h> // for open()
#include <fcntl.h> // for open()
#include <sys/mman.h> // for mmap
#include <string.h> // for memset

uint16_t *screen;
struct fb_copyarea rect;

void setupFB()
{
	int fd = open("/dev/fb0", O_RDWR);
	
	screen = mmap(0, 320*240*2, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	clearScreen();
}

void updateRect(int dx, int dy, int width, int height)
{
	rect.dx = dx;
	rect.dy = dy;
	rect.width = width;
	rect.height = height;
	ioctl(fd, 0x4680, &rect);
}

void clearScreen()
{
	memset(screen, 0xff, 320*240*2);
	updateRect(0, 0, 320, 240);
}
