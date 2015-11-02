#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "framebuffer.h"

int main(int argc, char *argv[])
{
	printf("Hello World, I'm game!\n");
	
	setupFB();
	
	color_t col;
	col.red = 0b00000;
	col.green = 0b111111;
	col.blue = 0b00000;
	drawRect(120, 100, 80, 50, &col);
	
	exit(EXIT_SUCCESS);
}

