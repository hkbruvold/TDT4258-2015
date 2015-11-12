#ifndef BITMAP_H
#define BITMAP_H

typedef struct
{
    int width;
    int height;
    char array[];
} bitmap_t;

bitmap_t trophy;

#endif
