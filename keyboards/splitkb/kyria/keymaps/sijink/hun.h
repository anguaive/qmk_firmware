#pragma once

#include "action.h"

#define SIJ_ACUTE  SS_DOWN(X_RALT)"'"SS_UP(X_RALT)
#define SIJ_DACUTE SS_DOWN(X_RALT)SS_DOWN(X_LSFT)"2"SS_UP(X_LSFT)SS_UP(X_RALT)
#define SIJ_UMLAUT SS_DOWN(X_RALT)"\""SS_UP(X_RALT)

// US_INTL (altgr, no dead keys) OS keyboard layout must be used for
// hungarian accented letters to work.
// TODO: describe how the HUN layer works (I forgot)
bool process_hun_macros(uint16_t keycode, keyrecord_t *record);
