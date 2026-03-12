# Replace TMDS with 10 bit UART (same baud rate):
# add_definitions(-DDVI_SERIAL_DEBUG=1)
# add_definitions(-DRUN_FROM_CRYSTAL)

add_executable(hello_dvi
	main.c
)

target_compile_options(hello_dvi PRIVATE -Wall)

target_compile_definitions(hello_dvi PRIVATE
	DVI_DEFAULT_SERIAL_CONFIG=${DVI_DEFAULT_SERIAL_CONFIG}
	PICO_PIO_USE_GPIO_BASE=1
)

pico_enable_stdio_uart(hello_dvi 1)
pico_enable_stdio_usb(hello_dvi  0)

target_link_libraries(hello_dvi
	pico_stdlib
	pico_multicore
	pico_util
	libdvi
)

# create map/bin/hex file etc.
pico_add_extra_outputs(hello_dvi)
