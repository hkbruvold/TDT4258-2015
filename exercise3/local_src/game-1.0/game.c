#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "game.h"
#include "framebuffer.h"

int main(int argc, char *argv[])
{
    printf("Hello World, I'm game!\n");
	
    setupFB();
    
    gameloop();
	
    exit(EXIT_SUCCESS);
}


void gameloop()
{
    uint16_t black = COLOR(0b00000, 0b000000, 0b00000);
    uint16_t white = COLOR(0b11111, 0b111111, 0b11111);
    
    uint16_t *curcol = &white;
    int dp = 0;
    
    struct timespec lastTime;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &lastTime);
    while (1) {
	while (msSince(lastTime)<1000);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &lastTime);
	
	drawRect(50+dp/2, 40+dp/2, 100-dp, 100-dp, curcol);
	
	dp += 10;
	if (dp >= 80) {
	    break;
	}
	if (*curcol == white) {
	    curcol = &black;
	} else {
	    curcol = &white;
	}
    }
}

// return difference in milliseconds from start to stop
long getmsDiff(struct timespec start, struct timespec stop)
{
    long diff;
    diff = ((long) stop.tv_sec*1000 + stop.tv_nsec/1E6) 
 	 - ((long) start.tv_sec*1000 + start.tv_nsec/1E6);
    
    return diff;
}

// return elapsed time in millisecond since prev
long msSince(struct timespec prev)
{
    struct timespec now;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &now);
    return getmsDiff(prev, now);
}
