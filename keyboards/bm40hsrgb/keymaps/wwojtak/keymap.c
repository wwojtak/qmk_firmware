/* Copyright 2020 tominabox1
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

enum layers {
  _DVORAK,
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};


#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define QWERTY MO(_QWERTY)
#define DVORAK MO(_DVORAK)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | /    |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Bksp |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | BLTog| GUI  | Alt  | Ctrl |Lower |Space |Space |Raise | GUI  | Alt  |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT_planck_mit(
   KC_ESC,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH,
   KC_BSPC, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_ENT,
   KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
   RGB_TOG, KC_LGUI, KC_LALT, KC_LCTRL, LOWER,  KC_SPC,   RAISE,  KC_RGUI, KC_RALT, _______, _______
),

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | BLTog| GUI  | Alt  | Ctrl |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_mit(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    RGB_TOG, KC_LGUI, KC_LALT, KC_LCTRL, LOWER,   KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

 /* Lower
  * ,-----------------------------------------------------------------------------------.
  * | Tab  |  F1  |  F2  |  F3  |  F4  |      |      |      |      |      |      | Del  |
  * |------+------+------+------+------+-------------+------+------+------+------+------|
  * | Bksp |  F5  |  F6  |  F7  |  F8  |      |  Left| Down |  Up  | Right|      |      |
  * |------+------+------+------+------+------|------+------+------+------+------+------|
  * |      |  F9  |  F10 |  F11 |  F12 |      | Prev |VolUp |VolDn | Next |Play  |      |
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * |      | GUI  | Alt  | Ctrl |Lower |     Enter   |Raise | GUI  | Alt  |      |      |
  * `-----------------------------------------------------------------------------------'
  */
 [_LOWER] = LAYOUT_planck_mit(
   KC_TAB,   KC_F1,    KC_F2,    KC_F3,    KC_F4,   _______,  _______,  _______,  _______,  _______,  _______, KC_DEL,
   KC_BSPC,  KC_F5,    KC_F6,    KC_F7,    KC_F8,   _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT, _______, _______,
   _______,  KC_F9,    KC_F10,   KC_F11,   KC_F12,  _______,  KC_MPRV,  KC_VOLD,  KC_VOLU,  KC_MNXT,  KC_MPLY, KC_RSFT,
   _______,  KC_LGUI,  KC_LALT,  KC_LCTRL, LOWER,   KC_ENT,             RAISE,    KC_RGUI,  KC_RALT,  _______, _______
 ),

 /* Raise
  * ,-----------------------------------------------------------------------------------.
  * |      |      |      |      |      |      |      |   7  |   8  |   9  |   0  | Del  |
  * |------+------+------+------+------+-------------+------+------+------+------+------|
  * | Bksp |  [   |  ]   |  (   |   )  |      |   *  |   4  |   5  |   6  |   -  | RGUI |
  * |------+------+------+------+------+------|------+------+------+------+------+------|
  * |Shift |  \   |  #   |  `   |      |      |  /   |   1  |   2  |   3  |   =  | Shift|
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * |      | GUI  | Alt  | Ctrl |Lower |    Enter    |Raise | GUI  | Alt  |      |      |
  * `-----------------------------------------------------------------------------------'
  */
 [_RAISE] = LAYOUT_planck_mit(
   KC_TAB,  _______, _______, _______, _______, _______, _______,   KC_7,    KC_8,    KC_9,  KC_0,    KC_DEL,
   KC_BSPC, KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, _______, KC_ASTR,   KC_4,    KC_5,    KC_6, KC_MINS, KC_RGUI,
   KC_LSFT, KC_GRV,  KC_BSLS, KC_NUBS, _______, _______, KC_SLSH,   KC_1,    KC_2,    KC_3,  KC_EQL, KC_RSFT,
   _______, KC_LGUI, KC_LALT, KC_LCTRL, LOWER,  KC_ENT,   RAISE,  KC_RGUI, KC_RALT, _______, _______
 ),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |RGBTOG|RGBHUI|RGBSAI|RGBVAI|      |      |      |Qwerty|Dvorak|      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |RGBMOD|RGBHUD|RGBSAD|RGBVAD|      |RESET |      |CGNORM|CGSWAP|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_mit(
    _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______,
    RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______,  _______, QWERTY , DVORAK, _______, KC_SLEP, _______,
    RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______, RESET  , _______, CG_NORM, CG_SWAP, _______, _______, _______,
    _______, _______, _______, _______, LOWER,  _______,   RAISE,  _______, _______, _______, _______
)

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
