#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "framebuffer.h"

int main(int argc, char *argv[])
{
	printf("Hello World, I'm game!\n");
	
	setupFB();
	
	uint16_t col = COLOR(0b11111, 0b000000, 0b11111);
	drawRect(120, 100, 80, 50, &col);
	
	exit(EXIT_SUCCESS);
}

