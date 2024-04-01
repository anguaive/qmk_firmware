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
#include "hun.h"
#include "keycodes.h"
#include "global.h"
#include "rgb.h"
#include QMK_KEYBOARD_H

#include "action_layer.h"
#include <stdint.h>
#include "action_util.h"
#include "modifiers.h"
#include "quantum.h"
#include "process_tap_dance.h"
#include "rgblight.h"

// Layer aliases
#define BASE     TO(_CANARY)
#define MO_NAV   MO(_NAV)
#define SYM      TG(_SYM) // unused
#define NUM      TG(_NUM) // unused
#define NUMSYM   TG(_NUMSYM) // unused
#define MQUSE    LT(_MOUSE, KC_Q)
#define HUN      TG(_HUN)
#define ADJUST   TG(_ADJUST)
#define MO_ADJ   MO(_ADJUST)

// Mod-tap aliases
#define LG(kc) LGUI_T(kc)
#define LA(kc) LALT_T(kc)
#define LC(kc) LCTL_T(kc)
#define LS(kc) LSFT_T(kc)
#define RG(kc) RGUI_T(kc)
#define RA(kc) RALT_T(kc)
#define RC(kc) RCTL_T(kc)
#define RS(kc) RSFT_T(kc)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_CANARY] = LAYOUT(
        KC_TAB    , KC_W      , KC_L      , KC_Y      , KC_P      , KC_B      ,                                                 KC_Z      , KC_F      , KC_O      , KC_U      , KC_QUOT   , KC_BSPC   ,
        KC_ESC    , LG(KC_C)  , LA(KC_R)  , LC(KC_S)  , LS(KC_T)  , KC_G      ,                                                 KC_M      , RS(KC_N)  , RC(KC_E)  , RA(KC_I)  , RG(KC_A)  , KC_ENT    ,
        HUN       , MQUSE     , KC_J      , KC_V      , KC_D      , KC_K      , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , KC_X      , KC_H      , KC_SLSH   , KC_COMM   , KC_DOT    , KC_DEL    ,
                                            MO_ADJ    , XXXXXXX   , MO_NAV    , KC_SPC    , XXXXXXX   , XXXXXXX   , OSL_SYM   , KC_LSFT   , MO_NAV    , XXXXXXX

    ),
    [_SYM] = LAYOUT(
        _______   , KC_TILD   , KC_AT     , KC_HASH   , KC_DLR    , KC_PERC   ,                                                 XXXXXXX   , XXXXXXX   , KC_PLUS   , KC_EQL    , KC_GRV    , _______   ,
        _______   ,LG(KC_COLN),LA(KC_LBRC),LC(KC_LCBR),LS(KC_LPRN), KC_LT     ,                                                 KC_BSLS   ,RS(KC_MINS),RC(KC_UNDS),RA(KC_PIPE),RG(KC_SCLN), _______   ,
        _______   , XXXXXXX   , KC_RBRC   , KC_RCBR   , KC_RPRN   , KC_GT     , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , KC_AMPR   , KC_ASTR   , KC_CIRC   , KC_EXLM   , _______   ,
                                            XXXXXXX   , XXXXXXX   , XXXXXXX   , _______   , XXXXXXX   , XXXXXXX   , TG_NUM    , BASE      , XXXXXXX   , XXXXXXX
    ),
    [_NUM] = LAYOUT(
        _______   , KC_F9     , KC_F5     , KC_F3     , KC_F1     , KC_F7     ,                                                 KC_F6     , KC_F10    , KC_F2     , KC_F4     , KC_F8     , _______   ,
        _______   , LG(KC_NO) , LA(KC_5)  , LC(KC_3)  , LS(KC_1)  , XXXXXXX   ,                                                 XXXXXXX   , RS(KC_0)  , RC(KC_2)  , RA(KC_4)  , RG(KC_NO) , _______   ,
        _______   , XXXXXXX   , XXXXXXX   , KC_9      , KC_7      , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , KC_6      , KC_8      , XXXXXXX   , XXXXXXX   , _______   ,
                                            XXXXXXX   , XXXXXXX   , XXXXXXX   , _______   , XXXXXXX   , XXXXXXX   , TG_NUMSYM , BASE      , XXXXXXX   , XXXXXXX
    ),
    [_NUMSYM] = LAYOUT(
        _______   , KC_TILD   , KC_AT     , KC_HASH   , KC_DLR    , KC_PERC   ,                                                 XXXXXXX   , XXXXXXX   , KC_PLUS   , KC_EQL    , KC_GRV    , _______   ,
        _______   ,LG(KC_COLN),LA(KC_LBRC),LC(KC_LCBR),LS(KC_LPRN), KC_LT     ,                                                 KC_BSLS   ,RS(KC_MINS),RC(KC_UNDS),RA(KC_PIPE),RG(KC_SCLN), _______   ,
        _______   , XXXXXXX   , KC_RBRC   , KC_RCBR   , KC_RPRN   , KC_GT     , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , KC_AMPR   , KC_ASTR   , KC_CIRC   , KC_EXLM   , _______   ,
                                            XXXXXXX   , XXXXXXX   , XXXXXXX   , _______   , XXXXXXX   , XXXXXXX   , _______   , BASE      , XXXXXXX   , XXXXXXX
    ),
    [_NAV] = LAYOUT(
        _______   , KC_TAB    , KC_MPRV   , KC_MPLY   , KC_MNXT   , KC_MFFD   ,                                                 KC_CUT    , KC_COPY   , KC_PAST   , KC_FIND   , KC_BSPC   , _______   ,
        _______   , KC_ESC    , KC_VOLD   , KC_MUTE   , KC_VOLU   , KC_MRWD   ,                                                 KC_LEFT   , KC_DOWN   , KC_UP     , KC_RGHT   , KC_ENT    , _______   ,
        _______   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , KC_PAUS   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , KC_HOME   , KC_PGDN   , KC_PGUP   , KC_END    , KC_DEL    , _______   ,
                                            XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , ADJUST    , XXXXXXX   , XXXXXXX   , XXXXXXX
    ),
    [_MOUSE] = LAYOUT(
        XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   ,                                                 KC_CUT    , KC_COPY   , KC_PSTE   , KC_FIND   , KC_BSPC   , _______   ,
        XXXXXXX   , KC_BTN4   , KC_BTN3   , KC_BTN2   , KC_BTN1   , KC_BTN5   ,                                                 KC_MS_L   , KC_MS_D   , KC_MS_U   , KC_MS_R   , KC_ENT    , _______   ,
        XXXXXXX   , XXXXXXX   , KC_ACL2   , KC_ACL1   , KC_ACL0   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , KC_WH_L   , KC_WH_D   , KC_WH_U   , KC_WH_R   , KC_DEL    , _______   ,
                                            XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX
    ),
    [_HUN] = LAYOUT(
        XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   ,                                                 XXXXXXX   , O_UMLAU   , O_ACUT    , U_ACUT    , XXXXXXX   , _______   ,
        XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   ,                                                 XXXXXXX   , O_DACUT   , E_ACUT    , I_ACUT    , A_ACUT    , _______   ,
        XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , U_UMLAU   , U_DACUT   , XXXXXXX   , XXXXXXX   , XXXXXXX   ,
                                            XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , KC_LSFT   , XXXXXXX   , XXXXXXX
    ),
    [_ADJUST] = LAYOUT(
        XXXXXXX   , RGB_M_B   , RGB_M_R   , RGB_M_SW  , XXXXXXX   , XXXXXXX   ,                                                 RGB_HUI   , RGB_SAI   , RGB_VAI   , XXXXXXX   , XXXXXXX   , XXXXXXX   ,
        XXXXXXX   , DT_PRNT   , DT_UP     , DT_DOWN   , XXXXXXX   , XXXXXXX   ,                                                 RGB_HUD   , RGB_SAD   , RGB_VAD   , XXXXXXX   , XXXXXXX   , XXXXXXX   ,
        XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   ,
                                            XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , BASE      , XXXXXXX   , RGB_TOG
    ),
};

bool tg_on_keydown(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed && keycode == TG_NUM) {
        layer_invert(_NUM);
        return false;
    }
    if (record->event.pressed && keycode == TG_NUMSYM) {
        layer_invert(_NUMSYM);
        return false;
    }

    return true;
}

bool osl_on_keydown(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed && keycode == OSL_SYM) {
        layer_on(_SYM);
        return false;
    }

    return true;
}

bool intercept_mod_tap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LC(KC_LCBR):
        case LS(KC_LPRN):
        case RC(KC_UNDS):
        case RA(KC_PIPE):
        case LG(KC_COLN): {
            uint16_t kc = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
            if (record->tap.count && record->event.pressed) {
                tap_code16(S(kc));
                layer_off(_SYM); // if we return false, we don't reach post_process_record_user
                return false;
            }
            break;
        }
    }

    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed && get_highest_layer(cached_layer_state) <= SYM) {
        layer_off(_SYM);
    }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (!tg_on_keydown(keycode, record)) return false;
    if (!osl_on_keydown(keycode, record)) return false;
    if (!intercept_mod_tap(keycode, record)) return false;

    if(record->event.pressed && IS_LAYER_ON(_HUN)) {
        return process_hun_macros(keycode, record);
    }

    return true;
}

void keyboard_pre_init_user(void) {
    disable_onboard_liatris_led();
}

void keyboard_post_init_user(void) {
    rgblight_setup();
}
