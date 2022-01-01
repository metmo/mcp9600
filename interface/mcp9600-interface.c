#include "i2c.h"

uint8_t if_i2c_init(char *name, uint8_t i2c_addr)
{
	return i2c_init(name, i2c_addr);
}

uint8_t if_i2c_deinit()
{
	return i2c_deinit();
}

uint8_t if_i2c_read_reg(uint8_t reg, uint8_t *data)
{
	return i2c_read_reg(reg, data);
}

uint8_t if_i2c_write_reg(uint8_t reg, uint8_t data)
{
	return i2c_write_reg(reg, data);
}

int16_t if_i2c_read(uint8_t *data)
{
	return i2c_read(data);
}

uint8_t if_i2c_write(uint8_t data)
{
	return i2c_write(data);
}

uint8_t if_i2c_read_word(uint8_t reg, uint16_t *data)
{
	return i2c_read_word(reg, data);
}
