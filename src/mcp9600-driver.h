#ifndef _MCP9600_DRIVER_H_
#define _MCP9600_DRIVER_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum mcp9600_registers {
	MCP9600_REG_TH = 0x00,
	MCP9600_REG_TD = 0x01,
	MCP9600_REG_TC = 0x02,

	MCP9600_REG_RAW = 0x03,
	MCP9600_REG_STATUS = 0x04,
	MCP9600_REG_TCONF = 0x05,
	MCP9600_REG_DCONF = 0x06,

	MCP9600_REG_ALERT1 = 0x08,
	MCP9600_REG_ALERT2 = 0x09,
	MCP9600_REG_ALERT3 = 0x0a,
	MCP9600_REG_ALERT4 = 0x0b,

	MCP9600_REG_T_HYST1 = 0x0c,
	MCP9600_REG_T_HYST2 = 0x0d,
	MCP9600_REG_T_HYST3 = 0x0e,
	MCP9600_REG_T_HYST4 = 0x0f,

	MCP9600_REG_T_ALERT1 = 0x10,
	MCP9600_REG_T_ALERT2 = 0x11,
	MCP9600_REG_T_ALERT3 = 0x12,
	MCP9600_REG_T_ALERT4 = 0x13,
	MCP9600_REG_DEV_ID = 0x20
} mcp9600_registers_t;

typedef enum mcp9600_thermocouple {
	TYPE_K = 0x00,
	TYPE_J = 0x01,
	TYPE_T = 0x02,
	TYPE_N = 0x03,
	TYPE_S = 0x04,
	TYPE_E = 0x05,
	TYPE_B = 0x06,
	TYPE_R = 0x07,
} mcp9600_thermocouple_t;

typedef enum mcp9600_resolution {
	RES_18 = 0x00,
	RES_16 = 0x01,
	RES_14 = 0x02,
	RES_12 = 0x03,
} mcp9600_resolution_t;

typedef enum mcp9600_filter_coefficients {
	FILTER_OFF = 0x00,
	FILTER_1 = 0x01,
	FILTER_2 = 0x02,
	FILTER_3 = 0x03,
	FILTER_4 = 0x04,
	FILTER_5 = 0x05,
	FILTER_6 = 0x06,
	FILTER_7 = 0x07,
} mcp9600_filter_t;

typedef struct mcp9600_handle {
	uint8_t i2c_addr;
	char *adapter;
	mcp9600_thermocouple_t tc_type;
	mcp9600_resolution_t resolution;
	mcp9600_filter_t filter;

	uint8_t (*i2c_init)(char *name, uint8_t i2c_addr);
	uint8_t (*i2c_deinit)();
	uint8_t (*i2c_write_reg)(uint8_t reg, uint8_t data);
	uint8_t (*i2c_read_reg)(uint8_t reg, uint8_t *data);
	uint8_t (*i2c_read_word)(uint8_t reg, uint16_t *data);

} mcp9600_handle_t;

uint8_t mcp9600_init(mcp9600_handle_t *handle);
uint8_t mcp9600_deinit(mcp9600_handle_t *handle);

uint8_t mcp9600_read_temp(mcp9600_handle_t *handle, mcp9600_registers_t reg, float *data);

uint8_t mcp9600_get_status_burst_complete(mcp9600_handle_t *handle, uint8_t *data);
uint8_t mcp9600_get_status_th_update(mcp9600_handle_t *handle, uint8_t *data);
uint8_t mcp9600_get_status_sc(mcp9600_handle_t *handle, uint8_t *data);
uint8_t mcp9600_get_status_input_range(mcp9600_handle_t *handle, uint8_t *data);
uint8_t mcp9600_get_status_alert_status(mcp9600_handle_t *handle, uint8_t *data);

uint8_t mcp9600_set_thermocouple_type(mcp9600_handle_t *handle, mcp9600_thermocouple_t type);

uint8_t mcp9600_set_resolution(mcp9600_handle_t *handle, mcp9600_resolution_t resolution);
uint8_t mcp9600_get_resolution(mcp9600_handle_t *handle, mcp9600_resolution_t *resolution);

uint8_t mcp9600_set_filter_coefficients(mcp9600_handle_t *handle, mcp9600_filter_t filter);
uint8_t mcp9600_get_filter_coefficients(mcp9600_handle_t *handle, mcp9600_filter_t *filter);

uint8_t mcp9600_get_device_id(mcp9600_handle_t *handle, uint8_t *id);

#ifdef __cplusplus
}
#endif

#endif
