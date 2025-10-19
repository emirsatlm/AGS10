# AGS10 Gas Sensor Driver

## Overview

This is a driver for the AGS10 TVOC (Total Volatile Organic Compounds) and gas sensor, which communicates over I2C. This driver handles register reading, data parsing, and CRC8 checksum validation.

The driver is split into (`ags10.c`, `ags10.h`) and requires the user to implement the platform-specific I/O functions. An example for STM32F1 (using HAL) is provided in the `example` directory.

## Files
* example
includes example for stm32f103c8t6
* lib
to adapt other enviroments
## Features

* Read gas resistance (Ohms)
* Read TVOC levels
* CRC8 checksum verification

# AGS10 TVOC & Gas Sensor Driver



## Hardware Dependencies

* **I2C:** The driver requires a functional I2C peripheral on your microcontroller.
* **Delay:** A millisecond-level delay function is required.
* **STM32 HAL (Example):** The provided example uses the `stm32f1xx_hal.h` library for I2C and delay functions.

## User Implementation (Hardware Abstraction)

This driver is designed to be portable. To make it work on your specific hardware (like an STM32, Nordic Semiconductor, Renesas, etc.), you **must** provide the implementations for the following three functions, which are declared in `ags10.h`:

```c
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