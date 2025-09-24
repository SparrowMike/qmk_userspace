// Copyright 2022 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H
#include "manna-harbour_miryoku.h"

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    } else {
        return OLED_ROTATION_180;
    }
    return rotation;
}

bool oled_task_user(){
    oled_set_brightness(1);

#if OLED_TIMEOUT > 0
    if (last_input_activity_elapsed() > OLED_TIMEOUT && last_led_activity_elapsed() > OLED_TIMEOUT) {
        return oled_off();
    } else {
        oled_on();
    }
#endif

    if (is_keyboard_master()) {
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state)) {
            case U_BASE:
                oled_write_P(PSTR("Base\n"), false);
                break;
            case U_NAV:
                oled_write_P(PSTR("Nav\n"), false);
                break;
            case U_MOUSE:
                oled_write_P(PSTR("Mouse\n"), false);
                break;
            case U_MEDIA:
                oled_write_P(PSTR("Media\n"), false);
                break;
            case U_NUM:
                oled_write_P(PSTR("Num\n"), false);
                break;
            case U_SYM:
                oled_write_P(PSTR("Sym\n"), false);
                break;
            case U_FUN:
                oled_write_P(PSTR("Fun\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undef\n"), false);
                break;
        }
        oled_write_P(PSTR("\n"), false);
    } else {
        oled_write_P(PSTR("KLOR\n"), false);
        oled_write_P(PSTR("Miryoku\n"), false);
    }

    return false;
}
#endif

// <<< Use Configuration Documentation (do not edit) >>>