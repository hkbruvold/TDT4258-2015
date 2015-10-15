#include "efm32gg.h"
#include "ex2.h"
#include "rand.h"

#include "music.h"

static unsigned int sample_counter;  // current sample in note
static unsigned int duration_counter; // time playing this note
static unsigned int part_counter;  // current note in song
static song_t *current_song;

#define MAX_EFFECT_DURATION 16384
static unsigned int effect_duration;

void play_next_sample(note_t *note);
void play_effect_sample();

/* start playing a song */
void play_song(song_t *song)
{
    current_song = song;
    part_counter = 0;
    duration_counter = 0;
    sample_counter = 0;
    effect_duration = 0;

    start_timer();
}

/* start playing a "random" sound effect */
void play_effect()
{
    play_song(0);
    effect_duration = MAX_EFFECT_DURATION;
}

/* The main sound function, should be called 32768 times per second */
void play()
{
    // if the sound effect is playing, play a sample and return
    if (effect_duration > 0)
    {
        play_effect_sample();
        return;
    }
    /* if there's no song playing (and no effect), turo off the timer and
     * return */
    else if (current_song == 0)
    {
        *DAC0_CH0DATA = 0;
        *DAC0_CH1DATA = 0;
        stop_timer();
        return;
    }

    // play next sample in the current song part
    song_part_t *part = &current_song->parts[part_counter];
    play_next_sample(part->note);
    ++duration_counter;

    /* if we've finished playing this part, move to the next one
     * Also, make sure we don't move in the middle of a tone */
    if (duration_counter >= part->duration && sample_counter == 1)
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

    // send samples to both DAC channels
    *DAC0_CH0DATA = note->samples[sample_counter];
    *DAC0_CH1DATA = note->samples[sample_counter];

    ++sample_counter;
}

/* The sound effect is just random noise fading in volume. Sounds kinda cool */
void play_effect_sample()
{
    *DAC0_CH0DATA = ((rand() % (1 << 12)) * effect_duration) / MAX_EFFECT_DURATION;
    *DAC0_CH1DATA = ((rand() % (1 << 12)) * effect_duration) / MAX_EFFECT_DURATION;

    --effect_duration;
}

