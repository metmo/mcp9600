#include "../src/mcp9600-driver.h"

int main(int argc, char **argv) {

    mcp9600_handle_t handle;

    mcp9600_thermocouple_t type = TYPE_K;
    mcp9600_resolution_t resolution = RES_12;
    mcp9600_filter_coefficients_t filter = FILTER_OFF;

    if (mcp9600_init(&handle, "/dev/i2c-22", 0x67, type, resolution) != 0)
        return 1;

    if (mcp9600_set_thermocouple_type(&handle, type) != 0)
        return 1;

    if (mcp9600_set_filter_coefficients(&handle, filter) != 0)
        return 1;

    return 0;
}
