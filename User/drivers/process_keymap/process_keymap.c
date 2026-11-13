#include "keymap.h"
#include "keycodes.h"
#include "layers.h"

uint16_t get_effective_keycode(uint8_t row, uint8_t col) {
    uint32_t *layers = get_layer_mask();
    uint32_t layers_snapshot = *layers;
    while (layers_snapshot > 0) {
        uint16_t keycode = keymap[get_highest_active_layer(layers_snapshot)][row][col];
        if(keycode != KC_TRNS) {
            return keycode;
        }
        layers_snapshot &= ~(1U << get_highest_active_layer(layers_snapshot));
    }
    return keymap[0][row][col];
}