#
# Simple development makefile
#

#
# add more flags here,
# but don't remove the "+="
#
CFLAGS += -O2 -g -Wall #-Wsign-compare -Wfloat-equal -Wformat-security #-Werror
CPPFLAGS +=
LDFLAGS += -lm


all: game

game: framebuffer.o board.o gamepad.o

clean:
	-rm -f game

install:


.PHONY: all install clean

# end of development makefile
