#ifndef FAICA_H
#define FAICA_H

#include <furi.h>
#include <gui/gui.h>
#include <input/input.h>

typedef struct {
    ViewDispatcher* view_dispatcher;
    Gui* gui;
    int selected;
    bool running;
} AppMenu;

void app_menu_init(void);

#endif // FAICA_H
