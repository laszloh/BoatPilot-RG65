/**
 * @file BMP280_RegisterMap.cpp
 * @author Laszlo Hegedüs (laszlo.hegedues@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-06-30
 * 
 * \copyright Copyright (c) 2020 under the MIT License
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#pragma once
#include <stdint.h>

constexpr uint8_t BMP280_RW_MASK = 0x80;

enum bmp280_register {
    BMP280_CALIB00  = 0x88,
    BMP280_CALIB01  = 0x89,
    BMP280_CALIB02  = 0x8A,
    BMP280_CALIB03  = 0x8B,
    BMP280_CALIB04  = 0x8C,
    BMP280_CALIB05  = 0x8D,
    BMP280_CALIB06  = 0x8E,
    BMP280_CALIB07  = 0x8F,
    BMP280_CALIB08  = 0x90,
    BMP280_CALIB09  = 0x91,
    BMP280_CALIB10  = 0x92,
    BMP280_CALIB11  = 0x93,
    BMP280_CALIB12  = 0x94,
    BMP280_CALIB13  = 0x95,
    BMP280_CALIB14  = 0x96,
    BMP280_CALIB15  = 0x97,
    BMP280_CALIB16  = 0x98,
    BMP280_CALIB17  = 0x99,
    BMP280_CALIB18  = 0x9A,
    BMP280_CALIB19  = 0x9B,
    BMP280_CALIB20  = 0x9C,
    BMP280_CALIB21  = 0x9D,
    BMP280_CALIB22  = 0x9E,
    BMP280_CALIB23  = 0x9F,
    BMP280_CALIB24  = 0xA0,
    BMP280_CALIB25  = 0xA1,
    BMP280_ID       = 0xD0,
    BMP280_RESET    = 0xE0,
    BMP280_STATUS   = 0xF3,
    BMP280_CTRL     = 0xF4,
    BMP280_CONFIG   = 0xF5,
    BMP280_PRS_MSB  = 0xF7,
    BMP280_PRS_LSB  = 0xF8,
    BMP280_PSR_XLSB = 0xF9,
    BMP280_TMP_MSB  = 0xFA,
    BMP280_TMP_LSB  = 0xFB,
    BMP280_TMP_XLSB = 0xFC
};

constexpr uint8_t BMP280_ID_VAL = 0x58;
constexpr uint8_t BMP280_RESET  = 0xB6;

enum bmp280_status_bits {
    BMP280_STATUS_IM_UPDATE = 0,
    BMP280_STATUS_MEASURING = 3,
};

enum bmp280_ctrl_meas_bits {
    BMP280_CTRL_MODE   = 0,
    BMP280_CTRL_OSRS_P = 2,
    BMP280_CTRL_OSRS_T = 5,
};
constexpr uint8_t BMP280_CTRL_MODE_MASK   = 0x03;
constexpr uint8_t BMP280_CTRL_OSRS_X_MASK = 0x07;

enum bmp280_config_bits {
    BMP280_CONFIG_SPI3W_EN = 0,
    BMP280_CONFIG_FILTER   = 2,
    BMP280_CONFIG_T_SB     = 5,
};
constexpr uint8_t BMP280_CONFIG_FILTER_MASK = 0x07;
constexpr uint8_t BMP280_CONFIG_T_SB_MASK   = 0x07;

