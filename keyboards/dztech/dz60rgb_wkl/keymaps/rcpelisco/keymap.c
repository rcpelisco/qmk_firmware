 /* Copyright 2021 Daniil <Macbet> Kivenko
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
#include "os_detection.h"

enum dz60rgb_wkl_layers {
    _BASE_MAC,
    _BASE_WIN,
    _MO1,
    _MO2,
    _MO3,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE_MAC] = LAYOUT_60_tsangan_hhkb(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        SC_LSPO,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SC_RSPC, MO(_MO1),
        _______, KC_LALT, KC_LGUI,                            KC_SPC,                                      KC_RGUI, KC_RALT, _______
    ),
    [_BASE_WIN] = LAYOUT_60_tsangan_hhkb(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        SC_LSPO,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SC_RSPC, MO(_MO1),
        _______, KC_LGUI, KC_LALT,                            KC_SPC,                                      KC_RALT, KC_RGUI, _______
    ),
    [_MO1] = LAYOUT_60_tsangan_hhkb(
        KC_PWR,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, KC_UP,   _______, _______,
        _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, _______, _______, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, KC_END,  KC_PGDN, KC_DOWN, _______, _______,
        _______, _______, _______,                            _______,                                     MO(_MO2),   _______, _______
    ),
    [_MO2] = LAYOUT_60_tsangan_hhkb(
        _______, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  KC_DEL,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                            _______,                                     _______, _______, _______
    ),
    [_MO3] = LAYOUT_60_tsangan_hhkb(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                            _______,                                     _______, _______, _______
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _BASE_MAC:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_base_effect_mac);
            break;
        case _BASE_WIN:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_base_effect_win);
            break;
        case _MO1:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_mo1_indicator);
            break;
        case _MO2:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_mo2_indicator);
            break;
        case _MO3:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_kitt_effect);
            break;
    }
    return state;
}

// Copyright 2023 Google LLC.
// SPDX-License-Identifier: Apache-2.0

void keyboard_post_init_user(void) {
  // Set default layer based on the detected OS after a 500 ms delay.
  uint32_t get_host_os(uint32_t trigger_time, void* cb_arg) {
    switch (detected_host_os()) {
      case OS_UNSURE:  // Don't change default layer if unsure.
        break;
      case OS_MACOS:   // On Mac, set default layer to BASE_MAC.
      case OS_IOS:
        set_single_persistent_default_layer(_BASE_MAC);
        break;
      default:         // On Windows and Linux, set to BASE_WIN.
        set_single_persistent_default_layer(_BASE_WIN);
        break;
    }
    return 0;
  }
  defer_exec(500, get_host_os, NULL);
}