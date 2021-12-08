#include "mcp9600-driver.h"
#include "linux/i2c-dev.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static uint8_t i2c_init(char *name, int *fd, uint8_t i2c_addr) {
  *fd = open(name, O_RDWR);

  if (*fd < 0) {
    perror("i2c open");
    return 1;
  }

  if (ioctl(*fd, I2C_SLAVE, i2c_addr) < 0) {
    perror("ioctl");
    return 1;
  }
  return 0;
}

static uint8_t i2c_deinit(int fd) {
  if (close(fd) < 0) {
    perror("i2c close");
    return 1;
  }
  return 0;
}

static uint8_t i2c_read_reg(int fd, uint8_t reg) {
  uint8_t result = i2c_smbus_read_byte_data(fd, reg);
  return result;
}

static uint8_t i2c_write_reg(int fd, uint8_t reg, uint8_t data) {
  uint8_t result = i2c_smbus_write_byte_data(fd, reg, data);
  return result;
}

static uint8_t i2c_read(int fd) {
  uint8_t result = i2c_smbus_read_byte(fd);
  return result;
}

static uint8_t i2c_write(int fd, uint8_t data) {
  uint8_t result = i2c_smbus_write_byte(fd, data);
  return result;
}

static uint16_t i2c_read_word(int fd, uint8_t reg) {
  uint16_t result = i2c_smbus_read_word_data(fd, reg);
  return result;
}

uint8_t mcp9600_init(mcp9600_handle_t *handle, char *device, uint8_t i2c_addr,
                     mcp9600_thermocouple_t tc_type,
                     mcp9600_resolution_t resolution) {
  int fd = 0;
  int err = i2c_init(device, &fd, i2c_addr);

  if (err != 0) {
    return 1;
  }

  handle->fd = fd;
  handle->i2c_addr = i2c_addr;
  handle->resolution = resolution;
  handle->tc_type = tc_type;

  return 0;
}

uint8_t mcp9600_deinit(mcp9600_handle_t *handle) {
  return i2c_deinit(handle->fd);
}

uint8_t mcp9600_read_hot(mcp9600_handle_t *handle, uint16_t *data) {
  *data = i2c_read_word(handle->fd, 0x00);
  return 0;
}

uint8_t mcp9600_read_cold(mcp9600_handle_t *handle, uint16_t *data) {
  return 0;
}
uint8_t mcp9600_read_delta(mcp9600_handle_t *handle, uint16_t *data) {
  return 0;
}
