/**
 * @file    AGS10.h
 * @brief   AGS10 Gas Sensor library header
 * @author  emirsatlm
 */
#ifndef INC_AGS10_H_
#define INC_AGS10_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_i2c.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* DEFINES--------------------------------------------------------*/
#define AGS10_I2C_ADDR_DEFAULT   0x1A    /**< Default I2C address */
#define AGS10_I2C_WRITE          0x34    /**< Write instruction */
#define AGS10_I2C_READ           0x35    /**< Read instruction */

#define AGS10_TVOCSTAT_REG       0x00    /**< Status and TVOC reading */
#define AGS10_VERSION_REG        0x11    /**< Firmware version */
#define AGS10_GASRES_REG         0x20    /**< Raw gas resistance */
#define AGS10_SETADDR_REG        0x21    /**< Change I2C address */

/*------------------------------------------------------------*/
typedef struct
{
    I2C_HandleTypeDef *hi2c;    /**< I2C handle */
    uint8_t i2c_addr;           /**< I2C address */
} AGS10_HandleTypeDef;

/* Functions------------------------------------------------------------*/
uint8_t ags10_crc8(const uint8_t *data, int len);
bool ags10_init(AGS10_HandleTypeDef *sensor, I2C_HandleTypeDef *hi2c, uint8_t i2c_addr);
bool ags10_read_register(AGS10_HandleTypeDef *sensor, uint8_t reg, uint16_t delayms, uint32_t *value);
bool ags10_get_firmware_version(AGS10_HandleTypeDef *sensor, uint32_t *version);
bool ags10_get_gas_resistance(AGS10_HandleTypeDef *sensor, uint32_t *resistance);
bool ags10_get_tvoc(AGS10_HandleTypeDef *sensor, uint32_t *tvoc);
bool ags10_set_address(AGS10_HandleTypeDef *sensor, uint8_t new_addr);

#endif /* INC_AGS10_GAS_SENSOR_H_ */
