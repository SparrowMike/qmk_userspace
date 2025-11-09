#include QMK_KEYBOARD_H
/* #include "../boards.h" */

#include "./klor.c"

#define HM_A LCTL_T(KC_A)
#define HM_S LALT_T(KC_S)
#define HM_D LGUI_T(KC_D)
#define HM_F LSFT_T(KC_F)

#define HM_J RSFT_T(KC_J)
#define HM_K RGUI_T(KC_K)
#define HM_L RALT_T(KC_L)
#define HM_SCLN RCTL_T(KC_SCLN)

enum {
    TD_RALT_CAPS,
};

enum layers {
    _BASE,
    _FIRST,
    _SECOND,
    _THIRD,
    _FOURTH
};

enum custom_keycodes {
    BK_TAB = SAFE_RANGE,
    QK_MYM_3,
    QK_MYM_4,
    QK_MYM_1,
    QK_MYM_2,
};

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
    MACRO_COMBO,
};

const uint16_t PROGMEM dot_slash_grv_combo[]  = {KC_DOT, KC_SLSH, COMBO_END};
const uint16_t PROGMEM angle_brackets_combo[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM m_comma_esc_combo[]    = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM esc_qw_combo[]  = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM l_semi_combo[]  = {HM_L, HM_SCLN, COMBO_END};
const uint16_t PROGMEM m_angle_combo[] = {KC_M, KC_COMM, COMBO_END};

const uint16_t PROGMEM cmd_z_combo[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM cmd_c_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM cmd_v_combo[] = {KC_C, KC_V, COMBO_END};

const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM we_combo[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM er_combo[] = {KC_E, KC_R, COMBO_END};

const uint16_t PROGMEM ui_combo[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM io_combo[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM op_combo[] = {KC_O, KC_P, COMBO_END};

const uint16_t PROGMEM ly_sec_combo[] = {KC_SPC, KC_BSPC, COMBO_END};
const uint16_t PROGMEM rf_combo[] = {KC_R, HM_F, COMBO_END};
const uint16_t PROGMEM uj_combo[] = {KC_U, HM_J, COMBO_END};
const uint16_t PROGMEM ik_combo[] = {KC_I, HM_K, COMBO_END};
const uint16_t PROGMEM ol_combo[] = {KC_O, HM_L, COMBO_END};

const uint16_t PROGMEM capword_combo[] = {KC_H, HM_J, COMBO_END};
const uint16_t PROGMEM macro_combo[] = {KC_7, KC_9, COMBO_END};

combo_t key_combos[] = {
    [ESC_QW]  = COMBO(esc_qw_combo, KC_ESC),
    [M_COMMA_ESC] = COMBO(m_comma_esc_combo, KC_ESC),
    [ANGLE_BRACKETS_TAB] = COMBO(angle_brackets_combo, KC_TAB),

    [DOT_SLASH_GRV]  = COMBO(dot_slash_grv_combo, KC_GRV),
    [L_SEMI_QUOTE]   = COMBO_ACTION(l_semi_combo),

    [CMD_Z] = COMBO_ACTION(cmd_z_combo),
    [CMD_C] = COMBO_ACTION(cmd_c_combo),
    [CMD_V] = COMBO_ACTION(cmd_v_combo),

    [QW] = COMBO(qw_combo, KC_LBRC),
    [WE] = COMBO(we_combo, KC_LCBR),
    [ER] = COMBO(er_combo, KC_LPRN),
    [UI] = COMBO(ui_combo, KC_RPRN),
    [IO] = COMBO(io_combo, KC_RCBR),
    [OP] = COMBO(op_combo, KC_RBRC),

    [LY_SEC] = COMBO(ly_sec_combo, MO(_SECOND)),
    [RF] = COMBO(rf_combo, KC_UNDS),
    [UJ] = COMBO(uj_combo, KC_MINS),
    [IK] = COMBO(ik_combo, KC_PLUS),
    [OL] = COMBO(ol_combo, KC_EQL),

    [CAPWORD] = COMBO(capword_combo, CW_TOGG),
    [MACRO_COMBO] = COMBO(macro_combo, MO(_THIRD)),
};

void register_combo(uint16_t keycode, bool pressed) {
    if (pressed) {
        register_code(KC_LGUI);
        register_code(keycode);
    } else {
        unregister_code(keycode);
        unregister_code(KC_LGUI);
    }
}

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
        case CMD_Z:
            register_combo(KC_Z, pressed);
            break;
        case CMD_C:
            register_combo(KC_C, pressed);
            break;
        case CMD_V:
            register_combo(KC_V, pressed);
            break;
        case L_SEMI_QUOTE:
            if (pressed) {
                register_code(KC_QUOT);
            } else {
                unregister_code(KC_QUOT);
            }
            break;
    }
}

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    switch (combo_index) {
        case MACRO_COMBO:
            return layer_state_is(_SECOND);
    }

    return true;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_RALT_CAPS] = ACTION_TAP_DANCE_DOUBLE(HM_K, KC_CAPS),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base Layer */
    [_BASE] = LAYOUT(
                 KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
      KC_TAB,    HM_A,    HM_S,    HM_D,    HM_F,    KC_G,                          KC_H,    HM_J,    HM_K,    HM_L,    HM_SCLN, KC_QUOT,
      KC_DEL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,    KC_MPLY,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                            MO(_SECOND), MO(_FIRST), KC_ENT,  KC_TRNS,    KC_TRNS,  KC_SPC, LT(_SECOND, KC_BSPC), MO(_SECOND)    ),

    [_FIRST] = LAYOUT(
                 KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
      KC_TRNS,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_MINS, KC_EQL,  KC_GRV,  KC_LBRC, KC_RBRC, KC_TRNS,
      KC_TRNS,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS,    KC_TRNS, KC_UNDS, KC_TRNS, KC_TILD, KC_PIPE, KC_BSLS, KC_TRNS,
                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_SECOND] = LAYOUT(
                 KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
      KC_TRNS,   KC_TRNS, KC_MUTE, KC_MPRV, KC_MNXT, KC_MPLY,                      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS,
      KC_TRNS,   RGB_TOG, RGB_RMOD,RGB_MOD, RGB_VAD, RGB_VAI, KC_TRNS,    KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU, BK_TAB,  KC_TRNS, KC_TRNS,
                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

    [_THIRD] = LAYOUT(
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, MO(_FOURTH), KC_TRNS
    ),

    [_FOURTH] = LAYOUT(
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
      KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_TRNS, QK_MYM_1,QK_MYM_3, QK_MYM_4,QK_MYM_2, KC_TRNS,
      KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, EE_CLR,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,
                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

void register_shift_tab(bool pressed) {
    if (pressed) {
        register_code(KC_LSFT);
        register_code(KC_TAB);
    } else {
        unregister_code(KC_TAB);
        unregister_code(KC_LSFT);
    }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    /* if (record->event.pressed) { */
    /*     switch (keycode) { */
    /*         case BK_TAB: */
    /*             register_shift_tab(record->event.pressed); */
    /*             return false; */
    /*         case QK_MYM_1: */
    /*             SEND_STRING(MACRO_Z SS_TAP(X_ENTER)); */
    /*             return false; */
    /*         case QK_MYM_2: */
    /*             SEND_STRING(MACRO_Z SS_TAP(X_ENTER) SS_DELAY(50) MACRO_B SS_TAP(X_ENTER)); */
    /*             return false; */
    /*         case QK_MYM_3: */
    /*             SEND_STRING(MACRO_B SS_DELAY(20) SS_TAP(X_ENTER)); */
    /*             return false; */
    /*         case QK_MYM_4: */
    /*             SEND_STRING(MACRO_A SS_DELAY(20) SS_TAP(X_ENTER)); */
    /*             return false; */
    /*     } */
    /* } */
    return true;
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
            case _BASE:
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
        }
    } else if (index == 1) {
        switch (get_highest_layer(layer_state)) {
            case _BASE:
                // Vertical scrolling
                if (clockwise) {
                    tap_code(KC_WH_D);
                } else {
                    tap_code(KC_WH_U);
                }
                break;
        }
    }
    return false;
}
