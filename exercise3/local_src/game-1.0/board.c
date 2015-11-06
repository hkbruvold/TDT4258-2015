#include "board.h"

char boardarray[76800]; // 320*240

// check for collision in given rectangle
int checkRect(int x, int y, int width, int height)
{
    char *pos;

    int dx;
    int y0;
    for (y0 = y; y0 <= y+height; y0++) {
	pos =  = &boardarray[320*y0+x];
	for (dx = 0; dx <= width; dx++) {
	    if (*pos++ == 1) { // check for collision
		return 1;
	    }
	}
    }
    return 0;
}

// store rectangle in array
void setRect(int x, int y, int width, int height)
{
    int y0;
    for (y0 = y; y0 <= y+height; y0++) {
	memset(&boardarray[320*y0+x], 1, width);
    }
}
