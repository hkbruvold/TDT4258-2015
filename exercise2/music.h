#ifndef MUSIC_H
#define MUSIC_H

#define SAMPLES 32768

/* Struct holding the samples for a musical note */
typedef struct
{
    unsigned int length;
    unsigned short samples[];
} note_t;

/* Struct holding information on a part of a song (a note and a duration) */
typedef struct
{
    note_t *note;
    unsigned int duration;  // duration in samples
} song_part_t;

/* Struct describing a song (an array of song parts) */
typedef struct
{
    unsigned int length;
    song_part_t parts[];
} song_t;

void play_song(song_t *song);
void play_effect();
void play();

#endif // MUSIC_H
