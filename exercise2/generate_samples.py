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

def format_array(sample, note):
    text = "static note_t note_{} = {{ ".format(note)
    text += ".length = {}, .samples = {{ ".format(len(sample))
    for i in range(len(sample)-1):
        text += str(sample[i])
        text += ", "
    text += str(sample[-1])
    text += " } };\n\n"
    return text

def create_samples(freq, note):
    a = generate_sample(freq)
    b = convert_to_12bit(a)
    c = format_array(b, note)
    return c

def new_song(name, notes):
    """notes are list of tuples (length_in_milliseconds, note)"""
    text = "song_t %s = {\n" %(name)
    text += "    .length = %i,\n" %(len(notes))
    text += "    .parts = {\n"
    for note in notes:
        length = int(note[0]/1000.0*samples_per_sec)
        text += "        { .duration = %i, .note = &note_%s },\n" %(length, note[1])
    text += "    }\n"
    text += "};\n\n"
    return text

def add_song(name, notes, c, h):
    c.write(new_song(name, notes))
    h.write("extern song_t {};\n".format(name))

c = open("music_defs.c", 'w')
h = open("music_defs.h", 'w')

c.write('#include "music_defs.h"\n\n')
h.write("#ifndef MUSIC_DEFS_H\n")
h.write("#define MUSIC_DEFS_H\n\n")
h.write('#include "music.h"\n\n')

### generate samples

c.write(format_array([0], "silence"))
c.write(create_samples(523.25, "c5"))
c.write(create_samples(587.33, "d5"))
c.write(create_samples(659.25, "e5"))
c.write(create_samples(698.46, "f5"))
c.write(create_samples(783.99, "g5"))
c.write(create_samples(880, "a5"))

### generate songs

speed = 2000
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

