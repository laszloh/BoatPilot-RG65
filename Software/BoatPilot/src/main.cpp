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

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/timer.h>

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
    // enable peripherial clocks
    rcc_periph_clock_enable(RCC_SPI1);
    rcc_periph_clock_enable(RCC_SPI2);

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

    while(1) {
        ;
    }

    return 0;
}

