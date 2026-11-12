#include "config.h"
#include <stdint.h>
#include <stdbool.h> 
#include "systick.h"

static uint32_t debounce_timers[MATRIX_ROWS][MATRIX_COLS];

#ifndef DEBOUNCE
#define DEBOUNCE 5
#endif

#if !defined(DEBOUNCE_EAGER_PK) && !defined(DEBOUNCE_DEFER_PK)
#define DEBOUNCE_DEFER_PK
#endif

#ifdef DEBOUNCE_DEFER_PK
bool debounce(bool matrix_raw[MATRIX_ROWS][MATRIX_COLS], volatile bool matrix_cleaned[MATRIX_ROWS][MATRIX_COLS]) {
    uint32_t current_time = sys_ticks_ms;
    bool matrix_did_change = false;
    for (uint8_t r = 0; r < MATRIX_ROWS_PER_HALF; r++) {

        for(uint8_t c = 0; c < MATRIX_COLS_PER_HALF; c++) {

            uint32_t last_debounce_time = debounce_timers[r][c];

            if(matrix_raw[r][c] != matrix_cleaned[r][c]) {
                // if the debounce timer is 0, then we set the lockout to the debounce window
                if(debounce_timers[r][c] == 0) {
                    debounce_timers[r][c] = current_time;
                }

                // otherwise if enough time has passed, then we update the keypress
                else if ((current_time - last_debounce_time) >= DEBOUNCE) {
                    matrix_cleaned[r][c] = matrix_raw[r][c];
                    debounce_timers[r][c] = 0; // reset the lockout window
                    matrix_did_change = true;
                }
            } else {
                debounce_timers[r][c] = 0;
            }
        }
    }
    return matrix_did_change;
}
#endif

#ifdef DEBOUNCE_EAGER_PK
bool debounce(bool matrix_raw[MATRIX_ROWS][MATRIX_COLS], volatile bool matrix_cleaned[MATRIX_ROWS][MATRIX_COLS]) {
    uint32_t current_time = sys_ticks_ms;
    bool matrix_did_change = false;

    for(uint8_t r = 0; r < MATRIX_ROWS_PER_HALF; r++) {

        for(uint8_t c = 0; c < MATRIX_COLS_PER_HALF; c++) {
            // if the key state changed and we are not in the lockout window then update immediately
            if((matrix_raw[r][c] != matrix_cleaned[r][c]) && ((current_time - debounce_timers[r][c]) >= DEBOUNCE)) {
                matrix_cleaned[r][c] = matrix_raw[r][c];
                debounce_timers[r][c] = current_time;

                matrix_did_change = true;
            }
        }

    }
    return matrix_did_change;
}
#endif