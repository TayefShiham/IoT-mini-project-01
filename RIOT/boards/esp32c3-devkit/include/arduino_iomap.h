/*
 * Copyright (C)  2022 Gunar Schorcht
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_esp32c3_devkit
 * @{
 *
 * @file
 * @brief       Mapping from MCU pins to Arduino pins
 *
 * @author      Gunar Schorcht <gunar@schorcht.net>
 */

#ifndef ARDUINO_IOMAP_H
#define ARDUINO_IOMAP_H

#include "periph/gpio.h"
#include "periph/adc.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name   Mapping of MCU pins to Arduino pins
 * @{
 */
#define ARDUINO_PIN_0       GPIO20  /**< Arduino pin 0 (RxD) */
#define ARDUINO_PIN_1       GPIO21  /**< Arduino pin 1 (TxD) */
#if !defined(MODULE_ESP_RTC_TIMER_32K)
#define ARDUINO_PIN_2       GPIO0   /**< Arduino pin 2 */
#define ARDUINO_PIN_3       GPIO1   /**< Arduino pin 3 (PWM) */
#endif
#define ARDUINO_PIN_5       GPIO3   /**< Arduino pin 5 (PWM) */
#define ARDUINO_PIN_6       GPIO4   /**< Arduino pin 6 (PWM) */
#define ARDUINO_PIN_7       GPIO8   /**< Arduino pin 7 */

#define ARDUINO_PIN_10      GPIO10  /**< Arduino pin 10 (CS0 / PWM)  */
#define ARDUINO_PIN_11      GPIO7   /**< Arduino pin 11 (MOSI / PWM) */
#define ARDUINO_PIN_12      GPIO2   /**< Arduino pin 12 (MISO) */
#define ARDUINO_PIN_13      GPIO6   /**< Arduino pin 13 (SCK)  */

/* analog pins as digital pins: */
#define ARDUINO_PIN_14  GPIO0       /**< Arduino pin A0 */
#if !defined(MODULE_ESP_RTC_TIMER_32K)
#define ARDUINO_PIN_15      GPIO1   /**< Arduino pin A1 */
#endif
#define ARDUINO_PIN_16      GPIO2   /**< Arduino pin A2 */
#define ARDUINO_PIN_17      GPIO3   /**< Arduino pin A3 */

#define ARDUINO_PIN_18      GPIO5   /**< Arduino pin A4 (SDA) */
#define ARDUINO_PIN_19      GPIO4   /**< Arduino pin A5 (SCL) */

#define ARDUINO_PIN_LAST    19
/** @} */

/**
 * @name    Aliases for analog pins
 * @{
 */
#define ARDUINO_PIN_A0      ARDUINO_PIN_14
#define ARDUINO_PIN_A1      ARDUINO_PIN_15
#define ARDUINO_PIN_A2      ARDUINO_PIN_16
#define ARDUINO_PIN_A3      ARDUINO_PIN_17

#define ARDUINO_PIN_A4      ARDUINO_PIN_18
#define ARDUINO_PIN_A5      ARDUINO_PIN_19
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* ARDUINO_IOMAP_H */
/** @} */
