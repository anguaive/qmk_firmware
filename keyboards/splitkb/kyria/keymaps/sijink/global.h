#pragma once

#include "action_layer.h"
#include "quantum_keycodes.h"

layer_state_t cached_layer_state;

enum layers {
    _CANARY = 0,
    _SYM,
    _NUM,
    _NUMSYM,
    _FUN,
    _NAV,
    _MOUSE,
    _HUN,
    _ADJUST,
};

enum tap_dance_keys { TD_SLSH, TD_QUOT };

enum keycodes {
    // OSL(...), but not reset by keypresses in higher layers
    OSL_SYM = SAFE_RANGE,
    OSL_FUN,
    // TG(...), but on keydown
    TG_NUM,
    TG_NUMSYM,
    // accented hungarian characters
    A_ACUT,
    E_ACUT,
    I_ACUT,
    O_ACUT,
    O_DACUT,
    O_UMLAU,
    U_ACUT,
    U_DACUT,
    U_UMLAU,
    // callum oneshot mods
    OS_SHFT,
    OS_CTRL,
    OS_ALT,
    OS_GUI,
};
