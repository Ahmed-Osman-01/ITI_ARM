/*
 * LED_config.c
 *
 *  Created on: Feb 17, 2024
 *      Author: Osman
 */

#include "LIB/STD_TYPES.h"
#include "HAL/LED/LED.h"
#include "MCAL/GPIO/GPIO.h "

const LED_Config_t Leds[_LED_NUM] = {
    [LED_ONE] = {
        .Port = GPIO_PORT_C,
        .Pin = GPIO_PIN_13,
        .Connection = LED_CONNECTION_REVERSE,
        .InitState = LED_STATE_OFF,
    },
    [LED_TWO] = {
        .Port = GPIO_PORT_A,
        .Pin = GPIO_PIN_0,
        .Connection = LED_CONNECTION_FORWARD,
        .InitState = LED_STATE_OFF,
    },
};