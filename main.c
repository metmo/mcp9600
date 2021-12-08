#include "src/mcp9600-driver.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  mcp9600_handle_t handle;

  mcp9600_init(&handle, 0x67, TYPE_K, RES_12);

  uint16_t temp;
  mcp9600_read_hot(&handle, &temp);

  printf("Temp: %x\n", temp);

  mcp9600_deinit(&handle);

  return (EXIT_SUCCESS);
}
