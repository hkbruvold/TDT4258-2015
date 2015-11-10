import math

sample_size = 30

sintext = "{"
costext = "{"

for i in range(sample_size):
    sintext += str(math.sin(i/float(sample_size) * 2*math.pi)) + ", "
    costext += str(math.cos(i/float(sample_size) * 2*math.pi)) + ", "



print sintext[:-2]+"}"
print costext[:-2]+"}"

