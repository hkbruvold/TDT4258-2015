#include <sys/ioctl.h> // for driver control
#include <sys/types.h> // for open()
#include <sys/stat.h> // for open()
#include <fcntl.h> // for open()
#include <unistd.h> // for read()

#include "gamepad.h"

int gfd;

void setupGamepad()
{
    gfd = open("/dev/gamepad", O_RDWR);
}

char readGamepad()
{
    char data;
    read(gfd, &data, 1);
    return data;
}
