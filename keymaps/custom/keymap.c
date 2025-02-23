#include QMK_KEYBOARD_H
#include "os_detection.h"


enum dasbob_layers {
  U_BASE,
  U_NUM,
  U_NAV
};


#define U_NP KC_NO // key is not present
#define U_NA KC_NO // present but not available for use
#define U_NU KC_NO // available but not used

#define U_RDO KC_AGIN
#define U_PST S(KC_INS)
#define U_CPY C(KC_INS)
#define U_CUT S(KC_DEL)
#define U_UND KC_UNDO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * Layer 0
      * ┌───────┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬──────────┐
      * │   Q   │ W │ E │ R │ T │       │ Y │ U │ I │ O │     P    │
      * ├───────┼───┼───┼───┼───┤       ├───┼───┼───┼───┼──────────┤
      * │   A   │ S │ D │ F │ G │       │ H │ J │ K │ L │    '"    │
      * ├───────┼───┼───┼───┼───┤       ├───┼───┼───┼───┼──────────┤
      * │SHFT/Z │ X │ C │ V │ B │       │ N │ M │ , │ . │ SHFT/ /? │
      * └───────┴───┴───┴───┴───┘       └───┴───┴───┴───┴──────────┘
      *  ┌────────┐                               ┌────────┐
      *  │OPT/ESC ├───────┐               ┌───────┤ L2/BKSP│
      *  └────────┤  CMD  ├───────┐   ┌───┤ L1/SPC├────────┘
      *           └───────│CTR/TAB│   │ENT├───────┘
      *                   └───────┘   └───┘
      */

    [U_BASE] = LAYOUT_split_3x5_3(
        KC_Q,         KC_W,      KC_E,           KC_R,         KC_T,            /**/  KC_Y,       KC_U,              KC_I,      KC_O,   KC_P,              \
        KC_A,         KC_S,      KC_D,           KC_F,         KC_G,            /**/  KC_H,       KC_J,              KC_K,      KC_L,   KC_QUOT,           \
        LSFT_T(KC_Z), KC_X,      KC_C,           KC_V,         KC_B,            /**/  KC_N,       KC_M,              KC_COMM,   KC_DOT, LSFT_T(KC_SLSH),   \
                                 LCTL_T(KC_ESC), KC_LCMD,  LALT_T(KC_TAB),  /**/  KC_ENT,     LT(U_NUM,KC_SPC),  LT(U_NAV,KC_BSPC)                               
     ),

    /* Layer 1: Symbols
     * ,-----.-----.-----.-----.-----.                      ,-----.-----.-----.-----.-----.
     * | 1!  | 2@  | 3#  | 4$  | 5%  |                      | 6^  | 7&  | 8*  | 9(  | 0)  |
     * |-----+-----+-----+-----+-----|                      |-----+-----+-----+-----+-----|
     * | `~  |     |     |     |     |                      |     |     |     |     | ;:  |
     * |-----+-----+-----+-----+-----+                      |-----+-----+-----+-----+-----|
     * |SHFT |ALGR |     |     |     |                      | -_  | =+  | [{  | ]}  |SHF\||
     * `-----'-----'-----'-----'-----'                      `-----'-----'-----'-----'-----'
     *               .-------.-------.-------.      .-------.-------.-------.   
     *               |       |       |       |      |       |(hold) |       |
     *               '-------'-------'-------'      '-------'-------'-------' 
    */

    [U_NUM] = LAYOUT_split_3x5_3(
        KC_1,      KC_2,     KC_3,    KC_4,    KC_5, /**/  KC_6,     KC_7,    KC_8,     KC_9,     KC_0,                   \
        KC_GRV,    U_NA,     U_NA,    U_NA,    U_NA, /**/  U_NA,     U_NA,    U_NA,     U_NA,     KC_SCLN,                \
        KC_LSFT,   KC_ALGR,  U_NA,    U_NA,    U_NA, /**/  KC_MINS,  KC_EQL,  KC_LBRC,  KC_RBRC,  LSFT_T(KC_BACKSLASH),   \
                             KC_ESC,    KC_LCMD,    KC_TAB, /**/  U_NA,     U_NA,    U_NA
    ),

    /* Layer 2: Nav/Fun
     * ,-----.-----.------.-----.-----.                      ,-----.-----.-----.-----.-----.
     * | F1  |  F2 | F3  | F4  | F5  |                       |     |     | UP  |     | HOME|
     * |-----+-----+------+-----+-----|                      |-----+-----+-----+-----+-----|
     * | F6  | F7  | F8   | F9  | F10 |                      |     | LEFT| DOWN|RIGHT| END |
     * |-----+-----+------+-----+-----+                      |-----+-----+-----+-----+-----|
     * | F11 | F12 | Vol+ | Vol-|     |                      |     |     |     |     |     |
     * `-----'-----'------'-----'-----'                      `-----'-----'-----'-----'-----'
     *               .-------.-------.-------.      .-------.-------.--------.   
     *               |       |       |       |      |       |       | (hold) |
     *               '-------'-------'-------'      '-------'-------'--------' 
    */

    [U_NAV] = LAYOUT_split_3x5_3(
        KC_F1,   KC_F2,  KC_F3,  KC_F4,   KC_F5,    /**/  U_RDO,             U_PST,             KC_UP,             U_CUT,             U_UND,             \
        KC_F6,   KC_F7,  KC_F8,  KC_F9,   KC_F10,   /**/  U_NA,              KC_LEFT,           KC_DOWN,           KC_RGHT,           U_CPY,             \
        KC_F11,  KC_F12, KC_F1,  KC_VOLU, KC_VOLD,  /**/  KC_INS,            KC_HOME,           KC_PGUP,           KC_PGDN,           KC_END,            \
                         KC_ESC, KC_LCMD,KC_TAB,/**/  KC_ENT,            KC_SPC,            KC_BSPC
    )
};

static os_variant_t current_os = OS_UNSURE;


bool process_detected_host_os_user(os_variant_t detected_os) {
    current_os = detected_os;
    return true;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    
  switch (keycode) {
    // Remap Alt-Q to Alt-Tab
  case KC_Q:
    if (record->event.pressed) {
      if (keyboard_report->mods & MOD_BIT(KC_LALT)){
        register_code(KC_TAB);
        return false;
      }
    } else {
      if (keyboard_report->mods & MOD_BIT(KC_LALT)){
        unregister_code(KC_TAB);
        return false;
      }
    }
    break;

    // Switch Cmd and Ctrl on Windows/Linux (So Win/Linux: Cmd | )
    case KC_LALT:
        if (current_os == OS_MACOS || current_os == OS_IOS) {
            tap_code16(KC_LGUI);
            return false;
        }
        break;
    case KC_LGUI:
        if (current_os == OS_WINDOWS || current_os == OS_LINUX) {
            tap_code16(KC_LALT);
            return false;
        }
        break;
  }
  return true;
};