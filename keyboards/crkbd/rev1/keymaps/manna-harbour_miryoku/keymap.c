// Copyright 2022 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

// Miryoku Layout with OLED Animations

#include QMK_KEYBOARD_H
#include "manna-harbour_miryoku.h"

// Animation includes
#ifdef INCLUDE_LAYERS
#   include "./animation/layers.h"
#endif

#ifdef INCLUDE_LOGO
#   include "./animation/corne_logo.h"
#endif

#ifdef INCLUDE_CAT
#   include "./animation/bongo.c"
#endif

#ifdef INCLUDE_OCEAN
#   include "./animation/ocean_dream.c"
#endif

#ifdef INCLUDE_ARASAKA
#   include "./animation/arasaka.c"
#endif

#ifdef INCLUDE_LUNA
#   include "./animation/luna.c"
#endif

#ifdef INCLUDE_BARS
#   include "./animation/music-bars.c"
#endif

// OLED Animation Functions
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
            case U_BASE:
                oled_write_raw_P(qwerty_img, sizeof(qwerty_img));
                break;
            case U_NAV:
                oled_write_raw_P(lower_img, sizeof(lower_img));
                break;
            case U_MOUSE:
                oled_write_raw_P(raise_img, sizeof(raise_img));
                break;
            case U_MEDIA:
                oled_write_raw_P(adjust_img, sizeof(adjust_img));
                break;
            default:
                oled_write_raw_P(qwerty_img, sizeof(qwerty_img));
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

// <<< Use Configuration Documentation (do not edit) >>>