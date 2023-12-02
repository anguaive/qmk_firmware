#pragma once

#include "action_layer.h"
#include "quantum_keycodes.h"

layer_state_t cached_layer_state;

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

