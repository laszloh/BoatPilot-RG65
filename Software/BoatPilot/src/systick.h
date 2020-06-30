/**
 * @file systick.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2020-06-24
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#pragma once
#include <stdint.h>

void systick_setup(void);
uint64_t millis(void);
void delayMs(uint64_t duration);
