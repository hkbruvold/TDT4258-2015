#! /usr/bin/env python

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
        value *= amp
        value += 1
        value /= 2
        value *= maxvalue
        s.append(int(value))
    return s

def format(sample):
    text = "{ "
    for i in range(len(sample)-1):
        text += str(sample[i])
        text += ", "
    text += str(sample[-1])
    text += " }"
    return text

a = generate_sample(440)
b = convert_to_12bit(a)
c = format(b)
print c
