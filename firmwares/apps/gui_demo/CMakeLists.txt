# Replace TMDS with 10 bit UART (same baud rate):
# add_definitions(-DDVI_SERIAL_DEBUG=1)
# add_definitions(-DRUN_FROM_CRYSTAL)

add_executable(gui_demo
	main.c
)

target_compile_options(gui_demo PRIVATE -Wall)

target_compile_definitions(gui_demo PRIVATE
	DVI_DEFAULT_SERIAL_CONFIG=${DVI_DEFAULT_SERIAL_CONFIG}
	DVI_VERTICAL_REPEAT=1
	DVI_N_TMDS_BUFFERS=3
	PICO_PIO_USE_GPIO_BASE=1
)

pico_enable_stdio_uart(gui_demo 1)
pico_enable_stdio_usb(gui_demo  0)

target_link_libraries(gui_demo
	pico_stdlib
	pico_multicore
	libdvi
	libgui
)

# create map/bin/hex file etc.
pico_add_extra_outputs(gui_demo)
