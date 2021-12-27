#ifndef _I2C_H
#define _I2C_H

#include <stdint.h>

uint8_t i2c_init(char *name, int *fd, uint8_t i2c_addr);
uint8_t i2c_deinit(int fd);
uint8_t i2c_read_reg(int fd, uint8_t reg, uint8_t *data);
uint8_t i2c_write_reg(int fd, uint8_t reg, uint8_t data);
int16_t i2c_read(int fd, uint8_t *data);
uint8_t i2c_write(int fd, uint8_t data);
uint8_t i2c_read_word(int fd, uint8_t reg, uint16_t *data);

#endif //_I2C_H
