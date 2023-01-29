/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"

struct repeating_timer timer;

bool repeating_timer_callback(struct repeating_timer *t) {
    static bool led_state = true;
    gpio_put(PICO_DEFAULT_LED_PIN, led_state);
    led_state = !led_state;
    printf("Core%u\n", get_core_num());
    return true;
}

void core1_entry() {
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, true);
    while (true) {
        printf("Core%u\n", get_core_num());
        sleep_ms(1000);
    }
}

int main() {
    set_sys_clock_khz(250000, true);
    stdio_init_all();

    multicore_launch_core1(core1_entry);
    add_repeating_timer_ms(500, repeating_timer_callback, NULL, &timer);
    while(true) {}
    return 0;
}
