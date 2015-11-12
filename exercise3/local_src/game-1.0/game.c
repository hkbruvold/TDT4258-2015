#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "game.h"
#include "framebuffer.h"
#include "board.h"
#include "gamepad.h"

#define PI 3.14159265

// TICKTIME is time in nanoseconds between each tick
#define TICKTIME 100000000
// SPEED is pixels per tick
#define SPEED 4
// SNAKE_WIDTH is diameter of snake
#define SNAKE_WIDTH 4

struct snake {
    double x;
    double y;
    int direction; // direction is between 0-29
};

void tick();
int updatePlayers();
void turnPlayer(struct snake *player, int d);
void updateDirections();
void checkForRestart();
void initGame();
void gameloop();
void getTimespecDiff(struct timespec *diffTime, struct timespec *start, struct timespec *stop);
void timespecSince(struct timespec *tSince, struct timespec *prev);

struct snake player1;
struct snake player2;
int running; // boolean if game is running
int exitgame; // boolean if game should exit
int p1collide; // boolean if player 1 collides
int p2collide; // boolean if player 2 collides

int main(int argc, char *argv[])
{
    printf("Welcome!\nSW1 and SW3 controls red player\nSW5 and SW7 controls blue player\n");
    
    // setup framebuffer and gamepad
    setupFB();
    setupGamepad();
    
    // initialise game and run gameloop
    initGame();
    gameloop();

    return 0;
}

void initGame()
{
    // initialise player positions
    player1.x = 80;
    player1.y = 120;
    player1.direction = 7;
    
    player2.x = 240;
    player2.y = 120;
    player2.direction = 7;

    // set value to keep game running
    running = 1;
    exitgame = 0;
    
    // clear board for fresh start
    clearBoard();
}

void gameloop()
{    
    // setup for keeping track of time
    struct timespec lastTime;
    struct timespec sleepTime;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &lastTime);

    // mainloop
    while (1) {
	// sleep until next tick
	timespecSince(&sleepTime, &lastTime);
	sleepTime.tv_nsec = TICKTIME - sleepTime.tv_nsec; // assume tick time is less than one sec
	nanosleep(&sleepTime, NULL);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &lastTime);
	
	// execute tick function
	tick();
    }
}

// each tick moves the players and check for collisions
void tick()
{
    if (running) {
	if (updatePlayers() == 0) {
	    // when a collision is not deteted
	    updateDirections();
	} else {
	    // when a collision is detected
	    running = 0;
	    printf("Press SW2 to restart or SW4 to exit\n");
	}
    } else {
	checkForRestart();
    }
    if (exitgame) {
	printf("Stopping game\n");
	exit(EXIT_SUCCESS);
    }	
}

// function to move players and update screen returns 1 if collision, and 0 if no collision
int updatePlayers()
{
    uint16_t blue = COLOR(0b00000, 0b000000, 0b11111);
    uint16_t red = COLOR(0b11111, 0b000000, 0b00000);
    
    // variables used to prevent collision detection on old position
    int old1x = (int) player1.x;
    int old1y = (int) player1.y;
    int old2x = (int) player2.x;
    int old2y = (int) player2.y;

    // calculate new position
    player1.x += SPEED*coslist[player1.direction];
    player1.y -= SPEED*sinlist[player1.direction]; //substract because of positive y direction
    player2.x += SPEED*coslist[player2.direction];
    player2.y -= SPEED*sinlist[player2.direction];

    // draw on screen
    drawRect((int) player1.x, (int) player1.y, SNAKE_WIDTH, SNAKE_WIDTH, &red);
    drawRect((int) player2.x, (int) player2.y, SNAKE_WIDTH, SNAKE_WIDTH, &blue);
    
    // check for collision
    p1collide = checkRect((int) player1.x, (int) player1.y, SNAKE_WIDTH, SNAKE_WIDTH, old1x, old1y);
    p2collide = checkRect((int) player2.x, (int) player2.y, SNAKE_WIDTH, SNAKE_WIDTH, old2x, old2y);

    // add position to board array
    setRect((int) player1.x, (int) player1.y, SNAKE_WIDTH, SNAKE_WIDTH);
    setRect((int) player2.x, (int) player2.y, SNAKE_WIDTH, SNAKE_WIDTH);

    if (p1collide == 1) {
	printf("Game over!\nBlue player won, red player collided\n");
	return 1;
    }
    if (p2collide == 1) {
	printf("Game over!\nRed player won, blue player collided\n");
	return 1;
    }
    return 0;
}

// function to read gamepad and update player directions
void updateDirections()
{
    char data = readGamepad();
    
    if (!(data & 0b1)) { // SW1
        turnPlayer(&player1, 1);
    }
    if (!(data & 0b100)) { //SW3
        turnPlayer(&player1, -1);
    }
    if (!(data & 0b10000)) { //SW5
	turnPlayer(&player2, 1);
    }
    if (!(data & 0b1000000)) { //SW7
	turnPlayer(&player2, -1);
    }
}

// check for restart or exit, will update boolean values
void checkForRestart()
{
    char data = readGamepad();

    if (!(data & 0b10)) { // SW2
	running = 1;
	initGame();
	clearScreen();
    }
    if (!(data & 0b1000)) { //SW4
	exitgame = 1;
    }
}

// function to turn player, every d is 12 degree
void turnPlayer(struct snake *player, int d)
{
    player->direction += d;
    if (player->direction < 0) {
	player->direction += 30;
    } else if (player->direction > 29) {
	player->direction -= 30;
    }
}    

// diffTime will get time difference between start and stop
void getTimespecDiff(struct timespec *diffTime, struct timespec *start, struct timespec *stop)
{
    diffTime->tv_sec = stop->tv_sec - start->tv_sec;
    if (stop->tv_nsec < start->tv_nsec) {
	diffTime->tv_nsec = stop->tv_nsec + 1E9 - start->tv_nsec;
	diffTime->tv_sec--;
    } else {
	diffTime->tv_nsec = stop->tv_nsec - start->tv_nsec;
    }
}

// tSince will get time difference since prev
void timespecSince(struct timespec *tSince, struct timespec *prev)
{
    struct timespec now;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &now);
    getTimespecDiff(tSince, prev, &now);
}
