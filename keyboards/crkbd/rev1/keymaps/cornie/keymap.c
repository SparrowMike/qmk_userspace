#include QMK_KEYBOARD_H

/* #include "../boards.h" */

#ifdef INCLUDE_LAYERS
#   include "layers.h"
#endif

#ifdef INCLUDE_LOGO
#   include "corne_logo.h"
#endif

#ifdef INCLUDE_CAT
#   include "bongo.c"
#endif

#ifdef INCLUDE_OCEAN
#   include "ocean_dream.c"
#endif

#ifdef INCLUDE_ARASAKA
#   include "arasaka.c"
#endif

#ifdef INCLUDE_LUNA
#   include "luna.c"
#endif

#ifdef INCLUDE_BARS
#   include "music-bars.c"
#endif

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
    _FOURTH,
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
    [TD_RALT_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_RALT, KC_CAPS),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_TRNS, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                           KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,   KC_TRNS,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_TRNS, HM_A,    HM_S,    HM_D,    HM_F,    KC_G,                           KC_H,    HM_J,    HM_K,    HM_L,   HM_SCLN,  KC_TRNS,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_TRNS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                           KC_N,    KC_M,  KC_COMM,  KC_DOT,  KC_SLSH,  KC_TRNS,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                   MO(_SECOND),MO(_FIRST),KC_ENT,   KC_SPC, LT(_SECOND, KC_BSPC), MO(_SECOND)
                                   //`--------------------------'  `--------------------------'

        ),

    [_FIRST] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_TRNS, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                           KC_MINS, KC_EQL,  KC_GRV,  KC_LBRC, KC_RBRC, KC_TRNS,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_TRNS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                           KC_UNDS, KC_TRNS, KC_TILD, KC_PIPE, KC_BSLS, KC_TRNS,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_TRNS, KC_TRNS,  KC_TRNS,     KC_TRNS, KC_TRNS, KC_ESC
                                            //`--------------------------'  `--------------------------'

    ),

    [_SECOND] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                          KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_TRNS, KC_TRNS, KC_MUTE, KC_MPRV, KC_MNXT, KC_MPLY,                        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TRNS, KC_TRNS,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_TRNS, RGB_TOG, RGB_RMOD,RGB_MOD, RGB_VAD, RGB_VAI,                        KC_TRNS, KC_VOLD, KC_VOLU, BK_TAB,  KC_TRNS, KC_TRNS,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS
                                            //`--------------------------'  `--------------------------'
    ),

    [_THIRD] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_TRNS, KC_TRNS,  KC_TRNS,     KC_TRNS, MO(_FOURTH), KC_TRNS
                                            //`--------------------------'  `--------------------------'
    ),

    [_FOURTH] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, QK_MYM_1,QK_MYM_3,QK_MYM_4,QK_MYM_2,KC_TRNS,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS
                                            //`--------------------------'  `--------------------------'
    ),
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

    // Handle other cases that need both press and release events
    switch (keycode) {
        case BK_TAB:
            register_shift_tab(record->event.pressed);
            return false;
        case KC_LCTL:
        case KC_RCTL:
#ifdef INCLUDE_OCEAN
            is_calm = (record->event.pressed) ? true : false;
#endif
#ifdef INCLUDE_LUNA
            if (record->event.pressed) {
                isSneaking = true;
            } else {
                isSneaking = false;
            }
#endif
            break;
        case KC_SPC:
#ifdef INCLUDE_LUNA
            if (record->event.pressed) {
                isJumping = true;
                showedJump = false;
            } else {
                isJumping = false;
            }
#endif
            break;
    }

    return true;
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
#if defined(INCLUDE_ARASAKA) || defined(INCLUDE_OCEAN)
    return OLED_ROTATION_270;
#else
    return OLED_ROTATION_180;
#endif
    }
    return rotation;
}

bool oled_task_user(){
    oled_set_brightness(1);

#if OLED_TIMEOUT > 0
    /* the animation prevents the normal timeout from occuring */
    if (last_input_activity_elapsed() > OLED_TIMEOUT && last_led_activity_elapsed() > OLED_TIMEOUT) {
        return oled_off();
    } else {
        oled_on();
    }
#endif

    if (is_keyboard_master()) {

#   ifdef INCLUDE_LAYERS
        switch (get_highest_layer(layer_state)) {
            case _BASE:
                oled_write_raw_P(qwerty_img, sizeof(qwerty_img));
                break;
            case _FIRST:
                oled_write_raw_P(lower_img, sizeof(lower_img));
                break;
            case _SECOND:
                oled_write_raw_P(raise_img, sizeof(raise_img));
                break;
            case _THIRD:
                oled_write_raw_P(adjust_img, sizeof(adjust_img));
                break;
        }
#   endif

#ifdef INCLUDE_LOGO
        oled_set_cursor(0, 12);
        oled_write_raw_P(corne_logo, sizeof(corne_logo));
#endif

#ifdef INCLUDE_LUNA
        led_usb_state = host_keyboard_led_state();
        render_luna(0, 13);
#endif

        // Display LED status
        // led_t led_state = host_keyboard_led_state();
        // oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
        // oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
        // oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
    } else {

#   ifdef INCLUDE_CAT
        draw_bongo(false);
#   endif

#   ifdef INCLUDE_OCEAN
        render_stars();
#   endif

#   ifdef INCLUDE_ARASAKA
        arasaka_draw();
#   endif

#   ifdef INCLUDE_BARS
        oled_render_anim();
#   endif
    }

    return false;
}
#endif
