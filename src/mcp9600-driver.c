#include "mcp9600-driver.h"

#define MCP9600_STATUS_REG_BIT_BURSTCLPT (1 << 7)
#define MCP9600_STATUS_REG_BIT_THUPDATE (1 << 6)
#define MCP9600_STATUS_REG_BIT_SC (1 << 5)
#define MCP9600_STATUS_REG_BIT_INPUTRANGE (1 << 4)
#define MCP9600_STATUS_REG_BIT_ALERT4_STATUS (1 << 3)
#define MCP9600_STATUS_REG_BIT_ALERT3_STATUS (1 << 2)
#define MCP9600_STATUS_REG_BIT_ALERT2_STATUS (1 << 1)
#define MCP9600_STATUS_REG_BIT_ALERT1_STATUS (1 << 0)

#define MCP9600_STATUS_REG_BIT_ALERT1_4_STATUS (4 << 0)

#define MCP9600_TCONF_REG_BIT_TCTYPE (3 << 3)
#define MCP9600_TCONF_REG_BIT_FILTER (3 << 0)

#define MCP9600_CONFIG_REG_BIT_CJ_RES (1 << 7)
#define MCP9600_CONFIG_REG_BIT_ADC_RES (3 << 5)
#define MCP9600_CONFIG_REG_BIT_BURST_SAMPLES (3 << 2)
#define MCP9600_CONFIG_REG_BIT_SHUTDOWN_MODES (2 << 0);

#define MCP9600_ALERT_REG_BIT_INTCLEAR (1 << 7)
#define MCP9600_ALERT_REG_BIT_MONITOR (1 << 4)
#define MCP9600_ALERT_REG_BIT_DETECT (1 << 3)
#define MCP9600_ALERT_REG_BIT_ACTIVE (1 << 2)
#define MCP9600_ALERT_REG_BIT_COMPMODE (1 << 1)
#define MCP9600_ALERT_REG_BIT_ENABLE (1 << 0)

uint8_t mcp9600_init(mcp9600_handle_t *handle)
{
	int err = handle->i2c_init(handle->adapter, handle->i2c_addr);

	if (err != 0) {
		return 1;
	}

	mcp9600_set_thermocouple_type(handle, handle->tc_type);
	mcp9600_set_filter_coefficients(handle, handle->filter);

	return 0;
}

uint8_t mcp9600_deinit(mcp9600_handle_t *handle)
{
	return handle->i2c_deinit();
}

uint8_t mcp9600_read_temp(mcp9600_handle_t *handle, mcp9600_register_t reg, float *data)
{
	uint16_t raw_temp = 0;
	uint8_t res = handle->i2c_read_word(reg, &raw_temp);

	*data = ((raw_temp & 0xff) * 16.0f) + ((raw_temp >> 8) / 16.0f);
	return res;
}

uint8_t mcp9600_get_status_burst_complete(mcp9600_handle_t *handle, uint8_t *data)
{
	uint8_t raw_data = 0;

	uint8_t res = handle->i2c_read_reg(MCP9600_REG_STATUS, &raw_data);

	*data = (raw_data & MCP9600_STATUS_REG_BIT_BURSTCLPT) >> 7;
	return res;
}

uint8_t mcp9600_get_status_th_update(mcp9600_handle_t *handle, uint8_t *data)
{
	uint8_t raw_data = 0;
	uint8_t res = handle->i2c_read_reg(MCP9600_REG_STATUS, &raw_data);

	*data = (raw_data & MCP9600_STATUS_REG_BIT_THUPDATE) >> 6;
	return res;
}

uint8_t mcp9600_get_status_sc(mcp9600_handle_t *handle, uint8_t *data)
{
	uint8_t raw_data = 0;
	uint8_t res = handle->i2c_read_reg(MCP9600_REG_STATUS, &raw_data);

	*data = (raw_data & MCP9600_STATUS_REG_BIT_SC) >> 5;
	return res;
}

uint8_t mcp9600_get_status_input_range(mcp9600_handle_t *handle, uint8_t *data)
{
	uint8_t raw_data = 0;
	uint8_t res = handle->i2c_read_reg(MCP9600_REG_STATUS, &raw_data);

	*data = (raw_data & MCP9600_STATUS_REG_BIT_INPUTRANGE) >> 4;
	return res;
}

uint8_t mcp9600_get_status_alert_status(mcp9600_handle_t *handle, uint8_t *data)
{
	uint8_t raw_data = 0;
	uint8_t res = handle->i2c_read_reg(MCP9600_REG_STATUS, &raw_data);

	*data = res & MCP9600_STATUS_REG_BIT_ALERT1_4_STATUS;

	return res;
}

uint8_t mcp9600_set_thermocouple_type(mcp9600_handle_t *handle, mcp9600_thermocouple_t type)
{
	uint8_t tc_type = (uint8_t)type << 3;
	uint8_t res = handle->i2c_write_reg(MCP9600_REG_TCONF, tc_type);

	return res;
}

uint8_t mcp9600_set_filter_coefficients(mcp9600_handle_t *handle, mcp9600_filter_t filter)
{
	uint8_t reg;
	handle->i2c_read_reg(MCP9600_REG_TCONF, &reg);

	reg |= (filter & 0x07);

	uint8_t res = handle->i2c_write_reg(MCP9600_REG_TCONF, filter);

	return res;
}

uint8_t mcp9600_get_filter_coefficients(mcp9600_handle_t *handle, mcp9600_filter_t *filter)
{
	uint8_t raw_data = 0;
	uint8_t res = handle->i2c_read_reg(MCP9600_REG_TCONF, &raw_data);

	*filter = raw_data & 0x07;

	return res;
}

uint8_t mcp9600_set_resolution(mcp9600_handle_t *handle, mcp9600_resolution_t resolution)
{
	uint8_t reg;
	handle->i2c_read_reg(MCP9600_REG_DCONF, &reg);

	reg = (reg & ~MCP9600_CONFIG_REG_BIT_ADC_RES) | (resolution << 5);

	int res = handle->i2c_write_reg(MCP9600_REG_DCONF, reg);

	return res;
}

uint8_t mcp9600_get_resolution(mcp9600_handle_t *handle, mcp9600_resolution_t *resolution)
{
	uint8_t reg;
	int res = handle->i2c_read_reg(MCP9600_REG_DCONF, &reg);
	*resolution = (reg & MCP9600_CONFIG_REG_BIT_ADC_RES) >> 5;

	return res;
}

uint8_t mcp9600_get_device_id(mcp9600_handle_t *handle, uint8_t *id)
{
	uint8_t raw_data = 0;
	uint8_t res = handle->i2c_read_reg(MCP9600_REG_DEV_ID, &raw_data);

	*id = raw_data;

	return res;
}
