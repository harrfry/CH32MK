#pragma once

#include <stdint.h>

typedef enum {
    ACT_NORMAL = 0,
    ACT_MODIFIER,
    ACT_MOD_TAP,
    ACT_LAYER_TAP,
    ACT_LAYER_MO,
    ACT_LAYER_TG,
    ACT_MOUSE_BUTTON,
    ACT_MOUSE_MOVEMENT,
    ACT_TRANSPARENT,
    ACT_MOD_AND_KEYCODE,
    ACT_MACRO,
} action_type;  // this occupies the top 4 bits [15:12]

typedef enum {
    MOD_LGUI = 0,
    MOD_LALT,
    MOD_LCTL,
    MOD_LSFT,
    MOD_RGUI,
    MOD_RALT,
    MOD_RCTL,
    MOD_RSFT
} mod_tap_type_t; // this occupies the middle 4 bits [11:8];


#define MOD_MASK_LCTL       0x01
#define MOD_MASK_LSFT       0x02
#define MOD_MASK_LALT       0x04
#define MOD_MASK_LGUI       0x08
#define MOD_MASK_RCTL       0x10
#define MOD_MASK_RSFT       0X20
#define MOD_MASK_RALT       0x40
#define MOD_MASK_RGUI       0x80

static inline uint8_t get_mod_mask(uint8_t mod) {
    switch(mod) {
        case MOD_LGUI:
            return MOD_MASK_LGUI;
        case MOD_LALT:
            return MOD_MASK_LALT;
        case MOD_LCTL:
            return MOD_MASK_LCTL;
        case MOD_LSFT:
            return MOD_MASK_LSFT;
        case MOD_RGUI:
            return MOD_MASK_RGUI;
        case MOD_RALT:
            return MOD_MASK_RALT;
        case MOD_RCTL:
            return MOD_MASK_RCTL;
        case MOD_RSFT:
            return MOD_MASK_RSFT;

        default: 
            return 0;
    }
}

typedef enum {
    LEFT = 1,
    RIGHT,
    UP,
    DOWN,
    SCROLL_LEFT,
    SCROLL_RIGHT,
    SCROLL_UP,
    SCROLL_DOWN
} mouse_movement_action_t;

// standard hid keycode occupies the least significant bits [0:7]

#define MT(mod, keycode)        (uint16_t)(ACT_MOD_TAP << 12 | mod << 8 | keycode)
#define LT(layer, keycode)      (uint16_t)(ACT_LAYER_TAP << 12 | layer << 8 | keycode)
#define MOD(mod_mask)           (uint16_t)(ACT_MODIFIER << 12 | mod_mask)
#define MSBTN(mask)             (uint16_t)(ACT_MOUSE_BUTTON << 12 | mask)
#define MSMV(action)         (uint16_t)(ACT_MOUSE_MOVEMENT << 12 | action)
#define MO(layer)               (uint16_t)(ACT_LAYER_MO << 12 | layer << 8)
#define TG(layer)               (uint16_t)(ACT_LAYER_TG << 12 | layer << 8)
#define LSFT(keycode)           (uint16_t)(ACT_MOD_AND_KEYCODE << 12 | MOD_LSFT << 8 | keycode)
#define LCTL(keycode)           (uint16_t)(ACT_MOD_AND_KEYCODE << 12 | MOD_LCTL << 8 | keycode)
#define LALT(keycode)           (uint16_t)(ACT_MOD_AND_KEYCODE << 12 | MOD_LALT << 8 | keycode)
#define LGUI(keycode)           (uint16_t)(ACT_MOD_AND_KEYCODE << 12 | MOD_LGUI << 8 | keycode)
#define RSFT(keycode)           (uint16_t)(ACT_MOD_AND_KEYCODE << 12 | MOD_RSFT << 8 | keycode)
#define RCTL(keycode)           (uint16_t)(ACT_MOD_AND_KEYCODE << 12 | MOD_RCTL << 8 | keycode)
#define RALT(keycode)           (uint16_t)(ACT_MOD_AND_KEYCODE << 12 | MOD_RALT << 8 | keycode)
#define RGUI(keycode)           (uint16_t)(ACT_MOD_AND_KEYCODE << 12 | MOD_RGUI << 8 | keycode)
#define MACRO(index)            (uint16_t)(ACT_MACRO << 12 | index)
#define MACRO_END               0x00      


#define KC_NONE             0x00
#define KC_TRNS             (uint16_t)(ACT_TRANSPARENT << 12)

#define KC_A                0x04
#define KC_B                0x05
#define KC_C                0x06
#define KC_D                0x07
#define KC_E                0x08
#define KC_F                0x09
#define KC_G                0x0A
#define KC_H                0x0B
#define KC_I                0x0C
#define KC_J                0x0D
#define KC_K                0x0E
#define KC_L                0x0F
#define KC_M                0x10
#define KC_N                0x11
#define KC_O                0x12
#define KC_P                0x13
#define KC_Q                0x14
#define KC_R                0x15
#define KC_S                0x16
#define KC_T                0x17
#define KC_U                0x18
#define KC_V                0x19
#define KC_W                0x1A
#define KC_X                0x1B
#define KC_Y                0x1C
#define KC_Z                0x1D

// Numbers & Symbols
#define KC_1                0x1E
#define KC_2                0x1F
#define KC_3                0x20
#define KC_4                0x21
#define KC_5                0x22
#define KC_6                0x23
#define KC_7                0x24
#define KC_8                0x25
#define KC_9                0x26
#define KC_0                0x27

// Control & Punctuation
#define KC_ENTER            0x28
#define KC_ESCAPE           0x29
#define KC_BACKSPACE        0x2A
#define KC_TAB              0x2B
#define KC_SPACE            0x2C
#define KC_MINUS            0x2D
#define KC_EQUAL            0x2E
#define KC_LEFT_BRACKET     0x2F
#define KC_RIGHT_BRACKET    0x30
#define KC_BACKSLASH        0x31
#define KC_NONUS_HASH       0x32
#define KC_SEMICOLON        0x33
#define KC_QUOTE            0x34
#define KC_GRAVE            0x35
#define KC_COMMA            0x36
#define KC_DOT              0x37
#define KC_SLASH            0x38
#define KC_CAPS_LOCK        0x39

// Function Keys
#define KC_F1               0x3A
#define KC_F2               0x3B
#define KC_F3               0x3C
#define KC_F4               0x3D
#define KC_F5               0x3E
#define KC_F6               0x3F
#define KC_F7               0x40
#define KC_F8               0x41
#define KC_F9               0x42
#define KC_F10              0x43
#define KC_F11              0x44
#define KC_F12              0x45

// Navigation & Editing
#define KC_PRINT_SCREEN     0x46
#define KC_SCROLL_LOCK      0x47
#define KC_PAUSE            0x48
#define KC_INSERT           0x49
#define KC_HOME             0x4A
#define KC_PAGE_UP          0x4B
#define KC_DELETE           0x4C
#define KC_END              0x4D
#define KC_PAGE_DOWN        0x4E
#define KC_RIGHT            0x4F
#define KC_LEFT             0x50
#define KC_DOWN             0x51
#define KC_UP               0x52

// Numpad
#define KC_NUM_LOCK         0x53
#define KC_KP_SLASH         0x54
#define KC_KP_ASTERISK      0x55
#define KC_KP_MINUS         0x56
#define KC_KP_PLUS          0x57
#define KC_KP_ENTER         0x58
#define KC_KP_1             0x59
#define KC_KP_2             0x5A
#define KC_KP_3             0x5B
#define KC_KP_4             0x5C
#define KC_KP_5             0x5D
#define KC_KP_6             0x5E
#define KC_KP_7             0x5F
#define KC_KP_8             0x60
#define KC_KP_9             0x61
#define KC_KP_0             0x62
#define KC_KP_DOT           0x63

// Miscellaneous / Extended Function Keys
#define KC_NONUS_BACKSLASH  0x64
#define KC_APPLICATION      0x65
#define KC_KB_POWER         0x66
#define KC_KP_EQUAL         0x67
#define KC_F13              0x68
#define KC_F14              0x69
#define KC_F15              0x6A
#define KC_F16              0x6B
#define KC_F17              0x6C
#define KC_F18              0x6D
#define KC_F19              0x6E
#define KC_F20              0x6F
#define KC_F21              0x70
#define KC_F22              0x71
#define KC_F23              0x72
#define KC_F24              0x73

#define KC_LCTL             MOD(MOD_MASK_LCTL)
#define KC_LSFT             MOD(MOD_MASK_LSFT)
#define KC_LALT             MOD(MOD_MASK_LALT)
#define KC_LGUI             MOD(MOD_MASK_LGUI)
#define KC_RCTL             MOD(MOD_MASK_RCTL)
#define KC_RSFT             MOD(MOD_MASK_RSFT)
#define KC_RALT             MOD(MOD_MASK_RALT)
#define KC_RGUI             MOD(MOD_MASK_RGUI)

#define HID_MOUSE_BUTTON_1      1U
#define HID_MOUSE_BUTTON_2      (1U << 1)
#define HID_MOUSE_BUTTON_3      (1U << 2)
#define HID_MOUSE_BUTTON_4      (1U << 3)
#define HID_MOUSE_BUTTON_5      (1U << 4)

#define MS_BTN1             MSBTN(HID_MOUSE_BUTTON_1)
#define MS_BTN2             MSBTN(HID_MOUSE_BUTTON_2)
#define MS_BTN3             MSBTN(HID_MOUSE_BUTTON_3)
#define MS_BTN4             MSBTN(HID_MOUSE_BUTTON_4)
#define MS_BTN5             MSBTN(HID_MOUSE_BUTTON_5)

#define MS_LEFT             MSMV(LEFT)
#define MS_RIGHT            MSMV(RIGHT)
#define MS_UP               MSMV(UP)
#define MS_DOWN             MSMV(DOWN)
#define MS_SCUP             MSMV(SCROLL_UP)
#define MS_SCDN             MSMV(SCROLL_DOWN)
#define MS_SCRL             MSMV(SCROLL_LEFT)
#define MS_SCRR             MSMV(SCROLL_RIGHT)
