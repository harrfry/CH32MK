#include "process_keymap.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "events.h"

event_queue_t q = {.head = 0, .tail = 0};

bool queue_is_empty(void) {
    return q.head == q.tail;
}

bool queue_is_full(void) {
    return ((q.tail + 1) & QUEUE_MASK) == q.head;
}

void queue_push(uint16_t keycode, uint8_t row, uint8_t col, event_type_t type, uint32_t timestamp) {
    if(queue_is_full()) {
        return;
    }

    q.events[q.tail].keycode = keycode;
    q.events[q.tail].matrix_row = row;
    q.events[q.tail].matrix_col = col;
    q.events[q.tail].type = type;
    q.events[q.tail].timestamp = timestamp;

    q.tail = (q.tail + 1) & QUEUE_MASK;
}

key_event_t* queue_peek_oldest(void) {
    if(queue_is_empty()) {
        return NULL;
    }
    return &q.events[q.head];
}

void queue_pop_oldest(void) {
    if(!queue_is_empty()) {
        q.head = (q.head + 1) & QUEUE_MASK;
    }
}

bool queue_has_next(void) {
    if(queue_is_empty()) return false;

    uint8_t next_idx = (q.head + 1) & QUEUE_MASK;

    return next_idx != q.tail;
}

key_event_t* queue_peek_next(void) {
    // FIX: Changed from !queue_is_empty() to allow scanning when data exists
    if(queue_is_empty()) {
        return NULL;
    }
    uint8_t next_idx = (q.head + 1) & QUEUE_MASK;
    return &q.events[next_idx];
}

