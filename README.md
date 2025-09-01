# AGS10 Gas Sensor Driver for STM32F1

## Overview

driver for the AGS10 gas sensor using I2C on STM32F1. Supports gas resistance and TVOC readings with CRC validation and polling.

## Features

* Read gas resistance (Ohms)
* Read TVOC levels
* CRC8 checksum verification

## Notes
* CRC8 is automatically checked for all reads.
* HAL I2C is required (`stm32f1xx_hal.h`).
