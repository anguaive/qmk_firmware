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
#include "action_layer.h"
#include QMK_KEYBOARD_H

#include <stdint.h>
#include "action_util.h"
#include "modifiers.h"
#include "process_tap_dance.h"
#include "quantum.h"
#include "oneshot.h"
#include "rgblight.h"

enum layers {
    _COLEMAK_DH = 0,
    _SYM,
    _NUM,
    _NAV,
    _MOUSE,
    _HUN,
    _ADJUST,
};

enum keycodes {
    // one-shot callum-style mods
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_GUI,
    // OSL(...), but not reset by keypresses in higher layers
    OSL_SYM,
    // TG(...), but on keydown
    TG_NUM,
    // accented hungarian characters
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

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_DOUBLE_TAP,
    TD_HOLD
} td_state_t;

// Layer aliases
#define BASE     TO(_COLEMAK_DH)
#define MO_NAV   MO(_NAV)
#define SYM      TG(_SYM) // unused
#define NUM      TG(_NUM) // unused
#define MOUZE    LT(_MOUSE, KC_Z)
#define HUN      OSL(_HUN) // unused
#define ADJUST   TG(_ADJUST)
#define MO_ADJ   MO(_ADJUST)

// Tap-hold keycodes, for cases when hold should act as a "regular keypress"
#define U_UNDS   LT(0, KC_U)
#define G_MINS   LT(0, KC_G)
#define COM_QUO  LT(0, KC_COMM)
#define DOT_DQU  LT(0, KC_DOT)
#define SLS_EXL  LT(0, KC_SLSH)
#define SLS_BSL  LT(0, KC_SLSH)
#define AMP_TLD  LT(0, KC_AMPR)
#define QUO_GRV  LT(0, KC_DQUO)
#define CPY_PSC  LT(0, KC_PSCR)
#define PST_INS  LT(0, KC_INS)
#define N1_F1    LT(0, KC_1)
#define N2_F2    LT(0, KC_2)
#define N3_F3    LT(0, KC_3)
#define N4_F4    LT(0, KC_4)
#define N5_F5    LT(0, KC_5)
#define N6_F6    LT(0, KC_6)
#define N7_F7    LT(0, KC_7)
#define N8_F8    LT(0, KC_8)
#define N9_F9    LT(0, KC_9)
#define N0_F10   LT(0, KC_0)
#define MIN_F11  LT(0, KC_MINS)
#define PLS_F12  LT(0, KC_PLUS)

// tap dance
enum {
    TD_WM_NAV,
    TD_HUN_Q
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK_DH] = LAYOUT(
      KC_TAB,TD(TD_HUN_Q),KC_W , KC_F   , KC_P   , KC_B   ,                                     KC_J   , KC_L   , U_UNDS , KC_Y   , KC_SCLN, KC_BSPC,
      KC_ESC , KC_A   , KC_R   , KC_S   , KC_T   , G_MINS ,                                     KC_M   , KC_N   , KC_E   , KC_I   , KC_O   , KC_MINS,
      KC_LCTL, MOUZE  , KC_X   , KC_C   , KC_D   , KC_V   , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_K   , KC_H   , COM_QUO, DOT_DQU, SLS_EXL, KC_RCTL,
                                 MO_ADJ , XXXXXXX,KC_LSFT,TD(TD_WM_NAV),XXXXXXX,XXXXXXX,OSL_SYM,KC_SPC , MO_NAV , XXXXXXX
    ),
    [_SYM] = LAYOUT(
      XXXXXXX, KC_TAB , KC_AMPR, KC_HASH, KC_DLR , KC_PERC,                                     KC_CIRC, KC_PIPE, KC_UNDS, KC_EQL , KC_BSPC, XXXXXXX,
      XXXXXXX, KC_ESC , KC_LBRC, KC_LCBR, KC_LPRN, KC_MINS,                                     KC_PLUS, KC_RPRN, KC_RCBR, KC_RBRC, KC_ENT , XXXXXXX,
      XXXXXXX, OS_GUI , OS_ALT , OS_CTRL, OS_SHFT, SLS_BSL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_ASTR, AMP_TLD, QUO_GRV, KC_DQUO, KC_DEL , XXXXXXX,
                                 XXXXXXX, XXXXXXX, BASE   , MO_NAV , XXXXXXX, XXXXXXX, TG_NUM , _______, XXXXXXX, XXXXXXX
    ),
    [_NUM] = LAYOUT(
      XXXXXXX, _______, XXXXXXX, N9_F9  , N7_F7  , _______,                                     _______, N6_F6  , N8_F8  , _______, _______, XXXXXXX,
      XXXXXXX, _______, N5_F5  , N3_F3  , N1_F1  , MIN_F11,                                     PLS_F12, N0_F10 , N2_F2  , N4_F4  , _______, XXXXXXX,
      XXXXXXX, _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX,
                                 XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX
    ),
    [_NAV] = LAYOUT(
      XXXXXXX, KC_TAB , KC_MPRV, KC_MPLY, KC_MNXT, KC_MFFD,                                     KC_CUT , CPY_PSC, PST_INS, KC_FIND, KC_BSPC, XXXXXXX,
      XXXXXXX, KC_ESC , KC_VOLD, KC_MUTE, KC_VOLU, KC_MRWD,                                     KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_ENT , XXXXXXX,
      XXXXXXX, OS_GUI , OS_ALT , OS_CTRL, OS_SHFT, KC_PAUS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END , KC_DEL , XXXXXXX,
                                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, ADJUST , _______, XXXXXXX, XXXXXXX
    ),
    [_MOUSE] = LAYOUT(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     KC_CUT , KC_COPY, KC_PSTE, KC_FIND, KC_BSPC, XXXXXXX,
      XXXXXXX, KC_BTN4, KC_BTN3, KC_BTN2, KC_BTN1, KC_BTN5,                                     KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_ENT , XXXXXXX,
      XXXXXXX, XXXXXXX, KC_ACL2, KC_ACL1, KC_ACL0, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_DEL , XXXXXXX,
                                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX
    ),
    [_HUN] = LAYOUT(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, U_UMLAU, U_ACUT , U_DACUT, O_UMLAU, XXXXXXX,
      XXXXXXX, A_ACUT , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, E_ACUT , I_ACUT , O_ACUT , XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, O_DACUT, XXXXXXX,
                                 XXXXXXX, XXXXXXX, KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_ADJUST] = LAYOUT(
      XXXXXXX, RGB_M_B, RGB_M_R, RGB_M_SW,XXXXXXX, XXXXXXX,                                     RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 XXXXXXX, XXXXXXX, BASE   , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG
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
        // Reset one-shot mods only on shift
    case KC_LSFT:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_GUI:
    // Also keep one-shot mods on layer switches...
    case BASE:
    case OSL_SYM:
    case TG_NUM:
    case TD(TD_WM_NAV):
    case MO_NAV:
    case MOUZE:
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

    layer_off(_HUN);

    return false;
}

bool tap_hold(uint16_t keycode, keyrecord_t *record, uint16_t trigger, uint16_t hold) {
    if (keycode == trigger) {
        if (!record->tap.count && record->event.pressed) {
            tap_code16(hold);
            // stop processing
            return false;
        }
    }

    // continue processing
    return true;
}

bool tg_on_keydown(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed && keycode == TG_NUM) {
        layer_invert(_NUM);
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

const rgblight_segment_t PROGMEM rgb_layer_base[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_OFF},
    {31, 7, HSV_OFF}
);

const rgblight_segment_t PROGMEM rgb_layer_sym[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_RED},
    {31, 7, HSV_RED}
);

const rgblight_segment_t PROGMEM rgb_layer_num[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_GOLD},
    {31, 7, HSV_GOLD}
);

const rgblight_segment_t PROGMEM rgb_layer_nav[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_AZURE},
    {31, 7, HSV_AZURE}
);

const rgblight_segment_t PROGMEM rgb_layer_hun[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_WHITE},
    {1, 4, HSV_RED},
    {5, 1, HSV_WHITE},
    {6, 1, HSV_RED},
    {31, 1, HSV_WHITE},
    {32, 4, HSV_GREEN},
    {36, 1, HSV_WHITE},
    {37, 1, HSV_GREEN}
);

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    rgb_layer_base, rgb_layer_sym, rgb_layer_num, rgb_layer_nav, rgb_layer_hun
);

layer_state_t cached_layer_state;

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _COLEMAK_DH));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _COLEMAK_DH));
    rgblight_set_layer_state(1, layer_state_cmp(state, _SYM));
    rgblight_set_layer_state(2, layer_state_cmp(state, _NUM));
    rgblight_set_layer_state(3, layer_state_cmp(state, _NAV));
    rgblight_set_layer_state(4, layer_state_cmp(state, _HUN));

    cached_layer_state = state;
    return state;
}

uint16_t osm_sym_ignored_keycodes[] = {TG_NUM, OS_GUI, OS_ALT, OS_CTRL, OS_SHFT, 0};

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed && get_highest_layer(cached_layer_state) <= _SYM) {
        for (uint16_t *kc = osm_sym_ignored_keycodes; *kc != 0; kc++) {
            if (*kc == keycode) {
                return;
            }
        }

        layer_off(_SYM);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!tg_on_keydown(keycode, record)) return false;
    if (!osl_on_keydown(keycode, record)) return false;

    if (!tap_hold(keycode, record, U_UNDS, KC_UNDS)) return false;
    if (!tap_hold(keycode, record, G_MINS, KC_MINS)) return false;
    if (!tap_hold(keycode, record, COM_QUO, KC_QUOT)) return false;
    if (!tap_hold(keycode, record, DOT_DQU, KC_DQUO)) return false;
    if (!tap_hold(keycode, record, SLS_EXL, KC_EXLM)) return false;
    if (!tap_hold(keycode, record, SLS_BSL, KC_BSLS)) return false;
    if (!tap_hold(keycode, record, AMP_TLD, KC_TILD)) return false;
    if (!tap_hold(keycode, record, QUO_GRV, KC_GRV)) return false;
    if (!tap_hold(keycode, record, CPY_PSC, KC_PSCR)) return false;
    if (!tap_hold(keycode, record, PST_INS, KC_INS)) return false;
    if (!tap_hold(keycode, record, N1_F1, KC_F1)) return false;
    if (!tap_hold(keycode, record, N2_F2, KC_F2)) return false;
    if (!tap_hold(keycode, record, N3_F3, KC_F3)) return false;
    if (!tap_hold(keycode, record, N4_F4, KC_F4)) return false;
    if (!tap_hold(keycode, record, N5_F5, KC_F5)) return false;
    if (!tap_hold(keycode, record, N6_F6, KC_F6)) return false;
    if (!tap_hold(keycode, record, N7_F7, KC_F7)) return false;
    if (!tap_hold(keycode, record, N8_F8, KC_F8)) return false;
    if (!tap_hold(keycode, record, N9_F9, KC_F9)) return false;
    if (!tap_hold(keycode, record, N0_F10, KC_F10)) return false;
    if (!tap_hold(keycode, record, MIN_F11, KC_F1)) return false;
    if (!tap_hold(keycode, record, PLS_F12, KC_F1)) return false;

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

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted || !state->pressed) return TD_DOUBLE_TAP;
        else return TD_HOLD;
    }

    return TD_UNKNOWN;
}

void td_wm_nav_finished_fn(tap_dance_state_t *state, void *user_data) {
    td_state_t td_state = cur_dance(state);
    switch (td_state) {
        case (TD_SINGLE_TAP):
            set_oneshot_mods(MOD_BIT_LGUI);
            break;
        case (TD_DOUBLE_TAP):
            set_oneshot_mods(MOD_BIT_LGUI | MOD_BIT_LSHIFT);
            break;
        case (TD_HOLD):
            clear_oneshot_mods();
            layer_on(_NAV);
            break;
        default:
            break;
    }
}

void td_wm_nav_reset_fn(tap_dance_state_t *state, void *user_data) {
    layer_off(_NAV);
}

void td_hun_q_finished_fn(tap_dance_state_t *state, void *user_data) {
    td_state_t td_state = cur_dance(state);
    switch (td_state) {
        case (TD_HOLD):
            // acts mode like a toggle actually... have to reset in handler
            layer_on(_HUN);
            break;
        default:
            for (int i = 0; i < state->count; i++) {
                tap_code16(KC_Q);
            }
            break;
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_WM_NAV] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_wm_nav_finished_fn, td_wm_nav_reset_fn),
    [TD_HUN_Q] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_hun_q_finished_fn, NULL)
};

void keyboard_pre_init_user(void) {
    // Disable on-board Liatris LED
    setPinOutput(24);
    writePinHigh(24);
}

void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
    rgblight_set_speed_noeeprom(32);

    rgblight_layers = rgb_layers;
}
