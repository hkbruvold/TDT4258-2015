#! /usr/bin/env python2

from math import sin, pi

samples_per_sec = 32768

def generate_sample(freq):
    s = []
    samples = samples_per_sec / freq
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
    text = "static struct note_t note_{} = {{ ".format(note)
    text += ".length = {}, .samples = {{ ".format(len(sample))
    for i in range(len(sample)-1):
        text += str(sample[i])
        text += ", "
    text += str(sample[-1])
    text += " } };"
    return text

def create_samples(freq, note):
    a = generate_sample(freq)
    b = convert_to_12bit(a)
    c = format_array(b, note)
    return c
    
def new_song(name, notes):
    """notes are list of tuples (length_in_milliseconds, note)"""
    text = "static song_t %s = {\n" %(name)
    text += "    .length = %i,\n" %(len(notes))
    text += "    .parts = {\n"
    for note in notes:
        length = int(note[0]/1000.0*samples_per_sec)
        text += "        { .duration = %i, .note = &note_%s },\n" %(length, note[1])
    text += "    }\n"
    text += "};\n\n"
    return text

c = open("music_defs.c", 'w')
h = open("music_defs.h", 'w')


c.write("#include \"music.h\"\n\n")

### generate samples

c.write(create_samples(440, "a4")+"\n")
c.write(create_samples(466, "bflat")+"\n")
c.write(create_samples(494, "b")+"\n")
c.write(create_samples(523, "c"))
c.write(create_samples(554, "csharp")+"\n")
c.write(create_samples(587, "d")+"\n")
c.write(create_samples(622, "dsharp")+"\n")
c.write(create_samples(659, "e")+"\n")
c.write(create_samples(698, "f")+"\n")
c.write(create_samples(740, "fsharp")+"\n")
c.write(create_samples(784, "g")+"\n")
c.write(create_samples(831, "aflat")+"\n")
c.write(create_samples(880, "a5")+"\n\n")

### generate music

testmusic = [(500, "a4"),
             (500, "bflat"),
             (500, "b"),
             (500, "c")]

c.write(new_song("test", testmusic))


c.close()
