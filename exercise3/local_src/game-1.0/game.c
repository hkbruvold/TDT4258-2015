#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "framebuffer.h"

int main(int argc, char *argv[])
{
    printf("Hello World, I'm game!\n");
	
    setupFB();
	
    uint16_t black = COLOR(0b00000, 0b000000, 0b00000);
    uint16_t white = COLOR(0b11111, 0b111111, 0b11111);
    drawRect(120, 100, 80, 80, &white);
    drawRect(125, 105, 70, 70, &black);
    drawRect(130, 110, 60, 60, &white);
    drawRect(135, 115, 50, 50, &black);
    drawRect(140, 120, 40, 40, &white);
    drawRect(145, 125, 30, 30, &black);
    drawRect(150, 130, 20, 20, &white);
    drawRect(155, 135, 10, 10, &black);
	
    exit(EXIT_SUCCESS);
}


void gameloop()
{
    timespec lastTime;
    clock_gettime(CLOCK_BOOTTIME, &lastTime);
    while (true){
	while (msSince(lastTime)<1000);
	clock_gettime(CLOCK_BOOTTIME, &lastTime);
	
	// do something
    }
}

// return difference in milliseconds from start to stop
long getmsDiff(timespec start, timespec stop)
{
    long diff;
    diff = ((long) stop.tv_sec*1000 + stop.tv_nsec/1E6) 
 	 - ((long) start.tv_sec*1000 + start.tv_nsec/1E6);
    
    return diff;
}

// return elapsed time in millisecond since prev
long msSince(timespec prev)
{
    timespec now;
    clock_gettime(CLOCK_BOOTTIME, &now);
    return getmsDiff(prev, now);
}
