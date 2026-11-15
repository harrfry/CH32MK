#include "config.h"
#include "keycodes.h"

#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39 \
) \
{ \
    {k00, k01, k02, k03, k04}, \
    {k10, k11, k12, k13, k14}, \
    {k20, k21, k22, k23, k24}, \
    {k30, k31, k32, k33, k34}, \
    {k05, k06, k07, k08, k09}, \
    {k15, k16, k17, k18, k19}, \
    {k25, k26, k27, k28, k29}, \
    {k35, k36, k37, k38, k39} \
} \

#define HRM_A MT(MOD_LGUI, KC_A)
#define HRM_R MT(MOD_LALT, KC_R)
#define HRM_S MT(MOD_LCTL, KC_S)
#define HRM_T MT(MOD_LSFT, KC_T)

#define HRM_N MT(MOD_RSFT, KC_N)
#define HRM_E MT(MOD_RCTL, KC_E)
#define HRM_I MT(MOD_LALT,   KC_I)
#define HRM_O MT(MOD_LGUI,   KC_O)

const uint16_t keymap[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    HRM_E,    KC_U,    KC_Y,    KC_SEMICOLON,
        MS_LEFT,   MS_SCUP, MS_SCDN,   MS_RIGHT,   KC_G,    KC_M,    HRM_N,   HRM_E,   HRM_I,   HRM_O,
        KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMMA, KC_DOT,  KC_SLASH,
        KC_TAB,  KC_ESCAPE,  KC_GRAVE,  MO(1),   MS_BTN1, KC_ENTER,  MO(2),   KC_SPACE,  KC_QUOTE, KC_MINUS
    ),
    [1] = LAYOUT(
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SEMICOLON,
        HRM_A,   HRM_R,   HRM_S,   HRM_T,   KC_G,    KC_M,    KC_A,     KC_B, KC_C, KC_D,
        KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMMA, KC_DOT,  KC_SLASH,
        KC_TAB,  KC_ESCAPE,  KC_GRAVE,  MO(1),   KC_BACKSPACE, KC_ENTER,  MO(2),   KC_SPACE,  KC_QUOTE, KC_MINUS
    ),
    [2] = LAYOUT(
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SEMICOLON,
        HRM_A,   HRM_R,   HRM_S,   HRM_T,   KC_G,    KC_M,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMMA, KC_DOT,  KC_SLASH,
        KC_TAB,  KC_ESCAPE,  KC_GRAVE,  MO(1),   KC_BACKSPACE, KC_ENTER,  MO(2),   KC_SPACE,  KC_QUOTE, KC_MINUS
    ),
};