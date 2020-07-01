/**
 * @file BMP280.h
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
#include <SPI.h>

class BMP280 {
public:
    BMP280();

    bool begin(SPIClass *spi, uint8_t cs);
    
    bool attachInterrupt();
    void detachInterrupt();

    uint32_t getTemperature(void);
    uint32_t getPressure(void);

private:
    uint8_t read8(uint8_t reg);
    void write8(uint8_t reg, uint8_t value);

    SPIClass *spi;
    uint8_t cs;

    union compensation{
        uint16_t array[12],
        struct s{
            uint16_t digT1,
            int16_t digT2,
            int16_t digT3,
            uint16_t digP1,
            int16_t digP2,
            int16_t digP3,
            int16_t digP4,
            int16_t digP5,
            int16_t digP6,
            int16_t digP7,
            int16_t digP8,
            int16_t digP9,
        } data
    };

    compensation comp;

};
