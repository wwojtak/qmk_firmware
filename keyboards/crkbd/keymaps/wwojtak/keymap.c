#include QMK_KEYBOARD_H
#include "wwojtak.h"

#define QMK_ESC_OUTPUT F4
#define QMK_ESC_INPUT D4
#define QMK_LED B0


#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

#ifdef RAW_ENABLE
#include "raw_hid.h"
#endif

bool layer_dvorak = true;
bool caps_on = false;

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum crkbd_layers {
  _DVORAK,
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  QWERTY,
  LOWER,
  RAISE,
  ADJUST,
  RGBRST,
  MCAPS
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [_DVORAK] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, KC_QUOT, KC_COMM,  KC_DOT,    KC_P,    KC_Y,                         KC_F,    KC_G,    KC_C,    KC_R,   KC_L,  KC_SLSH,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSPC,    KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                         KC_D,    KC_H,    KC_T,    KC_N,   KC_S,  KC_ENT ,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_SCLN,    KC_Q,    KC_J,    KC_K,    KC_X,                         KC_B,    KC_M,    KC_W,    KC_V,   KC_Z,  KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL,  LOWER, KC_SPC,       KC_SPC, RAISE,  KC_LALT \
                                      //`--------------------------'  `--------------------------'

  ),

  [_QWERTY] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       MCAPS ,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL,  LOWER, KC_SPC,       KC_ENT, RAISE,  KC_LALT \
                                      //`--------------------------'  `--------------------------'

  ),

  [_LOWER] = LAYOUT( \
  //,---------------!--------"--------£--------$----- --%-.                    ,------^--------&--------*--------(--------)----------.
       KC_TAB,  KC_F1,   KC_F2,   KC_F3,  KC_F4,  _______,                    _______,  _______,  _______,  _______,  _______, KC_DEL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSPC, KC_F5,    KC_F6,   KC_F7,  KC_F8,  _______,                     KC_LEFT,  KC_DOWN,  KC_UP,  KC_RIGHT, _______, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_F9,   KC_F10,  KC_F11,  KC_F12, _______,                     KC_MPRV,  KC_VOLD,  KC_VOLU,KC_MNXT,  KC_MPLY, _______,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   LOWER, KC_SPC,      KC_SPC, RAISE, KC_LALT \
                                      //`--------------------------'  `--------------------------'
  ),


  [_RAISE] = LAYOUT( \
  //,---------------!--------"--------£--------$----- --%-.                    ,------^--------&--------*--------(--------)----------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_DEL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSPC, KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, XXXXXXX,                      KC_ASTR,    KC_4,    KC_5,    KC_6, KC_MINS, KC_LCTL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_GRV,  KC_BSLS, KC_NUBS, XXXXXXX, XXXXXXX,                      KC_SLSH,    KC_1,    KC_2,    KC_3,  KC_EQL, KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   LOWER, KC_SPC,      KC_SPC, RAISE, KC_LALT \
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, _______,                   _______, _______,  _______,  _______, _______, _______,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, RGBRST,                       XXXXXXX, QWERTY , DVORAK, XXXXXXX, KC_SLEP, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, EEP_RST, RESET  ,                      XXXXXXX, CG_NORM, CG_SWAP, XXXXXXX, XXXXXXX, MCAPS,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL,   LOWER, KC_SPC,     KC_SPC, RAISE, KC_LALT \
                                      //`--------------------------'  `--------------------------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_LCTL:
#ifdef OCEAN_DREAM_ENABLE
            is_calm = (record->event.pressed) ? true : false;
#endif
#ifdef LUNA_ENABLE
            if (record->event.pressed) {
                isSneaking = true;
            } else {
                isSneaking = false;
            }
#endif
            break;
        case KC_SPC:
#ifdef LUNA_ENABLE
            if (record->event.pressed) {
                isJumping  = true;
                showedJump = false;
            } else {
                isJumping = false;
            }
#endif
            break;
    case DVORAK:
      if (record->event.pressed) {
        default_layer_set(1UL<<_DVORAK);
        layer_dvorak = true;
      }
      return false;
    case QWERTY:
      if (record->event.pressed) {
        default_layer_set(1UL<<_QWERTY);
        layer_dvorak = false;
      }
      return false;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
    case MCAPS:
        if (record->event.pressed) {
          register_code(KC_CAPS);
        } else {
          unregister_code(KC_CAPS);
          caps_on = !caps_on;
        }
        return false;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      #ifdef RGB_MATRIX_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgb_matrix_default();
          rgb_matrix_enable();
        }
      #endif
      break;
  }
  return true;
}


#ifdef RAW_ENABLE

void raw_hid_receive(uint8_t *data, uint8_t length) {
  uint8_t data_send[32] = {0};
  data_send[1]=0; // swap_lctl_lgui
  // data[1] == 1 means it's running on OSX
  data_send[2]=0; // default_layer_set
  // data[2] == 1 means we're using QWERTY layout
  // Process received data
  if (length > 1 && data[1] == 1 && !keymap_config.swap_lctl_lgui) {
      keymap_config.swap_lctl_lgui = true;
  } else if (length > 1 && data[1] == 0 && keymap_config.swap_lctl_lgui) {
      keymap_config.swap_lctl_lgui = false;
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
