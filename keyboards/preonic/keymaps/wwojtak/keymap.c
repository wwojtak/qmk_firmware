/* Copyright 2015-2017 Jack Humbert
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
#include "muse.h"

#ifdef RGBLIGHT_ENABLE
int RGB_current_mode;
extern rgblight_config_t rgblight_config;
#endif

#ifdef RAW_ENABLE
#include "raw_hid.h"
bool is_hid_connected = false;
extern keymap_config_t keymap_config;
#endif
bool layer_dvorak = true;
bool caps_on = false;

enum preonic_layers {
  _QWERTY,
  _DVORAK,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  DVORAK,
  LOWER,
  RAISE,
  RGBRST,
  MCAPS
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | CAPS |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | GUI  | Alt  | Ctrl |Lower |Space |Space |Raise | GUI  | Alt  |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid( \
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,  \
  MCAPS ,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  \
  _______, KC_LGUI, KC_LALT, KC_LCTRL, LOWER,  KC_SPC,  KC_ENT,   RAISE,  KC_RGUI, KC_LALT, _______, _______   \
),


 /* Dvorak
  * ,-----------------------------------------------------------------------------------.
  * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   `  |
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | /    |
  * |------+------+------+------+------+-------------+------+------+------+------+------|
  * | Bksp |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  | Enter|
  * |------+------+------+------+------+------|------+------+------+------+------+------|
  * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  | Shift|
  * |------+------+------+------+------+------+------+------+------+------+------+------|
  * |      | GUI  | Alt  | Ctrl |Lower |Space |Space |Raise | GUI  | Alt  |      |      |
  * `-----------------------------------------------------------------------------------'
  */
  [_DVORAK] = LAYOUT_preonic_grid( \
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,  \
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, \
    KC_BSPC, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_ENT, \
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT, \
    _______, KC_LGUI, KC_LALT, KC_LCTRL, LOWER,  KC_SPC,  KC_SPC,   RAISE,  KC_RGUI, KC_RALT, _______, _______  \
  ),


/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Bksp |   4  |   5  |   6  |  -   |   =  |  Left| Down |  Up  | Right|      | Ent  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Shift |   7  |   8  |   9  |   0  |      | Play |VolUp |VolDn | Next |      |Shift |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | GUI  | Alt  | Ctrl |Lower |Space |Enter |Raise | GUI  | Alt  |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
  KC_TAB,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,  \
  KC_BSPC,  KC_4,    KC_5,    KC_6,    KC_MINS, KC_EQL,  KC_LEFT, KC_DOWN,  KC_UP, KC_RIGHT, _______, KC_ENT, \
  KC_LSFT, KC_7,    KC_8,    KC_9,    KC_0,    _______,  KC_MPLY, KC_VOLD, KC_VOLU, KC_MNXT, _______, KC_RSFT, \
  _______,  KC_LGUI, KC_LALT, KC_LCTRL, LOWER,  KC_SPC,  KC_ENT,   RAISE,  KC_RGUI, KC_RALT, _______, _______ \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Bksp |  [   |  ]   |  (   |   )  |      |   *  |   4  |   5  |   6  |   -  | Ent  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Shift |  \   |  #   |  `   |      |      |  /   |   1  |   2  |   3  |   =  | Shift|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | GUI  | Alt  | Ctrl |Lower |Enter |Space |Raise | GUI  | Alt  |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
  KC_TAB,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,      KC_7,    KC_8,    KC_9,  KC_0,    KC_DEL,  \
  KC_BSPC, KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, XXXXXXX, KC_ASTR,   KC_4,    KC_5,    KC_6, KC_MINS, KC_ENT, \
  KC_LSFT, KC_GRV,  KC_BSLS, KC_NUBS, XXXXXXX, XXXXXXX, KC_SLSH,   KC_1,    KC_2,    KC_3,  KC_EQL, KC_RSFT, \
  _______, KC_LGUI, KC_LALT, KC_LCTRL, LOWER,  KC_ENT,  KC_SPC,   RAISE,  KC_RGUI, KC_RALT, _______, _______ \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |TermOn|TermOf|Debug | MuMod| AuOn |AuOff |MuvDe |MuvIn | MuOn |MuOff | MiOn | MiOff|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |RGBTOG|RGBHUI|RGBSAI|RGBVAI|      |RGBRST|      |Qwerty|Dvorak|      |Sleep |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |RGBMOD|RGBHUD|RGBSAD|RGBVAD|      |RESET |      |CGNORM|CGSWAP|      |      | CAPS |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | GUI  | Alt  | Ctrl |Lower |Space |Space |Raise | GUI  | Alt  |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   \
  TERM_ON, TERM_OFF, DEBUG,   MU_MOD,  AU_ON,   AU_OFF,  MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  \
  RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, RGBRST,  XXXXXXX, QWERTY , DVORAK, XXXXXXX, KC_SLEP, XXXXXXX, \
  RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, RESET  , XXXXXXX, CG_NORM, CG_SWAP, XXXXXXX, XXXXXXX, MCAPS, \
  _______, KC_LGUI, KC_LALT, KC_LCTRL, LOWER,  KC_SPC,  KC_SPC,   RAISE,  KC_RGUI, KC_RALT, _______, _______  \
)


};

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

void keyboard_post_init_user(void) {
    uint8_t default_layer = 0;
    default_layer = eeconfig_read_default_layer();
    if (default_layer & (1UL << _QWERTY)) {
      layer_dvorak = false;
    }
}

void suspend_power_down_user(void) {
    rgblight_disable_noeeprom();

}

void suspend_wakeup_init_user(void) {
    rgblight_enable_noeeprom();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
            layer_dvorak = false;
          }
          return false;
          break;
        case DVORAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_DVORAK);
            layer_dvorak = true;
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case MCAPS:
        if (record->event.pressed) {
          register_code(KC_CAPS);
          caps_on = !caps_on;
        } else {
          unregister_code(KC_CAPS);
        }
        return false;
        break;
        case RGBRST:
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
          return false;
          break;
      }
    return true;
};

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
}

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            break;
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
}


void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}

#ifdef RAW_ENABLE
void raw_hid_receive(uint8_t *data, uint8_t length) {
  uint8_t data_send[32] = {0};
  data_send[1]=0; // swap_lctl_lgui
  // data[1] == 1 means it's running on OSX
  data_send[2]=0; // default_layer_set
  // data[2] == 1 means we're using QWERTY layout
  is_hid_connected = true;
  // Process received data
  if (length > 1 && data[1] == 1 && !keymap_config.swap_lctl_lgui) {
      keymap_config.swap_lctl_lgui = true;
  }

  if (length > 1 && data[2] == 1 && layer_dvorak) {
      default_layer_set(1UL<<_QWERTY);
      layer_dvorak = false;

  } else if (length > 1 && data[2] == 0 && !layer_dvorak) {
      default_layer_set(1UL<<_DVORAK);
      layer_dvorak = true;
      if (caps_on) {
        register_code(KC_CAPS);
        caps_on = !caps_on;
        unregister_code(KC_CAPS);
      }
  }

  if (keymap_config.swap_lctl_lgui) {
    data_send[1]=1;
  }
  if (!layer_dvorak) {
    data_send[2]=1;
  }
  // data is sent with additional bit
  raw_hid_send(data_send, sizeof(data_send));

  return;
}
#endif