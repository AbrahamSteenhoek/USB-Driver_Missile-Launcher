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

#define GPIO_BTN_ADDR 0x41210000
#define GPIO_SW_ADDR 0x41220000
#define GPIO_DATA_SIZE 0x1

#define BTN_CENTER 0x1
#define BTN_UP 0x10
#define BTN_DOWN 0x2
#define BTN_RIGHT 0x4
#define BTN_LEFT 0x8
const u_int8_t SW[8] = {1, 2, 4, 8, 16, 32, 64, 128};

u_int32_t* btn_ptr = NULL;
u_int32_t* sw_ptr = NULL;

// uint8_t btn_state = 0;
// uint8_t sw_state = 0;
// uint8_t led_state = 0;

static void launcher_cmd(int fd, int cmd);
