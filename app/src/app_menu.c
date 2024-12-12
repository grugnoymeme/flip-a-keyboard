#include <furi.h>
#include <gui/gui.h>
#include "bluetooth_monitor.h"
#include "usb_monitor.h"

void main_menu_callback(uint32_t index) {
    switch (index) {
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
    ViewPort* viewport = view_port_alloc();
    Gui* gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, viewport, GuiLayerFullscreen);

    const char* menu_items[] = {"Bluetooth Monitoring", "USB Monitoring"};
    uint32_t selected_option = gui_show_menu("Keystroke Monitor", menu_items, 2);
    main_menu_callback(selected_option);

    view_port_free(viewport);
    furi_record_close(RECORD_GUI);
}
