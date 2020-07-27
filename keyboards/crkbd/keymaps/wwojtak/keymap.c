#include QMK_KEYBOARD_H


#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#ifdef OLED_DRIVER_ENABLE
static uint32_t oled_timer = 0;
#endif

#ifdef RAW_ENABLE
#include "raw_hid.h"
bool is_hid_connected = false;
#endif

bool layer_dvorak = true;

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum crkbd_layers {
  _QWERTY,
  _DVORAK,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  DVORAK,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

// enum {
//     TD_GUI_CTRL,
// };
//
// qk_tap_dance_action_t tap_dance_actions[] = {
//     // Tap once for GUI, twice for Ctrl
//     [TD_GUI_CTRL] = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, KC_LCTL),
// };


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_CAPS,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL,  LOWER, KC_SPC,       KC_ENT, RAISE,  KC_LALT \
                                      //`--------------------------'  `--------------------------'

  ),

  [_DVORAK] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, KC_QUOT, KC_COMM,  KC_DOT,    KC_P,    KC_Y,                         KC_F,    KC_G,    KC_C,    KC_R,   KC_L,  KC_SLSH,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSPC,    KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                         KC_D,    KC_H,    KC_T,    KC_N,   KC_S,  KC_LGUI,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_SCLN,    KC_Q,    KC_J,    KC_K,    KC_X,                         KC_B,    KC_M,    KC_W,    KC_V,   KC_Z,  KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL,  LOWER, KC_SPC,       KC_ENT, RAISE,  KC_LALT \
                                      //`--------------------------'  `--------------------------'

  ),

  [_LOWER] = LAYOUT( \
  //,---------------!--------"--------£--------$----- --%-.                    ,------^--------&--------*--------(--------)----------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_DEL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSPC,    KC_4,    KC_5,    KC_6, KC_MINS, KC_EQL,                      KC_LEFT, KC_DOWN,  KC_UP, KC_RIGHT, XXXXXXX, KC_LCTL,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_7,    KC_8,    KC_9,    KC_0, XXXXXXX,                     KC_MPLY, KC_VOLD, KC_VOLU, KC_MNXT, XXXXXXX, KC_RSFT,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   LOWER, KC_SPC,      KC_ENT, RAISE, KC_LALT \
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
                                          KC_LGUI,   LOWER, KC_SPC,      KC_ENT, RAISE, KC_LALT \
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                      KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, RGBRST,                       XXXXXXX, QWERTY , DVORAK, XXXXXXX, KC_SLEP,  RESET,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, EH_LEFT,                      EH_RGHT, CG_NORM, CG_SWAP, XXXXXXX, XXXXXXX, KC_CAPS,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL,   LOWER, KC_SPC,     KC_ENT, RAISE, KC_LALT \
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
  if (record->event.pressed) {
    #ifdef OLED_DRIVER_ENABLE
            oled_timer = timer_read32();
    #endif
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
        layer_dvorak = false;
      }
      return false;
    case DVORAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_DVORAK);
        layer_dvorak = true;
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

#ifdef RGB_MATRIX_ENABLE

void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}

#endif

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

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_master) {
        return OLED_ROTATION_270;
    }  else {
        return OLED_ROTATION_180;
    }
}

void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

void render_layer(void) {
    switch (biton32(layer_state)){
      case _LOWER:
        oled_write_ln_P(PSTR("LOWER"), false);
        break;
      case _RAISE:
        oled_write_ln_P(PSTR("RAISE"), false);
        break;
      case _ADJUST:
        oled_write_ln_P(PSTR("ADJST"), false);
        break;
      default:
        if (layer_dvorak) {
          oled_write_ln_P(PSTR("DVORK"), false);
        } else {
          oled_write_ln_P(PSTR("QWRTY"), false);
        }
      }
}

void susuwatari_logo(void) {
   static const char PROGMEM suswatari_logo[] = {
      0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
      0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
      0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
      0};
    oled_write_P(suswatari_logo, false);
}

char mode_icon[24];

void read_mode_icon(bool swap) {
  static const char PROGMEM win_logo[] = {
        0x20, 0x20, 0x97, 0x98, 0x20, 
        0x20, 0x20, 0xb7, 0xb8, 0x20, 
        0x20, 0x20, 0xd7, 0xd8, 0x20, 0};
  static const char PROGMEM osx_logo[] = {
        0x20, 0x20, 0x95, 0x96, 0x20,
        0x20, 0x20, 0xb5, 0xb6, 0x20,
        0x20, 0x20, 0xd5, 0xd6, 0x20, 0};
  if (swap) {
    oled_write_P(osx_logo, false);
  } else {
    oled_write_P(win_logo, false);
  }
}

void render_status_main(void) {
    render_space();
    render_space();
    render_space();
    read_mode_icon(keymap_config.swap_lctl_lgui);
    render_space();
    render_layer();
}

void render_status_secondary(void) {
    susuwatari_logo();
}

void oled_task_user(void) {
  if (timer_elapsed32(oled_timer) > 300000) {
        oled_off();
        return;
    }
    else { oled_on(); }

    if (is_master) {
        render_status_main();
    } else {
        render_status_secondary();
    }
}

#endif
