/**
 * @file    sensor.h
 * @brief   AGS10 Gas Sensor driver header
 * @date    Jan 31, 2025
 * @author  Emir
 */

#ifndef INC_AGS10_H_
#define INC_AGS10_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_i2c.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* Exported constants --------------------------------------------------------*/
#define AGS10MA_I2C_DEFAULT_ADDR   0x1A    /**< Default I2C address */
#define AGS10MA_I2C_WRITE          0x34    /**< Write instruction */
#define AGS10MA_I2C_READ           0x35    /**< Read instruction */

#define AGS10MA_TVOC_STAT_REG      0x00    /**< Status and TVOC reading */
#define AGS10MA_VERSION_REG        0x11    /**< Firmware version */
#define AGS10MA_GASRES_REG         0x20    /**< Raw gas resistance */
#define AGS10MA_SET_ADDR_REG       0x21    /**< Change I2C address */

/* Exported types ------------------------------------------------------------*/
typedef struct
{
    I2C_HandleTypeDef *hi2c;    /**< I2C handle */
    uint8_t i2c_addr;           /**< I2C address */
} AGS10MA_HandleTypeDef;

/* Exported functions --------------------------------------------------------*/
/**
 * @brief  Calculate CRC8 checksum.
 * @param  data Pointer to data buffer
 * @param  len  Length of data
 * @retval CRC8 value
 */
uint8_t ags10ma_crc8(const uint8_t *data, int len);

/**
 * @brief  Initialize the AGS10 sensor
 * @param  sensor Pointer to sensor handle
 * @param  hi2c  Pointer to I2C handle
 * @param  i2c_addr I2C address of the sensor
 * @retval true if initialization successful, false otherwise
 */
bool AGS10MA_Init(AGS10MA_HandleTypeDef *sensor, I2C_HandleTypeDef *hi2c, uint8_t i2c_addr);

/**
 * @brief  Read a sensor register
 * @param  sensor Pointer to sensor handle
 * @param  reg    Register address
 * @param  delayms Delay after read in ms
 * @param  value  Pointer to store the read value
 * @retval true if read successful, false otherwise
 */
bool ags10ma_register_read(AGS10MA_HandleTypeDef *sensor, uint8_t reg, uint16_t delayms, uint32_t *value);

/**
 * @brief  Get firmware version
 * @param  sensor Pointer to sensor handle
 * @param  version Pointer to store firmware version
 * @retval true if successful, false otherwise
 */
bool ags10ma_firmware_version_get(AGS10MA_HandleTypeDef *sensor, uint32_t *version);

/**
 * @brief  Get raw gas resistance
 * @param  sensor Pointer to sensor handle
 * @param  resistance Pointer to store gas resistance
 * @retval true if successful, false otherwise
 */
bool ags10ma_gas_resistance_get(AGS10MA_HandleTypeDef *sensor, uint32_t *resistance);

/**
 * @brief  Get TVOC value
 * @param  sensor Pointer to sensor handle
 * @param  tvoc Pointer to store TVOC value
 * @retval true if successful, false otherwise
 */
bool ags10ma_tvOc_get(AGS10MA_HandleTypeDef *sensor, uint32_t *tvoc);

/**
 * @brief  Set new I2C address for sensor
 * @param  sensor Pointer to sensor handle
 * @param  new_addr New I2C address
 * @retval true if successful, false otherwise
 */
bool ags10ma_address_set(AGS10MA_HandleTypeDef *sensor, uint8_t new_addr);

#endif /* INC_AGS10_GAS_SENSOR_H_ */
