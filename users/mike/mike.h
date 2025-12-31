#pragma once

#include QMK_KEYBOARD_H

// Home row mods
#define HM_A LCTL_T(KC_A)
#define HM_S LALT_T(KC_S)
#define HM_D LGUI_T(KC_D)
#define HM_F LSFT_T(KC_F)

#define HM_J RSFT_T(KC_J)
#define HM_K RGUI_T(KC_K)
#define HM_L RALT_T(KC_L)
#define HM_SCLN RCTL_T(KC_SCLN)

// Shared layer definitions
enum layers {
    _BASE,
    _FIRST,
    _SECOND,
};

// Custom keycodes
enum custom_keycodes {
    BK_TAB = SAFE_RANGE,
};

// Combo events
enum combo_events {
    DOT_SLASH_GRV,
    L_SEMI_QUOTE,
    ESC_QW,
    COMMA_DOT_ESC,
    M_COMMA_ESC,
    OP_CAPS,
    CMD_Z,
    CMD_C,
    CMD_V,
    ANGLE_BRACKETS_TAB,
    QW,
    WE,
    ER,
    UI,
    IO,
    OP,
    LY_SEC,
    RF,
    UJ,
    IK,
    OL,
    CAPWORD,
};

// Helper functions
void register_shift_tab(bool pressed);

// Keyboard-specific process_record handler (implement in keyboard .c file)
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);