/*
 * AGS10.c
 * Created on: Jan 31, 2025
 * Author: emirsatlm
 */
#include <AGS10.h>

uint8_t AGS10MA_CRC8(const uint8_t *data, int len) {
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

bool AGS10MA_Init(AGS10MA_HandleTypeDef *sensor, AGS10MA_PlatformI2C *platform, uint8_t i2c_addr) {
    if (!sensor || !platform) {
        return false;
    }
    sensor->platform = platform;
    sensor->i2c_addr = i2c_addr;
    return true;
}

bool AGS10MA_ReadRegister(AGS10MA_HandleTypeDef *sensor, uint8_t reg, uint16_t delayms, uint32_t *value) {
    uint8_t buf[5];

    // Send register address
    if (!sensor->platform->i2c_transmit(sensor->platform->handle, AGS10MA_I2C_WRITE, &reg, 1, 1000)) {
        return false;
    }

    // Delay
    sensor->platform->delay_ms(delayms);

    // Receive 5 bytes (4 data + 1 CRC)
    if (!sensor->platform->i2c_receive(sensor->platform->handle, AGS10MA_I2C_READ, buf, 5, 1000)) {
        return false;
    }

    // Verify CRC
    if (AGS10MA_CRC8(buf, 4) != buf[4]) {
        return false;  // CRC mismatch
    }

    *value = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
    return true;
}

bool AGS10MA_GetFirmwareVersion(AGS10MA_HandleTypeDef *sensor, uint32_t *version) {
    return AGS10MA_ReadRegister(sensor, AGS10MA_VERSION_REG, 30, version);
}

bool AGS10MA_GetGasResistance(AGS10MA_HandleTypeDef *sensor, uint32_t *resistance) {
    if (!AGS10MA_ReadRegister(sensor, AGS10MA_GASRES_REG, 1000, resistance)) {
        *resistance = 0xFFFFFFFF;
        return false;
    }
    *resistance *= 100;
    return true;
}

bool AGS10MA_GetTVOC(AGS10MA_HandleTypeDef *sensor, uint32_t *tvoc) {
    if (!AGS10MA_ReadRegister(sensor, AGS10MA_TVOCSTAT_REG, 1000, tvoc)) {
        *tvoc = 0xFFFFFFFF; // Indicate failure
        return false;
    }
    *tvoc &= 0xFFFFFF;
    return true;
}

bool AGS10MA_SetAddress(AGS10MA_HandleTypeDef *sensor, uint8_t new_addr) {
    uint8_t buf[6] = { AGS10MA_SETADDR_REG, new_addr, ~new_addr, new_addr, ~new_addr, 0x00 };
    if (!sensor->platform->i2c_transmit(sensor->platform->handle, AGS10MA_I2C_WRITE, buf, 6, 1000)) {
        return false;
    }
    sensor->i2c_addr = new_addr; // Update the stored address
    return true;
}