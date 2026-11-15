#include "config.h"
#include <stdint.h>
#include <stdbool.h> 
#include "systick.h"
#include "split_side.h"

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
        uint8_t ridx = r + local_row_offset;
        for(uint8_t c = 0; c < MATRIX_COLS_PER_HALF; c++) {
            uint8_t cidx = c + local_col_offset;
            uint32_t last_debounce_time = debounce_timers[ridx][cidx];

            if(matrix_raw[ridx][cidx] != matrix_cleaned[ridx][cidx]) {
                // if the debounce timer is 0, then we set the lockout to the debounce window
                if(debounce_timers[ridx][cidx] == 0) {
                    debounce_timers[ridx][cidx] = current_time;
                }

                // otherwise if enough time has passed, then we update the keypress
                else if ((current_time - last_debounce_time) >= DEBOUNCE) {
                    matrix_cleaned[ridx][cidx] = matrix_raw[ridx][cidx];
                    debounce_timers[ridx][cidx] = 0; // reset the lockout window
                    matrix_did_change = true;
                }
            } else {
                debounce_timers[ridx][cidx] = 0;
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

    for(uint8_t r = 0; r < MATRIX_ROWS_PER_HALF; r++)  {
        uint8_t ridx = r + local_row_offset;

        for(uint8_t c = 0; c < MATRIX_COLS_PER_HALF; c++) {
            uint8_t cidx = c + local_col_offset;
            // if the key state changed and we are not in the lockout window then update immediately
            if((matrix_raw[ridx][cidx] != matrix_cleaned[ridx][cidx]) && ((current_time - debounce_timers[ridx][cidx]) >= DEBOUNCE)) {
                matrix_cleaned[ridx][cidx] = matrix_raw[ridx][cidx];
                debounce_timers[ridx][cidx] = current_time;

                matrix_did_change = true;
            }
        }

    }
    return matrix_did_change;
}
#endif