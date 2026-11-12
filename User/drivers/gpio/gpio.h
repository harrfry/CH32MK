#pragma once

#include "config.h"
#include "pins.h"

void init_matrix_pins(const pin_t *row_pins, const pin_t *col_pins);
void init_direct_pins(const pin_t direct_pins[MATRIX_ROWS][MATRIX_COLS]);
void init_caps_led();
void caps_led_off();
void caps_led_on();