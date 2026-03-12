#include "f_util.h"
#include "ff.h"
#include "pico/stdlib.h"
#include "rtc.h"
//
#include "hw_config.h"

void setup() {
    Serial.begin(115200); 
    delay(2000);

    time_init();
    char buffer[64]; 

    Serial.println("Hello, world!");

    // See FatFs - Generic FAT Filesystem Module, "Application Interface",
    // http://elm-chan.org/fsw/ff/00index_e.html
    sd_card_t *pSD = sd_get_by_num(0);
    FRESULT fr = f_mount(&pSD->fatfs, pSD->pcName, 1);
    if (FR_OK != fr) panic("f_mount error: %s (%d)\n", FRESULT_str(fr), fr);
    FIL fil;
    const char* const filename = "filename.txt";
    fr = f_open(&fil, filename, FA_OPEN_APPEND | FA_WRITE);
    if (FR_OK != fr && FR_EXIST != fr)
        panic("f_open(%s) error: %s (%d)\n", filename, FRESULT_str(fr), fr);
    if (f_printf(&fil, "Hello, world!\n") < 0) {
        Serial.println("f_printf failed\n");
    }
    fr = f_close(&fil);
    if (FR_OK != fr) {
        sprintf(buffer, "f_close error: %s (%d)\n", FRESULT_str(fr), fr);
        Serial.println(buffer);
    }
    f_unmount(pSD->pcName);

    Serial.println("Goodbye, world!");
}

void loop() {
  // nothing happens after setup finishes.
  delay(1000); 
}