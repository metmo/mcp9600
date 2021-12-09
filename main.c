#include "src/mcp9600-driver.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  mcp9600_handle_t handle;

  int err = mcp9600_init(&handle, "/dev/i2c-22", 0x67, TYPE_K, RES_12);
  if (err != 0) {
    exit(EXIT_FAILURE);
  }

  uint16_t temp;
  mcp9600_read_hot(&handle, &temp);

  float f_data;
  mcp9600_read_temp(&handle, HOT, &f_data);

  printf("Temp: %x\n", temp);
  printf("Temp: %f\n", f_data);


  err = mcp9600_deinit(&handle);
  if (err != 0) {
    exit(EXIT_FAILURE);
  }

  return (EXIT_SUCCESS);
}
