#pragma once

#include <stdint.h>
#include <stdbool.h>

#define HID_REPORT_KEY_LIMIT    6
#define QUEUE_SIZE              128
#define QUEUE_MASK              (QUEUE_SIZE - 1)

typedef enum {
    EVENT_PRESS = 0,
    EVENT_RELEASE
} event_type_t;

typedef struct {
    uint16_t keycode;
    uint8_t matrix_row;
    uint8_t matrix_col;
    event_type_t type;
    uint32_t timestamp;
} key_event_t;

typedef struct {
    key_event_t events[QUEUE_SIZE];
    volatile uint8_t head;
    volatile uint8_t tail;
} event_queue_t;

extern event_queue_t q;

bool queue_is_empty(void);

bool queue_is_full(void);

void queue_push(uint16_t keycode, uint8_t row, uint8_t col, event_type_t type, uint32_t timestamp);

key_event_t* queue_peek_oldest(void);

void queue_pop_oldest(void);

bool queue_has_next(void);

key_event_t* queue_peek_next(void);