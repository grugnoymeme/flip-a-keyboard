#include <stdint.h>

char map_keycode_to_char(uint8_t* keycode) {
    if (keycode[0] >= 4 && keycode[0] <= 29) {
        return 'a' + (keycode[0] - 4); // a-z
    } else if (keycode[0] >= 30 && keycode[0] <= 38) {
        return '1' + (keycode[0] - 30); // 1-9
    } else if (keycode[0] == 39) {
        return '0'; // keycode 39 è 0
    }
    return '?'; // carattere non riconosciuto
}
