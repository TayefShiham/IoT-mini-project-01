/*
 * Copyright (C) 2013, 2014 INRIA
 *               2015 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_olimex_msp430_h2618
 *
 * @{
 *
 * @file
 * @brief       Basic definitions for the Olimex MSP430-H2618 board
 *
 * @author      Marian Buschsieweke <marian.buschsieweke@posteo.net>
 */

#ifndef BOARD_H
#define BOARD_H

#include "cpu.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Define the CPU model for the <msp430.h>
 */
#ifndef __MSP430F2618__
#define __MSP430F2618__
#endif

/**
 * @name    Xtimer configuration
 * @{
 */
#define XTIMER_WIDTH                (16)
#define XTIMER_BACKOFF              (40)
/** @} */

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* BOARD_H */
