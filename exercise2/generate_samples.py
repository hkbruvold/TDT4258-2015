#! /usr/bin/env python2

from math import sin, pi

samples_per_sec = 32768

def generate_sample(freq):
    s = []
    samples = int(samples_per_sec / freq)
    for i in range(samples):
        s.append(sin(2*pi*(i/float(samples))))
    return s

def convert_to_12bit(sample, amp=1.0):
    s = []
    maxvalue = 2**12
    for value in sample:
        value += 1
        value /= 2
        value *= amp
        value *= maxvalue
        s.append(int(value))
    return s

def format_array(sample, tone):
    text = "static tone_t tone_{} = {{ ".format(tone)
    text += ".length = {}, .samples = {{ ".format(len(sample))
    for i in range(len(sample)-1):
        text += str(sample[i])
        text += ", "
    text += str(sample[-1])
    text += " } };\n\n"
    return text

def create_samples(freq, tone):
    a = generate_sample(freq)
    b = convert_to_12bit(a)
    c = format_array(b, tone)
    return c

def new_song(name, tones):
    """tones are list of tuples (length_in_milliseconds, tone)"""
    text = "song_t %s = {\n" %(name)
    text += "    .length = %i,\n" %(len(tones))
    text += "    .notes = {\n"
    for tone in tones:
        length = int(tone[0]/1000.0*samples_per_sec)
        text += "        { .duration = %i, .tone = &tone_%s },\n" %(length, tone[1])
    text += "    }\n"
    text += "};\n\n"
    return text

def add_song(name, tones, c, h):
    c.write(new_song(name, tones))
    h.write("extern song_t {};\n".format(name))

c = open("music_defs.c", 'w')
h = open("music_defs.h", 'w')

c.write('#include "music_defs.h"\n\n')
h.write("#ifndef MUSIC_DEFS_H\n")
h.write("#define MUSIC_DEFS_H\n\n")
h.write('#include "music.h"\n\n')

### generate samples

c.write(format_array([2048], "silence"))
c.write(create_samples(207.65, "ab3"))
c.write(create_samples(235.08, "bb3"))
c.write(create_samples(261.63, "c4"))
c.write(create_samples(523.25, "c5"))
c.write(create_samples(587.33, "d5"))
c.write(create_samples(659.25, "e5"))
c.write(create_samples(698.46, "f5"))
c.write(create_samples(783.99, "g5"))
c.write(create_samples(880, "a5"))

### generate songs

speed = 60000/130.0
add_song("victory_fanfare", (
    (50, "silence"), (speed/2-100, "c4"), (50, "silence"),
    (50, "silence"), (speed/2-100, "c4"), (50, "silence"),
    (50, "silence"), (speed/2-100, "c4"), (50, "silence"),
    (speed/1-50, "c4"), (50, "silence"),
    (speed/1, "ab3"),
    (speed/1, "bb3"),
    (speed/2, "c4"),
    (speed/2, "bb3"),
    (speed*3, "c4"),
), c, h)

speed = 1500
add_song("lisa_gikk_til_skolen", (
    (speed/4, "c5"),
    (speed/4, "d5"),
    (speed/4, "e5"),
    (speed/4, "f5"),
    (speed/2-50, "g5"),
    (50, "silence"),
    (speed/2-50, "g5"),
    (50, "silence"),
    (speed/4-50, "a5"),
    (50, "silence"),
    (speed/4-50, "a5"),
    (50, "silence"),
    (speed/4-50, "a5"),
    (50, "silence"),
    (speed/4-50, "a5"),
    (50, "silence"),
    (speed-50, "g5"),
    (50, "silence"),

    (speed/4-50, "f5"),
    (50, "silence"),
    (speed/4-50, "f5"),
    (50, "silence"),
    (speed/4-50, "f5"),
    (50, "silence"),
    (speed/4-50, "f5"),
    (speed/2-50, "e5"),
    (50, "silence"),
    (speed/2-50, "e5"),
    (50, "silence"),
    (speed/4-50, "d5"),
    (50, "silence"),
    (speed/4-50, "d5"),
    (50, "silence"),
    (speed/4-50, "d5"),
    (50, "silence"),
    (speed/4-50, "d5"),
    (speed, "c5"),
), c, h)

h.write("\n#endif")
c.close()
h.close()

