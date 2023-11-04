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
#include QMK_KEYBOARD_H

#include "action_layer.h"
#include <stdint.h>
#include "action_util.h"
#include "modifiers.h"
#include "process_tap_dance.h"
#include "quantum.h"
#include "oneshot.h"
#include "rgblight.h"

enum layers {
    _CANARY = 0,
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

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

// Layer aliases
#define BASE     TO(_CANARY)
#define MO_NAV   MO(_NAV)
#define SYM      TG(_SYM) // unused
#define NUM      TG(_NUM) // unused
#define MQUSE    LT(_MOUSE, KC_Q)
#define HUN      OSL(_HUN) // unused
#define ADJUST   TG(_ADJUST)
#define MO_ADJ   MO(_ADJUST)

// tap dance
enum {
    WM_NAV, // GUI | shift+GUI | hold for NAV
    Q_HUN, // q | hold for one-shot HUN
    AMP_TLD,
    U_UNDS,
    G_MINS,
    COM_QUO,
    DOT_DQU,
    SLS_EXL,
    SLS_BSL,
    QUO_GRV,
    CPY_PSC,
    PST_INS,
    N1,
    N2,
    N3,
    N4,
    N5,
    N6,
    N7,
    N8,
    N9,
    N10,
    MIN_F11,
    PLS_F12
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_CANARY] = LAYOUT(
      KC_TAB,  KC_W   , KC_L   , KC_Y   , KC_P   , KC_B   ,                                     KC_Z   , KC_F   , KC_O,    KC_U   , KC_QUOT, KC_BSPC,
      KC_ESC , KC_C   , KC_R   , KC_S   , KC_T   , KC_G   ,                                     KC_M   , KC_N   , KC_E   , KC_I   , KC_A   , KC_ENT ,
      KC_LCTL, MQUSE  , KC_J   , KC_V   , KC_D   , KC_K   , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_X   , KC_H   , KC_SLSH, KC_COMM, KC_DOT , KC_DEL ,
                                 MO_ADJ , MO_NAV ,KC_SPC,TD(WM_NAV),XXXXXXX, XXXXXXX, OSL_SYM, KC_LSFT , MO_NAV , XXXXXXX
    ),
    [_SYM] = LAYOUT(
      _______, KC_TILD, KC_AT  , KC_HASH, KC_DLR , KC_PERC,                                     KC_CIRC, KC_LPRN, KC_RPRN, KC_EQL , KC_COLN, _______,
      _______, KC_PLUS, KC_AMPR, KC_ASTR, KC_UNDS, KC_MINS,                                     KC_BSLS, KC_LCBR, KC_RCBR, KC_PIPE, KC_SCLN, _______,
      _______, OS_GUI , OS_ALT , OS_CTRL, OS_SHFT, XXXXXXX ,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_GRV , KC_EXLM, _______,
                                 XXXXXXX, XXXXXXX, _______, MO_NAV , XXXXXXX, XXXXXXX, TG_NUM , BASE   , XXXXXXX, XXXXXXX
    ),
    [_NUM] = LAYOUT(
      _______, _______, XXXXXXX, TD(N9) , TD(N7) , KC_QUES,                                     _______, TD(N6) , TD(N8) , _______, KC_QUOT, _______,
      _______, _______, TD(N5) , TD(N3) , TD(N1) ,TD(MIN_F11),                              TD(PLS_F12), TD(N10), TD(N2) , TD(N4) , KC_DQUO, _______,
      _______, _______, _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LT  , KC_GT  , KC_SLSH, KC_COMM, KC_DOT , _______,
                                 XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX
    ),
    [_NAV] = LAYOUT(
      _______, KC_TAB , KC_MPRV, KC_MPLY, KC_MNXT, KC_MFFD,                                     KC_CUT,TD(CPY_PSC),TD(PST_INS),KC_FIND, KC_BSPC, _______,
      _______, KC_ESC , KC_VOLD, KC_MUTE, KC_VOLU, KC_MRWD,                                     KC_LEFT, KC_DOWN,  KC_UP  ,    KC_RGHT, KC_ENT , _______,
      _______, OS_GUI , OS_ALT , OS_CTRL, OS_SHFT, KC_PAUS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN,  KC_PGUP,    KC_END , KC_DEL , _______,
                                 XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, ADJUST , XXXXXXX, XXXXXXX,  XXXXXXX
    ),
    [_MOUSE] = LAYOUT(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     KC_CUT , KC_COPY, KC_PSTE, KC_FIND, KC_BSPC, _______,
      XXXXXXX, KC_BTN4, KC_BTN3, KC_BTN2, KC_BTN1, KC_BTN5,                                     KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_ENT , _______,
      XXXXXXX, XXXXXXX, KC_ACL2, KC_ACL1, KC_ACL0, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_DEL , _______,
                                 XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_HUN] = LAYOUT(
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, U_UMLAU, U_ACUT , U_DACUT, O_UMLAU, _______,
      XXXXXXX, A_ACUT , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX, E_ACUT , I_ACUT , O_ACUT , _______,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, O_DACUT, XXXXXXX,
                                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT, XXXXXXX, XXXXXXX
    ),
    [_ADJUST] = LAYOUT(
      XXXXXXX, RGB_M_B, RGB_M_R, RGB_M_SW,XXXXXXX, XXXXXXX,                                     RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX,
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, BASE   , XXXXXXX, RGB_TOG
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
    case TD(WM_NAV):
    case MO_NAV:
    case MQUSE:
        return true;
    default:
        return false;
    }
}

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_gui_state = os_up_unqueued;

layer_state_t cached_layer_state;

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
            if (get_highest_layer(cached_layer_state) <= _SYM) {
                layer_off(_SYM);
            }

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

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _CANARY));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _CANARY));
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

void handle_tap_dance(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) {
        case TD(AMP_TLD):
        case TD(U_UNDS):
        case TD(G_MINS):
        case TD(COM_QUO):
        case TD(DOT_DQU):
        case TD(SLS_EXL):
        case TD(SLS_BSL):
        case TD(QUO_GRV):
        case TD(CPY_PSC):
        case TD(PST_INS):
        case TD(N1):
        case TD(N2):
        case TD(N3):
        case TD(N4):
        case TD(N5):
        case TD(N6):
        case TD(N7):
        case TD(N8):
        case TD(N9):
        case TD(N10):
        case TD(MIN_F11):
        case TD(PLS_F12):
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    handle_tap_dance(keycode, record);

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
            layer_on(_HUN);
            break;
        default:
            for (int i = 0; i < state->count; i++) {
                tap_code16(KC_Q);
            }
            break;
    }
}

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

void tap_dance_tap_hold_no_repeat_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            tap_code16(tap_hold->hold);
        } else {
            tap_code16(tap_hold->tap);
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

#define ACTION_TAP_DANCE_TAP_HOLD_NO_REPEAT(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_no_repeat_finished, NULL}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
    [WM_NAV] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_wm_nav_finished_fn, td_wm_nav_reset_fn),
    [Q_HUN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_hun_q_finished_fn, NULL),
    [AMP_TLD] = ACTION_TAP_DANCE_TAP_HOLD(KC_AMPR, KC_TILD),
    [U_UNDS] = ACTION_TAP_DANCE_TAP_HOLD(KC_U, KC_UNDS),
    [G_MINS] = ACTION_TAP_DANCE_TAP_HOLD(KC_G, KC_MINS),
    [COM_QUO] = ACTION_TAP_DANCE_TAP_HOLD(KC_COMM, KC_QUOT),
    [DOT_DQU] = ACTION_TAP_DANCE_TAP_HOLD(KC_DOT, KC_DQUO),
    [SLS_EXL] = ACTION_TAP_DANCE_TAP_HOLD(KC_SLSH, KC_EXLM),
    [SLS_BSL] = ACTION_TAP_DANCE_TAP_HOLD(KC_SLSH, KC_BSLS),
    [QUO_GRV] = ACTION_TAP_DANCE_TAP_HOLD(KC_QUOT, KC_GRV),
    [CPY_PSC] = ACTION_TAP_DANCE_TAP_HOLD(KC_COPY, KC_PSCR),
    [PST_INS] = ACTION_TAP_DANCE_TAP_HOLD(KC_PSTE, KC_INS),
    [N1] = ACTION_TAP_DANCE_TAP_HOLD_NO_REPEAT(KC_1, KC_F1),
    [N2] = ACTION_TAP_DANCE_TAP_HOLD_NO_REPEAT(KC_2, KC_F2),
    [N3] = ACTION_TAP_DANCE_TAP_HOLD_NO_REPEAT(KC_3, KC_F3),
    [N4] = ACTION_TAP_DANCE_TAP_HOLD_NO_REPEAT(KC_4, KC_F4),
    [N5] = ACTION_TAP_DANCE_TAP_HOLD_NO_REPEAT(KC_5, KC_F5),
    [N6] = ACTION_TAP_DANCE_TAP_HOLD_NO_REPEAT(KC_6, KC_F6),
    [N7] = ACTION_TAP_DANCE_TAP_HOLD_NO_REPEAT(KC_7, KC_F7),
    [N8] = ACTION_TAP_DANCE_TAP_HOLD_NO_REPEAT(KC_8, KC_F8),
    [N9] = ACTION_TAP_DANCE_TAP_HOLD_NO_REPEAT(KC_9, KC_F9),
    [N10] = ACTION_TAP_DANCE_TAP_HOLD_NO_REPEAT(KC_0, KC_F10),
    [MIN_F11] = ACTION_TAP_DANCE_TAP_HOLD_NO_REPEAT(KC_MINS, KC_F11),
    [PLS_F12] = ACTION_TAP_DANCE_TAP_HOLD_NO_REPEAT(KC_PLUS, KC_F12)
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
