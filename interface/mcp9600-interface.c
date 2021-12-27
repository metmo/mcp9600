#include "i2c.h"

uint8_t if_i2c_init(char *name, int *fd, uint8_t i2c_addr)
{
	return i2c_init(name, fd, i2c_addr);
}

uint8_t if_i2c_deinit(int fd)
{
	return i2c_deinit(fd);
}

uint8_t if_i2c_read_reg(int fd, uint8_t reg, uint8_t *data)
{
	return i2c_read_reg(fd, reg, data);
}

uint8_t if_i2c_write_reg(int fd, uint8_t reg, uint8_t data)
{
	return i2c_write_reg(fd, reg, data);
}

int16_t if_i2c_read(int fd, uint8_t *data)
{
	return i2c_read(fd, data);
}

uint8_t if_i2c_write(int fd, uint8_t data)
{
	return i2c_write(fd, data);
}

uint8_t if_i2c_read_word(int fd, uint8_t reg, uint16_t *data)
{
	return i2c_read_word(fd, reg, data);
}
