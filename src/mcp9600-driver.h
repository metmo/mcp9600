#ifndef _MCP9600_DRIVER_H_
#define _MCP9600_DRIVER_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define REG_TH 0x00
#define REG_TD 0x01
#define REG_TC 0x02

#define REG_RAW 0x03
#define REG_STATUS 0x04
#define REG_TCONF 0x05
#define REG_DCONF 0x06

#define REG_ALERT1 0x08
#define REG_ALERT2 0x09
#define REG_ALERT3 0x0a
#define REG_ALERT4 0x0b

#define REG_T_HYST1 0x0c
#define REG_T_HYST2 0x0d
#define REG_T_HYST3 0x0e
#define REG_T_HYST4 0x0f

#define REG_T_ALERT1 0x10
#define REG_T_ALERT2 0x11
#define REG_T_ALERT3 0x12
#define REG_T_ALERT4 0x13

#define REG_DEV_ID 0x20

#define STATUS_REG_BIT_BURSTCLPT (1 << 7)
#define STATUS_REG_BIT_THUPDATE (1 << 6)
#define STATUS_REG_BIT_SC (1 << 5)
#define STATUS_REG_BIT_INPUTRANGE (1 << 4)
#define STATUS_REG_BIT_ALERT4_STATUS (1 << 3)
#define STATUS_REG_BIT_ALERT3_STATUS (1 << 2)
#define STATUS_REG_BIT_ALERT2_STATUS (1 << 1)
#define STATUS_REG_BIT_ALERT1_STATUS (1 << 0)

#define TCONF_REG_BIT_TCTYPE (3 << 3)
#define TCONF_REG_BIT_FILTER (3 << 0)

#define CONFIG_REG_BIT_CJ_RES (1 << 7)
#define CONFIG_REG_BIT_ADC_RES (2 << 5)
#define CONFIG_REG_BIT_BURST_SAMPLES (3 << 2)
#define CONFIG_REG_BIT_SHUTDOWN_MODES (2 << 0);

#define ALERT_REG_BIT_INTCLEAR (1 << 7)
#define ALERT_REG_BIT_MONITOR (1 << 4)
#define ALERT_REG_BIT_DETECT (1 << 3)
#define ALERT_REG_BIT_ACTIVE (1 << 2)
#define ALERT_REG_BIT_COMPMODE (1 << 1)
#define ALERT_REG_BIT_ENABLE (1 << 0)

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

typedef struct mcp9600_handle {
  int fd;
  uint8_t i2c_addr;
  mcp9600_thermocouple_t tc_type;
  mcp9600_resolution_t resolution;
} mcp9600_handle_t;

uint8_t mcp9600_init(mcp9600_handle_t *handle, char *device, uint8_t i2c_addr,
                     mcp9600_thermocouple_t tc_type,
                     mcp9600_resolution_t resolution);
uint8_t mcp9600_deinit(mcp9600_handle_t *handle);

uint8_t mcp9600_read_hot(mcp9600_handle_t *handle, uint16_t *data);
uint8_t mcp9600_read_cold(mcp9600_handle_t *handle, uint16_t *data);
uint8_t mcp9600_read_delta(mcp9600_handle_t *handle, uint16_t *data);

#ifdef __cplusplus
}
#endif

#endif
