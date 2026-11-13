#include "keycodes.h"
#include "usb.h"
#include "events.h"
#include "systick.h"
#include "layers.h"
#include "config.h"

#ifndef TAPPING_TERM_MS
#define TAPPING_TERM_MS 200
#endif

void handle_layer_tap(key_event_t *oldest) {
    uint32_t current_time = sys_ticks_ms;
    uint8_t action_info = ((oldest->keycode >> 8) & 0x0F);
    uint8_t keycode = (uint8_t)(oldest->keycode);
    uint8_t timestamp = oldest->timestamp;

    if(oldest->type == EVENT_RELEASE) {
        uint32_t *layers = get_layer_mask();
        if(*layers & (1 << action_info)) {
            layer_off(action_info);
            queue_pop_oldest();
            return;
        } else {
            remove_from_keyboard_report(keycode);
            queue_pop_oldest();
            return;
        }
    }

    if(oldest->type == EVENT_PRESS) {
        if((current_time - timestamp) >= TAPPING_TERM_MS) {
            layer_on(action_info);
            queue_pop_oldest();
            return;
        }
    }

    if(queue_has_next()) {
        uint8_t count = (q.tail >= q.head) ? (q.tail - q.head) : (QUEUE_SIZE - q.head + q.tail);
        
        for(uint8_t i = 1; i < count; i++) {
            uint8_t lookahead_idx = (q.head + i) & QUEUE_MASK;
            key_event_t *future_event = &q.events[lookahead_idx];

            if((future_event->matrix_row == oldest->matrix_row) && (future_event->matrix_col == oldest->matrix_col)) {
                if(future_event->type == EVENT_RELEASE) {
                    add_to_keyboard_report(keycode);
                    queue_pop_oldest();
                    return;
                }
                continue;
            } 

            if((future_event->matrix_row != oldest->matrix_row) || (future_event->matrix_col != oldest->matrix_col)) {
                add_to_keyboard_report(keycode);
                queue_pop_oldest();
                return;
            }
        }
    }
    return;
}