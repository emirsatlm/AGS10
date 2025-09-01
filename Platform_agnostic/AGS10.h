/**
 * @file    AGS10.h
 * @brief   AGS10 Gas Sensor driver header (Platform-Agnostic)
 * @date    Jan 31, 2025
 * @author  emirsatlm
 */
#ifndef INC_AGS10_H_
#define INC_AGS10_H_

 /* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* DEFINES --------------------------------------------------------*/
#define AGS10MA_I2C_ADDR_DEFAULT   0x1A    /**< Default I2C address */
#define AGS10MA_I2C_WRITE          0x34    /**< Write instruction */
#define AGS10MA_I2C_READ           0x35    /**< Read instruction */

#define AGS10MA_TVOCSTAT_REG       0x00    /**< Status and TVOC reading */
#define AGS10MA_VERSION_REG        0x11    /**< Firmware version */
#define AGS10MA_GASRES_REG         0x20    /**< Raw gas resistance */
#define AGS10MA_SETADDR_REG        0x21    /**< Change I2C address */

/* ------------------------------------------------------------*/

typedef struct {
    bool (*i2c_transmit)(void* handle, uint8_t addr, const uint8_t* data, uint16_t len, uint32_t timeout_ms);
    bool (*i2c_receive)(void* handle, uint8_t addr, uint8_t* data, uint16_t len, uint32_t timeout_ms);
    void (*delay_ms)(uint32_t ms);
    void* handle;  /**< Platform-specific I2C handle (e.g., I2C peripheral, driver context) */
} AGS10MA_PlatformI2C;

typedef struct {
    AGS10MA_PlatformI2C* platform; /**< Platform-specific I2C interface */
    uint8_t i2c_addr;              /**< I2C address */
} AGS10MA_HandleTypeDef;

/* Functions --------------------------------------------------------*/

uint8_t AGS10MA_CRC8(const uint8_t* data, int len);
bool AGS10MA_Init(AGS10MA_HandleTypeDef* sensor, AGS10MA_PlatformI2C* platform, uint8_t i2c_addr);
bool AGS10MA_ReadRegister(AGS10MA_HandleTypeDef* sensor, uint8_t reg, uint16_t delayms, uint32_t* value);
bool AGS10MA_GetFirmwareVersion(AGS10MA_HandleTypeDef* sensor, uint32_t* version);
bool AGS10MA_GetGasResistance(AGS10MA_HandleTypeDef* sensor, uint32_t* resistance);
bool AGS10MA_GetTVOC(AGS10MA_HandleTypeDef* sensor, uint32_t* tvoc);
bool AGS10MA_SetAddress(AGS10MA_HandleTypeDef* sensor, uint8_t new_addr);

#endif /* INC_AGS10_GAS_SENSOR_H_ */