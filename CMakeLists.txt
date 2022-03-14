cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(pico-clock-project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(pico-clock
	main.cpp
	Terminal.cpp
	Terminal.h
	LCD.cpp
	LCD.h
	)

target_link_libraries(pico-clock pico_stdlib hardware_i2c)

pico_enable_stdio_usb(pico-clock 0)
pico_enable_stdio_uart(pico-clock 1)

pico_add_extra_outputs(pico-clock)
