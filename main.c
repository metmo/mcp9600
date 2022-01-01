#include "mcp9600-driver.h"
#include "mcp9600-interface.h"
#include <stdio.h>
#include <stdlib.h>

static void help(char *path)
{
	printf("Usage: %s [i2c-bus] [i2c-addr]\n", path);
}

int main(int argc, char **argv)
{
	char adapter[19];
	int i2c_address;

	if (argc == 3) {
		int adapter_nr = (int)strtol(argv[1], NULL, 10);
		snprintf(adapter, 19, "/dev/i2c-%d", adapter_nr);
		i2c_address = (int)strtol(argv[2], NULL, 16);

		printf("adapter: %s addr: %d\n", adapter, i2c_address);

	} else {
		help(argv[0]);
		exit(EXIT_FAILURE);
	}

	mcp9600_handle_t handle = {
		.i2c_init = i2c_init,
		.i2c_deinit = i2c_deinit,
		.i2c_read_reg = i2c_read_reg,
		.i2c_write_reg = i2c_write_reg,
		.i2c_read_word = i2c_read_word,
		.i2c_addr = i2c_address,
		.adapter = adapter,
		.tc_type = TYPE_K,
		.resolution = RES_12,
		.filter = FILTER_OFF,
	};

	int err = mcp9600_init(&handle);
	if (err != 0)
		exit(EXIT_FAILURE);

	uint8_t id;
	mcp9600_get_device_id(&handle, &id);

	float f_data = 0.0f;
	mcp9600_read_temp(&handle, MCP9600_REG_TH, &f_data);

	printf("Set resolution: %d\n", RES_12);
	mcp9600_set_resolution(&handle, RES_12);

	mcp9600_resolution_t resolution;
	mcp9600_get_resolution(&handle, &resolution);
	printf("Get resolution: %d\n", resolution);

	printf("Set resolution: %d\n", RES_14);
	mcp9600_set_resolution(&handle, RES_14);

	mcp9600_get_resolution(&handle, &resolution);
	printf("Get resolution: %d\n", resolution);

	printf("DeviceId: 0x%x\n", id);
	printf("Temp: %f\n", f_data);

	err = mcp9600_deinit(&handle);
	if (err != 0)
		exit(EXIT_FAILURE);

	return (EXIT_SUCCESS);
}
