#include QMK_KEYBOARD_H
#ifdef CONSOLE_ENABLE
#include "print.h"
#endif

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum dz65rgb_layers {
  _OFF,
	_BASE,
	_FN,
  _SYS,
	_MACRO
};


enum {
    TD_CAPS,
};

//Function associated with all tap dances
td_state_t cur_dance (qk_tap_dance_state_t *state);

//Functions associated with individual tap dances
void ql_finished (qk_tap_dance_state_t *state, void *user_data);
void ql_reset (qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_OFF] = LAYOUT_65_ansi(
        _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        TD(TD_CAPS),_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
        _______,             _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,    _______, _______,                            _______,                   _______, _______, _______, _______, _______, _______
    ),
    [_BASE] = LAYOUT_65_ansi(
        QK_GESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
        KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        TD(TD_CAPS),KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGDN,
        KC_LSFT,             KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
        KC_LCTL,    KC_LGUI, KC_LALT,                            KC_SPC,                    KC_RALT, MO(_SYS), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FN] = LAYOUT_65_ansi(
        KC_GRV ,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  XXXXXXX,
        XXXXXXX,    RGB_TOG, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_CAPS,    RGB_VAD, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_VOLU,          XXXXXXX, XXXXXXX,
        KC_LSFT,             RGB_SPD, RGB_SPI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT, KC_UP,   XXXXXXX,
        KC_LCTL,    XXXXXXX, KC_LALT,                            KC_SPC,                    XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    // [_BASE] = LAYOUT_65_ansi(
    //     KC_GESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
    //     KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
    //     MO(_MACRO), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGDN,
    //     KC_LSFT,             KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
    //     KC_LCTL,    KC_LGUI, KC_LALT,                            KC_SPC,                    KC_RALT, MO(_FN), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    // ),
    // [_FN] = LAYOUT_65_ansi(
    //     _______,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  _______,
    //     _______,    RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, _______, _______, _______, KC_PSCR, _______, _______, _______, _______,
    //     KC_CAPS,    RGB_VAD, RGB_VAI, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_VOLU,          _______, _______,
    //     KC_LSFT,             RGB_SPD, RGB_SPI, _______, _______, _______, _______, KC_MUTE, _______, _______, _______, KC_RSFT, _______, _______,
    //     KC_LCTL,    _______, KC_LALT,                            _______),                   MO(_SYS),_______, _______, _______, _______, _______
    // ),
  
    [_SYS] = LAYOUT_65_ansi(
        XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RESET,   XXXXXXX,
        XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          EEP_RST, XXXXXXX,
        XXXXXXX,             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,    XXXXXXX, XXXXXXX,                            XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
    // [_MACRO] = LAYOUT_65_ansi(
    //     KC_GESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
    //     KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
    //     MO(_MACRO), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGDN,
    //     KC_LSFT,             KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
    //     KC_LCTL,    KC_LGUI, KC_LALT,                            KC_SPC,                    KC_RALT, MO(_FN), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    // ),
    // [_MACRO] = LAYOUT_65_ansi(
    //     KC_GESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,
    //     KC_TAB,     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
    //     TD(CAPS), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGDN,
    //     KC_LSFT,             KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
    //     KC_LCTL,    KC_LGUI, KC_LALT,                            KC_SPC,                    KC_RALT, MO(_FN), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    // ),
};         

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _BASE:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_macro_indicator);
            uprintf("_BASE\n");
            break;
        case _FN:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_fn_indicator);
            uprintf("_FN\n");
            break;
        case _SYS:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_sys_indicator);
            uprintf("_SYS\n");
            break;
        case _OFF:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_base_effect);
            uprintf("_OFF\n");
            // rgb_matrix_mode(RGB_MATRIX_CUSTOM_macro_indicator);
            break;
        default: 
            break;
    }
    return state;
}

void keyboard_post_init_user(void) {
  layer_on(_OFF);
}

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     #ifdef CONSOLE_ENABLE
//         if (record->event.pressed) {
//             uprintf("0x%04X,%u,%u,%u\n", keycode, record->event.key.row, record->event.key.col, get_highest_layer(layer_state));
//         }
//     #endif
//     switch (keycode) {
//     }
//     return true;
// }

//Determine the current tap dance state
td_state_t cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) return TD_SINGLE_TAP;
    else return TD_SINGLE_HOLD;
  } else if (state->count == 2) return TD_DOUBLE_TAP;
  else return TD_UNKNOWN;
}

//Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
  .is_press_action = true,
  .state = TD_NONE
};

//Functions that control what our tap dance key does
void ql_finished (qk_tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_HOLD: 
            layer_on(_FN); 
            break;
        case TD_DOUBLE_TAP: 
            uprintf("DOUBLE_TAP\n");
            if (layer_state_is(_BASE)) {
                layer_off(_BASE);
                layer_on(_OFF);
                uprintf("LAYER_ON OFF\n");
            } else { 
                layer_off(_OFF);
                layer_on(_BASE);
                uprintf("LAYER_ON BASE\n");
            }
            break;
        default:
            uprintf("TD_NONE\n");
            break;
    }
}

void ql_reset (qk_tap_dance_state_t *state, void *user_data) {
  //if the key was held down and now is released then switch off the layer
  if (ql_tap_state.state==TD_SINGLE_HOLD) {
    layer_off(_FN);
  }
  ql_tap_state.state = TD_NONE;
}

//Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ql_finished, ql_reset)
};
