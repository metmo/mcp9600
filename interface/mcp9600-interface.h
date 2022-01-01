#ifndef _MCP9600_INTERFACE_H_
#define _MCP9600_INTERFACE_H_

uint8_t i2c_init(char *name, uint8_t i2c_addr);
uint8_t i2c_deinit();
uint8_t i2c_read_reg(uint8_t reg, uint8_t *data);
uint8_t i2c_write_reg(uint8_t reg, uint8_t data);
int16_t i2c_read(uint8_t *data);
uint8_t i2c_write(uint8_t data);
uint8_t i2c_read_word(uint8_t reg, uint16_t *data);

#endif //_MCP9600_INTERFACE_H_
