#include "launcher_fire_keyboard.h"

static void launcher_cmd(int fd, int cmd) {
  int retval = 0;
  // fprintf(stdout, "Running launcher_cmd()\n");
  
  // fprintf(stdout, "writing command to launcher\n");
  retval = write(fd, &cmd, 1);
  // fprintf(stdout, "wrote command to launcher\n");
  while (retval != 1) {
    if (retval < 0) {
      fprintf(stderr, "Could not send command to %s (error %d)\n", LAUNCHER_NODE, retval);
    } 

    else if (retval == 0) {
      fprintf(stdout, "Command busy, waiting...\n");
    }
  }


  if (cmd == LAUNCHER_FIRE) {
    usleep(5000000);
  }
}

int main() {
  char c;
  int fd;
  int cmd = LAUNCHER_STOP;
  char *dev = LAUNCHER_NODE;
  unsigned int duration = 500;
  bool exit_condition = false;

  fd = open(dev, O_RDWR);
  if (fd == -1) {
    perror("Couldn't open file: %m");
    exit(1);
  }
  fprintf(stdout, "USB Missile Launcher Control Program\n");

  while( !exit_condition )
  {
    unsigned char kbd_cmd = getchar();
    getchar();

    switch ( kbd_cmd )
    {
      case LAUNCHER_KBD_UP:
        fprintf(stdout, "UP\n");
        cmd = LAUNCHER_UP;
        break;
      case LAUNCHER_KBD_DOWN:
        fprintf(stdout, "DOWN\n");
        cmd = LAUNCHER_DOWN;
        break;
      case LAUNCHER_KBD_RIGHT:
        fprintf(stdout, "RIGHT\n");
        cmd = LAUNCHER_RIGHT;
        break;
      case LAUNCHER_KBD_LEFT:
        fprintf(stdout, "LEFT\n");
        cmd = LAUNCHER_LEFT;
        break;
      case LAUNCHER_KBD_FIRE:
        fprintf(stdout, "FIRE\n");
        cmd = LAUNCHER_FIRE;
        break;
      case EXIT_PROGRAM:
        fprintf(stdout, "Exiting...\n");
        cmd = LAUNCHER_STOP;
        exit_condition = true;
        break;
      case LAUNCHER_KBD_STOP:
      default:
        fprintf(stdout, "STOP\n");
        cmd = LAUNCHER_STOP;
        break;
    }

    launcher_cmd( fd, cmd );

    usleep(100000);
  }
  
  launcher_cmd(fd, LAUNCHER_STOP);
  close(fd);
  return EXIT_SUCCESS;
}


