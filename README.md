# firmwares_Waveshare_RP2350-PiZero

- [MicroPython 1.26](firmwares/MicroPython_WAVESHARE-RP2350-20250807-v1.26.0-16MB/WAVESHARE-RP2350-20250807-v1.26.0-16MB.uf2)
- [picosms Plus](firmwares/picosmsPlus/picosmsPlus_WaveShareRP2350PiZero_arm_piousb.uf2)
-[Waveshare RP2350-PiZero Examples C, Python, Arduino](firmwares/RP2350-PiZero/)
  - [Arduino DVI](firmwares/RP2350-PiZero/Arduino/01-DVI/hello_dvi/)
  - [Arduino USB](firmwares/RP2350-PiZero/Arduino/02-USB/device_info/)
  - [Arduino MicroSD](firmwares/RP2350-PiZero/Arduino/03-MicroSD/)
  - [Python MicroSD](firmwares/RP2350-PiZero/Python/WAVESHARE_RP2350_PIZERO.uf2)
  - [C DVI](firmwares/RP2350-PiZero/C/uf2/01-DVI.uf2)
  - [C USB](firmwares/RP2350-PiZero/C/uf2/02-USB.uf2)
  - [C MicroSD](firmwares/RP2350-PiZero/C/uf2/03-MicroSD.uf2)
  - [C boards](firmwares/RP2350-PiZero/C/boards/waveshare_rp2350_pizero.h) Add this board fefinition to Pico SDK:
    ```
    - sdk/N.N.N/src/boards/include/boards/waveshare_rp2350_pizero.h
    ```
    Where N.N.N is the SDK version. This way we can choose our board from a list on [VSCode Raspberry Pi Pico Extension](https://marketplace.visualstudio.com/items?itemName=raspberry-pi.raspberry-pi-pico).
- [picosms Plus](firmwares/piconesPlus/piconesPlus_WaveShareRP2350PiZero_arm_piousb.uf2)
