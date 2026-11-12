#pragma once

uint32_t active_layers = 0;

void layer_on(uint8_t index);

uint32_t* get_layer_mask(void);

void layer_off(uint8_t index);

void layer_toggle(uint8_t index);

uint8_t get_highest_active_layer(uint32_t layer_mask);
