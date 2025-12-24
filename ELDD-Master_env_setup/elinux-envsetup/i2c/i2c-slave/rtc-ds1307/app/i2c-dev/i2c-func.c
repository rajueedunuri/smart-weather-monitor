#include <stdio.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "i2c-dev.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


struct func
{
        long value;
        const char* name;
};

static const struct func all_func[] = {
        { .value = I2C_FUNC_I2C,
          .name = "I2C" },
        { .value = I2C_FUNC_SMBUS_QUICK,
          .name = "SMBus Quick Command" },
        { .value = I2C_FUNC_SMBUS_WRITE_BYTE,
          .name = "SMBus Send Byte" },
        { .value = I2C_FUNC_SMBUS_READ_BYTE,
          .name = "SMBus Receive Byte" },
        { .value = I2C_FUNC_SMBUS_WRITE_BYTE_DATA,
          .name = "SMBus Write Byte" },
        { .value = I2C_FUNC_SMBUS_READ_BYTE_DATA,
          .name = "SMBus Read Byte" },
        { .value = I2C_FUNC_SMBUS_WRITE_WORD_DATA,
          .name = "SMBus Write Word" },
        { .value = I2C_FUNC_SMBUS_READ_WORD_DATA,
          .name = "SMBus Read Word" },
        { .value = I2C_FUNC_SMBUS_PROC_CALL,
          .name = "SMBus Process Call" },
        { .value = I2C_FUNC_SMBUS_WRITE_BLOCK_DATA,
          .name = "SMBus Block Write" },
        { .value = I2C_FUNC_SMBUS_READ_BLOCK_DATA,
          .name = "SMBus Block Read" },
        { .value = I2C_FUNC_SMBUS_BLOCK_PROC_CALL,
          .name = "SMBus Block Process Call" },
        { .value = I2C_FUNC_SMBUS_PEC,
          .name = "SMBus PEC" },
        { .value = I2C_FUNC_SMBUS_WRITE_I2C_BLOCK,
          .name = "I2C Block Write" },
        { .value = I2C_FUNC_SMBUS_READ_I2C_BLOCK,
          .name = "I2C Block Read" },
        { .value = 0, .name = "" }
};


int main()
{
  int fd;
  int i;
  unsigned long funcs;

  fd = open("/dev/i2c-1", O_RDWR);
  if (fd < 0) {
	printf("open fails\n");
	/* Some kind of error handling */
	exit(1);
  }

  printf("fd:%d\n",fd);
  if (ioctl(fd, I2C_FUNCS, &funcs) < 0) {
	/* Some kind of error handling */
	printf("exit");
  	  exit(1);
  }

  for (i = 0; all_func[i].value; i++) {
        printf("%-32s %s\n", all_func[i].name,
        (funcs & all_func[i].value) ? "yes" : "no");
  }
  
	return 0;
}
