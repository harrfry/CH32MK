#include "events.h"
#include "keymap.h"
#include "systick.h"
#include "keycodes.h"
#include <stddef.h>

#ifndef MACRO_COUNT
#define MACRO_COUNT 0
#endif

typedef struct {
    const uint32_t *ptr;
    uint32_t next_tick_ms;
} macro_runner_t;

static macro_runner_t runner = {0};

void handle_macro(uint16_t index, key_event_t *oldest) {
    if(oldest->type == EVENT_RELEASE) {
        queue_pop_oldest();
        return;
    }
    if(index < MACRO_COUNT) {
        runner.ptr = macros[index];
        runner.next_tick_ms = sys_ticks_ms;
    }
    queue_pop_oldest();
    return;
}

void macro_task(uint32_t current_ms) {
    if(!runner.ptr) return;
    if((int32_t)(current_ms - runner.next_tick_ms) < 0) return;

    uint32_t item = *runner.ptr;
    uint8_t op = (uint8_t)(item >> 24);
    uint16_t arg = (uint16_t)(item & 0xFFFF);

    if(op == MACRO_END) {
        runner.ptr = NULL;
        return;
    }

    switch(op) {
        case MACRO_PRESS:
            queue_push(arg, 0, 0, EVENT_PRESS, current_ms);
            break;
        case MACRO_RELEASE:
            queue_push(arg, 0, 0, EVENT_RELEASE, current_ms);
            break;
        case MACRO_DELAY:
            runner.next_tick_ms = current_ms + arg;
            break;
    }

    runner.ptr++;
}