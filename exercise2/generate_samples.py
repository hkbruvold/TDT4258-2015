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
    text += " } }"
    return text

def create_samples(freq, note):
    a = generate_sample(freq)
    b = convert_to_12bit(a)
    c = format_array(b, note)
    print c

create_samples(440, "a4")
create_samples(466, "bflat")
create_samples(494, "b")
create_samples(523, "c")
create_samples(554, "csharp")
create_samples(587, "d")
create_samples(622, "dsharp")
create_samples(659, "e")
create_samples(698, "f")
create_samples(740, "fsharp")
create_samples(784, "g")
create_samples(831, "aflat")
create_samples(880, "a5")
