#include "mike.h"

void register_shift_tab(bool pressed) {
    if (pressed) {
        register_code(KC_LSFT);
        register_code(KC_TAB);
    } else {
        unregister_code(KC_TAB);
        unregister_code(KC_LSFT);
    }
}

// Shared process_record_user implementation
// Handles common keycodes, then delegates to keyboard-specific process_record_keymap
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case BK_TAB:
            register_shift_tab(record->event.pressed);
            return false;
    }

    // Handle keyboard-specific keycodes (animations, etc.)
    return process_record_keymap(keycode, record);
}
