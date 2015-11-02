#include <stdio.h>
#include <stdlib.h>

#include "framebuffer.h"

int main(int argc, char *argv[])
{
	printf("Hello World, I'm game!\n");
	
	setupFB();
	
	exit(EXIT_SUCCESS);
}

