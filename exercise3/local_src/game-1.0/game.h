#ifndef GAME_H
#define GAME_H

void gameloop();
long getmsDiff(struct timespec start, struct timespec stop);
long msSince(struct timespec prev);

#endif
