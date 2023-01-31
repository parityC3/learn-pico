cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(learn_pico C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

## irq_wdt ##
add_executable(irq_wdt
        irq_wdt.c
        )

# pull in common dependencies
target_link_libraries(irq_wdt
    pico_stdlib
    pico_multicore
    )

# enable usb output, disable uart output
pico_enable_stdio_usb(irq_wdt 1)
pico_enable_stdio_uart(irq_wdt 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(irq_wdt)


## measure ##
add_executable(measure
        measure.c
        )

# pull in common dependencies
target_link_libraries(measure
    pico_stdlib
    pico_time
    )

# enable usb output, disable uart output
pico_enable_stdio_usb(measure 1)
pico_enable_stdio_uart(measure 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(measure)