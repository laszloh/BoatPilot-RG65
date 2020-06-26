/**
 * @file main.c
 * @author Laszlo Hegedüs (laszlo.hegedues@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-06-23
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <stdint.h>

#include <libopencm3/cm3/nvic.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/timer.h>

#include "systick.h"

extern "C" {
//    void tim2_isr(void);
};

typedef struct {
    int port;
    int pin;
} gpio_t;

constexpr gpio_t servo2 = {GPIOB, GPIO3};
constexpr gpio_t servo1 = {GPIOB, GPIO4};
constexpr gpio_t servo3 = {GPIOB, GPIO5};

static inline void clock_setup(void)
{
    rcc_clock_setup_in_hse_8mhz_out_72mhz();
}

static inline void gpio_setup(void) {
    // enable peripherial clocks
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);

    gpio_set_mode(servo1.port, GPIO_MODE_OUTPUT_50_MHZ,
        GPIO_CNF_OUTPUT_PUSHPULL, servo1.pin);
    gpio_clear(servo1.port, servo1.pin);

    gpio_set_mode(servo2.port, GPIO_MODE_OUTPUT_50_MHZ,
        GPIO_CNF_OUTPUT_PUSHPULL, servo2.pin);
    gpio_clear(servo2.port, servo2.pin);

    gpio_set_mode(servo3.port, GPIO_MODE_OUTPUT_50_MHZ,
        GPIO_CNF_OUTPUT_PUSHPULL, servo3.pin);
    gpio_clear(servo3.port, servo3.pin);
}

static inline void spi_setup(void) {
    // enable SPI1 as slave (communication channel to the NanoPI)
    rcc_periph_clock_enable(RCC_SPI1);

    // Configure GPIOA: SCK = PA5, MISO = PA6, MOSI = PA7, NSS = PA4
    gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, GPIO4 | GPIO5 | GPIO7);
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO6);

    // reset peripherial
    spi_reset(SPI1);

    // set main SPI settings
    spi_init_master(
        SPI1,
        SPI_CR1_BAUDRATE_FPCLK_DIV_4,
        SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE,
        SPI_CR1_CPHA_CLK_TRANSITION_1,
        SPI_CR1_DFF_8BIT,
        SPI_CR1_MSBFIRST
    );

    // set slave mode
    spi_set_slave_mode(SPI1);

    // anble HW chip select
    spi_disable_software_slave_management(SPI1);

    // enable unidirectional communication
    spi_set_unidirectional_mode(SPI1);

    // enable SPI module
    spi_enable(SPI1);

    // enable SPI2 as master (for the 9-axis gyrro and the BMP)
    rcc_periph_clock_enable(RCC_SPI2);

    // Configure GPIOB: SCK = PB13, MISO = PB14, MOSI = PB15
    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO13 | GPIO15);
    gpio_set_mode(GPIOB, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, GPIO14);

    // We will be manually controlling the SS pin here, so set it as a normal output
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO8 | GPIO10);

    // SS is active low, so pull it high for now
    gpio_set(GPIOA, GPIO8 | GPIO10);

    // Reset our peripheral
    spi_reset(SPI2);

    // Set main SPI settings:
    // - The datasheet for the 74HC595 specifies a max frequency at 4.5V of
    //   25MHz, but since we're running at 3.3V we'll instead use a 12MHz
    //   clock, or 1/4 of our main clock speed.
    // - Set the clock polarity to be zero at idle
    // - Set the clock phase to trigger on the rising edge, as per datasheet
    // - Set 8 bit transfer size
    // - Send the most significant bit (MSB) first
    spi_init_master(
        SPI2,
        SPI_CR1_BAUDRATE_FPCLK_DIV_4,
        SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE,
        SPI_CR1_CPHA_CLK_TRANSITION_1,
        SPI_CR1_DFF_8BIT,
        SPI_CR1_MSBFIRST
    );

    // Since we are manually managing the SS line, we need to move it to
    // software control here.
    spi_enable_software_slave_management(SPI2);

    // We also need to set the value of NSS high, so that our SPI peripheral
    // doesn't think it is itself in slave mode.
    spi_set_nss_high(SPI2);

    // The terminology around directionality can be a little confusing here -
    // unidirectional mode means that this is the only chip initiating
    // transfers, not that it will ignore any incoming data on the MISO pin.
    // Enabling duplex is required to read data back however.
    spi_set_unidirectional_mode(SPI2);

    // Enable the peripheral
    spi_enable(SPI2);
}

static inline void i2c_setup(void) {
    // enable peripherial clocks
    rcc_periph_clock_enable(RCC_I2C1);

}

static inline void tim_setup(void) {
    // enable peripherial clocks
    rcc_periph_clock_enable(RCC_TIM2);
    rcc_periph_clock_enable(RCC_TIM3);

    timer_reset(TIM2);

    timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, 
        TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

    timer_set_prescaler(TIM2, ((rcc_apb1_frequency * 2) / 1000000));
    timer_enable_preload(TIM2);
    timer_continuous_mode(TIM2);

    timer_set_period(TIM2, 20000);

    timer_set_oc_value(TIM2, TIM_OC1, 1000);

    timer_enable_counter(TIM2);

    timer_enable_irq(TIM2, TIM_DIER_CC1IE);
    timer_enable_irq(TIM2, TIM_DIER_UIE);
}

void tim2_isr(void) {
    if(timer_get_flag(TIM2, TIM_SR_CC1IF)) {
        //
    } else if(timer_get_flag(TIM2, TIM_SR_UIF)) {
        gpio_set(servo1.port, servo1.pin);
        gpio_set(servo2.port, servo2.pin);
        gpio_set(servo3.port, servo3.pin);
    }
}

int main(void) {
    clock_setup();
    gpio_setup();
    spi_setup();
    i2c_setup();
    tim_setup();
    systick_setup();

    while(1) {
        delayMs(500);
    }

    return 0;
}

