#include "faica.h"
#include <furi_hal.h>
#include <storage/storage.h>
#include <furi_log.h>

void save_keystroke_to_storage(char character);

static void start_usb_keylogger(void);
static void start_bluetooth_keylogger(void);

static AppMenu app;

static void view_menu_callback(Canvas* canvas, void* ctx) {
    canvas_clear(canvas);

    canvas_draw_str_aligned(canvas, 64, 10, AlignCenter, "Scegli modalità:");

    // Opzioni menu
    for(int i = 0; i < 3; i++) {
        if(i == app.selected) {
            canvas_draw_str_aligned(canvas, 64, 30 + i*20, AlignCenter, i == 0 ? "> USB Keylogger" : (i == 1 ? "> Bluetooth Keylogger" : "> Esci"));
        } else {
            canvas_draw_str_aligned(canvas, 64, 30 + i*20, AlignCenter, i == 0 ? "  USB Keylogger" : (i == 1 ? "  Bluetooth Keylogger" : "  Esci"));
        }
    }
}

static void keylogger_input_callback(InputEvent* event, void* ctx) {
    if(event->type == InputTypeShort) {
        switch(event->key) {
            case InputKeyUp:
                if(app.selected > 0) app.selected--;
                break;
            case InputKeyDown:
                if(app.selected < 2) app.selected++;
                break;
            case InputKeyOk:
                if(app.selected == 0) {
                    start_usb_keylogger();
                } else if(app.selected == 1) {
                    start_bluetooth_keylogger();
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
        furi_delay_ms(100);
    }

    gui_remove_view(app.gui, view_dispatcher_get_view(app.view_dispatcher));
    view_dispatcher_remove_view(app.view_dispatcher, view);
    view_free(view);
    view_dispatcher_free(app.view_dispatcher);
    furi_record_close(RECORD_GUI);
}


static void start_usb_keylogger(void) {
    furi_log_d("Keylogger", "USB keylogger avviato");


    bool running = true;
    while(running) {
        InputEvent event;
        if(furi_hal_input_get(&event, 100)) {
            if(event.type == InputTypeShort && event.key == InputKeyBack) {
                running = false;
            }
        }
    }

    furi_log_d("Keylogger", "USB keylogger terminato");
}

static void start_bluetooth_keylogger(void) {
    furi_log_d("Keylogger", "Bluetooth keylogger avviato");


    bool running = true;
    while(running) {
        // Simulazione input per uscire
        InputEvent event;
        if(furi_hal_input_get(&event, 100)) {
            if(event.type == InputTypeShort && event.key == InputKeyBack) {
                running = false;
            }
        }
    }

    furi_log_d("Keylogger", "Bluetooth keylogger terminato");
}
