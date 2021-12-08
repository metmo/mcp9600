// Based on https://www.kernel.org/doc/Documentation/i2c/dev-interface

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
    perror("i2c: Open failed.\n");
    return 1;
  }

  if (ioctl(*fd, I2C_SLAVE, i2c_addr) < 0) {
    printf("Oh dear, something went wrong with ioctl()! %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  return 0;
}

static uint8_t i2c_deinit(int fd) {
  if (close(fd) < 0) {
    perror("i2c: Close failed.\n");
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

uint8_t mcp9600_init(mcp9600_handle_t *handle, uint8_t i2c_addr,
                     mcp9600_thermocouple_t tc_type,
                     mcp9600_resolution_t resolution) {
  int fd = 0;
  i2c_init("/dev/i2c-22", &fd, 0x67);

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

int main() {

  mcp9600_handle_t handle;

  mcp9600_init(&handle, 0x67, TYPE_K, RES_12);

  uint16_t temp;
  mcp9600_read_hot(&handle, &temp);

  printf("Temp: %x\n", temp);

  mcp9600_deinit(&handle);

  return (EXIT_SUCCESS);
}
