// todo: use doxgen style brief
/**
 * @file ags10.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "ags10.h"

/*******************************************************************************
* Public Function Definitions
 ******************************************************************************/

bool ags10_init(AGS10MA_HandleTypeDef *p_sensor,
                ags10ma_platform_i2c_t *p_platform,
                uint8_t i2c_addr)
{
    if ((NULL == p_platform) || (NULL == p_sensor))
    {
        return false;
    }

    p_sensor->platform = p_platform;
    p_sensor->i2c_addr = i2c_addr;

    return true;
}

bool ags10_register_read(AGS10MA_HandleTypeDef *p_sensor, 
                         uint8_t reg,
                         uint16_t delayms,
                         uint32_t *p_value)
{
    // Send register address // todo: remove comments, code should be self-explanatory
    bool register_addr_send_status = 
        p_sensor->platform->i2c_transmit(p_sensor->platform->handle,
                                         AGS10MA_I2C_DEFAULT_ADDR, 
                                         &reg, 
                                         1, 
                                         1000);

    if (false == register_addr_send_status)
    {
        return false;
    }

    // Delay
    p_sensor->platform->delay_ms(delayms);

    #define READ_BYTE_CNT 5
    uint8_t buff[READ_BYTE_CNT] = {0U};

    // Receive 5 bytes (4 data + 1 CRC)
    if (!p_sensor->platform->i2c_receive(p_sensor->platform->handle,
                                         AGS10MA_READ_REG_ADDR,
                                         buff,
                                         READ_BYTE_CNT,
                                         1000))
    {
        return false;
    }
    #undef READ_BYTE_CNT

    // Verify CRC
    if (ags10_crc8(buff, 4) != buff[4]) // todo: why this is 4, remove all magic numbers, define macros
    {
        return false; // CRC mismatch
    }

    *p_value = ((uint32_t)buff[0] << 24) | 
               ((uint32_t)buff[1] << 16) | 
               ((uint32_t)buff[2] << 8)  | 
               ((uint32_t)buff[3]);

    return true;
}

bool ags10_firmware_version_get(AGS10MA_HandleTypeDef *p_sensor,
                                uint32_t *p_version)
{
    return ags10_register_read(p_sensor, AGS10MA_VERSION_REG, 30, p_version);
}

bool ags10_gas_resistance_get(AGS10MA_HandleTypeDef *p_sensor,
                              uint32_t *p_resistance)
{
    if (false == ags10_register_read(p_sensor,
                                     AGS10MA_GAS_RES_REG,
                                     1000,
                                     p_resistance))
    {
        #define FAIL_VAL 0xFFFFFFFF
        *p_resistance = FAIL_VAL;
        #undef FAIL_VAL

        return false;
    }

    *p_resistance *= 100;

    return true;
}

bool ags10_tvoc_get(AGS10MA_HandleTypeDef *p_sensor, uint32_t *p_tvoc)
{
    if (false == ags10_register_read(p_sensor,
                                     AGS10MA_TVOC_STAT_REG,
                                     1000,
                                     p_tvoc))
    {
        #define FAIL_VAL 0xFFFFFFFF
        *p_tvoc = FAIL_VAL;
        #undef FAIL_VAL

        return false;
    }

    *p_tvoc &= 0xFFFFFF;

    return true;
}

bool ags10_address_set(AGS10MA_HandleTypeDef *p_sensor, uint8_t new_addr)
{
    uint8_t buf[6] = {
        
        AGS10MA_SET_ADDR_REG,
        new_addr,
        ~new_addr,
        new_addr,
        ~new_addr, 
        0x00,
    };

    if (!p_sensor->platform->i2c_transmit(p_sensor->platform->handle,
                                          AGS10MA_WRITE_REG_ADDR,
                                          buf,
                                          6,
                                          1000))
    {
        return false;
    }

    p_sensor->i2c_addr = new_addr;

    return true;
}

uint8_t ags10_crc8(const uint8_t *p_data, int len)
{
    const uint8_t POLYNOMIAL = 0x31;
    uint8_t crc = 0xFF;

    for (int idx_1 = 0; idx_1 < len; idx_1++)
    {
        crc ^= p_data[idx_1];

        for (int idx_2 = 0; idx_2 < 8; idx_2++)
        {
            crc = (crc & 0x80) ? ((crc << 1) ^ POLYNOMIAL) : (crc << 1);
        }
    }

    return crc;
}

// eof
