#pragma once

#include "action_layer.h"
#include "quantum_keycodes.h"

layer_state_t cached_layer_state;

enum layers {
    _CANARY = 0,
    _SYM,
    _NUM,
    _NUMSYM,
    _NAV,
    _MOUSE,
    _HUN,
    _ADJUST,
};

enum keycodes {
    // OSL(...), but not reset by keypresses in higher layers
    OSL_SYM = SAFE_RANGE,
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
    U_UMLAU
};
