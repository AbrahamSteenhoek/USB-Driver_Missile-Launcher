#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/mman.h>


#define LAUNCHER_NODE           "/dev/launcher0"
#define LAUNCHER_FIRE           0x10
#define LAUNCHER_STOP           0x20
#define LAUNCHER_UP             0x02
#define LAUNCHER_DOWN           0x01
#define LAUNCHER_LEFT           0x04
#define LAUNCHER_RIGHT          0x08
#define LAUNCHER_UP_LEFT        (LAUNCHER_UP | LAUNCHER_LEFT)
#define LAUNCHER_DOWN_LEFT      (LAUNCHER_DOWN | LAUNCHER_LEFT)
#define LAUNCHER_UP_RIGHT       (LAUNCHER_UP | LAUNCHER_RIGHT)
#define LAUNCHER_DOWN_RIGHT     (LAUNCHER_DOWN | LAUNCHER_RIGHT)

#define LAUNCHER_KBD_UP         'w'
#define LAUNCHER_KBD_DOWN       's'
#define LAUNCHER_KBD_LEFT       'a'
#define LAUNCHER_KBD_RIGHT      'd'
#define EXIT_PROGRAM            'q'
#define LAUNCHER_KBD_FIRE       ' '
#define LAUNCHER_KBD_STOP       'e'

static void launcher_cmd(int fd, int cmd);
