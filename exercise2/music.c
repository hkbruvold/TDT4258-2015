#include "efm32gg.h"

#include "music.h"
//
static unsigned int sample_counter;  // current sample in note
static unsigned int duration_counter; // time playing this note
static unsigned int part_counter;  // current note in song
static song_t *current_song;

void play_next_sample(note_t *note);

void set_song(song_t *song)
{
    current_song = song;
    part_counter = 0;
    duration_counter = 0;
    sample_counter = 0;
}

void play()
{
    // check if a song is playing
    if (current_song == 0)
    {
        *DAC0_CH0DATA = 0;
        *DAC0_CH1DATA = 0;
        return;
    }

    // play next sample in the current part
    song_part_t *part = &current_song->parts[part_counter];
    play_next_sample(part->note);
    ++duration_counter;

    // if we've finished playing this part, move to the next one
    if (duration_counter >= part->duration)
    {
        duration_counter = 0;
        ++part_counter;
    }

    // we've played the entire song, stop
    if (part_counter >= current_song->length)
        current_song = 0;
}

void play_next_sample(note_t *note)
{
    // play a sample from the note
    if (sample_counter >= note->length)
        sample_counter = 0;

    *DAC0_CH0DATA = note->samples[sample_counter];
    *DAC0_CH1DATA = note->samples[sample_counter];

    ++sample_counter;
}

