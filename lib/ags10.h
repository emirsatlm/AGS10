/**
 * @file ags10.h
 * @author emirsatlm (emir@satlm.dev)
 * @brief
 * @version 0.3
 * @date 2025-19-10
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

/*******************************************************************************
* I/O Functions to be implemented by the user
 *******************************************************************************/

/**
 * @brief Write data to the AGS10 device via I2C.
 * 
 * This function transmits a data buffer to the AGS10 sensor at the specified
 * I2C address.
 * 
 * @param[in] addr  I2C address of the AGS10 device.
 * @param[in] pData Pointer to the data buffer to send.
 * @param[in] length Number of bytes to transmit.
 * 
 * @retval true  Data written successfully.
 * @retval false Write operation failed.
 */
bool AGS10_IO_Write(uint8_t addr, uint8_t *pData, uint16_t length);

/**
 * @brief Read data from the AGS10 device via I2C.
 * 
 * This function reads data from the AGS10 sensor at the specified I2C address
 * and stores it in the provided buffer.
 * 
 * @param addr  I2C address of the AGS10 device.
 * @param pData Pointer to the buffer where received data will be stored.
 * @param length Number of bytes to read.
 * 
 * @retval true  Data read successfully.
 * @retval false Read operation failed.
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

/*******************************************************************************
* Public Function Declaration
 ******************************************************************************/

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

/**
 * @brief Read a register value from the AGS10 sensor.
 * 
 * Reads data from a specified register of the AGS10 with an optional delay.
 * 
 * @param ph_sensor Pointer to the sensor handle structure.
 * @param reg Register address to read from.
 * @param delayms Delay in milliseconds before reading (for sensor readiness).
 * @param p_value Pointer to store the read register value.
 * 
 * @retval true  Register read successful.
 * @retval false Read failed or invalid arguments.
 */
bool ags10_register_read(AGS10_HandleTypeDef *ph_sensor, 
                         uint8_t reg, 
                         uint16_t delayms, 
                         uint32_t *p_value);


/**
 * @brief Get the AGS10 sensor firmware version.
 * 
 * Reads and returns the firmware version of the AGS10 sensor.
 * 
 * @param[in] ph_sensor Pointer to the sensor handle structure.
 * @param[out] p_version Pointer to store the firmware version.
 * 
 * @retval true  Firmware version read successfully.
 * @retval false Failed to read firmware version or invalid arguments.
 */
bool ags10_firmware_version_get(AGS10_HandleTypeDef *ph_sensor, 
                                uint32_t *p_version);

                                /**

/**
 * @brief Get the Total Volatile Organic Compounds (TVOC) value.
 * 
 * Retrieves the current TVOC concentration measured by the AGS10 sensor.
 * 
 * @param[in] ph_sensor Pointer to the sensor handle structure.
 * @param[out] p_tvoc Pointer to store the TVOC value (in ppb).
 * 
 * @retval true  TVOC read successfully.
 * @retval false Failed to read TVOC or invalid arguments.
 */
bool ags10_tvoc_get(AGS10_HandleTypeDef *ph_sensor, 
                       uint32_t *p_tvoc);

/**
 * @brief Change the I2C address of the AGS10 sensor.
 * 
 * Sets a new I2C address for the AGS10 sensor.
 * 
 * @param[in] ph_sensor Pointer to the sensor handle structure.
 * @param[in] new_addr New I2C address to assign to the sensor.
 * 
 * @retval true  Address set successfully.
 * @retval false Failed to set address or invalid arguments.
 */
bool ags10_address_set(AGS10_HandleTypeDef *ph_sensor, 
        uint8_t new_addr);

/**
 * @brief Compute CRC-8 checksum for data validation.
 * 
 * Calculates an 8-bit CRC checksum for the given data buffer.
 * 
 * @param[in] p_data Pointer to the input data buffer.
 * @param[in] len Length of the input data buffer.
 * 
 * @return Calculated 8-bit CRC value.
 */
uint8_t ags10_crc8(const uint8_t *p_data, int len);
#endif /* INC_AGS10_H_ */

