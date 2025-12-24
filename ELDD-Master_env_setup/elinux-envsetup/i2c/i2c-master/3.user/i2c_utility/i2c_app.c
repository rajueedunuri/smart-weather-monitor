#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <i2c/smbus.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int file;
int adapter_nr = 1;
char filename[20];
int slave_addr = 0x68;
__u8 row;
__u8 register_add;
__s32 length;
__s32 res;
__u8 buf[130];
int i;
unsigned long funcs;

int main(int argc, char *argv[])
{	
	if (argc < 4) {
		printf("Please enter the right number of arguments\n");
		exit(1);
	}
	register_add = atoi(argv[2]);
	if (register_add < 0 || register_add > 255) {
		printf("Register value must be 8 bit\n");
		exit(1);
	}
	length = atoi(argv[3]);
	if (length < 0) {
		printf("Please supply a valid value for length\n");
		exit(1);
	}
	row = argv[1][0];
	switch (row) {
		case 'r':
		case 'R':
			row = 0;
			break;
		case 'w':
		case 'W':
			if (argc != (4 + length)) {
				printf("Please supply the bytes to be written to the device\n");
				exit(1);
			}
			for(i = 0; i<length; i++) {
				buf[i] = atoi(argv[4+i]);
			}
			row = 1;
			break;
		default:
			printf("Please supply a valid value for read or write\n");	
			exit(1);
	}
	snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
	file = open(filename, O_RDWR);
	if (file < 0) {
		printf("Sorry, could not open file /dev/i2c-%d\n", adapter_nr);
		exit(1);
	}
	if (ioctl(file, I2C_FUNCS, &funcs) < 0) {
		printf("Sorry could not find the supported list of functions\n");
		exit(1);
	}
	if (ioctl(file, I2C_SLAVE, slave_addr) < 0) {
		printf("Sorry, could not set the slave address\n");
		exit(1);
	}
	switch (row) {
		case 0:
			switch (length) {
				case 1:
					if (!(funcs & I2C_FUNC_SMBUS_READ_BYTE_DATA)) {
						printf("SMBus read byte data not supported\n");
						exit(1);
					}
					res = i2c_smbus_read_byte_data(file, register_add);
					if (res < 0) {
						printf("Read error\n");
						exit(1);
					}
			printf("The value read from the register is Dec:%d Hex:%x\n", res,res);
					break;
				case 2:
					if (!(funcs & I2C_FUNC_SMBUS_READ_WORD_DATA)) {
						printf("SMBus read word data not supported\n");
						exit(1);
					}
					res = i2c_smbus_read_word_data(file, register_add);
					if (res < 0) {
						printf("Read error\n");	
						exit(1);
					}
			printf("The value read from the register is %d\n", res);
					break;
				case 4:
					if (!(funcs & I2C_FUNC_SMBUS_READ_BLOCK_DATA)) {
						printf("SMBus read block data not supported\n");
						exit(1);
					}
					res = i2c_smbus_read_block_data(file, register_add, buf);
					if (res < 0) {
						printf("Read error\n");
						exit(1);
					}
					printf("The bytes read from the register is %c %c %c %c\n", buf[1], buf[2], buf[3], buf[4]);
					break;
	
				default:
					break;
			}
			break;

		case 1:
			switch (length) {
				case 1:
					if (!(funcs & I2C_FUNC_SMBUS_WRITE_BYTE_DATA)) {
						printf("SMBus write byte data not supported\n");
						exit(1);
					}
					res = i2c_smbus_write_byte_data(file, register_add, buf[0]);
					if (res < 0) {
						printf("Read error\n");
						exit(1);
					}
					break;
				case 2:
					if (!(funcs & I2C_FUNC_SMBUS_WRITE_WORD_DATA)) {
						printf("SMBus write byte data not supported\n");
						exit(1);
					}
					__u16 temp = *((__u16 *)(&buf[0]));
					res = i2c_smbus_write_word_data(file, register_add, temp);
					if (res < 0) {
						printf("Read error\n");	
						exit(1);
					}
					break;
				case 4:
					if (!(funcs & I2C_FUNC_SMBUS_WRITE_BLOCK_DATA)) {
						printf("SMBus write block data not supported\n");
						exit(1);
					}
					res = i2c_smbus_write_block_data(file, register_add, length, buf);
					if (res < 0) {
						printf("Read error\n");
						exit(1);
					}
					break;
				default:
					break;
			}
			break;
		default:
			printf("Please specify a valid type of operation (Either read or write) \n");
			exit(1);
	}
	return 0;
}
