#ifndef MUSIC_H
#define MUSIC_H

#define SAMPLES 32768

/* Struct holding the samples for a musical tone */
typedef struct
{
    unsigned int length;
    unsigned short samples[];
} tone_t;

/* Struct holding information on a note of a song (a tone and a duration) */
typedef struct
{
    tone_t *tone;
    unsigned int duration;  // duration in samples
} note_t;

/* Struct describing a song (an array of notes) */
typedef struct
{
    unsigned int length;
    note_t notes[];
} song_t;

void play_song(song_t *song);
void play_effect();
void play();

#endif // MUSIC_H
