#include "config.h"
#include "gpio.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define CHARGE_DELAY_36() __asm__ volatile (".rept 36 \n\t nop \n\t .endr")
#define CHARGE_DELAY_144() __asm__ volatile (".rept 144 \n\t nop \n\t .endr")

#ifndef MATRIX_ROWS_PER_HALF
#define MATRIX_ROWS_PER_HALF MATRIX_ROWS
#endif

#ifndef MATRIX_COLS_PER_HALF
#define MATRIX_COLS_PER_HALF MATRIX_COLS
#endif

#if defined(ROW2COL) || defined(COL2ROW)
void matrix_scan_raw(const pin_t *row_pins, const pin_t *col_pins, bool matrix_raw[MATRIX_ROWS][MATRIX_COLS]) {

    #ifdef ROW2COL
        for(uint8_t i = 0; i < MATRIX_ROWS_PER_HALF; i++) {
            GPIO_WriteBit(row_pins[i].PORT, row_pins[i].PIN, Bit_SET);
            CHARGE_DELAY_144();
            for(uint8_t j = 0; j < MATRIX_COLS_PER_HALF; j++) {
                matrix_raw[i][j] = GPIO_ReadInputDataBit(col_pins[j].PORT, col_pins[j].PIN);
                CHARGE_DELAY_36();
            }
            GPIO_WriteBit(row_pins[i].PORT, row_pins[i].PIN, Bit_RESET);
            CHARGE_DELAY_144();
        }
    #endif
    #ifdef COL2ROW
    for(uint8_t i = 0; i < MATRIX_COLS_PER_HALF; i++) {
            GPIO_WriteBit(col_pins[i].PORT, col_pins[i].PIN, Bit_SET);
            CHARGE_DELAY_144(); // fuck ass charge delay because fuck ass electricity is fuck ass electricity
            for(uint8_t j = 0; j < MATRIX_ROWS_PER_HALF; j++) {
                matrix_raw[j][i] = (GPIO_ReadInputDataBit(row_pins[j].PORT, row_pins[j].PIN) == 1);
                CHARGE_DELAY_36();
            }
            GPIO_WriteBit(col_pins[i].PORT, col_pins[i].PIN, Bit_RESET);
            CHARGE_DELAY_144(); // another fuck ass delay because fuck ass electricity is fuck ass electricity
        }
    #endif
}
#endif

void print_matrix_state(volatile bool matrix[MATRIX_ROWS][MATRIX_COLS]) {

    printf("MATRIX_STATE:\n\r");
    for(uint8_t r = 0; r < MATRIX_ROWS; r++) {
        printf("Row %u: ", r);
        for(uint8_t c = 0; c < MATRIX_COLS; c++) {
            printf("%d ", matrix[r][c]);
        }
        printf("\n\r");
    }

}