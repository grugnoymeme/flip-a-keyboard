#include <furi.h>
#include <gui/gui.h>
#include <gui/modules/submenu.h>
#include "app_menu.h"
#include "bluetooth_monitor.h"
#include "usb_monitor.h"
#include "save_keystrokes.h"

void app_menu_callback(void* context, uint32_t index) {
    switch(index) {
        case 0:
            start_bluetooth_monitoring();
            break;
        case 1:
            start_usb_monitoring();
            break;
        default:
            furi_log("Invalid menu option");
            break;
    }
}

void app_menu_init() {
    Submenu* submenu = submenu_alloc();
    submenu_add_item(submenu, "Bluetooth Monitoring", 0, app_menu_callback, NULL);
    submenu_add_item(submenu, "USB Monitoring", 1, app_menu_callback, NULL);

    ViewPort* viewport = submenu_get_view_port(submenu);
    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, viewport, GuiLayerFullscreen);

    while(1) {
        furi_delay_ms(100);
    }

    gui_remove_view_port(gui, viewport);
    submenu_free(submenu);
    furi_record_close(RECORD_GUI);
}
