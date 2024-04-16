# Default settings for flashing Arduino from another Arduino ISP
if (NOT MCU)
    set(MCU "atmega328p")
endif()
if (NOT PORT)
    set(PORT "/dev/cu.usbmodem14201")
endif()
if (NOT PROGRAMMER)
    set(PROGRAMMER "stk500v1")
endif()
if (NOT BAUD_RATE)
    set(BAUD_RATE 19200)
endif()

# Compiler flags
set(CMAKE_C_COMPILER "/usr/local/bin/avr-gcc")
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
set(HAVE_FLAG_SEARCH_PATHS_FIRST 0)
set(CMAKE_OSX_SYSROOT "")
# -Os optimize for size
set(CMAKE_C_FLAGS "-mmcu=${MCU} -Os")

cmake_minimum_required(VERSION 3.10)

project(avr-led)

add_executable(avr-led src/main.c src/delay.c src/sleep.c)

add_custom_command(
    TARGET avr-led POST_BUILD
    COMMAND avr-objcopy 
        -O ihex  
        -j .text 
        -j .data 
        $<TARGET_FILE:avr-led> $<TARGET_FILE:avr-led>.hex
    VERBATIM)

set(AVRDUDE_ARGS 
    -C /usr/local/etc/avrdude.conf 
    -v 
    -p ${MCU} 
    -c ${PROGRAMMER} 
    -P ${PORT} 
    -b ${BAUD_RATE})

add_custom_target(flash
    COMMAND avrdude ${AVRDUDE_ARGS}
        -U flash:w:$<TARGET_FILE:avr-led>.hex:i)

# Page 244 - Fuse Bits
add_custom_target(fuses
    COMMAND avrdude ${AVRDUDE_ARGS}
        -U hfuse:r:-:b
        -U lfuse:r:-:b)

# Page 25 - Clock Sources
# Page 244 - Fuse Low Byte
add_custom_target(use-internal-oscillator
    COMMAND avrdude ${AVRDUDE_ARGS}
        -U lfuse:w:0b11110010:m)