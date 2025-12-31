// Cornie OLED and animation implementation
#include "mike.h"

// Animation includes
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

// Animation-specific process_record_user logic
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
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
