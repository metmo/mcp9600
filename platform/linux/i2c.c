#include <fcntl.h>
#include <i2c/smbus.h>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "i2c.h"

static int fd;

uint8_t i2c_init(char *name, uint8_t i2c_addr)
{
	fd = open(name, O_RDWR);

	if (fd < 0) {
		perror("i2c_init() open");
		return 1;
	}

	if (ioctl(fd, I2C_SLAVE, i2c_addr) < 0) {
		perror("i2c_init() ioctl");
		return 1;
	}
	return 0;
}

uint8_t i2c_deinit()
{
	if (close(fd) < 0) {
		perror("i2c_deinit() close");
		return 1;
	}
	return 0;
}

uint8_t i2c_read_reg(uint8_t reg, uint8_t *data)
{
	int32_t result = i2c_smbus_read_byte_data(fd, reg);

	if (result < 0) {
		printf("i2c_read_reg() fail: %s\n", strerror(-result));
		return 1;
	}

	*data = result;

	return 0;
}

uint8_t i2c_write_reg(uint8_t reg, uint8_t data)
{
	int32_t result = i2c_smbus_write_byte_data(fd, reg, data);

	if (result < 0) {
		printf("i2c_write_reg() fail: %s\n", strerror(-result));
		return 1;
	}

	return 0;
}

int16_t i2c_read(uint8_t *data)
{
	int32_t result = i2c_smbus_read_byte(fd);

	if (result < 0) {
		printf("i2c_read() fail: %s\n", strerror(-result));
		return 1;
	}

	*data = result;

	return 0;
}

uint8_t i2c_write(uint8_t data)
{
	int32_t result = i2c_smbus_write_byte(fd, data);

	if (result < 0) {
		printf("i2c_write() fail: %s\n", strerror(-result));
		return 1;
	}

	return 0;
}

uint8_t i2c_read_word(uint8_t reg, uint16_t *data)
{
	int32_t result = i2c_smbus_read_word_data(fd, reg);

	if (result < 0) {
		printf("i2c_read_word() fail: %s\n", strerror(-result));
		return 1;
	}

	*data = result;

	return 0;
}
