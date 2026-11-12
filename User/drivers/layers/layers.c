#include <stdint.h>

uint32_t active_layers = 0;

void layer_on(uint8_t index) {
    active_layers |= (1U << index);
}

uint32_t* get_layer_mask(void) {
    return &active_layers;
}

void layer_off(uint8_t index) {
    active_layers &= ~(1U << index);
}

void layer_toggle(uint8_t index) {
    active_layers ^= (1U <<  index);
}

uint8_t get_highest_active_layer(uint32_t layer_mask) {
    if(layer_mask == 0)  return 0;
    return 31 - __builtin_clz(layer_mask);
}

