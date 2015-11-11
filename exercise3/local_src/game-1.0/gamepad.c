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

void setupGamepad()
{
    struct sigaction action;
    
    fd = open("/dev/gamepad", O_RDWR);
    
    memset(&action, 0, sizeof(action));
    action.sa_handler = readDriver;
    action.sa_flags = 0;

    sigaction(SIGIO, &action, NULL);

    fcntl(fd, F_SETOWN, getpid());
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | FASYNC);
}

void readDriver(int signo)
{
    printf("signal handler running\n");
    if (signo == SIGIO) {
	read(fd, &data, 1);
    }
}

char readGamepad()
{
    return data;
}
