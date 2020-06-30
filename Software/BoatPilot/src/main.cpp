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
#include "servo.h"

extern "C" {
//    void tim2_isr(void);
};

#define SERVO_PORT  GPIOB
#define SERVO1_PIN  GPIO10
#define SERVO2_PIN  GPIO3
#define SERVO3_PIN  GPIO11

#define ROTARY_PORT GPIOB
#define ROTARY_PIN  GPIO8

#define SPI2CS_PORT GPIOA
#define BMP280_CS   GPIO8
#define MPU9250_CS  GPIO10

#define IBUS_PORT   GPIOA
#define IBUS_PIN    GPIO9

#define GPS_PORT    GPIOA
#define GPSTX_PIN   GPIO2
#define GPSRX_PIN   GPIO3

#define I2C_PORT    GPIOB
#define I2CSCL_PIN  GPIO6
#define I2CSDA_PIN  GPIO7

#define UBAT_PORT   GPIOA
#define UBAT_PIN    GPIO0

static inline void clock_setup(void)
{
    rcc_clock_setup_in_hse_8mhz_out_72mhz();
}

static inline void gpio_setup(void) {
    // enable peripherial clocks
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_AFIO);

    // Servo pins: SERVO1 = PB10, SERVO2 = PB3, SERVO3 = PB11
    gpio_set_mode(SERVO_PORT, GPIO_MODE_OUTPUT_50_MHZ,
        GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, SERVO1_PIN | SERVO2_PIN | SERVO3_PIN);
    gpio_primary_remap(0, AFIO_MAPR_TIM2_REMAP_FULL_REMAP);
    gpio_clear(SERVO_PORT, SERVO1_PIN | SERVO2_PIN | SERVO3_PIN);

    // PWM output of AS5600: ROTARY = PB8
    gpio_set_mode(ROTARY_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, ROTARY_PIN);

    // SPI1 pin setup: SCK = PA5, MISO = PA6, MOSI = PA7, NSS = PA4
    gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, GPIO4 | GPIO5 | GPIO7);
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO6);

    // SPI2 pin setup: SCK = PB13, MISO = PB14, MOSI = PB15
    gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO13 | GPIO15);
    gpio_set_mode(GPIOB, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, GPIO14);

    // manual control of the Slave-Selects: BMP280 = PA8, MPU9250 = PA10
    gpio_set_mode(SPI2CS_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, BMP280_CS | MPU9250_CS);

    // half-duplex UART for IBUS: IBUS = PA9
    gpio_set_mode(IBUS_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN, IBUS_PIN);
    gpio_set(IBUS_PORT, IBUS_PIN);

    // full-duplex UART for GPS: GPS_TX = PA2, GPS_RX = PA3
    gpio_set_mode(GPS_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPSTX_PIN);
    gpio_set_mode(GPS_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, GPSRX_PIN);

    // i2c 1 module: SDA = PB7, SCL = PB6
    gpio_set_mode(I2C_PORT, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN, I2CSCL_PIN | I2CSDA_PIN);

    // ADC for Battery measurment
    gpio_set_mode(UBAT_PORT, GPIO_MODE_INPUT, GPIO_CNF_INPUT_ANALOG, UBAT_PIN);
}

static inline void spi_setup(void) {
    // enable SPI1 as slave (communication channel to the NanoPI)
    rcc_periph_clock_enable(RCC_SPI1);

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

    // enable HW chip select
    spi_disable_software_slave_management(SPI1);

    // enable unidirectional communication
    spi_set_unidirectional_mode(SPI1);

    // enable SPI module
    spi_enable(SPI1);

    //
    //
    // enable SPI2 as master (for the 9-axis gyrro and the BMP)
    rcc_periph_clock_enable(RCC_SPI2);

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

    i2c_reset(I2C1);

    i2c_peripheral_disable(I2C1);

    // APB1 is running at 36MHz
    i2c_set_clock_frequency(I2C1, I2C_CR2_FREQ_36MHZ);
    
    // enable fast mode I2C
    i2c_set_fast_mode(I2C1);
	
    // fclock for I2C is 36MHz APB2 -> cycle time 28ns, low time at 400kHz
	// incl trise -> Thigh = 1600ns; CCR = tlow/tcycle = 0x1C,9;
	// Datasheet suggests 0x1e.
    i2c_set_ccr(I2C1, 0x1e);

	// fclock for I2C is 36MHz -> cycle time 28ns, rise time for
	// 400kHz => 300ns and 100kHz => 1000ns; 300ns/28ns = 10;
	// Incremented by 1 -> 11.
    i2c_set_trise(I2C1, 0x0b);

    // set a slave address (only needed if we want to receive data from the NanoPI)
    i2c_set_own_7bit_slave_address(I2C1, 0x32);

    // enable the peripherial
    i2c_peripheral_enable(I2C1);
}

static inline void tim_setup(void) {
    // enable peripherial clocks
    rcc_periph_clock_enable(RCC_TIM2);

    timer_reset(TIM2);

    timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, 
        TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

    timer_set_prescaler(TIM2, ((rcc_apb1_frequency * 2) / 1000000));
    timer_enable_preload(TIM2);
    timer_continuous_mode(TIM2);

    // 20 ms interval
    timer_set_period(TIM2, 20000);

    // Connect Servo 1
    timer_set_oc_mode(TIM2, TIM_OC3, TIM_OCM_PWM1);
    timer_enable_oc_preload(TIM2, TIM_OC3);
    timer_enable_oc_output(TIM2, TIM_OC3);
    timer_set_oc_value(TIM2, TIM_OC3, 1000);

    // connect Servo 2
    timer_set_oc_mode(TIM2, TIM_OC2, TIM_OCM_PWM1);
    timer_enable_oc_preload(TIM2, TIM_OC2);
    timer_enable_oc_output(TIM2, TIM_OC2);
    timer_set_oc_value(TIM2, TIM_OC2, 1000);

    // connect Servo 3
    timer_set_oc_mode(TIM2, TIM_OC4, TIM_OCM_PWM1);
    timer_enable_oc_preload(TIM2, TIM_OC4);
    timer_enable_oc_output(TIM2, TIM_OC4);
    timer_set_oc_value(TIM2, TIM_OC4, 1000);

    timer_enable_counter(TIM2);
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

