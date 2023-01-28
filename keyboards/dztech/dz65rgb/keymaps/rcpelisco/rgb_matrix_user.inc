/* Copyright 2021 Felix Springer
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
RGB_MATRIX_EFFECT(base_effect)
RGB_MATRIX_EFFECT(fn_indicator)
RGB_MATRIX_EFFECT(sys_indicator)
RGB_MATRIX_EFFECT(macro_indicator)
RGB_MATRIX_EFFECT(kitt_effect)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

/*
[_LEDS]    = LAYOUT_65_ansi(
     0,   1,       2,       3,       4,       5,       6,       7,       8,       9,       10,      11,      12,      13,      14,
    15,   16 Q,    17 W,    18 E,    19 R,    20 T,    21 Y,    22 U,    23 I,    24 O,    25 P,    26 [,    27 ],    28 \,    29,
    30,   31 A,    32 S,    33 D,    34 F,    35 G,    36 H,    37 J,    38 K,    39 L,    40,      41,               42,      43,
    44,            45 Z,    46 X,    47 C,    48 V,    49 B,    50 N,    51 M,    52 <,    53 >,    54,      55,      56,      57,
    58,   59,      60,                                 61,                        62,      63,      64,      65,      66,      67
)
*/

// variable for startup animation
bool BASE_EFFECT_NOT_STARTED_YET = true;
uint8_t base_effect_startup_counter = 255;

static HSV base_effect_math(HSV hsv, uint8_t i, uint8_t time) {

    if (BASE_EFFECT_NOT_STARTED_YET) {
        base_effect_startup_counter = 0;
        BASE_EFFECT_NOT_STARTED_YET = false;
    }

    // end animation
    if (base_effect_startup_counter >= 255) {
        switch (i) {

            case 57: 
                hsv.h = 148;
                break;
            case 43: 
                hsv.h = 160;
                break;
            case 29:
                hsv.h = 222;
                break;
            case 14:
                hsv.h = 255;
                break;
            default:
                hsv.v = 0;
                break;
        }
        return hsv;
    }

    // startup animation
    if (i == 0) { // only run for one key (key 0 is an arbitrary choice)
        if (base_effect_startup_counter == 0) {
            base_effect_startup_counter = 1; 
        } else if (base_effect_startup_counter == 70) {
            base_effect_startup_counter = 100; 
        } else if (base_effect_startup_counter == 120) {
            base_effect_startup_counter = 255; 
        } else {
            base_effect_startup_counter++;
        }
    }

    // clear rgb
    if (14 - i < base_effect_startup_counter - 100 && i >= 0 && i <= 14) {
        hsv.v = 0;
    } else if (29 - i < base_effect_startup_counter - 100 && i >= 15 && i <= 29) {
        hsv.v = 0;
    } else if (43 - i < base_effect_startup_counter - 100 && i >= 30 && i <= 43) {
        hsv.v = 0;
    } else if (57 - i < base_effect_startup_counter - 100 && i >= 44 && i <= 57) {
        hsv.v = 0;
    } else if (67 - i < base_effect_startup_counter - 100 && i >= 58 && i <= 67) {
        hsv.v = 0;

    // lightup all keys
    } else if (i < base_effect_startup_counter && i >= 0 && i <= 14) {
        hsv.s = 0;
    } else if (15 + 29 - i < base_effect_startup_counter && i >= 15 && i <= 29) {
        hsv.s = 0;
    } else if (i < base_effect_startup_counter && i >= 30 && i <= 43) {
        hsv.s = 0;
    } else if (44 + 57 - i < base_effect_startup_counter && i >= 44 && i <= 57) {
        hsv.s = 0;
    } else if (i < base_effect_startup_counter && i >= 58 && i <= 67) {
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

static HSV fn_indicator_math(HSV hsv, uint8_t i, uint8_t time) {

    // cancel base effect startup
    base_effect_startup_counter = 255;

    switch (i) {

        case 57:
            hsv.h = 64;
            break;
        case 43:
            hsv.h = 64;
            break;

        // cycle effect
        case 16:
            hsv.s = 255;
            hsv.v = 255;
            if (time < (255 / 3)) {
                hsv.h = 0;
            } else if (time < (2 * 255 / 3)) {
                hsv.h = 255 / 3;
            } else {
                hsv.h = 2 * 255 / 3;
            }
            break;

        // adjust hue
        case 17:
            hsv.h = 255 - time;
            hsv.s = 255;
            hsv.v = 255;
            break;
        case 18:
            hsv.h = time;
            hsv.s = 255;
            hsv.v = 255;
            break;
        
        // adjust saturation
        case 19:
            hsv.s = 0;
            hsv.v = 255;
            break;
        case 20:
            hsv.s = 255;
            hsv.v = 255;
            break;

        // adjust value
        case 31:
            hsv.v = 63;
            break;
        case 32:
            hsv.v = 255;
            break;

        // adjust speed
        case 45:
            if (((time / 16) % 2) == 0) {
                hsv.v = 63;
            } else {
                hsv.v = 255;
            }
            break;
        case 46:
            if (((time / 4) % 2) == 0) {
                hsv.v = 255;
            } else {
                hsv.v = 63;
            }
            break;

        default:
            hsv.v = 0;
            break;

    }

    return hsv;
}

bool fn_indicator(effect_params_t* params) {
    return effect_runner_i(params, &fn_indicator_math);
}

static HSV sys_indicator_math(HSV hsv, uint8_t i, uint8_t time) {

    // no startup animation
    if (BASE_EFFECT_NOT_STARTED_YET) {
        base_effect_startup_counter = 255; // act like startup is already completed
        BASE_EFFECT_NOT_STARTED_YET = false;
    }

    switch (i) {
        case 57: 
            hsv.h = 106;
            break;
        case 43: 
            hsv.h = 148;
            break;
        case 29: 
            hsv.h = 222;
            break;
        // QK_BOOT
        case 13:
            hsv.s = 0;
            if (time < 16) {
                hsv.v = 255 - time * 128 / 16;
            } else {
                hsv.v = 127;
            }
            break;
        // QK_RBT
        case 28:
            hsv.s = 0;
            if (time < 16) {
                hsv.v = 255 - time * 128 / 16;
            } else {
                hsv.v = 127;
            }
            break;

        // EE_CLR (reinitialize EEPROM)
        case 42:
            hsv.s = 0;
            hsv.v = 127;
            break;

        default:
            hsv.v = 0;
            break;
    }

    return hsv;
}

bool sys_indicator(effect_params_t* params) {
    return effect_runner_i(params, &sys_indicator_math);
}

static HSV macro_indicator_math(HSV hsv, uint8_t i, uint8_t time) {

    // cancel base effect startup
    base_effect_startup_counter = 255;

    switch (i) {

        case 57: 
            hsv.h = 148;
            break;
        case 43: 
            hsv.h = 160;
            break;
        case 29:
            hsv.h = 222;
            break;
        case 14:
            hsv.h = 255;
            break;
        default:
            hsv.v = 0;
            break;

    }

    return hsv;
}

bool macro_indicator(effect_params_t* params) {
    return effect_runner_i(params, &macro_indicator_math);
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

// vim: syntax=c
