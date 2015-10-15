#ifndef MUSIC_H
#define MUSIC_H

#define SAMPLES 32768

typedef struct
{
    unsigned int length;
    unsigned short samples[];
} note_t;

typedef struct
{
    note_t *note;
    unsigned int duration;  // duration in samples
} song_part_t;

typedef struct
{
    unsigned int length;
    song_part_t parts[];
} song_t;

void set_song(song_t *song);
void play();

#endif // MUSIC_H
