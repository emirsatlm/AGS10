/*
 *  AGS10.c
 *  Created on: Jan 31, 2025
 *  Author: emirsatlm
 */
#include <AGS10.h>

uint8_t ags10_crc8(const uint8_t *data, int len) {
    const uint8_t POLYNOMIAL = 0x31;
    uint8_t crc = 0xFF;

    for (int j = 0; j < len; j++) {
        crc ^= data[j];
        for (int i = 0; i < 8; i++) {
            crc = (crc & 0x80) ? (crc << 1) ^ POLYNOMIAL : (crc << 1);
        }
    }
    return crc;
}

bool ags10_init(AGS10_HandleTypeDef *sensor, I2C_HandleTypeDef *hi2c, uint8_t i2c_addr) {
    sensor->hi2c = hi2c;
    sensor->i2c_addr = i2c_addr;
    return true;
}

bool ags10_read_register(AGS10_HandleTypeDef *sensor, uint8_t reg, uint16_t delayms, uint32_t *value) {
    uint8_t buf[5];

    // Send register address
    if (HAL_I2C_Master_Transmit(sensor->hi2c, AGS10_I2C_WRITE, &reg, 1, HAL_MAX_DELAY) != HAL_OK) {
        return false;
    }

    HAL_Delay(delayms);

    // Receive 5 bytes (4 data + 1 CRC)
    if (HAL_I2C_Master_Receive(sensor->hi2c, AGS10_I2C_READ, buf, 5, HAL_MAX_DELAY) != HAL_OK) {
        return false;
    }

    if (ags10_crc8(buf, 4) != buf[4]) {
        return false;  // CRC mismatch
    }

    *value = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
    return true;
}

bool ags10_get_firmware_version(AGS10_HandleTypeDef *sensor, uint32_t *version) {
    return ags10_read_register(sensor, AGS10_VERSION_REG, 30, version);
}

bool ags10_get_gas_resistance(AGS10_HandleTypeDef *sensor, uint32_t *resistance) {
    if (!ags10_read_register(sensor, AGS10_GASRES_REG, 1000, resistance)) {
        *resistance = 0xFFFFFFFF;
        return false;
    }
    *resistance *= 100;
    return true;
}

bool ags10_get_tvoc(AGS10_HandleTypeDef *sensor, uint32_t *tvoc) {
    if (!ags10_read_register(sensor, AGS10_TVOCSTAT_REG, 1000, tvoc)) {
        *tvoc = 0xFFFFFFFF; // Indicate failure
        return false;
    }
    *tvoc &= 0xFFFFFF;
    return true;
}

bool ags10_set_address(AGS10_HandleTypeDef *sensor, uint8_t new_addr) {
    uint8_t buf[6] = { AGS10_SETADDR_REG, new_addr, ~new_addr, new_addr, ~new_addr, 0x00 };
    if (HAL_I2C_Master_Transmit(sensor->hi2c, AGS10_I2C_WRITE, buf, 6, HAL_MAX_DELAY) != HAL_OK) {
        return false;
    }
    return true;
}

