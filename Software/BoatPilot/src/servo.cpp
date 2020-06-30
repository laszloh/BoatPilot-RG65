/**
 * @file servo.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-06-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include "servo.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

constexpr int periode = 20000;  // µs

Servo::Servo(rcc_periph_clken rcc, uint32_t port, uint16_t pin, uint32_t timer, tim_oc_id oc, uint32_t altFunction) {
    rcc_periph_clock_enable(rcc);
    rcc_periph_clock_enable(RCC_AFIO);

    // set up gpio
    gpio_set_mode(port, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, pin);
    gpio_clear(port, pin);
    gpio_primary_remap(0, altFunction);

    // setup output compare timer
    timer_disable_counter(timer);

    timer_set_oc_mode(timer, oc, TIM_OCM_PWM1);
    timer_enable_oc_output(timer, oc);
    timer_set_oc_value(timer, oc, 1000);

    timer_set_counter(timer, 0);
    timer_enable_counter(timer);
}

void Servo::initTimer(uint32_t timer) {
    timer_reset(timer);

    timer_set_mode(timer, TIM_CR1_CKD_CK_INT, 
        TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

    timer_set_prescaler(timer, ((rcc_apb1_frequency * 2) / 1000000));
    timer_enable_preload(timer);
    timer_continuous_mode(timer);

    // 20 ms interval
    timer_set_period(timer, periode);

    timer_enable_counter(timer);
}

void Servo::setServo(int position) {

}

uint32_t Servo::getServo(void) {

}

void Servo::setServoMs(int ms) {

}

uint32_t Servo::getServoMs(void) {

}
