/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// QMK includes
#include QMK_KEYBOARD_H

// Layer names replacing numbers
enum layer_names {
    _BASE_,
    _F_ARR_CALC_,
    _NUM_,
    _MEDIA_,
    _TILES_
};

// words per minute string initialization
char wpm_str[10];

// if oled is enable
#ifdef OLED_ENABLE
// Import animation
// #include "ocean_dream.c"

// Supercharge oled init function to define screen rotation
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    } else {
        return OLED_ROTATION_270;
    }
    return rotation;
}

// function for master keyboard
static void left_hand_func(void) {
    // set display cursor at start of the screen
    oled_set_cursor(0, 0);

    // Define image array
    static const char PROGMEM logo_incaya[] = {
        // 'logoIncaya32x128', 32x128px
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0xc0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf8, 0xf8, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 
        0xfc, 0xfc, 0xfc, 0xfc, 0xf8, 0xf8, 0xf8, 0xf0, 0xf0, 0xe0, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x87, 0x87, 0xcf, 0xcf, 0xff, 0xff, 0xf1, 0xf1, 0xf1, 
        0xf1, 0xf1, 0xf1, 0xf3, 0xe3, 0xe3, 0xe3, 0xe7, 0xc7, 0xc7, 0x8f, 0x0f, 0x0f, 0x07, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x07, 0x07, 0x0f, 0x0f, 0x1f, 0x1f, 0x3f, 0xbf, 0xbf, 0xe7, 
        0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xcf, 0x8f, 0x0f, 0x0f, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0e, 0x1f, 0x1f, 0x3f, 0x3f, 0x7f, 
        0x7f, 0xef, 0xcf, 0x8f, 0x0f, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    // display logo
    oled_write_raw_P(logo_incaya, sizeof(logo_incaya));

    // write text on overlay of the logo
    oled_write_P(PSTR("LFYTE"), false);

    // write layer name
    oled_set_cursor(0, 1);
    switch (get_highest_layer(layer_state)) {
        case _BASE_:
            oled_write_ln_P(PSTR("base"), false);
            break;
        case _F_ARR_CALC_:
            oled_write_ln_P(PSTR("F->N"), false);
            break;
        case _NUM_:
            oled_write_ln_P(PSTR("nbrs"), false);
            break;
        case _MEDIA_:
            oled_write_ln_P(PSTR("media"), false);
            break;
            break;
        case _TILES_:
            oled_write_ln_P(PSTR("tiles"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
            break;
    }

    oled_set_cursor(0, 4);
    // Show the WPM
    // edit the string to change what shows up, edit %03d to change how many digits show up
    sprintf(wpm_str, "%02dWPM", get_current_wpm());
    oled_write(wpm_str, false);

    oled_set_cursor(0, 14);
    oled_write_ln_P(PSTR("inKya"), false);
}

// function for slave keyboard
void oled_render_logo(void) {
    // clang-format off
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    // clang-format on
    oled_write_P(crkbd_logo, false);
}

static void right_hand_func(void) {
    // Ocean Dream animations
    // see : https://github.com/snowe2010/qmk_firmware/blob/ocean-dream/users/snowe/readme_ocean_dream.md
    // render_stars();
    oled_render_logo();
}

// Global function for oled display
bool oled_task_user(){  
    if (is_keyboard_master()) {
        left_hand_func(); // master function
    } else {
        right_hand_func(); // slave function
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LCTL:
        case KC_RCTL:
        #ifdef OCEAN_DREAM_ENABLE
            is_calm = (record->event.pressed) ? true : false;
        #endif
            break;
    }
    return true;
}

#endif

// CUSTOM KEYMAP
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE_] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_ESC, KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                        KC_BSPC,  KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                        KC_DEL,  KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                           LT(4,KC_LGUI),   KC_LALT,  LT(1,KC_ENT),    KC_MPLY, LT(2,KC_SPC),  KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

    [_F_ARR_CALC_] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, 	 KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F11,  KC_F12,   KC_P7,   KC_P8,   KC_P9, KC_PMNS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_PGUP, KC_HOME,   KC_UP,  KC_END, MEH(KC_PGUP),                 KC_PSLS, KC_PAST,   KC_P4,   KC_P5,   KC_P6, KC_PPLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, MEH(KC_PGDN),                 KC_PDOT,   KC_P0,   KC_P1,   KC_P2,   KC_P3, KC_PENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, KC_LALT, KC_TRNS,  KC_MPLY, LT(3,KC_SPC),  KC_RALT
                                      //`--------------------------'  `--------------------------'   					 		
  ),

    [_NUM_] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_MINS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_EQL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                      KC_PSCR, LCTL(KC_QUOT), KC_LEFT,  KC_UP, KC_DOWN, KC_RGHT, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                   KC_LGUI, KC_LALT, LT(3,KC_ENT),      KC_BSPC, KC_TRNS,  KC_RALT
                                      //`--------------------------'  `--------------------------,			 		                                
  ),

    [_MEDIA_] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT,   KC_NO, KC_CALC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO, KC_NO,                           KC_VOLD,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_NO, KC_NO,                            KC_MUTE,   KC_NO,   KC_NO,   KC_NO, KC_BRID, KC_BRIU,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                    KC_LGUI, KC_LALT, KC_TRNS,          KC_NO, KC_TRNS,  KC_RALT
                                      //`--------------------------'  `--------------------------'  			 
  ),

    [_TILES_] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      LAG(KC_S), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                 KC_NO, LALT(KC_F4), KC_NO, KC_NO, LAG(KC_DOWN), LAG(KC_UP),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_CAPS, KC_SCLN, KC_NO, KC_NO, KC_NO, KC_NO,                                 KC_NO, KC_NO, LGUI(KC_ENT), LGUI(KC_UP), KC_NO, LAG(KC_RIGHT),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_NO, KC_NO,                    KC_NO, KC_NO, LGUI(KC_LEFT), LGUI(KC_DOWN), LGUI(KC_RGHT), LAG(KC_LEFT),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS,   KC_NO,   KC_NO,      LGUI(KC_L),   KC_SPC,   KC_LSFT
                                      //`--------------------------'  `--------------------------'                            
  )

//       [_QLAF_] = LAYOUT_split_3x6_3(
//   //,-----------------------------------------------------.                    ,-----------------------------------------------------.
//        KC_TAB, LALT(KC_Q), LALT(KC_W), LALT(KC_E), LALT(KC_R), LALT(KC_T),     KC_ESC,LALT(KC_Y), LALT(KC_U), LALT(KC_I), LALT(KC_O),LALT(KC_P),  
//   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//       KC_LSFT,LALT(KC_A),LALT(KC_S),LALT(KC_D),LALT(KC_F),LALT(KC_G),           KC_ENT,LALT(KC_H),LALT(KC_J),LALT(KC_K),LALT(KC_L),LALT(KC_SCLN), 
//   //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//       KC_LCTL, LALT(KC_Z), LALT(KC_X), LALT(KC_C), LALT(KC_V), LALT(KC_B),     KC_BSPC,LALT(KC_N), LALT(KC_M),LALT(KC_COMM),LALT(KC_DOT),LALT(KC_SLSH),  
//   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
//                            LT(4,KC_LGUI),   KC_LALT,  KC_SPC,           KC_NO, KC_TRNS,   KC_NO
//                                       //`--------------------------'  `--------------------------'
//   ),
};
