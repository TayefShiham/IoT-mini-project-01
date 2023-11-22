/*
 * Copyright (C) 2013 Freie Universität Berlin
 *               2015 Kaspar Schleiser <kaspar@schleiser.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     sys_shell_commands
 * @{
 *
 * @file
 * @brief       Shell commands for random generators
 *
 * @author      Christian Mehlis <mehlis@inf.fu-berlin.de>
 * @author      Kaspar Schleiser <kaspar@schleiser.de>
 * @}
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "random.h"
#include "shell.h"

#include "ztimer.h"

static int _random_init(int argc, char **argv)
{
    int initval;

    if (argc == 1) {
        if (IS_USED(MODULE_ZTIMER_USEC)) {
            initval = ztimer_now(ZTIMER_USEC);
            printf("PRNG initialized to current time: %d\n", initval);
        }
        else {
            puts("xtimer module not compiled in, can't initialize by time.\n"
                 "Please provide a seed.\n");
            return 1;
        }
    }
    else {
        initval = atoi(argv[1]);
        printf("PRNG initialized given value: %d\n", initval);
    }

    random_init(initval);

    return 0;
}

SHELL_COMMAND(random_init, "initializes the PRNG", _random_init);

static int _random_get(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    printf("%" PRIu32 "\n", random_uint32());

    return 0;
}

SHELL_COMMAND(random_get, "returns 32 bit of pseudo randomness", _random_get);
