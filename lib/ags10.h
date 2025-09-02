// todo: use doxgen style brief
/**
 * @file ags10.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef INC_AGS10_H
#define INC_AGS10_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/*******************************************************************************
* Defines
 ******************************************************************************/
// todo: If the client code stores the device's address as an argument in the init function, AGS10MA_I2C_DEVICE_ADDR definition is not necessary. The client code must define the addresses of their own devices.
#define AGS10MA_I2C_DEVICE_ADDR    0x1A
#define AGS10MA_WRITE_REG_ADDR     0x34
#define AGS10MA_READ_REG_ADDR      0x35

#define AGS10MA_TVOC_STAT_REG      0x00
#define AGS10MA_VERSION_REG        0x11
#define AGS10MA_GAS_RES_REG        0x20
#define AGS10MA_SET_ADDR_REG       0x21

/*******************************************************************************
* Structs
 ******************************************************************************/

typedef struct ags10ma_platform_i2c_s
{
    bool (*i2c_transmit)(void* handle, uint8_t addr, char* data, uint16_t len, uint32_t timeout_ms);
    bool (*i2c_receive)(void* handle, uint8_t addr, uint8_t* data, uint16_t len, uint32_t timeout_ms);
    void (*delay_ms)(uint32_t ms);
    void* handle;
} ags10ma_platform_i2c_t;

typedef struct {
    ags10ma_platform_i2c_t* platform;
    uint8_t i2c_addr;            
} AGS10MA_HandleTypeDef;

/*******************************************************************************
* Public Function Declaration
 ******************************************************************************/

// todo: write a brief comment (use Doxygen Documentation Generator)

//* Example brief comment
/**
 * @brief This funtion inits ags10 gas sensor.
 * 
 * @param ph_sensor A handle to indicate sensor ID.
 * @param p_platform A struct to abstract the functions of the MCU.
 * @param i2c_addr I2C address of gas sensor device.
 * 
 * @return true : Initialization successful.
 * @return false : Initialization fail.
 *                 Possible causes: null arguments
 * 
 */
bool ags10_init(AGS10MA_HandleTypeDef* ph_sensor,
                ags10ma_platform_i2c_t* p_platform,
                uint8_t i2c_addr);

bool ags10_register_read(AGS10MA_HandleTypeDef* ph_sensor,
                         uint8_t reg,
                         uint16_t delayms,
                         uint32_t* p_value);

bool ags10_firmware_version_get(AGS10MA_HandleTypeDef* ph_sensor,
                                uint32_t* p_version);

bool ags10_gas_resistance_get(AGS10MA_HandleTypeDef* ph_sensor,
                              uint32_t* p_resistance);

bool ags10_tvoc_get(AGS10MA_HandleTypeDef* ph_sensor,
                    uint32_t* p_tvoc);

bool ags10_address_set(AGS10MA_HandleTypeDef* ph_sensor,
                       uint8_t new_addr);

uint8_t ags10_crc8(const uint8_t* p_data, int len);

// todo: make private function if a function dont use by client code, remove from header file
// todo: add all features of device
// todo: check multiple sensor usage scenarios

#endif /* INC_AGS10_H */
