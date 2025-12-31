// Combo key sequences
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

// Combo definitions array
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
};

// Helper function for CMD combos
void register_combo(uint16_t keycode, bool pressed) {
    if (pressed) {
        register_code(KC_LGUI);
        register_code(keycode);
    } else {
        unregister_code(keycode);
        unregister_code(KC_LGUI);
    }
}

// Process combo events
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
