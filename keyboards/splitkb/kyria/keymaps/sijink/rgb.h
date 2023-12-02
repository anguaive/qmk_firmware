#pragma once

#include "action_layer.h"
#include "global.h"
#include "rgblight.h"

// TODO: document all of this basically

extern const rgblight_segment_t PROGMEM rgb_layer_base[];
extern const rgblight_segment_t PROGMEM rgb_layer_sym[];
extern const rgblight_segment_t PROGMEM rgb_layer_num[];
extern const rgblight_segment_t PROGMEM rgb_layer_nav[];
extern const rgblight_segment_t PROGMEM rgb_layer_hun[];
extern const rgblight_segment_t* const PROGMEM rgb_layers[];

void disable_onboard_liatris_led(void);

void rgblight_setup(void);
