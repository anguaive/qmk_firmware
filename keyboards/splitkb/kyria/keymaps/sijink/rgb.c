#include "rgb.h"
#include "color.h"
#include "gpio.h"
#include "rgblight.h"

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

const rgblight_segment_t PROGMEM rgb_layer_numsym[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_AZURE},
    {31, 7, HSV_AZURE}
);

const rgblight_segment_t PROGMEM rgb_layer_fun[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_GREEN},
    {31, 7, HSV_GREEN}
);

const rgblight_segment_t PROGMEM rgb_layer_nav[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_WHITE},
    {31, 7, HSV_WHITE}
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
    rgb_layer_base, rgb_layer_sym, rgb_layer_num, rgb_layer_numsym, rgb_layer_fun, rgb_layer_nav, rgb_layer_hun
);

// QMK impl
layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _CANARY));
    return state;
}

// QMK impl
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _CANARY));
    rgblight_set_layer_state(1, layer_state_cmp(state, _SYM));
    rgblight_set_layer_state(2, layer_state_cmp(state, _NUM));
    rgblight_set_layer_state(3, layer_state_cmp(state, _NUMSYM));
    rgblight_set_layer_state(4, layer_state_cmp(state, _FUN));
    rgblight_set_layer_state(5, layer_state_cmp(state, _NAV));
    rgblight_set_layer_state(6, layer_state_cmp(state, _HUN));

    cached_layer_state = state;
    return state;
}

void disable_onboard_liatris_led(void) {
    setPinOutput(24);
    writePinHigh(24);
}

void rgblight_setup(void) {
    rgblight_enable_noeeprom();
   rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
    rgblight_set_speed_noeeprom(32);

    rgblight_layers = rgb_layers;
}
