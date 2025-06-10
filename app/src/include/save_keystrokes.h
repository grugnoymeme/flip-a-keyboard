#ifndef SAVE_KEYSTROKES_H
#define SAVE_KEYSTROKES_H

#include <stdint.h>

/**
 * Salva un singolo carattere nel file keystrokes.txt sulla SD.
 * @param character Il carattere da salvare (es. 'a', 'B', '1', ecc.)
 */
void save_keystroke_to_storage(char character);

#endif // SAVE_KEYSTROKES_H
