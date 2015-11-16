#include <sys/ioctl.h> // for driver control
#include <sys/types.h> // for open()
#include <sys/stat.h> // for open()
#include <fcntl.h> // for open()
#include <unistd.h> // for read()
#include <signal.h> // for signal()
#include <string.h> // for memset()
#include <stdio.h>

#include "gamepad.h"

static int fd;
static char data;

void setupGamepad(void)
{
    struct sigaction action;

    fd = open("/dev/gamepad", O_RDWR);

    // clear the struct and set handler to readDriver function
    memset(&action, 0, sizeof(action));
    action.sa_handler = readDriver;
    action.sa_flags = 0;

    // register the struct to the signal SIGIO
    sigaction(SIGIO, &action, NULL);

    
    fcntl(fd, F_SETOWN, getpid()); // set this process as owner of file
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | FASYNC); // enable async notification
}

void readDriver(int signo)
{
    if (signo == SIGIO) {
        read(fd, &data, 1);
    }
}

char readGamepad(void)
{
    return data;
}
