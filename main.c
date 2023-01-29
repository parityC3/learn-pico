/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/watchdog.h"

bool repeating_timer_callback(struct repeating_timer *t) {
    static bool led_state = true;
    watchdog_update();
    gpio_put(PICO_DEFAULT_LED_PIN, led_state);
    led_state = !led_state;
    return true;
}

void core1_entry() {
    alarm_pool_t *pool_core1 = alarm_pool_create(2, 16);
    struct repeating_timer timer;

    alarm_pool_add_repeating_timer_ms(pool_core1, 500, repeating_timer_callback, NULL, &timer);

    watchdog_enable(0x7fffff, true); // 8.3 sec

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, true);
    while (true) {
        printf("%s: Core%u\n", __func__, get_core_num());
    }
}

int main() {
    set_sys_clock_khz(250000, true);
    stdio_init_all();

    multicore_launch_core1(core1_entry);
    while(true) {
        printf("%s: Core%u\n", __func__, get_core_num());
    }
    return 0;
}
