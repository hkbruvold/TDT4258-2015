#include <stdint.h>

#include "board.h"

uint32_t boardarray[2400]; // 320*240/32

int checkRect(int x, int y, int width, int height)
{
    int indx = 320*y+x;
    int rem = indx%32;
    int newpos = 0;
    uint32_t *pos = &boardarray[indx/32];

    int dx;
    int y0;
    
    // check all positions in rectangle
    for (y0 = y; y <= y+height; y++) {
	pos += (10-newpos)*sizeof(pos); // move to next row
	newpos = 0;
	for (dx = 0; dx <= width; dx++) {
	     // if we go to next position in array
	    if (rem - dx == 0) {
		newpos++;
		pos++;
	    }
	    // check for collision
	    if (*pos & (1 << (32-rem+dx))) {
		return 1;
	    }
	}
    }
    return 0
}

