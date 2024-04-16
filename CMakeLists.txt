set(CMAKE_C_COMPILER "/usr/local/bin/avr-gcc")
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
set(HAVE_FLAG_SEARCH_PATHS_FIRST 0)
set(CMAKE_OSX_SYSROOT "")
set(CMAKE_C_FLAGS "-mmcu=atmega328p")

cmake_minimum_required(VERSION 3.10)

project(avr-led)

add_executable(avr-led src/main.c src/delay.c)

add_custom_command(
    TARGET avr-led POST_BUILD
    COMMAND avr-objcopy 
        -O ihex  
        -j .text 
        -j .data 
        $<TARGET_FILE:avr-led> $<TARGET_FILE:avr-led>.hex
    VERBATIM)

add_custom_target(flash
    COMMAND avrdude 
        -C /usr/local/etc/avrdude.conf 
        -v 
        -p atmega328p 
        -c stk500v1 
        "-P/dev/cu.usbmodem14201" 
        -b 19200 
        -U lfuse:r:-:h)