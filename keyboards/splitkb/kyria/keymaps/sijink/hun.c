#include "hun.h"
#include "global.h"
#include "action_util.h"
#include QMK_KEYBOARD_H

bool process_hun_macros(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_RSFT || keycode == KC_LSFT) {
        return true;
    }

    uint8_t mods = get_mods();
    uint8_t oneshot_mods = get_oneshot_mods();
    bool shifted = (mods & MOD_MASK_SHIFT) | (oneshot_mods & MOD_MASK_SHIFT);

    clear_mods();
    clear_oneshot_mods();

    const char *letter = NULL;

    switch(keycode) {
        case A_ACUT:
        case E_ACUT:
        case I_ACUT:
        case O_ACUT:
        case U_ACUT:
            SEND_STRING(SIJ_ACUTE);
            break;
        case O_UMLAU:
        case U_UMLAU:
            SEND_STRING(SIJ_UMLAUT);
            break;
        case O_DACUT:
        case U_DACUT:
            SEND_STRING(SIJ_DACUTE);
            break;
    }

    switch(keycode) {
        case A_ACUT:
            letter = shifted ? "A" : "a";
            break;
        case E_ACUT:
            letter = shifted ? "E" : "e";
            break;
        case I_ACUT:
            letter = shifted ? "I" : "i";
            break;
        case O_ACUT:
        case O_UMLAU:
        case O_DACUT:
            letter = shifted ? "O" : "o";
            break;
        case U_ACUT:
        case U_UMLAU:
        case U_DACUT:
            letter = shifted ? "U" : "u";
            break;
    }

    if(letter) {
        add_mods(mods);
        send_string(letter);
    }

    layer_off(_HUN);

    return false;
}
