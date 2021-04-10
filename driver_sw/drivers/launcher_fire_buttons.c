#include "launcher_fire_buttons.h"

static void launcher_cmd(int fd, int cmd) {
  int retval = 0;
  
  retval = write(fd, &cmd, 1);
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

  int dev_fd = open("/dev/mem", O_RDONLY );
  // TODO: error checking for mmap()
  btn_ptr = mmap(
    NULL, // let kernel pick which virtual address to use
    GPIO_DATA_SIZE, // data regs from GPIO are 1 byte
    PROT_READ, // read-only
    MAP_SHARED,
    dev_fd,
    GPIO_BTN_ADDR
  );
  sw_ptr = mmap(
    NULL, // let kernel pick which virtual address to use
    GPIO_DATA_SIZE, // data regs from GPIO are 1 byte
    PROT_READ, // read-only
    MAP_SHARED,
    dev_fd,
    GPIO_BTN_ADDR
  );

  // cmd = LAUNCHER_FIRE;
  
  fd = open(dev, O_RDWR);
  if (fd == -1) {
    perror("Couldn't open file: %m");
    exit(1);
  }

  while( !exit_condition )
  {
    exit_condition = ( (*sw_ptr) & SW[0] );
    if ( *btn_ptr & BTN_RIGHT )
    {
      cmd |= LAUNCHER_RIGHT;
    }
    if ( *btn_ptr & BTN_LEFT )
    {
      cmd |= LAUNCHER_LEFT;
    }
    if ( *btn_ptr & BTN_UP )
    {
      cmd |= LAUNCHER_UP;
    }
    if ( *btn_ptr & BTN_DOWN )
    {
      cmd |= LAUNCHER_DOWN;
    }

    if ( *btn_ptr & BTN_CENTER ) // need to hold fire button
    {
      cmd |= LAUNCHER_FIRE;
    }

    cmd = ( *btn_ptr == 0x0 ) ? LAUNCHER_STOP : cmd; // stop if not pressing anything

    launcher_cmd( fd, cmd );

    usleep(10000);
  }
  
  launcher_cmd(fd, LAUNCHER_STOP);
  close(fd);
  return EXIT_SUCCESS;
}


