#pragma once

#include <stdbool.h>
#include "pins.h"

void matrix_scan_raw(const pin_t *row_pins, const pin_t *col_pins, bool matrix_raw[MATRIX_ROWS][MATRIX_COLS]);
void print_matrix_state(volatile bool matrix[MATRIX_ROWS][MATRIX_COLS]);