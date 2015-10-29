#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/ioctl.h>

// for framebuffer struct
#include <linux/fb.h>

// for open()
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// for mmap
#include <sys/mman.h>


int main(int argc, char *argv[])
{
	printf("Hello World, I'm gamaoeue!\n");
	int fd = open("/dev/fb0", O_RDWR);
	
	uint16_t *screen = mmap(0, 320*240*2, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	
	screen[240*3+10] = 0xffff;

	struct fb_copyarea rect;
	rect.dx = 0;
	rect.dy = 0;
	rect.width = 320;
	rect.height = 240;
	ioctl(fd, 0x4680, &rect);
	
	exit(EXIT_SUCCESS);
}
