#include <furi.h>
#include <ble/ble.h>
#include "keycode_mapper.h"
#include "storage.h"

void start_bluetooth_monitoring() {
    furi_log("Starting Bluetooth monitoring...");
    FuriHalBle.init();

    ble_device_t* keyboard = ble_find_device_by_type(HID_KEYBOARD_TYPE);
    if (!keyboard) {
        furi_log("No BLE keyboard found.");
        return;
    }

    ble_connect_device(keyboard);

    while (ble_is_connected(keyboard)) {
        uint8_t keycode[8];
        if (ble_receive_hid_report(keyboard, keycode, sizeof(keycode))) {
            char character = map_keycode_to_char(keycode);
            furi_log("Keystroke: %c", character);
            save_keystroke_to_storage(character);
        }
    }

    ble_disconnect_device(keyboard);
    furi_log("Bluetooth monitoring stopped.");
}
