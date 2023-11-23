RGB_MATRIX_EFFECT(base_effect)
RGB_MATRIX_EFFECT(mo1_indicator)
RGB_MATRIX_EFFECT(mo2_indicator)
RGB_MATRIX_EFFECT(kitt_effect)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

/*
[_LEDS]    = LAYOUT_60_tsangan_hhkb(
  14,   13,       12,       11,      10,       9,       8,       7,       6,       5,       4,       3,       2,     1,      0,     
  28,   27 Q,    26 W,    25 E,    24 R,    23 T,    22 Y,    21 U,    20 I,    19 O,    18 P,    17 [,    16 ],    15,
  41,   40 A,    39 S,    38 D,    37 F,    36 G,    35 H,    34 J,    33 K,    32 L,    31 ;,    30 ',    29,      
  54,   53 Z,    52 X,    51 C,    50 V,    49 B,    48 N,    47 M,    46 <,    45 >,    44 ?,    43,      42,      
  61,   60,      59,                           58,                     57,      56,      55,
)
*/

// variable for startup animation
bool BASE_EFFECT_NOT_STARTED_YET = true;
uint8_t base_effect_startup_counter = 255;
uint8_t end_row_1 = 14;
uint8_t end_row_2 = 28;
uint8_t end_row_3 = 41;
uint8_t end_row_4 = 54;
uint8_t end_row_5 = 61;


static HSV base_effect_math(HSV hsv, uint8_t i, uint8_t time) {

    if (BASE_EFFECT_NOT_STARTED_YET) {
        base_effect_startup_counter = 0;
        BASE_EFFECT_NOT_STARTED_YET = false;
    }

    // end animation
    if (base_effect_startup_counter >= 255) {
      hsv.v = 0;
      return hsv;
    }

    
    // startup animation
    if (i == 0) { // only run for one key (key 0 is an arbitrary choice)
        if (base_effect_startup_counter == 0) {
            base_effect_startup_counter = 1; 
        } else if (base_effect_startup_counter == 70) {
            base_effect_startup_counter = 127; 
        } else if (base_effect_startup_counter == 120) {
            base_effect_startup_counter = 255; 
        } else {
            base_effect_startup_counter++;
        }
    }

    // clear rgb
    if (end_row_1 - i < base_effect_startup_counter - 127 && i >= 0 && i <= end_row_1) {
        hsv.v = 0;
    } else if (end_row_2 - i < base_effect_startup_counter - 127 && i >= end_row_1 + 1 && i <= end_row_2) {
        hsv.v = 0;
    } else if (end_row_3 - i < base_effect_startup_counter - 127 && i >= end_row_2 + 1 && i <= end_row_3) {
        hsv.v = 0;
    } else if (end_row_4 - i < base_effect_startup_counter - 127 && i >= end_row_3 + 1 && i <= end_row_4) {
        hsv.v = 0;
    } else if (end_row_5 - i < base_effect_startup_counter - 127 && i >= end_row_4 + 1 && i <= end_row_5) {
        hsv.v = 0;

    // lightup all keys
    } else if (end_row_1 - i < base_effect_startup_counter && i >= 0 && i <= end_row_1) {
        hsv.s = 0;
    } else if (i < base_effect_startup_counter && i >= (end_row_1 + 1) && i <= end_row_2) {
        hsv.s = 0;
    } else if (((end_row_2 + 1) + end_row_3) - i < base_effect_startup_counter && i >= end_row_2 + 1 && i <= end_row_3) {
        hsv.s = 0;
    } else if (i < base_effect_startup_counter && i >= end_row_3 + 1 && i <= end_row_4) {
        hsv.s = 0;
    } else if (((end_row_4 + 1) + end_row_5) - i < base_effect_startup_counter && i >= end_row_4 + 1 && i <= end_row_5) {
        hsv.s = 0;

    // rest
    } else {
        hsv.v = 0;
    }

    return hsv;
}

bool base_effect(effect_params_t* params) {
    return effect_runner_i(params, &base_effect_math);
}


static HSV mo1_indicator_math(HSV hsv, uint8_t i, uint8_t time) {

    // no startup animation
    if (BASE_EFFECT_NOT_STARTED_YET) {
        base_effect_startup_counter = 255; // act like startup is already completed
        BASE_EFFECT_NOT_STARTED_YET = false;
    }

    switch (i) {
        // KC_UP
        case 17: 
            hsv.s = 63;
            break;
        // KC_LEFT
        case 31: 
            hsv.s = 106;
            break;
        // KC_RIGHT
        case 30: 
            hsv.s = 189;
            break;
        // KC_DOWN
        case 44:
            hsv.s = 252;
            break;
        default:
            hsv.v = 0;
            break;
    }

    return hsv;
}

bool mo1_indicator(effect_params_t* params) {
    return effect_runner_i(params, &mo1_indicator_math);
}


static HSV mo2_indicator_math(HSV hsv, uint8_t i, uint8_t time) {

    // no startup animation
    if (BASE_EFFECT_NOT_STARTED_YET) {
        base_effect_startup_counter = 255; // act like startup is already completed
        BASE_EFFECT_NOT_STARTED_YET = false;
    }

    switch (i) {
        // QK_BOOT
        case 15:
            hsv.s = 0;
            if (time < 16) {
                hsv.v = 255 - time * 128 / 16;
            } else {
                hsv.v = 255;
            }
            break;

        default:
            hsv.v = 0;
            break;
    }

    return hsv;
}

bool mo2_indicator(effect_params_t* params) {
    return effect_runner_i(params, &mo2_indicator_math);
}

uint8_t led_count = 7;
uint8_t led_first = 33;
static uint8_t time_to_led(uint8_t time, uint8_t led_behind) {
    uint16_t led_time = led_count * time;
    uint16_t step = ((2 * led_count + (led_time / 128)) - led_behind) % (2 * led_count);
    uint8_t led;
    if (step < led_count) {
        led = step;
    } else {
        led = led_count - 1 - (step - led_count);
    }
    return led;
}

static HSV kitt_effect_math(HSV hsv, uint8_t i, uint8_t time) {

    // reset base effect startup
    if (i == 0) {
        BASE_EFFECT_NOT_STARTED_YET = true;
    }

    hsv.h = 0;
    hsv.s = 255;

    if (i >= led_first && i < led_first + led_count) {
        uint8_t j = i - led_first;
        if (j == time_to_led(time, 0)) {
            hsv.v = hsv.v;
        } else if (j == time_to_led(time, 1)) {
            hsv.v = hsv.v/2;
        } else if (j == time_to_led(time, 2)) {
            hsv.v = hsv.v/4;
        } else if (j == time_to_led(time, 3)) {
            hsv.v = hsv.v/8;
        } else {
            hsv.v = 0;
        }
    } else {
        hsv.v = 0;
    }

    return hsv;
}

bool kitt_effect(effect_params_t* params) {
    return effect_runner_i(params, &kitt_effect_math);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
