/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdint.h>
#include "action_util.h"
#include "modifiers.h"
#include "quantum.h"
#include QMK_KEYBOARD_H
#include "oneshot.h"

enum layers {
    _COLEMAK_DH = 0,
    _QWERTY,
    _NAV,
    _SYM,
    _HUN,
    _NUM,
    _MOUSE,
    _ADJUST,
};

enum keycodes {
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_GUI,
    A_ACUT,
    E_ACUT,
    I_ACUT,
    O_ACUT,
    O_DACUT,
    O_UMLAU,
    U_ACUT,
    U_DACUT,
    U_UMLAU
};


// Aliases for readability
#define QWERTY   DF(_QWERTY)
#define COLEMAK  DF(_COLEMAK_DH)

#define QUOTNAV  LT(_NAV, KC_QUOT)
#define NAV      TL_LOWR
#define SYM      TL_UPPR
#define HUN      MO(_HUN)
#define NUM      MO(_NUM)
#define MOUSE    MO(_MOUSE)
#define ADJUST   MO(_ADJUST)

#define OSMEH    OSM(MOD_MEH)
#define OSLS     OSM(MOD_LSFT)
#define OSRS     OSM(MOD_RSFT)
#define OSLEFT   OSM(MOD_LGUI)
#define OSHUN    OSL(_HUN)
#define OSRGHT   OSM(MOD_LGUI | MOD_LSFT)
#define ALTTAB   LALT(KC_TAB)

#define M_ENTER  LT(MOUSE, KC_ENT)
#define M_SPACE  LT(MOUSE, KC_SPC)
#define M_Z      LT(MOUSE, KC_Z)
#define NAV_ENT  LT(NAV, KC_ENT)
#define SYM_SPC  LT(SYM, KC_SPC)
#define ENTLEFT  MT(MOD_LGUI, KC_ENT)
#define SPCRGHT  MT(MOD_LGUI | MOD_LSFT, KC_SPC)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT(
      KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,                                     KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC,
      KC_ESC , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,                                     KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_MINS,
      OSLS   , M_Z    , KC_X   , KC_C   , KC_V   , KC_B   , XXXXXXX, XXXXXXX, KC_PSCR, XXXXXXX, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, OSRS,
                                 ADJUST , OSHUN  , ENTLEFT, QUOTNAV, MOUSE  , MOUSE  , SYM    , SPCRGHT, NAV    , KC_RALT
    ),
    [_COLEMAK_DH] = LAYOUT(
      KC_TAB , KC_Q   , KC_W   , KC_F   , KC_P   , KC_B   ,                                     KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN, KC_BSPC,
      KC_ESC , KC_A   , KC_R   , KC_S   , KC_T   , KC_G   ,                                     KC_M   , KC_N   , KC_E   , KC_I   , KC_O   , KC_MINS,
      OSLS   , M_Z    , KC_X   , KC_C   , KC_D   , KC_V   , XXXXXXX, XXXXXXX, KC_PSCR, XXXXXXX, KC_K   , KC_H   , KC_COMM, KC_DOT , KC_SLSH, OSRS   ,
                                 ADJUST , OSHUN  , ENTLEFT, QUOTNAV, MOUSE  , MOUSE  , SYM    , SPCRGHT, NAV    , KC_RALT
    ),
    [_NAV] = LAYOUT(
      _______, KC_MRWD, KC_MPRV, KC_MPLY, KC_MNXT, KC_MFFD,                                     KC_CUT , KC_COPY, KC_PSTE, KC_FIND, XXXXXXX, KC_DEL,
      _______, OS_GUI , OS_ALT , OS_CTRL, OS_SHFT, KC_WSCH,                                     KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, XXXXXXX, KC_ENT,
      _______, KC_PAUS, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END , XXXXXXX, _______,
                                 XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX
    ),
    [_SYM] = LAYOUT(
      _______, XXXXXXX, KC_LBRC, KC_LCBR, KC_LPRN, KC_TILD,                                     KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC, KC_EQL , KC_DEL ,
      _______, KC_MINS, KC_ASTR, KC_SLSH, KC_UNDS, KC_DLR,                                      KC_HASH, OS_SHFT, OS_CTRL, OS_ALT , OS_GUI , XXXXXXX,
      _______, KC_PLUS, KC_AMPR, KC_BSLS, KC_GRV , KC_PERC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PIPE, KC_AT  , KC_QUES, KC_EXLM, _______,
                                 XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX
    ),
    [_HUN] = LAYOUT(
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, U_UMLAU, U_ACUT , U_DACUT, O_UMLAU, KC_BSPC,
      _______, A_ACUT , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, E_ACUT , I_ACUT , O_ACUT , XXXXXXX,
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, O_DACUT, _______,
                                 _______, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX
    ),
    [_NUM] = LAYOUT(
      _______, KC_7   , KC_5   , KC_3   , KC_1   , KC_9   ,                                     KC_8   , KC_0   , KC_2   , KC_4   , KC_6   , KC_BSPC,
      _______, OS_GUI , OS_ALT , OS_CTRL, OS_SHFT, KC_F11 ,                                     KC_F10 , OS_SHFT, OS_CTRL, OS_ALT , OS_GUI , _______,
      _______, KC_F7  , KC_F5  , KC_F3  , KC_F1  , KC_F9  , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F8  , KC_F12 , KC_F2  , KC_F4  , KC_F6  , _______,
                                 XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX
    ),
    [_MOUSE] = LAYOUT(
      _______, XXXXXXX, KC_FIND, KC_PSTE, KC_COPY, KC_CUT ,                                     KC_ESC , KC_BTN1, KC_BTN2, XXXXXXX, XXXXXXX, _______,
      _______, KC_BTN4, KC_BTN3, KC_BTN2, KC_BTN1, KC_BTN5,                                     KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_ENT , _______,
      _______, XXXXXXX, KC_ACL2, KC_ACL1, KC_ACL0, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, XXXXXXX, _______,
                                 XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX
    ),
    [_ADJUST] = LAYOUT(
      XXXXXXX, QWERTY , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, COLEMAK, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_RMOD,RGB_TOG, XXXXXXX
    ),
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case SYM:
    case NAV:
    case QUOTNAV:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case SYM:
    case NAV:
    case QUOTNAV:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_GUI:
        return true;
    default:
        return false;
    }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_gui_state = os_up_unqueued;

#define SIJ_ACUTE  SS_DOWN(X_RALT)"'"SS_UP(X_RALT)
#define SIJ_DACUTE SS_DOWN(X_RALT)SS_DOWN(X_LSFT)"2"SS_UP(X_LSFT)SS_UP(X_RALT)
#define SIJ_UMLAUT SS_DOWN(X_RALT)"\""SS_UP(X_RALT)

bool process_hun_macros(uint16_t keycode, keyrecord_t *record) {
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

    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_gui_state, KC_LGUI, OS_GUI,
        keycode, record
    );
    if(record->event.pressed && IS_LAYER_ON(_HUN)) {
        return process_hun_macros(keycode, record);
    }

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SYM, _NAV, _NUM);
}
