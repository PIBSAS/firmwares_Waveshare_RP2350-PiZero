set(PICO_BOARD_HEADER_DIRS ${CMAKE_CURRENT_LIST_DIR}/../../boards)
set(PICO_BOARD waveshare_rp2350_pizero)

cmake_minimum_required(VERSION 3.13)
include (pico_sdk_import.cmake)
project(pio_usb)

pico_sdk_init()

# add pico-pio-usb library for examples
set(PICO_PIO_USB_DIR "${CMAKE_CURRENT_LIST_DIR}/../")
# the second argument to add_subdirectory is needed here because this isn't
# a subdirectory, it's out of tree.
add_subdirectory(${PICO_PIO_USB_DIR} pico_pio_usb)

add_subdirectory(usb_device)
add_subdirectory(host_hid_to_device_cdc)
