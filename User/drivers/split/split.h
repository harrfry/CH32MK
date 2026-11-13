#pragma once

#include <stdint.h>
#include "config.h"
#include <stdbool.h>

#define SPLIT_BUFFER_SIZE 16

typedef struct {
    uint8_t state;
    uint8_t row;
    uint8_t col;
    uint8_t checksum;
} key_packet_t __attribute__((aligned(4)));

void split_transport_init(void);
void split_housekeeping_task(volatile bool matrix_debounced[MATRIX_ROWS][MATRIX_COLS], bool is_master);
void usart_tx_send(uint8_t row, uint8_t col, uint8_t state);