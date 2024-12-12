char map_keycode_to_char(uint8_t* keycode) {
    if (keycode[0] >= 4 && keycode[0] <= 29) {
        return 'a' + (keycode[0] - 4); // Map 'a' to 'z'
    } else if (keycode[0] >= 30 && keycode[0] <= 38) {
        return '0' + (keycode[0] - 30); // Map '1' to '9' and '0'
    }
    return '?'; // Unknown key
}
