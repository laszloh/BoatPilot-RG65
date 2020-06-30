/**
 * @file servo.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-06-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#pragma once
#include <stdint.h>
#include <libopencm3/stm32/rcc.h>




class Servo {
public:
    Servo(rcc_periph_clken rcc, uint32_t port, uint16_t pin, uint32_t timer, tim_oc_id oc, uint32_t altFunction);
    static void initTimer(uint32_t timer);

    void setServo(int position);
    uint32_t getServo(void);
    void setServoMs(int ms);
    uint32_t getServoMs(void);

private:
    int milliseconds;
};
