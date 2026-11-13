#include "process_keymap.h"
#include "keymap.h"
#include "events.h"
#include "systick.h"

uint16_t active_keys[MATRIX_ROWS][MATRIX_COLS] = {0};

void process_matrix_changed(volatile bool matrix_debounced[MATRIX_ROWS][MATRIX_COLS], bool matrix_debounced_prev[MATRIX_ROWS][MATRIX_COLS]) {
    uint32_t current_time = sys_ticks_ms;

    for(uint8_t r = 0; r < MATRIX_ROWS; r++)    {

        for(uint8_t c = 0; c < MATRIX_COLS; c++) {

            bool current = matrix_debounced[r][c];
            bool previous = matrix_debounced_prev[r][c];

            if(current == previous) continue;

            if(current && !previous) { // this is a press
                uint16_t keycode = get_effective_keycode(r, c);
                if(keycode == 0) continue;
                active_keys[r][c] = keycode;
                queue_push(keycode, r, c, EVENT_PRESS, current_time);
            }

            if(!current && previous) { // this is a release event

                uint16_t keycode = active_keys[r][c];
                if(keycode == 0) continue;

                queue_push(keycode, r, c, EVENT_RELEASE, current_time);

                active_keys[r][c] = 0;

            }

            matrix_debounced_prev[r][c] = current;
        }

    }
}