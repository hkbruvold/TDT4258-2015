#include <string.h>
#include <stdio.h>

#include "board.h"

// boardarray is used for detecting collisions
char boardarray[76800]; // 320*240

// check for collision in given rectangle
int checkRect(int x, int y, int width, int height, int oldx, int oldy)
{
    char *pos;

    int dx;
    int y0;
    for (y0 = y; y0 <= y+height; y0++) {
        pos = &boardarray[320*y0+x];
        for (dx = 0; dx <= width; dx++) {
            // check if not in same rectangle as previously
            if (!(y0 >= oldy && y0 <= (oldy + height) &&
                  (x + dx) >= oldx && (x + dx) <= (oldx + width))) {
                if (*pos == 1) { // check for collision
                    return 1;
                }
            }
            pos++;
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

// clear boardarray
void clearBoard(void)
{
    memset(&boardarray, 0, sizeof(boardarray));

    // add border around screen
    memset(&boardarray, 1, 320); // top edge
    memset(&boardarray[320*239], 1, 320); // bottom edge

    int y;
    for (y = 1; y <= 239; y++) {
        memset(&boardarray[320*y], 1, 1); // left edge
        memset(&boardarray[320*y+319], 1, 1); // right edge
    }
}
