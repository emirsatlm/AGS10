// todo: use doxgen style brief
/**
 * @file ags10.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.3
 * @date 2025-09-01
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef INC_AGS10_H_
#define INC_AGS10_H_

#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
* Defines
 ******************************************************************************/
// todo: If the client code stores the device's address as an argument in the init function, AGS10MA_I2C_DEVICE_ADDR definition is not necessary. The client code must define the addresses of their own devices.
#define AGS10MA_I2C_DEVICE_ADDR    0x1A

#define AGS10MA_TVOC_STAT_REG      0x00
#define AGS10MA_VERSION_REG        0x11
#define AGS10MA_GAS_RES_REG        0x20
#define AGS10MA_SET_ADDR_REG       0x21
#define AGS10MA_DATA_LEN           4U
/*******************************************************************************/

/*------------------------------------------------------------
 * Low-Level I/O Interface (to be implemented by user)
 *-----------------------------------------------------------*/

/**
 * @brief  Write data to the AGS10 device.
 * @param  addr: I2C address of device
 * @param  pData: pointer to data to send
 * @param  length: number of bytes to send
 * @retval true if success, false if failed
 */
bool AGS10_IO_Write(uint8_t addr, uint8_t *pData, uint16_t length);

/**
 * @brief  Read data from the AGS10 device.
 * @param  addr: I2C address of device
 * @param  pData: pointer to buffer to store read data
 * @param  length: number of bytes to read
 * @retval true if success, false if failed
 */
bool AGS10_IO_Read(uint8_t addr, uint8_t *pData, uint16_t length);

/**
 * @brief  Delay in milliseconds.
 * @param  ms: delay duration
 */
void AGS10_IO_Delay(uint16_t ms);

/*******************************************************************************
* Structs
 ******************************************************************************/
typedef struct {
    uint8_t i2c_addr;
} AGS10_HandleTypeDef;

/*------------------------------------------------------------
 * Public API
 *-----------------------------------------------------------*/

/**
 * @brief This funtion inits ags10 gas sensor.
 * 
 * @param ph_sensor A handle to indicate sensor ID.
 * @param i2c_addr I2C address of gas sensor device.
 * 
 * @return true : Initialization successful.
 * @return false : Initialization fail.
 *                 Possible causes: null arguments
 * 
 */
bool ags10_init(AGS10_HandleTypeDef *ph_sensor, 
                uint8_t i2c_addr);

bool ags10_register_read(AGS10_HandleTypeDef *ph_sensor, 
                         uint8_t reg, 
                         uint16_t delayms, 
                         uint32_t *p_value);

bool ags10_firmware_version_get(AGS10_HandleTypeDef *ph_sensor, 
                                uint32_t *p_version);

bool ags10_gas_resistance_get(AGS10_HandleTypeDef *ph_sensor, 
                              uint32_t *p_resistance);

bool ags10_tvoc_get(AGS10_HandleTypeDef *ph_sensor, 
                       uint32_t *p_tvoc);
                       
bool ags10_address_set(AGS10_HandleTypeDef *ph_sensor, 
        uint8_t new_addr);
uint8_t ags10_crc8(const uint8_t *p_data, int len);
#endif /* INC_AGS10_H_ */

