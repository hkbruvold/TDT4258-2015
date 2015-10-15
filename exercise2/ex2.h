#define USE_LETIMER

#ifndef EX2_H
#define EX2_H

void setupLETIMER();
void setupDAC();
void setupNVIC();
void setupGPIO();

void start_timer();
void stop_timer();

#endif // EX2_H
