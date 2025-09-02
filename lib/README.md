# AGS10 Gas Sensor Library (Platform-Agnostic)

This is a platform-agnostic C library for interfacing with the AGS10 gas sensor, which measures Total Volatile Organic Compounds (TVOC) and gas resistance. The library abstracts I2C communication and delay functions, allowing it to be used on any microcontroller or platform by providing platform-specific implementations.

## Features
- Initialize and configure the AGS10 sensor.
- Read raw gas resistance and TVOC values.
- Set a new I2C address for the sensor.
- Calculate CRC8 checksum for data integrity.
- Platform-agnostic design with customizable I2C and delay interfaces.


## Files
- `ags10_gas_sensor.h`: Header file with definitions, types, and function prototypes.
- `ags10_gas_sensor.c`: Source file with the core library implementation.

## Usage

### 1. Include the Library
Add `ags10_gas_sensor.h` and `ags10_gas_sensor.c` to your project. Include the header in your application code:

```c
#include <ags10_gas_sensor.h>
```

### 2. Define Platform-Specific Functions
The library uses a platform-agnostic interface (`ags10ma_platform_i2c_t`) for I2C communication and delays. You must provide implementations for the following functions:
- `bool i2c_transmit(void *handle, uint8_t addr, const uint8_t *data, uint16_t len, uint32_t timeout_ms)`: Sends data over I2C.
- `bool i2c_receive(void *handle, uint8_t addr, uint8_t *data, uint16_t len, uint32_t timeout_ms)`: Receives data over I2C.
- `void delay_ms(uint32_t ms)`: Delays execution for the specified milliseconds.
- `void *handle`: A platform-specific handle (e.g., I2C peripheral or driver context).

#### Example: STM32 Implementation
For an STM32 microcontroller using the HAL library, create a file (e.g., `platform_stm32.c`):

```c
#include <stm32f1xx_hal.h>
#include <ags10_gas_sensor.h>

bool stm32_i2c_transmit(void *handle, uint8_t addr, const uint8_t *data, uint16_t len, uint32_t timeout_ms) {
    return HAL_I2C_Master_Transmit((I2C_HandleTypeDef *)handle, addr, (uint8_t *)data, len, timeout_ms) == HAL_OK;
}

bool stm32_i2c_receive(void *handle, uint8_t addr, uint8_t *data, uint16_t len, uint32_t timeout_ms) {
    return HAL_I2C_Master_Receive((I2C_HandleTypeDef *)handle, addr, data, len, timeout_ms) == HAL_OK;
}

void stm32_delay_ms(uint32_t ms) {
    HAL_Delay(ms);
}
```

For other platforms (e.g., Arduino, ESP32), implement similar functions using the platform's I2C and delay.

### 3. Initialize the Sensor
Set up the platform interface and initialize the sensor in your application code:

```c
#include <ags10_gas_sensor.h>

int main(void) {
    // Define platform-specific interface
    ags10ma_platform_i2c_t platform = {
        .i2c_transmit = stm32_i2c_transmit, // Replace with your transmit function
        .i2c_receive = stm32_i2c_receive,   // Replace with your receive function
        .delay_ms = stm32_delay_ms,         // Replace with your delay function
        .handle = &hi2c1                    // Replace with your I2C handle
    };

    // Initialize sensor
    AGS10MA_HandleTypeDef sensor;
    if (!AGS10MA_Init(&sensor, &platform, AGS10MA_I2C_ADDR_DEFAULT)) {
        // Handle initialization failure
    }

    // Example: Read TVOC value
    uint32_t tvoc;
    if (AGS10MA_GetTVOC(&sensor, &tvoc)) {
        // Use tvoc value
    } else {
        // Handle error
    }

    return 0;
}
```
### 5. Notes
- Ensure your platform's I2C functions handle the AGS10's specific I2C addresses (`AGS10MA_I2C_WRITE` and `AGS10MA_I2C_READ`).
- The library assumes a 5-byte read (4 data bytes + 1 CRC byte) for register operations.
- The default I2C address is `0x1A`, but it can be changed using `AGS10MA_SetAddress`.
- Error handling is indicated by return values (`true` for success, `false` for failure).
- For failed reads, `AGS10MA_GetGasResistance` and `AGS10MA_GetTVOC` set output values to `0xFFFFFFFF`.

Adapt the platform-specific functions to match your hardware.

## License
This library is provided as-is for use with the AGS10 gas sensor. No warranty is provided.