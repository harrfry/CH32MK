#include <stdbool.h>
#include "usb.h"
#include "config.h"
#include "split.h"

static bool is_side_master = false;
static bool is_side_left = true;

uint8_t local_row_offset = 0;
uint8_t local_col_offset = 0;
uint8_t remote_row_offset = 0;
uint8_t remote_col_offset = 0;

bool is_master(void) {
    return is_side_master;
}

bool is_left(void) {
    return is_side_left;
}

void update_split_master(void) {
    if(tud_connected()) {
        is_side_master = true;
        return;
    }
}

#ifdef SPLIT_HAND_PIN
void split_hand_by_pin(void) {
    pin_t split_pin = SPLIT_HAND_PIN;
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = split_pin.PIN;
    GPIO_Init(split_pin.PORT, &GPIO_InitStructure);

    uint8_t value = GPIO_ReadInputDataBit(split_pin.PORT, split_pin.PIN);
    if(value) {
        is_side_left = true;
    } else {
        is_side_left = false;
    }
}
#endif

void split_side_update(void) {
    update_split_master();

    if(!is_side_master) {
        local_row_offset = 0;
        local_col_offset = 0;
        remote_col_offset = 0;
        remote_row_offset = 0;
    } else if(is_side_left) {
        local_row_offset = 0;
        local_col_offset = 0;
        remote_row_offset = ROW_OFFSET;
        remote_col_offset = COL_OFFSET;
    } else {
        local_row_offset = ROW_OFFSET;
        local_col_offset = COL_OFFSET;
        remote_row_offset = 0;
        remote_col_offset = 0;
    }
}

