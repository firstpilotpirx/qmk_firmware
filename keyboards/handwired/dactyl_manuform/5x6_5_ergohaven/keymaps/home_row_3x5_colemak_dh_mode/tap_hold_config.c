#include QMK_KEYBOARD_H

static uint16_t last_pressed_keycode;
static keypos_t last_pressed_key;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        last_pressed_keycode = keycode;
        last_pressed_key = record->event.key;
    }
    return true;
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_A):
        case LALT_T(KC_R):
        case LSFT_T(KC_S):
        case LGUI_T(KC_T):
        case RGUI_T(KC_N):
        case RSFT_T(KC_E):
        case RALT_T(KC_I):
        case RCTL_T(KC_O): {
            bool held_on_left = record->event.key.row < 6;
            bool other_on_left = last_pressed_key.row < 6;
            if (held_on_left != other_on_left) {
                return true;
            }
            if (!IS_QK_MOD_TAP(last_pressed_keycode)) {
                return true;
            }
            return false;
        }
        default:
            return true;
    }
}
