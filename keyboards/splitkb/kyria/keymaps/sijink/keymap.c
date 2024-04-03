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
#include "oneshot.h"
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
#define RA(kc) RALT_T(kc
#define RC(kc) RCTL_T(kc)
#define RS(kc) RSFT_T(kc)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_CANARY] = LAYOUT(
        KC_TAB    , KC_W      , KC_L      , KC_Y      , KC_P      , KC_B      ,                                                 KC_Z      , KC_F      , KC_O      , KC_U      , KC_QUOT   , KC_BSPC   ,
        KC_ESC    , KC_C      , KC_R      , KC_S      , KC_T      , KC_G      ,                                                 KC_M      , KC_N      , KC_E      , KC_I      , KC_A      , KC_ENT    ,
        HUN       , MQUSE     , KC_J      , KC_V      , KC_D      , KC_K      , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , KC_X      , KC_H      , KC_SLSH   , KC_COMM   , KC_DOT    , KC_DEL    ,
                                            MO_ADJ    , QK_REP    , KC_SPC    , MO_NAV    , XXXXXXX   , XXXXXXX   , OSL_SYM   , KC_LSFT   , OSL_FUN   , XXXXXXX

    ),
    [_SYM] = LAYOUT(
        _______   , KC_TILD   , KC_AT     , KC_HASH   , KC_DLR    , KC_PERC   ,                                                 KC_CIRC   , KC_GRV    , KC_PLUS   , KC_EQL    ,TD(TD_QUOT), _______   ,
        _______   , KC_COLN   , KC_LBRC   , KC_LCBR   , KC_LPRN   , KC_LT     ,                                                 KC_BSLS   , KC_MINS   , KC_UNDS   , KC_PIPE   , KC_SCLN   , _______   ,
        _______   , KC_AMPR   , KC_RBRC   , KC_RCBR   , KC_RPRN   , KC_GT     , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , KC_EXLM   , KC_ASTR   ,TD(TD_SLSH), KC_COMM   , KC_DOT    , _______   ,
                                            XXXXXXX   , XXXXXXX   , _______   , _______   , XXXXXXX   , XXXXXXX   , TG_NUM    , BASE      , XXXXXXX   , XXXXXXX
    ),
    [_NUM] = LAYOUT(
        _______   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   ,                                                 XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , _______   ,
        _______   , XXXXXXX   , KC_5      , KC_3      , KC_1      , XXXXXXX   ,                                                 XXXXXXX   , KC_0      , KC_2      , KC_4      , XXXXXXX   , _______   ,
        _______   , XXXXXXX   , XXXXXXX   , KC_9      , KC_7      , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , KC_6      , KC_8      , XXXXXXX   , XXXXXXX   , _______   ,
                                            XXXXXXX   , QK_REP    , _______   , _______   , XXXXXXX   , XXXXXXX   , TG_NUMSYM , BASE      , XXXXXXX   , XXXXXXX
    ),
    [_NUMSYM] = LAYOUT(
        _______   , KC_TILD   , KC_AT     , KC_HASH   , KC_DLR    , KC_PERC   ,                                                 KC_CIRC   , KC_GRV    , KC_PLUS   , KC_EQL    ,TD(TD_QUOT), _______   ,
        _______   , KC_COLN   , KC_LBRC   , KC_LCBR   , KC_LPRN   , KC_LT     ,                                                 KC_BSLS   , KC_MINS   , KC_UNDS   , KC_PIPE   , KC_SCLN   , _______   ,
        _______   , KC_AMPR   , KC_RBRC   , KC_RCBR   , KC_RPRN   , KC_GT     , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , KC_EXLM   , KC_ASTR   ,TD(TD_SLSH), KC_COMM   , KC_DOT    , _______   ,
                                            XXXXXXX   , QK_REP    , _______   , _______   , XXXXXXX   , XXXXXXX   , _______   , BASE      , XXXXXXX   , XXXXXXX
    ),
    [_FUN] = LAYOUT(
        _______   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   ,                                                 XXXXXXX   , XXXXXXX   , XXXXXXX    , XXXXXXX   , XXXXXXX   , _______   ,
        _______   , XXXXXXX   , KC_F5     , KC_F3     , KC_F1     , XXXXXXX   ,                                                 XXXXXXX   , KC_F10    , KC_F2      , KC_F4     , XXXXXXX   , _______   ,
        _______   , XXXXXXX   , KC_F11    , KC_F9     , KC_F7     , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , KC_F6     , KC_F8      , KC_F12    , XXXXXXX   , _______   ,
                                            XXXXXXX   , QK_REP    , _______   , _______   , XXXXXXX   , XXXXXXX   , XXXXXXX   , BASE      , BASE      , XXXXXXX
    ),
    [_NAV] = LAYOUT(
        _______   , KC_MRWD   , KC_MPRV   , KC_MPLY   , KC_MNXT   , KC_MFFD   ,                                                 KC_CUT    , KC_COPY   , KC_PSTE   , KC_FIND   , KC_INS    , _______   ,
        _______   , OS_GUI    , OS_ALT    , OS_CTRL   , OS_SHFT   , XXXXXXX   ,                                                 KC_LEFT   , KC_DOWN   , KC_UP     , KC_RGHT   , XXXXXXX   , _______   ,
        _______   , KC_BRID   , KC_VOLD   , KC_MUTE   , KC_VOLU   , KC_BRIU   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , KC_HOME   , KC_PGDN   , KC_PGUP   , KC_END    , KC_PSCR   , _______   ,
                                            XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX
    ),
    [_MOUSE] = LAYOUT(
        XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   ,                                                 KC_CUT    , KC_COPY   , KC_PSTE   , KC_FIND   , KC_BSPC   , _______   ,
        XXXXXXX   , KC_BTN4   , KC_BTN3   , KC_BTN2   , KC_BTN1   , KC_BTN5   ,                                                 KC_MS_L   , KC_MS_D   , KC_MS_U   , KC_MS_R   , KC_ENT    , _______   ,
        XXXXXXX   , XXXXXXX   , KC_ACL2   , KC_ACL1   , KC_ACL0   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , KC_WH_L   , KC_WH_D   , KC_WH_U   , KC_WH_R   , KC_DEL    , _______   ,
                                            XXXXXXX   , XXXXXXX   , XXXXXXX   , KC_LGUI   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX
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

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
        case BASE:
        case KC_LSFT: {
            return true;
        }
    }
    return false;
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case MO_NAV:
    case OSL_SYM:
    case OSL_FUN:
    case TG_NUM:
    case TG_NUMSYM:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_GUI:
    case KC_BTN1:
    case KC_BTN2:
    case KC_BTN3:
    case KC_BTN4:
    case KC_BTN5:
    case KC_MS_L:
    case KC_MS_D:
    case KC_MS_U:
    case KC_MS_R:
        return true;
    default:
        return false;
    }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

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
    if (record->event.pressed) {
        if (keycode == OSL_SYM) {
            layer_on(_SYM);
            return false;
        }
        if (keycode == OSL_FUN) {
            layer_on(_FUN);
            return false;
        }
    }

    return true;
}

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
    [TD_QUOT] = ACTION_TAP_DANCE_TAP_HOLD(KC_QUOT, KC_DQUO),
    [TD_SLSH] = ACTION_TAP_DANCE_TAP_HOLD(KC_SLSH, KC_QUES),
};

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        if (get_highest_layer(cached_layer_state) <= _SYM) {
            layer_off(_SYM);
        }
        if (get_highest_layer(cached_layer_state) <= _FUN) {
            layer_off(_FUN);
        }
    }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) {
        case TD(TD_QUOT):
        case TD(TD_SLSH):
            action = &tap_dance_actions[QK_TAP_DANCE_GET_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
    }

    if (!tg_on_keydown(keycode, record)) return false;
    if (!osl_on_keydown(keycode, record)) return false;

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
        &os_cmd_state, KC_LCMD, OS_GUI,
        keycode, record
    );

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
