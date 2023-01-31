#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/time.h"

int main() {
    stdio_init_all();

    while (true) {
        absolute_time_t from = get_absolute_time();
        for (volatile int i = 0; i < 125000000; i++);
        absolute_time_t to = get_absolute_time();
        printf("time: %lu\n", absolute_time_diff_us(from, to));
    }

    return 0;
}