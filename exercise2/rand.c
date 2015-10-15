#include "rand.h"

static unsigned int next = 1;

int rand_r(unsigned int *seed)
{
    *seed = *seed * 1103515245 + 12345;
    return (*seed % ((unsigned int)(1<<31) + 1));
}

int rand(void)
{
    return (rand_r(&next));
}

void srand(unsigned int seed)
{
    next = seed;
}
