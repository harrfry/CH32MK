#pragma once

#include <stdint.h>
#include "config.h"
#include <stdbool.h>

#define SPLIT_BUFFER_SIZE 32

typedef struct {
    uint8_t state;
    uint8_t row;
    uint8_t col;
    uint8_t checksum;
} key_packet_t;

#ifndef ROW_OFFSET
#define ROW_OFFSET 0
#endif
#ifndef COL_OFFSET
#define COL_OFFSET 0
#endif


void split_transport_init(void);
void split_housekeeping_task(volatile bool matrix_debounced[MATRIX_ROWS][MATRIX_COLS], bool is_master);
void usart_tx_send(uint8_t row, uint8_t col, uint8_t state);
void slave_process_matrix(volatile bool matrix_debounced[MATRIX_ROWS][MATRIX_COLS], bool matrix_previous[MATRIX_ROWS][MATRIX_COLS]);