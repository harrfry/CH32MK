/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2021/06/06
 * Description        : Main program body.
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*
 *@Note
 *USART Print debugging routine:
 *USART1_Tx(PA9).
 *This example demonstrates using USART1(PA9) as a print debug port output.
 *
 */
#include "ch32v20x.h"
#include "config.h"
#include "gpio.h"
#include "matrix.h"
#include "systick.h"
#include "debounce.h"
#include "usb.h"
#include "process_matrix.h"
#include "engine.h"
#include "split.h"
#include <stdio.h>
#include "engine/mouse/mouse.h"
#include "engine/macro/macro.h"
#include "split_side.h"

/* Global typedef */

/* Global define */

/* Global Variable */

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
bool matrix_raw[MATRIX_ROWS][MATRIX_COLS] = {0};
volatile bool matrix_debounced[MATRIX_ROWS][MATRIX_COLS] = {0};
bool matrix_previous[MATRIX_ROWS][MATRIX_COLS] = {0};

const pin_t row_pins[] = ROW_PINS;
const pin_t col_pins[] = COL_PINS;

void print_matrix_task();


int main(void)
{
    SystemInit();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SysTick_Init();
    init_usb_clocks();
    init_usb();
    
    init_matrix_pins(row_pins, col_pins);
    split_transport_init();
    #ifdef SPLIT_HAND_PIN
    split_hand_by_pin();
    #endif

    while(1)
    {

        split_side_update();

        tud_task();
        matrix_scan_raw(row_pins, col_pins, matrix_raw);
        debounce(matrix_raw, matrix_debounced);
        if(is_master()) {
            process_matrix_changed(matrix_debounced, matrix_previous);
            if(tud_hid_n_ready(0)) { // this check must be performed or otherwise keypresses get swallowed
                process_keyboard_queue(); // only process through the queue when the hid endpoint is ready
                send_keyboard_report_to_host(); // ship em off
                tud_task(); // idk call this for good measure
                macro_task(sys_ticks_ms);
            }
            if(tud_hid_n_ready(1)) {
                mouse_housekeeping_task();
                send_mouse_report_to_host();
                tud_task();
            }
        } else {
            slave_process_matrix(matrix_debounced, matrix_previous);
        }

        split_housekeeping_task(matrix_debounced, is_master());
    }
}

void print_matrix_task() {
    static uint32_t previous = 0;
    uint32_t current_time = sys_ticks_ms;
    if(current_time - previous >= 1000) {
            print_matrix_state(matrix_debounced);
            previous = current_time;
    }
}
