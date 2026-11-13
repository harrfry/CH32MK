#include "events.h"
#include "systick.h"
#include "usb.h"
#include "keycodes.h"
#include "config.h"
#include <stdio.h>

#ifndef TAPPING_TERM_MS
#define TAPPING_TERM_MS 200
#endif


void handle_mod_tap(key_event_t *oldest) {
    uint32_t current_time = sys_ticks_ms;
    uint8_t action_info = ((oldest->keycode >> 8) & 0x0F);
    uint8_t keycode = (uint8_t)(oldest->keycode);
    uint32_t timestamp = oldest->timestamp;

    uint8_t mod_mask = get_mod_mask(action_info);
    uint8_t *modifier_ptr = get_modifier_ptr();

    if(oldest->type == EVENT_RELEASE) {
        if(*modifier_ptr & mod_mask) {
            remove_modifier_from_report(mod_mask);
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
            add_modifier_to_report(mod_mask);
            queue_pop_oldest();
            return;
        }

        if(queue_has_next()) {
            uint8_t count = (q.tail >= q.head) ? (q.tail - q.head) : (QUEUE_SIZE - q.head + q.tail);
            for(uint8_t i = 1; i < count; i++) {
                uint8_t lookahead_idx = (q.head + i) & QUEUE_MASK;
                key_event_t *future_event = &q.events[lookahead_idx];
                uint8_t future_keycode_action = (future_event->keycode >> 12);

                // this is a single isolated fast tap
                if((future_event->matrix_row == oldest->matrix_row) && (future_event->matrix_col == oldest->matrix_col)) {
                    if(future_event->type == EVENT_RELEASE) {
                        add_to_keyboard_report(keycode);
                        queue_pop_oldest();
                        return;
                    }
                    continue;
                }

                // then if the next key is not a mod tap then it's a release
                if(((future_event->matrix_row != oldest->matrix_row) || (future_event->matrix_col != oldest->matrix_col)) && (future_keycode_action != ACT_MOD_TAP)) {
                    add_to_keyboard_report(keycode);
                    queue_pop_oldest();
                    return;
                }
                
            }
        }

    }
    return;
}