#include "mcp9600-driver.h"
#include <linux/i2c-dev.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static uint8_t i2c_init(char *name, int *fd, uint8_t i2c_addr) {
  *fd = open(name, O_RDWR);

  if (*fd < 0) {
    perror("i2c_init() open");
    return 1;
  }

  if (ioctl(*fd, I2C_SLAVE, i2c_addr) < 0) {
    perror("i2c_init() ioctl");
    return 1;
  }
  return 0;
}

static uint8_t i2c_deinit(int fd) {
  if (close(fd) < 0) {
    perror("i2c_deinit() close");
    return 1;
  }
  return 0;
}

static uint8_t i2c_read_reg(int fd, uint8_t reg, uint8_t *data) {
  int16_t result = i2c_smbus_read_byte_data(fd, reg);

  if (result < 0) {
    printf("i2c_read_reg() fail: %s\n", strerror(result));
    return 1;
  }

  *data = result;

  return 0;
}

static uint8_t i2c_write_reg(int fd, uint8_t reg, uint8_t data) {
  int16_t result = i2c_smbus_write_byte_data(fd, reg, data);

  if (result < 0) {
    printf("i2c_write_reg() fail: %s\n", strerror(result));
    return 1;
  }

  return 0;
}

static int16_t i2c_read(int fd, uint8_t *data) {
  int16_t result = i2c_smbus_read_byte(fd);

  if (result < 0) {
    printf("i2c_read() fail: %s\n", strerror(result));
    return 1;
  }

  *data = result;

  return 0;
}

static uint8_t i2c_write(int fd, uint8_t data) {
  int16_t result = i2c_smbus_write_byte(fd, data);

  if (result < 0) {
    printf("i2c_write() fail: %s\n", strerror(result));
    return 1;
  }

  return 0;
}

static uint8_t i2c_read_word(int fd, uint8_t reg, uint16_t *data) {
  int16_t result = i2c_smbus_read_word_data(fd, reg);

  if (result < 0) {
    printf("i2c_read_word() fail: %s\n", strerror(result));
    return 1;
  }

  *data = result;

  return 0;
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

  mcp9600_set_thermocouple_type(handle, tc_type);

  return 0;
}

uint8_t mcp9600_deinit(mcp9600_handle_t *handle) {
  return i2c_deinit(handle->fd);
}

uint8_t mcp9600_read_temp(mcp9600_handle_t *handle,
                          mcp9600_thermocouple_reg_t reg, float *data) {
  uint16_t raw_temp;
  uint8_t res = i2c_read_word(handle->fd, reg, &raw_temp);

  *data = ((raw_temp & 0xff) * 16.0f) + ((raw_temp >> 8) / 16.0f);
  return res;
}

uint8_t mcp9600_read_hot(mcp9600_handle_t *handle, uint16_t *data) {
  uint8_t res = i2c_read_word(handle->fd, MCP9600_REG_TH, data);
  return res;
}

uint8_t mcp9600_read_cold(mcp9600_handle_t *handle, uint16_t *data) {
  uint8_t res = i2c_read_word(handle->fd, MCP9600_REG_TC, data);
  return res;
}
uint8_t mcp9600_read_delta(mcp9600_handle_t *handle, uint16_t *data) {
  uint8_t res = i2c_read_word(handle->fd, MCP9600_REG_TD, data);
  return res;
}

uint8_t mcp9600_get_status_burst_complete(mcp9600_handle_t *handle,
                                          uint8_t *data) {

  uint8_t raw_data;

  uint8_t res = i2c_read_reg(handle->fd, MCP9600_REG_STATUS, &raw_data);

  *data = raw_data & MCP9600_STATUS_REG_BIT_BURSTCLPT;
  return res;
}

uint8_t mcp9600_get_status_th_update(mcp9600_handle_t *handle, uint8_t *data) {

  uint8_t raw_data;
  uint8_t res = i2c_read_reg(handle->fd, MCP9600_REG_STATUS, &raw_data);

  *data = raw_data & MCP9600_STATUS_REG_BIT_THUPDATE;
  return res;
}

uint8_t mcp9600_get_status_sc(mcp9600_handle_t *handle, uint8_t *data) {
  uint8_t raw_data;
  uint8_t res = i2c_read_reg(handle->fd, MCP9600_REG_STATUS, &raw_data);

  *data = raw_data & MCP9600_STATUS_REG_BIT_SC;
  return res;
}

uint8_t mcp9600_get_status_input_range(mcp9600_handle_t *handle,
                                       uint8_t *data) {

  uint8_t raw_data;
  uint8_t res = i2c_read_reg(handle->fd, MCP9600_REG_STATUS, &raw_data);

  *data = raw_data & MCP9600_STATUS_REG_BIT_INPUTRANGE;
  return res;
}

uint8_t mcp9600_get_status_alert_status(mcp9600_handle_t *handle,
                                        uint8_t *data) {
  uint8_t raw_data;
  uint8_t res = i2c_read_reg(handle->fd, MCP9600_REG_STATUS, &raw_data);

  *data = res & MCP9600_STATUS_REG_BIT_ALERT1_4_STATUS;

  return res;
}

uint8_t mcp9600_set_thermocouple_type(mcp9600_handle_t *handle,
                                      mcp9600_thermocouple_t type) {

  uint8_t tc_type = (uint8_t)type << 3;
  uint8_t res = i2c_write_reg(handle->fd, MCP9600_REG_TCONF, tc_type);

  return res;
}

uint8_t mcp9600_set_filter_coefficients(mcp9600_handle_t *handle,
                                        mcp9600_filter_coefficients_t filter) {

  uint8_t res = i2c_write_reg(handle->fd, MCP9600_REG_TCONF, filter);

  return res;
}

uint8_t mcp9600_get_filter_coefficients(mcp9600_handle_t *handle,
                                        mcp9600_filter_coefficients_t *filter) {
  uint8_t raw_data;
  uint8_t res = i2c_read_reg(handle->fd, MCP9600_REG_TCONF, &raw_data);

  *filter = raw_data & 0x07;

  return res;
}
