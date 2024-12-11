#include QMK_KEYBOARD_H


enum layer_names {
    _QWERTY,
    _NUMPAD,
    _NUMBER,
    _MEDIA_,
    _TILES_
};

// enum custom_keycodes {
//   QWERTY = SAFE_RANGE,
//   LOWER,
//   RAISE,
//   ADJUST,
// };

#define EISU LALT(KC_GRV)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |  Tab |   Q  |   W  |   E  |   R  |   T  |   [  |                    |  Esc |   Y  |   U  |   I  |   O  |   P  |  -   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Shift|   A  |   S  |   D  |   F  |   G  |   ]  |                    | Bksp |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Ctrl |   Z  |   X  |   C  |   V  |   B  |      |Delete|      | Play |      |   N  |   M  |   ,  |   .  |   /  |  \   |
   * |-------------+------+------+------+------+Enter/+------+------+------+Space/+------+------+------+------+-------------|
   * |      |  `   |CPSLCK|||||||| GUI  | LAlt | LT 1 |Delete||||||||      | LT 2 | Ralt |||||||| Left |  Up  | Down | Right|
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_QWERTY] = LAYOUT(
    KC_TAB,   KC_Q,     KC_W,     KC_E,   KC_R,           KC_T,     KC_LBRC,                              KC_ESC,       KC_Y,     KC_U,     KC_I,     KC_O,   KC_P,     KC_MINS,
    KC_LSFT,  KC_A,     KC_S,     KC_D,   KC_F,           KC_G,     KC_RBRC,                              KC_BSPC,      KC_H,     KC_J,     KC_K,     KC_L,   KC_SCLN,  KC_QUOT,
    KC_LCTL,  KC_Z,     KC_X,     KC_C,   KC_V,           KC_B,                   KC_DEL,       KC_MPLY,                KC_N,     KC_M,     KC_COMM,  KC_DOT, KC_SLSH,  KC_NUBS,
    KC_NO,    KC_GRV,   KC_CAPS,          LT(4,KC_LGUI),  KC_LALT,  LT(1,KC_ENT), KC_BSLS,      KC_NO,    LT(2,KC_SPC), KC_RALT,            KC_LEFT,  KC_UP,  KC_DOWN,  KC_RGHT
  ),

  /* NUMPAD
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |  Tab |  F1  |  F2  |  F3  |  F4  |  F5  |PageUp|                    | Esc  |  F11 |  F12 |   7  |   8  |   9  |  /   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Shift|   1  |   2  |   3  |   4  |   5  |PageDw|                    | Bksp | Home |      |  4   |  5   |  6   |  *   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Ctrl |   6  |   7  |   8  |   9  |   0  |      |      |      |      |      | End  |      |  1   |  2   |  3   |  -   |
   * |-------------+------+------+------+------+ LT 1 +------+------+------+Space/+------+------+------+------+-------------|
   * |      |      |      ||||||||      |      |      |      ||||||||      | LT 3 |      ||||||||  0   |  .   | Enter|  +   |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_NUMPAD] = LAYOUT(
    KC_TAB,   KC_F1,    KC_F2,    KC_F3,  KC_F4,      KC_F5,        KC_PGUP,                              KC_ESC,       KC_F11,   KC_F12,   KC_P7,    KC_P8,  KC_P9,    KC_PSLS,
    KC_LSFT,  KC_NO,    KC_NO,    KC_NO,  KC_NO,      MEH(KC_PGUP), KC_PGDN,                              KC_BSPC,      KC_HOME,  KC_NO,    KC_P4,    KC_P5,  KC_P6,    KC_PAST,
    KC_LCTL,  KC_NO,    KC_NO,    KC_NO,  KC_NO,      MEH(KC_PGDN),               KC_NO,        KC_NO,                  KC_END,   KC_NO,    KC_P1,    KC_P2,  KC_P3,    KC_PMNS,
    KC_NO,    KC_NO,    KC_NO,            KC_NO,      KC_NO,        KC_TRNS,      KC_NO,        KC_NO,    LT(3,KC_SPC), KC_NO,              KC_P0,    KC_PDOT,KC_PENT,  KC_PPLS
    ),

  /* Number
  */
  [_NUMBER] = LAYOUT(
    KC_EXLM, KC_AT,     KC_HASH,  KC_DLR, KC_PERC,    KC_CIRC,      KC_NO,                                KC_NO,        KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,KC_UNDS,  KC_PLUS,
    KC_1,    KC_2,      KC_3,     KC_4,   KC_5,       KC_6,         KC_NO,                                KC_NO,        KC_7,     KC_8,     KC_9,     KC_0,   KC_MINS,  KC_EQL,
    KC_NO,   KC_NO,     KC_NO,    KC_NO,  KC_NO,      KC_NO,                      KC_NO,        KC_NO,                  KC_NO,    KC_NO,    KC_NO,    KC_NO,  KC_NO,    KC_NO,
    KC_NO,   KC_NO,     KC_NO,            KC_NO,      KC_NO,        LT(3,KC_ENT), KC_NO,        KC_NO,    KC_TRNS,      KC_NO,              KC_NO,    KC_NO,  KC_NO,    KC_NO
  ),

  /* Media
  */
  [_MEDIA_] = LAYOUT(
    KC_NO,   KC_NO,     KC_NO,    KC_NO,  KC_NO,      KC_NO,        KC_VOLU,                              KC_MUTE,      KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_NO,  KC_NO,    KC_NO,
    KC_NO,   KC_NO,     KC_NO,    KC_NO,  KC_NO,      KC_NO,        KC_VOLD,                              KC_NO,        KC_NO,    KC_NO,    KC_NO,    KC_NO,  KC_NO,    KC_NO,
    KC_NO,   KC_NO,     KC_NO,    KC_NO,  KC_NO,      KC_NO,                      KC_NO,        KC_NO,                  KC_NO,    KC_NO,    KC_NO,    KC_NO,  KC_NO,    KC_NO,
    KC_NO,   KC_NO,     KC_NO,            KC_NO,      KC_NO,        KC_TRNS,      KC_NO,        KC_NO,    KC_TRNS,      KC_NO,              KC_NO,    KC_NO,  KC_NO,    KC_NO
  ),

  /* Tiles
  */
  [_TILES_] = LAYOUT(
    KC_NO,KC_NO,KC_NO,     KC_NO,KC_NO,  KC_NO,KC_NO,                                  LALT(KC_F4),KC_NO,KC_NO,KC_NO,             KC_NO,              KC_NO,        KC_NO,
    KC_NO,KC_NO,KC_NO,     KC_NO,KC_NO,  KC_NO,KC_NO,                                  KC_NO,      KC_NO,KC_NO,KC_NO,             KC_NO,              KC_NO,        KC_NO,
    KC_NO,KC_NO,KC_NO,     KC_NO,KC_NO,  KC_NO,             KC_NO,        KC_NO,                   KC_NO,KC_NO,LSA(LGUI(KC_LEFT)),LSA(LGUI(KC_RIGHT)),KC_NO,        KC_NO,
    KC_NO,KC_NO,LGUI(KC_L),      KC_TRNS,KC_NO,LGUI(KC_ENT),LAG(KC_LEFT), LAG(KC_RGHT),KC_NO,      KC_NO,      LGUI(KC_LEFT),     LGUI(KC_UP),        LGUI(KC_DOWN),LGUI(KC_RGHT)
    )
};

// Active layers on key press
// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   switch (keycode) {
//     case LOWER:
//       if (record->event.pressed) {
//         layer_on(_LOWER);
//         update_tri_layer(_LOWER, _RAISE, _ADJUST);
//       } else {
//         layer_off(_LOWER);
//         update_tri_layer(_LOWER, _RAISE, _ADJUST);
//       }
//       return false;
//       break;
//     case RAISE:
//       if (record->event.pressed) {
//         layer_on(_RAISE);
//         update_tri_layer(_LOWER, _RAISE, _ADJUST);
//       } else {
//         layer_off(_RAISE);
//         update_tri_layer(_LOWER, _RAISE, _ADJUST);
//       }
//       return false;
//       break;
//     case ADJUST:
//       if (record->event.pressed) {
//         layer_on(_ADJUST);
//       } else {
//         layer_off(_ADJUST);
//       }
//       return false;
//       break;
//   }
//   return true;
// }
