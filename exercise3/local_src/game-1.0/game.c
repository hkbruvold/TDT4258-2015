#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "game.h"
#include "framebuffer.h"
#include "board.h"

#define PI 3.14159265

// SPEED is pixels per tick
#define SPEED 1 
// SNAKE_WIDTH is diameter of snake
#define SNAKE_WIDTH 4

struct snake {
    double x;
    double y;
    int direction; // direction is between 0-29
};

void tick();
int updatePlayers();

struct snake player1;
struct snake player2;
int running; // boolean if game is running
int p1collide; // boolean if player 1 collides
int p2collide; // boolean if player 2 collides

int main(int argc, char *argv[])
{
    printf("Hello World, I'm game!\n");
	
    setupFB();
    
    gameloop();
	
    exit(EXIT_SUCCESS);
}


void gameloop()
{
    // initialise player positions
    player1.x = 80;
    player1.y = 120;
    player1.direction = 15;
    
    player2.x = 240;
    player2.y = 120;
    player2.direction = 0;

    // set value to keep game running
    running = 1;
    
    struct timespec lastTime;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &lastTime);
    while (1) {
	while (msSince(lastTime)<100); // TODO: replace with sleep
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &lastTime);
	
	tick();
    }
}

// each tick moves the players and check for collisions
void tick()
{
    if (running) {
	if (updatePlayers()) {
	    // when a collision is not deteted
	} else {
	    // when a collision is detected
	    running = 0;
	    printf("Collision detected, stopping\n");
	}
    }
}

// function to move players and update screen returns 1 if collision, and 0 if no collision
int updatePlayers()
{
    uint16_t blue = COLOR(0b00000, 0b000000, 0b11111);
    uint16_t red = COLOR(0b11111, 0b000000, 0b00000);

    // calculate new position
    player1.x += SPEED*coslist[player1.direction];
    player1.y -= SPEED*sinlist[player1.direction]; //substract because of positive y direction
    player2.x += SPEED*coslist[player2.direction];
    player2.y -= SPEED*sinlist[player2.direction];

    // draw on screen
    drawRect((int) player1.x, (int) player1.y, SNAKE_WIDTH, SNAKE_WIDTH, &red);
    drawRect((int) player2.x, (int) player2.y, SNAKE_WIDTH, SNAKE_WIDTH, &blue);
    
    // check for collision
    p1collide = checkRect((int) player1.x, (int) player1.y, SNAKE_WIDTH, SNAKE_WIDTH);
    p2collide = checkRect((int) player2.x, (int) player2.y, SNAKE_WIDTH, SNAKE_WIDTH);

    // add position to board array
    setRect((int) player1.x, (int) player1.y, SNAKE_WIDTH, SNAKE_WIDTH);
    setRect((int) player2.x, (int) player2.y, SNAKE_WIDTH, SNAKE_WIDTH);

    if (p1collide || p2collide) {
	return 1;
    }
    return 0;
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
